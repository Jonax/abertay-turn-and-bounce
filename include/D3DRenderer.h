//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	DIRECT3D RENDERER MODULE															//
//	Main class for handling the application's rendering via Direct3D.					//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef _D3DRENDERER_H_
#define _D3DRENDERER_H_

//////////////////////////////////////////////////////////////////////////////////////////
//	LIBRARY INCLUDES
//	The libraries & namespaces required for the module.  
//////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>	// Standard Win32 library.  
#include <d3d9.h>		// Main library for DirectX 9.0c functionality.  
#include <d3dx9.h>		// Extended library for DirectX 9.0c functionality.  
#include <dinput.h>		// Main library for DirectInput 8.0 functionality.  
#include "Defines.h"	// Library for the project's definitions & macros.  
#include "D3DSetup.h"	// Direct3D settings class.  
#include "GameLogic.h"	// Game Logic class.  
#include "GUI.h"		// GUI management class.  
#include "Timer.h"		// Timer class.  

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//	Declaration of all required class methods and data.  The code for the methods is 
//	detailed in the module's source file.  
//////////////////////////////////////////////////////////////////////////////////////////
class D3DRenderer
{
	public:
		D3DRenderer(HINSTANCE hInstance, HWND hWnd);	// Class constructor.  

		void Render();									// Main render loop.  

	private:
		// Startup functions, run once during initialisation.  
		void Init();				// Main initialisation function.  
		void SetUpLighting();		// Sets up lighting.  

		// Functions for assisting rendering, called for each frame.  
		void RenderFrame();			// Renders a frame.  
		void ClearBuffers();		// Clears the necessary buffers.  
		void SetView();				// Sets the viewport matrix.  
		void SetProjection();		// Sets the projection matrix.  
		void CheckKeyInput();		// Reads keyboard input.  
		void CheckMouseInput();		// Reads mouse input.  

		void Exit();				// Exits the game completely.  

		HINSTANCE hInstance;		// Handle to the application instance.  
		HWND hWnd;					// Handle to the Win32 window.  

		D3DSetup Setup;				// Direct3D settings object.  
		GameLogic* Ring;			// Game logic object.  
		GUISystem GUI;				// GUI object.  

		IDirect3D9*			d3d;	// A pointer to the Direct3D interface.  
		IDirect3DDevice9*	Device;	// A pointer to the Direct3D device.  

		Timer				Timer;	// Timer management object.  
};

#endif