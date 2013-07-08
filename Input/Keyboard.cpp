//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 21/1/2013 >
/// < File >	< Keyboard >
/// < Brief >	< Keyboard Implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "Keyboard.h"
#include <Windows.h>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
Keyboard* Keyboard::m_pSingleton = nullptr;

Keyboard* Keyboard::Create()
{
	if(m_pSingleton == nullptr)
		m_pSingleton = new Keyboard();
	return m_pSingleton;
}

void Keyboard::Release()
{
	if(m_pSingleton)
		delete m_pSingleton;
}

Keyboard* Keyboard::Get()
{
	return m_pSingleton;
}

Keyboard::Keyboard()
{
	memset(m_acKeys,0,sizeof(char)*256);
	memset(m_acKeysPrevious,0,sizeof(char)*256);
}

Keyboard::~Keyboard()
{

}

void Keyboard::Update()
{
	memcpy(Keyboard::Get()->m_acKeysPrevious, Keyboard::Get()->m_acKeys,sizeof(char)*256);
	memset(Keyboard::Get()->m_acKeys,0,sizeof(char)*256);
	GetKeyboardState((PBYTE)Keyboard::Get()->m_acKeys);
}


/////////////////////////////////////////////////////////////////////
bool Keyboard::IsKeyUp(unsigned char a_cKey)
{
	return (Keyboard::Get()->m_acKeys[(a_cKey)] & 0xf000) == 0;
}


//////////////////////////////////////////////////////////////////////////
bool Keyboard::IsKeyDown(unsigned char a_cKey)
{
	return (Keyboard::Get()->m_acKeys[(a_cKey)] & 0xf000) != 0;
}


//////////////////////////////////////////////////////////////////////////
bool Keyboard::IsKeyPressed(unsigned char a_cKey)
{
	return (Keyboard::Get()->m_acKeys[(a_cKey)] & 0xf000) && 
		!(Keyboard::Get()->m_acKeysPrevious[(a_cKey)] & 0xf000);
}


//////////////////////////////////////////////////////////////////////////
bool Keyboard::IsKeyReleased(unsigned char a_cKey)
{
	return !(Keyboard::Get()->m_acKeys[(a_cKey)] & 0xf000) && 
		(Keyboard::Get()->m_acKeysPrevious[(a_cKey)] & 0xf000);
}