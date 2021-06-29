//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	BALL CLASS MODULE																	//
//	The datatype class to handle the game's ball.  The class is derived from the		//
//	Direct3D mesh class and also includes extra data & functions specific to the ball.	//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MESHBALL_H_
#define _MESHBALL_H_

//////////////////////////////////////////////////////////////////////////////////////////
//	LIBRARY INCLUDES
//	The libraries & namespaces required for the module.  
//////////////////////////////////////////////////////////////////////////////////////////
#include "Defines.h"	// Library for the project's definitions & macros.  
#include "D3DMesh.h"	// Direct3D Mesh datatype class.  

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//	Declaration of all required class methods and data.  The code for the methods is 
//	detailed in the module's source file.  
//////////////////////////////////////////////////////////////////////////////////////////
class BallMesh : public D3DMesh
{
	public:
		BallMesh();					// Class constructor.  

		// Functions to handle the ball's rendering.  
		void Render();				// Renders the model onto the screen.  
		void RenderShadow();		// Renders the ball's shadow via the stencil buffer.  

		// Functions to modify the ball's behaviour.  
		void Bounce();				// Launches the ball into the air again.  
		void ChangeGravity();		// Modifies the gravity of the ball for harder levels.  

		// Functions to check ball data for comparisons.  
		bool Bounced();		// Checks whether the ball has bounced in the current frame.  
		bool Fallen();		// Checks whether the ball has falled through the ring.  
		float GetY();		// Reports the y-value of the ball.  

	private:
		void Translate();			// Sets the translation of the ball's mesh.  
	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS OBJECTS
	//////////////////////////////////////////////////////////////////////////////////////
		D3DXMATRIX	Translation;	// Matrix to store values for the translation.  

	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS DATA
	//////////////////////////////////////////////////////////////////////////////////////
		float		gravity;		// The gravitational constant in use by the ball.  
		float		y;				// The position of the ball in the y-axis.  
		int			t;				// The amount of time passed since the last bounce.  
};

#endif