#pragma once
#include "includes.h"          
class CTexture
{

public:
	CTexture(void);
	~CTexture(void);

GLvoid LoadGLTextures(GLuint *TexInd,LPCSTR fileName);
  GLuint	texture[7];		// Место для одной текстуры
  GLuint	texSky[2];	
  GLuint    texBoxes;
  GLuint    texWater[2];
  
  void InitTexture();
};
extern CTexture *Texture;