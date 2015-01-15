#pragma once

#include "Includes.h"
#include "Scene.h"
class CLandshaft
{
private:
	TPoint Normal(TPoint p1,TPoint p2,TPoint p3);
	void GenNormal(TPoint *g_NormalMap,int MAP_SIZE,int STEP_SIZE);
	void GenBedNormal(TPoint *g_NormalMap,int MAP_SIZE,int STEP_SIZE);
	int* LoadRawFile(LPSTR strName, int nSize);
	void SetVertexColor(int height);
	void RenderHeightMap(int *pHeightMap,TPoint g_NormalMap[],int MAP_SIZE,
		int STEP_SIZE,int texture,TPoint sdvig,int indexSpisok);
public:
	CLandshaft(void);
	~CLandshaft(void);
	
	int *g_HeightMap;                                          // �������� ����� ������
	int STEP_SIZE;                                            // ������ � ������ ������� ��������
	int LAND_SIZE;// ������ ����� ������
	int InitLanshaft();
};
extern CLandshaft *Landshaft;