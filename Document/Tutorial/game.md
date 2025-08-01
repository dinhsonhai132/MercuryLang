# MercuryLang Game Library (MGL)

**Library Name:** MGL
**Last Update:** 7/9/2025
**Created by:** dinhsonhai132
**License:** Free to modify and use

The **Mercury Game Library (MGL)** is a lightweight 2D game framework for MercuryLang. It provides tools for creating windows, drawing shapes, handling input, and managing a basic game loop.

---

## 1. Initialization

### 1.1 `screen_init(width, height)`

Creates a new game window with the given width and height.

```mercury
screen_init(500, 500)
```

---

### 1.2 `screen_quit()`

Closes the game window and exits the graphics system.

```mercury
screen_quit()
```

---

## 2. Rendering Functions

### 2.1 `screen_fill(r, g, b)`

Fills the entire screen with the specified color (RGB values 0-255).

```mercury
screen_fill(0, 0, 0) # Clear screen to black
```

### 2.2 `screen_draw(x, y, w, h, r, g, b)`

Draws a **colored rectangle** at position `(x, y)` with width `w` and height `h`.

```mercury
screen_draw(0, 450, 50, 50, 255, 255, 255) # Draw a white cube
```

### 2.3 `screen_flip()`

Updates the window with the latest frame buffer (double buffering).

```mercury
screen_flip()
```

---

## 3. Input Functions

### 3.1 `key_pressed()`

Returns the **key code** of the currently pressed key.

### 3.2 `get_key_char(key_code)`

Converts a key code to a readable **string character**.

```mercury
let key = get_key_char(key_pressed())
if same(key, "a") then
    cube_x -= 5
end
```

---

## 4. Example: Moving a Cube

```mercury
import "MGL" # Mercury Game Library

screen_width = 500
screen_height = 500
screen_init(screen_width, screen_height)

cube_width = 50
cube_height = 50
cube_x = 0
cube_y = screen_height - cube_height
cube_vel = 5
cube_color = [255, 255, 255]

while true do
    screen_fill(0, 0, 0)

    screen_draw(cube_x, cube_y, cube_width, cube_height, cube_color[0], cube_color[1], cube_color[2])

    let key = get_key_char(key_pressed())

    if same(key, "a") then
        cube_x -= cube_vel
    end

    if same(key, "d") then
        cube_x += cube_vel
    end

    if cube_x >= screen_width - cube_width then
        cube_x = screen_width - cube_width
    end

    if cube_x <= 0 then
        cube_x = 0
    end

    screen_flip()
end

screen_quit()
```

---

## 5. Summary

MGL provides a simple interface for:

* Creating windows and managing the game loop
* Drawing shapes and filling the screen with colors
* Handling keyboard input for interactive games

This library is perfect for **beginners** who want to create **2D games** quickly in MercuryLang.
