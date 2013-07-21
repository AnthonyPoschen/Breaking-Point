//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 10/12/2012 >
/// < File >	< CoreMath >
/// < Brief >	< Core Math standard functions >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "CoreMath.h"
#include "../Core/bpPython.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
/// < Setup Python Access>
PYTHON_MODULE(bzMath)
{
	using namespace boost::python;

	// Float2 Setup
	class_<float2>("float2")
		.def(init<float,float>())
		.def(init<float2>())
		.def("Length",&float2::Length)
		.def("SqrLength",&float2::SqrLength)
		.def("Unitise",&float2::Unitise)
		.def("Dot",&float2::DotProduct)
		.add_property("X",&float2::X,&float2::X,"this is the X Cordinate")
		.add_property("Y",&float2::Y,&float2::Y,"this is the Y Cordinate")
		//operator overloads
		.def(self + self)
		.def(self - self)
		.def(self * self)
		.def(self / self)
		.def(self * float())
		.def(self / float())
		.def(self == self)
		.def(-self)
		.def(self != self)
		.def(self += self)
		.def(self -= self)
		.def(self *= self)
		.def(self /= self)
		.def(self *= float())
		.def(self /= float())
		.def(self < self)
		.def(self > self);
	// end Float2 setup
	// float3 setup
	class_<float3>("float3")
		.def(init<float,float,float>())
		.def(init<float3>())
		.def("Length",&float3::Length)
		.def("SqrLength",&float3::SqrLength)
		.def("Cross",&float3::Cross)
		.def("Dot",&float3::Dot)
		.def("Unitise",&float3::Unitise)
		.def("Lerp",&float3::Lerp)

		.def(self + self)
		.def(self - self)
		.def(self * self)
		.def(self / self)
		.def(self * float())
		.def(self / float())
		.def(self += self)
		.def(self -= self)
		.def(self *= self)
		.def(self /= self)
		.def(self *= float())
		.def(self /= float())
		.def(-self)
		.def(self != self)
		.def(self == self)
		.def(self < self)
		.def(self > self);
	//end float3 setup

	//float4 setup
	class_<float4>("float4")
		.def(init<float,float,float,float>())
		.def(init<float4>())
		.def("Length",&float4::Length)
		.def("Unitise",&float4::Unitise)
		.def("Lerp",&float4::Lerp)
		
		.def(self + self)
		.def(self - self)
		.def(self * self)
		.def(self / self)
		.def(self * float())
		.def(self / float())
		.def(self += self)
		.def(self -= self)
		.def(self *= self)
		.def(self /= self)
		.def(self *= float())
		.def(self /= float())
		.def(-self)
		.def(self != self)
		.def(self == self)
		.def(self < self)
		.def(self > self);


	//////////////////////////////////////////////////////////////////////////
	/// <bzMath Global Scope Funcitons>
	def("UnitiseVector",&float2::UnitiseVector);
	def("UnitiseVector",&float3::UnitiseVector);
	def("UnitiseVector",&float4::UnitiseVector);
}

__declspec (naked) float __fastcall bzSqrt(float a_fValue)
{
	_asm fld dword ptr [esp+4]
	_asm fsqrt
	_asm ret 4
	a_fValue;
}

float bzFastInvSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x;         // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);  // what the fuck?
	x = *(float*)&i;
	x = x*(1.5f-(xhalf*x*x));
	return x;
}