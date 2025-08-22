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

// DLL_EXPORT table* screen_write_text(table* args[]) {
//     table *text = args[0];
//     table *x = args[1];
//     table *y = args[2];
//     table *r = args[3];
//     table *g = args[4];
//     table *b = args[5];

//     string str = __convert_to_string(text->f_str_v);

//     SDL_SetRenderDrawColor(renderer, r->cval, g->cval, b->cval, 255);
//     SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 800, 600, 32, SDL_PIXELFORMAT_RGBA32);
//     SDL_FRect rect = {static_cast<float>(x->cval), static_cast<float>(y->cval), 800.0f, 600.0f};
//     SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
//     SDL_FreeSurface(surface);

//     SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//     SDL_SetTextureAlphaMod(texture, 255);
//     SDL_SetTextureColorMod(texture, r->cval, g->cval, b->cval);

//     SDL_RenderCopy(renderer, texture, NULL, &rect);
//     SDL_DestroyTexture(texture);

//     SDL_RenderPresent(renderer);

//     return MER_VALUE(0);
// }

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