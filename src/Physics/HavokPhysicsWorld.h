//////////////////////////////////////////////////////////////////////////
/*! \class		HavokPhysicsWorld
 *  \brief		
 *	\details	
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		30/09/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _HAVOKPHYSICSWORLD_H_
# define _HAVOKPHYSICSWORLD_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "PhysicsWorld.h"

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/LargeBlock/hkLargeBlockAllocator.h>
#include <Common/Base/Memory/System/FreeList/hkFreeListMemorySystem.h>
#include <Common/Base/Fwd/hkcstdio.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Container/String/hkStringBuf.h>
#include <Common/Base/Fwd/hkcstdio.h>

// Dynamics includes
#include <Physics2012/Collide/hkpCollide.h>										
#include <Physics2012/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>	
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>					
#include <Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>				
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>					

#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>			
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>			

#include <Physics2012/Dynamics/World/hkpWorld.h>								
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>							
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>	


#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
#if defined(HK_PLATFORM_HAS_SPU)
#	include <Common/Base/Thread/Job/ThreadPool/Spu/hkSpuJobThreadPool.h>
#endif
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>


//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
class hkMallocAllocator;
class hkLargeBlockAllocator;
class hkFreeListAllocator;
class hkFreeListMemorySystem;
class hkMemorySystem;
class hkMemoryRouter;

//////////////////////////////////////////////////////////////////////////
class HavokPhysicsWorld : public PhysicsWorld
{
public:
	virtual const Rtti& GetType() const { return TYPE; }
	static const Rtti& Type() { return TYPE;}
	virtual operator Rtti() { return TYPE;}
	HavokPhysicsWorld();
	~HavokPhysicsWorld();
	
	static void HK_CALL errorReport(const char* msg, void* userContext)
	{
		using namespace std;
		printf("%s", msg);
	}
	
	
protected:
	static const Rtti TYPE;
	hkMallocAllocator m_kBaseMalloc;
	hkLargeBlockAllocator m_kLargeBlockAllocator;
	hkFreeListAllocator m_kFreeListAllocator;
	hkFreeListMemorySystem m_kMemorySystem;
	hkMemoryRouter* m_kpMemoryRouter;

private:

};

//////////////////////////////////////////////////////////////////////////
#endif // _HAVOKPHYSICSWORLD_H_
//////////////////////////////////////////////////////////////////////////