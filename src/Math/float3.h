//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 10 - 12 - 2012 >
/// < Class Brief >	< Implementation of float3 x,y,z / r,g,b  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _float3_H_
#define _float3_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >

//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class float3
{
public:
	float3();
	float3(const float3 &a_kVec);
	float3( float a_fX, float a_fY, float a_fZ);
	~float3();
	union 
	{
		struct  
		{
			float X,Y,Z;
		};
		struct 
		{
			float R,G,B;
		};
	};
	/* Returns the exact length of the Vector */
	float Length() const;
	/* Returns the Squared Length of the Vector */
	float SqrLength() const;
	/* Returns a Vector Parallel to Both Vectors*/
	float3 Cross( const float3 &a_kVec)  const;
	/* Returns the Dot Product of two Vectors */
	float Dot(const float3 &a_kVec)  const;
	/* Converts the Vector to being out of 1 and returns value to convert back */
	float Unitise();
	/* Converts the Vector to being out of 1 and returns value to convert back */
	static float UnitiseVector(float3 &a_kVec);
	/* Lerps between two points based on a time (0-1) */
	static float3 Lerp(const float3 &a_kBegin , const float3 &a_kEnd , const float a_fTime);

	float3 operator + (const float3 &a_kVec) const;
	float3 operator - (const float3 &a_kVec) const;
	float3 operator * (const float3 &a_kVec) const;
	float3 operator / (const float3 &a_kVec) const;
	float3 operator * (const float &a_fValue) const;
	float3 operator / (const float &a_fValue) const;

	void operator += (const float3 &a_kVec);
	void operator -= (const float3 &a_kVec);
	void operator *= (const float3 &a_kVec);
	void operator /= (const float3 &a_kVec);
	void operator *= (const float &a_fValue);
	void operator /= (const float &a_fValue);

	float3 operator - ();
	bool operator != (const float3 &a_kVec) const;
	bool operator == (const float3 &a_kVec) const;
	void operator = (const float3 &a_kVec);
	bool operator > (const float3 &a_kVec) const;
	bool operator < (const float3 &a_kVec) const;
protected:
	

private:

};
//////////////////////////////////////////////////////////////////////////
#endif // _float3_H_
//////////////////////////////////////////////////////////////////////////
