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
	



	vertexdatatest = new float[9];
	vertexdatatest[0] = -1.0f;
	vertexdatatest[1] = -1.0f;
	vertexdatatest[2] = 0.0f;
	vertexdatatest[3] = 1.0f; 
	vertexdatatest[4] = -1.0f;
	vertexdatatest[5] = 0.0f;
	vertexdatatest[6] = 0.0f;
	vertexdatatest[7] = 1.0f;
	vertexdatatest[8] = 0.0f;

	vertcolors = new float[9];
	vertcolors[0] = 1.0f;
	vertcolors[1] = 0.0f;
	vertcolors[2] = 0.0f;

	vertcolors[3] = 0.0f;
	vertcolors[4] = 1.0f;
	vertcolors[5] = 0.0f;

	vertcolors[6] = 0.0f;
	vertcolors[7] = 0.0f;
	vertcolors[8] = 1.0f;

	// information to determine type to use for glbufferdata
	// http://www.opengl.org/sdk/docs/man/xhtml/glBufferData.xml
	// Give our vertices to OpenGL.
	
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, vertexdatatest, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,m_uiVertColorBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*9,vertcolors,GL_STATIC_DRAW);

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
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
}