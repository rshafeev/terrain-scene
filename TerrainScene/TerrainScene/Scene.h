#pragma once
#include "Includes.H"

class CScene 
{
private:
public:
 
struct TCamera
{
    float	PosX;
	float	PosY;
	float	PosZ;
	float	Angle_X;
	float	Angle_Y;	
    float	walkbiasangle;                                      // ���� �������	
	float   walkbias;                                           // ����������� �������
} Camera,CameraAuto;
struct TObjects
{
  GLuint  land[2];                                                 // ������ ��� ������ ���������
  GLuint  piramids;                                             // ������ ��� ������ �������
  GLuint  skyBox;
  GLuint  Boxes;
  GLuint  Water;
} Object ;

    void HandleControls();                                      // ������� ������ �� ������� ������
	void Init();                                                // ��������� �������� ��������� �����
	int DrawGLScene( GLvoid );                                  // �����  ���������� ��� ���������� �����
	GLvoid ReSizeGLScene( GLsizei width, GLsizei height );      // �������� ������ � ���������������� ���� GL 
	bool MoveNext(int type);     
	bool autoOblet;
	// ����� �� ������������� ������ � ��������� �����������
	CScene(void);
	~CScene(void);
};
extern CScene *sceene;