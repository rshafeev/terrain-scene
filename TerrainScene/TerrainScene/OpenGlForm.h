#pragma once
#include "Includes.H"

class COpenGlForm
{

public:
 COpenGlForm(void);
 ~COpenGlForm(void);
 HGLRC  hRC;                       // ���������� �������� ����������
 HDC  hDC;                         // ��������� �������� ���������� GDI
 HWND  hWnd;                       // ����� ����� �������� ���������� ����
 HINSTANCE  hInstance;              // ����� ����� �������� ���������� ����������
     
 bool  keys[256];                // ������, ������������ ��� �������� � �����������
 bool  active;                   // ���� ���������� ����, ������������� � true �� ���������
 bool  fullscreen;               // ���� ������ ����, ������������� � ������������� �� ���������
 bool activeShades;
 int screenW,screenH;// ���������� ������
 int formW,formH;
 int screenBitSize; // ������� �������������
     

void OnCreate(); 

int InitGL( GLvoid );
GLvoid KillGLWindow( GLvoid );
BOOL CreateGLWindow(const char* title);
};
extern COpenGlForm *OpenGlForm;