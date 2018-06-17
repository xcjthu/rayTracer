#include "stdafx.h"
#include "Engine.h"
#include <cstdio>
#include <iostream>

Engine::Engine()
{
	mScene = new Scene();
}

Engine::~Engine()
{
	delete mScene;
}


//set the render target canvas
void Engine::setTarget(int* aDest, int aW, int aH) {
	mDest = aDest;
	mW = aW;
	mH = aH;
	img = new Color[aW * aH];
}


int Engine::nearIntersect(Primitive*& prim, Ray& aRay, double& aDist) {
	//find the nearest intersection
	int result;
	for (int s = 0; s < mScene->getnumPrimitive(); ++s) {
		Primitive* pr = mScene->getPrimitive(s);
		//printf("%lld\n", pr);
		int res;
		res = pr->Intersect(aRay, aDist);

		if (res) {
			//printf("%d", s);
			prim = pr;
			result = res; // 0 = MISS. 1 = HIT, -1 = CONTAIN
		}

	}
	return result; 
}

double Engine::diffuse(Primitive* prim, Vector3& N, Vector3& L) {
	double diff = prim->getMaterial()->GetDiffuse();
	if (diff > 0) {
		double dot = N.dot(L);

		if (dot > 0) {

			diff *= dot;
			//add diffuse component to ray color
			//aAcc += (prim->getMaterial()->getColor() * light->getMaterial()->getColor()) * diff;
			return diff;
		}
		
	}
	return 0;
}


Primitive* Engine::raytrace(Ray& aRay, Color& aAcc, int aD, double aRIndex, double& aDist) {
	if (aD > TRACEDEPTH) {
		return 0;
	}
	//trace primary ray
	aDist = 1000000.0f;
	Vector3 pi;
	Primitive* prim = 0;
	
	//find the nearest intersection
	int result = nearIntersect(prim, aRay, aDist);
	
	//no hit, terminate ray
	if (!prim) {
		return 0;
	}

	//double envLight = 0.01;
	// we hit a light, stop tracing
	if (prim->isLight()) {
		aAcc = Color(1, 1, 1);
	}
	else {
		pi = aRay.getOrigin() + aRay.getDir() * aDist; // 交点
		Vector3 N = prim->getNormal(pi); //法向量

		//trace lights
		for (int l = 0; l < mScene->getnumPrimitive(); ++l) {
			Primitive* p = mScene->getPrimitive(l);
			if (p->isLight()) {
				Primitive* light = p;

				Vector3 L = ((Sphere*)light)->getCentre() - pi;
				L = L.normalize();

				Primitive* tmp = 0;
				double m = 1000000.f;
				double shade = 1.0f;
				nearIntersect(tmp, Ray(pi + L * EPSILON, L), m);
				if (tmp != light ) {
					shade = 0.0;
					//说明不能看到点光源
				}

				//漫反射
				if (shade > 0) {
					double diff = diffuse(prim, N, L);

					aAcc += prim->getMaterial()->getColor() * (light->getMaterial()->getColor() * diff);
				}
				
				//Phong
				if (shade > 0) {
					Vector3 V = aRay.getDir();
					Vector3 R = L.reflect(N);
					double dot = V.dot(R);
					if (dot > 0)
					{
						double spec = powf(dot, 20) * prim->getMaterial()->GetSpecular();//shade;
						// add specular component to ray color
						
						aAcc += light->getMaterial()->getColor() * spec;
						//if (shade == 0 && spec == 0 && (light->getMaterial()->getColor() * spec).r == 0) printf("happy\n");
					}
				}
				
			}
		}


		//cal Reflection
		double refl = prim->getMaterial()->GetReflection();
		// refl = 0;
		if (refl > 0.0f)
		{
			Vector3 R = aRay.getDir().reflect(N);
			if (aD < TRACEDEPTH)
			{
				Color rcol(0, 0, 0);
				double dist = 10000;
				raytrace(Ray(pi + R * EPSILON, R), rcol, aD + 1, aRIndex, dist);
				aAcc += prim->getMaterial()->getColor() * (rcol * refl);
			}
		}


		//折射 cal refraction
		double refr = prim->getMaterial()->GetRefraction();
		if ((refr > 0) && (aD < TRACEDEPTH))
		{
			double rindex = prim->getMaterial()->GetRefrIndex();
			double n = aRIndex / rindex;
			Vector3 N = prim->getNormal(pi) * (float)result;
			double cosI = -N.dot(aRay.getDir());
			double cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);
			if (cosT2 > 0.0f)
			{
				Vector3 T = (aRay.getDir() * n) + N * (n * cosI - sqrtf(cosT2));
				Color rcol(0, 0, 0);
				double dist = 10000;
				raytrace(Ray(pi + T * EPSILON, T), rcol, aD + 1, rindex, dist);
				// aAcc += rcol;

				// apply Beer's law
				Color absorbance = prim->getMaterial()->getColor() * 0.15f * -dist;
				Color transparency = Color(expf(absorbance.r), expf(absorbance.g), expf(absorbance.b));
				aAcc += rcol * transparency;

			}
		}



	}
	//return pointer to primitive hit by primary ray
	return prim;
}

void Engine::initRender() {
	//set first line to draw to 
	mCurrLine = 20;
	//set Pixel buffer address of first pixel
	mPPos = 20 * mW;
	//screen plane in world space coordinates
	mWX1 = -4, mWX2 = 4, mWY1 = mSY = 3, mWY2 = -3;
	
	//calculate deltas for interpolation
	mDX = (mWX2 - mWX1) / mW;
	mDY = (mWY2 - mWY1) / mH;
	mSY += 20 * mDY;
	//allocate space to store pointers to primitives for previous line
	mLastRow = new Primitive*[mW];
	memset(mLastRow, 0, mW * 4);

}

bool Engine::render() {
	//render scene
	Vector3 o(0, 0, -5);
	
	//这里还可以加上超采样
	
	double dx, dy;
	dx = 0.01;
	dy = 0.01;
	double beginx = -5;
	double beginy = -3;
	for (int i = 0; i < mW; ++ i) {
		for (int j = 0; j < mH; ++ j) {
			Color acc(0, 0, 0);

			Vector3 dir = Vector3(beginx + i * dx, beginy + j * dy, 0) - o;
			dir = dir.normalize();
			Ray r(o, dir);
			double dist = 0;
			raytrace(r, acc, 1, 1.0f, dist);
			int aR = int(acc.r * 256);
			int aG = int(acc.g * 256);
			int aB = int(acc.b * 256);
			if (aR >= 256) aR = 255;
			if (aG >= 256) aG = 255;
			if (aB >= 256) aB = 255;
			img[(mH - j - 1) * mW + i] = Color(aR, aG, aB);
		}
	}

	return true;
}
