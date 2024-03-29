
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <corecrt_math.h>


#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Robot"

int qNo = 1;

float up = 0, down = 0, tspeedd = 1;
float le = 0, ri = 0;
float tz = 0, tspeed = 1.0, tx = 0, ty = 0;
bool isOrtho = true;				// Is orthorgraphic View?
float ONear = -15.0, OFar = 15.0; //Ortho near and Far
float PNear = 20.0, PFar = 30.0;		//Perspective Near and Far
float ptx = 0, pty = 0, ptz = 0, ptSpeed = 1;   //traslate for projection
float pry = 0, pxy = 0, pzy = 0, prSpeed = 3;		//rotate whole object
LPCSTR texture1 = "darkblueMetal.bmp";
LPCSTR texture2 = "blackMetal.bmp";
LPCSTR texture3 = "redMetal.bmp";
LPCSTR texture4 = "lightblueMetal.bmp";
LPCSTR texture5 = "red.bmp";
LPCSTR texture6 = "whiteblueMark.bmp";

float skysize = 100;

//Fanspeeed (CHEST)
float fanspeed = 5, fanrotate = 0;

//SmokeSpeed (JETPACK)
float smokespeed = 0, smokedrop = -16;

//GunSpeed (GUN)
float gunspeed = 0, bulletpos1 = -4, bulletpos2 = -4;

//ROCKET
float Fly = 0, FlySpeed = 0, rocketpos1 = 6;

//For texture
GLuint texture = 0;			//texture name
BITMAP BMP;					//bitmap structure
HBITMAP hBMP = NULL;		//bitmap handle



//Lighting
float a = 0, b = 20, c = 0;
float angle = 0;
float amb[3] = { 1, 1, 1 }; // Ambient Light
float posB[3] = { a,b,c };		//position for lighting{6,0,0}
float dif[3] = { 1.0,1.0,1.0 };			// color dif light 
float MBlue[3] = { 0.0,0.0,1.0 };		// blue material
float MRed[3] = { 1.0,0.0,0.0 };		// red material
float MYellow[3] = { 1.0, 1.0, 0.0 };	//yellow material
float MWhite[3] = { 1.0, 1.0, 0.0 };	//white material
bool isLightOn = false;
bool isDiffuse = true;
bool lightcheck = true;

float headAngle = 0;
boolean headTurnRight, headTurnLeft;

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
		else if (wParam == VK_LEFT) {
			if (isOrtho) {
			}
			else {
				tz -= tspeed;

			}
		}
		else if (wParam == 'W')
		{
			if (pty <= 30) {
				pty += ptSpeed;
			}
		}
		else if (wParam == 'S')
		{
			if (pty >= -20) {
				pty -= ptSpeed;
			}
		}
			
		else if (wParam == 'O')
			isOrtho = true;
		else if (wParam == 'P')
			isOrtho = false, skysize = 100;
		else if (wParam == 'D')
					{
			if (ptx <= 20) {
				ptx += ptSpeed;
			}
		}	
		else if (wParam == 'A')
		{
			if (ptx >= -20) {
				ptx -= ptSpeed;
			}
		}
		else if (wParam == 'Q')
			pry -= prSpeed;
		else if (wParam == 'E')
			pry += prSpeed;
		else if (wParam == 'Z')
			fanspeed += 10;
		else if (wParam == 'X')
			fanspeed -= 10;

		else if (wParam == 'G')
			up += tspeedd;
		else if (wParam == 'V')
			up -= tspeedd;
		else if (wParam == '5')
			down += tspeedd;
		else if (wParam == 'T')
			down -= tspeedd;
		else if (wParam == 'Y')
			le += tspeedd;
		else if (wParam == 'U')
			le -= tspeedd;
		else if (wParam == '6')
			ri += tspeedd;
		else if (wParam == '7')
			ri -= tspeedd;
		else if (wParam == '0')
		{
			if (gunspeed >= 0.9) {
				gunspeed = 0, bulletpos1 = -4;
			}
			else {
				gunspeed = 1.3;
			}
		}
		else if (wParam == '9')
		{
			if (FlySpeed >= 0.9) {
				FlySpeed = 0, Fly = 0, rocketpos1 = 6;
			}
			else {
				FlySpeed = 2;
			}
		}
		else if (wParam == 'C')
		{
			if (smokespeed >= 0.2)
			{
				smokespeed = 0, smokedrop = -16;
			}
			else {
				smokespeed = 0.2;
			}
		}
		else if (wParam == 'L')
		{
			if (isLightOn) {
				isLightOn = false;
			}
			else {
				isLightOn = true;
			}
		}
		else if (wParam == 'I')
			if (isDiffuse) {
				isDiffuse = false;
			}
			else {
				isDiffuse = true;
			}
		else if (wParam == '1')
		{
			texture1 = "darkblueMetal.bmp";
			texture2 = "blackMetal.bmp";
			texture3 = "redMetal.bmp";
			texture4 = "lightblueMetal.bmp";
			texture5 = "red.bmp";
			texture6 = "whiteblueMark.bmp";
		}
		else if (wParam == '2')
		{
			texture1 = "greenMetal.bmp";
			texture2 = "greenMetal.bmp";
			texture3 = "lightblueMetal.bmp";
			texture4 = "white3.bmp";
			texture5 = "red.bmp";
			texture6 = "white3.bmp";
		}
		else if (wParam == '3')
		{
			texture1 = "blackMetal.bmp";
			texture2 = "blackMetal.bmp";
			texture3 = "white3.bmp";
			texture4 = "white3.bmp";
			texture5 = "red.bmp";
			texture6 = "white3.bmp";
		}
		else if (wParam == '4')
		{
			texture1 = "pink1.bmp";
			texture2 = "pink1.bmp";
			texture3 = "white3.bmp";
			texture4 = "white3.bmp";
			texture5 = "red.bmp";
			texture6 = "white3.bmp";
		}
		else if (wParam == 'J')
		b += prSpeed, posB[1] += prSpeed;
		else if (wParam == 'N')
		b -= prSpeed, posB[1] -= prSpeed;
		else if (wParam == 'M')
		a -= prSpeed, posB[0] -= prSpeed;
		else if (wParam == 'B')
		a += prSpeed, posB[0] += prSpeed;
		else if (wParam == 'H')
		c -= prSpeed, posB[2] -= prSpeed;
		else if (wParam == 'K')
		c += prSpeed, posB[2] += prSpeed;
		else if (wParam == VK_SPACE) {
		glLoadIdentity();
		//RESET TEXTURE
		texture1 = "darkblueMetal.bmp";
		texture2 = "blackMetal.bmp";
		texture3 = "redMetal.bmp";
		texture4 = "lightblueMetal.bmp";
		texture5 = "red.bmp";
		texture6 = "whiteblueMark.bmp";
		//RESET SMOKE
		smokespeed = 0, smokedrop = -16;
		//RESET PROJECTION
		tx = 0, ty = 0, tz = 0;
		ptx = 0, pty = 0, ptz = 0;
		pry = 0, pxy = 0, pzy = 0;
		//RESET LIGHTING
		posB[0] = 0.0;
		posB[1] = 0.0;
		posB[2] = 0.0;
		angle = 0;
		//RESET GUN
		gunspeed = 0;
		bulletpos1 = -4;
		//RESET ROCKET
		gunspeed = 0;
		bulletpos1 = -4;

		}
		else if (wParam == 'R') {
			headTurnRight = true;
		}
		else if (wParam == 'T') {
			headTurnLeft == true;
		}
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
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
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

void circleFill(float r, int sl, int st) {
	GLUquadricObj* leftc = NULL;
	leftc = gluNewQuadric();
	gluQuadricDrawStyle(leftc, GLU_FILL);
	gluSphere(leftc, r, sl, st);
	gluDeleteQuadric(leftc);
}

void drawTriangle(float l, float h) {
	glBegin(GL_TRIANGLES);
	//drawing triangle in all dimensions
	  // Front
	glTexCoord2f(0.5, 1);
	glVertex3f(h, l, 0.0f); // Top Of Triangle (Front)
	glTexCoord2f(0, 0);
	glVertex3f(-h, -h, h); // Left Of Triangle (Front)
	glTexCoord2f(1, 0);
	glVertex3f(h, -h, h); // Right Of Triangle (Front)

	// Right
	glTexCoord2f(0.5, 1);
	glVertex3f(h, l, 0.0f); // Top Of Triangle (Right)
	glTexCoord2f(0, 0);
	glVertex3f(h, -h, h); // Left Of Triangle (Right)
	glTexCoord2f(1, 0);
	glVertex3f(h, -h, -h); // Right Of Triangle (Right)

	// Left
	glTexCoord2f(0.5, 1);
	glVertex3f(h, l, 0.0f); // Top Of Triangle (Back)
	glTexCoord2f(0, 0);
	glVertex3f(h, -h, -h); // Left Of Triangle (Back)
	glTexCoord2f(1, 0);
	glVertex3f(-h, -h, -h); // Right Of Triangle (Back)

	//left
	glTexCoord2f(0.5, 1);
	glVertex3f(h, l, 0.0f); // Top Of Triangle (Left)
	glTexCoord2f(0, 0);
	glVertex3f(-h, -h, -h); // Left Of Triangle (Left)
	glTexCoord2f(1, 0);
	glVertex3f(-h, -h, h); // Right Of Triangle (Left)

	glEnd();
}

//-------------------------------------PROJECTION--------------------------------------------
void projection() {

	//--------------------------------
	//	Camera Projection
	//--------------------------------
	glMatrixMode(GL_PROJECTION); //refer to projection matrix
	glLoadIdentity(); //reset projection matrix

	if (isOrtho)
	{
		glRotatef(180, 0, 1, 0);
		//----- Orthographic view -----
		glOrtho(-30, 30, -30, 30, ONear, OFar); //left, right, bottom, top, near, far
	}
	else
	{
		glRotatef(180, 0, 1, 0);
		//----- Perspective view -----
		gluPerspective(20, 1, -1, 1); //fovy, aspect, near, far
		glFrustum(-10, 10, -10, 10, PNear, PFar); //xmin, xmax, ymin, ymax, -zmin(need to start from positive), -zmax

	}

	glRotatef(pry, 0, 1, 0); //Rotate projection y
	glTranslatef(ptx, pty, 0.0); //Translate projection x & y

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //Reset modelview matrix
	glTranslatef(tx, 0, tz); //Translate along the x & z axis (Translate for modelview) *

}

void lighting() {
	if (isLightOn) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}
	if (isDiffuse) {
		lightcheck = true;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MBlue);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MRed);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MYellow);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MWhite);
	}
	else {
		lightcheck = false;
		glMaterialfv(GL_FRONT, GL_AMBIENT, MRed);
		glMaterialfv(GL_FRONT, GL_AMBIENT, MBlue);
		glMaterialfv(GL_FRONT, GL_AMBIENT, MYellow);
		glMaterialfv(GL_FRONT, GL_AMBIENT, MWhite);
	}

	if (lightcheck) {
		//Light 1: white color diffuse light at pos(0, 20, 0) right
		glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT1, GL_POSITION, posB);
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
	else {
		//Light 2: white color ambient light at pos(0, 20, 0) right
		glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT2, GL_POSITION, posB);
		glEnable(GL_LIGHT2);
		glDisable(GL_LIGHT1);
	}






	glRotatef(angle, 1.0, 1.0, 1.0);

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
void Ncube(float sz) {
	glBegin(GL_POLYGON);
	//face1 bottom face
	//glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, 0.0f, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//face2 left

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);
	//face3 front

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.3 * sz, sz, sz); 
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, sz);
	//face4 right

	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.3 * sz, sz, sz); 
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.3 * sz, sz, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);
	//face5 back

	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.3 * sz, sz, 0.0f);
	//face6 top
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.3 * sz, sz, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.3 * sz, sz, sz);
	glEnd();
}

void feidan() {
	GLuint texture[2];
	texture[0] = loadTexture("whitegrey.bmp");
	Fly += FlySpeed;
	glPushMatrix();
	glTranslatef(9.4, 9.2, 14.0);
	glRotatef(Fly, 0.1, 0.0, 1.0);
	glScalef(0.35, 0.35, 0.35);
	DrawCylinder(0.9, 0.0, 3.0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, -2);
	DrawCylinder(1.1, 0.9, 2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -6.0);
	DrawCylinder(1.1, 1.1, 4.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -9.0);
	DrawCylinder(0.8, 1.1, 3.0);
	glPopMatrix();
	glDeleteTextures(1, &texture[0]);
	texture[1] = loadTexture("red.bmp");
	glPushMatrix();
	glTranslatef(-2.0, -0.2, -6.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glScalef(0.4, 1.0, 0.1);
	Ncube(4.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 0.3, -6);
	glRotatef(-180, 0.0, 0.0, 1.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glScalef(0.4, 1.0, 0.1);
	Ncube(4.0);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(-2.0, -0.2, -6.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glScalef(0.4, 1.0, 0.1);
	Ncube(4.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 0.3, -6);
	glRotatef(-180, 0.0, 0.0, 1.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glScalef(0.4, 1.0, 0.1);
	Ncube(4.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glDeleteTextures(1, &texture[1]);

}

void drawWaist() {
	GLuint waisttextureArr[5];		//initialize texture
	waisttextureArr[0] = loadTexture(texture1);

	//middle DOWN
	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, -0.25, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -0.25, 1);

	 //		left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.25, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 2,1.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 1.5, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, 0);

	//			bottom
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 1.5, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 1.5, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 0, 0);


	//		right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, 1.5, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.7, 2, 1.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, -0.25, 1);

	//		above
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, -0.25, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.25, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, 2, 1.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.7, 2, 1.5);

	//		back
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.7, 2, 1.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 2, 1.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 1.5, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 1.5, 0);
	glEnd();
	glPopMatrix();

	//LEFT Bottom
	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);				//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3, -0.17, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3, -0.17, 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -0.17, 0.7);

	//above
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.17, 0.7);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 2, 1.3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5, 2, 1.35);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3, -0.17, 2);

	//left 
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3, -0.17, 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3, -0.17, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5, 2, 0.35);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5, 2, 1.35);

	//BEHIND
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5, 2, 1.35);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 2, 1.3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 1.5, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5, 2, 0.35);

	//BELOW
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5, 2, 0.35);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3, -0.17, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1.5, 0);
	glEnd();
	glPopMatrix();

	//RIGHT Bottom
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, 0, 0);				//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.5, -0.17, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.5, -0.17, 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, -0.17, 0.7);

	//above
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, -0.17, 0.7);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.7, 2, 1.3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4, 2, 1.35);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.5, -0.17, 2);

	//right 
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.5, -0.17, 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.5, -0.17, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4, 2, 0.35);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4, 2, 1.35);


	//BEHIND
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4, 2, 1.35);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.7, 2, 1.3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 1.5, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4, 2, 0.35);

	//BELOW
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4, 2, 0.35);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.5, -0.17, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 1.5, 0);
	glEnd();
	glPopMatrix();


	glDeleteTextures(1, &waisttextureArr[0]);

	waisttextureArr[1] = loadTexture(texture6);
	//middle UP
	glColor3f(1, 1, 1);	
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, -0.25, 1);		//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.25, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, 2, 1.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.7, 2, 1.5);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.7, 2, 1.5);	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 2, 1.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 1.5, 3);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 1.5, 3);

	//above
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, 1.5, 3);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, -0.5, 3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.5, 3);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1.5, 3);

	//left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 1.5, 3);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 2, 1.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.25, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -0.5, 3);

	//front
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.5, 3);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.25, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, -0.25, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, -0.5, 3);


	//right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, -0.5, 3);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, -0.25, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.7, 2, 1.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 1.5, 3);

	glEnd();
	glPopMatrix();


	

	//Left Top
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.17, 0.7);		//front 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.5, 3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3, -0.5, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3, -0.17, 2);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3, -0.17, 2);		//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3, -0.5, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.1, 1.6, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5, 2, 1.35);

		//behind
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5, 2, 1.35);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 2, 1.3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 1.5, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.1, 1.6, 2.6);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.1, 1.6, 2.6);		//Above
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3, -0.5, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.5, 3);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1.5, 2.6);
	

	glEnd();
	glPopMatrix();

	//Right Top

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, -0.17, 0.7);		//front 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, -0.5, 3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.5, -0.5, 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.5, -0.17, 2);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.5, -0.17, 2);		//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.5, -0.5, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.6, 1.6, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4, 2, 1.35);

	glTexCoord2f(0.0f, 0.0f);			//behind
	glVertex3f(4, 2, 1.35);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.7, 2, 1.3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 1.5, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.6, 1.6, 2.6);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.6, 1.6, 2.6);		//Above
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.5, -0.5, 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, -0.5, 3);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 1.5, 2.6);

	glEnd();
	glPopMatrix();
	glDeleteTextures(1, &waisttextureArr[1]);
}

void drawBody() {
	GLuint bodytextureArr[5];		//initialize texture
	///0---------------------------------------------------bEHIND------------------------------------------
	bodytextureArr[0] = loadTexture(texture4);
	glColor3f(1, 1, 1);
	//------------------------------------middle bottom UP 1
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

	//------------------------------middle bottom up 2
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.4, -1.69, -6.2);
	drawRectangle(2.3, 1, 2);
	glPopMatrix();


	//------------------------------------middle bottom UP 3
	glPushMatrix();
	glTranslatef(0, -1.49, -9);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.4, -0.2, 2.8);		//front view (FROM behind)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.9, -0.2, 2.8);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2., -0.3,-1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, -0.3, -1);

	glTexCoord2f(0.0f, 0.0f);			//right view
	glVertex3f(-0.5, -0.3, -1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 1, -1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.4, 1, 2.8);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.4, -0.2, 2.8);

	glTexCoord2f(0.0f, 0.0f);			//Bottom View
	glVertex3f(-0.4, -0.2, 2.8);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.4, 1, 2.8);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.9, 1, 2.8);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.9, -0.2, 2.8);

	glTexCoord2f(0.0f, 0.0f);			//left
	glVertex3f(1.9, -0.2, 2.8);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.9, 1, 2.8);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2., 1, -1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2., -0.3, -1);

	glTexCoord2f(0.0f, 0.0f);			//	ABOVE
	glVertex3f(2., -0.3, -1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, -0.3, -1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 1, -1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.,1, -1);

	glTexCoord2f(0.0f, 0.0f);			//BEHIND(FROM BEHIND)
	glVertex3f(2., 1, -1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 1, -1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 1, 2.8);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2., 1, 2.8);
	glEnd();
	glPopMatrix();
	glDeleteTextures(1, &bodytextureArr[0]);

	bodytextureArr[3] = loadTexture(texture2);
	glColor3f(1, 1, 1);
	glPushMatrix();							//MUSCLE Line 1
	glTranslatef(-0.45, -1.7, -4.2);
	drawRectangle(2.35, 0.5, 0.1);
	glPopMatrix();

	glPushMatrix();							//MUSCLE Line 2
	glTranslatef(-0.44, -1.7, -6.3);
	drawRectangle(2.35, 0.5, 0.1);
	glPopMatrix();

	glPushMatrix();							//MUSCLE Line 3
	glTranslatef(-0.75, 0.35, -7.2);
	drawRectangle(3, 0.1, 0.1);
	glPopMatrix();

	glDeleteTextures(1, &bodytextureArr[3]);



	//--------------------------------------FRONT ------------------------------------------------
	bodytextureArr[1] = loadTexture(texture2);
	//LEFT SIDE
	glPushMatrix();
	glRotatef(180, 1, 0, 0);		//back
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 1.5, 2.6);	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2, 1.6, 2.6);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.8, 1.6, 10);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1.5, 10);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 1.5, 10);			//above
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.2, 10);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.8, -0.2, 10);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.8, 1.6, 10);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.8, 1.6, 10);		//left	(outside)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.8, 1.6, 2.6);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2, -0.2, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.8, -0.2, 10);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.8, -0.2, 10);		//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2, -0.2, 2.6);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.2, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -0.2, 10);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.2, 10);		//right (inside)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.2, 2.6);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 1.5, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1.5, 10);
	glEnd();
	glPopMatrix();

	//rIGHT SIDE
	glPushMatrix();
	glRotatef(180, 1, 0, 0);		//back
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, 1.5, 2.6);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.5, 1.6, 2.6);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.3, 1.6, 10);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 1.5, 10);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, 1.5, 10);			//above
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, -0.2, 10);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.3, -0.2, 10);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.3, 1.6, 10);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.3, 1.6, 10);		//left	(outside)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.3, 1.6, 2.6);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5, -0.2, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.3, -0.2, 10);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.3, -0.2, 10);		//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.5, -0.2, 2.6);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, -0.2, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, -0.2, 10);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, -0.2, 10);		//right (inside)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, -0.2, 2.6);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 1.5, 2.6);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5, 1.5, 10);
	glEnd();
	glPopMatrix();
	glDeleteTextures(1, &bodytextureArr[1]);

	//--------------------------------------------MUSCLE-----------------------------------------------------
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	bodytextureArr[2] = loadTexture(texture4);
	glPushMatrix();							//MUSCLE Middle 1
	glTranslatef(-0.75, 0.25, -3.4);
	glRotatef(6, 1, 0, 0);
	drawRectangle(3, 0.1, 0.5);
	glPopMatrix();

	glPushMatrix();							//MUSCLE Middle 2
	glTranslatef(-0.75, 0.35, -5);
	glRotatef(5, 1, 0, 0);
	drawRectangle(3, 0.1, 1.5);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();							//MUSCLE Middle 3
	glTranslatef(-0.75, 0.35, -7.1);
	drawRectangle(3, 0.1, 2);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();							//MUSCLE Middle 4
	glTranslatef(-0.75, 0.35, -10);
	drawRectangle(3, 0.1, 2.8);
	glPopMatrix();
	glDeleteTextures(1, &bodytextureArr[2]);

	bodytextureArr[3] = loadTexture(texture2);
	glColor3f(1, 1, 1);
	glPushMatrix();							//MUSCLE Line 1
	glTranslatef(-0.75, 0.25, -3.5);
	drawRectangle(3, 0.1, 0.1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();							//MUSCLE Line 2
	glTranslatef(-0.75, 0.35, -5.1);
	drawRectangle(3, 0.1, 0.1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();							//MUSCLE Line 3
	glTranslatef(-0.75, 0.35, -7.2);
	drawRectangle(3, 0.1, 0.1);
	glPopMatrix();

	glDeleteTextures(1, &bodytextureArr[3]);



	glPopMatrix();
	bodytextureArr[2] = loadTexture(texture2);
	glPushMatrix();							//MUSCLE Left 1
	glTranslatef(-1.7, 0.2, -10);
	glRotatef(10, 0, 0, 1);
	drawRectangle(1, 0.1, 6.8);
	glPopMatrix();


	glPushMatrix();							//MUSCLE Left 1
	glTranslatef(2.2, 0.36, -10);
	glRotatef(-10, 0, 0, 1);
	drawRectangle(1, 0.1, 6.8);
	glPopMatrix();

	glDeleteTextures(1, &bodytextureArr[2]);




}

void drawChest() {
	GLuint chesttextureArr[5];		//initialize texture
	//-------------------------------------------Front left
	chesttextureArr[1] = loadTexture(texture1);
	glBegin(GL_QUADS);				//front
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 1, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6, 1, -11);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-7, 1, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.1, 1, -14);

	glTexCoord2f(0.0f, 0.0f);			//back
	glVertex3f(-0.7, -2.5, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6, -2.5, -13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-7, -2.5, -20);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.1, -2.5, -20);

	glTexCoord2f(0.0f, 0.0f);			//left
	glVertex3f(-6, 1, -11);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-7, 1, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-7, -2.5, -20);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-6, -2.5, -13);

	glTexCoord2f(0.0f, 0.0f);			//below
	glVertex3f(-6, -2.5, -13);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.7, -2.5, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.1, 1, -9);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-6, 1, -11);


	glTexCoord2f(0.0f, 0.0f);				//above
	glVertex3f(-7, -2.5, -20);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.1, -2.5, -20);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.1, 1, -14);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-7, 1, -15);

	glTexCoord2f(0.0f, 0.0f);				//right
	glVertex3f(-2.1, -2.5, -20);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.7, -2.5, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.7, 1, -9);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.1, 1, -14);
	
	//-------------------------------------------Front Right
	glBegin(GL_QUADS);				//front
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.6, 1, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(7.5, 1, -11);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(8.5, 1, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.6, 1, -14);

	glTexCoord2f(0.0f, 0.0f);			//back
	glVertex3f(2.2, -2.5, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(7.5, -2.5, -13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(8.5, -2.5, -20);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.6, -2.5, -20);

	glTexCoord2f(0.0f, 0.0f);			//left
	glVertex3f(7.5, 1, -11);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(8.5, 1, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(8.5, -2.5, -20);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(7.5, -2.5, -13);

	glTexCoord2f(0.0f, 0.0f);			//below
	glVertex3f(7.5, -2.5, -13);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.2, -2.5, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.6, 1, -9);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(7.5, 1, -11);


	glTexCoord2f(0.0f, 0.0f);				//above
	glVertex3f(8.5, -2.5, -20);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.6, -2.5, -20);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.6, 1, -14);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(8.5, 1, -15);

	glTexCoord2f(0.0f, 0.0f);				//right
	glVertex3f(3.6, -2.5, -20);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.2, -2.5, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.2, 1, -9);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.6, 1, -14);
	//-----------------------------------------------------------Behind Middle
	glTexCoord2f(0.0f, 0.0f);			//front (FROM BEHIND)
	glVertex3f(-0.7, -2.5, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.2, -2.5, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.6, -2.5, -20);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.1, -2.5, -20);
	
	glTexCoord2f(0.0f, 0.0f);			//behind & inside (FROM BEHIND)
	glVertex3f(-0.7, 0.3, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.2, 0.3, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.5,-0.1, -16);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3, -0.1, -16);

	glTexCoord2f(0.0f, 0.0f);			//above
	glVertex3f(-3, -0.1, -16);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.5, -0.1, -16);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.6, -2.5, -20);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.1, -2.5, -20);



	glTexCoord2f(0.0f, 0.0f);			//front (FROM BEHIND)
	glVertex3f(-0.7, -2.5, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.2, -2.5, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.2,	0.3, -9);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.7, 0.3, -9);
	glEnd();
	glDeleteTextures(1, &chesttextureArr[1]);
	//----------------------------------------Right TUBE near head

	chesttextureArr[2] = loadTexture(texture6);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.5, -0.1, -16);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.4, -0.1, -16);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(4, -0.1, -18);


	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.3, -1.5, -18.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.2, -1.5, -18.5);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(3.8, -1.5, -20);

	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			//Right side face
	glVertex3f(4, -0.1, -18);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.8, -1.5, -20);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.2, -1.5, -18.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.4, -0.1, -16);

	glTexCoord2f(0.0f, 0.0f);			//left side face
	glVertex3f(4, -0.1, -18);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.8, -1.5, -20);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.3, -1.5, -18.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5, -0.1, -16);

	glTexCoord2f(0.0f, 0.0f);			//bottom side face
	glVertex3f(3.5, -0.1, -16);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.4, -0.1, -16);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.2, -1.5, -18.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.3, -1.5, -18.5);
	glEnd();

	//----------------------------------------Left TUBE near head
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2, -0.1, -16);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.9, -0.1, -16);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(-2.5, -0.1, -18);


	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.8, -1.5, -18.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.7, -1.5, -18.5);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(-2.3, -1.5, -20);

	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			//Right side face
	glVertex3f(-2.5, -0.1, -18);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.3, -1.5, -20);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.7, -1.5, -18.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.9, -0.1, -16);

	glTexCoord2f(0.0f, 0.0f);			//left side face
	glVertex3f(-2.5, -0.1, -18);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.3, -1.5, -20);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.8, -1.5, -18.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2, -0.1, -16);

	glTexCoord2f(0.0f, 0.0f);			//bottom side face
	glVertex3f(-2, -0.1, -16);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.9, -0.1, -16);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.7, -1.5, -18.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.8, -1.5, -18.5);
	glEnd();
	glDeleteTextures(1, &chesttextureArr[2]);
	chesttextureArr[0] = loadTexture(texture6);

	//-------------------------------------------Front middle
	glBegin(GL_POLYGON);				//front
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 1, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.6, 1, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4, 1, -15);
	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(2.5, 1, -17);
	glTexCoord2f(0.75f, 1.0f);
	glVertex3f(-1, 1, -17);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5, 1, -15);
	glEnd();

	glBegin(GL_POLYGON);				//back
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.6, 0, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4, 1, -15);
	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(2.5, 0, -17);
	glTexCoord2f(0.75f, 1.0f);
	glVertex3f(-1, 0, -17);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5, 0, -15);
	glEnd();

	glBegin(GL_QUADS);				//left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5, 1, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5, 0, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.1, 0, -9);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1, 1, -9);

	glTexCoord2f(0.0f, 0.0f);		//top left
	glVertex3f(-2.5, 1, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5, 0, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1, 0, -17);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1, 1, -17);

	glTexCoord2f(0.0f, 0.0f);		//top Middle
	glVertex3f(2.5, 1, -17);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5, 0, -17);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1, 0, -17);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1, 1, -17);

	glTexCoord2f(0.0f, 0.0f);		//top Right
	glVertex3f(2.5, 1, -17);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5, 0, -17);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4, 0, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4, 1, -15);

	glTexCoord2f(0.0f, 0.0f);		//Right
	glVertex3f(1.6, 1, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.6, 0, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4, 0, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4, 1, -15);

	glTexCoord2f(0.0f, 0.0f);		//Bottom
	glVertex3f(1.6, 1, -9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.6, 0, -9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.1, 0, -9);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1, 1, -9);
	glEnd();
	glDeleteTextures(1, &chesttextureArr[0]);

	//Draw RED CRYSTAL INFRONT body
	chesttextureArr[2] = loadTexture(texture5);
	glBegin(GL_QUADS);				//front
	glTexCoord2f(0.0f, 0.0f);				//middle bottom
	glVertex3f(-0.1, 1, -9.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.6, 1, -9.1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5, 1.5, -13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1, 1.5, -13);

	glTexCoord2f(0.0f, 0.0f);				//right bottom
	glVertex3f(1.6, 1, -9.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5, 1.5, -13);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2, 1, -13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.6, 1, -9.1);

	glTexCoord2f(0.0f, 0.0f);				//left bottom
	glVertex3f(-0.1, 1, -9.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1, 1.5, -13);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.7, 1, -13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1, 1, -9.1);

	glTexCoord2f(0.0f, 0.0f);				//middle up
	glVertex3f(2.5, 1.5, -13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1, 1.5, -13);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.1, 1.1, -17);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5, 1.1, -17);

	glTexCoord2f(1.0f, 1.0f);				//right up
	glVertex3f(2.5, 1.5, -13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5, 1.1, -17);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4, 1, -15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2, 1, -13);

	glTexCoord2f(1.0f, 1.0f);				//left up
	glVertex3f(-1, 1.5, -13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.1, 1.1, -17);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5, 1, -15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.7, 1, -13);

	//------------------above middle
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5, 1, -17);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.1, 1, -17);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.1, 1.1, -17);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5, 1.1, -17);

	glTexCoord2f(1.0f, 1.0f);				//right above
	glVertex3f(2.5, 1, -17);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5, 1.1, -17);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4, 1, -15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4, 1, -15);

	glTexCoord2f(1.0f, 1.0f);				//left above
	glVertex3f(-1.1, 1, -17);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.1, 1.1, -17);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5, 1, -15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5, 1, -15);

	glEnd();
	glDeleteTextures(1, &chesttextureArr[2]);

	//Draw black line INFRONT crystal
	chesttextureArr[2] = loadTexture(texture2);
	glPushMatrix();					//middle line
	glTranslatef(-1, 1, -13.2);
	drawRectangle(3.5, 0.5, 0.3);
	glPopMatrix();

	glPushMatrix();					//right line
	glTranslatef(2.25, 1.1, -13.2);
	glRotatef(-35,0,0,1);
	drawRectangle(2, 0.5, 0.3);
	glPopMatrix();

	glPushMatrix();					//left line
	glTranslatef(-2.4, 0, -13.2);
	glRotatef(35, 0, 0, 1);
	drawRectangle(2, 0.5, 0.3);
	glPopMatrix();
	glDeleteTextures(1, &chesttextureArr[2]);

	//----------------------------------------------------------CHEST TWO FRONT CIRCLE-------------------------------------
	//Right SIDE
	chesttextureArr[3] = loadTexture(texture2);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(6, 12.5, 0.1);
	DrawCylinder(0, 1.2, 1);
	glPopMatrix();
	glDeleteTextures(1, &chesttextureArr[3]);


	chesttextureArr[3] = loadTexture(texture6);			//middle
	glPushMatrix();
	glTranslatef(6, 0.9, -12.5);
	DrawSphere(0.35);
	glPopMatrix();
	glDeleteTextures(1, &chesttextureArr[3]);

	chesttextureArr[3] = loadTexture(texture6);			//fan
	glPushMatrix();
	glTranslatef(6, 1, -12.6);			//right
	glRotatef(fanrotate, 0, 1, 0);
	drawRectangle(0.9, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();						//left 
	glTranslatef(6, 1, -12.6);
	glRotatef(fanrotate, 0, 1, 0);
	drawRectangle(-0.9, 0.1, 0.3);
	glPopMatrix();

	glDeleteTextures(1, &chesttextureArr[3]);

	//LEFT SIDE
	chesttextureArr[3] = loadTexture(texture2);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-4.5, 12.5, 0.1);
	DrawCylinder(0, 1.2, 1);
	glPopMatrix();
	glDeleteTextures(1, &chesttextureArr[3]);


	chesttextureArr[3] = loadTexture(texture6);			//middle
	glPushMatrix();
	glTranslatef(-4.5, 0.9, -12.5);
	DrawSphere(0.35);
	glPopMatrix();
	glDeleteTextures(1, &chesttextureArr[3]);

	chesttextureArr[3] = loadTexture(texture6);			//fan
	glPushMatrix();
	glTranslatef(-4.5, 1, -12.6);			//right
	glRotatef(fanrotate, 0, 1, 0);
	drawRectangle(0.9, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();						//left 
	glTranslatef(-4.5, 1, -12.6);
	glRotatef(fanrotate, 0, 1, 0);
	drawRectangle(-0.9, 0.1, 0.3);
	glPopMatrix();
	fanrotate -= fanspeed;
	glDeleteTextures(1, &chesttextureArr[3]);
}

void drawBack() {
	GLuint backtextureArr[20];		//initialize texture
	backtextureArr[0] = loadTexture(texture6);

	//-----------------------------------------------------MIDDLE PART --------------------------------------------------
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 0.0f);			//front above (FROM BEHIND)
	glVertex3f(0, -4, -18);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, -4, -18);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3, -3, -20.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.5, -3, -20.5);

	glTexCoord2f(0.0f, 0.0f);			//front middle (FROM BEHIND)
	glVertex3f(0, -4, -18);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, -4, -18);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, -4, -12);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -4, -12);


	glTexCoord2f(0.0f, 0.0f);			//right middle (FROM BEHIND)
	glVertex3f(0, -4, -18);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -4, -12);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.4, -3, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.5, -3, -20.5);

	glTexCoord2f(0.0f, 0.0f);			//left middle (FROM BEHIND)
	glVertex3f(1.5, -4, -18);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.5, -4, -12);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.9, -3, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3, -3, -20.5);

	glTexCoord2f(0.0f, 0.0f);			//under middle (FROM BEHIND)
	glVertex3f(1.5, -4, -12);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.9, -3, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.4, -3, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -4, -12);

	glEnd();
	glDeleteTextures(1, &backtextureArr[0]);




	//-----------------------------------------------------Left Wing --------------------------------------------------
	backtextureArr[1] = loadTexture(texture1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.4, -3, -15);				//inside (FROM behind)
	glTexCoord2f(0.2f, 0.7f);
	glVertex3f(-3, -3, -13);
	glTexCoord2f(0.8f, 1.0f);
	glVertex3f(-15, -3, -21);
	glTexCoord2f(1.0f, 0.8f);
	glVertex3f(-14, -3, -24);
	glTexCoord2f(0.0f, 0.4f);
	glVertex3f(-2.1, -3, -20.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.4, -3.2, -15);				//Front & outside (FROM behind)
	glTexCoord2f(0.2f, 0.7f);
	glVertex3f(-3, -3.2, -13);
	glTexCoord2f(0.8f, 1.0f);
	glVertex3f(-15, -3.2, -21);
	glTexCoord2f(1.0f, 0.8f);
	glVertex3f(-14, -3.2, -24);
	glTexCoord2f(0.0f, 0.4f);
	glVertex3f(-2.1, -3.2, -20.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);					//right outer layer (FROM BEHIND)
	glVertex3f(-14, -3.2, -24);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-14, -3, -24);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-15, -3, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-15, -3.2, -21);

	glTexCoord2f(0.0f, 0.0f);					//Top outer layer (FROM BEHIND)
	glVertex3f(-14, -3.2, -24);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-14, -3, -24);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.1, -3, -20.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.1, -3.2, -20.5);

	glTexCoord2f(0.0f, 0.0f);					//left outer layer (FROM BEHIND)
	glVertex3f(-1.4, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.4, -3, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.1, -3, -20.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.1, -3.2, -20.5);

	glTexCoord2f(0.0f, 0.0f);					//left bottom outer layer (FROM BEHIND)
	glVertex3f(-1.4, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.4, -3, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3, -3, -13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3, -3.2, -13);

	glTexCoord2f(0.0f, 0.0f);					//right bottom outer layer (FROM BEHIND)
	glVertex3f(-3, -3.2, -13);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3, -3, -13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-15, -3, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-15, -3.2, -21);

	glEnd();
	glDeleteTextures(1, &backtextureArr[1]);
	//---------------------------------------------------red layer
	backtextureArr[2] = loadTexture(texture3);
	glBegin(GL_POLYGON);				//front
	glTexCoord2f(0.8f, 0.0f);
	glVertex3f(-14, -3, -24);
	glTexCoord2f(0.85f, 0.0f);
	glVertex3f(-15, -3, -21);
	glTexCoord2f(0.95f, 0.1f);
	glVertex3f(-16, -3, -21.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-15.7, -3, -28.5);
	glTexCoord2f(0.85f, 0.8f);
	glVertex3f(-15, -3, -26.5);
	glTexCoord2f(0.0f, 0.7f);
	glVertex3f(-2, -3, -22.5);
	glTexCoord2f(0.0f, 0.6f);
	glVertex3f(-2.1, -3, -20.5);
	glEnd();

	glBegin(GL_POLYGON);				//back
	glTexCoord2f(0.8f, 0.0f);
	glVertex3f(-14, -3.2, -24);
	glTexCoord2f(0.85f, 0.0f);
	glVertex3f(-15, -3.2, -21);
	glTexCoord2f(0.95f, 0.1f);
	glVertex3f(-16, -3.2, -21.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-15.7, -3.2, -28.5);
	glTexCoord2f(0.85f, 0.8f);
	glVertex3f(-15, -3.2, -26.5);
	glTexCoord2f(0.0f, 0.7f);
	glVertex3f(-2, -3.2, -22.5);
	glTexCoord2f(0.0f, 0.6f);
	glVertex3f(-2.1, -3.2, -20.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			//Inner right
	glVertex3f(-14, -3, -24);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-14, -3.2, -24);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-15, -3.2, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-15, -3, -21);

	glTexCoord2f(0.0f, 0.0f);			//Below
	glVertex3f(-16, -3, -21.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-16, -3.2, -21.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-15, -3.2, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-15, -3, -21);

	glTexCoord2f(0.0f, 0.0f);			//Right side
	glVertex3f(-16, -3, -21.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-16, -3.2, -21.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-15.7, -3.2, -28.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-15.7, -3, -28.5);

	glTexCoord2f(0.0f, 0.0f);			//Right top side
	glVertex3f(-15, -3, -26.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-15, -3.2, -26.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-15.7, -3.2, -28.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-15.7, -3, -28.5);

	glTexCoord2f(0.0f, 0.0f);			// top side
	glVertex3f(-15, -3, -26.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-15, -3.2, -26.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2, -3.2, -22.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2, -3, -22.5);

	glTexCoord2f(0.0f, 0.0f);			// left side
	glVertex3f(-2.1, -3, -20.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.1, -3.2, -20.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2, -3.2, -22.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2, -3, -22.5);

	glEnd();
	glDeleteTextures(1, &backtextureArr[2]);



	//-----------------------------------------------------Right Wing --------------------------------------------------
	backtextureArr[1] = loadTexture(texture1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.9, -3, -15);				//inside (FROM behind)
	glTexCoord2f(0.2f, 0.7f);
	glVertex3f(4.5, -3, -13);
	glTexCoord2f(0.8f, 1.0f);
	glVertex3f(16.5, -3, -21);
	glTexCoord2f(1.0f, 0.8f);
	glVertex3f(15.5, -3, -24);
	glTexCoord2f(0.0f, 0.4f);
	glVertex3f(3.6, -3, -20.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.9, -3.2, -15);				//Front & outside (FROM behind)
	glTexCoord2f(0.2f, 0.7f);
	glVertex3f(4.5, -3.2, -13);
	glTexCoord2f(0.8f, 1.0f);
	glVertex3f(16.5, -3.2, -21);
	glTexCoord2f(1.0f, 0.8f);
	glVertex3f(15.5, -3.2, -24);
	glTexCoord2f(0.0f, 0.4f);
	glVertex3f(3.6, -3.2, -20.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);					//right outer layer (FROM BEHIND)
	glVertex3f(15.5, -3.2, -24);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(15.5, -3, -24);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(16.5, -3, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(16.5, -3.2, -21);

	glTexCoord2f(0.0f, 0.0f);					//Top outer layer (FROM BEHIND)
	glVertex3f(15.5, -3.2, -24);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(15.5, -3, -24);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.6, -3, -20.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.6, -3.2, -20.5);

	glTexCoord2f(0.0f, 0.0f);					//left outer layer (FROM BEHIND)
	glVertex3f(2.9, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.9, -3, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.6, -3, -20.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.6, -3.2, -20.5);

	glTexCoord2f(0.0f, 0.0f);					//left bottom outer layer (FROM BEHIND)
	glVertex3f(2.9, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.9, -3, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.5, -3, -13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.5, -3.2, -13);

	glTexCoord2f(0.0f, 0.0f);					//right bottom outer layer (FROM BEHIND)
	glVertex3f(4.5, -3.2, -13);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.5, -3, -13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(16.5, -3, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(16.5, -3.2, -21);

	glEnd();

	glDeleteTextures(1, &backtextureArr[1]);

	//---------------------------------------------------red layer
	backtextureArr[2] = loadTexture(texture3);
	glBegin(GL_POLYGON);				//front
	glTexCoord2f(0.8f, 0.0f);
	glVertex3f(15.5, -3, -24);
	glTexCoord2f(0.85f, 0.0f);
	glVertex3f(16.5, -3, -21);
	glTexCoord2f(0.95f, 0.1f);
	glVertex3f(17.5, -3, -21.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(17.2, -3, -28.5);
	glTexCoord2f(0.85f, 0.8f);
	glVertex3f(16.5, -3, -26.5);
	glTexCoord2f(0.0f, 0.7f);
	glVertex3f(3.5, -3, -22.5);
	glTexCoord2f(0.0f, 0.6f);
	glVertex3f(3.6, -3, -20.5);
	glEnd();

	glBegin(GL_POLYGON);				//back
	glTexCoord2f(0.8f, 0.0f);
	glVertex3f(15.5, -3.2, -24);
	glTexCoord2f(0.85f, 0.0f);
	glVertex3f(16.5, -3.2, -21);
	glTexCoord2f(0.95f, 0.1f);
	glVertex3f(17.5, -3.2, -21.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(17.2, -3.2, -28.5);
	glTexCoord2f(0.85f, 0.8f);
	glVertex3f(16.5, -3.2, -26.5);
	glTexCoord2f(0.0f, 0.7f);
	glVertex3f(3.5, -3.2, -22.5);
	glTexCoord2f(0.0f, 0.6f);
	glVertex3f(3.6, -3.2, -20.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			//Inner right
	glVertex3f(15.5, -3, -24);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(15.5, -3.2, -24);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(16.5, -3.2, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(16.5, -3, -21);

	glTexCoord2f(0.0f, 0.0f);			//Below
	glVertex3f(17.5, -3, -21.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(17.5, -3.2, -21.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(16.5, -3.2, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(16.5, -3, -21);

	glTexCoord2f(0.0f, 0.0f);			//Right side
	glVertex3f(17.5, -3, -21.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(17.5, -3.2, -21.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(17.2, -3.2, -28.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(17.2, -3, -28.5);

	glTexCoord2f(0.0f, 0.0f);			//Right top side
	glVertex3f(16.5, -3, -26.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(16.5, -3.2, -26.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(17.2, -3.2, -28.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(17.2, -3, -28.5);

	glTexCoord2f(0.0f, 0.0f);			// top side
	glVertex3f(16.5, -3, -26.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(16.5, -3.2, -26.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5, -3.2, -22.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5, -3, -22.5);

	glTexCoord2f(0.0f, 0.0f);			// left side
	glVertex3f(3.6, -3, -20.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.6, -3.2, -20.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5, -3.2, -22.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5, -3, -22.5);

	glEnd();
	glDeleteTextures(1, &backtextureArr[2]);
	//-------------------------------------------------Right side jetpack---------------------------------
	backtextureArr[1] = loadTexture(texture1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			//FRONT (FROM BEHIND)
	glVertex3f(3, -3.7, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(6, -3.7, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6, -3.9, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3, -3.9, -21);

	glTexCoord2f(0.0f, 0.0f);			//Behind (FROM BEHIND)
	glVertex3f(3, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5, -3.2, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6, -3.2, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3, -3.2, -21);

	glTexCoord2f(0.0f, 0.0f);			//Right (FROM BEHIND)
	glVertex3f(3, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3, -3.7, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3, -3.9, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3, -2.9, -19);

	glTexCoord2f(0.0f, 0.0f);			//left (FROM BEHIND)
	glVertex3f(6, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(6, -3.7, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6, -3.9, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6, -3.2, -21);

	glTexCoord2f(0.0f, 0.0f);			//under (FROM BEHIND)
	glVertex3f(3, -3.7, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3, -3.2, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6, -3.2, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6, -3.7, -15);

	glTexCoord2f(0.0f, 0.0f);			//above (FROM BEHIND)
	glVertex3f(6, -3.9, -21);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(6, -3.2, -21);;
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3, -3.2, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3, -3.9, -21);

	//-------------------------------------------------left side jetpack---------------------------------

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			//FRONT (FROM BEHIND)
	glVertex3f(-1.5, -3.7, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.5, -3.7, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.5, -3.9, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.5, -3.9, -21);

	glTexCoord2f(0.0f, 0.0f);			//Behind (FROM BEHIND)
	glVertex3f(-1.5, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5, -3.2, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.5, -3.2, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.5, -3.2, -21);

	glTexCoord2f(0.0f, 0.0f);			//Right (FROM BEHIND)
	glVertex3f(-1.5, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.5, -3.7, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.5, -3.9, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.5, -2.9, -19);

	glTexCoord2f(0.0f, 0.0f);			//left (FROM BEHIND)
	glVertex3f(-4.5, -3.2, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.5, -3.7, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.5, -3.9, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.5, -3.2, -21);

	glTexCoord2f(0.0f, 0.0f);			//under (FROM BEHIND)
	glVertex3f(-1.5, -3.7, -15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.5, -3.2, -15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.5, -3.2, -15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.5, -3.7, -15);

	glTexCoord2f(0.0f, 0.0f);			//above (FROM BEHIND)
	glVertex3f(-4.5, -3.9, -21);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.5, -3.2, -21);;
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.5, -3.2, -21);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.5, -3.9, -21);

	//-----------------------------------------JETPACK TOP Right----------------------------------------------------
	glTexCoord2f(0.0f, 0.0f);			//FRONT (FROM BEHIND)
	glVertex3f(6, -3.9, -21);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3, -3.9, -21);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3, -3.5, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2, -3.5, -32);

	glTexCoord2f(0.0f, 0.0f);			//back (FROM BEHIND)
	glVertex3f(6, -2.9, -19);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3, -2.9, -19);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3, -2.9, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2, -2.9, -32);

	glTexCoord2f(0.0f, 0.0f);			//right (FROM BEHIND)
	glVertex3f(3, -3.9, -21);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3, -2.9, -19);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3, -2.9, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3, -3.5, -32);

	glTexCoord2f(0.0f, 0.0f);			//left (FROM BEHIND)
	glVertex3f(6, -3.9, -21);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(6, -2.9, -19);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2, -2.9, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2, -3.5, -32);

	glTexCoord2f(0.0f, 0.0f);			//Above (FROM BEHIND)
	glVertex3f(3, -3.5, -32);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2, -3.5, -32);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2, -2.9, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3, -2.9, -32);


	//-----------------------------------------JETPACK TOP left----------------------------------------------------
	glTexCoord2f(0.0f, 0.0f);			//FRONT (FROM BEHIND)
	glVertex3f(-4.5, -3.9, -21);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.5, -3.9, -21);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.5, -3.5, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.7, -3.5, -32);

	glTexCoord2f(0.0f, 0.0f);			//back (FROM BEHIND)
	glVertex3f(-4.5, -2.9, -19);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.5, -2.9, -19);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.5, -2.9, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.7, -2.9, -32);

	glTexCoord2f(0.0f, 0.0f);			//right (FROM BEHIND)
	glVertex3f(-1.5, -3.9, -21);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.5, -2.9, -19);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.5, -2.9, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.5, -3.5, -32);

	glTexCoord2f(0.0f, 0.0f);			//left (FROM BEHIND)
	glVertex3f(-4.5, -3.9, -21);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.5, -2.9, -19);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.7, -2.9, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.7, -3.5, -32);

	glTexCoord2f(0.0f, 0.0f);			//Above (FROM BEHIND)
	glVertex3f(-1.5, -3.5, -32);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.7, -3.5, -32);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.7, -2.9, -32);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.5, -2.9, -32);

	glEnd();
	glDeleteTextures(1, &backtextureArr[1]);

	//------------------------------jetpack middle
	backtextureArr[3] = loadTexture(texture5);
	glPushMatrix();
	glTranslatef(0.8,-3.2, -19);
	DrawSphere(0.5);
	glPopMatrix();
	glDeleteTextures(1, &backtextureArr[3]);

	//-----------------------------------JETPACK ADD DETAILS
	//jetpack right bottom
	backtextureArr[4] = loadTexture(texture6);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			//FRONT (FROM BEHIND)
	glVertex3f(-2.2, -3.8, -16);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.8, -3.8, -16);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.8, -3.85, -20);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.2, -3.85, -20);


	//jetpack left bottom
	glTexCoord2f(0.0f, 0.0f);			//FRONT (FROM BEHIND)
	glVertex3f(3.7, -3.8, -16);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.3, -3.8, -16);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.3, -3.85, -20);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.7, -3.85, -20);


	//--------------------------------------------LEFT TOP

	glTexCoord2f(0.0f, 0.0f);			//FRONT (FROM BEHIND)
	glVertex3f(-3.9, -3.85, -23);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2, -3.85, -23);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2, -3.7, -29);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.3, -3.7, -29);

	//--------------------------------------------right TOP

	glTexCoord2f(0.0f, 0.0f);			//FRONT (FROM BEHIND)
	glVertex3f(5.4, -3.85, -23);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.5, -3.85, -23);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5, -3.7, -29);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.8, -3.7, -29);

	glEnd();

	glDeleteTextures(1, &backtextureArr[4]);

	//black line 
	backtextureArr[5] = loadTexture(texture2);
	glPushMatrix();							//left jetpack bottom
	glTranslatef(-3.8, -3.85, -18.3);
	drawRectangle(1.6, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();							//left jetpack top 1
	glTranslatef(-3.8, -3.85, -24.5);
	drawRectangle(1.9, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();							//left jetpack top 2
	glTranslatef(-3.6, -3.85, -26.5);
	drawRectangle(1.6, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();							//left jetpack top 3
	glTranslatef(-3.4, -3.75, -28);
	drawRectangle(1.5, 0.1, 0.3);
	glPopMatrix();

	//right
	glPushMatrix();							//right jetpack bottom
	glTranslatef(3.7, -3.85, -18.3);
	drawRectangle(1.6, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();							//right jetpack top 1
	glTranslatef(3.5, -3.85, -24.5);
	drawRectangle(1.9, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();							//right jetpack top 2
	glTranslatef(3.5, -3.85, -26.5);
	drawRectangle(1.6, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();							//right jetpack top 3
	glTranslatef(3.4, -3.75, -28);
	drawRectangle(1.5, 0.1, 0.3);
	glPopMatrix();

	//jetpack front black holes
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			//back (FROM BEHIND)
	glVertex3f(-4.3, -2.85, -19);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.7, -2.85, -19);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.9, -2.85, -31.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.4, -2.85, -31.5);

	glTexCoord2f(0.0f, 0.0f);			//back (FROM BEHIND)
	glVertex3f(5.8, -2.85, -19);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2, -2.85, -19);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.4, -2.85, -31.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.9, -2.85, -31.5);
	glEnd();
	glDeleteTextures(1, &backtextureArr[5]);

	//------------------------------------------------------------ANIMATION-----------------------------------------------
	// Smoke Hole
	backtextureArr[6] = loadTexture(texture2);

	glPushMatrix();						//left side
	glTranslatef(-3, -3, -15);
	DrawCylinder(0.8, 0.8, 0.8);
	glPopMatrix();

	glPushMatrix();						//right side
	glTranslatef(4.5, -3, -15);
	DrawCylinder(0.8, 0.8, 0.8);
	glPopMatrix();

	glDeleteTextures(1, &backtextureArr[6]);


	//RELOAD SMOKE BULLET
	backtextureArr[5] = loadTexture("smoke.bmp");
	//left side
	glPushMatrix();							//smoke 1
	glTranslatef(-3, -3, smokedrop);
	DrawCylinder(0.6, 0.6, 0.8);
	glPopMatrix();

	if (smokedrop >= -13) {
		smokedrop = -16;
	}

	//right side
	glPushMatrix();							//smoke 1
	glTranslatef(4.5, -3, smokedrop);
	DrawCylinder(0.6, 0.6, 0.8);
	glPopMatrix();


	if (smokedrop >= -13) {
		smokedrop = -16;
	}
	smokedrop += smokespeed;
	glDeleteTextures(1, &backtextureArr[5]);
}

void drawHead() {
	GLuint headtextureArr[20];		//initialize texture
	
	

	glPushMatrix();
	//Animation for head
	glRotatef(headAngle, 0.0, 1.0, 0.0);

	if (headTurnRight == true) {
		if (headAngle <= 30 && headAngle != 30) {
			headAngle += 0.5;
			headTurnLeft = true;
		}
	}
	else {
		if (headAngle >= 0 && headAngle != 0) {
			headAngle -= 0.5;
		}
	}



	glPushMatrix();
	//Draw head
	glPushMatrix();						//L part
	glTranslatef(0.2, 0.7, 0.42);
	headtextureArr[0] = loadTexture(texture4);
	DrawSphere(0.4);
	glPopMatrix();

	glPushMatrix();						//A part
	drawRectangle(0.4, 0.4, 0.65);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[0]);

	
	glPushMatrix();						//I part
	glTranslatef(0.1, 0.5, 0.003);
	headtextureArr[1] = loadTexture(texture2);
	drawRectangle(0.202, 0.65, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[1]);


	
	glPushMatrix();						//B part
	glTranslatef(0.1, 0.4, 0.0);
	headtextureArr[2] = loadTexture(texture1);
	drawRectangle(0.2, 0.12, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[2]);


	glPushMatrix();						//C part
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.2, 0.2);
	headtextureArr[3] = loadTexture(texture6);
	drawTriangle(0.1, 0.2);
	glPopMatrix();
	

	glPushMatrix();						//D part
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.2, 0.6, -0.2);
	drawTriangle(0.1, 0.2);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[3]);

	
	glPushMatrix();						//E part
	glTranslatef(-0.3, 0.4, 0.0);
	headtextureArr[0] = loadTexture(texture4);
	drawCube(0.4);
	glPopMatrix();

	glPushMatrix();						//F part
	glTranslatef(0.3, 0.4, 0.0);
	drawCube(0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[0]);


	glPushMatrix();						//G part
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glTranslatef(0.105, 1.0, -0.2);
	headtextureArr[3] = loadTexture(texture6);
	drawTriangle(0.007, 0.2);
	glPopMatrix();

	glPushMatrix();						//H part
	glTranslatef(0.5, 1.0, 0.2);
	drawTriangle(0.007, 0.2);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[3]);

	
	glPushMatrix();						//J part
	glTranslatef(-0.5, 0.3, 0.007);
	headtextureArr[1] = loadTexture(texture2);
	drawRectangle(0.202, 0.75, 0.4);
	glPopMatrix();

	glPushMatrix();						//K part
	glTranslatef(0.7, 0.3, 0.007);
	drawRectangle(0.202, 0.75, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[1]);

	
	glPushMatrix();						//M part
	glTranslatef(-1.3, 0.8, 0.0);
	headtextureArr[2] = loadTexture(texture1);
	drawRectangle(0.8, 0.25, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[2]);

	
	glPushMatrix();						//N part
	glTranslatef(-1.2, 0.55, 0.0);
	headtextureArr[3] = loadTexture(texture6);
	drawRectangle(0.7, 0.25, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[3]);

	
	glPushMatrix();						//O part
	glTranslatef(-1.1, 0.3, 0.0);
	headtextureArr[2] = loadTexture(texture1);
	drawRectangle(0.6, 0.25, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[2]);

	
	glPushMatrix();						//P part
	glTranslatef(0.9, 0.8, 0.0);
	headtextureArr[2] = loadTexture(texture1);
	drawRectangle(0.8, 0.25, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[2]);

	
	glPushMatrix();						//Q part
	glTranslatef(0.9, 0.55, 0.0);
	headtextureArr[3] = loadTexture(texture6);
	drawRectangle(0.7, 0.25, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[3]);

	
	glPushMatrix();						//R part
	glTranslatef(0.9, 0.3, 0.0);
	headtextureArr[2] = loadTexture(texture1);
	drawRectangle(0.6, 0.25, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[2]);

	glPopMatrix();

	glPushMatrix();
	//Draw Eyes
	
	glPushMatrix();
	glTranslatef(-0.03, 0.52, -0.07);
	headtextureArr[4] = loadTexture("robotEye.bmp");
	drawRectangle(0.13, 0.08, 0.3);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[3]);

	
	glPushMatrix();
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(0.56, 0.07, -0.02);
	headtextureArr[1] = loadTexture(texture2);
	DrawPyramid(0.04);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[1]);

	
	glPushMatrix();
	glTranslatef(0.3, 0.52, -0.05);
	headtextureArr[4] = loadTexture("robotEye.bmp");
	drawRectangle(0.13, 0.08, 0.3);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[3]);

	
	glPushMatrix();
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.56, 0.47, -0.02);
	headtextureArr[1] = loadTexture(texture2);
	DrawPyramid(0.04);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[1]);
	glPopMatrix();
	
	
	glPushMatrix();
	//Draw Nose
	
	glPushMatrix();
	glTranslatef(0.16, 0.3, -0.07);
	headtextureArr[5] = loadTexture(texture3);
	drawRectangle(0.08, 0.1, 0.3);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[5]);

	glPushMatrix();
	glRotatef(-180.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.2, -0.26, -0.015);
	headtextureArr[5] = loadTexture(texture3);
	DrawPyramid(0.04);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[5]);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	//Draw Neck
	glPushMatrix();
	
	glTranslatef(0.05, -0.4, 0.2);
	headtextureArr[1] = loadTexture(texture2);
	drawRectangle(0.3, 1.0, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &headtextureArr[1]);
	glPopMatrix();
	glPopMatrix();
}

void drawGun() {
	GLuint guntextureArr[2];		//initialize texture
	guntextureArr[0] = loadTexture("whitegrey.bmp");
	glPushMatrix();							//gun middle
	glTranslatef(1, -2, -5);
	drawRectangle(1, 1, 4);
	glPopMatrix();

	glPushMatrix();							//gun middle
	glRotatef(90, 1, 0, 0);
	glTranslatef(1.1, -2, 1);
	drawRectangle(0.8, 1.2, 2);
	glPopMatrix();

	glDeleteTextures(1, &guntextureArr[0]);

	guntextureArr[0] = loadTexture("black1.bmp");
	glPushMatrix();							//gun top
	glTranslatef(1.3, -1, -5);
	drawRectangle(0.5, 0.5, 0.2);
	glPopMatrix();

	glPushMatrix();						//gun hole
	glTranslatef(1.5, -1.4, -5.4);
	DrawCylinder(0.3, 0, 2);
	glPopMatrix();

	glDeleteTextures(1, &guntextureArr[0]);

	//gun bullet
	guntextureArr[1] = loadTexture("red.bmp");
	glPushMatrix();
	glTranslatef(1.5, -1.4, bulletpos1);
	DrawCylinder(0.3, 0, 2);
	DrawSphere(0.3);
	glPopMatrix();

	glDeleteTextures(1, &guntextureArr[1]);
	bulletpos1 -= gunspeed;
	
	bulletpos1 -= gunspeed;

	if (bulletpos1 <= -40) {
		bulletpos1 = -4;

	}

}

void drawShoulderSphere(float rad) {

	GLuint Sphere1textureArr[1];
	Sphere1textureArr[0] = loadTexture("darkblueMetal.bmp");
	GLUquadricObj* sphere1 = NULL;
	glPointSize(4);
	sphere1 = gluNewQuadric();
	gluQuadricDrawStyle(sphere1, GLU_FILL);
	gluQuadricTexture(sphere1, true);
	gluSphere(sphere1, rad, 30, 30);
	gluDeleteQuadric(sphere1);
	glDeleteTextures(1, &Sphere1textureArr[0]);

}

void drawShoulderCylinder() {

	GLUquadricObj* Cylinder = NULL;
	Cylinder = gluNewQuadric();
	gluQuadricDrawStyle(Cylinder, GLU_FILL);
	gluCylinder(Cylinder, 0.5, 0.5, 1, 20, 20);
	gluDeleteQuadric(Cylinder);
}

void drawArmLeft(float size) {

	GLuint ArmtextureArr[1];
	ArmtextureArr[0] = loadTexture("lightblueMetal.bmp");
	glBegin(GL_QUADS);
	//face1 bottom face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//face2 left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, size);
	//face3 front
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0.0f, size);
	//face4 right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0.0f, 0.0f);
	//face5 back
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, 0.0f);
	//face6 top
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, size);
	glEnd();
	glDeleteTextures(1, &ArmtextureArr[0]);
}

void drawForeArmLeft1(float size) {

	GLuint ForeArmtextureArr[1];
	ForeArmtextureArr[0] = loadTexture("lightblueMetal.bmp");
	glBegin(GL_QUADS);
	//face1 bottom face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0.0f, 0.0f);

	//face2 left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, size);
	//face3 front
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0.0f, size);
	//face4 right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0.0f, 0.0f);
	//face5 back
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, 0.0f);
	//face6 top
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, size);
	glEnd();
	glDeleteTextures(1, &ForeArmtextureArr[0]);
}

void drawForeArmLeft2(float size) {
	glBegin(GL_QUADS);
	//face1 bottom face
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//face2 left
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(0.0f, 0.0f, size);
	//face3 front
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, 0.0f, size);
	//face4 right
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	//face5 back
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, size, 0.0f);
	//face6 top
	glVertex3f(size, size, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glEnd();
}

void drawForeArmLeft3(float size) {
	glBegin(GL_QUADS);
	//face1 bottom face
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//face2 left
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(0.0f, 0.0f, size);
	//face3 front
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, 0.0f, size);
	//face4 right
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	//face5 back
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, size, 0.0f);
	//face6 top
	glVertex3f(size, size, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glEnd();
}

void drawtrapezoid() {
	GLuint trapezoidtextureArr[1];
	trapezoidtextureArr[0] = loadTexture("blackMetal.bmp");

	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.5, 1, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.0, 0, 0);

	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 1, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.5, 1, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.0, 0, 1);

	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 1, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 1, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.5, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.5, 1, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.0, 0, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.0, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.5, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.5, 1, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 1, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, 1, 0);
	glEnd();

	glPopMatrix();
	glDeleteTextures(1, &trapezoidtextureArr[0]);
}

void drawFingers(float l, float w, float h) {
	GLuint fingertextureArr[1];
	fingertextureArr[0] = loadTexture("redMetal.bmp");
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
	glDeleteTextures(1, &fingertextureArr[0]);
}
void shoulderLeft() {
	glPushMatrix();
	glTranslatef(-8.8, 14, -0.6);
	drawShoulderSphere(2.5);
	glPopMatrix();
}

void shoulderRight() {
	glPushMatrix();
	glTranslatef(10.5, 14, -0.6);
	drawShoulderSphere(2.5);
	glPopMatrix();
}

void upperArmLeft() {
	glPushMatrix();
	glScalef(2.5, 5, 1.4);
	glTranslatef(-4, 1.4, -1.1);
	drawArmLeft(1.0);
	glPopMatrix();
}

void lowerArmLeft() {
	glPushMatrix();
	glPushMatrix();
	glScalef(2.5, 5.3, 1.4);
	glTranslatef(-3, 1.5, -0.2);
	glRotatef(-180, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	drawForeArmLeft1(0.9);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.7, 1.5, -1.0);
	drawShoulderSphere(1.8);
	glPopMatrix();
}

void wristLeft() {
	glPushMatrix();
	glScalef(2.5, 2.9, 1.4);
	glRotatef(180, 1, 0, 0);
	glTranslatef(-2.4, 0.1, 0.3);
	drawtrapezoid();
	glPopMatrix();
}

void fingersLeft() {
	//draw fingers left 1
	glPushMatrix();
	glTranslatef(-9.8, -4.7, -0.8);
	drawFingers(1, 1.6, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-9.8, -5.2, -0.8);
	drawFingers(1, 1.6, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-9.8, -6.4, -0.8);
	drawFingers(1, 1.2, 0.3);
	glPopMatrix();

		//draw fingers left 2
		glPushMatrix();
	glTranslatef(-9.8, -4.7, -1.5);
	drawFingers(1, 2, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-9.8, -5.2, -1.5);
	drawFingers(1, 2, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-9.8, -6.4, -1.5);
	drawFingers(1, 1.5, 0.3);
	glPopMatrix();

	//draw fingers left 3
	glPushMatrix();
	glTranslatef(-8.0, -4.3, -1.0);
	drawFingers(1, 2, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.0, -5.0, -1.0);
	drawFingers(1, 2, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.0, -6.2, -1.0);
	drawFingers(1, 1.5, 0.3);
	glPopMatrix();
}

void upperArmRight() {
	glPushMatrix();
	glScalef(2.5, 5, 1.4);
	glTranslatef(3.7, 1.4, -1.1);
	drawArmLeft(1.0);
	glPopMatrix();
}

void lowerArmRight() {
	glPushMatrix();
	glScalef(2.5, 5.3, 1.4);
	glTranslatef(3.75, 0.6, -1.1);
	drawForeArmLeft1(0.9);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.4, 1.5, -1.0);
	drawShoulderSphere(1.8);
	glPopMatrix();
}

void wristRight() {
	glPushMatrix();
	glScalef(2.5, 2.9, 1.4);
	glRotatef(180, 1, 0, 0);
	glTranslatef(5.2, 0.1, 0.3);
	drawtrapezoid();
	glPopMatrix();
}

void fingersRight() {
	//draw fingers right 1
	glPushMatrix();
	glTranslatef(10.8, -4.7, -0.8);
	drawFingers(1, 1.6, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10.8, -5.2, -0.8);
	drawFingers(1, 1.6, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10.8, -6.4, -0.8);
	drawFingers(1, 1.2, 0.3);
	glPopMatrix();

	//draw fingers right 2
	glPushMatrix();
	glTranslatef(10.8, -4.7, -1.5);
	drawFingers(1, 2, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10.8, -5.2, -1.5);
	drawFingers(1, 2, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10.8, -6.4, -1.5);
	drawFingers(1, 1.5, 0.3);
	glPopMatrix();

	//draw fingers right 3
	glPushMatrix();
	glTranslatef(9.0, -4.3, -1.0);
	drawFingers(1, 2, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(9.0, -5.0, -1.0);
	drawFingers(1, 2, 0.3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(9.0, -6.2, -1.0);
	drawFingers(1, 1.5, 0.3);
	glPopMatrix();
	glPopMatrix();
}

void thighLeft() {
	glPushMatrix();
	glTranslatef(-1.9, -1.7, -1.0);
	drawShoulderSphere(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.4, -11, -0.9);
	drawFingers(5, 8, -1.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	glScalef(3, 3, 1);
	glTranslatef(0, 0, -1.95);
	drawtrapezoid();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.9, -12, -1.0);
	drawShoulderSphere(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.4, -20, -0.9);
	drawFingers(5, 8, -1.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glScalef(3, 3, 1);
	glTranslatef(-2.6, 1.2, -1.95);
	drawtrapezoid();
	glPopMatrix();
}

void thighRight() {
	glPushMatrix();
	glTranslatef(4.5, -1.7, -1.0);
	drawShoulderSphere(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.3, -11, -0.9);
	drawFingers(5, 8, -1.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	glScalef(3, 3, 1);
	glTranslatef(4.5, 2.2, -2);
	drawtrapezoid();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.7, -12, -1.0);
	drawShoulderSphere(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.3, -20, -0.9);
	drawFingers(5, 8, -1.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 0, 1);
	glScalef(3, 3, 1);
	glTranslatef(2.5, 0.6, -1.95);
	drawtrapezoid();
	glPopMatrix();
}

void feetLeft() {
	glPushMatrix();
	glScalef(5, 3, 1);
	glRotatef(90, 0, 1, 0);
	glTranslatef(2, -7, -0.85);
	drawtrapezoid();
	glPopMatrix();
}

void feetRight() {
	glPushMatrix();
	glScalef(5, 3, 1);
	glRotatef(90, 0, 1, 0);
	glTranslatef(2, -7, 0.45);
	drawtrapezoid();
	glPopMatrix();
}


void display() {
	glClearColor(0.313725, 0.513725, 0.721568, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear screen
	glEnable(GL_DEPTH_TEST);
	projection();

	glMatrixMode(GL_MODELVIEW);		//refer to modelview Matrix

	glLoadIdentity();		//reset to modelview matrix
	glTranslatef(tx, ty, tz);		//tranlate along the z-axis
	GLuint textureArr[2];		//initialize texture
	lighting();

	//lighting ball
	glPushMatrix();
	textureArr[1] = loadTexture("sun.bmp");
	glRotatef(angle, 1.0, 1.0, 1.0);
	glTranslatef(posB[0], posB[1], posB[2]);
	//light source position
	DrawSphere(0.5);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//--------------------START OF DESIGN-----------------------------------------------------
	
	textureArr[0] = loadTexture("sky.bmp");
	glPushMatrix();
	DrawSphere(skysize);
	glPopMatrix();
	glDeleteTextures(1, &textureArr[0]);

	glPushMatrix();
	glScalef(0.8, 0.8, 1.5);
	glTranslatef(0, -20, 0);
	glRotatef(180, 0, 1, 0);
	//Draw Waist
	glRotatef(90, 1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.4, 1.4, 1.4);
	drawWaist();
	glPopMatrix();
	//Draw Body
	glPushMatrix();
	glRotatef(-4, 1, 0, 0);
	glTranslatef(0,0.2,0);
	glScalef(1.3, 1.1, 1.3);
	drawBody();
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.1, -0.5, -1.3);
	//Draw Chest
	drawChest();
	glPopMatrix();

	glPushMatrix();
	//Draw Back
	glTranslatef(0, 0, -0.8);
	drawBack();
	glPopMatrix();

	glPushMatrix();
	//Draw Head
	glTranslatef(2.0, 0.3, -20.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glScalef(5.0, 5.0, 4.0);
	drawHead();
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
	glPopMatrix();


	//draw gun 1
	glPushMatrix();
	glTranslatef(2, 6.5, 3);
	drawGun();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6.5, 6.5, 3);
	drawGun();
	glPopMatrix();

	glPushMatrix();						//rocket 1
	glTranslatef(-1.4, 1.2, rocketpos1);
	glRotatef(180, 0, 1, 0);
	glScalef(0.4, 0.4, 0.4);
	feidan();
	glPopMatrix();

	//draw gun 1
	glPushMatrix();
	glTranslatef(2, 6.5, 3);
	drawGun();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6.5, 6.5, 3);
	drawGun();
	glPopMatrix();

	glPushMatrix();						//rocket 1
	glTranslatef(-1.4, 1.2, rocketpos1);
	glRotatef(180, 0, 1, 0);
	glScalef(0.4, 0.4, 0.4);
	feidan();
	glPopMatrix();


	glPushMatrix();						//rocket 2
	glTranslatef(7.2, 1.2, rocketpos1);
	glRotatef(180, 0, 1, 0);
	glScalef(0.4, 0.4, 0.4);
	feidan();
	glPopMatrix();

	//control rocket
	rocketpos1 -= FlySpeed;


	if (rocketpos1 <= -40) {
		rocketpos1 = 6;

	}



	//Draw shoulder left
	glPushMatrix();
	glTranslatef(-0.5, -17, 2);
	glPushMatrix();
	glRotatef(down, 1, 0, 0);
	shoulderLeft();



	//draw arm left
	glPushMatrix();
	glRotatef(down, 1, 0, 0);
	upperArmLeft();


	//draw forearm left
	glPushMatrix();
	glRotatef(down, 1, 0, 0);
	lowerArmLeft();

	// draw wrist left
	glPushMatrix();
	glRotatef(down, 1, 0, 0);
	wristLeft();

	//draw fingers
	glPushMatrix();
	glRotatef(down, 1, 0, 0);
	fingersLeft();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//draw shoulder right
	glPushMatrix();
	glTranslatef(-2.4, -17, 2);
	glPushMatrix();
	glRotatef(up, 1, 0, 0);
	shoulderRight();
	//draw arm right
	glPushMatrix();
	glRotatef(up, 1, 0, 0);
	upperArmRight();
	//draw forearm right
	glPushMatrix();
	glRotatef(up, 1, 0, 0);
	lowerArmRight();

	//draw wrist right
	glPushMatrix();
	glRotatef(up, 1, 0, 0);
	wristRight();

	glPushMatrix();
	glRotatef(up, 1, 0, 0);
	fingersRight();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//draw thigh left
	glPushMatrix();
	glTranslatef(-2, -16, 2);
	glPushMatrix();
	glRotatef(le, 1, 0, 0);
	thighLeft();

	// draw feet left
	glPushMatrix();
	glRotatef(le, 0.5, 0, 0);
	feetLeft();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//draw thigh right
	glPushMatrix();
	glTranslatef(-2, -16, 2);
	glPushMatrix();
	glRotatef(ri, 1, 0, 0);
	thighRight();

	// draw feet right
	glPushMatrix();
	glRotatef(ri, 0.5, 0, 0);
	feetRight();

	glPopMatrix();
	glPopMatrix();
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
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
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