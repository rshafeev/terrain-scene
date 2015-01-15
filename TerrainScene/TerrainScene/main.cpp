
#include "Landshaft.h"
#include "OpenGlForm.h"
#include "Texture.h"
#include "Scene.H"
#include "GLObjects.h"
#include "Landshaft.h"
#include "TexShader.h"
///**********************************************************************************************************
int WINAPI WinMain(HINSTANCE  hInstance,       // ���������� ����������
                   HINSTANCE  hPrevInstance,   // ���������� ������������� ����������
                   LPSTR    lpCmdLine,         // ��������� ��������� ������
                   int    nCmdShow )           // ��������� ����������� ����
{
   Landshaft=new CLandshaft;
   sceene=new CScene;
   Texture= new CTexture;
   OpenGlForm=new COpenGlForm;
   GLObjects= new CGLObjects; 
   TexShader=new CTexShader;
  
   

   OpenGlForm->OnCreate();
   
   delete Landshaft;
   delete sceene;
   delete Texture;
   delete OpenGlForm;
   delete TexShader;
  return 0;
}
//**********************************************************************************************************************
