//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 10 - 12 - 2012 >
/// < Class Brief >	< Implementation of float4 x,y,z,w / r,g,b,a  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _FLOAT4_H_
#define _FLOAT4_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >

//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class float4
{
public:
	float4();
	float4(const float4 &a_kVec);
	float4( float a_fX, float a_fY, float a_fZ, float a_fW);
	~float4();
	union 
	{
		struct  
		{
			float X,Y,Z,W;
		};
		struct 
		{
			float R,G,B,A;
		};
	};
	float Length() const;
	float Unitise();
	static float UnitiseVector(float4 &a_kVec);

	static float4 Lerp(const float4 &a_kBegin , const float4 &a_kEnd , const float &a_fTime);

	float4 operator + (const float4 &a_kVec);
	float4 operator - (const float4 &a_kVec);
	float4 operator * (const float4 &a_kVec);
	float4 operator / (const float4 &a_kVec);
	float4 operator * (const float &a_fValue);
	float4 operator / (const float &a_fValue);

	void operator += (const float4 &a_kVec);
	void operator -= (const float4 &a_kVec);
	void operator *= (const float4 &a_kVec);
	void operator /= (const float4 &a_kVec);
	void operator *= (const float &a_fValue);
	void operator /= (const float &a_fValue);

	float4 operator - ();
	bool operator != (const float4 &a_kVec);
	bool operator == (const float4 &a_kVec);
	void operator = (const float4 &a_kVec);
	bool operator > (const float4 &a_kVec);
	bool operator < (const float4 &a_kVec);
protected:
	

private:

};
//////////////////////////////////////////////////////////////////////////
#endif // _FLOAT4_H_
//////////////////////////////////////////////////////////////////////////
