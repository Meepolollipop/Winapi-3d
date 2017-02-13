// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include <vector>
#include <string>
#include <fstream>


#define MAX_LOADSTRING 100

class three_dimension_point
{
public:
	three_dimension_point();
	void SetPoint(float x, float y, float z);
	float x, y, z;								//coordinates
	float xc, yc, zc;							//center of the point. it used to rotation
	float xn, yn, zn;
	void XY(int t);
	void XZ(int t);
	void ZY(int t);
};

three_dimension_point::three_dimension_point()
{
	x = y = z = xc = yc = zc = xn = yn = zn = 0;
}

void three_dimension_point::SetPoint(float X, float Y, float Z)
{
	x = xn = X; y = yn = Y; z = zn = Z;
}

int size;
std::vector<three_dimension_point> point; ///////////////////////
std::vector<std::vector<double>> normals;
int lens = 10000;
//center of the scene
float xo = 300, yo = 200, zo = 0;
float t = 0;
float pi = 3.14;

int sgn(float Val) 
{
	if (Val == 0.)  return 0;
	if (Val > 0.)  return 1;
	else return -1;
}

void MoveX(int t)
{
	for (int i = 0; i <= size - 1; i++)
	{    ////////24
		point[i].x += t; point[i].xc += t;
		
	}
}

void MoveY(int t)
{
	for (int i = 0; i <= size - 1; i++)
	{   //////////24
		point[i].y += t; point[i].yc += t;
	}
}

void MoveZ(int t)
{
	for (int i = 0; i <= size - 1; i++)
	{   //////24
		point[i].z += t; point[i].zc += t;
	}
}

void RotX(int t/*degree*/)
{
	float teta = t*pi / (float)180;
	for (int i = 0; i<size - 1; i++)
	{  ////////////24
		float c = cos(teta), s = sin(teta);//use once these functions to reduce calculating
		float zt = (point[i].z - point[i].zc)*c - (point[i].y - point[i].yc)*s + point[i].zc;
		float yt = (point[i].z - point[i].zc)*s + (point[i].y - point[i].yc)*c + point[i].yc;
		point[i].z = zt;
		point[i].y = yt;
	}
}

void RotY(int t/*degree*/)
{
	float teta = t*pi / (float)180;
	for (int i = 0; i <= size - 1; i++)
	{       //////////24
		float c = cos(teta), s = sin(teta);//use once these functions to reduce calculating
		float zt = (point[i].z - point[i].zc)*c - (point[i].x - point[i].xc)*s + point[i].zc;
		float xt = (point[i].z - point[i].zc)*s + (point[i].x - point[i].xc)*c + point[i].xc;
		point[i].z = zt;
		point[i].x = xt;

	}
}

void RotZ(int t/*degree*/)
{
	float teta = -t*pi / (float)180;
	for (int i = 0; i <= size - 1; i++)
	{          //////////24
		float c = cos(teta), s = sin(teta);//use once these functions to reduce calculating
		float xt = (point[i].x - point[i].xc)*c - (point[i].y - point[i].yc)*s + point[i].xc;
		float yt = (point[i].x - point[i].xc)*s + (point[i].y - point[i].yc)*c + point[i].yc;
		point[i].x = xt;
		point[i].y = yt;
	}
}

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc,hdcMem;
	HBITMAP hbmMem;
	HANDLE hOld;
	RECT rect;
	HBRUSH hbr = CreateSolidBrush(RGB(255,255,255));
	HBRUSH hbr1 = CreateSolidBrush(RGB(255, 0, 0));
	GetClientRect(hWnd, &rect);
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	int win_width = rect.right - rect.left;
	int win_height = rect.bottom + rect.left;
	/*
	hdcMem = CreateCompatibleDC(hdc);
	int savedDC = SaveDC(hdcMem);
	hbmMem = CreateCompatibleBitmap(hdc, 1280, 800);
	hOld = SelectObject(hdcMem, hbmMem);
	*/
	std::ifstream f("teapot.obj");
	std::vector<std::vector<double>> verticles;
	std::vector<std::vector <int>> faces;
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
	{
		int vc = 0, vf = 0;
		while (!f.eof())
		{
			std::string lineHeader;
			std::getline(f, lineHeader);
			if (lineHeader[0] == 'v')
			{
				std::vector<double>vec(3);
				int size = lineHeader.length(), i = 0;
				char* str = new char[size + 1], *str2;
				strcpy(str, lineHeader.c_str());
				str2 = strtok(str, " ");
				while (str2 != NULL)
				{
					i++;
					if (i > 1)
						vec[i - 2] = atof(str2) * 50;
					str2 = strtok(NULL, " ");
				}
				verticles.push_back(vec);
				vc++;
			}
			else if (lineHeader[0] == 'f')
			{
				std::vector<int>vec1(3);
				int size = lineHeader.length(), i = 0;
				char* str3 = new char[size + 1], *str4;
				strcpy(str3, lineHeader.c_str());
				str4 = strtok(str3, " ");
				while (str4 != NULL)
				{
					i++;
					if (i > 1)
						vec1[i - 2] = atoi(str4);
					str4 = strtok(NULL, " ");
				}
				faces.push_back(vec1);
				vf++;
			}
		}
		f.close();
		size = vf * 3;
		point.resize(size);

		normals.resize(vf);
		std::vector<double>vec2(3);

		for (int i = 0; i < vf; i++)
		{
			vec2[0] = (verticles[faces[i][1] - 1][1] - verticles[faces[i][0] - 1][1])*(verticles[faces[i][2] - 1][2] - verticles[faces[i][0] - 1][2]) - (verticles[faces[i][1] - 1][2] - verticles[faces[i][0] - 1][2])*(verticles[faces[i][2] - 1][1] - verticles[faces[i][0] - 1][1]);
			vec2[1] = (verticles[faces[i][1] - 1][2] - verticles[faces[i][0] - 1][2])*(verticles[faces[i][2] - 1][0] - verticles[faces[i][0] - 1][0]) - (verticles[faces[i][1] - 1][0] - verticles[faces[i][0] - 1][0])*(verticles[faces[i][2] - 1][2] - verticles[faces[i][0] - 1][2]);
			vec2[2] = (verticles[faces[i][1] - 1][0] - verticles[faces[i][0] - 1][0])*(verticles[faces[i][2] - 1][1] - verticles[faces[i][0] - 1][1]) - (verticles[faces[i][1] - 1][1] - verticles[faces[i][0] - 1][1])*(verticles[faces[i][2] - 1][0] - verticles[faces[i][0] - 1][0]);
		
			normals.push_back(vec2);
		}

		

		for (int i = 0, a = 0; i < vf; i++, a += 3)
		{
			point[a].SetPoint(verticles[faces[i][0] - 1][0], verticles[faces[i][0] - 1][1], verticles[faces[i][0] - 1][2]);
			point[a + 1].SetPoint(verticles[faces[i][1] - 1][0], verticles[faces[i][1] - 1][1], verticles[faces[i][1] - 1][2]);
			point[a + 2].SetPoint(verticles[faces[i][2] - 1][0], verticles[faces[i][2] - 1][1], verticles[faces[i][2] - 1][2]);
		}
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
			t = -10;
			SetTimer(hWnd, 1, 10, 0);
			break;
		case VK_RIGHT:
			t = 10;
			SetTimer(hWnd, 1, 10, 0);
			break;
		case VK_UP:
			t = 10;
			SetTimer(hWnd, 2, 10, 0);
			break;
		case VK_DOWN:
			t = -10;
			SetTimer(hWnd, 2, 10, 0);
			break;
		case 0x30:
			t = 10;
			SetTimer(hWnd, 3, 10, 0);
			break;
		case 0x31:
			t = -10;
			SetTimer(hWnd, 3, 10, 0);
			break;
		case 0x32:
			t = 10;
			SetTimer(hWnd, 4, 10, 0);
			break;
		case 0x33:
			t = -10;
			SetTimer(hWnd, 4, 10, 0);
			break;
		case 0x34:
			t = 10;
			SetTimer(hWnd, 5, 10, 0);
			break;
		case 0x35:
			t = -10;
			SetTimer(hWnd, 5, 10, 0);
			break;
		case 0x36:
			t = 10;
			SetTimer(hWnd, 6, 10, 0);
			break;
		case 0x37:
			t = -10;
			SetTimer(hWnd, 6, 10, 0);
			break;

		}
		break;
	}
		
	case WM_KEYUP:
	{
					
		switch (wParam)
		{
		case VK_LEFT:
			t = 0;
			//SetTimer(hWnd, 1, 100, 0);
			KillTimer(hWnd, 1);
			break;
		case VK_RIGHT:
			t = 0;
			//SetTimer(hWnd, 1, 100, 0);
			KillTimer(hWnd, 1);
			break;
		case VK_UP:
			t = 0;
			//SetTimer(hWnd, 2, 100, 0);
			KillTimer(hWnd, 2);
			break;
		case VK_DOWN:
			t = 0;
			//SetTimer(hWnd, 2, 100, 0);
			KillTimer(hWnd, 2);
			break;
		case 0x30:
			t = 0;
			//SetTimer(hWnd, 3, 100, 0);
			KillTimer(hWnd, 3);
			break;
		case 0x31:
			t = 0;
		//	SetTimer(hWnd, 3, 100, 0);
			KillTimer(hWnd, 3);
			break;
		case 0x32:
			t = 0;
			//SetTimer(hWnd, 4, 100, 0);
			KillTimer(hWnd, 4);
			break;
		case 0x33:
			t = 0;
		//	SetTimer(hWnd, 4, 100, 0);
			KillTimer(hWnd, 4);
			break;
		case 0x34:
			t = 0;
			//SetTimer(hWnd, 5, 100, 0);
			KillTimer(hWnd, 5);
			break;
		case 0x35:
			t = 0;
			//SetTimer(hWnd, 5, 100, 0);
			KillTimer(hWnd, 5);
			break;
		case 0x36:
			t = 0;
			//SetTimer(hWnd, 6, 100, 0);
			KillTimer(hWnd, 6);
			break;
		case 0x37:
			t = 0;
			//SetTimer(hWnd, 6, 100, 0);
			KillTimer(hWnd, 6);
			break;
		}
		break;
	}
	case WM_TIMER:
	{
		switch (wParam)
		{
			case(1) : 
			{
				MoveX(t );
				break;
			}
			case(2) : 
			{
				MoveY(t);
				break;
			}
			case(3) : 
			{
				MoveZ(t*50);
				break;
			}
			case(4) : 
			{//rot z
				RotZ(t);
				break;
			}
			case(5) : 
			{//rot y
				RotY(t);
				break;
			}
			case(6) : 
			{//rot x
				RotX(t);
				break;
			}
		}
		InvalidateRect(hWnd, NULL, 1);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		hbmMem = CreateCompatibleBitmap(hdc, win_width, win_height);
		SelectObject(hdcMem, hbmMem);
		SelectObject(hdcMem, hPen);
		FillRect(hdcMem, &rect, hbr);
		SelectObject(hdcMem, hbr1);
		float zm, xn, yn;
		int tek = 0;
		while (tek < size - 3)
		{//connect two points and draw an edge
			
			for (int i = 0; i < 3; i++)   ////trianglering
			{
				zm = yn = xn = 0;
				zm = point[tek + i].z / (float)lens;
				float d = abs(pow(zm + sgn(zm), sgn(zm)));
				point[tek + i].xn = xo + (point[tek + i].x)*d;
				point[tek + i].yn = yo - (point[tek + i].y)*d;

				//p[i].x = point[tek + i].xn;
				//p[i].y = point[tek + i].yn;
				
				if (i == 0)
				{

					MoveToEx(hdcMem, point[tek + i].xn, point[tek + i].yn, NULL);
					
				}
				else if (i == 1)
					LineTo(hdcMem, point[tek + i].xn, point[tek + i].yn);
				else if (i == 2)
				{
					LineTo(hdcMem, point[tek + i].xn, point[tek + i].yn);
					LineTo(hdcMem, point[tek].xn, point[tek].yn);
				}
				
			}
			
			tek += 3;
		}

		BitBlt(hdc, 0, 0, win_width, win_height, hdcMem, 0, 0, SRCCOPY);

		DeleteObject(hbr);
		DeleteObject(hbmMem);
		DeleteObject(hPen);
		DeleteDC(hdcMem);
		DeleteDC(hdc);

		EndPaint(hWnd, &ps);
		break;
	}
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
