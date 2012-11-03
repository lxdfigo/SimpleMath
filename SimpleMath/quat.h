#ifndef __QUAT_H
#define __QUAT_H

#include "Vector.h"

template<class T>
class  Quat{
public:
	T  Elements[4];   

	inline Quat() { Elements[0]=0.0; Elements[1]=0.0; Elements[2]=0.0; Elements[3]=1.0; }
	inline Quat( T x, T y, T z, T w ){
		Elements[0]=x;
		Elements[1]=y;
		Elements[2]=z;
		Elements[3]=w;
	}

	inline Quat( const CVector<T,4>& v ) {
		Elements[0]=v.Elements[0];
		Elements[1]=v.Elements[1];
		Elements[2]=v.Elements[2];
		Elements[3]=v.Elements[3];
	}

	inline Quat( T angle, const CVector<T,3>& axis){
		makeRotate(angle,axis);
	}

	inline Quat& operator = (const Quat& v) { Elements[0]=v.Elements[0];  Elements[1]=v.Elements[1]; Elements[2]=v.Elements[2]; Elements[3]=v.Elements[3]; return *this; }

	inline bool operator == (const Quat& v) const { return Elements[0]==v.Elements[0] && Elements[1]==v.Elements[1] && Elements[2]==v.Elements[2] && Elements[3]==v.Elements[3]; }

	inline bool operator != (const Quat& v) const { return Elements[0]!=v.Elements[0] || Elements[1]!=v.Elements[1] || Elements[2]!=v.Elements[2] || Elements[3]!=v.Elements[3]; }

	inline bool operator <  (const Quat& v) const{
		if (Elements[0]<v.Elements[0]) return true;
		else if (Elements[0]>v.Elements[0]) return false;
		else if (Elements[1]<v.Elements[1]) return true;
		else if (Elements[1]>v.Elements[1]) return false;
		else if (Elements[2]<v.Elements[2]) return true;
		else if (Elements[2]>v.Elements[2]) return false;
		else return (Elements[3]<v.Elements[3]);
	}

	inline void set(T x, T y, T z, T w) {
		Elements[0]=x;
		Elements[1]=y;
		Elements[2]=z;
		Elements[3]=w;
	}

	inline T & operator [] (int i) { return Elements[i]; }
	inline T   operator [] (int i) const { return Elements[i]; }

	inline T & x() { return Elements[0]; }
	inline T & y() { return Elements[1]; }
	inline T & z() { return Elements[2]; }
	inline T & w() { return Elements[3]; }

	inline T x() const { return Elements[0]; }
	inline T y() const { return Elements[1]; }
	inline T z() const { return Elements[2]; }
	inline T w() const { return Elements[3]; }


	inline const Quat operator * (T rhs) const{
		return Quat(Elements[0]*rhs, Elements[1]*rhs, Elements[2]*rhs, Elements[3]*rhs);
	}

	inline Quat& operator *= (T rhs){
		Elements[0]*=rhs;
		Elements[1]*=rhs;
		Elements[2]*=rhs;
		Elements[3]*=rhs;
		return *this;        
	}

	inline const Quat operator*(const Quat& rhs) const{
		return Quat( rhs.Elements[3]*Elements[0] + rhs.Elements[0]*Elements[3] + rhs.Elements[1]*Elements[2] - rhs.Elements[2]*Elements[1],
			rhs.Elements[3]*Elements[1] - rhs.Elements[0]*Elements[2] + rhs.Elements[1]*Elements[3] + rhs.Elements[2]*Elements[0],
			rhs.Elements[3]*Elements[2] + rhs.Elements[0]*Elements[1] - rhs.Elements[1]*Elements[0] + rhs.Elements[2]*Elements[3],
			rhs.Elements[3]*Elements[3] - rhs.Elements[0]*Elements[0] - rhs.Elements[1]*Elements[1] - rhs.Elements[2]*Elements[2] );
	}

	inline const Quat operator*(const CVector<T,3>& rhs) const{
		return *this * Quat(rhs.Elements[0],rhs.Elements[1],rhs.Elements[2],0);
	}

	inline Quat& operator*=(const Quat& rhs){
		T x = rhs.Elements[3]*Elements[0] + rhs.Elements[0]*Elements[3] + rhs.Elements[1]*Elements[2] - rhs.Elements[2]*Elements[1];
		T y = rhs.Elements[3]*Elements[1] - rhs.Elements[0]*Elements[2] + rhs.Elements[1]*Elements[3] + rhs.Elements[2]*Elements[0];
		T z = rhs.Elements[3]*Elements[2] + rhs.Elements[0]*Elements[1] - rhs.Elements[1]*Elements[0] + rhs.Elements[2]*Elements[3];
		Elements[3]   = rhs.Elements[3]*Elements[3] - rhs.Elements[0]*Elements[0] - rhs.Elements[1]*Elements[1] - rhs.Elements[2]*Elements[2];

		Elements[2] = z;
		Elements[1] = y;
		Elements[0] = x;
		return (*this);         
	}

	inline Quat operator / (T rhs) const{
		T div = 1.0/rhs;
		return Quat(Elements[0]*div, Elements[1]*div, Elements[2]*div, Elements[3]*div);
	}

	inline Quat& operator /= (T rhs){
		T div = 1.0/rhs;
		Elements[0]*=div;
		Elements[1]*=div;
		Elements[2]*=div;
		Elements[3]*=div;
		return *this;
	}

	inline const Quat operator/(const Quat& denom) const {
		return ( (*this) * denom.inverse() );
	}

	inline Quat& operator/=(const Quat& denom){
		(*this) = (*this) * denom.inverse();
		return (*this);           
	}

	inline const Quat operator + (const Quat& rhs) const{
		return Quat(Elements[0]+rhs.Elements[0], Elements[1]+rhs.Elements[1],
			Elements[2]+rhs.Elements[2], Elements[3]+rhs.Elements[3]);
	}

	inline Quat& operator += (const Quat& rhs) {
		Elements[0] += rhs.Elements[0];
		Elements[1] += rhs.Elements[1];
		Elements[2] += rhs.Elements[2];
		Elements[3] += rhs.Elements[3];
		return *this;           
	}
	inline const Quat operator - (const Quat& rhs) const {
		return Quat(Elements[0]-rhs.Elements[0], Elements[1]-rhs.Elements[1],
			Elements[2]-rhs.Elements[2], Elements[3]-rhs.Elements[3] );
	}

	inline Quat& operator -= (const Quat& rhs){
		Elements[0]-=rhs.Elements[0];
		Elements[1]-=rhs.Elements[1];
		Elements[2]-=rhs.Elements[2];
		Elements[3]-=rhs.Elements[3];
		return *this;           
	}

	inline const Quat operator - () const{
		return Quat (-Elements[0], -Elements[1], -Elements[2], -Elements[3]);
	}

	T Dot(const Quat& rhs) const{
		return rhs.Elements[3]*Elements[3] + rhs.Elements[2]*Elements[2] + rhs.Elements[1]*Elements[1] + rhs.Elements[0]*Elements[0];
	}

	T length() const{
		return sqrt( Elements[0]*Elements[0] + Elements[1]*Elements[1] + Elements[2]*Elements[2] + Elements[3]*Elements[3]);
	}

	T length2() const{
		return Elements[0]*Elements[0] + Elements[1]*Elements[1] + Elements[2]*Elements[2] + Elements[3]*Elements[3];
	}

	inline Quat conj () const { 
		return Quat( -Elements[0], -Elements[1], -Elements[2], Elements[3] );
	}

	inline const Quat inverse () const{
		return conj() / length2();
	}

	void makeRotate (T  angle,  T  x, T  y, T  z ){
		angle /= 2.;
		T sin1 = sin(angle);
		T cos1 = cos(angle);
		T len = sqrt(x*x + y*y + z*z);
		Elements[0] = x * sin1 / len;
		Elements[1] = y * sin1 / len;
		Elements[2] = z * sin1 / len;
		Elements[3] = cos1;
	}
	void makeRotate ( T  angle, const CVector<T,3>& vec ){
		makeRotate(angle,vec.Elements[0],vec.Elements[1],vec.Elements[2]);
	}
	void makeRotate( const CVector<T,3>& vec1, const CVector<T,3>& vec2 ){
		vec1.Normalize();
		vec2.Normalize();
		T x = vec1.Elements[1]* vec2.Elements[2] - vec1.Elements[2]*vec2.Elements[1];
		T y = vec1.Elements[2]* vec2.Elements[0] - vec1.Elements[0]*vec2.Elements[2];
		T z = vec1.Elements[0]* vec2.Elements[1] - vec1.Elements[1]*vec2.Elements[0];
		makeRotate(acos(vec1.Dot(vec2)),x,y,z);
	}

	void getRotate ( T & angle, T & x, T & y, T & z ) const{
		angle = acos(Elements[3]);
		T sin1 = sin(angle);
		x = Elements[0] / sin1;
		y = Elements[1] / sin1;
		z = Elements[2] / sin1;
		angle *= 2;
	}
	void getRotate ( T & angle, CVector<T,3>& vec ) const{
		getRotate(angle,vec.Elements[0],vec.Elements[1],vec.Elements[2]);
	}

	void slerp(T  t, const Quat& from, const Quat& to){
		T angle = acos(from.Dot(to));
		*this = (from * sin((1-t)*angle) + to * sin(t*angle)) / sin(angle)
	}
	CVector<T,3> rotate (const CVector<T,3>& vec ) const{
		Quat quat = *this * vec * this->inverse();
		CVector<T,3> result;
		result.Elements[0] = quat.Elements[0];
		result.Elements[1] = quat.Elements[1];
		result.Elements[2] = quat.Elements[2];

		return result;
	}
};    

typedef Quat<float> Quatf;
typedef Quat<double> Quatd;

#endif