
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
			pty -= ptSpeed;
		else if (wParam == 'S')
			pty += ptSpeed;
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
//--------------------------------------------------------------------
void drawSphereWithoutGLU()
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;
	int sliceNo = 30, stackNo = 30;
	for (sliceA = 0.0; sliceA < PI; sliceA += PI / sliceNo)
	{
		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void DrawSphere(double r) {


	GLUquadricObj* sphere = NULL;
	glPointSize(2);
	sphere = gluNewQuadric();



	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);

}

void drawCube(float length) {
	glBegin(GL_QUADS);
	// Face 1 : Bottom
	glVertex3f(0.0f, 0.0f, length);
	glVertex3f(length, 0.0f, length);
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);


	// Face 2 : Left
	glVertex3f(0, 0, 0);
	glVertex3f(0, length, 0);
	glVertex3f(0, length, length);
	glVertex3f(0, 0, length);

	// Face 3 : Front
	glVertex3f(0, 0, length);
	glVertex3f(0, length, length);
	glVertex3f(length, length, length);
	glVertex3f(length, 0, length);

	// Face 4 : Right
	glVertex3f(length, 0, length);
	glVertex3f(length, 0, 0);
	glVertex3f(length, length, 0);
	glVertex3f(length, length, length);

	// Face 5 : Top
	glVertex3f(length, length, length);
	glVertex3f(0, length, length);
	glVertex3f(0, length, 0);
	glVertex3f(length, length, 0);

	// Face 6 : Back
	glVertex3f(length, length, 0);
	glVertex3f(0, length, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(length, 0, 0);
	glEnd();
}

void DrawCylinder(double br, double tr, double h) {


	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, br, tr, h, 10, 10);
	gluDeleteQuadric(cylinder);
}

void projection() {
	glMatrixMode(GL_PROJECTION);  //refer to porjetion matrix
	glLoadIdentity();				// reset to project matrix

	glTranslatef(ptx, pty, ptz);		//translate for projection matrix
	glRotatef(pry, 0.0, 1.0, 0.0);		//rotate y-axis for projection
	glRotatef(pxy, 1.0, 0.0, 0.0);		//rotate x-axis for projection
	glRotatef(pzy, 0.0, 0.0, 1.0);		//rotate x-axis for projection


	//Ortho View
	glOrtho(-10.0, 10.0, -10.0, 10.0, ONear, OFar);

	//if (isOrtho) {
		//Ortho View
	//	glOrtho(-10.0, 10.0, -10.0, 10.0, ONear, OFar);
	//}
	//else {
		//Perspective View
	//	gluPerspective(20, 1.0, -1, 1);
	//	glFrustum(-10.0, 10.0, -10.0, 10.0, PNear, PFar);
	//}

}

void drawRectangle(double l, double w, double h) {
	glBegin(GL_QUADS);
	//face 1 down
	glVertex3f(0, 0, 0);
	glVertex3f(l, 0, 0);
	glVertex3f(l, 0, h);
	glVertex3f(0, 0, h);

	//face 2 face
	glVertex3f(0, 0, h);
	glVertex3f(0, w, h);
	glVertex3f(l, w, h);
	glVertex3f(l, 0, h);

	//face 3 right
	glVertex3f(l, 0, h);
	glVertex3f(l, w, h);
	glVertex3f(l, w, 0);
	glVertex3f(l, 0, 0);

	//face 4 face bottom
	glVertex3f(l, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, w, 0);
	glVertex3f(l, w, 0);

	//face 5 above
	glVertex3f(l, w, 0);
	glVertex3f(l, w, h);
	glVertex3f(0, w, h);
	glVertex3f(0, w, 0);

	//face 6 left
	glVertex3f(0, w, 0);
	glVertex3f(0, w, h);
	glVertex3f(0, 0, h);
	glVertex3f(0, 0, 0);
	glEnd();
}

void drawTextureRectangle(double l, double w, double h) {
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

void drawBody() {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(0, 0.5, 0);
	glEnd();
	glPopMatrix();
}

void display() {
	glClearColor(0.313725, 0.513725, 0.721568, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear screen
	glEnable(GL_DEPTH_TEST);
	projection();

	glMatrixMode(GL_MODELVIEW);		//refer to modelview Matrix

	GLuint textureArr[4];		//initialize texture

	glLoadIdentity();		//reset to modelview matrix
	glTranslatef(tx, ty, tz);		//tranlate along the z-axis



	glTranslatef(-8, -4, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	//--------------------START OF DESIGN-----------------------------------------------------

	//water
	//glPushMatrix();
	//textureArr[0] = loadTexture("texture/water.bmp");
	//drawTextureRectangle(15, 10, 0.2);
	//glDeleteTextures(1, &textureArr[0]);
	//glPopMatrix();


	drawBody();


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