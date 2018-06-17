#pragma once

#include<sstream>


class Color {
public:
	double r, g, b;

	explicit Color(double R = 0, double G = 0, double B = 0) : r(R), g(G), b(B) {}
	Color(const Color& c) { r = c.r; g = c.g; b = c.b; }
	~Color() {}

	friend Color operator + (const Color& A, const Color& B) { return Color(A.r + B.r, A.g + B.g, A.b + B.b); }
	friend Color operator - (const Color& A, const Color& B) { return Color(A.r - B.r, A.g - B.g, A.b - B.b); }
	friend Color operator * (const Color& A, const Color& B) { return Color(A.r * B.r, A.g * B.g, A.b * B.b); }
	friend Color operator * (const Color& A, const double& k) { return Color(A.r * k, A.g * k, A.b * k); }
	friend Color operator / (const Color& A, const double& k) { return Color(A.r / k, A.g / k, A.b / k); }
	friend Color operator += (Color& A, const Color& B) {	A = A + B; return A; }
	friend Color operator -= (Color& A, const Color& B) { A = A - B;	return A; }
	friend Color operator *= (Color& A, const double& k) { A = A * k;	return A; }
	friend Color operator /= (Color& A, const double& k) { A = A / k;	return A; }
	void Confine(); //luminance must be less than or equal to 1
	void Input(std::stringstream&);
};

