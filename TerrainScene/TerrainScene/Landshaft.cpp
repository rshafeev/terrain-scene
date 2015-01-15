#include "Landshaft.h"

#include "Texture.h"
#include "GLObjects.h"
#include "TexShader.h"
CLandshaft *Landshaft;
	
CLandshaft::CLandshaft(void)
{
 }

CLandshaft::~CLandshaft(void)
{
}
//***********************************************************************************************
void CLandshaft::GenBedNormal(TPoint *g_NormalMap,int MAP_SIZE,int STEP_SIZE)
{
	int i,j;
	TPoint Normals[6];//нормали всех 6 плоскостей
	TPoint Versh[3];// вершины плоскости
	TPoint NormalRes;// усредненная нормаль вершины
	
 	for ( i = 0; i < 6; i++)
	{
	  Normals[i].x=0;
      Normals[i].y=0;
      Normals[i].z=0;
	}
for ( i = STEP_SIZE; i < MAP_SIZE-STEP_SIZE; i += STEP_SIZE)
    for ( j = STEP_SIZE; j < MAP_SIZE-STEP_SIZE; j += STEP_SIZE)
	{
      if(i+j>MAP_SIZE*MAP_SIZE) continue;
	  if(i+j<0) continue;

	  Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i+STEP_SIZE;Versh[1].y=g_HeightMap[i+STEP_SIZE+j*MAP_SIZE];Versh[1].z=j;
	  Versh[2].x=i+STEP_SIZE;Versh[2].y=g_HeightMap[i+STEP_SIZE+(j+STEP_SIZE)*MAP_SIZE];Versh[2].z=j+STEP_SIZE;
      Normals[0]=Normal(Versh[0],Versh[1],Versh[2]);
	
	  Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i+STEP_SIZE;Versh[1].y=g_HeightMap[i+STEP_SIZE+j*MAP_SIZE];Versh[1].z=j;
	  Versh[2].x=i;Versh[2].y=g_HeightMap[i+(j-STEP_SIZE)*MAP_SIZE];Versh[2].z=j-STEP_SIZE;
	  Normals[1]=Normal(Versh[0],Versh[1],Versh[2]);

      Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i;Versh[1].y=g_HeightMap[i+(j-STEP_SIZE)*MAP_SIZE];Versh[1].z=j-STEP_SIZE;
	  Versh[2].x=i-STEP_SIZE;Versh[2].y=g_HeightMap[i-STEP_SIZE+(j-STEP_SIZE)*MAP_SIZE];Versh[2].z=j-STEP_SIZE;
	  Normals[2]=Normal(Versh[0],Versh[1],Versh[2]);
   
	/*  Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i;Versh[1].y=g_HeightMap[i+(j+STEP_SIZE)*MAP_SIZE];Versh[1].z=j+STEP_SIZE;
	  Versh[2].x=i-STEP_SIZE;Versh[2].y=g_HeightMap[i-STEP_SIZE+(j)*MAP_SIZE];Versh[2].z=j;
	  Normals[3]=Normal(Versh[0],Versh[1],Versh[2]);

      Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i-STEP_SIZE;Versh[1].y=g_HeightMap[i-STEP_SIZE+(j)*MAP_SIZE];Versh[1].z=j;
	  Versh[2].x=i-STEP_SIZE;Versh[2].y=g_HeightMap[i-STEP_SIZE+(j-STEP_SIZE)*MAP_SIZE];Versh[2].z=j-STEP_SIZE;
	  Normals[4]=Normal(Versh[0],Versh[1],Versh[2]);


	  Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i;Versh[1].y=g_HeightMap[i+(j+STEP_SIZE)*MAP_SIZE];Versh[1].z=j+STEP_SIZE;
	  Versh[2].x=i+STEP_SIZE;Versh[2].y=g_HeightMap[i+STEP_SIZE+(j+STEP_SIZE)*MAP_SIZE];Versh[2].z=j+STEP_SIZE;
	  Normals[5]=Normal(Versh[0],Versh[1],Versh[2]);
*/
	    NormalRes.x=(Normals[0].x+Normals[1].x+Normals[2].x+Normals[3].x+Normals[4].x+Normals[5].x);
        NormalRes.y=(Normals[0].y+Normals[1].y+Normals[2].y+Normals[3].y+Normals[4].y+Normals[5].y);
        NormalRes.z=(Normals[0].z+Normals[1].z+Normals[2].z+Normals[3].z+Normals[4].z+Normals[5].z);

		g_NormalMap[i+j*MAP_SIZE]=NormalRes;
	}
}
//***********************************************************************************************
TPoint CLandshaft::Normal(TPoint p1,TPoint p2,TPoint p3)
{
   TPoint NVector;
   NVector.x=(p2.y-p1.y)*(p3.z-p1.z)-(p2.z-p1.z)*(p3.y-p1.y);
   NVector.y=(p3.x-p1.x)*(p2.z-p1.z)-(p2.x-p1.x)*(p3.z-p1.z);
   NVector.z=(p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y);
   return NVector;
}
//***********************************************************************************************
void CLandshaft::GenNormal(TPoint *g_NormalMap,int MAP_SIZE,int STEP_SIZE)
{
	int i,j;
	TPoint Normals[6];//нормали всех 6 плоскостей
	TPoint Versh[3];// вершины плоскости
	TPoint NormalRes;// усредненная нормаль вершины
	bool *FlagNormalMap= new bool[(MAP_SIZE+STEP_SIZE)*(MAP_SIZE+STEP_SIZE)];
	TPoint *PloskNormals= new TPoint[(MAP_SIZE+STEP_SIZE)*(MAP_SIZE+STEP_SIZE)];
	 for(int i=0;i<MAP_SIZE*MAP_SIZE-1;i++)
        FlagNormalMap[i]=false;

 	for ( i = 0; i < 6; i++)
	{
	  Normals[i].x=0;
      Normals[i].y=0;
      Normals[i].z=0;
	}
for ( i = STEP_SIZE; i < MAP_SIZE-STEP_SIZE; i += STEP_SIZE)
    for ( j = STEP_SIZE; j < MAP_SIZE-STEP_SIZE; j += STEP_SIZE)
	{
      if(i+j>MAP_SIZE*MAP_SIZE) continue;
	  if(i+j<0) continue;

	  if(FlagNormalMap[i+j*MAP_SIZE]==false)
	  {
	  Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i+STEP_SIZE;Versh[1].y=g_HeightMap[i+STEP_SIZE+j*MAP_SIZE];Versh[1].z=j;
	  Versh[2].x=i+STEP_SIZE;Versh[2].y=g_HeightMap[i+STEP_SIZE+(j+STEP_SIZE)*MAP_SIZE];Versh[2].z=j+STEP_SIZE;
      Normals[0]=Normal(Versh[0],Versh[1],Versh[2]);
      PloskNormals[i+j*MAP_SIZE]=Normals[0];
	  FlagNormalMap[i+j*MAP_SIZE]=true;
	  }
	  else
       Normals[0]=PloskNormals[i+j*MAP_SIZE];

      if(FlagNormalMap[i+(STEP_SIZE+j)*MAP_SIZE]==false)
	  {
      Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i+STEP_SIZE;Versh[1].y=g_HeightMap[i+STEP_SIZE+j*MAP_SIZE];Versh[1].z=j;
	  Versh[2].x=i;Versh[2].y=g_HeightMap[i+(j-STEP_SIZE)*MAP_SIZE];Versh[2].z=j-STEP_SIZE;
	  Normals[1]=Normal(Versh[0],Versh[1],Versh[2]);
	  PloskNormals[i+(STEP_SIZE+j)*MAP_SIZE]=Normals[1];
	  FlagNormalMap[i+(STEP_SIZE+j)*MAP_SIZE]=true;
	  }
	  else
       Normals[1]= PloskNormals[i+(STEP_SIZE+j)*MAP_SIZE];

	  if(FlagNormalMap[i+STEP_SIZE+j*MAP_SIZE]==false)
	  {
     Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i;Versh[1].y=g_HeightMap[i+(j-STEP_SIZE)*MAP_SIZE];Versh[1].z=j-STEP_SIZE;
	  Versh[2].x=i-STEP_SIZE;Versh[2].y=g_HeightMap[i-STEP_SIZE+(j-STEP_SIZE)*MAP_SIZE];Versh[2].z=j-STEP_SIZE;
	  Normals[2]=Normal(Versh[0],Versh[1],Versh[2]);
	  PloskNormals[STEP_SIZE+i+j*MAP_SIZE]=Normals[2];
	  FlagNormalMap[STEP_SIZE+i+j*MAP_SIZE]=true;
	  }
	  else
       Normals[2]=PloskNormals[i+STEP_SIZE+j*MAP_SIZE];

	    if(FlagNormalMap[i-STEP_SIZE+j*MAP_SIZE]==false)
	  {
   
	  Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i;Versh[1].y=g_HeightMap[i+(j+STEP_SIZE)*MAP_SIZE];Versh[1].z=j+STEP_SIZE;
	  Versh[2].x=i-STEP_SIZE;Versh[2].y=g_HeightMap[i-STEP_SIZE+(j)*MAP_SIZE];Versh[2].z=j;
	  Normals[3]=Normal(Versh[0],Versh[1],Versh[2]);
	  PloskNormals[-STEP_SIZE+i+j*MAP_SIZE]=Normals[3];
	  FlagNormalMap[-STEP_SIZE+i+j*MAP_SIZE]=true;
	  }
	  else
       Normals[3]=PloskNormals[i-STEP_SIZE+j*MAP_SIZE];

    if(FlagNormalMap[i+(-STEP_SIZE+j)*MAP_SIZE]==false)
	  {
   
	  Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i-STEP_SIZE;Versh[1].y=g_HeightMap[i-STEP_SIZE+(j)*MAP_SIZE];Versh[1].z=j;
	  Versh[2].x=i-STEP_SIZE;Versh[2].y=g_HeightMap[i-STEP_SIZE+(j-STEP_SIZE)*MAP_SIZE];Versh[2].z=j-STEP_SIZE;
	  Normals[4]=Normal(Versh[0],Versh[1],Versh[2]);
	  PloskNormals[i+(j-STEP_SIZE)*MAP_SIZE]=Normals[4];
	  FlagNormalMap[i+(j-STEP_SIZE)*MAP_SIZE]=true;
	  }
	  else
       Normals[4]=PloskNormals[i+(j-STEP_SIZE)*MAP_SIZE];

   if(FlagNormalMap[i-STEP_SIZE+(-STEP_SIZE+j)*MAP_SIZE]==false)
	  {
 
	  Versh[0].x=i;Versh[0].y=g_HeightMap[i+j*MAP_SIZE];Versh[0].z=j;
	  Versh[1].x=i;Versh[1].y=g_HeightMap[i+(j+STEP_SIZE)*MAP_SIZE];Versh[1].z=j+STEP_SIZE;
	  Versh[2].x=i+STEP_SIZE;Versh[2].y=g_HeightMap[i+STEP_SIZE+(j+STEP_SIZE)*MAP_SIZE];Versh[2].z=j+STEP_SIZE;
	  Normals[5]=Normal(Versh[0],Versh[1],Versh[2]);
   	  PloskNormals[i-STEP_SIZE+(j-STEP_SIZE)*MAP_SIZE]=Normals[5];
	  FlagNormalMap[i-STEP_SIZE+(j-STEP_SIZE)*MAP_SIZE]=true;
	  }
	  else
       Normals[5]=PloskNormals[i-STEP_SIZE+(j-STEP_SIZE)*MAP_SIZE];

	    NormalRes.x=(Normals[0].x+Normals[1].x+Normals[2].x+Normals[3].x+Normals[4].x+Normals[5].x);
        NormalRes.y=(Normals[0].y+Normals[1].y+Normals[2].y+Normals[3].y+Normals[4].y+Normals[5].y);
        NormalRes.z=(Normals[0].z+Normals[1].z+Normals[2].z+Normals[3].z+Normals[4].z+Normals[5].z);

		g_NormalMap[i+j*MAP_SIZE]=NormalRes;
	}
	delete[] FlagNormalMap;
	delete[] PloskNormals;
}
//***********************************************************************************************
int* CLandshaft::LoadRawFile(LPSTR strName, int nSize)
{
  BYTE *pTempMap= new BYTE[nSize];
  int *HeightMap= new int[(LAND_SIZE+STEP_SIZE)*(LAND_SIZE+STEP_SIZE)];

  FILE *pFile = NULL;
  pFile = fopen( strName, "rb" );
  fread( pTempMap, 1, nSize, pFile );

  
  fclose(pFile);
  for(int i=0;i<nSize;i++)
   HeightMap[i]=int(pTempMap[i]);

  delete[] pTempMap;
  return HeightMap;
 }

//***********************************************************************************************
int CLandshaft::InitLanshaft()
{
TPoint sdvig;	
TPoint *g_NormalMap; 
int i,j;
sceene->Object.land[0]=glGenLists(1);                 //создаем два списка

///////////загружаем основной ландшафт
    LAND_SIZE=4096;
    STEP_SIZE=4;

g_NormalMap= new TPoint[(LAND_SIZE+STEP_SIZE)*(LAND_SIZE+STEP_SIZE)];

g_HeightMap=LoadRawFile("RES\\my.raw", LAND_SIZE * LAND_SIZE);  
int X,Y;
 /*for ( X = 0; X < LAND_SIZE-STEP_SIZE; X += 1 )
    for ( Y = 0; Y < LAND_SIZE-STEP_SIZE; Y += 1 )
    {     

      if(X>650&&X<1470&&Y>1070&&Y<1600)
		 g_HeightMap[X+Y*LAND_SIZE]=g_HeightMap[X+Y*LAND_SIZE]*(-1);
		 
    }
*/

for ( X = 650; X < 1300; X ++)
    for ( Y = 700; Y <1700; Y++)
		 g_HeightMap[X+Y*LAND_SIZE]=g_HeightMap[X+Y*LAND_SIZE]*(-1);
		
 for(i=0;i<LAND_SIZE*LAND_SIZE-1;i++)
 {
   g_NormalMap[i].x=0;
   g_NormalMap[i].y=0;
   g_NormalMap[i].z=0;
 }
 //GenBedNormal(g_NormalMap,LAND_SIZE,STEP_SIZE);
 GenNormal(g_NormalMap,LAND_SIZE,STEP_SIZE); 
  sdvig.x=0;
  sdvig.y=0;
  sdvig.z=0;
  RenderHeightMap(g_HeightMap,g_NormalMap,LAND_SIZE,STEP_SIZE,0,sdvig,0);   
  delete[]	g_NormalMap;
////////////загружаем разбросанные камни

  return TRUE;               
}
//***********************************************************************************************
void CLandshaft::SetVertexColor(int height)
{

}
//***********************************************************************************************
void CLandshaft::RenderHeightMap(int *pHeightMap,TPoint g_NormalMap[],int MAP_SIZE,
								 int STEP_SIZE,int texture,TPoint sdvig,int indexSpisok) // Визуализация карты высоты с помощью квадратов
{
	//const GLfloat TextureBit = 1.0f/(float)2000; 
 int X = 0, Y = 0;                                 // Создаем пару переменных для перемещения по массиву
 const float Texcord=1.0;
 TPoint p[4];
 if(!pHeightMap) return;                           // Данные корректны?
////////////////////////////////////////
//Высчитываем нормали 
////////////////////////////////////////
glNewList(sceene->Object.land[indexSpisok],GL_COMPILE);                        // Новый откомпилированный список отображения box
  	 //glUseProgram(0);
 
 glUseProgram(TexShader->TexShadPr);
  GLint tex1,tex2,Obgtex,tex3;
 glActiveTexture(GL_TEXTURE0);
 glBindTexture(GL_TEXTURE_2D, Texture->texture[0]);
 
 glActiveTexture(GL_TEXTURE1);
 glBindTexture(GL_TEXTURE_2D, Texture->texture[1]);
 
 glActiveTexture(GL_TEXTURE2);
 glBindTexture(GL_TEXTURE_2D, Texture->texture[2]);

 tex1=glGetUniformLocation(TexShader->TexShadPr,"tex1");
 glUniform1i(tex1,0);
 tex2=glGetUniformLocation(TexShader->TexShadPr,"tex2");
 glUniform1i(tex2,1);
 tex3=glGetUniformLocation(TexShader->TexShadPr,"tex3");
 glUniform1i(tex3,2);

 for ( X = 0; X < MAP_SIZE-STEP_SIZE; X += STEP_SIZE )
    for ( Y = 0; Y < MAP_SIZE-STEP_SIZE; Y += STEP_SIZE )
    {     
		
		 p[0].x = X+sdvig.x;              
         p[0].y = pHeightMap[X + (Y * MAP_SIZE)]+sdvig.y;  
         p[0].z = Y+sdvig.z;  
		 
		 p[1].x = X+sdvig.x;                    
         p[1].y = pHeightMap[X + (Y+STEP_SIZE) * MAP_SIZE]+sdvig.y;  
         p[1].z = Y + STEP_SIZE+sdvig.z;              
  	     p[2].x =X + STEP_SIZE+sdvig.x; 
         p[2].y = pHeightMap[X +STEP_SIZE+ (Y+STEP_SIZE) * MAP_SIZE]+sdvig.y;  
         p[2].z = Y + STEP_SIZE+sdvig.z;
		 p[3].x =X + STEP_SIZE+sdvig.x; 
         p[3].y = pHeightMap[X +STEP_SIZE+ (Y * MAP_SIZE)]+sdvig.y;  
         p[3].z =Y+sdvig.z;

	
	glBegin(GL_QUADS);                           //GL_TRIANGLE_FAN  Полигоны GL_LINES GL_QUADS  GL_TRIANGLE_STRIP GL_LINE_STRIP
		 glMultiTexCoord2f(GL_TEXTURE0,0,0);
		 glMultiTexCoord2f(GL_TEXTURE1,0,0);
		 glMultiTexCoord2f(GL_TEXTURE2,0,0);
		 glNormal3f(g_NormalMap[X + (Y * MAP_SIZE)].x,
			        g_NormalMap[X + (Y * MAP_SIZE)].y,
					g_NormalMap[X + (Y * MAP_SIZE)].z);     
         glVertex3i(p[0].x, p[0].y, p[0].z);      
                                                        
	     glMultiTexCoord2f(GL_TEXTURE0,Texcord,0.0);
		 glMultiTexCoord2f(GL_TEXTURE1,Texcord,0.0);
		 glMultiTexCoord2f(GL_TEXTURE2,Texcord,0.0);
		 glNormal3f(g_NormalMap[X + (Y + STEP_SIZE )*MAP_SIZE].x,
			        g_NormalMap[X + (Y + STEP_SIZE )*MAP_SIZE].y,
					g_NormalMap[X + (Y + STEP_SIZE )*MAP_SIZE].z);    
         glVertex3i(p[1].x, p[1].y, p[1].z);     
         
         glMultiTexCoord2f(GL_TEXTURE0,0.0,Texcord);
		 glMultiTexCoord2f(GL_TEXTURE1,0.0,Texcord);
		 glMultiTexCoord2f(GL_TEXTURE2,0.0,Texcord);
		 glNormal3f(g_NormalMap[X + STEP_SIZE + ((Y + STEP_SIZE) * MAP_SIZE)].x,
			        g_NormalMap[X + STEP_SIZE + ((Y + STEP_SIZE) * MAP_SIZE)].y,
					g_NormalMap[X + STEP_SIZE + ((Y + STEP_SIZE) * MAP_SIZE)].z);    
         glVertex3i(p[2].x, p[2].y, p[2].z);     
       
         glMultiTexCoord2f(GL_TEXTURE0,Texcord,Texcord);
		 glMultiTexCoord2f(GL_TEXTURE1,Texcord,Texcord);
		 glMultiTexCoord2f(GL_TEXTURE2,Texcord,Texcord);
		 glNormal3f(g_NormalMap[X + STEP_SIZE + ((Y) * MAP_SIZE)].x,
			        g_NormalMap[X + STEP_SIZE + ((Y) * MAP_SIZE)].y,
					g_NormalMap[X + STEP_SIZE + ((Y) * MAP_SIZE)].z);    
         glVertex3i( p[3].x, p[3].y, p[3].z);     
	
	glEnd();
	}
  glEndList();                                                // Закончили создание списка land
  
} 
//***********************************************************************************************


