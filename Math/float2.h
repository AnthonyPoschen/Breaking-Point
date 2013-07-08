//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 6 - 12 - 2012 >
/// < Class Brief >	< float2 math class. for 2d vectors  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _FLOAT2_H_
#define _FLOAT2_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >

//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class float2
{

public:
	float2();
	float2(float a_X,float a_Y);
	float2(const float2& a_kVec);
	~float2();
	float X , Y;

	/* Returns Distance From 0 */
	float Length() const;
	float SqrLength() const;
	/* converts the vector to being out of 1. and returns the number needed to convert back */
	float Unitise();
	static float UnitiseVector(float2 &a_kVec);
	/* returns a float repreenting the dot product of the vector */
	float DotProduct(const float2 &a_kVec);


	float2 PerpendicularRight();
	float2 PerpendiculerLeft();

	/////////////////////////////////////////////////////////////////////////////////////////////
	/// Brief:	<A Vector between two points determined by time>
	/// Return	<A Vector on the plane of two points>
	/////////////////////////////////////////////////////////////////////////////////////////////
	static float2 Lerp(const float2& a_kBegin,const float2 &a_kEnd,const float a_fTime);

	float2 operator + (const float2 &a_kTarget);
	float2 operator - (const float2 &a_kTarget);
	float2 operator * (const float2 &a_kTarget);
	float2 operator / (const float2 &a_kTarget);
	float2 operator * (const float &a_fScale);
	float2 operator / (const float &a_fScale);


	void operator = (const float2 &a_Target);
	bool operator == (const float2 &a_Target);
	float2 operator - ();
	bool operator != (const float2 &a_Target);
	void operator += (const float2 &a_Target);
	void operator -= (const float2 &a_Target);
	void operator *= (const float2 &a_Target);
	void operator /= (const float2 &a_Target);
	void operator *= (const float &a_fScale);
	void operator /= (const float &a_fScale);
	bool operator < (const float2 &a_Target);
	bool operator > (const float2 &a_Target);
};
//////////////////////////////////////////////////////////////////////////
#endif // _FLOAT2_H_
//////////////////////////////////////////////////////////////////////////
