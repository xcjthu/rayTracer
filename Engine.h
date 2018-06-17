#pragma once

#include "Primitive.h"

const int TRACEDEPTH = 6;
const double EPSILON = 0.0001; //一个很小的量

class Engine
{
public:
	Engine();
	~Engine();

	void setTarget(int* aDest, int aW, int aH);
	Scene* getScene() { return mScene; }
	Primitive* raytrace(Ray& aRay, Color& aAcc, int aDepth, double aRIndex, double& aDist);
	void initRender();
	int nearIntersect(Primitive*& pointer, Ray& aRay, double& aDist);
	double diffuse(Primitive* prim, Vector3& N, Vector3& L);
	//double reflect();
	bool render();

	double mWX1, mWY1, mWX2, mWY2, mDX, mDY, mSX, mSY;
	Scene* mScene;
	int* mDest;
	int mW, mH, mCurrLine, mPPos;
	Color* img;
	Primitive** mLastRow;
};

