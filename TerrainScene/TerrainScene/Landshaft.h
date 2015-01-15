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
	
	int *g_HeightMap;                                          // Содержит карту вершин
	int STEP_SIZE;                                            // Ширина и высота каждого квадрата
	int LAND_SIZE;// Размер карты вершин
	int InitLanshaft();
};
extern CLandshaft *Landshaft;