//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 5/2/2013 >
// < File >	< ITime >
// < Brief >	< ITime Class implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Includes 
#include "bzTime.h"
#include "bpPython.h"
//////////////////////////////////////////////////////////////////////////
bzTime* bzTime::m_pSingleton = nullptr;

/*! \defgroup bpTime
 *  \ingroup PyModules
 *  \brief Handles Time Based Functions 
 *  \details can be used to help find delta time or elapsed time.
 *	\todo Add Elapsed time to Python function list. 
 */
PYTHON_MODULE(bpTime)
{
/**  
	 * @addtogroup bpTime 
	 * @{
	 *		\page DeltaTime float DeltaTime()
	 *		This function returns a float which represents the current delta time of the application. 
	 */
	using namespace boost::python;
	def("DeltaTime",&bzTime::DeltaTime);

	/** @} */
}

//////////////////////////////////////////////////////////////////////////
bzTime::bzTime()
{
	m_liPrev.QuadPart = 0;
}

//////////////////////////////////////////////////////////////////////////
bzTime::~bzTime()
{

}

//////////////////////////////////////////////////////////////////////////
bzTime* bzTime::Create()
{
	if(m_pSingleton == nullptr)
		m_pSingleton = new bzTime();
	return m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
bzTime* bzTime::Get()
{
	return m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
void bzTime::Release()
{
	if(m_pSingleton != nullptr)
		delete m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
void bzTime::Update()
{
	LARGE_INTEGER liFreq;
	QueryPerformanceFrequency(&liFreq);

	LARGE_INTEGER liCurr;
	QueryPerformanceCounter(&liCurr);

	if(m_liPrev.QuadPart)
	{
		m_fDelta = (float)(liCurr.QuadPart - m_liPrev.QuadPart) / liFreq.QuadPart;
		if(m_fDelta > 1)
		{
			m_fDelta = 1;
		}
		else
		{
			m_fElapsed += m_fDelta;
		}
	}
	else
	{
		m_fDelta = 0;
	}

	m_liPrev = liCurr;
}

//////////////////////////////////////////////////////////////////////////
float bzTime::DeltaTime()
{
	return bzTime::Get()->m_fDelta;
}

//////////////////////////////////////////////////////////////////////////
float bzTime::ElapsedTime()
{
	return bzTime::Get()->m_fElapsed;
}