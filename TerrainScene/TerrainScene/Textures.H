#ifndef __TEXTURES_H
#define __TEXTURES_H
#include "Includes.H"
// ����� ��� ������ � Targa �������
class Texture
{
protected:
	GLubyte *ImmageData;
	GLubyte	Header[6];
	// ����������� ���� �� ���� ����� �����������, ��� �� ������������ ��� ����������� 
	// �������� ���������� ��� ��������� �������� ������ � �����-��������
	GLuint	BytesPerPixel;
	GLuint Width,Height;


public:
	Texture()  {};
	~Texture() {};

	bool Load(char *FileName, GLuint *ID);
};


#endif