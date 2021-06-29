//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	WIN32 WINDOW MODULE																	//
//	Class used handling the Win32 window.												//
//////////////////////////////////////////////////////////////////////////////////////////
#include "Win32.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	SINGLETON INITIALISATION
//////////////////////////////////////////////////////////////////////////////////////////
Wind32 Wind32_SingletonInit;		// Initialises the singleton instance.  

// Class constructor.  
//////////////////////////////////////////////////////////////////////////////////////////
Wind32::Wind32()
{
}

// Function to initialise the Win32 window.  
//////////////////////////////////////////////////////////////////////////////////////////
HWND Wind32::InitialiseWindow(int w, int h, HINSTANCE instance, int nCmdShow)
{
	// Creates the Win32 window and uses the result as the handle.  
	HWND hWndTemp = CreateWindowEx(	NULL,
									CLASS_NAME, 
									WINDOW_NAME, 
									WS_OVERLAPPEDWINDOW, 
									0, 0,			// Starting x-y position of the window.  
									w, h,			// Size of the window.  
									NULL,			// No parent window.
									NULL,			// Not using menus
									instance,		// Application's handle
									NULL);

	// Displays the window on the screen.  
	ShowWindow(hWndTemp, nCmdShow);

	return hWndTemp;
}

// Function that acts as the application's message handler.  
//////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK Wind32::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	this->ProcessInput(message);		// Sends the message on.  

	// Handles any messages the ProcessInput function didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Function that processes the Win32-specific input of the window.  
//////////////////////////////////////////////////////////////////////////////////////////
void Wind32::ProcessInput(UINT message)
{
	switch (message)
	{
		// If the DESTROY message is called, send the Quit Message.  
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
	}
}