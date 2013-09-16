//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 7/4/2013 >
// < File >	< bpPython >
// < Brief >	< bpPython implementation. this handles wraping python. and making it simpiler to use boost::python to setup and shut down python. >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >
#include "bpPython.h"
#include <boost/filesystem.hpp>
//////////////////////////////////////////////////////////////////////////
// < Forward Declares >
bpPython* bpPython::m_pInst = nullptr;
boost::python::api::object bpPython::m_kGlobalNamespace = boost::python::api::object();
boost::python::api::object bpPython::m_kLocalNamespace = boost::python::api::object();

//////////////////////////////////////////////////////////////////////////
bpPython* bpPython::Create()
{
	return (m_pInst != nullptr) ? m_pInst : m_pInst = new bpPython();
}

//////////////////////////////////////////////////////////////////////////
void bpPython::Release()
{
	if(m_pInst != nullptr)
		delete m_pInst;
}

//////////////////////////////////////////////////////////////////////////
bpPython* bpPython::Get()
{
	return m_pInst;
}
 
//////////////////////////////////////////////////////////////////////////
bpPython::bpPython()
{
	PyMethodDef tmp[] = { { 0, 0, 0, 0 } }; // this stops the access violation wtf right.
	Py_SetProgramName((wchar_t*)"Python32");
	Py_Initialize();
	

	boost::python::api::object main_module = boost::python::import("__main__");
	m_kGlobalNamespace = main_module.attr("__dict__");
	m_kLocalNamespace = m_kGlobalNamespace;
	try
	{
		boost::filesystem::path pComplete;
		pComplete = boost::filesystem::complete(boost::filesystem::path());
		std::wstring oString = pComplete.wstring();
		oString.append(std::wstring(L"\\Data\\Scripts"));
		wchar_t* sOldPath = Py_GetPath();
		std::wstring sResult(sOldPath);
		sResult += std::wstring(L";") + oString;
		PySys_SetPath(sResult.c_str());

		boost::python::exec("import sys",m_kGlobalNamespace);
		boost::python::exec("sys.stdout = open(\"CONOUT$\", \"wt\");",m_kGlobalNamespace);
		//boost::python::exec(std::string("sys.path.append(\"" + oString + "\");").c_str(),m_kGlobalNamespace);
	}
	catch (boost::python::error_already_set const&)
	{
		std::string perror_str = bpPython::Get()->parse_python_exception();
#ifdef _DEBUG
		std::cout << "Error in Python:\nType: " << perror_str << std::endl;
#endif
	}


}

//////////////////////////////////////////////////////////////////////////
bpPython::~bpPython()
{
	Py_Finalize();
}

//////////////////////////////////////////////////////////////////////////
void bpPython::AddPythonModule(const char* a_cpName, PyObject*(*a_fpInitFunc)())
{
	PyImport_AppendInittab(a_cpName,a_fpInitFunc);
}


//////////////////////////////////////////////////////////////////////////
void bpPython::exec(boost::python::str a_sCommand, const boost::python::api::object& a_kLocalNameSpace /* = m_kLocalNamespace */, const boost::python::api::object& a_kGlobalNameSpace /* = m_kGlobalNamespace */)
{
	try
	{ 
		
		boost::python::exec(a_sCommand,a_kGlobalNameSpace,a_kLocalNameSpace);
	}
	catch (boost::python::error_already_set const&)
	{
		std::string perror_str = bpPython::Get()->parse_python_exception();
#ifdef _DEBUG
		std::cout << "Error in Python:\nType: " << perror_str << std::endl;
#endif
	}

}

//////////////////////////////////////////////////////////////////////////
std::string bpPython::parse_python_exception() 
{
	PyObject* type_ptr = nullptr;
	PyObject* value_ptr = nullptr;
	PyObject* traceback_ptr = nullptr;

	PyErr_Fetch(&type_ptr,&value_ptr,&traceback_ptr);
	std::string ret("Unfetchable Python error");
	if(type_ptr != nullptr)
	{

		boost::python::handle<> h_type(type_ptr);
		boost::python::str type_pstr(h_type);
		boost::python::extract<std::string> e_type_pstr(type_pstr);
		if(e_type_pstr.check())
			ret = e_type_pstr;
		else
			ret = "Unknown exception type";
	}

	if(value_ptr != nullptr)
	{
		boost::python::handle<> h_val(value_ptr);
		boost::python::str a(h_val);
		boost::python::extract<std::string> returned(a);
		if(returned.check())
			ret += "\nValue: " + returned();
		else
			ret += std::string("\n: Unparseable Python error: ");
	}
	
	if(traceback_ptr != nullptr)
	{
		boost::python::handle<> h_tb(traceback_ptr);
		boost::python::object tb(boost::python::import("traceback"));
		boost::python::object fmt_tb(tb.attr("format_tb"));
		boost::python::object tb_list(fmt_tb(h_tb));
		boost::python::object tb_str(boost::python::str("\n").join(tb_list));
		boost::python::extract<std::string> returned(tb_str);
		if(returned.check())
			ret += "\nTraceBack: " + returned();
		else
			ret += std::string("\n: Unparseable Python traceback");
	}

	return ret;
}