#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

extern "C" {
#include "../WOLFSRC/WL_MAIN.H"
}

// Strings:
static const TCHAR* szTitle			= TEXT( "Wolfenstein VR" );
static const TCHAR* szWindowClass	= TEXT( "Wolfenstein VR Window" );

// Declaration of main window functions:
static HWND	CreateMainWindow( HINSTANCE hInstance, int nCmdShow );
static LRESULT CALLBACK	MainWindowProc(HWND, UINT, WPARAM, LPARAM);


////////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	MSG msg = {0};
	int res = 0;

	// Perform application initialization:
	HWND hWnd = CreateMainWindow( hInstance, nCmdShow );
	if( !hWnd )
	{
		return -1;
	}

	// Init game.
	InitWolf( );

	// Main message loop:
	while( true )
	{
		bool quit = false;

		while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if( msg.message == WM_QUIT )
			{
				quit = true;
				res = (int) msg.wParam;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		if( quit )
			break;

		// Update game.
		UpdateWolf( );

		// Quit if game is down.
		if( WolfIsDone() )
		{
			res = -1;
			break;
		}
	}

	const char* errorStr = GetWolfErrorString();
	if( errorStr )
	{
		MessageBoxA( NULL, errorStr, "Wolfenstein VR Error", MB_OK );
	}

	// Shutdown game.
	ShutdownWolf( );

	return res;
}

////////////////////////////////////////////////////////////////////////////////////////////
HWND CreateMainWindow( HINSTANCE hInstance, int nCmdShow )
{
	// Register Class Definition.
	WNDCLASSEX wcex = {0};
	wcex.cbSize = sizeof( wcex );

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= MainWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	//wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NEWWINPROJ));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszClassName	= szWindowClass;
	//wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if( !RegisterClassEx( &wcex ) )
		return NULL;

	// Create window with class.
	HWND hWnd = CreateWindow( szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL );

	if( hWnd )
	{
		ShowWindow( hWnd, nCmdShow );
		UpdateWindow( hWnd );
	}

	return hWnd;
}

LRESULT CALLBACK MainWindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
		//case WM_PAINT:
		//{
		//	PAINTSTRUCT ps;
		//	HDC hdc = BeginPaint(hWnd, &ps);

		//	// TODO: Add any drawing code here...

		//	EndPaint(hWnd, &ps);
		//}
		//return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}