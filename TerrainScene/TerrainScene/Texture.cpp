#include "Texture.h"
#include "atlstr.h"
#include "TexShader.h"
CTexture *Texture;

CTexture::CTexture(void)
{
}

CTexture::~CTexture(void)
{
}
GLvoid CTexture::LoadGLTextures(GLuint *TexInd,LPCSTR fileName)
{
AUX_RGBImageRec *texture1;                                             // Загрузка картинки

	texture1=auxDIBImageLoadA(fileName);

   glGenTextures(1,TexInd);                                  // Создание текстуры
  
     glBindTexture(GL_TEXTURE_2D, *TexInd);	
	 gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture1->sizeX, texture1->sizeY,
                       GL_RGB, GL_UNSIGNED_BYTE, texture1->data); 
	
	 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); 
	 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_FILTER_CONTROL,GL_CLAMP_TO_BORDER); 
//	 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT); 
     

   texture1=NULL;
}
void CTexture::InitTexture()
{
  /////**shader
		                                            // Загрузка текстуры пирамид
  LoadGLTextures(&texture[0],"RES\\textureL0.bmp"); 
  LoadGLTextures(&texture[1],"RES\\textureL1.bmp");	
  LoadGLTextures(&texture[2],"RES\\textureL2.bmp");

  LoadGLTextures(&texture[4],"RES\\texturePiram.bmp");
  LoadGLTextures(&texture[5],"RES\\texVec.bmp");
  LoadGLTextures(&texSky[0],"RES\\textureSKY1.bmp");
  LoadGLTextures(&texBoxes,"RES\\textureBox.bmp");
  LoadGLTextures(&texWater[0],"RES\\textureWater1.bmp");
  LoadGLTextures(&texWater[1],"RES\\textureWater2.bmp");
}