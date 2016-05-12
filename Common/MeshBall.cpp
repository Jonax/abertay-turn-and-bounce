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

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//////////////////////////////////////////////////////////////////////////////////////////
#include "MeshBall.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//	Methods called by other classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Class constructor.  When initialised, the functions sets the class values to default
//	values.  
//////////////////////////////////////////////////////////////////////////////////////////
BallMesh::BallMesh()
: D3DMesh()
{
	this->gravity = INITIAL_GRAVITY;	// Sets the default gravity.  
	this->Bounce();						// Sets the ball to bounce for the first frame.  
}

//	Function to render the block onto the screen.  
//////////////////////////////////////////////////////////////////////////////////////////
void BallMesh::Render()
{
	// Translates the ball by the required amount.  
	this->Translate();					// Calculates the necessary translation matrix.
	Device->SetTransform(D3DTS_WORLD, &this->Translation);
						// Sets the world matrix as that of the class's rotation matrix.  

	this->RenderMesh();					// Renders the mesh after the world matrix is set.  
}

//	Function to render the ball's shadow via the stencil buffer.  When this function is
//	called, it is assumed that the Game Logic system had automatically configured the
//	required elements to drawing to the stencil buffer.  
//////////////////////////////////////////////////////////////////////////////////////////
void BallMesh::RenderShadow()
{
	// Draws the shadow of the model to the stencil buffer.  
	for (DWORD i = 0 ; i < this->numMaterials ; i++)	// For each subset of the mesh...
		Mesh->DrawSubset(i);					// Draw the subset to the stencil buffer.  
}

//	Function to make the ball bounce on the ring.  At its most basic, the function resets
//	the two dynamic variables (position on the y-axis & time).  
//////////////////////////////////////////////////////////////////////////////////////////
void BallMesh::Bounce()
{
	this->y = 0.0f;
	this->t = 0;
}

//	Function to increase the gravitational constant of the ball's motion.  This function
//	is called each time the player increases in level.  
//////////////////////////////////////////////////////////////////////////////////////////
void BallMesh::ChangeGravity()
{
	// Gravity is increased to an increased percentage of the previous gravity (in case of
	// commenting, it is increased to 110% of what it was before).  
	this->gravity += (this->gravity * GRAV_INCREASE);
}

//	Function to check whether the ball has bounced since the last frame.  
//////////////////////////////////////////////////////////////////////////////////////////
bool BallMesh::Bounced()
{
	// Reports whether the ball appears between the values of y = -0.5 and y = 0.  This
	// acts as a very rudimentary way to determine whether the ball has hit the ring since
	// the last frame.  
	return ((this->y > -0.5f) && (this->y <= 0.0f));
}

//	Function to check whether the ball has finally fallen through the ring.  
//////////////////////////////////////////////////////////////////////////////////////////
bool BallMesh::Fallen()
{
	// Once the ball has falled down a certain depth below the ring, it is reported that
	// the ball has falled through the ring.  
	return (this->y < -5.0f);
}

//	Function to report the position of the ball on the y-axis.  
//////////////////////////////////////////////////////////////////////////////////////////
float BallMesh::GetY()
{
	return this->y;
}

//////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
// Methods called from within the class for better organisation of the module.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Function to calculate the y-position of the ball since last time and then pass it to
//	the ball's translation matrix.  
//////////////////////////////////////////////////////////////////////////////////////////
void BallMesh::Translate()
{
	this->t++;									// Adds another frame to the ball's timer.  

	// Y is increased by the result of a "v = u + at" equation of motion, 
	//	v = The ball's displacement since the last frame
	//	u = The velocity of the ball at launch
	//	a = The ball's gravitational constant
	//	t = How long the ball has been in the air
	// The result is also times by a scale to make the result relevant to the world scale.
	this->y += SCALE * (LAUNCH_VELOCITY - (this->gravity * this->t));

	// Sets the translation matrix to accommodate the given result.  
	D3DXMatrixTranslation(&Translation, 0.0f, this->y, -2.5f);
}