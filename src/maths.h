#ifndef MATHS_H
#define MATHS_H

#include <cmath>
double toRadians(double degree);

class Vector2f {
   public:
    float x, y;

    Vector2f(float x, float y);
    void set(float x, float y);

    static Vector2f add(Vector2f vector1, Vector2f vector2);
    static Vector2f subtract(Vector2f vector1, Vector2f vector2);
    static Vector2f multiply(Vector2f vector1, Vector2f vector2);
    static Vector2f divide(Vector2f vector1, Vector2f vector2);
    static float length(Vector2f vector);
    static Vector2f normalize(Vector2f vector);
    static float dot(Vector2f vector1, Vector2f vector2);
};

class Vector3f {
   public:
    float x, y, z;

    Vector3f(float x, float y, float z);
    void set(float x, float y, float z);

    static Vector3f add(Vector3f vector1, Vector3f vector2);
    static Vector3f subtract(Vector3f vector1, Vector3f vector2);
    static Vector3f multiply(Vector3f vector1, Vector3f vector2);
    static Vector3f divide(Vector3f vector1, Vector3f vector2);
    static float length(Vector3f vector);
    static Vector3f normalize(Vector3f vector);
    static float dot(Vector3f vector1, Vector3f vector2);
};

class Matrix4f {
    static const int SIZE = 4;
    float element[SIZE * SIZE];

   public:
    static Matrix4f identity();
    static Matrix4f translate(Vector3f translation);
    static Matrix4f rotate(float angle, Vector3f axis);
    static Matrix4f scale(Vector3f scalar);
    static Matrix4f multiply(Matrix4f matrix, Matrix4f other);
    float get(int r, int c);
    void set(int r, int c, float val);
    float* getAll();
    static Matrix4f transform(Vector3f position, Vector3f rotation, Vector3f scale);
    static Matrix4f perspective(float fov, float aspect, float near, float far);
    static Matrix4f view(Vector3f position, Vector3f rotation);
};

#endif  // MATHS_H
