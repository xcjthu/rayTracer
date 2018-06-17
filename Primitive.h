#pragma once


#include "Vector3.h"
#include "Material.h"
#include "Ray.h"

int const HIT = 1;
int const MISS = 0;
int const CONTAIN = -1;


class Primitive
{
public:
	Material material;
	char* name;
	bool mLight;

	Primitive();
	~Primitive();

	Material* getMaterial() { return &material; }
	void setMaterial(Material& mat) { material = mat; }

	virtual int Intersect(Ray& a_Ray, double& dist) = 0;
	virtual Vector3 getNormal(Vector3& pos) = 0;
	virtual void Light(bool a_light) { mLight = a_light; }
	virtual Color getColor(Vector3&) { return material.getColor(); }
	bool isLight() { return mLight; }
	void setName(char* aName);
	char* getName() { return name; }
};


class Sphere : public Primitive {
public:
	double R;
	Vector3 centre;

	Sphere(Vector3& cen, float radius): R(radius), centre(cen){}

	Vector3& getCentre() { return centre; }
	double getR() { return R; }
	int Intersect(Ray& ray, double& dist);
	Vector3 getNormal(Vector3& pos) { return (pos - centre) / R; }

};



class Plane : public Primitive {
public:
	Vector3 n; 
	double D;

	//平面的参数方程为 H(P) = nP +D = 0   P = (x, y, z)
	//n必须为单位向量

	Plane(Vector3& nor, double d): n(nor), D(d){}
	Vector3& getNormal() { return n; }
	double getD() { return D; }
	int Intersect(Ray& ray, double& dist);
	Vector3 getNormal(Vector3& pos);

};


class Scene {
public:
	Scene() : numPrimitive(0), mPrimitive(0) {}
	~Scene() { delete mPrimitive; }
	void initScene();
	void initScene1();
	int getnumPrimitive() { return numPrimitive; }
	Primitive* getPrimitive(int index) { return mPrimitive[index]; }

	int numPrimitive;
	Primitive** mPrimitive;
};