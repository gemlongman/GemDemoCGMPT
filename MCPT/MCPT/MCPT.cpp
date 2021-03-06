// MCPT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "pch.h"
#include "Display.h"

#define gydebug

using namespace std;

void scene1cup(string scenesName)
{
	Scene scene(scenesName);
	scene.pCamera.LookAt(0, 0.64, 0.52, 0, 0.4, 0.3, 0, 1, 0);
	scene.pCamera.CalcViewPort(60, 512, 512);
	scene.lights = scene.inputModel.lights;
	//scene.lights.push_back(Light(Point3f(-2.758771896, 1.5246, 0), Vector3f(0, 0, -1), Vector3f(0, 1, 0), Vector3f(1, 0, 0), Color3f(40, 40, 40)));
	scene.SceneInit("scene1cup");

	//debug all light
	int i = 0;
	for (vector<Light>::iterator lighit = scene.lights.begin(); lighit != scene.lights.end(); lighit++) {
		i++;
#ifdef gydebug
		cout << " light:x " << lighit->LightPosition.x << " y " << lighit->LightPosition.y << " z " << lighit->LightPosition.z << "\t"
			<< " lightType " << lighit->lightType << " Radius " << lighit->Radius << "\t" << " Area " << lighit->Area << "\n"
			<< " e " << lighit->Emission.r << " e " << lighit->Emission.g << " e " << lighit->Emission.b << "\t"
			<< " EdgeA " << lighit->EdgeA.x << " EdgeA " << lighit->EdgeA.y << " EdgeA " << lighit->EdgeA.z << "\t"
			<< " EdgeB " << lighit->EdgeB.x << " EdgeB " << lighit->EdgeB.y << " EdgeB " << lighit->EdgeB.z << "\t"
			<< endl;
#endif // gydebug
	}
	cout << "light num: " << i << endl;

	//PathTracer rayTracer(&scene, 0.1);
	Display display(&scene, 0.1);
	display.Run();
}

void scene2room(string scenesName)
{
	Scene scene(scenesName);
	scene.pCamera.LookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);//
	scene.pCamera.CalcViewPort(50, 512, 512);
	scene.lights.push_back(Light(Point3f(0.0, 1.589, -1.274), 0.2, Color3f(50, 50, 40)));
	scene.SceneInit("scene2room");

	//debug all light
	int i = 0;
	for (vector<Light>::iterator lighit = scene.lights.begin(); lighit != scene.lights.end(); lighit++) {
		i++;
#ifdef gydebug
		cout << " light:x " << lighit->LightPosition.x << " y " << lighit->LightPosition.y << " z " << lighit->LightPosition.z << "\t"
			<< " lightType " << lighit->lightType << " Radius " << lighit->Radius << "\t" << " Area " << lighit->Area << "\n"
			<< " e " << lighit->Emission.r << " e " << lighit->Emission.g << " e " << lighit->Emission.b << "\t"
			<< " EdgeA " << lighit->EdgeA.x << " EdgeA " << lighit->EdgeA.y << " EdgeA " << lighit->EdgeA.z << "\t"
			<< " EdgeB " << lighit->EdgeB.x << " EdgeB " << lighit->EdgeB.y << " EdgeB " << lighit->EdgeB.z << "\t"
			<< endl;
#endif // gydebug
	}
	cout << "light num: " << i << endl;

	//PathTracer rayTracer(&scene, 0.1);
	Display display(&scene, 0.1);
	display.Run();
}

void scene3VeachMIS(string scenesName)
{
	Scene scene(scenesName);
	scene.pCamera.LookAt(0, 2, 15, 0, 1.69521, 14.0476, 0, 0.952421, -0.304787);
	// 28 1152 864
#ifdef LOW
	camera.CalcViewPort(40, 512, 512);
#else
	scene.pCamera.CalcViewPort(38, 1152, 864);
#endif // LOW
	scene.lights.push_back(Light(Point3f(-10, 10, 4), 0.5, Color3f(800, 800, 800)));
	scene.lights.push_back(Light(Point3f(3.75, 0, 0), 0.033, Color3f(901.803, 901.803, 901.803)));
	scene.lights.push_back(Light(Point3f(1.25, 0, 0), 0.1, Color3f(100, 100, 100)));
	scene.lights.push_back(Light(Point3f(-1.25, 0, 0), 0.3, Color3f(11.1111, 11.1111, 11.1111)));
	scene.lights.push_back(Light(Point3f(-3.75, 0, 0), 0.9, Color3f(1.23457, 1.23457, 1.23457)));
	//scene.lights = model.lights;
	scene.SceneInit("scene3VeachMIS");

	//debug all light
	int i = 0;
	for (vector<Light>::iterator lighit = scene.lights.begin(); lighit != scene.lights.end(); lighit++) {
		i++;
#ifdef gydebug
		cout << " light:x " << lighit->LightPosition.x << " y " << lighit->LightPosition.y << " z " << lighit->LightPosition.z << "\t"
			<< " lightType " << lighit->lightType << " Radius " << lighit->Radius << "\t" << " Area " << lighit->Area << "\n"
			<< " e " << lighit->Emission.r << " e " << lighit->Emission.g << " e " << lighit->Emission.b << "\t"
			<< " EdgeA " << lighit->EdgeA.x << " EdgeA " << lighit->EdgeA.y << " EdgeA " << lighit->EdgeA.z << "\t"
			<< " EdgeB " << lighit->EdgeB.x << " EdgeB " << lighit->EdgeB.y << " EdgeB " << lighit->EdgeB.z << "\t"
			<< endl;
#endif // gydebug
	}
	cout << endl << "light num: " << i << endl;

	//PathTracer rayTracer(&scene, 0.5);
	Display display(&scene, 0.5);
	display.Run();
}

int main()
{
	char inOption;
	cin >> inOption;
	switch (inOption) {
	case '1':
		scene1cup("scenes/Scene01/cup.obj");
		break;
	case '2':
		scene2room("scenes/Scene02/room.obj");
		break;
	case '3':
		scene3VeachMIS("scenes/Scene03/VeachMIS.obj");
		break;
	default:
		break;
	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
