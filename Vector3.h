#pragma once

#include <cmath>

class Vector3
{
public:
	double x, y, z;
	explicit Vector3(double x_ = 0, double y_ = 0, double z_ = 0);
	Vector3(const Vector3& d) { x = d.x; y = d.y; z = d.z; }
	~Vector3();

	
	double length();
	Vector3 normalize() const;
	Vector3 operator+(const Vector3& d) const;
	Vector3 operator-(const Vector3& d) const;
	void operator*=(double f) { x *= f; y *= f; z *= f; }
	Vector3 operator*(double f) { return Vector3(x * f, y * f, z *f); }
	// void operator*=(Vector3& )
	double dot(const Vector3& d) const;
	Vector3 operator/(double v) const;
	Vector3 reflect(const Vector3& N);
	Vector3 refract(const Vector3& N, double n);

	static Vector3 zero() { return Vector3(0, 0, 0); }

};

