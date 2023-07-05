# Input Class

## Overview

The `Input` class provides functionality for handling input events in a raytracing project. It allows you to check for key presses, mouse button presses, and retrieve mouse position and scroll values.

## Constructor

### `Input(GLFWwindow* window)`

Creates a new `Input` object with the specified GLFW window.

**Parameters:**

- `window`: A pointer to the GLFW window.

## Member Functions

### `void Update()`

Updates the input state. This function should be called every frame to handle input events.

### `static bool IsKeyPressed(ImGuiKey key)`

Checks whether the specified ImGui key is currently pressed.

**Parameters:**

- `key`: The ImGui key to check.

**Returns:**

- `true` if the key is currently pressed, `false` otherwise.

### `static bool IsMouseButtonPressed(ImGuiMouseButton button)`

Checks whether the specified ImGui mouse button is currently pressed.

**Parameters:**

- `button`: The ImGui mouse button to check.

**Returns:**

- `true` if the mouse button is currently pressed, `false` otherwise.

### `static double GetMouseX()`

Gets the current x-coordinate of the mouse cursor.

**Returns:**

- The current x-coordinate of the mouse cursor.

### `static double GetMouseY()`

Gets the current y-coordinate of the mouse cursor.

**Returns:**

- The current y-coordinate of the mouse cursor.

### `static double GetScrollX()`

Gets the horizontal scroll value of the mouse wheel.

**Returns:**

- The horizontal scroll value of the mouse wheel.

### `static double GetScrollY()`

Gets the vertical scroll value of the mouse wheel.

**Returns:**

- The vertical scroll value of the mouse wheel.

### `void mouseState(bool state)`

Sets the state of the mouse cursor.

**Parameters:**

- `state`: The state of the mouse cursor (`true` for visible, `false` for hidden).

### `void setMouseLock(bool state)`

Sets the lock state of the mouse cursor.

**Parameters:**

- `state`: The lock state of the mouse cursor (`true` for locked, `false` for unlocked).
