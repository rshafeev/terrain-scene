#include "GLObjects.h"
#include "Scene.h"
#include "Texture.h"
#include "TexShader.h"
#include "atlstr.h"
#include "string.h"
#include "stdlib.h"
#include "Landshaft.h"
CGLObjects *GLObjects; 
CGLObjects::CGLObjects(void)
{
PiramCol=0;
volna[0]=0;
volna[1]=1;
}

CGLObjects::~CGLObjects(void)
{
}
//*****************************************************************************************************
void CGLObjects::Water()
{
GLint tex1;	
TPoint p1,p2;

p1.x=650;p1.y=-34; p1.z=700;
p2.x=1300;p2.y=-34; p2.z=1700;
//sceene->Object.Water=glGenLists(2);                                //создаем 1 списoк
//glNewList(sceene->Object.Water,GL_COMPILE);                        // Новый откомпилированный список отображения

 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture->texWater[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture->texWater[1]);


	tex1=glGetUniformLocation(TexShader->WaterShadPr,"tex1");
    glUniform1i(tex1,0);

	tex1=glGetUniformLocation(TexShader->WaterShadPr,"tex2");
    glUniform1i(tex1,1);

	tex1=glGetUniformLocation(TexShader->WaterShadPr,"volna");
    glUniform2f(tex1,volna[0],volna[1]);

	//volna[0]-=0.001;
	//volna[1]+=0.001;

	if(volna[0]<0.5)volna[0]=0.8;
	if(volna[1]<0.5)volna[1]=0.8;
	if(volna[0]>0.8)volna[0]=0.5;
	if(volna[1]>0.8)volna[1]=0.5;
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE); 


 glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(p1.x,-35,p1.z);
  glTexCoord2f(2.0f, 0.0f);
  glVertex3f(p2.x,-35,p1.z);
  glTexCoord2f(2.0f, 2.0f);
  glVertex3f(p2.x,-35,p2.z);
  glTexCoord2f(0.0f, 2.0f);
  glVertex3f(p1.x,-35,p2.z);
 glDisable(GL_BLEND);
  glEnd();
 glEnable(GL_DEPTH);
glDisable(GL_BLEND);
//glEndList();
}
//*****************************************************************************************************
void CGLObjects::Boxes()
{
TPoint NVector;
int i,j,k;
int boxCol;
int minx,minz,maxx,maxz;
float lengthSumm,ltemp;//сумма длин стдлины сторон 
float ***Boxes;
TPoint **NormalBoxes;
boxCol=LoadObjectFromFile("RES\\Models\\box.cord",&Boxes);
NormalBoxes=new TPoint*[boxCol+2]; 

	   GLint tex1;

// изменяем карту высот
for(k=0;k<boxCol;k++)
{
//ищем минимум и макс точки по х и z
  minx=Boxes[k][0][0];
  maxx=Boxes[k][0][0];
  minz=Boxes[k][0][2];
  maxz=Boxes[k][0][2];
  lengthSumm=sqrt(pow((Boxes[k][0][0]-Boxes[k][1][0]),2)+pow((Boxes[k][0][1]-Boxes[k][1][1]),2))+
             sqrt(pow((Boxes[k][0][0]-Boxes[k][4][0]),2)+pow((Boxes[k][0][1]-Boxes[k][4][1]),2))+
             sqrt(pow((Boxes[k][1][0]-Boxes[k][5][0]),2)+pow((Boxes[k][1][1]-Boxes[k][5][1]),2))+
	         sqrt(pow((Boxes[k][4][0]-Boxes[k][5][0]),2)+pow((Boxes[k][4][1]-Boxes[k][5][1]),2));
	         	         

for(i=0;i<8;i++)
  {
    if(Boxes[k][i][0]<minx)minx=Boxes[k][i][0];
    if(Boxes[k][i][0]>maxx)maxx=Boxes[k][i][0];
    if(Boxes[k][i][2]<minz)minz=Boxes[k][i][2];
    if(Boxes[k][i][2]>maxz)maxz=Boxes[k][i][2];
  }

  for(i=minx;i<maxx;i++)
   for(j=minz;j<maxz;j++)
   {

	     ltemp=sqrt(pow((Boxes[k][0][0]-Boxes[k][1][0]),2)+pow((Boxes[k][0][1]-Boxes[k][1][1]),2))+
             sqrt(pow((Boxes[k][0][0]-i),2)+pow((j-Boxes[k][0][1]),2))+
             sqrt(pow((Boxes[k][1][0]-Boxes[k][5][0]),2)+pow((Boxes[k][1][1]-Boxes[k][5][1]),2))+
	         sqrt(pow((i-Boxes[k][5][0]),2)+pow((j-Boxes[k][5][1]),2));
	//	 if(ltemp>lengthSumm) continue;

		   ltemp=sqrt(pow((i-Boxes[k][1][0]),2)+pow((j-Boxes[k][1][1]),2))+
             sqrt(pow((i-Boxes[k][4][0]),2)+pow((j-Boxes[k][4][1]),2))+
             sqrt(pow((Boxes[k][1][0]-Boxes[k][5][0]),2)+pow((Boxes[k][1][1]-Boxes[k][5][1]),2))+
	         sqrt(pow((Boxes[k][4][0]-Boxes[k][5][0]),2)+pow((Boxes[k][4][1]-Boxes[k][5][1]),2));
    //    if(ltemp>lengthSumm) continue;

           lengthSumm=sqrt(pow((Boxes[k][0][0]-i),2)+pow((Boxes[k][0][1]-j),2))+
             sqrt(pow((Boxes[k][0][0]-Boxes[k][4][0]),2)+pow((Boxes[k][0][1]-Boxes[k][4][1]),2))+
             sqrt(pow((i-Boxes[k][5][0]),2)+pow((j-Boxes[k][5][1]),2))+
	         sqrt(pow((Boxes[k][4][0]-Boxes[k][5][0]),2)+pow((Boxes[k][4][1]-Boxes[k][5][1]),2));
	//	 if(ltemp>lengthSumm) continue;

	   Landshaft->g_HeightMap[i+Landshaft->LAND_SIZE*j]=-255;
   }

}
 sceene->Object.Boxes=glGenLists(1);                                //создаем 1 списoк
 glNewList(sceene->Object.Boxes,GL_COMPILE);                        // Новый откомпилированный список отображения box
 glActiveTextureARB(GL_TEXTURE4);
 glBindTexture(GL_TEXTURE_2D, Texture->texBoxes);
 tex1=glGetUniformLocationARB(TexShader->LightShadPr,"tex1");
 glUniform1iARB(tex1,4);
 
for(i=0;i<boxCol;i++)
{
	NormalBoxes[i]=new TPoint[4]; 
	NormalBoxes[i][0]=Normal(Boxes[i][0],Boxes[i][1],Boxes[i][4]);
	NormalBoxes[i][1]=Normal(Boxes[i][2],Boxes[i][1],Boxes[i][4]);
	NormalBoxes[i][2]=Normal(Boxes[i][2],Boxes[i][3],Boxes[i][4]);
	NormalBoxes[i][3]=Normal(Boxes[i][0],Boxes[i][3],Boxes[i][4]);
}

glEnable(GL_NORMALIZE);
for(i=0;i<boxCol;i++)
{
 	  glBegin(GL_QUADS);                                           // Начало рисования пирамиды 1

	    glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalBoxes[i][0].x, NormalBoxes[i][0].y,NormalBoxes[i][0].z);
		glVertex3f(Boxes[i][0][0], Boxes[i][0][1],Boxes[i][0][2]);    
		glTexCoord2f(3.0f, 0.0f);
  	    glNormal3f( NormalBoxes[i][0].x, NormalBoxes[i][0].y,NormalBoxes[i][0].z);
 		glVertex3f(Boxes[i][1][0], Boxes[i][1][1],Boxes[i][1][2]);        
		glTexCoord2f(3.0f, 3.0f);
		glNormal3f( NormalBoxes[i][0].x, NormalBoxes[i][0].y,NormalBoxes[i][0].z);
 	    glVertex3f(Boxes[i][2][0], Boxes[i][2][1],Boxes[i][2][2]);                
		glTexCoord2f(0.0f, 3.0f);
		glNormal3f( NormalBoxes[i][0].x, NormalBoxes[i][0].y,NormalBoxes[i][0].z);
 	    glVertex3f(Boxes[i][3][0], Boxes[i][3][1],Boxes[i][3][2]);  

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][0][0], Boxes[i][0][1],Boxes[i][0][2]); 
		glTexCoord2f(0.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][3][0], Boxes[i][3][1],Boxes[i][3][2]);   
		glTexCoord2f(3.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][7][0], Boxes[i][7][1],Boxes[i][7][2]);     
		glTexCoord2f(3.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][4][0], Boxes[i][4][1],Boxes[i][4][2]);  

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][1][0], Boxes[i][1][1],Boxes[i][1][2]); 
		glTexCoord2f(0.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][2][0], Boxes[i][2][1],Boxes[i][2][2]);   
		glTexCoord2f(3.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][6][0], Boxes[i][6][1],Boxes[i][6][2]);     
		glTexCoord2f(3.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][5][0], Boxes[i][5][1],Boxes[i][5][2]);  

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][4][0], Boxes[i][4][1],Boxes[i][4][2]); 
		glTexCoord2f(3.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][5][0], Boxes[i][5][1],Boxes[i][5][2]);   
		glTexCoord2f(3.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][6][0], Boxes[i][6][1],Boxes[i][6][2]);     
		glTexCoord2f(0.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][7][0], Boxes[i][7][1],Boxes[i][7][2]);  

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][0][0], Boxes[i][0][1],Boxes[i][0][2]); 
		glTexCoord2f(3.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][1][0], Boxes[i][1][1],Boxes[i][1][2]);   
		glTexCoord2f(3.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][5][0], Boxes[i][5][1],Boxes[i][5][2]);     
		glTexCoord2f(0.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][4][0], Boxes[i][4][1],Boxes[i][4][2]);  

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][2][0], Boxes[i][2][1],Boxes[i][2][2]); 
		glTexCoord2f(3.0f, 0.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][6][0], Boxes[i][6][1],Boxes[i][6][2]);   
		glTexCoord2f(3.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][7][0], Boxes[i][7][1],Boxes[i][7][2]);     
		glTexCoord2f(0.0f, 3.0f);
		glNormal3f( NormalBoxes[i][1].x, NormalBoxes[i][1].y,NormalBoxes[i][1].z);
        glVertex3f(Boxes[i][3][0], Boxes[i][3][1],Boxes[i][3][2]);  

  glEnd();     
}
glEndList(); 

 glColor4f(1.0f, 1.0f, 1.0f, 1.0f);                                            // Сбрасываем цвет
 for(i=0;i<boxCol;i++)
	{
       for(j=0;j<8;j++)
  		 delete[] Boxes[i][j];
	   delete[] Boxes[i];
	   delete[] NormalBoxes[i];
	}
    delete[] NormalBoxes;
	delete[] Boxes;
}
//***********************************************************************************************
void CGLObjects::SkyBox(float x, float y, float z, float width, float height, float length)
{
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;
		   GLint tex1;
 

	glNewList(sceene->Object.skyBox,GL_COMPILE);                        // Новый откомпилированный список отображения box
 glActiveTextureARB(GL_TEXTURE4);
 glBindTexture(GL_TEXTURE_2D, Texture->texSky[0]);
 tex1=glGetUniformLocationARB(TexShader->LightShadPr,"tex1");
 glUniform1iARB(tex1,4);
 glEnable(GL_NORMALIZE);	
 
 glBegin(GL_QUADS);
 		// Установим текстурные координаты и вершины ЗАДНЕЙ стороны
	    glNormal3f(-2000.0,-2400.0,0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,	y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,	y,z);
 
	glEnd();
 	glBegin(GL_QUADS);
 		// Установим текстурные координаты и вершины ПЕРЕДНЕЙ стороны
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,	y + height, z + length);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(x + width, y,z + length);
	glEnd();
 	glBegin(GL_QUADS);
 		// Установим текстурные координаты и вершины ВЕРХНЕЙ стороны
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,	y + height,z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,	y + height,z);
 
	glEnd();
 	glBegin(GL_QUADS);
 		// Установим текстурные координаты и вершины ЛЕВОЙ стороны
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,	y + height,z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,	y + height,z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,	y,z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,	y,z);
	glEnd();
 	glBegin(GL_QUADS);
 		// Установим текстурные координаты и вершины ПРАВОЙ стороны
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height,z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,z);
	glEnd();
	//**
	glEndList(); 
}
//***********************************************************************************************
TPoint CGLObjects::Normal(float *p1,float *p2,float *p3)
{
   TPoint NVector;
   NVector.x=(p2[1]-p1[1])*(p3[2]-p1[2])-(p2[2]-p1[2])*(p3[1]-p1[1]);
   NVector.y=(p3[0]-p1[0])*(p2[2]-p1[2])-(p2[0]-p1[0])*(p3[2]-p1[2]);
   NVector.z=(p2[0]-p1[0])*(p3[1]-p1[1])-(p3[0]-p1[0])*(p2[1]-p1[1]);

   return NVector;
}
//*****************************************************************************************************
char * CGLObjects::StrCopy(char *str,int index,int col)
{
 char *szResult=new char[col+1];
 int i;
 for(i=index;i<col;i++)
   szResult[i-index]=str[i];
 szResult[i-index]='\0';
 return szResult;
}
//*****************************************************************************************************
char * CGLObjects::StrDelete(char *str,int index,int col)
{
char *szResult=new char[strlen(str)-col+1];
int nCounter = strlen(str);
int i;
for(i=0;i<index;i++)
  szResult[i]=str[i];

for(i=index+col;i<nCounter;i++)
  szResult[i-col]=str[i];
szResult[i-col]='\0';
return szResult;
}
//*****************************************************************************************************
int CGLObjects::LoadObjectFromFile(char *FileName,float**** objects)
{
	const int sizeS=400;
	FILE *File;
	char *str=new char [sizeS];
	char *buf;
	int colObject=0;
    int i,j,k;
	int ind=0,s=0;
	float ***mass;

	File=fopen(FileName,"r");
	if(File==NULL)
      return 0;	
// узнаем кол-во объектов в файле, ко-во точек у каждого объекта
	while(fscanf_s(File,"%s",str,sizeS)!=EOF)
     colObject++;// подсчитали кол-во моделей( кол-вострок)	
	mass=new float**[colObject+1];
	fclose(File);
	File=fopen(FileName,"r");
    i=0;
	while(k=fscanf_s(File,"%s",str,sizeS)!=EOF)
	{
		j=0;
		k=0;
		while(str[j]!='\0')
		{
			if(str[j]=='(')
                k++;
			j++;
		}
		mass[i]=new float*[k+1];
			
	    i++;
}
//////
	fclose(File);
	File=fopen(FileName,"r");

	while(fscanf_s(File,"%s",str,sizeS)!=EOF)
	{
		i=0;
		j=0;
		k=-1;
		while(strlen(str)!=0)
		{
	    	if(str[j]=='(') 
			{
				k++;
	     		mass[ind][k]=new float[3];
				s=0;
				str=StrDelete(str,0,1);
				j=0;
			}
            if(str[j]==','||str[j]==')')
			{
				buf=StrCopy(str,0,j);
				str=StrDelete(str,0,j+1);
				mass[ind][k][s]=atof(buf);
				s++;
				delete []buf;
				buf=NULL;
				j=-1;
			}
			if(str[j]==')')
			{
				str=StrDelete(str,0,1);
				j=-1;
			}
			j++;
		}
		//delete []buf;
		delete [] str;
		str=NULL;
		str=new char [2*sizeS];
	    ind++;
	}
	*objects= mass;
	return colObject;
}
//*****************************************************************************************************
void CGLObjects::Piramida()
{
TPoint NVector;
int i,j,k;
int minx,minz,maxx,maxz;
float ***Piram;
TPoint **NormalPirams;
PiramCol=LoadObjectFromFile("RES\\Models\\piramids.cord",&Piram);
NormalPirams=new TPoint*[PiramCol+2]; 
sceene->Object.piramids=glGenLists(1);                                //создаем 1 списoк
const float ind=10;
 //!!!!!!!!!!!!
	   // изменяем карту высот
for(k=0;k<PiramCol;k++)
{
//ищем минимум и макс точки по х и z
  minx=Piram[k][0][0];
  maxx=Piram[k][0][0];
  minz=Piram[k][0][2];
  maxz=Piram[k][0][2];
      
for(i=0;i<5;i++)
  {
    if(Piram[k][i][0]<minx)minx=Piram[k][i][0];
    if(Piram[k][i][0]>maxx)maxx=Piram[k][i][0];
    if(Piram[k][i][2]<minz)minz=Piram[k][i][2];
    if(Piram[k][i][2]>maxz)maxz=Piram[k][i][2];
  }
  for(i=minx;i<maxx;i++)
   for(j=minz;j<maxz;j++)
   {
	   Landshaft->g_HeightMap[i+Landshaft->LAND_SIZE*j]=-255;
   }
}
 //!!!!!!!!!!!!

 glNewList(sceene->Object.piramids,GL_COMPILE);                        // Новый откомпилированный список отображения box
 glUseProgram(TexShader->TexShadPr);
  GLint tex1,tex2,Obgtex,tex3;
 glActiveTexture(GL_TEXTURE0);
 glBindTexture(GL_TEXTURE_2D, Texture->texture[4]);
 
 glActiveTexture(GL_TEXTURE1);
 glBindTexture(GL_TEXTURE_2D, Texture->texture[0]);
 
 glActiveTexture(GL_TEXTURE2);
 glBindTexture(GL_TEXTURE_2D, Texture->texture[0]);

 tex1=glGetUniformLocation(TexShader->TexShadPr,"tex1");
 glUniform1i(tex1,0);
 tex2=glGetUniformLocation(TexShader->TexShadPr,"tex2");
 glUniform1i(tex2,1);
 tex3=glGetUniformLocation(TexShader->TexShadPr,"tex3");
 glUniform1i(tex3,2);
for(i=0;i<PiramCol;i++)
{
	NormalPirams[i]=new TPoint[12]; 
	
	NormalPirams[i][0]=Normal(Piram[i][0],Piram[i][1],Piram[i][4]);
	NormalPirams[i][1]=Normal(Piram[i][0],Piram[i][1],Piram[i][4]);
	NormalPirams[i][2]=Normal(Piram[i][0],Piram[i][1],Piram[i][4]);
    
	NormalPirams[i][3]=Normal(Piram[i][2],Piram[i][1],Piram[i][4]);
    NormalPirams[i][4]=Normal(Piram[i][2],Piram[i][1],Piram[i][4]);
    NormalPirams[i][5]=Normal(Piram[i][2],Piram[i][1],Piram[i][4]);

	NormalPirams[i][6]=Normal(Piram[i][2],Piram[i][3],Piram[i][4]);
    NormalPirams[i][7]=Normal(Piram[i][2],Piram[i][3],Piram[i][4]);
    NormalPirams[i][8]=Normal(Piram[i][2],Piram[i][3],Piram[i][4]);

	NormalPirams[i][9]=Normal(Piram[i][0],Piram[i][3],Piram[i][4]);
    NormalPirams[i][10]=Normal(Piram[i][0],Piram[i][3],Piram[i][4]);
    NormalPirams[i][11]=Normal(Piram[i][0],Piram[i][3],Piram[i][4]);
    
	NormalPirams[i][3].x+=NormalPirams[i][2].x;
	NormalPirams[i][3].y+=NormalPirams[i][2].y;
	NormalPirams[i][3].z+=NormalPirams[i][2].z;

	NormalPirams[i][9].x+=NormalPirams[i][2].x;
	NormalPirams[i][9].y+=NormalPirams[i][2].y;
	NormalPirams[i][9].z+=NormalPirams[i][2].z;
}

glEnable(GL_NORMALIZE);
for(i=0;i<PiramCol;i++)
{
 	  glBegin(GL_TRIANGLES);                                           // Начало рисования пирамиды 1

	    glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalPirams[i][0].x, NormalPirams[i][0].y,NormalPirams[i][0].z);
		glVertex3f(Piram[i][0][0], Piram[i][0][1],Piram[i][0][2]);    
		glTexCoord2f(0.0f, ind);
  	    glNormal3f( NormalPirams[i][1].x, NormalPirams[i][1].y,NormalPirams[i][1].z);
 		glVertex3f(Piram[i][1][0], Piram[i][1][1],Piram[i][1][2]);        
		glTexCoord2f(ind,ind);
		glNormal3f( NormalPirams[i][2].x, NormalPirams[i][2].y,NormalPirams[i][2].z);
 	    glVertex3f(Piram[i][4][0], Piram[i][4][1],Piram[i][4][2]);                

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalPirams[i][3].x, NormalPirams[i][3].y,NormalPirams[i][3].z);
        glVertex3f(Piram[i][1][0], Piram[i][1][1],Piram[i][1][2]); 
		glTexCoord2f(ind, ind);
		glNormal3f( NormalPirams[i][4].x, NormalPirams[i][4].y,NormalPirams[i][4].z);
        glVertex3f(Piram[i][2][0], Piram[i][2][1],Piram[i][2][2]);   
		glTexCoord2f(ind, 0.0);
		glNormal3f( NormalPirams[i][5].x, NormalPirams[i][5].y,NormalPirams[i][5].z);
        glVertex3f(Piram[i][4][0], Piram[i][4][1],Piram[i][4][2]);                

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalPirams[i][6].x, NormalPirams[i][6].y,NormalPirams[i][6].z);
        glVertex3f(Piram[i][2][0], Piram[i][2][1],Piram[i][2][2]); 
		glTexCoord2f(ind, ind);
		glNormal3f( NormalPirams[i][7].x, NormalPirams[i][7].y,NormalPirams[i][7].z);
        glVertex3f(Piram[i][3][0], Piram[i][3][1],Piram[i][3][2]); 
		glTexCoord2f(ind, 0.0f);
		glNormal3f( NormalPirams[i][8].x, NormalPirams[i][8].y,NormalPirams[i][8].z);
        glVertex3f(Piram[i][4][0], Piram[i][4][1],Piram[i][4][2]);               
        
		glTexCoord2f(0.0f, 0.0f);
		glNormal3f( NormalPirams[i][9].x, NormalPirams[i][9].y,NormalPirams[i][9].z);
        glVertex3f(Piram[i][0][0], Piram[i][0][1],Piram[i][0][2]);       
		glTexCoord2f(0.0, ind);
		glNormal3f( NormalPirams[i][10].x, NormalPirams[i][10].y,NormalPirams[i][10].z);
        glVertex3f(Piram[i][3][0], Piram[i][3][1],Piram[i][3][2]);     
		glTexCoord2f(ind, ind);
		glNormal3f( NormalPirams[i][11].x, NormalPirams[i][11].y,NormalPirams[i][11].z);
        glVertex3f(Piram[i][4][0], Piram[i][4][1],Piram[i][4][2]);  
  glEnd();     
}
glEndList(); 

 glColor4f(1.0f, 1.0f, 1.0f, 1.0f);                                            // Сбрасываем цвет
 for(i=0;i<PiramCol;i++)
	{
       for(j=0;j<5;j++)
  		 delete[] Piram[i][j];
	   delete[] Piram[i];
	   delete[] NormalPirams[i];
	}
    delete[] NormalPirams;
	delete[] Piram;
}
//*****************************************************************************************************
void CGLObjects::InitModels()
{
	SkyBox(2000,0,2000,8500,570,8500);
	Boxes();
	Piramida();
    Water();
}
//*****************************************************************************************************
