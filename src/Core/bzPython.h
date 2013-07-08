//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 7 - 4 - 2013 >
/// < Class Brief >	< Python wrapper class which wraps python and boost python. to make an easy api namespace free  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _BZPYTHON_H_
#define _BZPYTHON_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include <boost/python.hpp>
#include <Python.h>
#include <boost/container/string.hpp>
#include <boost/container/vector.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/stringize.hpp>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
namespace bp = boost::python;
#define bpObject bp::api::object

// this macro wraps the boost python macro and auto registers them to python. allowing less confusion
#define PYTHON_MODULE_INIT(name) \
	BOOST_PYTHON_MODULE(name); /* semicolon to turn the final function into a prototype */ \
namespace { /* namespace hides the varriable and function from everything freeing clutter in global namespace */ \
	PyMethodDef BOOST_PP_CAT(FixAccessViolation_,name)[] = { { 0, 0, 0, 0 } };  /* cant work out why this is needed for the life of me. just is.*/ \
	int BOOST_PP_CAT(PythonSelfRegister_,name)() \
{ /* this function block gets executed by the static which does the setup before main is called, order doesnt matter */ \
	bzPython::AddPythonModule(BOOST_PP_STRINGIZE(name),BOOST_PP_CAT(PyInit_,name)); \
	return 0; \
} \
 static int BOOST_PP_CAT(PySelfRegisterVar_,name) = BOOST_PP_CAT(PythonSelfRegister_,name)(); \
}; \
void BOOST_PP_CAT(init_module_, name)() // calls the final function from BOOST_PYTHON_MODULE so that it can be setup as per normal

#define PYTHON_MODULE(name) PYTHON_MODULE_INIT(name)


//////////////////////////////////////////////////////////////////////////
class bzPython
{
public:
	static bzPython* Create();
	virtual void Release();
	static bzPython* Get();
	static void AddPythonModule(const char* a_cpName, PyObject*(*a_fpInitfunc)());
	//static bool Exec(bp::detail::str_base a_sCommand, bp::api::object a_kGlobalObj = bp::api::object )
	static void exec(boost::python::str a_sCommand, const boost::python::api::object& a_kLocalNameSpace  = m_kLocalNamespace, const boost::python::api::object& a_kGlobalNameSpace  = m_kGlobalNamespace);
protected:
	bzPython();
	~bzPython();

	// this handles exceptions that occur and reports the issue to the console
	std::string parse_python_exception();
	static boost::python::api::object m_kLocalNamespace , m_kGlobalNamespace;
private:
	static bzPython* m_pInst;

};

//////////////////////////////////////////////////////////////////////////
#endif // _BZPYTHON_H_
//////////////////////////////////////////////////////////////////////////
