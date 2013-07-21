//////////////////////////////////////////////////////////////////////////
/*! \class		bzTime
 *  \brief		This class handles Time Management. classes abstract from this to form clocks and add functionality.
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		05/02/2013
 *  \copyright  N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _BZTIME_H_
# define _BZTIME_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 


//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
#include <Windows.h>

//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class bzTime
{
public:
	/*! \brief Creates the singleton.
	 *  \return bzTime* - to singleton.
	 *	\sa bzTime::get()
	 *	\sa bzTime::Release()
	 */
	static bzTime*	Create();

	/*! \brief This returns the Time singleton
	 *  \return bzTime* - to singleton object.
	 */
	static bzTime*	Get();

	/*! \brief Releases the singleton
	 */
	void			Release();

	/*! \brief Updates the Time object. this should be called once per program loop so that bzTime::DeltaTime() & bzTime::ElapsedTime() return accurate results
	 */
	void			Update();

	/*! \brief This returns the current time since the last time bzTime::Update() was called.
	 *  \return float - time since last update.
	 *	\sa bzTime::DeltaTime()
	 */
	static float	DeltaTime();

	/*! \brief This returns a float which represents the time since program started
	 *  \return float - time since program start. 
	 *	\sa bzTime::DeltaTime()
	 */
	static float	ElapsedTime();

protected:
	

private:
	bzTime();
	~bzTime();

	static bzTime*	m_pSingleton;//!<	Singleton Object.
	
	LARGE_INTEGER	m_liPrev;//!<		Holds windows machine time of the previous time call. this is used to help calculate the delta in update
	float			m_fDelta;//!<		this is the current delta time of the object.
	float			m_fElapsed;//!<		this holds the total time since the program has started. 
};
//////////////////////////////////////////////////////////////////////////
#endif // _BZTIME_H_
//////////////////////////////////////////////////////////////////////////
