#include <cstdio>
#include "stdafx.h"

#include "Engine.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <cstdio>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Engine* tracer = new Engine();
	int w = 1000;
	int h = 800;
	tracer->setTarget(new int[w * h], w, h);
	tracer->getScene()->initScene();
	/*
	Vector3 o(1, 0, 0);
	Vector3 goal(-0, -0.5, 7);
	Vector3 dir = goal - o;
	dir = dir.normalize();
	Ray ray(o, dir);
	cout << "ray origin:" << ray.getOrigin().x << " " << ray.getOrigin().y << " " << ray.getOrigin().z << endl;
	double dist = 100000;
	cout << tracer->getScene()->getPrimitive(2)->Intersect(ray, dist);
	*/
	tracer->initRender();
	tracer->render();
	Mat image = Mat::zeros(w, h, CV_8UC3);

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			//cout << i << j << endl;
			image.at<Vec3b>(j, i)[0] = int(tracer->img[i * w + j].b);
			image.at<Vec3b>(j, i)[1] = int(tracer->img[i * w + j].g);
			image.at<Vec3b>(j, i)[2] = int(tracer->img[i * w + j].r);
		}
	}
	imwrite("D:/learn/graphics/image.png", image);
	
	//system("pause");
    return 0;
}

