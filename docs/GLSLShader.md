# Ray Tracing Shader Documentation

This documentation provides an overview of the Ray Tracing shader code. The shader is responsible for simulating the interaction of light rays with spheres in a 3D scene.

## Shader Inputs

The shader accepts the following inputs:

- `iResolution`: A 2D vector representing the resolution of the output image.
- `position`: A 3D vector representing the position of the camera.
- `dimension`: A 2D vector representing the dimensions of the frame.
- `delta`: A 2D vector representing the change in position.
- `rotation`: A 3D vector representing the rotation angles.
- `maxBounces`: An integer representing the maximum number of ray bounces.
- `raysPerPixel`: An integer representing the number of rays to cast per pixel.
- `frameNo`: An integer representing the frame number.
- `focus`: A float representing the focus of the camera.
- `envEnable`: A boolean indicating whether the environment is enabled.
- `GroundColour`: A 3D vector representing the color of the ground.
- `SkyColourHorizon`: A 3D vector representing the color of the sky at the horizon.
- `SkyColourZenith`: A 3D vector representing the color of the sky at the zenith.
- `SunDirection`: A 3D vector representing the direction of the sun.
- `SunFocus`: A float representing the focus of the sun.
- `SunIntensity`: A float representing the intensity of the sun.
- `AirRefractiveIndex`: A float representing the refractive index of air.
- `focusSensitivity`: A float representing the sensitivity of the focus.

## Shader Outputs

The shader outputs the following:

- `FragColor`: A 4D vector representing the color of the pixel.

## Functions

The shader code includes the following functions:

- `perspective(fovy, aspect, near, far)`: Calculates the perspective projection matrix.
- `lookAt(eye, at, up)`: Calculates the view matrix based on the camera position, target, and up vector.
- `RecalculateProjection()`: Recalculates the projection matrix.
- `translate(translation)`: Creates a translation matrix.
- `rotate(angle, axis)`: Creates a rotation matrix.
- `view(position, rotation)`: Creates the view matrix based on the position and rotation.
- `RecalculateView()`: Recalculates the view matrix.
- `RaySphere(ray, spherePosition, radius)`: Computes the intersection of a ray with a sphere.
- `CalculateRayCollision(ray)`: Finds the closest intersection of a ray with the scene spheres.
- `pcg_hash(state)`: Hashes the given state value using the PCG algorithm.
- `pcg_hash_to_float(state)`: Converts the hashed state value to a float in the range [0, 1).
- `randomNormalDistribution(state)`: Generates a random number from a normal distribution.
- `randomDirection(state)`: Generates a random direction vector.
- `randomHemisphereDirection(normal, state)`: Generates a random direction within a hemisphere.
- `RefractRay(incidentDir, normal, refractiveIndex, state)`: Computes the refracted direction of a ray.
- `getEnvironmentColor(direction)`: Retrieves the color from the environment map based on the given direction.
- `TraceRay(origin, direction, depth, state)`: Traces a ray through the scene and computes the resulting color.


## Shader Logic

The shader follows the following logic:

1. Recalculate the projection and view matrices based on the camera parameters.
2. Calculate the target position based on the normalized device coordinates.
3. Iterate over each pixel and cast multiple rays per pixel.
4. Trace each ray through the scene, calculating the intersections with spheres and computing the lighting.
5. Calculate the final pixel color based on the accumulated lighting and background colors.
6. Output the final pixel color.
