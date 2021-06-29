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

//////////////////////////////////////////////////////////////////////////////////////////
//	CLASS HEADER
//////////////////////////////////////////////////////////////////////////////////////////
#include "D3DMesh.h"

//////////////////////////////////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//	Methods called by other classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Class constructor.  When initialised, the function gets a pointer to the application's
//	main Direct3D device and stores the pointer in the class for use in other functions.  
//////////////////////////////////////////////////////////////////////////////////////////
D3DMesh::D3DMesh()
{
	this->Device = Settings.GetDevice();
}

//	Class destructor.  When initialised, the function makes sure that the stored mesh is
//	removed to prevent a memory leak.  
//////////////////////////////////////////////////////////////////////////////////////////
D3DMesh::~D3DMesh()
{
	Mesh->Release();
}

//	Function to load in the class's .x mesh.  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DMesh::Load(LPCTSTR Filename)
{
	// Loads a mesh in from an .x file.  
	HRESULT result = D3DXLoadMeshFromX(	Filename,				// Name of the .x file.  
						D3DXMESH_SYSTEMMEM,		// Loads the mesh into system memory
						this->Device,			// The application's Direct3D Device
						NULL,					// Adjacency isn't being used.  
						&this->MaterialBuffer,	// Materials are placed in the given buffer.  
						NULL,					// Effect instances aren't being used.  
						&this->numMaterials,	// Reports number of materials in the mesh.  
						&this->Mesh);			// Stores the mesh in this place.  

	// A temporary pointer calls the pointer for the material buffer.  
	D3DXMATERIAL* TempMaterial = (D3DXMATERIAL*) MaterialBuffer->GetBufferPointer();

	// Creates a material buffer for each material in the mesh.  
	Material = new D3DMATERIAL9[numMaterials];

	// Stores the necessary colour values for each material in the mesh.  
	for (DWORD i = 0 ; i < this->numMaterials ; i++)	// For each material...
	{
		// Material info is retrieved from the relevant D3D material in the temp material
		// buffer...
		Material[i]			= TempMaterial[i].MatD3D;
		Material[i].Ambient = Material[i].Diffuse;	// Then the ambient is made the same 
			// as the diffuse (a common workaround due to limitations in Direct3D to date.  
	}
}

//	Function to change the main colour of the mesh.  The function changes the colour of
//	the stored material, as well as the id of the colour used (this is used later for
//	comparison operations).  
//////////////////////////////////////////////////////////////////////////////////////////
void D3DMesh::ChangeColour(int id, ColourRGB* Colour)
{
	// Changes the colour for each material used in the mesh (although all should be the
	// same due to how the models are coded.  
	for (DWORD i = 0 ; i < this->numMaterials ; i++)	// For each subset in the mesh...
	{
		// Overwrite the RGB values of the materials with the given colour.  Alpha is
		// intentional omitted - This is because the alpha value is already read from the
		// mesh and it isn't desired for it to be overwritten with another value.  
		Material[i].Diffuse.r = Colour->r;
		Material[i].Diffuse.g = Colour->g;
		Material[i].Diffuse.b = Colour->b;
		Material[i].Ambient = Material[i].Diffuse;	// Makes ambient the same as diffuse
													// (Again, the same workaround.)
	}

	this->colour = id;	// Stores the ID of the given colour in the class.  
}

//	Function to report the colour ID stored in the class.  While pretty useless for the
//	class itself, it is of major importance for comparison operations by the game logic
//	class.  
//////////////////////////////////////////////////////////////////////////////////////////
int D3DMesh::GetColourID()
{
	return this->colour;
}

//////////////////////////////////////////////////////////////////////////////////////////
// PROTECTED METHODS
// Methods called from within the class for better organisation of the module.  They are
// only of real use in the derived classes.  
//////////////////////////////////////////////////////////////////////////////////////////

//	Function to render the mesh.  Each derived class added their own required code to just
//	before this function (e.g. matrix uploading).
//////////////////////////////////////////////////////////////////////////////////////////
void D3DMesh::RenderMesh()
{
	// Draws each subset of the mesh to make the full model.  
	for (DWORD i = 0 ; i < this->numMaterials ; i++)	// For each subset in the mesh...
	{
		Device->SetMaterial(&Material[i]);				// Set the material as required.

		Mesh->DrawSubset(i);							// Then draw the subset.  
	}
}