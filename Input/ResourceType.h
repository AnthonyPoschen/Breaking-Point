//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 7 - 6 - 2013 >
/// < Class Brief >	< ResourceType  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _RESOURCETYPE_H_
#define _RESOURCETYPE_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include <boost/container/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/container/map.hpp>
#include <boost/container/vector.hpp>

#include <iostream>
#include <fstream>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
using namespace boost::container;
using namespace boost::filesystem;

class Resource;
//////////////////////////////////////////////////////////////////////////
class ResourceType // all inheritance should be singleton
{
public:
	friend class ResourceManager;
	ResourceType(string a_sName, vector<string> a_vFileTypesManaged );
	virtual ~ResourceType();
	string GetName();
	vector<string> GetFileTypesManaged();

protected:
	string m_sName; // unique name needed will be cross refrenced
	vector<string> m_vFileTypes; // unique filetypes per reosurce type
	// if debug mode, build file is called then Loadfile. if release then jsut loadfile.
	// this allows easy loading and saving.
	virtual void PreProcessBuildFile(char* a_cpRawDataFile) = 0;
	virtual Resource& LoadToResource(string a_sName) = 0; 
private:
	void BuildFile(); // non inheritable its a unified method for doing the files. 
	void LoadFile(string a_sName); 
	
	std::ifstream m_File;
};
//////////////////////////////////////////////////////////////////////////
#endif // _RESOURCETYPE_H_
//////////////////////////////////////////////////////////////////////////
