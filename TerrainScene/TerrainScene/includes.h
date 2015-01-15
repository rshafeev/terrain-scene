#ifndef __Includes
#define __Includes
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>              // Заголовочные файлы для Windows

#include <gl\glew.h>
#include <gl\gl.h>
#include <gl\glaux.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\glut.h>
#include <gl\wglext.h>
#include <Stdio.H>
#include <Stdlib.H>
#include <Math.H>

struct TPoint
{
    float x;
	float y;
	float z;
};
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glut32.lib")

#pragma comment (lib,"OpenGL32.Lib")
#pragma comment (lib,"GLu32.Lib")
#pragma comment (lib,"WinMm.Lib")
#pragma comment (lib,"GLaux.Lib")
#endif