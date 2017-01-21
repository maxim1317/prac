//
// Basic class for 3d vectors.
// Supports all basic vector operations
//
// Author: Alex V. Boreskoff
//
// Last change: 1/12/2002
//

#ifndef	__VECTOR3D__
#define	__VECTOR3D__

#include	<math.h>

#define	EPS	0.0001f

#ifndef	M_PI								// since not all compilers define it						
#define M_PI        3.14159265358979323846f
#endif

class	Vector3D
{
public:
	float	x, y, z;

	Vector3D () {}
	Vector3D ( float px, float py, float pz )
	{
		x = px;
		y = py;
		z = pz;
	}

	Vector3D ( const Vector3D& v )
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	Vector3D& operator = ( const Vector3D& v )
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	Vector3D operator + () const
	{
		return *this;
	}

	Vector3D operator - () const
	{
		return Vector3D ( -x, -y, -z );
	}

	Vector3D& operator += ( const Vector3D& v )
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	Vector3D& operator -= ( const Vector3D& v )
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3D& operator *= ( const Vector3D& v )
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;
	}

	Vector3D& operator *= ( float f )
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	Vector3D& operator /= ( const Vector3D& v )
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;

		return *this;
	}

	Vector3D& operator /= ( float f )
	{
		x /= f;
		y /= f;
		z /= f;

		return *this;
	}

	float& operator [] ( int index )
	{
		return * ( index + &x );
	}

	float operator [] ( int index ) const
	{
		return * ( index + &x );
	}

	int	operator == ( const Vector3D& v ) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	int	operator != ( const Vector3D& v ) const
	{
		return x != v.x || y != v.y || z != v.z;
	}

	operator float * ()
	{
		return &x;
	}

	operator const float * () const
	{
		return &x;
	}

	float	length () const
	{
		return (float) sqrt ( x * x + y * y + z * z );
	}

    float   lengthSq () const
    {
        return x * x + y * y + z * z;
    }

	Vector3D&	normalize ()
	{
		return (*this) /= length ();
	}

    float   maxLength () const
    {
        return max3 ( (float)fabs (x), (float)fabs (y), (float)fabs (z) );
    }

    float   distanceToSq ( const Vector3D& p ) const
    {
        return sqr ( x - p.x ) + sqr ( y - p.y ) + sqr ( z - p.z );
    }

    float   distanceTo ( const Vector3D& p ) const
    {
        return (float)sqrt ( sqr ( x - p.x ) + sqr ( y - p.y ) + sqr ( z - p.z ) );
    }

	float	distanceToAlongAxis ( const Vector3D& p, int axis ) const
	{
		return (float)fabs ( operator [] ( axis ) - p [axis] );
	}

	int	getMainAxis () const
	{
		int		axis = 0;
		float	val  = (float) fabs ( x );

		for ( register int i = 1; i < 3; i++ )
		{
			float	vNew = (float) fabs ( operator [] ( i ) );

			if ( vNew > val )
			{
				val  = vNew;
				axis = i;
			}
		}

		return axis;
	}

	Vector3D&	clamp ( float lower, float upper )
	{
		if ( x < lower )
			x = lower;
		else
		if ( x > upper )
			x = upper;

		if ( y < lower )
			y = lower;
		else
		if ( y > upper )
			y = upper;
			
		if ( z < lower )
			z = lower;
		else
		if ( z > upper )
			z = upper;

		return *this;
	}

	static	Vector3D	getRandomVector ( float len = 1 );

	friend Vector3D operator + ( const Vector3D&, const Vector3D& );
	friend Vector3D operator - ( const Vector3D&, const Vector3D& );
	friend Vector3D operator * ( const Vector3D&, const Vector3D& );
	friend Vector3D operator * ( float,           const Vector3D& );
	friend Vector3D operator * ( const Vector3D&, float );
	friend Vector3D operator / ( const Vector3D&, float );
	friend Vector3D operator / ( const Vector3D&, const Vector3D& );
	friend float    operator & ( const Vector3D&, const Vector3D& );
	friend Vector3D operator ^ ( const Vector3D&, const Vector3D& );

private:
    float   max3 ( float a, float b, float c ) const
    {
        return a > b ? (a > c ? a : (b > c ? b : c)) :
                       (b > c ? b : (a > c ? a : c));
    }

    float   sqr ( float x ) const
    {
        return x*x;
    }
};

inline Vector3D operator + ( const Vector3D& u, const Vector3D& v )
{
	return Vector3D ( u.x + v.x, u.y + v.y, u.z + v.z );
}

inline Vector3D operator - ( const Vector3D& u, const Vector3D& v )
{
	return Vector3D ( u.x - v.x, u.y - v.y, u.z - v.z );
}

inline Vector3D operator * ( const Vector3D& u, const Vector3D& v )
{
	return Vector3D ( u.x*v.x, u.y*v.y, u.z * v.z );
}

inline Vector3D operator * ( const Vector3D& v, float a )
{
	return Vector3D ( v.x*a, v.y*a, v.z*a );
}

inline Vector3D operator * ( float a, const Vector3D& v )
{
	return Vector3D ( v.x*a, v.y*a, v.z*a );
}

inline Vector3D operator / ( const Vector3D& u, const Vector3D& v )
{
	return Vector3D ( u.x/v.x, u.y/v.y, u.z/v.z );
}

inline Vector3D operator / ( const Vector3D& v, float a )
{
	return Vector3D ( v.x/a, v.y/a, v.z/a );
}

inline Vector3D operator / ( float a, const Vector3D& v )
{
	return Vector3D ( a / v.x, a / v.y, a / v.z );
}

inline float operator & ( const Vector3D& u, const Vector3D& v )
{
	return u.x*v.x + u.y*v.y + u.z*v.z;
}

inline Vector3D operator ^ ( const Vector3D& u, const Vector3D& v )
{
	return Vector3D (u.y*v.z-u.z*v.y, u.z*v.x-u.x*v.z, u.x*v.y-u.y*v.x);
}

inline	Vector3D lerp ( const Vector3D& a, const Vector3D& b, float t )
{
	return a + t * (b - a);
}

inline	float	mixedProduct ( const Vector3D& a, const Vector3D& b, const Vector3D& c )
{
	return ( a & ( b ^ c ) );
}

inline	bool	areCollinear ( const Vector3D& a, const Vector3D& b, const Vector3D& c )
{
	return ((b - a) ^ (c - a)).lengthSq () < EPS * EPS;
}

inline	bool	areComplanar ( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d )
{
	return fabs ( mixedProduct ( b - a, c - a, d - a ) ) < EPS * EPS * EPS;
}

inline	Vector3D	getNormal ( const Vector3D& a, const Vector3D& b, const Vector3D& c )
{
	return ((a - b) ^ (c - b)).normalize();
}

#endif
