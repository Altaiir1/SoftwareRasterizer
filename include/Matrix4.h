#pragma once

#include <cmath>
#include "Vector3.h"

// 4x4 matrix for 3D transformations
struct Matrix4 {
    float m[4][4]; // Row-major: m[row][column]

    // Constructor - creates identity matrix by default
    Matrix4() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] = i == j ? 1.0f : 0.0f;
            }
        }
    }

    // Matrix multiplication
    Matrix4 operator*(const Matrix4 &other) const {
        Matrix4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; ++k) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }

    // Transform a 3D point (multiply matrix by vector)
    Vector3 Transform(const Vector3& v) const {
        float x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
        float y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
        float z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
        float w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];

        // Perspective divide (homogeneous coordinates)
        if (w != 0.0f) {
            x /= w;
            y /= w;
            z /= w;
        }

        return Vector3(x, y, z);
    }

    // Create rotation matrix around X axis
    static Matrix4 RotationX(float angle) {
        Matrix4 mat;
        float c = cos(angle);
        float s = sin(angle);

        mat.m[1][1] = c;
        mat.m[1][2] = -s;
        mat.m[2][1] = s;
        mat.m[2][2] = c;

        return mat;
    }

    // Create rotation matrix around Y axis
    static Matrix4 RotationY(float angle) {
        Matrix4 mat;
        float c = cos(angle);
        float s = sin(angle);

        mat.m[0][0] = c;
        mat.m[0][2] = s;
        mat.m[2][0] = -s;
        mat.m[2][2] = c;

        return mat;
    }

    // Create rotation matrix around Z axis
    static Matrix4 RotationZ(float angle) {
        Matrix4 mat;
        float c = cos(angle);
        float s = sin(angle);

        mat.m[0][0] = c;
        mat.m[0][1] = -s;
        mat.m[1][0] = s;
        mat.m[1][1] = c;

        return mat;
    }

    // Create translation matrix
    static Matrix4 Translation(float x, float y, float z) {
        Matrix4 mat;
        mat.m[0][3] = x;
        mat.m[1][3] = y;
        mat.m[2][3] = z;
        return mat;
    }

    // Create perspective projection matrix
    static Matrix4 Perspective(float fov, float aspect, float near, float far) {
        Matrix4 mat;
        float tanHalfFov = tan(fov / 2.0f);

        mat.m[0][0] = 1.0f / (aspect * tanHalfFov);
        mat.m[1][1] = 1.0f / tanHalfFov;
        mat.m[2][2] = -(far + near) / (far - near);
        mat.m[2][3] = -(2.0f * far * near) / (far - near);
        mat.m[3][2] = -1.0f;
        mat.m[3][3] = 0.0f;

        return mat;
    }
};
