//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	DIRECT3D SETTINGS MODULE															//
//	Class for organising the startup of the Direct3D game as well as the lookup of		//
//	various devices used by other classes.												//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef _D3DSETUP_H_
#define _D3DSETUP_H_

//////////////////////////////////////////////////////////////////////////////////////////
//	LIBRARY INCLUDES
//	The libraries & namespaces required for the module.  
//////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>	// Standard Win32 library.  
#include <d3d9.h>		// Main library for DirectX 9.0c functionality.  
#include <dinput.h>		// Main library for DirectInput 8.0 functionality.  
#include "Defines.h"	// Library for the project's definitions & macros.  
#include "Singleton.h"	// Singleton class.  

//////////////////////////////////////////////////////////////////////////////////////////
//	MODULE DEFINES
//	Simplifies the call for the module.  
//////////////////////////////////////////////////////////////////////////////////////////
#define Settings	D3DSetup::GetSingleton()

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//	Declaration of all required class methods and data.  The code for the methods is 
//	detailed in the module's source file.  
//////////////////////////////////////////////////////////////////////////////////////////
class D3DSetup : public CSingleton <D3DSetup>
{
	public:
		D3DSetup();		// Class constructor.  
		~D3DSetup();	// Class destructor.  

		// Initialises all of the Direct3D elements for the application.  
		bool Initialise(HINSTANCE hInstance, HWND hWnd);
		// Sets the active state for drawing to the stencil buffer.  
		void ActiveStencilBuffer(bool active);

		// Various functions to get pointers to necessary items.  
		IDirect3D9*				GetInterface();		// Gets the Direct3D interface.  
		IDirect3DDevice9*		GetDevice();		// Gets the Direct3D device.  
		float					GetAspectRatio();	// Gets the aspect ratio.  
		IDirectInputDevice8*	GetKeyboard();		// Gets the device for keyboard input.  
		IDirectInputDevice8*	GetMouse();			// Gets the device for mouse input.  

	private:
		bool SetInterface();		// Sets up the Direct3D interface.
		bool SetDevice();			// Sets up the Direct3D device.

		void LoadParameters();		// Loads up the parameters for the Direct3D renderer.  

		void SetVertexProcessing();	// Sets up the mode for vertex processing.  
		void SetZBuffer();			// Sets up the Z Buffer.  
		void SetStencilBuffer();	// Sets up the Stencil Buffer.  
		void SetRenderStates();		// Sets up the needed render states.  
		void SetInput();			// Sets up the DirectInput devices.  

	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS OBJECTS
	//////////////////////////////////////////////////////////////////////////////////////
		HINSTANCE				hInstance;	// A handle for the Win32 instance.  
		HWND					hWnd;		// A handle for the Win32 window.  

		D3DPRESENT_PARAMETERS	D3DPara;	// Holds the various device information.  
		D3DDISPLAYMODE			Display;	// Holds details on the display mode.  

		IDirect3DSurface9*		ZBuffer;	// A pointer to the z-buffer.  
		IDirect3DDevice9*		Device;		// A pointer to the Direct3D device.  
		IDirect3D9*				Direct3D;	// A pointer to the Direct3D interface.  

		IDirectInput8*			DInput;		// A pointer to the DirectInput interface.  
		IDirectInputDevice8*	Keyboard;	// A pointer to the keyboard device.  
		IDirectInputDevice8*	Mouse;		// A pointer to the mouse device

	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS DATA
	//////////////////////////////////////////////////////////////////////////////////////
		int						vp_mode;	// Holds the mode for vertex processing.  
};

#endif