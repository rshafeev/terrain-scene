#include "Includes.H"
#include "Textures.H"
class Terrain
{
protected:
	
	int  MapSize;						// ������ �����
	GLfloat TextureBit;
     GLfloat	VertexMap[128 * 2][3]; 
     GLfloat	TextureMap[128 * 2][2];
     GLuint	Indices[128 * 2];
	unsigned char HeightMap[128][128];		// ����� �����


	int Zoom;										// ����������� ����������
	float VertAngle, HorizAngle;					// ������������ � �������������� ���� ������
	float CameraX,CameraY,CameraZ;					// ������� ��������� ����� �����������

	GLuint TextureId;								// ������������� ��������
	
	// ������ � ������ ������ � ��������, ���������� ��� ��������� ����������
	int Width, Height;
public:

	Terrain();
	~Terrain();

	void Init();
	void LoadRawFile(const char *FileName, int nSize, BYTE *pHeightMap);
	void RenderLandscape();							// ����� � ���������� ��������� ���������

	void HandleControls();							// ��������� ����������
};
