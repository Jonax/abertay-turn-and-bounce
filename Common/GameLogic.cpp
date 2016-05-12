//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	GAME LOGIC MODULE																	//
//	The primary class for the game's logic algorithms.  The module handles the main		//
//	organisation of the game.															//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//////////////////////////////////////////////////////////////////////////////////////////
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//	Methods called by other classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Class constructor.  When initialised, the models are created and the values are
//	set to default.  
//////////////////////////////////////////////////////////////////////////////////////////
GameLogic::GameLogic()
{
	// Create each block and set their position around the ring as every 60 degrees.  
	for (int i = 0 ; i < NUM_BLOCKS ; i++)
		Block[i] = new RingBlock(i * SPLIT_SIX);

	// Creates the ball.  
	Ball = new BallMesh();

	// Creates each of the six colours used in the game.  
	Colour[0] = new ColourRGB(1.0f, 0.0f, 0.0f);	// Red
	Colour[1] = new ColourRGB(1.0f, 1.0f, 0.0f);	// Yellow
	Colour[2] = new ColourRGB(0.0f, 1.0f, 0.0f);	// Green
	Colour[3] = new ColourRGB(0.0f, 1.0f, 1.0f);	// Cyan
	Colour[4] = new ColourRGB(0.0f, 0.0f, 1.0f);	// Blue
	Colour[5] = new ColourRGB(1.0f, 0.0f, 1.0f);	// Magenta

	this->x	= 0.0f;		// Rotation displacement is 0. 
	this->score = 0;	// Score at start is 0.
	this->level = 1;	// Level at start is 1.  

	this->Load();			// Loads the meshes into the models.  
	this->ChangeColours();	// Sets the colours for the blocks & the ball to start off the game.  

	// Sets the base plane to a plane straight upwards.  
	BasePlane = D3DXPLANE(0.0f, 1.0f, 0.0f, 1.0f);

	// Sets the shadow material to black with half alpha.  
	BlackMatter.Diffuse  = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	BlackMatter.Ambient  = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	BlackMatter.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	BlackMatter.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

//	Function to render each of the models, as well as comparisons as to whether special
//	actions should be created for the frame.  
//////////////////////////////////////////////////////////////////////////////////////////
bool GameLogic::Render()
{
	// First stage - Render the ring.  
	for (int i = 0 ; i < NUM_BLOCKS ; i++)	// For each block in the ring...
	{
		Block[i]->RotationY(this->x);	// Set the world matrix to the relevant rotation.  
		Block[i]->Render();				// Renders the block.  
	}

	// Second stage - Render the shadow.  
	this->DrawShadow();

	// Third stage - Render the ball.  
	Ball->Render();
	
	// Checks whether specific actions need to be taken.  
	if (Ball->Bounced())	// If the ball touches the ring...
	{
		// And the colour of the block below the ball matches the colour of the ball...
		if (Ball->GetColourID() == Block[this->GetBlockBelow()]->GetColourID())
		{
			this->ChangeColours();	// Change the colours of the ring blocks & the ball.  
			Ball->Bounce();			// Bounces the ball.  
			this->IncreaseScore();	// Increases the score by 1.  
		}
		// Otherwise, the ball falls through the ring to a game over.  
	}

	if (Ball->Fallen())	// If the ball is acknowledged as fully fell through the ring...
		return false;	// Report it to the renderer.  

	return true;		// Otherwise, report to the renderer that everything is fine.  
}

//	Function to rotate the ring based on the given x value.  
//////////////////////////////////////////////////////////////////////////////////////////
void GameLogic::Rotate(float x)
{
	this->x -= x;
}

//	Function to report the level attained for the current game.  
//////////////////////////////////////////////////////////////////////////////////////////
int GameLogic::GetLevel()
{
	return this->level;
}

//	Function to report the current progress to the next level.  
//////////////////////////////////////////////////////////////////////////////////////////
int GameLogic::GetScore()
{
	return this->score;
}

//////////////////////////////////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//	Methods called from within the class for better organisation of the module.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Function to report the current progress to the next level.  
//////////////////////////////////////////////////////////////////////////////////////////
void GameLogic::Load()
{	
	// Loads each of the models into memory.  
	for (int i = 0 ; i < NUM_BLOCKS ; i++)	// For each block in the ring...
	{
		Block[i]->Load("Block.x");			// Load the relevant mesh in.  
	}
	Ball->Load("Ball.x");					// Loads the required mesh for the ball.  
}

//	Function to draw the shadow via the stencil buffer.  
//////////////////////////////////////////////////////////////////////////////////////////
void GameLogic::DrawShadow()
{
	// A pointer to the main Direc3D Device.  
	IDirect3DDevice9* Device = Settings.GetDevice();

	D3DXMATRIX ShadowMatrix;	// A matrix for storing the transformation data for drawing
								// the shadow.  

	// Calculates the light ray based on the position of the ball.  This line alone is
	// basically a very cheap trick in getting a dynamically-sized shadow for the ball - 
	// instead of writing a full function to make sure the shadow changed, this method
	// simply changes the ray's y co-ord and length based on the position of the ball.  
	this->LightRay = D3DXVECTOR4(	 0.0f,
									(0.5f + (2 * Ball->GetY())), 
									 BASE_Z, 
									(1.0f - Ball->GetY()));

	// Generates the plane required for the shadow rendering.  
	D3DXMatrixShadow(&ShadowMatrix, &this->LightRay, &this->BasePlane);

	// Uploads the matrix to the World matrix.  
	Settings.GetDevice()->SetTransform(D3DTS_WORLD, &ShadowMatrix);

	Settings.ActiveStencilBuffer(true);		// Starts drawing to the stencil buffer.  

		Device->SetMaterial(&this->BlackMatter);// Starts drawing with the shadow material.  
		Device->SetTexture(0, 0);				// Makes sure a texture isn't used.  

		Ball->RenderShadow();				// Renders the shadow to the stencil buffer.  

	Settings.ActiveStencilBuffer(false);	// Stops drawing to the stencil buffer.  
}

//	Function to change the colours for the ring & ball.
//////////////////////////////////////////////////////////////////////////////////////////
void GameLogic::ChangeColours()
{
	int newcolid;			// Saves the id of the new colour to change to.  
	bool valid = false;		// Check that there's a block available for the player to hit
							// on each switch.  

	srand(GetTickCount());	// Seeds the random generator with the present time.  

	// Picks a new colour at random and assigns it to the ball.  
	newcolid = rand() % NUM_COLOURS;
	Ball->ChangeColour(newcolid, Colour[newcolid]);

	// For each block, a new colour is picked at random and assigned to it.  
	for (int i = 0 ; i < NUM_BLOCKS ; i++)
	{
		newcolid = rand() % 6;
		Block[i]->ChangeColour(newcolid, Colour[newcolid]);

		// If the block's new colour matches that of the ball, mark it as such.  
		if (newcolid == Ball->GetColourID())
			valid = true;  
	}

	// If, after generating each block, none of them match the same colour as the block...
	if (!valid)
	{
		// A block is picked at random.  This block then takes the same colour as the ball.
		int blockid = rand() % NUM_BLOCKS;
		Block[blockid]->ChangeColour(Ball->GetColourID(), Colour[Ball->GetColourID()]);
	}
}

//	Function to increase the score of the game.  
//////////////////////////////////////////////////////////////////////////////////////////
void GameLogic::IncreaseScore()
{
	this->score++;						// Increments the score by 1.  
	if (this->score == this->level)		// If the score matches that of the level...
	{
		this->level++;					// Increases the attained level.  
		this->score = 0;				// Resets the score to 0.  
		Ball->ChangeGravity();			// Increases the gravitational pull of the ball.  
	}
}

//	Function to find the ID of the block the ball is currently below.  
//////////////////////////////////////////////////////////////////////////////////////////
int GameLogic::GetBlockBelow()
{
	// Adds 30 degrees to the current value of the x value around the ring.  This is added
	// as a means to standardise the value to the front of the ring (without this, it would
	// see the block a little towards the left of the ring).  
	float b_std = this->x + (PI / 6);

	int b_id = (int)floor(b_std);		// Take the value calculated above and round it down
										// (e.g. 3.142 -> 3).

	// While the number is negative, add another full circle to make it positive.  
	while (b_id < 0)
		b_id += 6;

	return (b_id % 6);	// Find the reminder to get the ID of the block the ball is over.  
}