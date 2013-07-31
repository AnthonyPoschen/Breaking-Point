//////////////////////////////////////////////////////////////////////////
/*! \class		ShaderFactory
 *  \brief		This class Handles all ShaderObjects. 
 *	\details	handles loading and saving shader programs to disk.
 *  \details	handles in fetching shaderprograms.
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		02/03/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _SHADERFACTORY_H_
# define _SHADERFACTORY_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include <algorithm>
#include <iostream>

#define BOOST_FILESYSTEM_VERSION 3

#include <boost/filesystem.hpp>
#include <boost/container/string.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/map.hpp>
#include <boost/move/move.hpp>
#include <boost/filesystem/operations.hpp>
#include "ShaderProgram.h"
#include <gl/GL.h>
//////////////////////////////////////////////////////////////////////////
//  Forward Declares 

using namespace boost::container;
using namespace boost::filesystem;

//////////////////////////////////////////////////////////////////////////
class ShaderFactory
{
public:
	friend class ShaderProgram;

	/*! \brief Creates the signleton object.
	 *  \return returns a pointed to the instance thats created.
	 */
	static ShaderFactory* Create();

	/*! \brief Releases the object freeing all memory it uses.
	 */
	virtual void Release();

	/*! \brief gets an instance of the singleton object. 
	 *  \return Shaderfactory* - rreturns the singleton object.
	 */
	static ShaderFactory* Get();

	/*! \brief Sets up the shaderfactory with all shaderprograms it can discover
	 *  \param a_pcRootShaderDir [in] - directory relative to the program to search for shader programs to load. 
	 */
	void Initilise(const char* a_pcRootShaderDir = ".\\");

	
protected:
	ShaderFactory();
	~ShaderFactory();

private:
	void BuildBNFS();
	static ShaderFactory* m_pInst;
	string m_kRootDir;
	map<boost::container::string, path> m_kNSF; // map<Program Name , File name + path>
	map<boost::container::string, path> m_kBSF; // map<Program Name, File name + path>
	
	bool m_bDebug;
	void ScanDirForShaders();
	void DebugShaderScan();
	void ReleaseShaderScan();
	bool LoadShader(boost::container::string a_sProgramName, boost::filesystem::path a_kPath);
	bool BuildShader(ShaderProgram& a_kProgram);
	//void CreateShader(const char);
	boost::container::map<boost::container::string,GLuint> m_vProgramIDMap;
};
//////////////////////////////////////////////////////////////////////////
#endif // _SHADERFACTORY_H_
//////////////////////////////////////////////////////////////////////////
