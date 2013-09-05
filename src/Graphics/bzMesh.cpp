//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 23/3/2013 >
//  < File >	< bzMesh >
//  < Brief >	< bzMesh implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >
#include "bzMesh.h"

#define GLEW_STATIC

#include "../Include/glew.h"
#include "../include/wglew.h"


//////////////////////////////////////////////////////////////////////////
// < Forward Declares >
const Rtti bzMesh::TYPE("bzmesh",&AVObject::TYPE);

//////////////////////////////////////////////////////////////////////////
bzMesh::bzMesh()
	:AVObject()
{

	glGenVertexArrays(1,&m_uiVAOID);

	glBindVertexArray(m_uiVAOID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &m_uiVertexBuffer);
	glGenBuffers(1,&m_uiVertColorBuffer);
	glGenBuffers(1,&m_uiIndicieBuffer);



	vertexdatatest = new float[24];
	//front
	//0
	vertexdatatest[0] = -1.0f;
	vertexdatatest[1] = -1.0f;
	vertexdatatest[2] = 1.0f;
	//1
	vertexdatatest[3] = 1.0f; 
	vertexdatatest[4] = -1.0f;
	vertexdatatest[5] = 1.0f;
	//2
	vertexdatatest[6] = 1.0f;
	vertexdatatest[7] = 1.0f;
	vertexdatatest[8] = 1.0f;
	//3
	vertexdatatest[9] = -1.0f;
	vertexdatatest[10] = 1.0f;
	vertexdatatest[11] = 1.0f;

	//back
	//4
	vertexdatatest[12] = -1.0f;
	vertexdatatest[13] = -1.0f;
	vertexdatatest[14] = -1.0f;
	//5
	vertexdatatest[15] = 1.0f; 
	vertexdatatest[16] = -1.0f;
	vertexdatatest[17] = -1.0f;
	//6
	vertexdatatest[18] = 1.0f;
	vertexdatatest[19] = 1.0f;
	vertexdatatest[20] = -1.0f;
	//7
	vertexdatatest[21] = -1.0f;
	vertexdatatest[22] = 1.0f;
	vertexdatatest[23] = -1.0f;



	vertcolors = new float[24];
	vertcolors[0] = 1.0f;
	vertcolors[1] = 0.0f;
	vertcolors[2] = 0.0f;

	vertcolors[3] = 1.0f;
	vertcolors[4] = 0.0f;
	vertcolors[5] = 0.0f;

	vertcolors[6] = 0.0f;
	vertcolors[7] = 1.0f;
	vertcolors[8] = 0.0f;

	vertcolors[9] = 0.0f;
	vertcolors[10] = 1.0f;
	vertcolors[11] = 0.0f;

	vertcolors[12] = 1.0f;
	vertcolors[13] = 0.0f;
	vertcolors[14] = 0.0f;

	vertcolors[15] = 1.0f;
	vertcolors[16] = 0.0f;
	vertcolors[17] = 0.0f;

	vertcolors[18] = 0.0f;
	vertcolors[19] = 1.0f;
	vertcolors[20] = 0.0f;

	vertcolors[21] = 0.0f;
	vertcolors[22] = 1.0f;
	vertcolors[23] = 0.0f;

	unsigned int Indicies[] =
	{
		//top front indicies L-R
		// 3,2
		//bottom front indicies L-R
		// 0,1
		// top back indicies L-R
		// 7,6
		// bottom back indicies L-R
		// 4,5

		//front face
		0,1,2,
		2,3,0,

		//bottom face
		//0,1 4,5
		4,5,1,
		0,1,4,

		//top face
		//3,2 7,6
		3,2,6,
		6,7,3,
		//back face
		6,5,4,
		4,7,6,

		//left face
		4,0,3,
		3,7,4,

		//right face
		2,1,5,
		5,6,2
	};
	unsigned int uiSize = sizeof(Indicies);
	// information to determine type to use for glbufferdata
	// http://www.opengl.org/sdk/docs/man/xhtml/glBufferData.xml
	// Give our vertices to OpenGL.
	
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24, vertexdatatest, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,m_uiVertColorBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*24,vertcolors,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_uiIndicieBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indicies),Indicies,GL_STATIC_DRAW);
}

bzMesh::~bzMesh()
{
	glDeleteVertexArrays(1,&m_uiVAOID);
	delete[] vertexdatatest;
}

void bzMesh::Render()
{

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,m_uiVertColorBuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	// Draw the triangle !
	//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0); // magic number is number of indicies to draw
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
}