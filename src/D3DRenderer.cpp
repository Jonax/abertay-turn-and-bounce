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

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//////////////////////////////////////////////////////////////////////////////////////////
#include "D3DRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//	Methods called by other classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Class constructor.  The function retrieves handles from the main function and
//	initialises the other Direct3D components.  
//////////////////////////////////////////////////////////////////////////////////////////
D3DRenderer::D3DRenderer(HINSTANCE hInstance, HWND hWnd)
{
	// Stores handles to the application instance and window.  
	this->hWnd		= hWnd;
	this->hInstance = hInstance;

	this->Init();	// Initialises the full Direct3D setup.  
}

//	Function to hold the main render loop.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::Render()
{
	MSG msg;				// Holds Win32 event messages

	Timer.SetFrameRate(120);	// Sets the frame rate to 120 frames per second.  

	while (true)			// Until however long the game runs for...
	{
		// If the timer dictates it's time for another frame...
		if (Timer.NextFrame())
		{
			Timer.Reset();	// Reset the timer.  

			// Check to see if any messages are waiting in the queue
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// If the message is for a quit, exit the while loop
				if (msg.message == WM_QUIT)
					return;

				// Otherwise, translate the message and dispatch it to the message handler()
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			this->RenderFrame();		// Renders a frame of the game.  
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//	Methods called from within the class for better organisation of the module.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Function to organise the main initialisation of the game.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::Init()
{
	// Runs the main initialisation from the Direct3D settings class.  If there are any 
	// problems reported, the application exits.  
	if (!Setup.Initialise(this->hInstance, this->hWnd))
		this->Exit();

	// Assuming everything went well though, handles to the Direct3D interface & device are
	// acquired.  
	this->d3d = Setup.GetInterface();
	this->Device = Setup.GetDevice();

	this->SetUpLighting();		// Sets up lighting.  

	Ring = new GameLogic();		// Creates the game logic module.  

	// Creates the initialisation of the font device.  If there are any problems reported, 
	// the application exits.  
	if (!GUI.CreateFont())
		this->Exit();
}

//	Function to set up lighting.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::SetUpLighting()
{
	D3DLIGHT9 Light;						// A struct for a Direct3D light.  

	// Assigns & clears memory for the light.  
    ZeroMemory(&Light, sizeof(Light));

	// Makes a point light of medium grey colour, and a range of 10.0f with a inverse
	// attenuation of 0.5.  
    Light.Type			= D3DLIGHT_POINT;
    Light.Diffuse.r		= 0.5f;
    Light.Diffuse.g		= 0.5f;
    Light.Diffuse.b		= 0.5f;
	Light.Range			= 10.0f;
    Light.Attenuation0	= 0.5f;
    Light.Attenuation1	= 0.0f;
	Light.Attenuation2	= 0.0f;

	// Sets the position of the light at (0, 5, 0).
    D3DVECTOR vecPosition = {0.0f, 5.0f, 0.0f};
    Light.Position = vecPosition;
	
	// Sets the light to #0 and activates it.  
	Device->SetLight(0, &Light);
    Device->LightEnable(0, true);
}

//	Function to render a frame.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::RenderFrame()
{
	this->ClearBuffers();	// Clears the buffers.  

	Device->BeginScene();	// Starts rendering the 3D scene.  

		this->SetView();		// Sets the viewpoint matrix.  
		this->SetProjection();	// Sets the projection matrix.  

		// Renders the scene via the game logic system.  If reported to do so, exit from
		// the game.  
		if (!Ring->Render())
			this->Exit();

		// Renders the score onto the screen.  
		GUI.RenderScore(Ring->GetLevel(), Ring->GetScore());

	Device->EndScene();		// Ends rendering the 3D scene.  

	Device->Present(NULL, NULL, NULL, NULL);    // Displays the created frame.

	// Checks for input from the keyboard & mouse.  
	this->CheckKeyInput();
	this->CheckMouseInput();
}

//	Function to clear the buffers to specific colours.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::ClearBuffers()
{
	// Clears the background, depth & stencil buffers respectively.  
	Device->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND, 1.0f, 0);
	Device->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	Device->Clear(0, 0, D3DCLEAR_STENCIL, 0xfffffff, 1.0f, 0);
}

//	Function to set the viewpoint matrix.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::SetView()
{
	D3DXMATRIX Viewpoint;		// The viewpoint matrix.  

	// Sets the matrix with...
	D3DXMatrixLookAtLH(	&Viewpoint,
						&D3DXVECTOR3 (0.0f, 1.0f, -5.0f),	// The camera's position.
						&D3DXVECTOR3 (0.0f, 0.0f,  0.0f),	// The camera's focal point.
						&D3DXVECTOR3 (0.0f, 1.0f,  0.0f));	// The camera's up vector.  

	// Uploads the viewpoint matrix.  
	Device->SetTransform(D3DTS_VIEW, &Viewpoint);
}

//	Function to set the projection matrix.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::SetProjection()
{
	D3DXMATRIX Projection;		// The projection matrix.  

	// Sets the matrix with...
	D3DXMatrixPerspectiveFovLH(	&Projection,
								D3DXToRadian(75),		// FOV of 75 degrees
								Setup.GetAspectRatio(),	// The aspect ratio
								1.0f,					// The near view-plane
								10.0f);					// The far view-plane

	// Uploads the viewpoint matrix.  
	Device->SetTransform(D3DTS_PROJECTION, &Projection);
}

//	Function to check for key input.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::CheckKeyInput()
{
	// Gets a pointer to the keyboard device.  
	IDirectInputDevice8* Keyboard = Setup.GetKeyboard();

	static BYTE KeyState[256];	// Creates a static storage for the key states.

	Keyboard->Acquire();		// Acquires access if not already possessed.  
	// Fills the storage with the input flags.  
	Keyboard->GetDeviceState(256, (LPVOID)KeyState);

	// If left or right arrow keys are pressed, move the ring.  
	if (KEY_PRESSED(DIK_LEFT) || KEY_PRESSED(DIK_A))
		Ring->Rotate(-0.05f);
	if (KEY_PRESSED(DIK_RIGHT) || KEY_PRESSED(DIK_D))
		Ring->Rotate( 0.05f);
	// Otherwise, exit is Escape key is pressed.  
	if (KEY_PRESSED(DIK_ESCAPE))
		this->Exit();
}

//	Function to check for mouse movement & input.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::CheckMouseInput()
{
	// Gets a pointer to the mouse device.  
	IDirectInputDevice8* Mouse = Setup.GetMouse();

	static DIMOUSESTATE mousestate;    // Creates a static storage for the mouse states.

	Mouse->Acquire();			// Acquires access if not already possessed.  
	// Fills the storage with the input flags.  
	Mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mousestate);

	// Rotates the ring based on how much the mouse has moved since the last frame.  
	Ring->Rotate(0.01f * mousestate.lX);
}

//	Function to exit the application.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DRenderer::Exit()
{
	// Sends the message to the Win32 handler to exit.
	PostQuitMessage(0);
}