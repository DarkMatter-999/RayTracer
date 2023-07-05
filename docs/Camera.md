# Camera Class

## Overview

The `Camera` class represents a camera in a raytracing project. It provides functionality to manipulate the camera's position, rotation, and projection matrix. The camera is responsible for generating rays in the scene based on its position and projection settings.

## Member Variables

-   `position`: Represents the position of the camera in 3D space.
-   `rotation`: Represents the rotation of the camera.
-   `projection`: Represents the projection matrix used for transforming world coordinates to screen coordinates.
-   `moveSpeed`: Controls the speed of camera movement.
-   `mouseSens`: Controls the sensitivity of mouse movement for camera rotation.
-   `lockMouse`: Specifies whether the mouse movement should be locked.
-   `oldMouseX`, `oldMouseY`: Stores the previous mouse coordinates for calculating mouse movement delta.
-   `newMouseX`, `newMouseY`: Stores the current mouse coordinates for calculating mouse movement delta.
-   `distance`: Distance of the camera from the target point.
-   `angle`: Angle of the camera around the target point.
-   `verticalAngle`: Vertical angle of the camera.
-   `horizontalAngle`: Horizontal angle of the camera.
-   `FOV`: Field of view of the camera.
-   `nearClip`: Near clipping plane distance for the camera.
-   `farClip`: Far clipping plane distance for the camera.

## Constructor

    Camera(const Vector3f& position, const Vector3f& rotation, float FOV, float nearClip, float farClip, float width, float height)

Creates a new `Camera` object with the specified position, rotation, field of view, clipping plane distances, and screen dimensions.

#### Parameters:

-   `position`: The initial position of the camera.
-   `rotation`: The initial rotation of the camera.
-   `FOV`: The field of view of the camera in degrees.
-   `nearClip`: The distance to the near clipping plane.
-   `farClip`: The distance to the far clipping plane.
-   `width`: The width of the screen or viewport.
-   `height`: The height of the screen or viewport.

## Member Functions

### Update

Updates the camera's position and rotation based on user input and mouse movement. This function should be called every frame to ensure smooth camera movement.

### OnResize

Handles the resizing of the screen or viewport. This function updates the camera's projection matrix based on the new screen dimensions.

#### Parameters:

-   `width`: The new width of the screen or viewport.
-   `height`: The new height of the screen or viewport.

### getPosition

Returns the current position of the camera.

#### Returns:

A `Vector3f` object representing the camera's position.

### getRotation

Returns the current rotation of the camera.

#### Returns:

A `Vector3f` object representing the camera's rotation.

### getProjection

Returns the projection matrix of the camera.

#### Returns:

A `Matrix4f` object representing the camera's projection matrix.
