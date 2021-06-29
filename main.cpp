//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	APPLICATION ROOT FILE																//
//	The root of the rest of the program.  Most of the code is code that could not be	//
//	added to the Win32 class for one reason or another.									//
//////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>		// Standard Win32 library.  
#include "Defines.h"		// Library for the project's definitions & macros.  
#include "Win32.h"			// Win32 window module.  
#include "D3DRenderer.h"	// Direct3D Renderer module.  

// Message Handler.  
//////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Sends the input to the dedicated message handler in the Win32 class.  
	return Win32.MessageHandler(hWnd, message, wParam, lParam);
}

// Function to create the Win32 window.  
//////////////////////////////////////////////////////////////////////////////////////////
void CreateTheWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc;		// Struct for the window class.  

	// Assigns and clears out memory for the window class to use.  
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Fills in the struct with the required information.  
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.hInstance		= hInstance;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName	= CLASS_NAME;

	// Registers the window class.  
	RegisterClassEx(&wc);
}

// Main Application Function.  
//////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CreateTheWindow(hInstance);		// Creates the application's window class.  

	// Initialises the window and returns a handle for it.  
	HWND hWnd = Win32.InitialiseWindow(SCREEN_WIDTH, SCREEN_HEIGHT, hInstance, nCmdShow);

	// Creates the renderer object and sends to the class handles for the application's instance
	// and window.  
	D3DRenderer Direct3D(hInstance, hWnd);

	Direct3D.Render();		// Starts off the render loop.  Will not leave it until the renderer
							// decides to bail out.  

	return WM_QUIT;			// Returns a quit message for when the application is finished.  
}