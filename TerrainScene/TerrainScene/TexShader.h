#pragma once
#include "Includes.h"
class CTexShader
{
public:
	CTexShader(void);
	~CTexShader(void);
 char* textFileRead(char *fn);
 int   textFileWrite(char *fn, char *s);
 void  setShaders(char * fileV,char *fileF,GLuint *pr);
 void  Init();
  
 GLuint v,f,TexShadPr,LightShadPr,WaterShadPr;		// Дескрипторы программ и шейдеров


  
};
extern CTexShader *TexShader;