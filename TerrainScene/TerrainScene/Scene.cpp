#include "Scene.h"
#include "GLObjects.H"
#include "Texture.h"
#include "Landshaft.h"
#include "OpenGlForm.h"
#include "TexShader.h"

const double PI = 3.1415;
const float Speed=1.7f;
const float R=1000;
const float	 PosLight[]={-32.0,137.0,-10.0,1.0};
CScene *sceene;
bool sound;
CScene::CScene(void)
{
 /* 	Camera.PosX=790;
	Camera.PosY=3;
	Camera.PosZ=1130;
*/
	Camera.PosX=800;
	Camera.PosY=3;
	Camera.PosZ=410;

	Camera.Angle_X=0;
	Camera.Angle_Y =0;
    Camera.walkbias=0;

	CameraAuto.PosX=-15;
	CameraAuto.PosY=280;
	CameraAuto.PosZ=-20;
	CameraAuto.Angle_X=0;
	CameraAuto.Angle_Y = -20;
    CameraAuto.walkbias=0;
	autoOblet=false;
	sound=false;
}   
CScene::~CScene(void)
{
	
}
//**********************************************************************************************************
bool CScene::MoveNext(int type)
{
 float X=Camera.PosX,Z=Camera.PosZ;
 const float height=3.0;
 int ind;
 int h;
 int i,j;
   if(type==0)
  {
 	 X += Speed*sin((-Camera.Angle_X+90)/180.0*PI);
     Z += Speed*cos((-Camera.Angle_X+90)/180.0*PI);
    }
   else 
   if(type==1)
  {
     X -= Speed*sin((-Camera.Angle_X+90)/180.0*PI);
     Z -= Speed*cos((-Camera.Angle_X+90)/180.0*PI);
    }
  else
  if(type==2)
  {
     X -= (float)sin(-Camera.Angle_X* PI/180.0) * Speed;
     Z -= (float)cos(-Camera.Angle_X* PI/180.0) * Speed;
  }
  else
    if(type==3)
  {
     X += (float)sin(-Camera.Angle_X* PI/180.0) * Speed;
     Z += (float)cos(-Camera.Angle_X* PI/180.0) * Speed;
  }
	else
  return false;
 //////
   
  ind= int(X)+int(Z)*Landshaft->LAND_SIZE;
  if(X<0||Z<0||X>Landshaft->LAND_SIZE||Z>Landshaft->LAND_SIZE) return false;
  h=Landshaft->g_HeightMap[ind]+height;
  if(fabs(h-Camera.PosY)<=2)
  {
     for(i=-1;i<=1;i++)
		 for(j=-1;j<=1;j++)
		 {
			 if( (int(X)+j+(int(Z)+i)*Landshaft->LAND_SIZE<0)||
				 (int(X)+j+(int(Z)+i)*Landshaft->LAND_SIZE>Landshaft->LAND_SIZE*Landshaft->LAND_SIZE) )
				 break;
			 if(abs(Landshaft->g_HeightMap[int(X)+j+(int(Z)+i)*Landshaft->LAND_SIZE]+height-int(Camera.PosY))>8)
				 return false;
		 }
	 Camera.PosX = X;
     Camera.PosZ = Z;
			  Camera.PosY=Landshaft->g_HeightMap[ind]+height;
  }
  else
     return false;

	 Camera.PosX = X;
     Camera.PosZ = Z;

  return true;
}
//**********************************************************************************************************
void CScene::HandleControls()
{
	static long xCurPosOld, yCurPosOld;
    
	POINT Point;

	GetCursorPos(&Point);
	Camera.Angle_Y+= (yCurPosOld-Point.y)*0.05f;
	Camera.Angle_X-= (xCurPosOld-Point.x)*0.05f;
    if(Camera.Angle_Y<-30)   Camera.Angle_Y=-30;
	if(Camera.Angle_Y> 50.0) Camera.Angle_Y= 50.0;
	if(Camera.Angle_X< 0.0)   Camera.Angle_X = 359.0;
	if(Camera.Angle_X> 359.0) Camera.Angle_X = 0.0;
	
	if (OpenGlForm->keys[VK_HOME])              
	   Camera.PosY+=Speed;
    if (OpenGlForm->keys[VK_END])              
	   Camera.PosY-=Speed;

    if (OpenGlForm->keys[VK_RIGHT]&&MoveNext(0)==true)             
    {
        if (Camera.walkbiasangle <= 1.0f)    
            Camera.walkbiasangle = 359.0f; 
        else                          
           Camera.walkbiasangle-= 10;
        Camera.walkbias = (float)sin(Camera.walkbiasangle * PI/180.0)/20.0f; // Иммитация походки человека
   }

   if (OpenGlForm->keys[VK_LEFT]&&MoveNext(1)==true)               
   {
         if (Camera.walkbiasangle <= 1.0f)    
            Camera.walkbiasangle = 359.0f; 
         else                        
            Camera.walkbiasangle-= 10;
         Camera.walkbias = (float)sin(Camera.walkbiasangle * PI/180.0)/20.0f; 
   }
   if (OpenGlForm->keys[VK_UP]&&MoveNext(2)==true)                
   {
	//   PlaySoundA(NULL, NULL, SND_ASYNC);
	//   if(sound==false)
    //   PlaySoundA("Res\\Sound\\Run.wav", NULL, SND_ASYNC|SND_LOOP);
 	   
	 //   sound=true;
	    if (Camera.walkbiasangle >= 359.0f)
            Camera.walkbiasangle = 0.0f;
         else                      
             Camera.walkbiasangle+= 10;
         Camera.walkbias = (float)sin(Camera.walkbiasangle * PI/180.0)/20.0f;
   }
   else
	   if(OpenGlForm->keys[VK_UP]==false&&sound==true)
	   {
   //        sound=false;
		 //  PlaySound(NULL, NULL,0);
	   }
   if (OpenGlForm->keys[VK_DOWN]&&MoveNext(3)==true)        
   {
      if (Camera.walkbiasangle <= 1.0f)   
            Camera.walkbiasangle = 359.0f;
      else                         
            Camera.walkbiasangle-= 10;
      Camera.walkbias = (float)sin(Camera.walkbiasangle * PI/180.0)/20.0f; 
    }
    if(Point.x==OpenGlForm->screenW-1)
	{
		Point.x = 1;
		SetCursorPos(Point.x,Point.y);
	}
    if(Point.y==OpenGlForm->screenH-1)
	{
		Point.y = 1;
		SetCursorPos(Point.x,Point.y);
	}
	if(Point.x==0)
	{	
		Point.x = OpenGlForm->screenW;
		SetCursorPos(Point.x,Point.y);
	}
	if(Point.y==0)
	{	
		Point.y = OpenGlForm->screenH;
		SetCursorPos(Point.x,Point.y);
	}

   	xCurPosOld = Point.x;
	yCurPosOld = Point.y;		
}
//**********************************************************************************************************
void CScene::Init()
{
 glUseProgram(TexShader->TexShadPr);
 glActiveTexture(GL_TEXTURE5);
 glBindTexture(GL_TEXTURE_2D, Texture->texture[5]);
 
 GLint tex1;
 tex1=glGetUniformLocation(TexShader->TexShadPr,"texVec");
 glUniform1i(tex1,5);  	
 Landshaft->InitLanshaft();//1!!
 GLObjects->InitModels();//2!!
}
//**********************************************************************************************************
GLvoid CScene::ReSizeGLScene( GLsizei width, GLsizei height)          // Изменить размер и инициализировать окно GL 
{
  if( height == 0 )                                                   // Предотвращение деления на ноль 
     height = 1;


 glViewport( 0, 0, width, height );                                   // Сброс текущей области вывода 
 	 
	 GLfloat LightAmbient[] = {0.0, 0.0, 0.0};
	 GLfloat LightDiff[] = {1.0, 1.0, 1.0, 1.0};
	    GLfloat MaterialAmbient[] = {0.9, 0.9, 0.9, 0.0};
     GLfloat MaterialDiffuse[] = {0.8, 0.8, 0.8, 0.0 };//
     GLfloat MaterialSpecular[] = {0.9, 0.9, 0.9, 1.0 };//
     GLfloat MaterialShininess[] = {100.0};
     GLfloat MaterialEmis[] = {0.21, 0.01, 0.01, 0.0};
////////////////////////////////////////
	glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
  //  glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
 	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiff);
/*	glMaterialfv(GL_FRONT, GL_EMISSION, MaterialEmis);
 	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
 */
 glMatrixMode( GL_PROJECTION );                                       // Выбор матрицы проекций
 glLoadIdentity();                                                    // Сброс матрицы проекции
 gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f,7500 ); // Вычисление соотношения геометрических размеров для окна
 glMatrixMode( GL_MODELVIEW );                                        // Выбор матрицы вида модели
 glLoadIdentity();                                                    // Сброс матрицы вида модели
}
//**********************************************************************************************************
int CScene::DrawGLScene( GLvoid )            
{
	GLfloat ytrans = -Camera.walkbias-0.35f-Camera.PosY;
	int i=0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.25f, .25f, .75f, .25f);

	glLoadIdentity();                                                 // Сброс просмотра
    if(autoOblet==false)
	{
	 HandleControls();	
	  ytrans = -Camera.walkbias-0.35f-Camera.PosY;
	 glRotatef(-Camera.Angle_Y, 1.0f, 0.0, 0.0);
	 glRotatef( Camera.Angle_X, 0.0, 1.0f, 0.0);
	 glTranslatef(-Camera.PosX,ytrans,-Camera.PosZ);

	}
	else
	{
     CameraAuto.Angle_X-=0.3;
 	 CameraAuto.PosX =R*cos(CameraAuto.Angle_X/180.0*PI)+R;
     CameraAuto.PosZ =R*sin(CameraAuto.Angle_X/180.0*PI)+R;
	 glRotatef(-CameraAuto.Angle_Y, 1.0f, 0.0, 0.0);
	 glRotatef( CameraAuto.Angle_X-90, 0.0, 1.0f, 0.0);
	 glTranslatef(-CameraAuto.PosX,-CameraAuto.PosY,-CameraAuto.PosZ);
	}
//shade draw	 
//light
	 glLightfv(GL_LIGHT0, GL_POSITION, PosLight);
// пирамида
glUseProgram(TexShader->TexShadPr);	
glCallList(Object.land[0]); 
glUseProgram(0);
glColor3b(30,0,0);
glDisable(GL_LIGHTING);
glCallList(Object.piramids);// Рисуем пирамиды из списка
glEnable(GL_LIGHTING);

glUseProgram(TexShader->LightShadPr);
glCallList(Object.skyBox);
glCallList(Object.Boxes);// Рисуем пирамиды из списка
glUseProgram(TexShader->WaterShadPr);
GLObjects->Water();
glCallList(Object.Water);// Рисуем пирамиды из списка
//ландшафт	

	                                        // Рисуем ландшафт из списка
//*** 
return true;
}
//**********************************************************************************************************