//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	TEXT BOX CLASS MODULE																//
//	The datatype class to handle a text box.  The class is used to handle the settings	//
//	of each text box, as well as managing the rendering of the box with the Direct3D	//
//	renderer.																			//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

//////////////////////////////////////////////////////////////////////////////////////////
//	LIBRARY INCLUDES
//	The libraries & namespaces required for the module.  
//////////////////////////////////////////////////////////////////////////////////////////
#include <d3dx9.h>		// Extended library for DirectX 9.0c functionality.  
#include <stdio.h>		// Standard I/O library.  

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//	Declaration of all required class methods and data.  The code for the methods is 
//	detailed in the module's source file.  
//////////////////////////////////////////////////////////////////////////////////////////
class TextBox
{
	public:
		// Class constructor that fills in the data stored in the class.  
		TextBox(int xl, int xr, int yt, int yb, DWORD Alignment, D3DCOLOR Colour);

		// Functions to render text onto the screen.  
		void Render(ID3DXFont* FontDevice, LPCTSTR String);	// Renders a string.
		void Render(ID3DXFont* FontDevice, int n);			// Renders an integer value.  

	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS OBJECTS
	//////////////////////////////////////////////////////////////////////////////////////
	private:
		RECT		Box;		// Rectangular object to store the box's dimensions.  
		DWORD		Alignment;	// The alignment of the text in the box.  
		D3DCOLOR	Colour;		// Colour of the box's text stored in a DWORD.  
};

#endif