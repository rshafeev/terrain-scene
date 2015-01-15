#include "OpenGlForm.h"
#include "Scene.H"
#include "TexShader.h"
#include "Texture.h"
COpenGlForm *OpenGlForm;
LRESULT  CALLBACK WndGLProc( HWND, UINT, WPARAM, LPARAM );        // Прототип функции WndProc
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
 MSG  msg;                                                   // Структура для хранения сообщения Windows
 BOOL  done = false;                                         // Логическая переменная для выхода из цикла
 if( !CreateGLWindow( "3D Terrain") )              // Создать наше OpenGL окно
    return;                                                  // Выйти, если окно не может быть создано
 
 // sceene->Init();

 
while(!done)                                                 // Цикл продолжается, пока done не равно true
{
   if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )          // Есть ли в очереди какое-нибудь сообщение?
   {
      if( msg.message == WM_QUIT )                           // Мы поучили сообщение о выходе?
         done = true;                                        // Если так, done=true
      else                                                   // Если нет, обрабатывает сообщения
      {
         TranslateMessage( &msg );                            // Переводим сообщение
         DispatchMessage( &msg );                             // Отсылаем сообщение
      }
   }
   else
   {														  // Прорисовываем сцену.
       if( active )                                           // Активна ли программа?
       {
          if(keys[VK_ESCAPE])                                 // Было ли нажата клавиша ESC?
          {
            done = true;                                      // ESC говорит об останове выполнения программы
          }
          else                                                // обновим экран.
          {
			sceene->DrawGLScene();
            SwapBuffers( hDC );                               // Меняем буфер (двойная буферизация)
          }
        }
	   if( keys[VK_F1] )                                      // Была ли нажата F1?
       {
          keys[VK_F1] = false;                                // Если так, меняем значение ячейки массива на false
          KillGLWindow();                                     // Разрушаем текущее окно
          fullscreen = !fullscreen;                           // Переключаем режим
          if( !CreateGLWindow( "3D Terrain") )          // Пересоздаём наше OpenGL окно
            return;                                           // Выходим, если это невозможно
       }
	   if( keys[VK_F2] )
	   {
            keys[VK_F2] = false; 
			sceene->autoOblet=!sceene->autoOblet;
	   }
   }
}

KillGLWindow();                                                // Разрушаем окно
}
//**********************************************************************************************************
int COpenGlForm::InitGL( GLvoid )// Начальные установки касаемо OpenGL
{	
 glShadeModel( GL_SMOOTH );                                   // Разрешить плавное цветовое сглаживание
 glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                        // Очистка экрана в черный цвет
 glClearDepth( 1.0f );                                        // Разрешить очистку буфера глубины
 glEnable( GL_DEPTH_TEST );                                   // Разрешить тест глубины
 glDepthFunc( GL_LEQUAL );									  // Тип теста глубины
 glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );		  // Улучшение в вычислении перспективы
 if(activeShades==false) 
 {
	 activeShades=true;
    	 
 }
 else
	 glDeleteProgram(TexShader->TexShadPr);
 TexShader->Init();
  Texture->InitTexture();
 sceene->Init();
 return true;												  // Инициализация прошла успешно
}
//**********************************************************************************************************
GLvoid COpenGlForm::KillGLWindow( GLvoid )                    // Корректное разрушение окна
{
 if( fullscreen )                                             // Мы в полноэкранном режиме?
 {
    ChangeDisplaySettings( NULL, 0 );                         // Если да, то переключаемся обратно в оконный режим
    ShowCursor( true );                                       // Показать курсор мышки
 }
 if( hRC )                                                    // Существует ли Контекст Рендеринга?
 {
    if( !wglMakeCurrent( NULL, NULL ) )                       // Возможно ли освободить RC и DC?
      MessageBox( NULL,LPCWSTR( "Release Of DC And RC Failed."),LPCWSTR( "SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION );
    if( !wglDeleteContext( hRC ) )                            // Возможно ли удалить RC?
    {
      MessageBox( NULL,LPCWSTR("Release Rendering Context Failed."),LPCWSTR( "SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION );
    }
    hRC = NULL;                                               // Установить RC в NULL
 }
 if( hDC && !ReleaseDC( hWnd, hDC ) )                         // Возможно ли уничтожить DC?
 {
      MessageBox( NULL,LPCWSTR( "Release Device Context Failed."),LPCWSTR( "SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION );
      hDC=NULL;                                               // Установить DC в NULL
 }
 if(hWnd && !DestroyWindow(hWnd))                             // Возможно ли уничтожить окно?
 {
      MessageBox( NULL,LPCWSTR( "Could Not Release hWnd."),LPCWSTR( "SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION );
      hWnd = NULL;                                            // Установить hWnd в NULL
 }
 if( !UnregisterClass(LPCWSTR( "OpenGL"), hInstance ) )       // Возможно ли разрегистрировать класс
 {
    MessageBox( NULL, LPCWSTR("Could Not Unregister Class."), LPCWSTR("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
    hInstance = NULL;                                         // Установить hInstance в NULL
 }
   hRC=NULL;												  // Постоянный контекст рендеринга
   hDC=NULL;											      // Приватный контекст устройства GDI
   hWnd=NULL;												  // Здесь будет хранится дескриптор окна
   hInstance=NULL;											  // Здесь будет хранится дескриптор приложения
}
//**********************************************************************************************************
BOOL COpenGlForm::CreateGLWindow( const char* title)
{
 GLuint    PixelFormat;										// Хранит результат после поиска
 DWORD    dwStyle;                                          // Обычный стиль окна
 RECT WindowRect;                                           // Grabs Rectangle Upper Left / Lower Right Values
 WNDCLASS	wc;
  WindowRect.left=(long)0;                                  // Установить левую составляющую в 0
  WindowRect.right=(long)formW;                             // Установить правую составляющую в Width
  WindowRect.top=(long)0;                                   // Установить верхнюю составляющую в 0
  WindowRect.bottom=(long)formH;                            // Установить нижнюю составляющую в Height

  wc.hInstance    = GetModuleHandle(NULL);                  // Считаем дескриптор нашего приложения
  wc.style    = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;         // Перерисуем при перемещении и создаём скрытый DC
  wc.lpfnWndProc    = (WNDPROC)WndGLProc;                   // Процедура обработки сообщений
  wc.cbClsExtra    = 0;                                     // Нет дополнительной информации для окна
  wc.cbWndExtra    = 0;                                     // Нет дополнительной информации для окна
  wc.hInstance    = hInstance;                              // Устанавливаем дескриптор
  wc.hIcon    = LoadIcon(NULL, IDI_WINLOGO);                // Загружаем иконку по умолчанию
  wc.hCursor    = LoadCursor(NULL, IDC_ARROW);              // Загружаем указатель мышки
  wc.hbrBackground  = NULL;                                 // Фон не требуется для GL
  wc.lpszMenuName    = NULL;                                // Меню в окне не будет
  wc.lpszClassName  = LPCWSTR("OpenGL");                    // Устанавливаем имя классу
  if( !RegisterClass( &wc ) )                               // Пытаемся зарегистрировать класс окна
  {
    MessageBox( NULL,LPCWSTR( "Failed To Register The Window Class."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;                                           // Выход и возвращение функцией значения false
  }
  if( fullscreen==true )                                    // Полноэкранный режим?
  {
    DEVMODE dmScreenSettings;                               // Режим устройства
    memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );             // Очистка для хранения установок
    dmScreenSettings.dmSize=sizeof( dmScreenSettings );                     // Размер структуры Devmode
	dmScreenSettings.dmPelsWidth  =   screenW;                              // Ширина экрана
	dmScreenSettings.dmPelsHeight  =  screenH;                              // Высота экрана
    dmScreenSettings.dmBitsPerPel  =   screenBitSize;                       // Глубина цвета
    dmScreenSettings.dmFields= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// Режим Пикселя
	//Пытаемся установить выбранный режим и получить результат.  Примечание: CDS_FULLSCREEN убирает панель управления.
    if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
    {
     // Если переключение в полноэкранный режим невозможно, будет предложено два варианта: оконный режим или выход.
       if( MessageBox( NULL,LPCWSTR("The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?"), 
           LPCWSTR( "NeHe GL"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES )
            fullscreen = false;                              // Выбор оконного режима (fullscreen = false)
      else
      {
      // Выскакивающее окно, сообщающее пользователю о закрытие окна.
          MessageBox( NULL, LPCWSTR("Program Will Now Close."),LPCWSTR( "ERROR"), MB_OK | MB_ICONSTOP );
          return false;                                      // Выход и возвращение функцией false
      }
    }
  }

  if(fullscreen)                                              // Мы остались в полноэкранном режиме?
  {
	 dwStyle    =  WS_POPUP;                                  // Обычный стиль окна
     ShowCursor( false );                                     // Скрыть указатель мышки
  }
  else
      dwStyle    =   WS_OVERLAPPEDWINDOW;                      // Обычный стиль окна
  
  AdjustWindowRectEx( &WindowRect, dwStyle, false, WS_EX_APPWINDOW);      // Подбирает окну подходящие размеры
  if( !( hWnd = CreateWindowEx(WS_EX_APPWINDOW,                           // Расширенный стиль для окна
          LPCWSTR("OpenGL"),                                   // Имя класса
		  /*title*/TEXT("3D Terrain"),                                        // Заголовок окна
          WS_CLIPSIBLINGS |									   // Требуемый стиль для окна
          WS_CLIPCHILDREN |                                    // Требуемый стиль для окна
     	  dwStyle,                                             // Выбираемые стили для окна
          0, 0,                                                // Позиция окна
          WindowRect.right-WindowRect.left,                    // Вычисление подходящей ширины
          WindowRect.bottom-WindowRect.top,                    // Вычисление подходящей высоты
          NULL,                                                // Нет родительского
          NULL,                                                // Нет меню
          hInstance,                                           // Дескриптор приложения
          NULL ) ) )                                           // Не передаём ничего до WM_CREATE (???)

  {
    KillGLWindow();                                             // Восстановить экран
    MessageBox( NULL, LPCWSTR("Window Creation Error."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;                                                 
  }

static  PIXELFORMATDESCRIPTOR pfd=                              // pfd сообщает Windows каким будет вывод на экран каждого пикселя
{
    sizeof(PIXELFORMATDESCRIPTOR),                              // Размер дескриптора данного формата пикселей
    1,                                                          // Номер версии
    PFD_DRAW_TO_WINDOW |                                        // Формат для Окна
    PFD_SUPPORT_OPENGL |                                        // Формат для OpenGL
    PFD_DOUBLEBUFFER,                                           // Формат для двойного буфера
    PFD_TYPE_RGBA,                                              // Требуется RGBA формат
    screenBitSize,                                              // Выбирается бит глубины цвета
    0, 0, 0, 0, 0, 0,                                           // Игнорирование цветовых битов
    0,                                                          // Нет буфера прозрачности
    0,                                                          // Сдвиговый бит игнорируется
    0,                                                          // Нет буфера накопления
    0, 0, 0, 0,                                                 // Биты накопления игнорируются
    32,                                                         // 32 битный Z-буфер (буфер глубины)
    0,                                                          // Нет буфера трафарета
    0,                                                          // Нет вспомогательных буферов
    PFD_MAIN_PLANE,                                             // Главный слой рисования
    0,                                                          // Зарезервировано
    0, 0, 0                                                     // Маски слоя игнорируются
};

if( !( hDC = GetDC( hWnd ) ) )                                  // Можем ли мы получить Контекст Устройства?
{
    KillGLWindow();                                             // Восстановить экран
    MessageBox( NULL, LPCWSTR("Can't Create A GL Device Context."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;                
}
if( !( PixelFormat = ChoosePixelFormat( hDC, &pfd ) ) )          // Найден ли подходящий формат пикселя?
{
    KillGLWindow();                                              // Восстановить экран
    MessageBox( NULL, LPCWSTR("Can't Find A Suitable PixelFormat."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
   return false;              
}
if( !SetPixelFormat( hDC, PixelFormat, &pfd ) )                  // Возможно ли установить Формат Пикселя?
{
    KillGLWindow();                                              // Восстановить экран
    MessageBox( NULL, LPCWSTR("Can't Set The PixelFormat."),LPCWSTR( "ERROR)"), MB_OK | MB_ICONEXCLAMATION );
    return false;                
}
if( !( hRC = wglCreateContext( hDC ) ) )                         // Возможно ли установить Контекст Рендеринга?
{
    KillGLWindow();               
    MessageBox( NULL,LPCWSTR( "Can't Create A GL Rendering Context."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION);
    return false;                
}
if( !wglMakeCurrent( hDC, hRC ) )                                 // Попробовать активировать Контекст Рендеринга
{
    KillGLWindow();              
    MessageBox( NULL, LPCWSTR("Can't Activate The GL Rendering Context."),LPCWSTR( "ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;                
}

  ShowWindow( hWnd, SW_SHOW );                                     // Показать окно
  SetForegroundWindow( hWnd );                                     // Слегка повысим приоритет
  SetFocus( hWnd );                                                // Установить фокус клавиатуры на наше окно
 
 if( !InitGL() )                                                   // Инициализация только что созданного окна
 {
    KillGLWindow();                                                // Восстановить экран
    MessageBox( NULL, LPCWSTR("Initialization Failed."), LPCWSTR("ERROR"), MB_OK | MB_ICONEXCLAMATION );
    return false;              
 }
  sceene->ReSizeGLScene( screenW, screenH);                        // Настроим перспективу для нашего OpenGL экрана.
 return true;                  
}
//**********************************************************************************************************************
LRESULT CALLBACK WndGLProc(HWND  hWnd,                       // Дескриптор нужного окна
                         UINT  uMsg,                         // Сообщение для этого окна
                         WPARAM  wParam,                     // Дополнительная информация
                         LPARAM  lParam)                     // Дополнительная информация
{
 switch (uMsg)                                               // Проверка сообщения для окна
 {
    case WM_ACTIVATE:                                        // Проверка сообщения активности окна
    {
       if( !HIWORD( wParam ) )                               // Проверить состояние минимизации
        OpenGlForm->active = true;                           // Программа активна
       else
        OpenGlForm->active = false;                           // Программа теперь не активна
       return 0;                                              // Возвращаемся в цикл обработки сообщений
    }
    case WM_SYSCOMMAND:                                       // Перехватываем системную команду
    {
       switch ( wParam )                                      // Останавливаем системный вызов
       {
         case SC_SCREENSAVE:                                  // Пытается ли запустится скринсейвер?
         case SC_MONITORPOWER:                                // Пытается ли монитор перейти в режим сбережения энергии?
         return 0;                                            // Предотвращаем это
        }
      break;           
    }
    case WM_CLOSE:                                            // Мы получили сообщение о закрытии?
    {
      PostQuitMessage( 0 );                                   // Отправить сообщение о выходе
      return 0;  
    }
    case WM_KEYDOWN:                                          // Была ли нажата кнопка?
    {
      OpenGlForm->keys[wParam] = true;       
	  return 0;        
    }
	case WM_KEYUP:                                             // Была ли отпущена клавиша?
    {
      OpenGlForm->keys[wParam] = false;       
      return 0;  
    }

	case WM_SIZE:                                               // Изменены размеры OpenGL окна
    {
       
      sceene->ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );  // Младшее слово=Width, старшее слово=Height
      return 0;     
    }

 }
 return DefWindowProc( hWnd, uMsg, wParam, lParam );           // пересылаем все необработанные сообщения DefWindowProc
}
//**********************************************************************************************************

