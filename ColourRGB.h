//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	RGB COLOUR CLASS MODULE																//
//	The datatype class to handle seperate values for a RGB-based colour.  This class	//
//	was created due to an issue with Direct3D's given D3DCOLOR structure (namely		//
//	retrieving the seperate components after storing them).								//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef _COLOURRGB_H_
#define _COLOURRGB_H_

class ColourRGB
{
	public:
		ColourRGB(float r, float g, float b);		// Class constructor.  

		float r, g, b;
};

#endif