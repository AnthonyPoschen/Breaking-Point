//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 5/12/2012 >
/// < File >	< UniversalTypes >
/// < Brief >	< define our own types. to make things simplier.  >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >


//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////

typedef bool                Bool;

typedef char                Char;
typedef unsigned short      WChar;

typedef __int8              SInt8;
typedef unsigned __int8     UInt8;

#define BZ_SINT8_MAX        (127)
#define BZ_UINT8_MAX        (255)

typedef __int16             SInt16;
typedef unsigned __int16    UInt16;

#define BZ_SINT16_MAX       (32767)
#define BZ_UINT16_MAX       (65535)

typedef __int32             SInt32;
typedef unsigned __int32    UInt32;

#define BZ_SINT32_MAX       (2147483647)
#define BZ_UINT32_MAX       (4294967295)

typedef __int64             SInt64;
typedef unsigned __int64    UInt64;

#define BZ_SINT64_MAX       (9223372036854775807ll)
#define BZ_UINT64_MAX       (18446744073709551615ull)

typedef float               Float32;
typedef double              Float64;