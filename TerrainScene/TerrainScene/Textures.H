#ifndef __TEXTURES_H
#define __TEXTURES_H
#include "Includes.H"
// Класс для работы с Targa файлами
class Texture
{
protected:
	GLubyte *ImmageData;
	GLubyte	Header[6];
	// Колличество байт на одну точку изображения, так же используется как колличество 
	// цветовых плоскостей при генерации текстуры бычной и альфа-текстуры
	GLuint	BytesPerPixel;
	GLuint Width,Height;


public:
	Texture()  {};
	~Texture() {};

	bool Load(char *FileName, GLuint *ID);
};


#endif