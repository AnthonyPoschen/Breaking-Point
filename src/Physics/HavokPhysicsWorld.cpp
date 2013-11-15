//////////////////////////////////////////////////////////////////////////
/*! \class		HavokPhysicsWorld
 *  \brief		
 *	\details	
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		16/09/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "HavokPhysicsWorld.h"

				

// Keycode
#include <Common/Base/keycode.cxx>

// This excludes libraries that are not going to be linked
// from the project configuration, even if the keycodes are
// present

#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR
#undef HK_FEATURE_PRODUCT_PHYSICS
#define HK_FEATURE_REFLECTION_PHYSICS_2012
#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkClasses.h>
#define HK_EXCLUDE_FEATURE_MemoryTracker
#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches 
#define HK_EXCLUDE_LIBRARY_hkGeometryUtilities
#include <Common/Base/Config/hkProductFeatures.cxx>

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
const Rtti HavokPhysicsWorld::TYPE("HavokPhysicsWorld",&Object::TYPE);

//////////////////////////////////////////////////////////////////////////
HavokPhysicsWorld::HavokPhysicsWorld()
	:m_kLargeBlockAllocator(&m_kBaseMalloc),
	m_kFreeListAllocator(&m_kLargeBlockAllocator,&m_kLargeBlockAllocator),
	m_kMemorySystem(&m_kBaseMalloc,&m_kFreeListAllocator,&m_kFreeListAllocator)
{
	hkMemorySystem::replaceInstance(&m_kMemorySystem);
	m_kpMemoryRouter = m_kMemorySystem.mainInit(hkMemorySystem::FrameInfo(1024));

	hkBaseSystem::init( m_kpMemoryRouter, errorReport );
	{
		HK_WARN_ALWAYS(0x417ffd72, "Hello world!");
	}
	
}

HavokPhysicsWorld::~HavokPhysicsWorld()
{
	//hkBaseSystem::quit();
	//m_kMemorySystem.mainQuit();
}