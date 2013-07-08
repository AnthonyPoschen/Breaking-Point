//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 2/3/2013 >
/// < File >	< ShaderFactory >
/// < Brief >	< ShaderFactory Implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "ShaderFactory.h"
#include <boost/algorithm/string.hpp>

#include "../math/UniversalTypes.h"
#include <iostream>
#include <fstream>
#include "../include/wglew.h"
#include <gl/GLU.h>


//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
ShaderFactory* ShaderFactory::m_pInst = nullptr;
std::vector<std::string> find_files_by_type(const path& dir_path , const path& file_Ext);
std::string StringToUpper(std::string a_sConvert);


//////////////////////////////////////////////////////////////////////////
ShaderFactory* ShaderFactory::Create()
{
	return (m_pInst != nullptr) ? m_pInst : m_pInst = new ShaderFactory();
}

//////////////////////////////////////////////////////////////////////////
void ShaderFactory::Release()
{
	if(m_pInst != nullptr)
		delete m_pInst;
}

//////////////////////////////////////////////////////////////////////////
ShaderFactory::ShaderFactory()
	:m_kRootDir(".\\")
{
	// set if this is debug build or not. this way the program knows if it should
	// compile shaders. or use the precompiled files from debug's output
	// this reduces shader linking time and stops people from freely editing 
	// the shaders.
#ifdef _DEBUG
	m_bDebug = true;
#else
	m_bDebug = false;
#endif
}

//////////////////////////////////////////////////////////////////////////
ShaderFactory::~ShaderFactory()
{

}



//////////////////////////////////////////////////////////////////////////
ShaderFactory* ShaderFactory::Get()
{
	return m_pInst;
}

//////////////////////////////////////////////////////////////////////////
void ShaderFactory::Initilise(const char* a_pcRootShaderDir /*= ".\\"*/)
{
	m_kRootDir = a_pcRootShaderDir;
	ScanDirForShaders();

}

//////////////////////////////////////////////////////////////////////////
void ShaderFactory::ScanDirForShaders()
{
	if(m_bDebug)
	{
		DebugShaderScan();
		BuildBNFS();
	}
	ReleaseShaderScan();

}

//////////////////////////////////////////////////////////////////////////
void ShaderFactory::DebugShaderScan()
{
	// highly under optimised and a cluster fuck. re programming needed

	m_kNSF.clear();
	path dir_path(m_kRootDir.c_str());
	path FileType("*.nsf");
	std::vector<std::string> vFiles;
	vFiles = find_files_by_type(dir_path,FileType);
	
	auto Itr = vFiles.begin();
	for(;Itr != vFiles.end(); Itr++)
	{
		
		std::string kFileName = (*Itr);
		// load the file and get the shader program name and store it in the map.
		
		std::string sLine;
		std::ifstream kStreamFile;
		kStreamFile.open(kFileName.c_str());


		bool bFinished = false;
		while (!bFinished)
		{
			if(!kStreamFile.eof())
			{
				std::getline(kStreamFile,sLine);
				sLine = StringToUpper(sLine);
				unsigned iresult = sLine.find("PROGRAMNAME");
				if(iresult != std::string::npos)
				{
					int isize = sLine.length();
					std::string sName;

					sName = sLine.substr(iresult + 12,sLine.length());
					while(sName[0] == char(' '))
					{
						sName = sName.substr(1 , sName.size());
					}
					boost::container::string bsName(sName.c_str());
					path oPath((*Itr).c_str());
					m_kNSF[bsName] = oPath;

					path ptest = m_kNSF[bsName];
					bFinished = true;
				}
			}
			else
			{
				bFinished = true;
			}
		}
	}

}

void ShaderFactory::ReleaseShaderScan()
{
	m_kBSF.clear();
	path dir_path(m_kRootDir.c_str());
	path FileType("*.bsf");
	std::vector<std::string> vFiles;
	
	vFiles = find_files_by_type(dir_path,FileType);
	auto Itr = vFiles.begin();
	for(;Itr != vFiles.end(); Itr++)
	{
		boost::filesystem::path sFilePath = (*Itr);
		std::string sTest = sFilePath.filename().string();
		boost::container::string kProgramName = sTest.c_str();

		int iPos = kProgramName.find(".",0);
		kProgramName.erase(iPos,kProgramName.size());
		boost::algorithm::to_upper(kProgramName);

		m_kBSF[kProgramName] = sFilePath;

	}

}


//////////////////////////////////////////////////////////////////////////
std::vector<std::string> find_files_by_type(const path& dir_path , const path& file_Ext)
{
	std::vector<std::string> vResult;
	const recursive_directory_iterator end;
	recursive_directory_iterator oItr(dir_path);
	
	for( ; oItr != end ; oItr++ )
	{
		directory_entry e = (*oItr);
		if(e.path().extension() == file_Ext.extension())
		{
			std::string oPath = e.path().string();
			//vResult.push_back(e.path());
			vResult.push_back(oPath);
		}
	}
	return vResult;

/*  // really cool find_if example
	const recursive_directory_iterator end;
	const auto it = std::find_if(recursive_directory_iterator(dir_path), end,
		[&file_name](const directory_entry& e) {
			return e.path().extension() == file_name.extension();
			
	});

	if (it == end) {
		return false;
	} else {
		path_found = it->path();
		return true;
	}
	*/
}

boost::container::map<std::string,std::string> GetFilesSource(std::string a_sFilePath, std::string a_sFileNames)
{
	boost::container::map<std::string,std::string> mResult;
	bool bFinished = false;
	int iLastStartPoint = 0;
	int iBreaker = 0;
	while(!bFinished)// loop through all shader names and extract the names and load the file data
	{
		std::string sVSCurrentFileName;
		int iExtIncrement = 0;
		iBreaker = a_sFileNames.find(".GLSL",iLastStartPoint); 
		if(iBreaker == std::string::npos)
		{
			
			iBreaker = a_sFileNames.find(".VERT", iLastStartPoint);
			if(iBreaker == std::string::npos)
			{
				iBreaker = a_sFileNames.find(".FRAG", iLastStartPoint);
				if(iBreaker == std::string::npos)
				{
					iBreaker = a_sFileNames.find(".GEO", iLastStartPoint);
					if(iBreaker == std::string::npos)
					{
						bFinished = true;
						continue;
					}
					else
						iExtIncrement = 4;

				}
				else
					iExtIncrement = 5;

			}
			else
				iExtIncrement = 5;

		}
		else
			iExtIncrement = 5;

		iBreaker += iExtIncrement; // count for ".GLSL" extention chars 
		sVSCurrentFileName = a_sFileNames.substr(iLastStartPoint,iBreaker);
		std::ifstream oFile(a_sFilePath + sVSCurrentFileName);
		std::string sFileSourceCode;
		if(!oFile.good())
		{
			// some kind of warning or assert that a shader file cant be opened
		}
		while(oFile.good()) // get all the lines from the shader file till we are at EOF
		{
			std::string sSourceLine;
			std::getline(oFile,sSourceLine);
			sFileSourceCode += sSourceLine;
			sFileSourceCode += "\n"; // this is needed ebcause getline dos not add the \n at the end 
									 //of the line which is needed fro valid GLSL syntak
		}
		// we now have a shader file's source code now to store it away in our map with the file name
		if(sFileSourceCode.size())
			mResult[sVSCurrentFileName] = sFileSourceCode;
		// now to prepare for next loop
		iLastStartPoint = a_sFileNames.find_first_not_of(" ",iBreaker); // sets the start point to the start of the next file
		oFile.close();

	}
	return mResult;

}

//////////////////////////////////////////////////////////////////////////
void ShaderFactory::BuildBNFS()
{
	// Notes at end of file on file structure of saved file
	auto oItr = m_kNSF.begin();
	for(;oItr != m_kNSF.end(); oItr++) // for every program recognised read and write to new file format
	{
		// define all the buffers we will save to read from the NSF for the BNF
		boost::container::map<std::string,std::string> vVSFiles;
		boost::container::map<std::string,std::string> vPSFiles;
		boost::container::map<std::string,std::string> vGSFiles;

		// have some helper varriables setup
		boost::container::string oProgramName = (*oItr).first;
		boost::algorithm::to_lower(oProgramName); // convert the programname to lowercase for file name
		boost::filesystem::path oFile = (*oItr).second;
		boost::filesystem::path oFilePath = oFile.parent_path();
		boost::filesystem::path oRawShadersPath = oFilePath;
		oRawShadersPath += "\\source\\";
		std::string oNewFileName = oFilePath.string() + "\\" + oProgramName.c_str(); // this is the filename of the binary shader program
		oNewFileName += ".bsf"; // add the filetype to our new file
		

		std::string sLine;
		std::ifstream INSTREAM; // to read the nsf file to get everythign needed to build the shader program
		INSTREAM.open(oFile.string());
		for(;!INSTREAM.eof();) // this for loop extracts everything needed to construct the final file encombering all shader program information
		{
			int iResult = 0;
			std::getline(INSTREAM,sLine); 
			boost::algorithm::to_upper(sLine);// convert to caps so case sensitivity is irrelevent
			iResult = sLine.find("//");
			if( iResult != -1) // if theirs a comment section block within the first 5 chars
				continue;
			
			// prepare all vertex shader source code
			iResult = sLine.find("VERTEXSHADERS");// size = 13 chars | 14 with space
			if(iResult != std::string::npos) 
			{
				std::string sVSFileNames;
				if(iResult + 14 < (int)sLine.length())
				{
					sVSFileNames = sLine.substr(iResult + 14,sLine.length());
					vVSFiles = GetFilesSource(oRawShadersPath.string(),sVSFileNames);
				}
				continue;
			}

			// prepare all pixel shader source code 
			iResult = sLine.find("PIXELSHADERS"); // size = 12 | 13 with space
			if(iResult != std::string::npos)
			{
				std::string sPSFileNames;
				if(iResult + 13 < (int)sLine.length())
				{
					sPSFileNames = sLine.substr(iResult + 13, sLine.length());
					vPSFiles = GetFilesSource(oRawShadersPath.string(),sPSFileNames);
				}
				continue;
			}

			// prepare all source code for geometry shaders
			iResult = sLine.find("GEOMETRYSHADERS"); // size = 15 | 16 with space 
			if(iResult != std::string::npos)
			{
				std::string sGSFileNames;
				if(iResult + 16 < (int)sLine.length())
				{
					sGSFileNames = sLine.substr(iResult + 16, sLine.length());
					vGSFiles = GetFilesSource(oRawShadersPath.string(), sGSFileNames);
				}
				continue;
			}

		}


		INSTREAM.close(); // close the NSF we were reading from
		//------------------------------------------------------------------------------
		// from this point onwards we are working with writing to our own file type 
		// for storing all the information in the nsf + the source code from the glsl files referenced
		//------------------------------------------------------------------------------

		std::ofstream OUTSTREAM; // save binary of the shader program in a order acceptable for recovery
		OUTSTREAM.open(oNewFileName,std::fstream::binary | std::fstream::out);
		boost::algorithm::to_upper(oProgramName);
		UInt8 ui8SizeOfProgramName = (UInt8)oProgramName.length();
		OUTSTREAM << ui8SizeOfProgramName;
		OUTSTREAM << oProgramName;

		// out the vertex shader count 
		OUTSTREAM << (UInt8)vVSFiles.size(); // number of Vertex Shaders being saved in the loop
		auto ovsItr = vVSFiles.begin();
		for(;ovsItr != vVSFiles.end(); ovsItr++) // loop over every vertex shader
		{

			OUTSTREAM << (UInt8)((*ovsItr).first.size()); // get the size of the name of the shader
			OUTSTREAM << (*ovsItr).first.c_str();		  // output the name of the shader (good for debuging later what shader is fucked)
			OUTSTREAM << (UInt32)((*ovsItr).second.size());// output the size of the shader source code
			OUTSTREAM << (*ovsItr).second.c_str();		  // output the source code itself into the file
			
		}
		OUTSTREAM.flush();

		OUTSTREAM << (UInt8)vPSFiles.size(); // repeat same for pixel shaders
		auto opsItr = vPSFiles.begin();
		for(;opsItr != vPSFiles.end(); opsItr++)
		{
			OUTSTREAM << (UInt8)((*opsItr).first.size());
			OUTSTREAM << (*opsItr).first.c_str();
			OUTSTREAM << (UInt32)((*opsItr).second.size());
			OUTSTREAM << (*opsItr).second.c_str();
		}
		OUTSTREAM.flush();

		OUTSTREAM << (UInt8)vGSFiles.size(); // repeat same for geometry shaders 
		auto ogsItr = vGSFiles.begin();
		for(;ogsItr != vGSFiles.end(); ogsItr++)
		{
			OUTSTREAM << (UInt8)((*ogsItr).first.size());
			OUTSTREAM << (*ogsItr).first.c_str();
			OUTSTREAM << (UInt32)((*ogsItr).second.size());
			OUTSTREAM << (*ogsItr).second.c_str();
		}
		OUTSTREAM.flush();
		OUTSTREAM.close();
	}

}




//////////////////////////////////////////////////////////////////////////
std::string StringToUpper(std::string a_sConvert)
{
	// this causes a stupid std warning C4996: 'std::transform1':...
	std::transform(a_sConvert.begin(),a_sConvert.end(),a_sConvert.begin(),::toupper);
	return a_sConvert;
}

bool ShaderFactory::BuildShader(ShaderProgram& a_kProgram)
{

	for(auto oItr = m_vProgramIDMap.begin(); oItr != m_vProgramIDMap.end(); oItr++)
	{
		if((*oItr).first == a_kProgram.m_sProgramName)
		{
			a_kProgram.m_uiProgramID = m_vProgramIDMap[a_kProgram.m_sProgramName];
			return true;
		}

	}
	// prebuilt shader cant be found. lets see if we have the file for this program stored
	for(auto oItr = m_kBSF.begin();oItr != m_kBSF.end(); ++oItr)
	{
		if((*oItr).first == a_kProgram.m_sProgramName) // if we have it found
		{
			if(LoadShader((*oItr).first,(*oItr).second))
			{
				// shader got loaded now set the passed in program up
				a_kProgram.m_uiProgramID = m_vProgramIDMap[a_kProgram.m_sProgramName];

			}
			else // shader failed to load
			{
				return false; // because we found the program requested but cant be loaded
			}
		}
	}


	return false;
}

bool ShaderFactory::LoadShader(boost::container::string a_sProgramName, boost::filesystem::path a_kPath)
{
	// create the new program
	GLuint ProgramID = glCreateProgram();
	vector<GLuint> vVertShaders;
	vector<GLuint> vPixelShaders;
	vector<GLuint> vgeoShaders;

	auto oItr = m_kBSF.find(a_sProgramName);
	boost::container::string oName = (*oItr).first;
	boost::filesystem::path oPath = (*oItr).second;

	std::ifstream INSTREAM;
	INSTREAM.open(oPath.c_str(),std::fstream::binary | std::fstream::in);
	INSTREAM >> std::noskipws; // stops tabs and white space chars from being skipped in the reading process
	if(INSTREAM.is_open())
	{
		char cReader[1000000];
		UInt8 uiSizeElement;
		UInt8 uiNumberOfShaders;
		UInt32 uiShaderSource;
		boost::container::string sProgramName;
		
		INSTREAM >> uiSizeElement;
		INSTREAM.readsome(cReader,uiSizeElement);
		sProgramName = cReader;
		sProgramName.erase(uiSizeElement);

		//if program names dont match return false as we have the wrong program
		if(sProgramName != a_sProgramName)
			return false;



		INSTREAM >> uiSizeElement; // get number of vert shaders 
		uiNumberOfShaders = uiSizeElement;
		for(int i = 0; i != uiNumberOfShaders; ++i) // for each vert shader build it and track its name
		{											// for error reporting if needed. 
			INSTREAM >> uiSizeElement; // get size of shader name
			INSTREAM.read(cReader,uiSizeElement);
			std::string sShaderName = cReader;
			sShaderName.erase(uiSizeElement);

			// get shader source from file
			INSTREAM >> uiShaderSource;
			std::string sShaderSource;
			//INSTREAM >> std::skipws;
			INSTREAM.read(cReader,uiShaderSource);
			//INSTREAM >> std::noskipws;
			sShaderSource = cReader;
			sShaderSource.erase(uiShaderSource);

			// now lets compile a shader and link it to the program
			OutputDebugString((std::string("\nCompiling Shader ") +  sShaderName).c_str());
			GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			const GLchar* glcpSource = (const GLchar*)sShaderSource.c_str();
			glShaderSource(VertexShaderID,1,&glcpSource,NULL);
			glCompileShader(VertexShaderID);
			
			// lets check everything went ok
			GLint Result;
			int InfoLogLength = 0;
			glGetShaderiv(VertexShaderID,GL_COMPILE_STATUS,&Result);
			glGetShaderiv(VertexShaderID,GL_INFO_LOG_LENGTH,&InfoLogLength);

			if(Result != 1)
			{
				char* caLog = new char[InfoLogLength];
				glGetShaderInfoLog(VertexShaderID,InfoLogLength,NULL,caLog);
				OutputDebugString((std::string(" \nCompile Result: FAIL\n") + std::string(caLog) + std::string("\n")).c_str());
				delete[] caLog;
				return false;
			}
			else
			{
				OutputDebugString(std::string (" \nCompile Result: PASS\n").c_str());
				vVertShaders.push_back(VertexShaderID);
				glAttachShader(ProgramID,VertexShaderID);
			}

		} // end of vert shader loop

		//begin pixel shader loop
		INSTREAM >> uiSizeElement; // get number of Pixel shaders 
		uiNumberOfShaders = uiSizeElement;
		for(int i = 0; i != uiNumberOfShaders; ++i) // for each vert shader build it and track its name
		{											// for error reporting if needed. 
				
			INSTREAM >> uiSizeElement; // get size of shader name
			INSTREAM.read(cReader,uiSizeElement);
			std::string sShaderName = cReader;
			sShaderName.erase(uiSizeElement);

			// get shader source from file
			INSTREAM >> uiShaderSource;
			std::string sShaderSource;
			INSTREAM.read(cReader,uiShaderSource);
			sShaderSource = cReader;
			sShaderSource.erase(uiShaderSource);

			// compile the Pixel Shader
			OutputDebugString((std::string("\nCompiling Shader ") +  sShaderName).c_str());
			GLuint PixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			const GLchar* glcpSource = (const GLchar*)sShaderSource.c_str();
			glShaderSource(PixelShaderID,1,&glcpSource,NULL);
			glCompileShader(PixelShaderID);

			// lets check everything went ok
			GLint Result;
			int InfoLogLength = 0;
			glGetShaderiv(PixelShaderID,GL_COMPILE_STATUS,&Result);
			glGetShaderiv(PixelShaderID,GL_INFO_LOG_LENGTH,&InfoLogLength);

			if(Result != 1)
			{
				char* caLog = new char[InfoLogLength];
				glGetShaderInfoLog(PixelShaderID,InfoLogLength,NULL,caLog);
				OutputDebugString((std::string(" \nCompile Result: FAIL\n") + std::string(caLog) + std::string("\n")).c_str());
				delete[] caLog;
				return false;
			}
			else
			{
				OutputDebugString(std::string (" \nCompile Result: PASS\n").c_str());
				vPixelShaders.push_back(PixelShaderID);
				glAttachShader(ProgramID,PixelShaderID);
			}

		} // end Pixel shader loop


		//begin GEO shader loop
		INSTREAM >> uiSizeElement; // get number of Geo shaders 
		uiNumberOfShaders = uiSizeElement;
		for(int i = 0; i != uiNumberOfShaders; ++i) // for each vert shader build it and track its name
		{											// for error reporting if needed. 

			INSTREAM >> uiSizeElement; // get size of shader name
			INSTREAM.read(cReader,uiSizeElement);
			std::string sShaderName = cReader;
			sShaderName.erase(uiSizeElement);

			// get shader source from file
			INSTREAM >> uiShaderSource;
			std::string sShaderSource;
			INSTREAM.read(cReader,uiShaderSource);
			sShaderSource = cReader;
			sShaderSource.erase(uiShaderSource);

			// compile the Pixel Shader
			OutputDebugString((std::string("\nCompiling Shader ") +  sShaderName).c_str());
			GLuint GeoShaderID = glCreateShader(GL_GEOMETRY_SHADER);
			const GLchar* glcpSource = (const GLchar*)sShaderSource.c_str();
			glShaderSource(GeoShaderID,1,&glcpSource,NULL);
			glCompileShader(GeoShaderID);

			// lets check everything went ok
			GLint Result;
			int InfoLogLength = 0;
			glGetShaderiv(GeoShaderID,GL_COMPILE_STATUS,&Result);
			glGetShaderiv(GeoShaderID,GL_INFO_LOG_LENGTH,&InfoLogLength);

			if(Result != 1)
			{
				char* caLog = new char[InfoLogLength];
				glGetShaderInfoLog(GeoShaderID,InfoLogLength,NULL,caLog);
				OutputDebugString((std::string(" \nCompile Result: FAIL\n") + std::string(caLog) + std::string("\n")).c_str());
				delete[] caLog;
				return false;
			}
			else
			{
				OutputDebugString(std::string (" \nCompile Result: PASS\n").c_str());
				vgeoShaders.push_back(GeoShaderID);
				glAttachShader(ProgramID,GeoShaderID);
			}

		} // end geo shader loop

		//compile the shader program and check it worked
		glLinkProgram(ProgramID);
		GLint iResult;
		glGetProgramiv(ProgramID,GL_LINK_STATUS, &iResult);
		if(iResult != 1)
		{
			int InfoLogLength;
			glGetProgramiv(ProgramID,GL_INFO_LOG_LENGTH,&InfoLogLength);
			char* caLog = new char[InfoLogLength];
			glGetProgramInfoLog(ProgramID,InfoLogLength,NULL,caLog);
			OutputDebugString((std::string(" \nCompile Shader Program Result: FAIL\n") + std::string(caLog) + std::string("\n")).c_str());
			return false;
		}
		m_vProgramIDMap[a_sProgramName] = ProgramID;

		return true;
	}// end if File Can Open
	return false;
}




/*
BSF file type save structure
--------------------------------

Uint8 FileNameLength
string ProgramName
Uint8 Number of VertexShaders
 loop for count of vertexshaders
		Uint8 Size OF Source shader file name
		string shader file name with relative path
		Uint8 sizeofshaderfile
		string shader file content
 end loop

Uint8 Number of PixelShaders
 loop for count of pixel shaders
		Uint8 Size OF Source shader file name
		string shader file name with relative path
		Uint8 sizeofshaderfile
		string shader file content
 end loop

Uint8 Number of geoShaders
 loop for count of geo shaders
		Uint8 Size OF Source shader file name
		string shader file name with relative path
		Uint8 sizeofshaderfile
		string shader file content
 end loop

(more stuff needed) ( the defined shit )

--------------------------------
end of file strucute of BSF file type
*/