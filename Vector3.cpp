#include "stdafx.h"
#include "Vector3.h"

const double EPS = 1e-6;

Vector3::Vector3(double x_, double y_, double z_)
{
	// printf("init! %llf, %llf, %llf\n", x_, y_, z_);
	x = x_;
	y = y_;
	z = z_;
}

Vector3::~Vector3()
{
}

double Vector3::length() {
	return x * x + y * y + z * z;
}

Vector3 Vector3::normalize() const {
	
	double a = sqrt(x * x + y * y + z * z);
	return Vector3(x/a, y/a, z/a);

}

Vector3 Vector3::operator+(const Vector3& d) const{
	return Vector3(d.x + x, d.y + y, d.z + z);
}

Vector3 Vector3::operator-(const Vector3& d) const {
	return Vector3(x - d.x, y - d.y, z - d.z);
}

Vector3 Vector3::operator/(double v) const {
	return Vector3(x / v, y / v, z / v);
}

Vector3 operator * (const Vector3& A, const double& k) {
	return Vector3(A.x * k, A.y * k, A.z * k);
}

double Vector3::dot(const Vector3& d) const{
	return d.x * x + d.y * y + d.z * z;
}

Vector3 Vector3::reflect(const Vector3& N) {
	return *this - N * 2.0f * dot(N);
}

Vector3 Vector3::refract(const Vector3& N, double n) {
	/*
	Vector3 V = normalize();
	double cosI = -N.dot(V), cosT2 = 1 - (n * n) * (1 - cosI * cosI);
	if (cosT2 > EPS) return V * n + N * (n * cosI - sqrt(cosT2));
	return V.reflect(N);
	*/
	return Vector3(0, 0, 0);
}
