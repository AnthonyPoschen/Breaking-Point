//////////////////////////////////////////////////////////////////////////
/*! \class		PhysicsWorld
 *  \brief		
 *	\details	
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		16/09/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _PhysicsWorld_H_
# define _PhysicsWorld_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "../core/Object.h"
/*
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Memory/Allocator/LargeBlock/hkLargeBlockAllocator.h>
#include <Common/Base/Memory/System/FreeList/hkFreeListMemorySystem.h>
#include <Common/Base/Fwd/hkcstdio.h>
// Platform specific initialization
#include <Common/Base/System/Init/PlatformInit.cxx>

*/
//////////////////////////////////////////////////////////////////////////
//  Forward Declares 


//////////////////////////////////////////////////////////////////////////
class PhysicsWorld :public Object
{
public:
	virtual const Rtti& GetType() const { return TYPE; }
	static const Rtti& Type() { return TYPE;}
	virtual operator Rtti() { return TYPE;}
	PhysicsWorld();
	virtual ~PhysicsWorld();
	
protected:
	static const Rtti TYPE;
private:
	
};

//////////////////////////////////////////////////////////////////////////
#endif // _PhysicsWorld_H_
//////////////////////////////////////////////////////////////////////////