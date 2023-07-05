# Shader Class

## Constructor

### `Shader(const char* vertexPath, const char* fragmentPath)`

Creates a new `Shader` object with the specified vertex and fragment shader file paths.

**Parameters:**

- `vertexPath`: The file path of the vertex shader.
- `fragmentPath`: The file path of the fragment shader.

## Member Functions

### `void use()`

Sets the current shader as the active shader.

### `void setInt(const std::string& name, int value) const`

Sets an integer uniform value in the shader.

**Parameters:**

- `name`: The name of the uniform variable.
- `value`: The integer value to set.

### `void setFloat(const std::string& name, float value) const`

Sets a float uniform value in the shader.

**Parameters:**

- `name`: The name of the uniform variable.
- `value`: The float value to set.

### `void setMat4(const std::string& name, const float* value) const`

Sets a 4x4 matrix uniform value in the shader.

**Parameters:**

- `name`: The name of the uniform variable.
- `value`: A pointer to the array representing the matrix value.

### `void setVec2(const std::string& name, float x, float y) const`

Sets a 2D vector uniform value in the shader.

**Parameters:**

- `name`: The name of the uniform variable.
- `x`: The x component of the vector.
- `y`: The y component of the vector.

### `void setVec3(const std::string& name, float x, float y, float z) const`

Sets a 3D vector uniform value in the shader.

**Parameters:**

- `name`: The name of the uniform variable.
- `x`: The x component of the vector.
- `y`: The y component of the vector.
- `z`: The z component of the vector.

### `void setUniform(const std::string& name, int value) const`

Alias for `setInt(const std::string& name, int value) const`.

### `void setUniform(const std::string& name, float value) const`

Alias for `setFloat(const std::string& name, float value) const`.

### `void setUniform(const std::string& name, const float* value) const`

Alias for `setMat4(const std::string& name, const float* value) const`.

### `void setUniform(const std::string& name, float x, float y) const`

Alias for `setVec2(const std::string& name, float x, float y) const`.

### `void setUniform(const std::string& name, float x, float y, float z) const`

Alias for `setVec3(const std::string& name, float x, float y, float z) const`.
