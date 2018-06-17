#pragma once

#include "Color.h"

class Material
{
public:
	Color color;
	double refl;
	double diff;
	double refr;
	double refrIndex;
	double specular;
	
	//double drefl;

public:
	void SetColor(Color& c) { color = c; }
	Color getColor() { return color; }
	void SetDiffuse(double a_Diff) { diff = a_Diff; }
	void SetReflection(double a_Refl) { refl = a_Refl; }
	void SetRefraction(double a_Refr) { refr = a_Refr; }
	void SetRefrIndex(double r_index) { refrIndex = r_index; }
	void SetSpecular(double a) { specular = a; }
	double GetSpecular() { return specular; }
	double GetDiffuse() { return diff; }
	double GetReflection() { return refl; }
	double GetRefraction() { return refr; }
	double GetRefrIndex() { return refrIndex; }
	Material();
	~Material();
};

