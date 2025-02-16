//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	RING BLOCK CLASS MODULE																//
//	The datatype class to handle a block of the game's ring system.  The class is		//
//	derived from the Direct3D mesh class and also includes extra data & functions		//
//	specific to the ring.																//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//////////////////////////////////////////////////////////////////////////////////////////
#include "MeshRing.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//	Methods called by other classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Class constructor.  When initialised, the functions sets how far along the ring the
//	block should be rotated based on the parameter value.  
//////////////////////////////////////////////////////////////////////////////////////////
RingBlock::RingBlock(float displacement)
: D3DMesh()
{
	this->displacement = displacement;
}

//	Function to render the block onto the screen.  
//////////////////////////////////////////////////////////////////////////////////////////
void RingBlock::Render()
{
	// Sets the world matrix as that of the class's rotation matrix.  
	Device->SetTransform(D3DTS_WORLD, &(this->Rotation));

	this->RenderMesh();		// Renders the mesh after the world matrix is set.  
}

//	Function to rotate the block around the y-axis at the origin based on a given angle
//	in radians.  
//////////////////////////////////////////////////////////////////////////////////////////
void RingBlock::RotationY(float rad)
{
	// Sets the rotation matrix as that for a rotation around the y-axis of value (given
	// angle in radians - the displacement angle stored in the class).  
	D3DXMatrixRotationY(&this->Rotation, (rad - this->displacement));
}