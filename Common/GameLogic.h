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
#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

//////////////////////////////////////////////////////////////////////////////////////////
//	LIBRARY INCLUDES
//	The libraries & namespaces required for the module.  
//////////////////////////////////////////////////////////////////////////////////////////
#include <math.h>		// Standard math library.  
#include "Defines.h"	// Library for the project's definitions & macros.  
#include "D3DSetup.h"	// Direct3D settings class.
#include "MeshRing.h"	// Ring block class.
#include "MeshBall.h"	// Ball class.  

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//	Declaration of all required class methods and data.  The code for the methods is 
//	detailed in the module's source file.  
//////////////////////////////////////////////////////////////////////////////////////////
class GameLogic
{
	public:
		GameLogic();			// Class constructor.  

		bool Render();			// Renders all of the various elements of the game.  

		void Rotate(float x);	// Moves the ring based on a given amount.  

		int GetLevel();			// Gets the current level.  
		int GetScore();			// Gets the current progress towards the next level.  

	private:
		void Load();			// Loads in the various meshes.  

		void DrawShadow();		// Draws the shadow of the ball on the ring.  
		void ChangeColours();	// Changes the colours of the ball & ring.  
		void IncreaseScore();	// Increases the score after a successful bounce.  

		int GetBlockBelow();	// Reports the ID of the block below the ball.  

	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS OBJECTS
	//////////////////////////////////////////////////////////////////////////////////////
		RingBlock*	Block[NUM_BLOCKS];		// The six blocks that make up the iconic ring.  
		BallMesh*	Ball;					// The ball of the game.  
		ColourRGB*	Colour[NUM_COLOURS];	// The six colours that are used in the game.  

		// Objects used for shadow rendering.  
		D3DXVECTOR4		LightRay;			// Vector to store a light ray.  
		D3DXPLANE		BasePlane;			// Plane to act as calculate the geometry.  
		D3DMATERIAL9	BlackMatter;		// Material used for drawing the shadows.  

	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS DATA
	//////////////////////////////////////////////////////////////////////////////////////
		int level;		// The level of the game.  
		int score;		// The score during the game.  
		float x;
};

#endif