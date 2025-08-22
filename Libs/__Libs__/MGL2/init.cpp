#include <SDL3/SDL.h>
#include <Mercury.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool user_quit = false;

struct Cube {
    float x;
    float y;
    float width;
    float height;

    uint8_t address;
};

uint8_t start_address = 0x00;
std::vector<Cube> cubes;

START_DLL

DLL_EXPORT table* init(table *args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "[ERROR] SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    table* width = args[0];
    table* height = args[1];
    table* name = args[2];

    string str = __convert_to_string(name->f_str_v);

    window = SDL_CreateWindow(str.c_str(), width->cval, height->cval, SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cout << "[ERROR] Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, nullptr);

    return MER_VALUE(0);
}

DLL_EXPORT table* flip(table* args[]) {
    if (!renderer) {
        return MER_VALUE(0);
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            user_quit = true;
            exit(1);
        }
    }

    SDL_RenderPresent(renderer);

    return MER_VALUE(0);
}

DLL_EXPORT table* draw_square(table* args[]) {
    if (!renderer) {
        return MER_VALUE(0);
    }

    float x = args[0]->cval;
    float y = args[1]->cval;
    float width  = args[2]->cval;
    float height = args[3]->cval;

    int r = args[4]->cval;
    int g = args[5]->cval;
    int b = args[6]->cval;
    
    SDL_FRect *rect = new SDL_FRect;
    rect->x = x;
    rect->y = y;
    rect->w = width;
    rect->h = height;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, rect);

    delete rect;
    return MER_VALUE(0);
}

DLL_EXPORT table* quit(table *args[]) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return MER_VALUE(0);
}

DLL_EXPORT int true_quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

DLL_EXPORT int get_input_char() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            SDL_Keycode key = event.key.key;

            if (key >= 'a' && key <= 'z') {
                return 'a' + (key - 'a');
            }
            else if (key >= SDLK_0 && key <= SDLK_9) {
                return '0' + (key - SDLK_0);
            }
            else {
                switch (key) {
                    case SDLK_RETURN:  return '\n';
                    case SDLK_SPACE:   return ' ';
                    case SDLK_ESCAPE:  return 27;
                    default: return 0;
                }
            }
        }
        else if (event.type == SDL_EVENT_QUIT) {
            user_quit = true;
            exit(1);
        }
    }
    
    return 0;
}

DLL_EXPORT table* draw_image(table* args[]) {
    if (!renderer) {
        return MER_VALUE(0);
    }

    string path = __convert_to_string(args[0]->f_str_v);
    float x = args[1]->cval;
    float y = args[2]->cval;
    float w = args[3]->cval;
    float h = args[4]->cval;

    // Load BMP (nếu muốn PNG/JPG thì cần SDL_image)
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        std::cout << "[ERROR] Failed to load image: " << SDL_GetError() << std::endl;
        return MER_VALUE(0);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);   // SDL3: SDL_FreeSurface -> SDL_DestroySurface

    if (!texture) {
        std::cout << "[ERROR] Failed to create texture: " << SDL_GetError() << std::endl;
        return MER_VALUE(0);
    }

    SDL_FRect dstRect = {x, y, w, h};
    SDL_RenderTexture(renderer, texture, nullptr, &dstRect); // SDL3: SDL_RenderCopy -> SDL_RenderTexture

    SDL_DestroyTexture(texture);

    return MER_VALUE(0);
}

DLL_EXPORT table* draw_line_circle(table* args[]) {
    if (!renderer) {
        return MER_VALUE(0);
    }

    float cx = args[0]->cval;
    float cy = args[1]->cval;
    float radius = args[2]->cval;
    int r = args[3]->cval;
    int g = args[4]->cval;
    int b = args[5]->cval;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    int x = (int)radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        SDL_RenderPoint(renderer, cx + x, cy + y);  // SDL3: SDL_RenderDrawPoint -> SDL_RenderPoint
        SDL_RenderPoint(renderer, cx + y, cy + x);
        SDL_RenderPoint(renderer, cx - y, cy + x);
        SDL_RenderPoint(renderer, cx - x, cy + y);
        SDL_RenderPoint(renderer, cx - x, cy - y);
        SDL_RenderPoint(renderer, cx - y, cy - x);
        SDL_RenderPoint(renderer, cx + y, cy - x);
        SDL_RenderPoint(renderer, cx + x, cy - y);

        y += 1;
        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x -= 1;
            err -= 2 * x + 1;
        }
    }

    return MER_VALUE(0);
}

DLL_EXPORT table* draw_line_ellipse(table* args[]) {
    if (!renderer) {
        return MER_VALUE(0);
    }

    float cx = args[0]->cval;
    float cy = args[1]->cval;
    float a = args[2]->cval;
    float b = args[3]->cval;
    int r = args[4]->cval;
    int g = args[5]->cval;
    int bb = args[6]->cval;

    SDL_SetRenderDrawColor(renderer, r, g, bb, 255);

    for (float theta = 0; theta < 2 * M_PI; theta += 0.01f) {
        float x = a * cos(theta);
        float y = b * sin(theta);
        SDL_RenderPoint(renderer, (int)(cx + x), (int)(cy + y));
    }

    return MER_VALUE(0);
}

DLL_EXPORT table* draw_arc(table* args[]) {
    if (!renderer) {
        return MER_VALUE(0);
    }

    float cx = args[0]->cval;
    float cy = args[1]->cval;
    float radius = args[2]->cval;
    float start_angle = args[3]->cval;
    float end_angle   = args[4]->cval;
    int r = args[5]->cval;
    int g = args[6]->cval;
    int b = args[7]->cval;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    for (float theta = start_angle; theta <= end_angle; theta += 0.01f) {
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        SDL_RenderPoint(renderer, (int)(cx + x), (int)(cy + y));
    }

    return MER_VALUE(0);
}

DLL_EXPORT table* draw_filled_ellipse(table* args[]) {
    if (!renderer) {
        return MER_VALUE(0);
    }

    float cx = args[0]->cval;
    float cy = args[1]->cval;
    float a = args[2]->cval;
    float b = args[3]->cval;
    int r = args[4]->cval;
    int g = args[5]->cval;
    int bb = args[6]->cval;

    SDL_SetRenderDrawColor(renderer, r, g, bb, 255);

    for (int y = -b; y <= b; y++) {
        float dx = a * sqrt(1 - (y * y) / (b * b));
        SDL_RenderLine(renderer,                     // SDL3: SDL_RenderDrawLine -> SDL_RenderLine
                       (int)(cx - dx), (int)(cy + y),
                       (int)(cx + dx), (int)(cy + y));
    }

    return MER_VALUE(0);
}

DLL_EXPORT table* draw_filled_circle(table* args[]) {
    if (!renderer) {
        return MER_VALUE(0);
    }

    float cx = args[0]->cval;
    float cy = args[1]->cval;
    float radius = args[2]->cval;
    int r = args[3]->cval;
    int g = args[4]->cval;
    int b = args[5]->cval;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    int rad = (int)radius;
    for (int y = -rad; y <= rad; y++) {
        int dx = (int)(sqrt(radius * radius - y * y));
        SDL_RenderLine(renderer,
                       (int)(cx - dx), (int)(cy + y),
                       (int)(cx + dx), (int)(cy + y));
    }

    return MER_VALUE(0);
}

DLL_EXPORT table* __get_input_char(table* args[]) {
    table* result = MerCompiler_Table_new();
    result->is_str = true;
    result->f_str_v = creat_char_obj(static_cast<uint8_t>(get_input_char()));
    return result;
}

DLL_EXPORT table* fill_screen(table* args[]) {
    float arr[3] = {args[0]->cval, args[1]->cval, args[2]->cval};
    SDL_SetRenderDrawColor(renderer, arr[0], arr[1], arr[2], 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return MER_VALUE(0);
}

DLL_EXPORT table* is_quit(table *args[]) {
    return MER_VALUE(user_quit);
}

END_DLL