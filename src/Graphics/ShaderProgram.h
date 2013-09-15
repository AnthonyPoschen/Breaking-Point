//////////////////////////////////////////////////////////////////////////
/*! \class		ShaderProgram
 *  \brief		This holds all shader information for the render to use to draw geometry.
 *	\details	
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		15/03/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _SHADERPROGRAM_H_
# define _SHADERPROGRAM_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "../Include/glew.h"
#include "../include/wglew.h"
#include <gl/GL.h>
#include "../core/Property.h"
#include <boost/container/string.hpp>


//////////////////////////////////////////////////////////////////////////
//  Forward Declares 


//////////////////////////////////////////////////////////////////////////
class ShaderProgram : public Property
{
public:
	friend class ShaderFactory;
	friend class Renderer;
	ShaderProgram();
	~ShaderProgram();
	/*! \brief This function loads the shader specified from the shaderfactory.
	 *  \param a_pcProgramName [in] - The name of the shaderprogram to use. shader program names must be unique.
	 *  \return bool - determine if the shader could be loaded or not. 
	 */
	bool LoadShaderProgram(const char * a_pcProgramName);
protected:
	

private:
	
	GLuint m_uiProgramID;
	boost::container::string m_sProgramName;

};
//////////////////////////////////////////////////////////////////////////
#endif // _SHADERPROGRAM_H_
//////////////////////////////////////////////////////////////////////////
