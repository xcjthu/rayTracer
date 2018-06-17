#include "stdafx.h"
#include "Primitive.h"
#include <string>
#include <cstring>
#include <cmath>
#include <iostream>

Primitive::Primitive()
{
}


Primitive::~Primitive()
{
}

void Primitive::setName(char* aName) {
	//¸³ÓèÃû×Ö
	name = new char[strlen(aName) + 1];
	for (int i = 0; i < strlen(aName); ++i) {
		name[i] = aName[i];
	}
}

int Sphere::Intersect(Ray& ray, double& dist) {
	Vector3 v = ray.getOrigin();
	//std::cout << "centre: " << centre.x << " " << centre.y << " " << centre.z << std::endl;
	v = v - centre;
	//std::cout << "v: " << v.x << " " << v.y << " " << v.z << std::endl;
	Vector3 dir = ray.getDir();
	//std::cout << "dir: " << dir.x << " " << dir.y << " " << dir.z << std::endl;
	
	double b = -v.dot(ray.getDir());
	//std::cout << "b: " << b << std::endl;
	double det = b * b - v.dot(v) + R * R;
	//std::cout << "det: " << det << std::endl;
	int tmp = MISS;
	if (det > 0) {
		//printf("Sphere");
		det = sqrtf(det);
		double i1 = b - det;
		double i2 = b + det;
		// printf("b, det, i1,i2 %d %d %d %d\n", b, det, i1, i2);
		if (i2 > 0) {
			if (i1 < 0) {
				if (i2 < dist) {
					dist = i2;
					tmp = CONTAIN;
				}
			}
			else {
				if (i1 < dist) {
					dist = i1;
					//printf("HIT!\n");
					tmp = HIT;
				}
			}
		}
		// tmp = HIT;
	}
	return tmp;
}

int Plane::Intersect(Ray& ray, double& dist) {
	
	double d = n.dot(ray.getDir());
	if (d != 0) {
		double distTmp = -(n.dot(ray.getOrigin()) + D) / d;
		if (distTmp > 0) {
			if (distTmp < dist) {

				dist = distTmp;
				return HIT;

			}
		}
	}
	return MISS;
}

Vector3 Plane::getNormal(Vector3& pos) {
	return n;
}

void Scene::initScene1() {
	mPrimitive = new Primitive*[20];

	//ground plane
	mPrimitive[0] = new Plane(Vector3(0, 1, 0), 4.4f);
}

void Scene::initScene() {
	mPrimitive = new Primitive*[500];
	// ground plane
	mPrimitive[0] = new Plane(Vector3(0, 1, 0), 4.4f);
	mPrimitive[0]->setName("plane");
	mPrimitive[0]->getMaterial()->SetReflection(0.0f);
	mPrimitive[0]->getMaterial()->SetRefraction(0.0f);
	mPrimitive[0]->getMaterial()->SetDiffuse(1.0f);
	mPrimitive[0]->getMaterial()->SetColor(Color(0.4f, 0.3f, 0.3f));
	
	
	// big sphere
	mPrimitive[1] = new Sphere(Vector3(2, 0.8f, 3), 2.5f);
	mPrimitive[1]->setName("big sphere");
	mPrimitive[1]->getMaterial()->SetReflection(0.2f);
	mPrimitive[1]->getMaterial()->SetRefraction(1.0f);
	mPrimitive[1]->getMaterial()->SetRefrIndex(1.3f);
	mPrimitive[1]->getMaterial()->SetSpecular(0.6f);
	// mPrimitive[1]->getMaterial()->SetDiffuse(0.5f);
	mPrimitive[1]->getMaterial()->SetColor(Color(0.7f, 0.7f, 1.0f));
	

	// small sphere
	mPrimitive[2] = new Sphere(Vector3(-5.5f, -0.5, 7), 2);
	mPrimitive[2]->setName("small sphere");
	mPrimitive[2]->getMaterial()->SetReflection(0.5f);
	mPrimitive[2]->getMaterial()->SetRefraction(0.0f);
	mPrimitive[2]->getMaterial()->SetRefrIndex(1.3f);
	mPrimitive[2]->getMaterial()->SetDiffuse(0.2f);
	mPrimitive[2]->getMaterial()->SetSpecular(0.6f);
	mPrimitive[2]->getMaterial()->SetColor(Color(0.7f, 0.7f, 1.0f));
	// light source 1
	mPrimitive[3] = new Sphere(Vector3(0, 5, 5), 0.1f);
	mPrimitive[3]->Light(true);
	mPrimitive[3]->getMaterial()->SetColor(Color(0.4f, 0.4f, 0.4f));
	// light source 2
	mPrimitive[4] = new Sphere(Vector3(-3, 5, 1), 0.1f);
	mPrimitive[4]->Light(true);
	mPrimitive[4]->getMaterial()->SetColor(Color(0.6f, 0.6f, 0.8f));
	// extra sphere
	mPrimitive[5] = new Sphere(Vector3(-1.5f, -3.8f, 1), 1.5f);
	mPrimitive[5]->setName("extra sphere");
	mPrimitive[5]->getMaterial()->SetReflection(0.4f);
	mPrimitive[5]->getMaterial()->SetRefraction(0.2f);
	mPrimitive[5]->getMaterial()->SetRefrIndex(1.3f);
	mPrimitive[5]->getMaterial()->SetDiffuse(0.1f);
	mPrimitive[5]->getMaterial()->SetSpecular(0.6f);
	mPrimitive[5]->getMaterial()->SetColor(Color(1.0f, 0.4f, 0.4f));
	// back plane
	mPrimitive[6] = new Plane(Vector3(0.4f, 0, -1), 12);
	mPrimitive[6]->setName("back plane");
	mPrimitive[6]->getMaterial()->SetReflection(0.0f);
	mPrimitive[6]->getMaterial()->SetRefraction(0.0f);
	mPrimitive[6]->getMaterial()->SetSpecular(0);
	mPrimitive[6]->getMaterial()->SetDiffuse(0.6f);
	mPrimitive[6]->getMaterial()->SetColor(Color(0.5f, 0.3f, 0.5f));
	// ceiling plane
	mPrimitive[7] = new Plane(Vector3(0, -1, 0), 7.4f);
	mPrimitive[7]->setName("back plane");
	mPrimitive[7]->getMaterial()->SetReflection(0.0f);
	mPrimitive[7]->getMaterial()->SetRefraction(0.0f);
	mPrimitive[7]->getMaterial()->SetSpecular(0);
	mPrimitive[7]->getMaterial()->SetDiffuse(0.5f);
	mPrimitive[7]->getMaterial()->SetColor(Color(0.4f, 0.7f, 0.7f));
	// grid
	int prim = 8;
	for (int x = 0; x < 8; x++) 
		for (int y = 0; y < 7; y++)
		{
			mPrimitive[prim] = new Sphere(Vector3(-4.5f + x * 1.5f, -4.3f + y * 1.5f, 10), 0.3f);
			mPrimitive[prim]->setName("grid sphere");
			mPrimitive[prim]->getMaterial()->SetReflection(0);
			mPrimitive[prim]->getMaterial()->SetRefraction(0);
			mPrimitive[prim]->getMaterial()->SetSpecular(0.6f);
			mPrimitive[prim]->getMaterial()->SetDiffuse(0.6f);
			mPrimitive[prim]->getMaterial()->SetColor(Color(0.3f, 1.0f, 0.4f));
			prim++;
		}
	// set number of primitives
	numPrimitive = prim ;




	/*
	mPrimitive = new Primitive*[100];
	// ground plane
	mPrimitive[0] = new Plane(Vector3(0, 1, 0), 4.4f);
	mPrimitive[0]->setName("plane");
	mPrimitive[0]->getMaterial()->SetReflection(0.0f);
	mPrimitive[0]->getMaterial()->SetDiffuse(1.0f);
	mPrimitive[0]->getMaterial()->setColor(Color(0.4f, 0.3f, 0.3f)); 
	// big sphere
	mPrimitive[1] = new Sphere(Vector3(1, -0.8f, 3), 2.f);
	mPrimitive[1]->setName("big sphere");
	//mPrimitive[1]->getMaterial()->SetReflection(1.0f);
	mPrimitive[1]->getMaterial()->SetDiffuse(0.5f);
	mPrimitive[1]->getMaterial()->setColor(Color(0.3f, 0.6f, 0.9f));
	// small sphere
	mPrimitive[2] = new Sphere(Vector3(-5.5f, -0.5, 7), 2);
	mPrimitive[2]->setName("small sphere");
	mPrimitive[2]->getMaterial()->SetReflection(1.0f);
	mPrimitive[2]->getMaterial()->SetDiffuse(0.1f);
	mPrimitive[2]->getMaterial()->setColor(Color(0.7f, 0.7f, 1.0f));
	
	// light source 1
	mPrimitive[3] = new Sphere(Vector3(0, 5, 5), 0.1f);
	mPrimitive[3]->Light(true);
	mPrimitive[3]->getMaterial()->setColor(Color(1.f, 1.f, 1.f));
	*/
	/*
	// light source 2
	mPrimitive[4] = new Sphere(Vector3(2, 5, 1), 0.1f);
	mPrimitive[4]->Light(true);
	mPrimitive[4]->getMaterial()->setColor(Color(1.f, 1.f, 1.f));
	*/
	/*
	//light source 3
	mPrimitive[5] = new Sphere(Vector3(0, 5, 1), 0.1f);
	mPrimitive[5]->Light(true);
	mPrimitive[5]->getMaterial()->setColor(Color(0.7f, 0.7f, 0.9f));
	*/
	/*
	//light source 4
	mPrimitive[5] = new Sphere(Vector3(5, 0, 0), 0.1f);
	mPrimitive[5]->Light(true);
	mPrimitive[5]->getMaterial()->setColor(Color(0.7f, 0.7f, 0.9f));
	*/
	// set number of primitives
	//numPrimitive = 4;
}

