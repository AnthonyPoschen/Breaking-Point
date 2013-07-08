//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 26 - 5 - 2013 >
/// < Class Brief >	< This class handles loading Resources used by the program from .dat to expected output  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include <boost/container/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/container/map.hpp>
#include <boost/container/vector.hpp>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >

using namespace boost::container;
using namespace boost::filesystem;
class ResourceType;
//////////////////////////////////////////////////////////////////////////
class ResourceManager
{
public:

	// change this to need any prerequisit info like filepath to search
	static ResourceManager* Create();
	virtual void Release();
	static ResourceManager* Get();
	
protected:
	ResourceManager();
	~ResourceManager();

private:
	
	path m_kFilePath;
	static ResourceManager* m_pInst; 
	vector<ResourceType> m_kResourceHandlers;
};

//////////////////////////////////////////////////////////////////////////
#endif // _RESOURCEMANAGER_H_
//////////////////////////////////////////////////////////////////////////



/*
notes

Resource Manager creates every ResourceType it manages when it gets created
i.e list.add( new FBXMANAGER());
this reduces need to check who owns what filetype can have a trust system. or still check

ResourceType needs built in method to read raw data files do any processing if needed
and it builds its own files with helper functions from ResourceManager,

*/
