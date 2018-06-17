#pragma once

#include "Vector3.h"

//���߱��ʽΪ r(t) = orgin + t * dir  �������dirΪ��λ����
class Ray
{
private:
	Vector3 origin;
	Vector3 dir;
public:
	Ray(const Vector3& o, const Vector3& d) :origin(o), dir(d) {};
	//Ray(const Vector3& o, const Vector3& goal) :origin(o), dir((goal - o).normalize())){};

	Vector3 getDir() { return dir; }
	Vector3 getOrigin() { return origin; }

	~Ray();
};

