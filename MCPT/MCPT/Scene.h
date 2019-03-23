#pragma once

#include <vector>
#include "pch.h"
#include "Common.h"

using namespace std;
class BasicObj;
class KdTree;

class Camera
{
public:
	int width, height;
	float fov;
	//Camera position toward upward
	void LookAt(float eye_x, float eye_y, float eye_z,
		float center_x, float center_y, float center_z,
		float up_x, float up_y, float up_z);
	void CalcViewPort(float _fov, int _width, int _height);
	Ray CameraGetRay(float x, float y);

private:
	Point3f CameraPosition;
	Vector3f CameraDirection;
	Vector3f front, up, right;
	Vector3f viewHorizontal, viewVertical, viewDepth;
};

class Scene
{
public:
	ObjModel inputModel;
	Camera pCamera;
	vector<Light> lights;

	string SceneName;
	float averageLightWeight;
	float * pixColors;

	Scene(string scenesName);
	~Scene();

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SceneInit(string name="");
	Ray * SceneGetRays(float x, float y, int pxSampleNum);
	bool GetIsIntersect(Ray & ray, Intersection & intersection);
	bool IsInShadow(Ray & ray);//is Occlusion between
	Color3f DirectIllumination(Intersection & intersection, Ray & ray);

private:
	int width, height;
	
	KdTree kdTree;
};

