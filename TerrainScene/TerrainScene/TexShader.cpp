#include "TexShader.h"

//#pragma comment(lib, "glaux.lib")


#include <stdio.h>
#include <iostream>
#include <string.h>
#include <windows.h>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glut32.lib")
//**************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//**********************************************

CTexShader *TexShader;

CTexShader::CTexShader(void)
{
	

}

CTexShader::~CTexShader(void)
{
}
//*********************************************************************************************
char* CTexShader::textFileRead(char *fn)
{
	FILE *fp;
	char *content = NULL;
 
	int count=0;
 
	if (fn != NULL) {
		fp = fopen(fn,"rt");
 
		if (fp != NULL) {
      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
	  content=new char[count+3];
      rewind(fp);
      fclose(fp);
	  fp = fopen(fn,"rt");
			if (count > 0) {
				count = fread(content,sizeof(char),count-1,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}
 //*********************************************************************************************
int CTexShader::textFileWrite(char *fn, char *s) 
{
	FILE *fp;
	int status = 0;
 
	if (fn != NULL) {
		fp = fopen(fn,"w");
 
		if (fp != NULL) {
			
			if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
}
//*********************************************************************************************
void CTexShader::setShaders(char * fileV,char *fileF,GLuint *pr)
{
	char *vs = NULL,*fs = NULL,*fs2 = NULL;
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
//	v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
//	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	
	vs = textFileRead(fileV);
	fs = textFileRead(fileF);
	// Копируем код шейдеров
	const char * vv = vs;
	const char * ff = fs;

	// Передаём шейдерам их исходный код
	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);
 
	// Освобождаем память под ненужные теперь массивы
	free(vs);free(fs);
 
	// Компилируем шейдеры
	glCompileShader(v);
	glCompileShader(f);
 
	// Создаём программу
	*pr = glCreateProgram();
	// Присоединяем к программе шейдеры
	glAttachShader(*pr,v);
	glAttachShader(*pr,f);
 
	// Линкуем программу
	glLinkProgram(*pr);
 
}
//*********************************************************************************************
void CTexShader::Init()
{
	glewInit();
 	// Устанавливаем шейдеры
	setShaders("RES\\Shaders\\Land.vert","RES\\Shaders\\Land.frag",&TexShadPr);
	setShaders("RES\\Shaders\\light.vert","RES\\Shaders\\light.frag",&LightShadPr);
	setShaders("RES\\Shaders\\Water.vert","RES\\Shaders\\Water.frag",&WaterShadPr);
}
//*********************************************************************************************