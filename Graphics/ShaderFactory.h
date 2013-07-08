//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 2 - 3 - 2013 >
/// < Class Brief >	< This class Handles finding shaders to be ready to be loaded  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _SHADERFACTORY_H_
#define _SHADERFACTORY_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
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
/// < Forward Declares >

using namespace boost::container;
using namespace boost::filesystem;

//////////////////////////////////////////////////////////////////////////
class ShaderFactory
{
public:
	friend class ShaderProgram;

	static ShaderFactory* Create();
	virtual void Release();
	static ShaderFactory* Get();

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
