#include "Includes.H"
#include "Textures.H"
class Terrain
{
protected:
	
	int  MapSize;						// Размер карты
	GLfloat TextureBit;
     GLfloat	VertexMap[128 * 2][3]; 
     GLfloat	TextureMap[128 * 2][2];
     GLuint	Indices[128 * 2];
	unsigned char HeightMap[128][128];		// Карта высот


	int Zoom;										// Коэффициент увиличения
	float VertAngle, HorizAngle;					// Вертикальный и горизонтальный угол обзора
	float CameraX,CameraY,CameraZ;					// Текущее положение точки наблюдателя

	GLuint TextureId;								// Идентификатор текстуры
	
	// Ширина и высота экрана в пикселах, необходима для процедуры управления
	int Width, Height;
public:

	Terrain();
	~Terrain();

	void Init();
	void LoadRawFile(const char *FileName, int nSize, BYTE *pHeightMap);
	void RenderLandscape();							// Здесь и происходит рисование ландшафта

	void HandleControls();							// Обработка управления
};
