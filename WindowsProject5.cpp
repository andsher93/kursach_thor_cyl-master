/*****************************************************************/
/*                                                               */
/*                         inters_surface                        */
/*                         ==============                        */
/*                    Пересечение поверхностей      ddd             */
/*****************************************************************/

#include "WindowsProject5.h"
//#include "inters.h"
//#include "draw_figure.h"

//#include "draw_figure.h"
//-------------------------------------
// область отсечения
//-------------------------------------
RECT rcClip;
float   g_sceneWidth = 50.0;
GLUquadricObj* g_pGluQuadObj = NULL;
//-------------------------------------//
//  Параметры цилиндра и сферы		   //
//-------------------------------------//
POINT3D pt_cyl = { 0, 0, 0 };            // точка вставки цилиндра
//pt_sphere = { 0.3, 0.3, 0.5 }; // точка вставки сферы
GLfloat r_max = 10.0, r_min = 5.0;
POINT3D pt_torus = { 0,0,g_sceneWidth };
//pt_inters[200][2]; // массив точек пересечения
double r_cyl = g_sceneWidth / 3;       // радиус цилиндра
//r_sphere = g_sceneWidth / 3,   // радиус сферы
//r_point = g_sceneWidth / 40;    // радиус сферы для точки пересечения


//void DrawSphere(double);
/*
int Draw_inters(POINT3D Mas_output [2], POINT3D krug_rez)
{
	if (Mas_output[1].x != 0 && Mas_output[1].y != 0)
	{
		glPushMatrix();
		glTranslatef(Mas_output[0].x, krug_rez.y, Mas_output[0].y);
		DrawSphere(0.5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(Mas_output[1].x, krug_rez.y, Mas_output[1].y);
		DrawSphere(0.5);
		glPopMatrix();
		return 1;
	}
	else
		return 0;
}
*/
//void SetMaterialAndLight0(int);

// экземпляр приложения
HINSTANCE hiApp;
LPCWSTR pczAppName = _T("OpenGL");
// главное окно
HWND hwndMain;
HDC hdcMain;
HGLRC hglrcMain;
LPCWSTR pczMainWndClass = _T("WcOgl"),
pcz_wndTitle = pczAppName;

int wndW, wndH;
//POINT3D pt1, pt2, pt_rez[4] = { 0 }, pt_rez_vnut[4] = { 0 };
//POINT3D SPIRAL_center[800] = {};
//POINT3D Krug[2], Krug_rez_left[50] = { 0 }, Krug_rez_right[50];
//POINT3D	Start[2] = { 0, 0, 0 }, center = { 0, 0, 0 }, Mas_output[2] = { 0, 0, 0 };
//double g_angle = 0;
extern POINT3D SPIRAL_center[800];
extern int Kol_center_spiral;
BOOL fPlanes = FALSE;
int stPosX, stPosY;
float fAngViewX = 30,
fAngViewY = 45;
void Init(int, int);
// рисование сцены
void Draw(HDC hdc);
// установка формата пикселей
BOOL SetPixelFormat(HDC dc);

LRESULT CALLBACK MainWindowProc(HWND, UINT, WPARAM, LPARAM);
BOOL MainOnCreate(HWND, LPCREATESTRUCT);
BOOL MainOnSize(HWND, int, int);
BOOL MainOnCommand(HWND, int);
BOOL MainOnPaint(HWND);
BOOL MainOnLButtonDown(HWND hwnd_, int x, int y);
BOOL MainOnRButtonDown(HWND hwnd_, int x, int y);
BOOL MainOnMouseMove(HWND hwnd_, int x, int y, UINT flags);
BOOL MainOnDestroy(HWND);
BOOL InitApp(void);

void UninitApp(void);
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
// установка формата пикселей
BOOL SetPixelFormat(HDC dc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cStencilBits = 24;
	pfd.cDepthBits = 24;
	pfd.cAccumBits = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int pf = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pf, &pfd);
	return !(pfd.dwFlags & PFD_NEED_PALETTE);
}  //func SetPixelFormat
/***************************************************************/
/*                      Init                                   */
/*                      ====                                   */
/*       Инициализация  параметров  отрисовки                  */
/***************************************************************/
void Init(int ww, int wh)
{
	glFrontFace(GL_CW);
	//glEnable (GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// определить область отсечения
	int viewportSize = ww / 2;
	rcClip.left = ww / 2 - ww / 4;
	rcClip.bottom = wh / 2 + viewportSize / 2;

	rcClip.right = rcClip.left + viewportSize;
	rcClip.top = rcClip.bottom - viewportSize;

	glViewport(rcClip.left, rcClip.top,
		viewportSize, viewportSize);

	glOrtho(-48, 48, -48, 48, -48, 48);



	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}  //func Init
/*
void DrawSphere(double r)
{
	GLfloat m_ambient[] = { 0.24725, 0.1995, 0.0745, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);

	glColor3d(0, 0, 1);
	gluSphere(g_pGluQuadObj, r, 32, 32);
}

void DrawCylinder()
{
	SetMaterialAndLight0(POINT);
	gluCylinder(g_pGluQuadObj, g_sceneWidth / 4, g_sceneWidth / 4, g_sceneWidth - g_sceneWidth / 8, 32, 1);
}
*/
/*
int get_spiral_center(GLfloat r_max, POINT3D SPIRAL_center[800])
{
	int Kol = 0;
	double D_fi = 0.020;
	GLfloat d_z = 0.04,fi,fi_max;
	for (fi_max = -PI; fi_max < PI * 4; fi_max += D_fi)
	{
		for (fi = -PI; fi < PI; fi += D_fi)
		{



		}

		SPIRAL_center[Kol].x = r_max * cos(fi_max);
		SPIRAL_center[Kol].y = r_max * sin(fi_max);
		SPIRAL_center[Kol].z = g_sceneWidth / 4;

		Kol++;



	}
	return Kol;
}
*/
void DrawTorus()		// рисование тора
{

	/*----------------------*/
	/* нарисовать тор       */
	/*----------------------*/
	//Kol_center_spiral = 0;
	GLfloat         x1, x2, x3, x4,
		y1, y2, y3, y4,
		z1, z2, z3, z4,
		//fi, fi_max, r_max = 10.0, r_min = 5.0, dr, dr1, d_z = 0.2, R_c;
		fi, fi_max, dr, dr1, d_z = 0.2, R_c;
	R_c = r_max - r_min;
	C3dVector  v1, v2, v3, vn, v12, v13;

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glFrontFace(GL_CCW);

	glBegin(GL_TRIANGLES);
	double D_fi = 0.1;
	for (fi_max = -PI; fi_max < PI * 4; fi_max += D_fi)
	{
		for (fi = -PI; fi < PI; fi += D_fi)
		{
			dr = r_min * cos(fi);
			dr1 = r_min * cos(fi + D_fi);

			x1 = (r_max + dr) * cos(fi_max);      x2 = (r_max + dr1) * cos(fi_max);
			x3 = (r_max + dr1) * cos(fi_max + D_fi);  x4 = (r_max + dr) * cos(fi_max + D_fi);

			y1 = (r_max + dr) * sin(fi_max);      y2 = (r_max + dr1) * sin(fi_max);
			y3 = (r_max + dr1) * sin(fi_max + D_fi);  y4 = (r_max + dr) * sin(fi_max + D_fi);

			z1 = r_min * sin(fi);					z2 = r_min * sin(fi + D_fi);
			z3 = r_min * sin(fi + D_fi);     z4 = r_min * sin(fi);

			v1.x = x1;   v1.y = y1; v1.z = z1;
			v2.x = x2;   v2.y = y2; v2.z = z2;
			v3.x = x3;   v3.y = y3; v3.z = z3;

			v13 = v1 - v3;
			v12 = v1 - v2;
			vn = v12 ^ v13;

			glNormal3f(vn.x, vn.y, vn.z);
			glVertex3f(x1, y1, z1);
			glVertex3f(x3, y3, z3);
			glVertex3f(x2, y2, z2);

			glVertex3f(x1, y1, z1);
			glVertex3f(x4, y4, z4);
			glVertex3f(x3, y3, z3);

		}

	}
	glEnd();
	//Kol_center_spiral = get_spiral_center(r_max, SPIRAL_center);

	glFrontFace(GL_CW);
}  //DrawTorus

/***************************************************************/
/*                      Draw                                   */
/*                      ====                                   */
/*             Функция  отрисовки  куба                        */
/***************************************************************/
void Draw(HDC hdc) {

	//int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat m_ambient[] = { 0.24725, 0.1995, 0.0745, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);

	// диффузный
	GLfloat m_diffuse[] = { 0.75164, 0.60648, 0.22648, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse);

	// зеркальный
	GLfloat m_specular[] = { 0.628281, 0.555802, 0.366065, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);

	// сохранить текущую модельную матрицу в стек
	glPushMatrix();

	// матрицы поворота отностительно осей X и Y

	glRotatef(fAngViewY, 0.f, 1.f, 0.f);
	glRotatef(10, 0.f, 0.f, 1.f);
	glRotatef(fAngViewX, 1.f, 0.f, 0.f);


	/*----------------------*/
	/* нарисовать оси       */
	/*----------------------*/

	SetMaterialAndLight0(AXIS);

	glLineWidth(2.f);
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(10, 0, 0);
	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 20, 0);
	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 30);
	glEnd();

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);




	glColor3d(1, 0, 0);
	double d_z = 0.2;



	glPushMatrix();
	glTranslated(0, 0, g_sceneWidth / 4);

	//SetMaterialAndLight0(CYLINDER);
	DrawTorus();
	//glTranslated(0, 0, -g_sceneWidth / 4);
	glPopMatrix();

	
	glPushMatrix();
	//SetMaterialAndLight0(SPIRAL);
	glTranslated(0, -g_sceneWidth / 4, 0.);

	DrawCylinder();
	glPopMatrix();
	//glTranslated(0, +g_sceneWidth / 4, 0.);
	glColor3d(0, 0, 1);
	intersection();
	/*
	pt1 = { 0, 0, 0 };
	pt2 = { 0, -g_sceneWidth / 4, 0 };
	inters_2_circle(pt1, pt2, 15, g_sceneWidth / 4, pt_rez);
	inters_2_circle(pt1, pt2, 5, g_sceneWidth / 4, pt_rez_vnut);

	//поиск крайних точек слева от НК
	Krug[0] = pt_rez[0];
	Krug[1] = pt_rez_vnut[0];
	Polyr_poisk(Krug, Krug_rez_left);

	//поиск крайних точек справа от НК
	Krug[0] = pt_rez[1];
	Krug[1] = pt_rez_vnut[1];
	Polyr_poisk(Krug, Krug_rez_right);




	// Поиск точек пересечения слева от начала координат и их отрисовка
	Start[1].y = g_sceneWidth;
	for (int j = 0, i = 0; j < Kol_center_spiral; j += 1)
	{
		Start[0].x = Krug_rez_left[i].x;
		Start[0].y = 0;
		Start[1].x = Krug_rez_left[i].x;
		center.x = SPIRAL_center[j].x;
		center.y = SPIRAL_center[j].z;
		
	

		inters_line_circle(Start[0], Start[1], center, 5.0, Mas_output);
		
		if (Draw_inters(Mas_output, Krug_rez_left[i]))
			i++;

		if (i == N_delta + 1) {
			j += 80;
			i = 0;
		}
	}


	// Поиск точек пересечения справа от начала координат и их отрисовка
	Start[1].y = g_sceneWidth;
	for (int j = 0, i = N_delta; j < Kol_center_spiral; j += 1)
	{
		Start[0].x = Krug_rez_right[i].x;
		Start[0].y = 0;
		Start[1].x = Krug_rez_right[i].x;
		center.x = SPIRAL_center[j].x;
		center.y = SPIRAL_center[j].z;

		inters_line_circle(Start[0], Start[1], center, 5.0, Mas_output);

		if (Draw_inters(Mas_output, Krug_rez_right[i]))
		{
			i--;
		}
		if (i == -1) {
			i = N_delta;
			j += 280;
		}
	}*/
	glPopMatrix();
	
	glFinish();
	SwapBuffers(hdc);
}  //func Draw


LRESULT CALLBACK MainWindowProc(HWND hwnd_, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT r;
	switch (msg)
	{
	case WM_CREATE:
		return MainOnCreate(hwnd_, (LPCREATESTRUCT)lParam);
	case WM_SIZE:
		return MainOnSize(hwnd_, LOWORD(lParam), HIWORD(lParam));
	case WM_COMMAND:
		return MainOnCommand(hwnd_, LOWORD(wParam));
	case WM_PAINT:
		return MainOnPaint(hwnd_);
	case WM_LBUTTONDOWN:
		return MainOnLButtonDown(hwnd_, LOWORD(lParam), HIWORD(lParam));
	case WM_RBUTTONDOWN:
		return MainOnRButtonDown(hwnd_, LOWORD(lParam), HIWORD(lParam));
	case WM_MOUSEMOVE:
		return MainOnMouseMove(hwnd_, LOWORD(lParam), HIWORD(lParam), wParam);
	case WM_DESTROY:
		return MainOnDestroy(hwnd_);
	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			fPlanes = !fPlanes;
			GetClientRect(hwnd_, &r);
			Init(r.right, r.bottom);
			InvalidateRect(hwnd_, NULL, FALSE);
			return 0L;
		}
	default:
		return DefWindowProc(hwnd_, msg, wParam, lParam);
	}
	return 0L;
}  //func MainWndProc
// обработчик WM_CREATE
BOOL MainOnCreate(HWND hwnd_, LPCREATESTRUCT p_cs)
{

	// получить контекст окна
	// (значение дескриптора не меняется, т.к. класс окна имеет стиль CS_OWNDC)
	hdcMain = GetDC(hwnd_);
	// установить формат пикселей
	SetPixelFormat(hdcMain);
	// создать контекст воспроизведения OpenGL, сделать его текущим
	hglrcMain = wglCreateContext(hdcMain);
	wglMakeCurrent(hdcMain, hglrcMain);

	// создать квадратичный объект OpenGL
	g_pGluQuadObj = gluNewQuadric();
	assert(g_pGluQuadObj);

	return TRUE;
}  //func MainOnCreate
// обработчик сообщения WM_SIZE
BOOL MainOnSize(HWND hwnd_, int wndW_, int wndH_)
{
	wndW = wndW_;
	wndH = wndH_;
	Init(wndW, wndH);
	return TRUE;
}  //func MainOnSize
// обработчик сообщения WM_COMMAND
BOOL MainOnCommand(HWND hwnd_, int cmdID_)
{
	//	InvalidateRect (hwnd_, NULL, FALSE);
	return 0L;
}  //func MainOnSize
// обработчик сообщения WM_PAINT
BOOL MainOnPaint(HWND hwnd_)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd_, &ps);
	Draw(hdcMain);

	//SelectObject (hdc, GetStockObject (WHITE_PEN));
	//SelectObject (hdc, GetStockObject (NULL_BRUSH));
	//Rectangle (hdc, rcClip.left, rcClip.top, rcClip.right, rcClip.bottom);

	EndPaint(hwnd_, &ps);
	return TRUE;
}  //func MainOnPaint
// обработчик сообщения WM_LBUTTONDOWN
BOOL MainOnLButtonDown(HWND hwnd_, int x, int y)
{
	stPosX = x;
	stPosY = y;
	return TRUE;
}  //func MainOnLButtonDown
// обработчик сообщения WM_RBUTTONDOWN
BOOL MainOnRButtonDown(HWND hwnd_, int x, int y)
{
	stPosX = x;
	stPosY = y;
	//pr_cube = -pr_cube;
	InvalidateRect(hwnd_, NULL, FALSE);
	return TRUE;
}  //func MainOnRButtonDown
// обработчик сообщения WM_MOUSEMOVE
BOOL MainOnMouseMove(HWND hwnd_, int x, int y, UINT flags)
{
	if (!((MK_LBUTTON | MK_RBUTTON) & flags))
		return FALSE;
	if (MK_LBUTTON == flags)
	{
		float fDAng = 180.f * (x - stPosX) / wndW;
		fAngViewY += fDAng;
		if (fAngViewY > 360.f)
			fAngViewY -= 360.f;
		if (fAngViewY < -360.f)
			fAngViewY += 360.f;
		fDAng = 180.f * (y - stPosY) / wndH;
		fAngViewX += fDAng;
		if (fAngViewX > 360.f)
			fAngViewX -= 360.f;
		if (fAngViewX < -360.f)
			fAngViewX += 360.f;
		stPosX = x;
		stPosY = y;
	}
	else
	{
		stPosX = x;
		stPosY = y;
	}
	InvalidateRect(hwnd_, NULL, FALSE);
	return TRUE;
}  //func MainOnMouseMove
BOOL MainOnDestroy(HWND hwnd_)
{
	// удалить контекст воспроизведения OpenGL
	wglMakeCurrent(NULL, NULL);
	if (hglrcMain)
		wglDeleteContext(hglrcMain);
	PostQuitMessage(0);
	return TRUE;
}  //func MainOnDestroy
BOOL InitApp()
{
	// зарегистрировать класс для главного окна
	WNDCLASSEX wce;
	ZeroMemory(&wce, sizeof(WNDCLASSEX));
	wce.cbSize = sizeof(WNDCLASSEX);
	wce.hInstance = hiApp;
	wce.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wce.lpfnWndProc = MainWindowProc;
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//	wce.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
	wce.lpszClassName = pczMainWndClass;
	if (!RegisterClassEx(&wce))
		return FALSE;
	// определить размеры экрана
	int scrw2 = GetSystemMetrics(SM_CXSCREEN) / 2,
		scrh2 = GetSystemMetrics(SM_CYSCREEN) / 2;
	// создать главное окно, показать его
	hwndMain = CreateWindow(pczMainWndClass, pcz_wndTitle,
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
		| WS_THICKFRAME | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		0, 0, 1600, 900, NULL, NULL, hiApp, NULL);
	if (!hwndMain)
		return FALSE;
	ShowWindow(hwndMain, SW_SHOW);
	UpdateWindow(hwndMain);
	return TRUE;
}  //func InitApp
void UninitApp()
{
	// снять регистрацию класса главного окна
	UnregisterClass(pczMainWndClass, hiApp);
}  //func UninitApp
int APIENTRY WinMain(HINSTANCE hiApp__, HINSTANCE, LPSTR, int)
{
	MSG msg;
	hiApp = hiApp__;
	// инициализация приложения
	if (!InitApp())
		return 0;
	// ожидание и обработка сообщений
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);
	// заключительные действия
	UninitApp();
	// вернуть значение, переданное из PostQuitMessage
	return msg.wParam;
}  //func WinMain
// --- main.cpp ---
//
// установка материала и источника света
//
/*
void SetMaterialAndLight0(int type_material)
{
	float r = 1.0,
		g = 0.5,
		b = 0.5;

	float diffuse[] = { r, g, b, 1.f },
		specular[] = { 0.0f, 1.0f, 1.0f, 1.f },

		sphere_mat[] = { .0f, 0.f, 1.1f, 1.f },
		cone_mat[] = { 1.f, 1.3f, .0f, 1.f },
		point_mat[] = { 0.0f, 1.0f, 0.f, 1.f };


	//glMaterialfv (GL_FRONT, GL_DIFFUSE, diffuse);

	switch (type_material)
	{
	case CYLINDER:  glMaterialfv(GL_FRONT, GL_AMBIENT, cone_mat); break;
	case SPIRAL:    glMaterialfv(GL_FRONT, GL_AMBIENT, sphere_mat); break;
	case POINT:     glMaterialfv(GL_FRONT, GL_DIFFUSE, point_mat); break;
	default: break;
	}

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 64.0);

	GLfloat ambient[] = { 0.75, 0.75, 0.75, 1.0 };
	GLfloat lightPos[] = { 10.0, 10.0, 10.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}
*/