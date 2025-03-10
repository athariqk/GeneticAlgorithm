#pragma once

struct Vector2D {
    float x, y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D &Add(const Vector2D &vec);
    Vector2D &Subtract(const Vector2D &vec);
    Vector2D &Multiply(const Vector2D &vec);
    Vector2D &Divide(const Vector2D &vec);

    Vector2D &Add(const float f);
    Vector2D &Subtract(const float f);
    Vector2D &Multiply(const float f);
    Vector2D &Divide(const float f);

    friend Vector2D &operator+(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator-(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator*(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator/(Vector2D &v1, const Vector2D &v2);

    Vector2D &operator+=(const Vector2D &vec);
    Vector2D &operator-=(const Vector2D &vec);
    Vector2D &operator*=(const Vector2D &vec);
    Vector2D &operator/=(const Vector2D &vec);

    Vector2D &operator+(const float &f);
    Vector2D &operator-(const float &f);
    Vector2D &operator*(const float &f);
    Vector2D &operator/(const float &f);

    Vector2D &operator*(const int &i);
    Vector2D &Zero();

    float Length() const;
    float LengthSqr() const;

    static Vector2D Lerp(const Vector2D &vec1, const Vector2D &vec2, float amount);
};
