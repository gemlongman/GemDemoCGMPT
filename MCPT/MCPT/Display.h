#pragma once

#include "PathTracer.h"
#include "glut/glut.h"
#include <time.h>
#include <iostream>
#include <windows.h>

class Display
{
public:
	static PathTracer * thisPathTracer;

	Display(Scene* _pScene, float _ambient);
	~Display() 
	{
		delete thisPathTracer;
	}
	static void Render();
	static void Update();
	static void ScreenShot(int width, int height, const char * filepath);
	static void KeyboardHandle(unsigned char key, int x, int y);
	static void AutoScreenShot();
	void Run();
};

using namespace std;

PathTracer * Display::thisPathTracer = NULL;

Display::Display(Scene* _pScene, float _ambient)
{
	thisPathTracer = new PathTracer(_pScene, _ambient);
}

void Display::Render()
{
	int width = thisPathTracer->GetScene()->GetWidth();
	int height = thisPathTracer->GetScene()->GetHeight();

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);

	float* colors = thisPathTracer->PathTracerRender();

	glRasterPos2i(0, 0);
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, (GLvoid *)colors);

	glFlush();
	AutoScreenShot();
}

void Display::Update()
{
	glutPostRedisplay();
}

void Display::AutoScreenShot() 
{
	if(MaxIterationsNum < thisPathTracer->Iterations)
	{
		return;
	}
	string tfilename = "scenes\\";
	char costtime[20];
	tfilename += thisPathTracer->GetScene()->SceneName;
	tfilename += to_string(thisPathTracer->Iterations);
	tfilename += "-";
	sprintf(costtime, "%d", clock()- thisPathTracer->LoadStartTime);
	tfilename += costtime;
	tfilename += ".bmp";

	cout << "cost time " << costtime << "ms" << endl;

	if (thisPathTracer->Iterations == 1)
	{
		//ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		//cout << "自动保存截图：" << tfilename << endl;
	}else if (thisPathTracer->Iterations == 2)
	{
		//ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		//cout << "自动保存截图：" << tfilename << endl;
	}else if (thisPathTracer->Iterations == 4)
	{
		//ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		//cout << "自动保存截图：" << tfilename << endl;
	}
	else if (thisPathTracer->Iterations == 8)
	{
		//ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		//cout << "自动保存截图：" << tfilename << endl;
	}
	else if (thisPathTracer->Iterations == 16)
	{
		//ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		//cout << "自动保存截图：" << tfilename << endl;
	}
	else if (thisPathTracer->Iterations == 32)
	{
		//ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		//cout << "自动保存截图：" << tfilename << endl;
	}
	else if (thisPathTracer->Iterations == 64)
	{
		//ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		//cout << "自动保存截图：" << tfilename << endl;
	}
	else if (thisPathTracer->Iterations == 128)
	{
		//ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		//cout << "自动保存截图：" << tfilename << endl;
	}
	else {
		return;
	}

	ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
	cout << "auto save caputre bmp：" << tfilename << endl;
}

void Display::ScreenShot(int width, int height,const char * filepath)
{
	GLint pView[4];
	glGetIntegerv(GL_VIEWPORT, pView);//得到视图矩阵,pView[2]为宽即width,pView[3]为高即height

	GLsizei numComponet = 3;
	GLsizei bufferSize = pView[2] * pView[3] * sizeof(GLfloat)*numComponet;

	GLfloat * _data = new GLfloat[bufferSize];
	unsigned char *  data = new unsigned char[bufferSize];
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);//设置4字节对齐
	glReadBuffer(GL_FRONT);
	glReadPixels(pView[0], pView[1], pView[2], pView[3], GL_BGR_EXT, GL_FLOAT, _data);//不是GL_RGB的读取方式，而是GL_BGR或者GL_BGR_Ext
	glReadBuffer(GL_BACK);
	for (int i = 0; i < bufferSize; i++)
	{
		data[i] = _data[i] * 255;
	}
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	infoHeader.biSize = 40;
	infoHeader.biWidth = width;
	infoHeader.biHeight = height;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biCompression = BI_RGB;
	infoHeader.biSizeImage = pView[2] * pView[3] * 3;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;
	fileHeader.bfType = 0x4D42;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = 54;
	fileHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + pView[2] * pView[3] * 3);
	FILE *fd;
	if (!(fd = fopen(filepath, "wb+")))
	{
		cout<<"bmp fopen error";
		exit(0);
	}
	else
	{
		fwrite(&fileHeader, 1, sizeof(BITMAPFILEHEADER), fd);
		fwrite(&infoHeader, 1, sizeof(BITMAPINFOHEADER), fd);
		fwrite(data, 1, pView[2] * pView[3] * 3, fd);
		fclose(fd);
	}
	delete[] data;
	delete[] _data;
}

void Display::KeyboardHandle(unsigned char key, int x, int y)
{
	string tfilename = "scenes\\capture";
	switch (key) {
	case 'c':
	case 'C':
		char timenow[20];
		sprintf(timenow, "%d", clock());
		tfilename += timenow;
		tfilename += ".bmp";
		ScreenShot(thisPathTracer->GetScene()->GetWidth(), thisPathTracer->GetScene()->GetHeight(), tfilename.c_str());
		cout << "save capture bmp：" << tfilename << endl;
		break;
	default:
		break;
	}
}

void Display::Run()
{
	int width = thisPathTracer->GetScene()->GetWidth();
	int height = thisPathTracer->GetScene()->GetHeight();
	cout << endl << "LightSampleNum: " << LightSampleNum << "PixSampleNum: " << PixSampleNum << " MaxRescursiveDepth: " << MaxRescursiveDepth << " LightRate 1/x: " << LightRate << endl;
	cout << "pixs: " << width << " * " << height << endl << endl;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CGMCPT");
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutKeyboardFunc(KeyboardHandle);
	glutMainLoop();
}