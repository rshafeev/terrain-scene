//#include <FStream.H>
#include "Textures.H"

bool Texture::Load(char *FileName,GLuint *ID)
{
	GLubyte	TargaMagic[12] = {0,0,2,0,0,0,0,0,0,0,0,0};
	GLubyte	FileMagic[12];
	GLuint	ImageSize;
	GLuint	Temp;

	FILE *File = fopen(FileName, "rb");
	
    if (File == NULL) 
	{
		return false;
	}

    if(fread(FileMagic, 1, sizeof(FileMagic), File)      != sizeof(FileMagic) ||
       memcmp(TargaMagic, FileMagic, sizeof(TargaMagic)) != 0                 ||
       fread(Header, 1, sizeof(Header), File)            != sizeof(Header))
		{
			fclose(File);
			return false;
		}

	// Определяем размеры изображения
	Width  = Header[1] * 256 + Header[0];
    Height = Header[3] * 256 + Header[2];

	// Определяем глубину цвета используемую в изображении
    if(Width<=0||Height<=0||(Header[4]!=24&&Header[4]!=32))
    {
		fclose(File);
		return false;
    }

	BytesPerPixel = Header[4] / 8;
    ImageSize = Width * Height * BytesPerPixel;
	
	// Выделяем память
    ImmageData = (GLubyte *)malloc(ImageSize);
	// Читаем данные
	if(ImmageData==NULL||(int)fread(ImmageData, 1, ImageSize, File)!=ImageSize)
    {
		if(ImmageData!=NULL) free(ImmageData);
		fclose(File);
		return false;
    } 

    for(GLuint Index=0; Index<ImageSize; Index+=BytesPerPixel)
    {
          Temp=ImmageData[Index];
          ImmageData[Index]=ImmageData[Index + 2];
          ImmageData[Index+2]= Temp;
    }

	// Выполняем фильтрацию текстуры
	
	glGenTextures(1, ID);
	glBindTexture(GL_TEXTURE_2D, *ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D,0,BytesPerPixel,Width,Height,0,(BytesPerPixel==3)?GL_RGB:GL_RGBA,GL_UNSIGNED_BYTE,ImmageData);

	// Закрываем файл
	fclose (File);
	free (ImmageData);
	return true;
}
