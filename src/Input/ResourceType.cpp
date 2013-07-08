//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 7/6/2013 >
/// < File >	< ResourceType >
/// < Brief >	< Reosurce Type implementation. this handles loading all resources of a certain type. >
//////////////////////////////////////////////////////////////////////////
/*
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "ResourceType.h"
#include "ResourceManager.h"
#include "../core/Utilities.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
ResourceType::ResourceType(string a_sName, vector<string> a_vFileTypesManaged)
	:m_sName(a_sName), m_vFileTypes(a_vFileTypesManaged)
{

}

//////////////////////////////////////////////////////////////////////////
ResourceType::~ResourceType()
{

}

//////////////////////////////////////////////////////////////////////////
vector<string> ResourceType::GetFileTypesManaged()
{
	return m_vFileTypes;
}

//////////////////////////////////////////////////////////////////////////
string ResourceType::GetName()
{
	return m_sName;
}

//////////////////////////////////////////////////////////////////////////
void ResourceType::BuildFile()
{
	/// <this section handles checking we can build the file. and grabbing all the raw data>
	/// < processing it then saving it to the file>
	path kBuildDir;
	if(ResourceManager::Get() != nullptr)
	{
		//kBuildDir = ResourceManager::Get()->GetBuildDir();
	}
	else
	{
		Utilities::Debug_ConsoleWrite("Resource Load Attempt before ResourceManager Created");
		return;
	}
	//vector<path> vFilesManaged = ResourceManager::Get()->GetAllFilesByType(m_vFileTypes);
	map<path,char*> vFileData;
	//for(unsigned int i = 0; i < vFilesManaged.size(); ++i)
	{

		// make char* to file data.
	//	vFileData[vFilesManaged.at(i)];
	}

}
//////////////////////////////////////////////////////////////////////////
void ResourceType::LoadFile(string a_sName)
{

}

*/