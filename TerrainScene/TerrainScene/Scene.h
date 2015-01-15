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
    float	walkbiasangle;                                      // угол походки	
	float   walkbias;                                           // перемещение походки
} Camera,CameraAuto;
struct TObjects
{
  GLuint  land[2];                                                 // Память для списка ландшафта
  GLuint  piramids;                                             // Память для списка пирамид
  GLuint  skyBox;
  GLuint  Boxes;
  GLuint  Water;
} Object ;

    void HandleControls();                                      // поворот камеры от нажатия клавиш
	void Init();                                                // начальные действия постройки сцены
	int DrawGLScene( GLvoid );                                  // Здесь  происходит вся прорисовка сцены
	GLvoid ReSizeGLScene( GLsizei width, GLsizei height );      // Изменить размер и инициализировать окно GL 
	bool MoveNext(int type);     
	bool autoOblet;
	// Можно ли передвинуться игроку в выбранном направлении
	CScene(void);
	~CScene(void);
};
extern CScene *sceene;