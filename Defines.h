//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	PROJECT DEFINES																		//
//	A central collection of macros & definitions to make changes to static values		//
//	without having to spend valuable development time searching for values within the	//
//	code.																				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	COMPILE SETTINGS
//	Settings for optimising the build's compile stage.  
//////////////////////////////////////////////////////////////////////////////////////////
#define WIN32_MEAN_AND_LEAN		// Unnecessary Win32 headers are ignored during compile.  

//////////////////////////////////////////////////////////////////////////////////////////
//	WIN32 SETTINGS
//	Settings specific to the Win32 code and the main window.  
//////////////////////////////////////////////////////////////////////////////////////////
#define WINDOW_NAME			"Turn And Bounce Prototype"	// Caption for the window.  
#define CLASS_NAME			"TABClass"					// Name of the window's class.

//////////////////////////////////////////////////////////////////////////////////////////
//	WIN32 SETTINGS
//	Settings specific to the Win32 code and the main window.  
//////////////////////////////////////////////////////////////////////////////////////////
// Settings to establish a 1024 x 768 window.  
#define SCREEN_WIDTH		1024
#define SCREEN_HEIGHT		768

// Handles whether the window is windowed or fullscreen.  It is currently set to 
// fullscreen but it is possible to comment the FULLSCREEN flag below.  
//#define FULLSCREEN
#ifdef FULLSCREEN
	#define WINDOW_STYLE	WS_EX_TOPMOST | WS_POPUP,    // fullscreen values
	#define WINDOWED		false
#else
	#define WINDOW_STYLE	WS_OVERLAPPEDWINDOW
	#define WINDOWED		true
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//	DIRECT3D SETTINGS
//	Settings specific to the Direct3D renderer.  
//////////////////////////////////////////////////////////////////////////////////////////
#define BACKGROUND			D3DCOLOR_XRGB(0, 0, 0)	// Makes the background black.  

// Sets the buffer to 24-bit depth, 8-bit stencil.
#define STENCIL_FORMAT		D3DFMT_D24S8

#define PROJECT_FONT		"Tahoma"

//////////////////////////////////////////////////////////////////////////////////////////
//	DIRECTINPUT SETTINGS
//	Settings specific to the DirectInput systems.  
//////////////////////////////////////////////////////////////////////////////////////////
// A macro to simplify the check for whether a specific key is pressed.  id is the ID of
// the key in question.  
#define KEY_PRESSED(id)		(KeyState[id] & 0x80)

//////////////////////////////////////////////////////////////////////////////////////////
//	PROTOTYPE SETTINGS
//	Various values and macros used in calculations and comparisons in the prototype's game
//	logic.  
//////////////////////////////////////////////////////////////////////////////////////////
// The value of pi to a fairly accurate degree.  
#define PI					3.1415926535897932384626433832795f
#define	SPLIT_SIX			(PI / 3)	// The angular length of each ring block in radians.  

//////////////////////////////////////////////////////////////////////////////////////////
//	PROTOTYPE SETTINGS
//	Various values and macros used in calculations and comparisons in the prototype's game
//	logic.  
//////////////////////////////////////////////////////////////////////////////////////////
// Error messages.  The actual captions are fairly self-explanatory as to what each is for.
#define ERROR_DEVICE_MSG	"Unable to create Direct3D device."
#define ERROR_FONTDEV_MSG	"Unable to create Direct3D font device."
#define ERROR_INTERFC_MSG	"Unable to create Direct3D interface."

// Captions for error windows.  The actual captions are fairly self-explanatory as to what 
// each is for.
#define ERROR_DEVICE_TTL	"CreateDevice() Failed"
#define ERROR_FONTDEV_TTL	"D3DXCreateFont() Failed"
#define ERROR_INTERFC_TTL	"Direct3DCreate9() Failed"



#define GRAV_INCREASE	0.1f
#define LAUNCH_VELOCITY	5.0f
#define SCALE			0.01f
#define BASE_Z			0.2f

#define INITIAL_GRAVITY	0.1f

#define NUM_BLOCKS		6
#define NUM_COLOURS		6