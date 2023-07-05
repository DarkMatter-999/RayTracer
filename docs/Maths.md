# Maths Header Documentation

## `toRadians(double degree)`

Converts the specified degree value to radians.

**Parameters:**

- `degree`: The degree value to convert to radians.

**Returns:**

- The converted value in radians.

## `Vector2f` Class

### `Vector2f(float x, float y)`

Creates a new `Vector2f` object with the specified x and y values.

**Parameters:**

- `x`: The x value of the vector.
- `y`: The y value of the vector.

### `void set(float x, float y)`

Sets the x and y values of the vector.

**Parameters:**

- `x`: The new x value.
- `y`: The new y value.

### Static Member Functions

- `static Vector2f add(Vector2f vector1, Vector2f vector2)`
- `static Vector2f subtract(Vector2f vector1, Vector2f vector2)`
- `static Vector2f multiply(Vector2f vector1, Vector2f vector2)`
- `static Vector2f divide(Vector2f vector1, Vector2f vector2)`
- `static float length(Vector2f vector)`
- `static Vector2f normalize(Vector2f vector)`
- `static float dot(Vector2f vector1, Vector2f vector2)`

## `Vector3f` Class

### `Vector3f(float x, float y, float z)`

Creates a new `Vector3f` object with the specified x, y, and z values.

**Parameters:**

- `x`: The x value of the vector.
- `y`: The y value of the vector.
- `z`: The z value of the vector.

### `void set(float x, float y, float z)`

Sets the x, y, and z values of the vector.

**Parameters:**

- `x`: The new x value.
- `y`: The new y value.
- `z`: The new z value.

### Static Member Functions

- `static Vector3f add(Vector3f vector1, Vector3f vector2)`
- `static Vector3f subtract(Vector3f vector1, Vector3f vector2)`
- `static Vector3f multiply(Vector3f vector1, Vector3f vector2)`
- `static Vector3f divide(Vector3f vector1, Vector3f vector2)`
- `static float length(Vector3f vector)`
- `static Vector3f normalize(Vector3f vector)`
- `static float dot(Vector3f vector1, Vector3f vector2)`

## `Matrix4f` Class

### Static Member Functions

- `static Matrix4f identity()`
- `static Matrix4f translate(Vector3f translation)`
- `static Matrix4f rotate(float angle, Vector3f axis)`
- `static Matrix4f scale(Vector3f scalar)`
- `static Matrix4f multiply(Matrix4f matrix, Matrix4f other)`
- `static Matrix4f transform(Vector3f position, Vector3f rotation, Vector3f scale)`
- `static Matrix4f perspective(float fov, float aspect, float near, float far)`
- `static Matrix4f view(Vector3f position, Vector3f rotation)`

### Member Functions

- `float get(int r, int c)`
- `void set(int r, int c, float val)`
- `float* getAll()`
