#pragma once
#include "includes.h"
//////////////////////////////
class CGLObjects
{
private:
	int PiramCol;
	char* StrCopy(char *str,int index,int col); //копирует из строки str
	char* StrDelete(char *str,int index,int col);//удаляет из строки
	TPoint Normal(float *p1,float *p2,float *p3);// нормаль к плоскости

	void SkyBox(float x, float y, float z, float width, float height, float length);
	void Piramida();// рисует пирамиды
	void Boxes();
	float volna[2];
public:
	int LoadObjectFromFile(char *FileName,float**** object);// загрузка координат с файла
	void InitModels();// загружает списки объектов(пирамиды и т.д.) в память 
	void Water();
	CGLObjects(void);
	~CGLObjects(void);
};
extern CGLObjects *GLObjects;