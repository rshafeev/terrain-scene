#include "Terrain.H"
#include <stdio.h>
Terrain::Terrain()
{
	MapSize=128;
	TextureBit = 1.0f/128;

	Zoom = 16;								// Коэффициент увиличения
	CameraX = (MapSize/2)*Zoom;				// Положение точки наблюдателя
	CameraY = (MapSize/2)*Zoom;
	CameraZ = -300.0;
	VertAngle = 90.0;
	HorizAngle = 0.0;
};

Terrain::~Terrain()
{	
};

void Terrain::LoadRawFile(const char *FileName, int nSize, BYTE *pHeightMap)
{
	FILE *pFile = NULL;
	pFile = fopen( FileName, "rb" );

	
	if ( pFile == NULL )	
	{
//		MessageBox(NULL, "Can't find the Height Map data file", "Error", MB_OK);
		return;
	}
	fread( pHeightMap, 1, nSize, pFile );
	fclose(pFile);
}


void Terrain::Init()
{
	int i,j;

	glViewport(0,0,GetSystemMetrics( SM_CXSCREEN ),GetSystemMetrics( SM_CYSCREEN ));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,1,1,2048); 
	glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	Width = GetSystemMetrics( SM_CXSCREEN );	// Ролучаем размеры экрана
	Height = GetSystemMetrics( SM_CYSCREEN );
	// Читаем карту высот
	LoadRawFile("res\\terrain.Raw", MapSize *MapSize, &HeightMap[0][0]);
	// Создаем текстуру
	Texture *LandscapeTexture = new Texture;
	LandscapeTexture->Load("RES\\grass.tga",&TextureId);
	// Удаляем объект класса Textures - текстуру уже создали и он нам больше не нужен
	delete LandscapeTexture;

	// Инициализация массивов
	glEnableClientState(GL_VERTEX_ARRAY);			// Массив вершины
	glVertexPointer (3, GL_FLOAT, 0, VertexMap);
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	// Массив координат текстур
	glTexCoordPointer(2, GL_FLOAT, 0, TextureMap);

	for (int Row=0;Row<MapSize*2;Row++)			// Заполняем массив индексов 
	{
		Indices[Row] = Row;
	}
}

void Terrain::RenderLandscape()
{
	HandleControls();							// Обрабатываем управление
    float piramidaSize[4];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.25f, .25f, .75f, .25f);
	glPushMatrix();

	glRotated( -VertAngle, 1.0, 0.0, 0.0);
	glRotated( HorizAngle, 0.0, 0.0, 1.0);
	glTranslatef(-CameraX,-CameraY,CameraZ);

	int x,y,i,j;
	int Index=0;
	//!!
  piramidaSize[0]=350;
  glBegin(GL_LINE_LOOP);                          // Начало рисования пирамиды
       // glColor3f(5.0f,0.0f,0.0f);                      // Красный
       
        glVertex3f( 0.0f, piramidaSize[0], 0.0f);                  // Верх треугольника (Передняя)
        glVertex3f(-piramidaSize[0],-1.0f,piramidaSize[0]);                  // Левая точка
        glVertex3f( piramidaSize[0],-1.0f, piramidaSize[0]);                  // Правая точка
        glVertex3f( 0.0f, piramidaSize[0], 0.0f);                  // Верх треугольника (Правая)
        glVertex3f( piramidaSize[0],-1.0f, piramidaSize[0]);                  // Лево треугольника (Правая)
        glVertex3f( piramidaSize[0],-1.0f, -piramidaSize[0]);                 // Право треугольника (Правая)
        glVertex3f( 0.0f, piramidaSize[0], 0.0f);                  // Низ треугольника (Сзади)
        glVertex3f( piramidaSize[0],-1.0f, -piramidaSize[0]);                 // Лево треугольника (Сзади)
        glVertex3f(-piramidaSize[0],-1.0f, -piramidaSize[0]);                 // Право треугольника (Сзади)
        glVertex3f( 0.0f, piramidaSize[0], 0.0f);                  // Верх треугольника (Лево)
        glVertex3f(-piramidaSize[0],-1.0f,-piramidaSize[0]);                  // Лево треугольника (Лево)
        glVertex3f(-piramidaSize[0],-1.0f, piramidaSize[0]);                  // Право треугольника (Лево)
  glEnd();                                                // Кончили рисовать пирамиду

	//!!	 
	// Рисуем ландшафт
	for (i=0;i<MapSize-1;i++)
	{
		Index=0;
		for (j=0;j<MapSize-1;j++)
		{	
			x=j*Zoom;
			y=i*Zoom;

			TextureMap[Index+0][0]=j*TextureBit;		// Рассчитывем координаты текстур
			TextureMap[Index+0][1]=i*TextureBit;
			TextureMap[Index+1][0]=j*TextureBit;
			TextureMap[Index+1][1]=(i+1)*TextureBit;

			VertexMap[Index+0][2] =	HeightMap[j][i];			// Высота, значенеи из карты высот
			VertexMap[Index+1][2] =	HeightMap[j][i+1];
			
			VertexMap[Index+0][0] = x;				// Вершины
			VertexMap[Index+0][1] = y;
			VertexMap[Index+1][0] = x;
			VertexMap[Index+1][1] = y+Zoom;


			Index+=2;					// Увеличиваем колличество "подготовленных" вершин и т.п.
		}
		// Рисуем кучу примитивов одним вызовом
		glDrawElements(GL_TRIANGLE_STRIP, Index, GL_UNSIGNED_INT, Indices);
	}
	
	glPopMatrix();
}

void Terrain::HandleControls()
{
	float PI = 3.1415;
	static long xCurPosOld, yCurPosOld;

	POINT Point;
	GetCursorPos(&Point);

	float Speed=20.0f;
	
	VertAngle+= (yCurPosOld-Point.y)*0.05f;
	HorizAngle -= (xCurPosOld-Point.x)*0.05f;

	if(VertAngle< 0.0) VertAngle= 0.0;
	else
	if(VertAngle> 180.0) VertAngle= 180.0;
	else
	if(HorizAngle< 0.0) HorizAngle = 359.0;
	else
	if(HorizAngle> 359.0) HorizAngle = 0.0;

	if( GetAsyncKeyState(VK_HOME) < 0)
	{	
	CameraZ-=2;
	}
	
	if( GetAsyncKeyState(VK_END) < 0)
	{	
	CameraZ+=2;
	}
	if( GetAsyncKeyState(VK_UP) < 0 || GetAsyncKeyState(VK_LBUTTON) < 0 )
	{	
		CameraX += Speed*sin(HorizAngle/180*PI);
		CameraY += Speed*cos(HorizAngle/180*PI);
	}
	
	if( GetAsyncKeyState(VK_DOWN) < 0 || GetAsyncKeyState(VK_RBUTTON) < 0 )
	{	
		CameraX -= Speed*sin(HorizAngle/180*PI);
		CameraY -= Speed*cos(HorizAngle/180*PI);
	}
	if( GetAsyncKeyState(VK_RIGHT) < 0 )
	{	
		CameraX += Speed*sin((HorizAngle+90)/180*PI);
		CameraY += Speed*cos((HorizAngle+90)/180*PI);
	}
	if( GetAsyncKeyState(VK_LEFT) < 0 )
	{
		CameraX += Speed*sin((HorizAngle-90)/180*PI);
		CameraY += Speed*cos((HorizAngle-90)/180*PI);
	}

	if(Point.x==Width-1)
	{	Point.x = 1;
		SetCursorPos(Point.x,Point.y);
	}
	if(Point.y==Height-1)
	{	Point.y = 1;
		SetCursorPos(Point.x,Point.y);
	}
	if(Point.x==0)
	{	Point.x = Width;
		SetCursorPos(Point.x,Point.y);
	}
	if(Point.y==0)
	{	Point.y = Height;
		SetCursorPos(Point.x,Point.y);
	}

   	xCurPosOld = Point.x;
	yCurPosOld = Point.y;		
}

