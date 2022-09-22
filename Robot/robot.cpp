
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <corecrt_math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Robot"

int qNo = 1;

float tz = 0, tspeed = 1.0, tx = 0, ty = 0;
bool isOrtho = true;				// Is orthorgraphic View?
float ONear = -5.0, OFar = 10.0; //Ortho near and Far
float PNear = 8.0, PFar = 30.0;		//Perspective Near and Far
float ptx = 0, pty = 0, ptz = 0, ptSpeed = 0.1;   //traslate for projection
float pry = 0, pxy = 0, pzy = 0, prSpeed = 2;		//rotate whole object

//For texture
GLuint texture = 0;			//texture name
BITMAP BMP;					//bitmap structure
HBITMAP hBMP = NULL;		//bitmap handle

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_UP) {
			if (isOrtho) {
				if (tz < OFar)
					tz += tspeed;
			}
			else {
				if (tz < PFar)
					tz += tspeed;
			}

		}
		else if (wParam == VK_DOWN) {
			if (isOrtho) {
				if (tz > ONear)
					tz -= tspeed;
			}
			else {
				if (tz > PNear)
					tz -= tspeed;
			}

		}
		else if (wParam == 'W')
			pty += ptSpeed;
		else if (wParam == 'S')
			pty -= ptSpeed;
		else if (wParam == 'O')
			isOrtho = true;
		else if (wParam == 'P')
			isOrtho = false;
		else if (wParam == 'D')
			ptx += ptSpeed;
		else if (wParam == 'A')
			ptx -= ptSpeed;
		else if (wParam == 'Q')
			ptz += ptSpeed;
		else if (wParam == 'E')
			ptz -= ptSpeed;
		else if (wParam == 'B')
			pry -= prSpeed;
		else if (wParam == 'M')
			pry += prSpeed;
		else if (wParam == 'N')
			pxy -= prSpeed;
		else if (wParam == 'J')
			pxy += prSpeed;
		else if (wParam == 'H')
			pzy -= prSpeed;
		else if (wParam == 'K')
			pzy += prSpeed;
		else if (wParam == 'O')
			isOrtho = true;
		else if (wParam == 'P')
			isOrtho = false, tz = 10;
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------SHAPES and Polygons-------------------------

void DrawSphere(double r) {


	GLUquadricObj* sphere = NULL;
	glPointSize(2);
	sphere = gluNewQuadric();



	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);

}

void drawShape(float downMinX, float downMaxX, float upMinX, float upMaxX, float downMinY, float downMaxY, float upMinY, float upMaxY, float downMinZ, float downMaxZ, float upMinZ, float upMaxZ) {
	//Back
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(upMinX, upMinY, upMinZ);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(downMinX, downMinY, downMinZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(downMaxX, downMaxY, downMinZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(upMaxX, upMaxY, upMinZ);
	glEnd();

	//Bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(downMinX, downMinY, downMinZ);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(downMaxX, downMaxY, downMinZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(downMaxX, downMaxY, downMaxZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(downMinX, downMinY, downMaxZ);
	glEnd();

	//Left
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(upMaxX, upMaxY, upMinZ);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(downMaxX, downMaxY, downMinZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(downMaxX, downMaxY, downMaxZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(upMaxX, upMaxY, upMaxZ);
	glEnd();

	//Top
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(upMaxX, upMaxY, upMinZ);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(upMinX, upMinY, upMinZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(upMinX, upMinY, upMaxZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(upMaxX, upMaxY, upMaxZ);
	glEnd();

	//Right
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(upMinX, upMinY, upMinZ);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(downMinX, downMinY, downMinZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(downMinX, downMinY, downMaxZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(upMinX, upMinY, upMaxZ);
	glEnd();

	//Front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(upMinX, upMinY, upMaxZ);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(downMinX, downMinY, downMaxZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(downMaxX, downMaxY, downMaxZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(upMaxX, upMaxY, upMaxZ);
	glEnd();
}

void drawCube(float length) {
	glBegin(GL_QUADS);
	// Face 1 : Bottom
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(length, 0.0f, length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);


	// Face 2 : Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, length, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, length, length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, length);

	// Face 3 : Front
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, length, length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(length, length, length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(length, 0, length);

	// Face 4 : Right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(length, 0, length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(length, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(length, length, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(length, length, length);

	// Face 5 : Top
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(length, length, length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, length, length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, length, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(length, length, 0);

	// Face 6 : Back
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(length, length, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, length, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(length, 0, 0);
	glEnd();
}

void DrawCylinder(double br, double tr, double h) {


	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, br, tr, h, 10, 10);
	gluDeleteQuadric(cylinder);
}

void drawRectangle(double l, double w, double h) {
	glBegin(GL_QUADS);
	//face 1 down
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(l, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(l, 0, h);

	glTexCoord2f(0, 0);
	glVertex3f(0, 0, h);

	//face 2 face
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, h);

	glTexCoord2f(1, 1);
	glVertex3f(0, w, h);

	glTexCoord2f(1, 0);
	glVertex3f(l, w, h);

	glTexCoord2f(0, 0);
	glVertex3f(l, 0, h);

	//face 3 right
	glTexCoord2f(0, 1);
	glVertex3f(l, 0, h);

	glTexCoord2f(1, 1);
	glVertex3f(l, w, h);

	glTexCoord2f(1, 0);
	glVertex3f(l, w, 0);

	glTexCoord2f(0, 0);
	glVertex3f(l, 0, 0);

	//face 4 face bottom
	glTexCoord2f(0, 1);
	glVertex3f(l, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(0, w, 0);

	glTexCoord2f(0, 0);
	glVertex3f(l, w, 0);

	//face 5 above
	glTexCoord2f(0, 1);
	glVertex3f(l, w, 0);

	glTexCoord2f(1, 1);
	glVertex3f(l, w, h);

	glTexCoord2f(1, 0);
	glVertex3f(0, w, h);

	glTexCoord2f(0, 0);
	glVertex3f(0, w, 0);

	//face 6 left
	glTexCoord2f(0, 1);
	glVertex3f(0, w, 0);

	glTexCoord2f(1, 1);
	glVertex3f(0, w, h);

	glTexCoord2f(1, 0);
	glVertex3f(0, 0, h);

	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glEnd();
}

void DrawPyramid(float sz) {
	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	 // Front
	glTexCoord2f(0.5, 1);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-sz, -sz, sz);
	glTexCoord2f(1, 0);
	glVertex3f(sz, -sz, sz);

	// Right
	glTexCoord2f(0.5, 1);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(sz, -sz, sz);
	glTexCoord2f(1, 0);
	glVertex3f(sz, -sz, -sz);

	// Back
	glTexCoord2f(0.5, 1);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(sz, -sz, -sz);
	glTexCoord2f(1, 0);
	glVertex3f(-sz, -sz, -sz);

	// Left
	glTexCoord2f(0.5, 1);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-sz, -sz, -sz);
	glTexCoord2f(1, 0);
	glVertex3f(-sz, -sz, sz);
	glEnd();   // Done drawing the pyramid

	glBegin(GL_POLYGON);
	//Bottom
	glTexCoord2f(0, 0);
	glVertex3f(-sz, -sz, -sz);
	glTexCoord2f(0, 1);
	glVertex3f(sz, -sz, -sz);
	glTexCoord2f(1, 1);
	glVertex3f(sz, -sz, sz);
	glTexCoord2f(1, 0);
	glVertex3f(-sz, -sz, sz);

	glEnd();
}


//-------------------------------------PROJECTION--------------------------------------------
void projection() {
	glMatrixMode(GL_PROJECTION);  //refer to porjetion matrix
	glLoadIdentity();				// reset to project matrix

	glTranslatef(ptx, pty, ptz);		//translate for projection matrix
	glRotatef(pry, 0.0, 1.0, 0.0);		//rotate y-axis for projection
	glRotatef(pxy, 1.0, 0.0, 0.0);		//rotate x-axis for projection
	glRotatef(pzy, 0.0, 0.0, 1.0);		//rotate x-axis for projection

	if (isOrtho) {
		//Ortho View
		glOrtho(-10.0, 10.0, -10.0, 10.0, ONear, OFar);
	}
	else {
		//Perspective View
	gluPerspective(20, 1.0, -1, 1);
	glFrustum(-10.0, 10.0, -10.0, 10.0, PNear, PFar);
	}

}

//--------------------------------------TEXTURE--------------------------------------------------
GLuint loadTexture(LPCSTR filename) {
	//take from Step 1 
	GLuint texture = 0;			//texture name

	//Step 3 initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4 assign texture to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//take from step 5
	DeleteObject(hBMP);
	return texture;
}


//-----------------------------------Start Draw Robot Function----------------------------------------------------------
void drawWaist() {
	//middle DOWN
	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);	//front
	glVertex3f(1.5, 0, 0);
	glColor3f(1, 0, 0);
	glVertex3f(1.5, -0.25, 1);
	glVertex3f(0, -0.25, 1);

	glColor3f(1, 0, 1); //PINK		left
	glVertex3f(0, -0.25, 1);
	glVertex3f(-0.2, 2,1.5);
	glVertex3f(0, 1.5, 0);
	glVertex3f(0, 0, 0);

	glColor3f(0, 1, 0);	//green			bottom
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1.5, 0);
	glVertex3f(1.5, 1.5, 0);
	glVertex3f(1.5, 0, 0);


	glColor3f(0, 0, 1);		//blue		right
	glVertex3f(1.5, 0, 0);
	glVertex3f(1.5, 1.5, 0);
	glVertex3f(1.7, 2, 1.5);
	glVertex3f(1.5, -0.25, 1);

	glColor3f(1, 1, 1);			//white			above
	glVertex3f(1.5, -0.25, 1);
	glVertex3f(0, -0.25, 1);
	glVertex3f(-0.2, 2, 1.5);
	glVertex3f(1.7, 2, 1.5);

	glColor3f(1, 1, 0);		//yellow		back
	glVertex3f(1.7, 2, 1.5);
	glVertex3f(-0.2, 2, 1.5);
	glColor3f(1, 1, 0);
	glVertex3f(0, 1.5, 0);
	glVertex3f(1.5, 1.5, 0);
	glEnd();
	glPopMatrix();

	//middle UP
	glColor3f(1, 1, 1);	
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(1.5, -0.25, 1);		//bottom
	glVertex3f(0, -0.25, 1);
	glVertex3f(-0.2, 2, 1.5);
	glVertex3f(1.7, 2, 1.5);

	glVertex3f(1.7, 2, 1.5);	//back
	glVertex3f(-0.2, 2, 1.5);
	glColor3f(1, 0, 0);
	glVertex3f(0, 1.5, 3);
	glColor3f(1, 0, 1);
	glVertex3f(1.5, 1.5, 3);

	glColor3f(0, 0, 1);			//above
	glVertex3f(1.5, 1.5, 3);
	glColor3f(0, 0, 0);
	glVertex3f(1.5, -0.5, 3);
	glVertex3f(0, -0.5, 3);
	glColor3f(0, 1, 1);
	glVertex3f(0, 1.5, 3);

	glColor3f(0, 1, 0);		//left
	glVertex3f(0, 1.5, 3);
	glVertex3f(-0.2, 2, 1.5);
	glVertex3f(0, -0.25, 1);
	glVertex3f(0, -0.5, 3);

	glColor3f(1, 0.5, 0);			//front
	glVertex3f(0, -0.5, 3);
	glVertex3f(0, -0.25, 1);
	glVertex3f(1.5, -0.25, 1);
	glVertex3f(1.5, -0.5, 3);


	glColor3f(1, 0, 0);			//right
	glVertex3f(1.5, -0.5, 3);
	glVertex3f(1.5, -0.25, 1);
	glVertex3f(1.7, 2, 1.5);
	glVertex3f(1.5, 1.5, 3);

	glEnd();
	glPopMatrix();


	//LEFT Bottom
	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);				//front
	glVertex3f(-3, -0.17, 1);
	glVertex3f(-3, -0.17, 2);
	glVertex3f(0, -0.17, 0.7);

	glColor3f(1, 0, 1);				//above
	glVertex3f(0, -0.17, 0.7);
	glVertex3f(-0.2, 2, 1.3);
	glVertex3f(-2.5, 2, 1.35);
	glColor3f(1, 0, 0);
	glVertex3f(-3, -0.17, 2);

	glColor3f(0, 0, 1);				//left 
	glVertex3f(-3, -0.17, 2);
	glVertex3f(-3, -0.17, 1);
	glVertex3f(-2.5, 2, 0.35);
	glColor3f(1, 1, 1);
	glVertex3f(-2.5, 2, 1.35);

	glColor3f(0, 1,0);		//BEHIND
	glVertex3f(-2.5, 2, 1.35);
	glVertex3f(-0.2, 2, 1.3);
	glVertex3f(0, 1.5, 0);
	glVertex3f(-2.5, 2, 0.35);

	glColor3f(0, 0, 0);			//BELOW
	glVertex3f(-2.5, 2, 0.35);
	glVertex3f(-3, -0.17,1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1.5, 0);
	glEnd();
	glPopMatrix();

	//RIGHT Bottom
	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(1.5, 0, 0);				//front
	glVertex3f(4.5, -0.17, 1);
	glVertex3f(4.5, -0.17, 2);
	glVertex3f(1.5, -0.17, 0.7);

	glColor3f(1, 0, 1);				//above
	glVertex3f(1.5, -0.17, 0.7);
	glVertex3f(1.7, 2, 1.3);
	glVertex3f(4, 2, 1.35);
	glColor3f(1, 0, 0);
	glVertex3f(4.5, -0.17, 2);

	glColor3f(0, 0, 1);				//right 
	glVertex3f(4.5, -0.17, 2);
	glVertex3f(4.5, -0.17, 1);
	glVertex3f(4, 2, 0.35);
	glColor3f(1, 1, 1);
	glVertex3f(4, 2, 1.35);

	
	glColor3f(0, 1, 0);		//BEHIND
	glVertex3f(4, 2, 1.35);
	glVertex3f(1.7, 2, 1.3);
	glVertex3f(1.5, 1.5, 0);
	glVertex3f(4, 2, 0.35);

	glColor3f(0, 0, 0);			//BELOW
	glVertex3f(4, 2, 0.35);
	glVertex3f(4.5, -0.17, 1);
	glVertex3f(1.5, 0, 0);
	glVertex3f(1.5, 1.5, 0);
	glEnd();
	glPopMatrix();

	//Left Top
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 1);

	glVertex3f(0, -0.17, 0.7);		//front 
	glVertex3f(0, -0.5, 3);
	glVertex3f(-3, -0.5, 4);
	glVertex3f(-3, -0.17, 2);

	glColor3f(1, 1, 1);
	glVertex3f(-3, -0.17, 2);		//left
	glVertex3f(-3, -0.5, 4);
	glVertex3f(-2.1, 1.6, 2.6);
	glVertex3f(-2.5, 2, 1.35);

	glColor3f(0, 0, 0);			//behind
	glVertex3f(-2.5, 2, 1.35);
	glVertex3f(-0.2, 2, 1.3);
	glVertex3f(0, 1.5, 2.6);
	glVertex3f(-2.1, 1.6, 2.6);

	glVertex3f(-2.1, 1.6, 2.6);		//Above
	glVertex3f(-3, -0.5, 4);
	glVertex3f(0, -0.5, 3);
	glColor3f(1, 1, 1);
	glVertex3f(0, 1.5, 2.6);
	
	
	glVertex3f(0, 1.5, 2.6);		//right
	glColor3f(0, 0, 0);
	glVertex3f(0, -0.17, 0.7);
	glColor3f(1, 0, 0);
	glVertex3f(0, -0.5, 3);
	glEnd();
	glPopMatrix();

	//Right Top

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 1);

	glVertex3f(1.5, -0.17, 0.7);		//front 
	glVertex3f(1.5, -0.5, 3);
	glVertex3f(4.5, -0.5, 4);
	glVertex3f(4.5, -0.17, 2);

	glColor3f(1, 1, 1);
	glVertex3f(4.5, -0.17, 2);		//left
	glVertex3f(4.5, -0.5, 4);
	glVertex3f(3.6, 1.6, 2.6);
	glVertex3f(4, 2, 1.35);

	glColor3f(0, 0, 0);			//behind
	glVertex3f(4, 2, 1.35);
	glVertex3f(1.7, 2, 1.3);
	glVertex3f(1.5, 1.5, 2.6);
	glVertex3f(3.6, 1.6, 2.6);

	glVertex3f(3.6, 1.6, 2.6);		//Above
	glVertex3f(4.5, -0.5, 4);
	glVertex3f(1.5, -0.5, 3);
	glColor3f(2.5, 1, 1);
	glVertex3f(1.5, 1.5, 2.6);


	glVertex3f(1.5, 1.5, 2.6);		//right
	glColor3f(0, 0, 0);
	glVertex3f(1.5, -0.17, 0.7);
	glColor3f(1, 0, 0);
	glVertex3f(1.5, -0.5, 3);
	glEnd();
	glPopMatrix();


}

void drawBody(GLuint* bodytextureArr) {
	bodytextureArr[0] = loadTexture("blackMetal.bmp");
	glColor3f(1, 1, 1);
	//------------------------------------middle bottom Behind
	glPushMatrix();		
	glTranslatef(0, -1.5, -7);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, 0, 4);		//front view (FROM behind)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.4,-0.2,2.8);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.9, -0.2, 2.8);

	//left view (FROM BEHIND)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.9, -0.2, 2.8);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, 0, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.9, 1, 2.8);

	glTexCoord2f(0.0f, 0.0f);			//above (FROM BEHIND)
	glVertex3f(1.9, 1, 2.8);		
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.9, -0.2, 2.8);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.4, -0.2, 2.8);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.4, 1, 2.8);

	glTexCoord2f(0.0f, 0.0f);			//back view (FROM BEHIND)
	glVertex3f(-0.4, 1, 2.8);		
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.9, 1, 2.8);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1, 4);
	
					//Right view (FROM BEHIND)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 1, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.4, 1, 2.8);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.4, -0.2, 2.8);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, 4);

	glTexCoord2f(0.0f, 0.0f);		//bottom view (FROM BEHIND)
	glVertex3f(0, 0, 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 1, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 1, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 0, 4);

	glEnd();
	glPopMatrix();

	//------------------------------middle bottom up 1
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.4, -1.69, -6.2);
	drawRectangle(2.3, 1, 2);
	glPopMatrix();
	glDeleteTextures(1, &bodytextureArr[0]);




	//--------------------------------------FRONT ------------------------------------------------
	//LEFT SIDE
	glPushMatrix();
	glRotatef(180, 1, 0, 0);		//back
	glBegin(GL_QUADS);
	glVertex3f(0, 1.5, 2.6);		
	glVertex3f(-2, 1.6, 2.6);
	glVertex3f(-1.8, 1.6, 10);
	glVertex3f(0, 1.5, 10);

	glVertex3f(0, 1.5, 10);			//above
	glVertex3f(0, -0.2, 10);
	glVertex3f(-1.8, -0.2, 10);
	glVertex3f(-1.8, 1.6, 10);

	glVertex3f(-1.8, 1.6, 10);		//left	(outside)
	glVertex3f(-1.8, 1.6, 2.6);
	glVertex3f(-2, -0.2, 2.6);
	glVertex3f(-1.8, -0.2, 10);

	glVertex3f(-1.8, -0.2, 10);		//front
	glVertex3f(-2, -0.2, 2.6);
	glVertex3f(0, -0.2, 2.6);
	glVertex3f(0, -0.2, 10);
	
	glColor3f(0, 0, 0);
	glVertex3f(0, -0.2, 10);		//right (inside)
	glVertex3f(0, -0.2, 2.6);
	glVertex3f(0, 1.5, 2.6);
	glVertex3f(0, 1.5, 10);
	glEnd();
	glPopMatrix();

}

void display() {
	glClearColor(0.313725, 0.513725, 0.721568, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear screen
	glEnable(GL_DEPTH_TEST);
	projection();

	glMatrixMode(GL_MODELVIEW);		//refer to modelview Matrix

	GLuint bodytextureArr[20];		//initialize texture

	glLoadIdentity();		//reset to modelview matrix
	glTranslatef(tx, ty, tz);		//tranlate along the z-axis




	//--------------------START OF DESIGN-----------------------------------------------------


	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	drawWaist();
	drawBody(bodytextureArr);
	glPopMatrix();

	//-----------------------------END OF DESIGN----------------------------------------------------------------

	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}


//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 900, 700,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));





	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------