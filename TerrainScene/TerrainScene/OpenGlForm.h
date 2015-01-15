#pragma once
#include "Includes.H"

class COpenGlForm
{

public:
 COpenGlForm(void);
 ~COpenGlForm(void);
 HGLRC  hRC;                       // Постоянный контекст рендеринга
 HDC  hDC;                         // Приватный контекст устройства GDI
 HWND  hWnd;                       // Здесь будет хранится дескриптор окна
 HINSTANCE  hInstance;              // Здесь будет хранится дескриптор приложения
     
 bool  keys[256];                // Массив, используемый для операций с клавиатурой
 bool  active;                   // Флаг активности окна, установленный в true по умолчанию
 bool  fullscreen;               // Флаг режима окна, установленный в полноэкранный по умолчанию
 bool activeShades;
 int screenW,screenH;// разрешение экрана
 int formW,formH;
 int screenBitSize; // глубина цветопередачи
     

void OnCreate(); 

int InitGL( GLvoid );
GLvoid KillGLWindow( GLvoid );
BOOL CreateGLWindow(const char* title);
};
extern COpenGlForm *OpenGlForm;