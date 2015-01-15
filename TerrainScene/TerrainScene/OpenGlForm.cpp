#include "OpenGlForm.h"
#include "Scene.H"
#include "TexShader.h"
#include "Texture.h"
COpenGlForm *OpenGlForm;
LRESULT  CALLBACK WndGLProc( HWND, UINT, WPARAM, LPARAM );        // �������� ������� WndProc
//**********************************************************************************************************	
COpenGlForm::COpenGlForm(void)
{
   int i;
   
   hRC=NULL;                                
   hDC=NULL;                               
   hWnd=NULL;                               
   hInstance=NULL;    

   active=true;                            
   fullscreen=true;                        
   screenW=1440;screenH=900;                
   formW=screenW;formH=screenH;
   screenBitSize=32;                       
   for(i=0;i<256;i++)
     keys[i]=false;
   activeShades=false;
}
COpenGlForm::~COpenGlForm(void)
{
}
//**********************************************************************************************************
void COpenGlForm::OnCreate()
{
 MSG  msg;                                                   // ��������� ��� �������� ��������� Windows
 BOOL  done = false;                                         // ���������� ���������� ��� ������ �� �����
 if( !CreateGLWindow( "3D Terrain") )              // ������� ���� OpenGL ����
    return;                                                  // �����, ���� ���� �� ����� ���� �������
 
 // sceene->Init();

 
while(!done)                                                 // ���� ������������, ���� done �� ����� true
{
   if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )          // ���� �� � ������� �����-������ ���������?
   {
      if( msg.message == WM_QUIT )                           // �� ������� ��������� � ������?
         done = true;                                        // ���� ���, done=true
      else                                                   // ���� ���, ������������ ���������
      {
         TranslateMessage( &msg );                            // ��������� ���������
         DispatchMessage( &msg );                             // �������� ���������
      }
   }
   else
   {														  // ������������� �����.
       if( active )                                           // ������� �� ���������?
       {
          if(keys[VK_ESCAPE])                                 // ���� �� ������ ������� ESC?
          {
            done = true;                                      // ESC ������� �� �������� ���������� ���������
          }
          else                                                // ������� �����.
          {
			sceene->DrawGLScene();
            SwapBuffers( hDC );                               // ������ ����� (������� �����������)
          }
        }
	   if( keys[VK_F1] )                                      // ���� �� ������ F1?
       {
          keys[VK_F1] = false;                                // ���� ���, ������ �������� ������ ������� �� false
          KillGLWindow();                                     // ��������� ������� ����
          fullscreen = !fullscreen;                           // ����������� �����
          if( !CreateGLWindow( "3D Terrain") )          // ���������� ���� OpenGL ����
            return;                                           // �������, ���� ��� ����������
       }
	   if( keys[VK_F2] )
	   {
            keys[VK_F2] = false; 
			sceene->autoOblet=!sceene->autoOblet;
	   }
   }
}

KillGLWindow();                                                // ��������� ����
}
//**********************************************************************************************************
int COpenGlForm::InitGL( GLvoid )// ��������� ��������� ������� OpenGL
{	
 glShadeModel( GL_SMOOTH );                                   // ��������� ������� �������� �����������
 glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                        // ������� ������ � ������ ����
 glClearDepth( 1.0f );                                        // ��������� ������� ������ �������
 glEnable( GL_DEPTH_TEST );                                   // ��������� ���� �������
 glDepthFunc( GL_LEQUAL );									  // ��� ����� �������
 glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );		  // ��������� � ���������� �����������
 if(activeShades==false) 
 {
	 activeShades=true;
    	 
 }
 else
	 glDeleteProgram(TexShader->TexShadPr);
 TexShader->Init();
  Texture->InitTexture();
 sceene->Init();
 return true;												  // ������������� ������ �������
}
//**********************************************************************************************************
GLvoid COpenGlForm::KillGLWindow( GLvoid )                    // ���������� ���������� ����
{
 if( fullscreen )                                             // �� � ������������� ������?
 {
    ChangeDisplaySettings( NULL, 0 );                         // ���� ��, �� ������������� ������� � ������� �����
    ShowCursor( true );                                       // �������� ������ �����
 }
 if( hRC )                                                    // ���������� �� �������� ����������?
 {
    if( !wglMakeCurrent( NULL, NULL ) )                       // �������� �� ���������� RC � DC?
      MessageBox( NULL,LPCWSTR( "Release Of DC And RC Failed."),LPCWSTR( "SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION );
    if( !wglDeleteContext( hRC ) )                            // �������� �� ������� RC?
    {
      MessageBox( NULL,LPCWSTR("Release Rendering Context Failed."),LPCWSTR( "SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION );
    }
    hRC = NULL;                                               // ���������� RC � NULL
 }
 if( hDC && !ReleaseDC( hWnd, hDC ) )                         // �������� �� ���������� DC?
 {
      MessageBox( NULL,LPCWSTR( "Release Device Context Failed."),LPCWSTR( "SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION );
      hDC=NULL;                                               // ���������� DC � NULL
 }
 if(hWnd && !DestroyWindow(hWnd))                             // �������� �� ���������� ����?
 {
      MessageBox( NULL,LPCWSTR( "Could Not Release hWnd."),LPCWSTR( "SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION );
      hWnd = NULL;                                            // ���������� hWnd � NULL
 }
 if( !UnregisterClass(LPCWSTR( "OpenGL"), hInstance ) )       // �������� �� ����������������� �����
 {
    MessageBox( NULL, LPCWSTR("Could Not Unregister Class."), LPCWSTR("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
    hInstance = NULL;                                         // ���������� hInstance � NULL
 }
   hRC=NULL;												  // ���������� �������� ����������
   hDC=NULL;											      // ��������� �������� ���������� GDI
   hWnd=NULL;												  // ����� ����� �������� ���������� ����
   hInstance=NULL;											  // ����� ����� �������� ���������� ����������
}
//**********************************************************************************************************
BOOL COpenGlForm::CreateGLWindow( const char* title)
{
 GLuint    PixelFormat;										// ������ ��������� ����� ������
 DWORD    dwStyle;                                          // ������� ����� ����
 RECT WindowRect;                                           // Grabs Rectangle Upper Left / Lower Right Values
 WNDCLASS	wc;
  WindowRect.left=(long)0;                                  // ���������� ����� ������������ � 0
  WindowRect.right=(long)formW;                             // ���������� ������ ������������ � Width
  WindowRect.top=(long)0;                                   // ���������� ������� ������������ � 0
  WindowRect.bottom=(long)formH;                            // ���������� ������ ������������ � Height

  wc.hInstance    = GetModuleHandle(NULL);                  // ������� ���������� ������ ����������
  wc.style    = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;         // ���������� ��� ����������� � ������ ������� DC
  wc.lpfnWndProc    = (WNDPROC)WndGLProc;                   // ��������� ��������� ���������
  wc.cbClsExtra    = 0;                                     // ��� �������������� ���������� ��� ����
  wc.cbWndExtra    = 0;                                     // ��� �������������� ���������� ��� ����
  wc.hInstance    = hInstance;                              // ������������� ����������
  wc.hIcon    = LoadIcon(NULL, IDI_WINLOGO);                // ��������� ������ �� ���������
  wc.hCursor    = LoadCursor(NULL, IDC_ARROW);              // ��������� ��������� �����
  wc.hbrBackground  = NULL;                                 // ��� �� ��������� ��� GL
  wc.lpszMenuName    = NULL;                                // ���� � ���� �� �����
  wc.lpszClassName  = LPCWSTR("OpenGL");                    // ������������� ��� ������
  if( !RegisterClass( &wc ) )                               // �������� ���������������� ����� ����
  {
    MessageBox( NULL,LPCWSTR( "Failed To Register The Window Class."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;                                           // ����� � ����������� �������� �������� false
  }
  if( fullscreen==true )                                    // ������������� �����?
  {
    DEVMODE dmScreenSettings;                               // ����� ����������
    memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );             // ������� ��� �������� ���������
    dmScreenSettings.dmSize=sizeof( dmScreenSettings );                     // ������ ��������� Devmode
	dmScreenSettings.dmPelsWidth  =   screenW;                              // ������ ������
	dmScreenSettings.dmPelsHeight  =  screenH;                              // ������ ������
    dmScreenSettings.dmBitsPerPel  =   screenBitSize;                       // ������� �����
    dmScreenSettings.dmFields= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// ����� �������
	//�������� ���������� ��������� ����� � �������� ���������.  ����������: CDS_FULLSCREEN ������� ������ ����������.
    if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
    {
     // ���� ������������ � ������������� ����� ����������, ����� ���������� ��� ��������: ������� ����� ��� �����.
       if( MessageBox( NULL,LPCWSTR("The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?"), 
           LPCWSTR( "NeHe GL"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES )
            fullscreen = false;                              // ����� �������� ������ (fullscreen = false)
      else
      {
      // ������������� ����, ���������� ������������ � �������� ����.
          MessageBox( NULL, LPCWSTR("Program Will Now Close."),LPCWSTR( "ERROR"), MB_OK | MB_ICONSTOP );
          return false;                                      // ����� � ����������� �������� false
      }
    }
  }

  if(fullscreen)                                              // �� �������� � ������������� ������?
  {
	 dwStyle    =  WS_POPUP;                                  // ������� ����� ����
     ShowCursor( false );                                     // ������ ��������� �����
  }
  else
      dwStyle    =   WS_OVERLAPPEDWINDOW;                      // ������� ����� ����
  
  AdjustWindowRectEx( &WindowRect, dwStyle, false, WS_EX_APPWINDOW);      // ��������� ���� ���������� �������
  if( !( hWnd = CreateWindowEx(WS_EX_APPWINDOW,                           // ����������� ����� ��� ����
          LPCWSTR("OpenGL"),                                   // ��� ������
		  /*title*/TEXT("3D Terrain"),                                        // ��������� ����
          WS_CLIPSIBLINGS |									   // ��������� ����� ��� ����
          WS_CLIPCHILDREN |                                    // ��������� ����� ��� ����
     	  dwStyle,                                             // ���������� ����� ��� ����
          0, 0,                                                // ������� ����
          WindowRect.right-WindowRect.left,                    // ���������� ���������� ������
          WindowRect.bottom-WindowRect.top,                    // ���������� ���������� ������
          NULL,                                                // ��� �������������
          NULL,                                                // ��� ����
          hInstance,                                           // ���������� ����������
          NULL ) ) )                                           // �� ������� ������ �� WM_CREATE (???)

  {
    KillGLWindow();                                             // ������������ �����
    MessageBox( NULL, LPCWSTR("Window Creation Error."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;                                                 
  }

static  PIXELFORMATDESCRIPTOR pfd=                              // pfd �������� Windows ����� ����� ����� �� ����� ������� �������
{
    sizeof(PIXELFORMATDESCRIPTOR),                              // ������ ����������� ������� ������� ��������
    1,                                                          // ����� ������
    PFD_DRAW_TO_WINDOW |                                        // ������ ��� ����
    PFD_SUPPORT_OPENGL |                                        // ������ ��� OpenGL
    PFD_DOUBLEBUFFER,                                           // ������ ��� �������� ������
    PFD_TYPE_RGBA,                                              // ��������� RGBA ������
    screenBitSize,                                              // ���������� ��� ������� �����
    0, 0, 0, 0, 0, 0,                                           // ������������� �������� �����
    0,                                                          // ��� ������ ������������
    0,                                                          // ��������� ��� ������������
    0,                                                          // ��� ������ ����������
    0, 0, 0, 0,                                                 // ���� ���������� ������������
    32,                                                         // 32 ������ Z-����� (����� �������)
    0,                                                          // ��� ������ ���������
    0,                                                          // ��� ��������������� �������
    PFD_MAIN_PLANE,                                             // ������� ���� ���������
    0,                                                          // ���������������
    0, 0, 0                                                     // ����� ���� ������������
};

if( !( hDC = GetDC( hWnd ) ) )                                  // ����� �� �� �������� �������� ����������?
{
    KillGLWindow();                                             // ������������ �����
    MessageBox( NULL, LPCWSTR("Can't Create A GL Device Context."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;                
}
if( !( PixelFormat = ChoosePixelFormat( hDC, &pfd ) ) )          // ������ �� ���������� ������ �������?
{
    KillGLWindow();                                              // ������������ �����
    MessageBox( NULL, LPCWSTR("Can't Find A Suitable PixelFormat."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
   return false;              
}
if( !SetPixelFormat( hDC, PixelFormat, &pfd ) )                  // �������� �� ���������� ������ �������?
{
    KillGLWindow();                                              // ������������ �����
    MessageBox( NULL, LPCWSTR("Can't Set The PixelFormat."),LPCWSTR( "ERROR)"), MB_OK | MB_ICONEXCLAMATION );
    return false;                
}
if( !( hRC = wglCreateContext( hDC ) ) )                         // �������� �� ���������� �������� ����������?
{
    KillGLWindow();               
    MessageBox( NULL,LPCWSTR( "Can't Create A GL Rendering Context."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION);
    return false;                
}
if( !wglMakeCurrent( hDC, hRC ) )                                 // ����������� ������������ �������� ����������
{
    KillGLWindow();              
    MessageBox( NULL, LPCWSTR("Can't Activate The GL Rendering Context."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;                
}

  ShowWindow( hWnd, SW_SHOW );                                     // �������� ����
  SetForegroundWindow( hWnd );                                     // ������ ������� ���������
  SetFocus( hWnd );                                                // ���������� ����� ���������� �� ���� ����
 
 if( !InitGL() )                                                   // ������������� ������ ��� ���������� ����
 {
    KillGLWindow();                                                // ������������ �����
    MessageBox( NULL, LPCWSTR("Initialization Failed."), LPCWSTR("ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;              
 }
  sceene->ReSizeGLScene( screenW, screenH);                        // �������� ����������� ��� ������ OpenGL ������.
 return true;                  
}
//**********************************************************************************************************************
LRESULT CALLBACK WndGLProc(HWND  hWnd,                       // ���������� ������� ����
                         UINT  uMsg,                         // ��������� ��� ����� ����
                         WPARAM  wParam,                     // �������������� ����������
                         LPARAM  lParam)                     // �������������� ����������
{
 switch (uMsg)                                               // �������� ��������� ��� ����
 {
    case WM_ACTIVATE:                                        // �������� ��������� ���������� ����
    {
       if( !HIWORD( wParam ) )                               // ��������� ��������� �����������
        OpenGlForm->active = true;                           // ��������� �������
       else
        OpenGlForm->active = false;                           // ��������� ������ �� �������
       return 0;                                              // ������������ � ���� ��������� ���������
    }
    case WM_SYSCOMMAND:                                       // ������������� ��������� �������
    {
       switch ( wParam )                                      // ������������� ��������� �����
       {
         case SC_SCREENSAVE:                                  // �������� �� ���������� �����������?
         case SC_MONITORPOWER:                                // �������� �� ������� ������� � ����� ���������� �������?
         return 0;                                            // ������������� ���
        }
      break;           
    }
    case WM_CLOSE:                                            // �� �������� ��������� � ��������?
    {
      PostQuitMessage( 0 );                                   // ��������� ��������� � ������
      return 0;  
    }
    case WM_KEYDOWN:                                          // ���� �� ������ ������?
    {
      OpenGlForm->keys[wParam] = true;       
	  return 0;        
    }
	case WM_KEYUP:                                             // ���� �� �������� �������?
    {
      OpenGlForm->keys[wParam] = false;       
      return 0;  
    }

	case WM_SIZE:                                               // �������� ������� OpenGL ����
    {
       
      sceene->ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );  // ������� �����=Width, ������� �����=Height
      return 0;     
    }

 }
 return DefWindowProc( hWnd, uMsg, wParam, lParam );           // ���������� ��� �������������� ��������� DefWindowProc
}
//**********************************************************************************************************

