#include "maths.h"

double toRadians(double degree) {
    double pi = 3.14159265359;
    return (degree * (pi / 180));
}

// Vector3f

Vector2f::Vector2f(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vector2f::set(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2f Vector2f::add(Vector2f vector1, Vector2f vector2) {
    return Vector2f(vector1.x + vector2.x, vector1.y + vector2.y);
}

Vector2f Vector2f::subtract(Vector2f vector1, Vector2f vector2) {
    return Vector2f(vector1.x - vector2.x, vector1.y - vector2.y);
}

Vector2f Vector2f::multiply(Vector2f vector1, Vector2f vector2) {
    return Vector2f(vector1.x * vector2.x, vector1.y * vector2.y);
}

Vector2f Vector2f::divide(Vector2f vector1, Vector2f vector2) {
    return Vector2f(vector1.x / vector2.x, vector1.y / vector2.y);
}

float Vector2f::length(Vector2f vector) {
    return (float)std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f Vector2f::normalize(Vector2f vector) {
    float len = length(vector);
    return divide(vector, Vector2f(len, len));
}

float Vector2f::dot(Vector2f vector1, Vector2f vector2) {
    return vector1.x * vector2.x + vector1.y * vector2.y;
}

// Vector3f
Vector3f::Vector3f(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3f::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3f Vector3f::add(Vector3f vector1, Vector3f vector2) {
    return Vector3f(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector3f Vector3f::subtract(Vector3f vector1, Vector3f vector2) {
    return Vector3f(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
}

Vector3f Vector3f::multiply(Vector3f vector1, Vector3f vector2) {
    return Vector3f(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z);
}

Vector3f Vector3f::divide(Vector3f vector1, Vector3f vector2) {
    return Vector3f(vector1.x / vector2.x, vector1.y / vector2.y, vector1.z / vector2.z);
}

float Vector3f::length(Vector3f vector) {
    return (float)std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vector3f Vector3f::normalize(Vector3f vector) {
    float len = length(vector);
    return divide(vector, Vector3f(len, len, len));
}

float Vector3f::dot(Vector3f vector1, Vector3f vector2) {
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

// Matrix4f
Matrix4f Matrix4f::identity() {
    Matrix4f res = Matrix4f();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            res.set(i, j, 0.0f);
            if (i == j) {
                res.set(i, j, 1);
            }
        }
    }
    return res;
}

Matrix4f Matrix4f::translate(Vector3f translation) {
    Matrix4f res = Matrix4f::identity();
    res.set(3, 0, translation.x);
    res.set(3, 1, translation.y);
    res.set(3, 2, translation.z);

    return res;
}

Matrix4f Matrix4f::rotate(float angle, Vector3f axis) {
    Matrix4f result = Matrix4f::identity();

    float cos = (float)std::cos(toRadians(angle));
    float sin = (float)std::sin(toRadians(angle));
    float C = 1 - cos;

    result.set(0, 0, cos + axis.x * axis.x * C);
    result.set(0, 1, axis.x * axis.y * C - axis.z * sin);
    result.set(0, 2, axis.x * axis.z * C + axis.y * sin);
    result.set(1, 0, axis.y * axis.x * C + axis.z * sin);
    result.set(1, 1, cos + axis.y * axis.y * C);
    result.set(1, 2, axis.y * axis.z * C - axis.x * sin);
    result.set(2, 0, axis.z * axis.x * C - axis.y * sin);
    result.set(2, 1, axis.z * axis.y * C + axis.x * sin);
    result.set(2, 2, cos + axis.z * axis.z * C);

    return result;
}

Matrix4f Matrix4f::scale(Vector3f scalar) {
    Matrix4f res = Matrix4f::identity();

    res.set(0, 0, scalar.x);
    res.set(1, 1, scalar.y);
    res.set(2, 2, scalar.z);

    return res;
}

Matrix4f Matrix4f::multiply(Matrix4f matrix, Matrix4f other) {
    Matrix4f result = Matrix4f::identity();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result.set(i, j, matrix.get(i, 0) * other.get(0, j) + matrix.get(i, 1) * other.get(1, j) + matrix.get(i, 2) * other.get(2, j) + matrix.get(i, 3) * other.get(3, j));
        }
    }

    return result;
}

float Matrix4f::get(int r, int c) {
    return element[c * SIZE + r];
}

void Matrix4f::set(int r, int c, float val) {
    element[c * SIZE + r] = val;
}

float* Matrix4f::getAll() {
    return element;
}

Matrix4f Matrix4f::transform(Vector3f position, Vector3f rotation, Vector3f scale) {
    Matrix4f result = Matrix4f::identity();

    Matrix4f translationMatrix = Matrix4f::translate(position);
    Matrix4f rotXMatrix = Matrix4f::rotate(rotation.x, Vector3f(1, 0, 0));
    Matrix4f rotYMatrix = Matrix4f::rotate(rotation.y, Vector3f(0, 1, 0));
    Matrix4f rotZMatrix = Matrix4f::rotate(rotation.z, Vector3f(0, 0, 1));
    Matrix4f scaleMatrix = Matrix4f::scale(scale);

    Matrix4f rotationMatrix = Matrix4f::multiply(rotXMatrix, Matrix4f::multiply(rotYMatrix, rotZMatrix));

    result = Matrix4f::multiply(translationMatrix, Matrix4f::multiply(rotationMatrix, scaleMatrix));

    return result;
}

Matrix4f Matrix4f::perspective(float fov, float aspect, float near, float far) {
    Matrix4f res = Matrix4f::identity();

    float tanFOV = (float)std::tan(toRadians(fov / 2));

    float zp = far + near;
    float zm = far - near;

    res.set(0, 0, 1.0f / (aspect * tanFOV));
    res.set(1, 1, 1 / (tanFOV));
    res.set(2, 2, -(zp / zm));
    res.set(3, 3, 0.0f);
    res.set(2, 3, -1.0f);
    res.set(3, 2, -((2.0f * far * near) / zm));

    return res;
}

Matrix4f Matrix4f::view(Vector3f position, Vector3f rotation) {
    Matrix4f result = Matrix4f::identity();

    Vector3f negposition = Vector3f(-position.x, -position.y, -position.z);

    Matrix4f translationMatrix = Matrix4f::translate(negposition);
    Matrix4f rotXMatrix = Matrix4f::rotate(rotation.x, Vector3f(1, 0, 0));
    Matrix4f rotYMatrix = Matrix4f::rotate(rotation.y, Vector3f(0, 1, 0));
    Matrix4f rotZMatrix = Matrix4f::rotate(rotation.z, Vector3f(0, 0, 1));

    Matrix4f rotationMatrix = Matrix4f::multiply(rotYMatrix, Matrix4f::multiply(rotZMatrix, rotXMatrix));

    result = Matrix4f::multiply(translationMatrix, rotationMatrix);

    return result;
}