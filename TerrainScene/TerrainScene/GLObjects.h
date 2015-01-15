#pragma once
#include "includes.h"
//////////////////////////////
class CGLObjects
{
private:
	int PiramCol;
	char* StrCopy(char *str,int index,int col); //�������� �� ������ str
	char* StrDelete(char *str,int index,int col);//������� �� ������
	TPoint Normal(float *p1,float *p2,float *p3);// ������� � ���������

	void SkyBox(float x, float y, float z, float width, float height, float length);
	void Piramida();// ������ ��������
	void Boxes();
	float volna[2];
public:
	int LoadObjectFromFile(char *FileName,float**** object);// �������� ��������� � �����
	void InitModels();// ��������� ������ ��������(�������� � �.�.) � ������ 
	void Water();
	CGLObjects(void);
	~CGLObjects(void);
};
extern CGLObjects *GLObjects;