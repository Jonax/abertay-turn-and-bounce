//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	GRAPHICAL USER INTERFACE MODULE														//
//	The primary class for the GUI system.  The module handles the rendering of dynamic	//
//	text onto the screen.																//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//////////////////////////////////////////////////////////////////////////////////////////
#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//	Methods called by other classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Class constructor.  The function creates the necessary text boxes, ready for 
//	rendering into each.  
//////////////////////////////////////////////////////////////////////////////////////////
GUISystem::GUISystem()
{
	// Creates a text box to render the current level.  The box is placed in the upper-
	// right corner of the screen, and writes right-aligned white text.  
	Level = new TextBox(0, 1270, 10, 34, 
						DT_RIGHT, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	// Creates a text box to render the current score.  The box is placed in the upper-
	// right corner of the screen below the level text box , and writes right-aligned 
	// white text.  
	Score = new TextBox(0, 1270, 40, 64, DT_RIGHT, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));
}

//	Function to create the font device for the GUI.  
//////////////////////////////////////////////////////////////////////////////////////////
bool GUISystem::CreateFont()
{
	// Create the font.

	// Here is where we create the font using a function called D3DXCreateFont().
	// The prototype for D3DXCreateFont() is...
	HRESULT hr = D3DXCreateFont(Settings.GetDevice(),			// Device for Direct3D.  
								24,								// Text height of 24px.  
								0,								// Width is auto-sized.  
								FW_NORMAL,						// Normal font weight.  
								1,								// One mipmap for all text.
								0,								// No italics.  
								DEFAULT_CHARSET,				// Default character set.  
								OUT_DEFAULT_PRECIS,				// Default precision.  
								ANTIALIASED_QUALITY,			// Text is anti-aliased.  
								DEFAULT_PITCH | FF_DONTCARE,	// Default pitch settings.  
								PROJECT_FONT,					// Uses Tahoma text.  
								&this->Font);					// Maps to the font device.  
	
	// If the font device failed to be created, throw out an error.  
	if (FAILED(hr))
	{
		// Sends the error message to the user.  
		MessageBox(0, ERROR_FONTDEV_MSG, ERROR_FONTDEV_TTL, 0);
		return false;		// Report to the renderer the font device creation failed.  
	}
	
	// If all went well, report to the renderer the font device was successfully created.  
	return true;
}

//	Function to render the current score to the screen.  
//////////////////////////////////////////////////////////////////////////////////////////
void GUISystem::RenderScore(int level, int score)
{
	// Renders the current level to its assigned text box.  
	Level->Render(this->Font, level);

	char string[12];			// Temporary string for converting the values to a string.  
	sprintf(string, "%d / %d", score, level);	// Prints the value to the temporary string.

	// Renders the current progress to its assigned text box.  
	Score->Render(this->Font, string);
}