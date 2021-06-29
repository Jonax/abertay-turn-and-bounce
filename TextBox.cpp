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

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//////////////////////////////////////////////////////////////////////////////////////////
#include "TextBox.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//	Methods called by other classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Class constructor.  When initialised, necessary data is added into the text box.  
//	Parameters denote the dimensions of the text box, and the alignment & colour of the
//	text box.  
//////////////////////////////////////////////////////////////////////////////////////////
TextBox::TextBox(int xl, int xr, int yt, int yb, DWORD Alignment, D3DCOLOR Colour)
{
	// Sets the parameters of the text box.  
	Box.left = xl;		// x-value for the left side of the box.  
	Box.right = xr;		// x-value for the right side of the box.  
	Box.top = yt;		// y-value for the top side of the box.  
	Box.bottom = yb;	// y-value for the bottom side of the box.  

	this->Alignment = Alignment;	// Sets the alignment of the text box.  
	this->Colour = Colour;			// Sets the colour of the text.  
}

//	Function to draw a string onto the screen using the text box's values.  
//////////////////////////////////////////////////////////////////////////////////////////
void TextBox::Render(ID3DXFont* FontDevice, LPCTSTR String)
{
	// Draws the text.  
	FontDevice->DrawText(	NULL,			// A HDC is not required.  
							String,			// The text to render.
							-1,				// String length is automatically calculated.  
							&this->Box,		// Drawn with the class box's dimensions.  
							this->Alignment,// Text is aligned as previously set.   
							this->Colour);	// Text is coloured as previously set.  
}

//	Function to draw an integer value onto the screen using the text box's values.  
//////////////////////////////////////////////////////////////////////////////////////////
void TextBox::Render(ID3DXFont* FontDevice, int n)
{
	char string[3];				// Temporary string for converting the value to a string.  

	sprintf(string, "%d", n);	// Prints the value to the temporary string.  

	// Draws the text.  
	FontDevice->DrawText(	NULL,			// A HDC is not required.  
							string,			// The text to render.
							-1,				// String length is automatically calculated.  
							&this->Box,		// Drawn with the class box's dimensions.  
							this->Alignment,// Text is aligned as previously set.   
							this->Colour);	// Text is coloured as previously set.  
}