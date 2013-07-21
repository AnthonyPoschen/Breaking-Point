//////////////////////////////////////////////////////////////////////////
/*! \class		bpPython
 *  \brief      Python Wrapper 
 *  \details    this class wraps Standard Python. and Boost Python. allowing easy module extention to scripts
 *  \author     Anthony Poschen
 *  \version    1.0
 *  \date       7 / 04 / 2013
 *  \copyright  N/A
 */

//////////////////////////////////////////////////////////////////////////
// File Define
#ifndef _BPPYTHON_H_
#define _BPPYTHON_H_
//////////////////////////////////////////////////////////////////////////
// Includes
#include <boost/python.hpp>
#include <Python.h>
#include <boost/container/string.hpp>
#include <boost/container/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
//////////////////////////////////////////////////////////////////////////
// Forward Declares 

#define bpObject boost::python::api::object

// this macro wraps the boost python macro and auto registers them to python. allowing less confusion
#define PYTHON_MODULE_INIT(name) \
	BOOST_PYTHON_MODULE(name); /* semicolon to turn the final function into a prototype */ \
namespace { /* namespace hides the varriable and function from everything freeing clutter in global namespace */ \
	PyMethodDef BOOST_PP_CAT(FixAccessViolation_,name)[] = { { 0, 0, 0, 0 } };  /* cant work out why this is needed for the life of me. just is.*/ \
	int BOOST_PP_CAT(PythonSelfRegister_,name)() \
{ /* this function block gets executed by the static which does the setup before main is called, order doesnt matter */ \
	bpPython::AddPythonModule(BOOST_PP_STRINGIZE(name),BOOST_PP_CAT(PyInit_,name)); \
	return 0; \
} \
 static int BOOST_PP_CAT(PySelfRegisterVar_,name) = BOOST_PP_CAT(PythonSelfRegister_,name)(); \
}; \
void BOOST_PP_CAT(init_module_, name)() // calls the final function from BOOST_PYTHON_MODULE so that it can be setup as per normal

/*! \brief This wraps BOOST_PYTHON_MODULE(name). this wrapper automatically makes it accessible from scripts at runtime before the main function is called. this is a function header so should be proceded by { ...module stuff }
 *  \param name - name of the Module
 */
#define PYTHON_MODULE(name) PYTHON_MODULE_INIT(name)


//////////////////////////////////////////////////////////////////////////
class bpPython
{
public:

	/*! \brief Create The Singleton. this is a singleton class only 1 instance will ever be active
	 *  \return bpPython instance
	 */
	static bpPython* Create();
	
	/*! \brief Frees the singleton from memory
	 */
	virtual void Release();

	/*! \brief Get the Singleton instance
	 *  \return bpPython instance
	 */
	static bpPython* Get();

	/*! \brief Make a locally defined Python Module accessible from scripts. this function should not be called as it is done automatically by the PYTHON_MODULE() macro  
	 *  \param a_cpName - Name of the module
	 *	\param a_fpInitfunc - function pointer to entry point of the module
	 *	\sa PYTHON_MODULE(name)
	 */
	static void AddPythonModule(const char* a_cpName, PyObject*(*a_fpInitfunc)());
	//static bool Exec(bp::detail::str_base a_sCommand, bp::api::object a_kGlobalObj = bp::api::object )

	/*! \brief exec python commands. This Wrapper adds a more friendly stack tracer in the event an error occurs the error is automatically outputed to stdout. 
	 *  \param a_sCommand - the python command to be executed
	 *	\param a_kLocalNameSpace - The Local Namespace used.
	 *	\param a_kGlobalNameSpace - The Global Namespace used.
	 */
	static void exec(boost::python::str a_sCommand, const boost::python::api::object& a_kLocalNameSpace  = m_kLocalNamespace, const boost::python::api::object& a_kGlobalNameSpace  = m_kGlobalNamespace);
protected:
	bpPython();
	~bpPython();

	// this handles exceptions that occur and reports the issue to the console

	/*! \brief error parser. this is called when an error is occured from python code. and returns a formated output to be put wherever necesery (output , stdout , logfile? )
	 *  \return string - formated string with error details
	 */
	std::string parse_python_exception();

	static boost::python::api::object m_kLocalNamespace , m_kGlobalNamespace;//!<	NameSpace for python to avoid cluttering global namespace with garbage.
private:
	static bpPython* m_pInst;//!<	Singleton Instance

};

//////////////////////////////////////////////////////////////////////////
#endif // _bpPython_H_
//////////////////////////////////////////////////////////////////////////
