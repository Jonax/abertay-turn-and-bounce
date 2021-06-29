//////////////////////////////////////////////////////////////////////////////////////////
//								 "Turn & Bounce" Prototype								//
//					   Written 2007 by Jon Wills (jonaxc@gmail.com)						//
//				  Written for a Win32 environment using the Direct3D API.				//
//																						//
//				   Written at the University of Abertay Dundee, Scotland				//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//	DIRECT3D MESH CLASS MODULE															//
//	The datatype class to handle an encapsulated Direct3D mesh.  The class is used to	//
//	hold fundamental functions & data for handling the loading & settings of the mesh	//
//	as well as managing its rendering.													//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef _D3DMESH_H_
#define _D3DMESH_H_

//////////////////////////////////////////////////////////////////////////////////////////
//	LIBRARY INCLUDES
//	The libraries & namespaces required for the module.  
//////////////////////////////////////////////////////////////////////////////////////////
#include <d3d9.h>		// Library for DirectX 9.0c functionality.  
#include <d3dx9.h>		// Extended library for DirectX 9.0c functionality.  
#include "Defines.h"	// Library for the project's definitions & macros.  
#include "D3DSetup.h"	// Direct3D settings class.  
#include "ColourRGB.h"	// RGB Colour datatype class.  

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//	Declaration of all required class methods and data.  The code for the methods is 
//	detailed in the module's source file.  
//////////////////////////////////////////////////////////////////////////////////////////
class D3DMesh
{
	public:
		D3DMesh();		// Class constructor.
		~D3DMesh();		// Class destructor.  
		
		// Fundamental functions for functionality required in all derived classes.  
		void Load(LPCTSTR Filename);					// Loads in a specified .x mesh.  
		void ChangeColour(int id, ColourRGB* Colour);	// Changes the main colour.  

		int GetColourID();		// Reports the assigned colour ID given to it.  

	protected:
		void RenderMesh();		// Handles the main mesh rendering.  

	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS OBJECTS
	//////////////////////////////////////////////////////////////////////////////////////
		IDirect3DDevice9*	Device;			// Pointer to the main Direct3D device.  

		ID3DXMesh*			Mesh;			// Pointer to the class's stored mesh.  
		ID3DXBuffer*		MaterialBuffer;	// The mesh's material buffer.  

		D3DMATERIAL9*		Material;		// The materials used in the mesh.  
	
	//////////////////////////////////////////////////////////////////////////////////////
	//	CLASS DATA
	//////////////////////////////////////////////////////////////////////////////////////
		DWORD				numMaterials;	// The number of materials used in the mesh.  
		int					colour;			// The ID of the main material's current colour.  
};

#endif