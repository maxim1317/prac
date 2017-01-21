//////////////////////////////////////////////////////////////////////////////////////////
//	Vector4D.h
//	Class declaration for a 4d vector
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	8th November 2002	-	Changed Constructor layout
//									-	Some speed Improvements
//									-	Corrected Lerp
//				7th January 2003	-	Added QuadraticInterpolate
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef Vector4D_H
#define Vector4D_H

#include "Vector3D.h"

class Vector4D
{
public:
	//constructors
	Vector4D(void)	:	x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}

	Vector4D(float newX, float newY, float newZ, float newW)	
		:	x(newX), y(newY), z(newZ), w(newW)
	{}

	Vector4D(const float * rhs)	:	x(*rhs), y(*(rhs+1)), z(*(rhs+2)), w(*(rhs+3))
	{}

	Vector4D(const Vector4D & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
	{}

	//convert v3d to v4d
	Vector4D(const Vector3D & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
	{}

	~Vector4D() {}	//empty

	void Set(float newX, float newY, float newZ, float newW)
	{	x=newX;	y=newY;	z=newZ; w=newW;	}
	
	//accessors kept for compatability
	void SetX(float newX) {x = newX;}
	void SetY(float newY) {y = newY;}
	void SetZ(float newZ) {z = newZ;}
	void SetW(float newW) {w = newW;}
	
	float GetX() const {return x;}	//public accessor functions
	float GetY() const {return y;}	//inline, const
	float GetZ() const {return z;}
	float GetW() const {return w;}

	void LoadZero(void)
	{	x=0.0f; y=0.0f; z=0.0f; w=0.0f;	}

	void LoadOne(void)
	{	x=1.0f; y=1.0f; z=1.0f; w=1.0f;	}

	//vector algebra
	float DotProduct(const Vector4D & rhs)
	{	return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;	}

	//rotations
	void RotateX(double angle);
	Vector4D GetRotatedX(double angle) const;
	void RotateY(double angle);
	Vector4D GetRotatedY(double angle) const;
	void RotateZ(double angle);
	Vector4D GetRotatedZ(double angle) const;
	void RotateAxis(double angle, const Vector3D & axis);
	Vector4D GetRotatedAxis(double angle, const Vector3D & axis) const;
	
	Vector4D lerp(const Vector4D & v2, float factor) const
	{	return (*this)*(1.0f-factor)+v2*factor;	}

	Vector4D QuadraticInterpolate(const Vector4D & v2, const Vector4D & v3, float factor) const
	{	return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor;}

	//binary operators
	Vector4D operator+(const Vector4D & rhs) const
	{	return Vector4D(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);	}

	Vector4D operator-(const Vector4D & rhs) const
	{	return Vector4D(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);	}

	Vector4D operator*(const float rhs) const
	{	return Vector4D(x*rhs, y*rhs, z*rhs, w*rhs);	}

	Vector4D operator/(const float rhs) const
	{	return rhs==0.0f	?	Vector4D(0.0f, 0.0f, 0.0f, 0.0f)
							:	Vector4D(x/rhs, y/rhs, z/rhs, w/rhs);	}

	//multiply by a float, eg 3*v
	friend Vector4D operator*(float scaleFactor, const Vector4D & rhs);

	bool operator==(const Vector4D & rhs) const;
	bool operator!=(const Vector4D & rhs) const
	{	return !((*this)==rhs);	}

	//self-add etc
	void operator+=(const Vector4D & rhs)
	{	x+=rhs.x; y+=rhs.y; z+=rhs.z; w+=rhs.w;	}

	void operator-=(const Vector4D & rhs)
	{	x-=rhs.x; y-=rhs.y; z-=rhs.z; w-=rhs.w;	}

	void operator*=(const float rhs)
	{	x*=rhs; y*=rhs; z*=rhs; w*=rhs;	}

	void operator/=(const float rhs)
	{	if(rhs==0.0f)
			return;
		else
		{	x/=rhs; y/=rhs; z/=rhs; w/=rhs;	}
	}

	//unary operators
	Vector4D operator-(void) const {return Vector4D(-x, -y, -z, -w);}
	Vector4D operator+(void) const {return (*this);}

	//cast to pointer to float for glVertex4fv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	operator Vector3D();							//convert v4d to v3d

	//member variables
	float x;
	float y;
	float z;
	float w;
};

#endif	//Vector3D_H