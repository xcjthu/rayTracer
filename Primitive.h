#pragma once


#include "Vector3.h"
#include "Material.h"
#include "Ray.h"
#include <string>

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
	virtual std::string getType();
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
	std::string getType() { return "SPHERE"; }

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
	std::string getType() { return "PLANE"; }

};



class planeLight : public Primitive
{
public:
	std::string getType() { return "PLANELIGHT"; }
	planeLight();
	planeLight(aabb& a_Box);
	int Intersect(Ray& a_Ray, float& a_Dist);
	bool IntersectBox(aabb& a_Box) { return m_Box.Intersect(a_Box); }
	vector3 GetNormal(vector3&);
	bool Contains(vector3& a_Pos) { return m_Box.Contains(a_Pos); }
	vector3& GetPos() { return m_Box.GetPos(); }
	vector3& GetSize() { return m_Box.GetSize(); }
	float GetGridX(int a_Idx) { return m_Grid[a_Idx << 1]; }
	float GetGridY(int a_Idx) { return m_Grid[(a_Idx << 1) + 1]; }
	void Light(bool a_Light);
	aabb GetAABB() { return m_Box; }
protected:
	aabb m_Box;
	float* m_Grid;
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