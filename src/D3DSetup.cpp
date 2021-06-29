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

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//////////////////////////////////////////////////////////////////////////////////////////
#include "D3DSetup.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	SINGLETON INITIALISATION
//////////////////////////////////////////////////////////////////////////////////////////
D3DSetup D3DSetup_SingletonInit();		// Initialises the singleton instance.  

//////////////////////////////////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//	Methods called by other classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Class constructor.  Due to the various checks performed, the initialisation of 
//	various components is called from another function.  As a result, this singleton is
//	left empty.  
//////////////////////////////////////////////////////////////////////////////////////////
D3DSetup::D3DSetup()
{
}

//	Class destructor.  Removes all remaining Direct3D devices - Very important for
//	preventing memory leaks during application termination.  
//////////////////////////////////////////////////////////////////////////////////////////
D3DSetup::~D3DSetup()
{
	// Makes sure the keyboard device no longer exists.
	if (this->Keyboard)			// If the device still exists...
		Keyboard->Unacquire();	// Unacquires the device.  

	// Makes sure the mouse device no longer exists.
	if (this->Mouse)			// If the device still exists...
		Mouse->Unacquire();		// Unacquires the device.  

	// Makes sure the DirectInput device no longer exists.
	if (this->DInput)			// If the device still exists...
		DInput->Release();		// Releases the device.  

	// Makes sure the Direct3D device no longer exists.
	if (this->Device)			// If the device still exists...
		Device->Release();		// Releases the device.  

	// Makes sure the Direct3D interface no longer exists.
	if (this->Direct3D)			// If the device still exists...
		Direct3D->Release();	// Releases the interface.  
}

//	Function to set the status of the stencil buffer.  
//////////////////////////////////////////////////////////////////////////////////////////
bool D3DSetup::Initialise(HINSTANCE hInstance, HWND hWnd)
{
	// Stores the parameters into the assigned pointers for later use in functions
	// requiring the handles.  
	this->hInstance	= hInstance;
	this->hWnd		= hWnd;

	// Sets up the Direct3D interface.  If the creation of the interface fails for some
	// reason, the function throws an error message and reports to the renderer that the 
	// application's initialisation ran into a problem.  
	if (!this->SetInterface())
	{
		MessageBox(0, ERROR_INTERFC_MSG, ERROR_INTERFC_TTL, 0);
		return false;
	}

	this->SetVertexProcessing();	// Sets the required mode for vertex processing.  
	this->LoadParameters();			// Loads the parameters for the Direct3D device.  
	
	// Sets up the Direct3D interface.  If the creation of the interface fails for some
	// reason, the function throws an error message and reports to the renderer that the 
	// application's initialisation ran into a problem.  
	if (!this->SetDevice())
	{
		MessageBox(0, ERROR_DEVICE_MSG, ERROR_DEVICE_TTL, 0);
		return false;
	}

	this->SetInput();				// Sets up the various devices for DirectInput.  
	this->SetZBuffer();				// Sets up the Z-Buffer.  
	this->SetRenderStates();		// Sets up various states for Direct3D rendering.  

	// If everything was initialised and created with no problems, report the result to the
	// renderer.  
	return true;
}

//	Function to handle the status of the stencil buffer at a given moment.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DSetup::ActiveStencilBuffer(bool active)
{
	// Sets the stencil buffer as stated in the parameter boolean (e.g. true->true)
	Device->SetRenderState(D3DRS_STENCILENABLE, active);
	// Sets the Z-Buffer to the opposite state of the stencil buffer (e.g. true->false)
	Device->SetRenderState(D3DRS_ZENABLE, !active);
}

//	Function to acquire a pointer to the Direct3D interface.  
//////////////////////////////////////////////////////////////////////////////////////////
IDirect3D9* D3DSetup::GetInterface()
{
	return this->Direct3D;
}

//	Function to acquire a pointer to the Direct3D device.  
//////////////////////////////////////////////////////////////////////////////////////////
IDirect3DDevice9* D3DSetup::GetDevice()
{
	return this->Device;
}

//	Function to acquire a pointer to the given aspect ratio.  
//////////////////////////////////////////////////////////////////////////////////////////
float D3DSetup::GetAspectRatio()
{
	return (Display.Width / Display.Height);
}

//	Function to acquire a pointer to the keyboard input device.  
//////////////////////////////////////////////////////////////////////////////////////////
IDirectInputDevice8* D3DSetup::GetKeyboard()
{
	return this->Keyboard;
}

//	Function to acquire a pointer to the mouse input device.  
//////////////////////////////////////////////////////////////////////////////////////////
IDirectInputDevice8* D3DSetup::GetMouse()
{
	return this->Mouse;
}

//////////////////////////////////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//	Methods called from within the class for better organisation of the module.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Function to set up the Direct3D interface.  
//////////////////////////////////////////////////////////////////////////////////////////
bool D3DSetup::SetInterface()
{
	// Creates the Direct3D interface based on the version of the DirectX SDK used for
	// compiling.  
	this->Direct3D = Direct3DCreate9(D3D_SDK_VERSION);

	// Returns the result of creating the interface; if it wasn't successful, it will 
	// report as such.  
	return (this->Direct3D);
}

//	Function to load in the necessary parameters for the Direct3D renderer.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DSetup::LoadParameters()
{
	// Gets the used display mode from the adapter.  
	Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &this->Display);

	// Assigns & clears out the required memory for the parameters struct.  
	ZeroMemory(&this->D3DPara, sizeof(this->D3DPara));

	// Assigns the required parameters for the Direct3D renderer.  
	// Windowed/fullscreen is set in Defines.h
	D3DPara.Windowed				= WINDOWED;
	// Backbuffer dimensions are set by the adapter.  
	D3DPara.BackBufferFormat		= Display.Format;
	D3DPara.BackBufferWidth			= Display.Width;
	D3DPara.BackBufferHeight		= Display.Height;
	// Old buffer frames are discarded and overwritten.  
	D3DPara.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	// Sets the device window to that of the Win32 window.  
	D3DPara.hDeviceWindow			= this->hWnd;
	// Enables stencil buffering and sets the format to be decided in Defines.h
	D3DPara.EnableAutoDepthStencil	= true;
	D3DPara.AutoDepthStencilFormat	= STENCIL_FORMAT;
}

//	Function to create & set up the Direct3D device.  
//////////////////////////////////////////////////////////////////////////////////////////
bool D3DSetup::SetDevice()
{
	// create a device class using this information and information from the D3DPara stuct
	Direct3D->CreateDevice(	D3DADAPTER_DEFAULT,	// Device uses the default graphics card.  
							D3DDEVTYPE_HAL,		// Uses HAL for processing the graphics.  
							this->hWnd,			// Draws to the Win32 window.  
							this->vp_mode,		// Sets vertex processing mode to decided.  
							&this->D3DPara,		// Adds previously-set dimensions.  
							&this->Device);		// Gives pointer to the new device.  

	// Returns the result of creating the device; if it wasn't successful, it will report 
	// as such.  
	return (this->Device);
}

//	Function to set the required mode for vertex processing based on the available
//	hardware.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DSetup::SetVertexProcessing()
{
	D3DCAPS9 caps;	// Stores the capabilities of the available hardware.  

	// Gets the capabilities of the available hardware based on using the default graphics
	// card and Hardware Abstraction Layer.  
	Direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	// If the graphics hardware shows it can handle T&L (Transform & Lighting)...
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		// Then set vertex processing to be done in hardware mode.  
		this->vp_mode = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		// However, if it can't - set vertex processing to be use software emulation.  
		this->vp_mode = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
}

//	Function to set the Depth & Stencil buffer in one function.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DSetup::SetZBuffer()
{
	// Creates the depth & stencil buffer.  
	Device->CreateDepthStencilSurface(	Display.Width,		// Buffer is same size as window.  
										Display.Height,
										STENCIL_FORMAT,		// Determined in Defines.h
										D3DMULTISAMPLE_NONE,// No multisampling.  
										0,					// No multisampling quality.  
										true,				// Discards old buffer data
										&this->ZBuffer,		// Pointer for the buffer.  
										NULL);
}

//	Function to set the miscellaneous states of rendering.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DSetup::SetRenderStates()
{
	Device->SetRenderState(D3DRS_LIGHTING,			true);	// Turns on lighting.  
	// Sets the ambience to a lowish grey colour.  
    Device->SetRenderState(D3DRS_AMBIENT,			D3DCOLOR_XRGB(50, 50, 50));
	// Culls counter-clockwise primitives.  
	Device->SetRenderState(D3DRS_CULLMODE,			D3DCULL_CCW);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE,	true);	// Turns alpha blending on.  

	this->SetStencilBuffer();			// Sets up the stencil buffer.  
	this->ActiveStencilBuffer(false);	// Marks drawing to the stencil buffer as off.  
}

//	Function to set the miscellaneous states of rendering.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DSetup::SetStencilBuffer()
{
	// Used for blending.  Sets the source blend as the alpha value and the destination
	// blend as the negative alpha.  
	Device->SetRenderState(D3DRS_SRCBLEND,			D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND,			D3DBLEND_INVSRCALPHA);

	// Sets the various states for drawing to the stencil buffer.  
	Device->SetRenderState(D3DRS_STENCILFUNC,		D3DCMP_EQUAL);
    Device->SetRenderState(D3DRS_STENCILREF,		0x0);
    Device->SetRenderState(D3DRS_STENCILMASK,		0xffffffff);
    Device->SetRenderState(D3DRS_STENCILWRITEMASK,	0xffffffff);
    Device->SetRenderState(D3DRS_STENCILZFAIL,		D3DSTENCILOP_KEEP);
    Device->SetRenderState(D3DRS_STENCILFAIL,		D3DSTENCILOP_KEEP);
    Device->SetRenderState(D3DRS_STENCILPASS,		D3DSTENCILOP_INCR);
}

//	Function to create & set up the various DirectInput devices.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DSetup::SetInput()
{
	// Creates the DirectInput interface.  
    DirectInput8Create(	this->hInstance,		// The handle to the application.
						DIRECTINPUT_VERSION,    // The latest compatible version.
						IID_IDirectInput8,		// The DirectInput interface version (DX8).
						(void**)&this->DInput,	// The pointer to the interface.
						NULL);

	// Creates the keyboard device. 
    DInput->CreateDevice(	GUID_SysKeyboard,	// The default keyboard is used/
							&this->Keyboard,	// The pointer to the device.
							NULL);
	Keyboard->SetDataFormat(&c_dfDIKeyboard);	// Sets the device's format to keyboard data.  

	// Creates the mouse device
    DInput->CreateDevice(	GUID_SysMouse,		// The default mouse is used
							&this->Mouse,		// The pointer to the device.  
							NULL);
	Mouse->SetDataFormat(&c_dfDIMouse);			// Sets the device's format to mouse data.  

    // Sets the control the devices have over the keyboard & mouse.  
    Keyboard->SetCooperativeLevel	(this->hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	Mouse->SetCooperativeLevel		(this->hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

    Mouse->Acquire();	// Acquires the mouse the only time necessary.  
}