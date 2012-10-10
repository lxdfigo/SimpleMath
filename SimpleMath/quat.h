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

        inline Quat( const Vec4f& v ) {
            Elements[0]=v.Elements[0];
            Elements[1]=v.Elements[1];
            Elements[2]=v.Elements[2];
            Elements[3]=v.Elements[3];
        }

		inline Quat( const Vec4d& v ){
			Elements[0]=v.Elements[0];
			Elements[1]=v.Elements[1];
			Elements[2]=v.Elements[2];
			Elements[3]=v.Elements[3];
        }

        inline Quat( T angle, const Vec3f& axis){
            makeRotate(angle,axis);
        }
        inline Quat( T angle, const Vec3d& axis){
            makeRotate(angle,axis);
        }

        inline Quat( T angle1, const Vec3f& axis1, 
                     T angle2, const Vec3f& axis2,
                     T angle3, const Vec3f& axis3){
            makeRotate(angle1,axis1,angle2,axis2,angle3,axis3);
        }

        inline Quat( T angle1, const Vec3d& axis1, 
                     T angle2, const Vec3d& axis2,
                     T angle3, const Vec3d& axis3) {
            makeRotate(angle1,axis1,angle2,axis2,angle3,axis3);
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

        inline Vec4d asVec4() const{
            return Vec4d(Elements[0], Elements[1], Elements[2], Elements[3]);
        }

        inline Vec3d asVec3() const{
            return Vec3d(Elements[0], Elements[1], Elements[2]);
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

        void makeRotate ( T  angle,  T  x, T  y, T  z );
        void makeRotate ( T  angle, const Vec3f& vec );
        void makeRotate ( T  angle, const Vec3d& vec );
        void makeRotate ( T  angle1, const Vec3f& axis1, 
                         T  angle2, const Vec3f& axis2,
                         T  angle3, const Vec3f& axis3);
        void makeRotate ( T  angle1, const Vec3d& axis1, 
                         T  angle2, const Vec3d& axis2,
                         T  angle3, const Vec3d& axis3);
        void makeRotate( const Vec3f& vec1, const Vec3f& vec2 );
        void makeRotate( const Vec3d& vec1, const Vec3d& vec2 );
        void makeRotate_original( const Vec3d& vec1, const Vec3d& vec2 );

        void getRotate ( T & angle, T & x, T & y, T & z ) const;
        void getRotate ( T & angle, Vec3f& vec ) const;
        void getRotate ( T & angle, Vec3d& vec ) const;

        void slerp   ( T  t, const Quat& from, const Quat& to);
               
        Vec3f operator* (const Vec3f& v) const  {
            Vec3f uv, uuv; 
            Vec3f qvec(Elements[0], Elements[1], Elements[2]);
            uv = qvec ^ v;
            uuv = qvec ^ uv; 
            uv *= ( 2.0f * Elements[3] ); 
            uuv *= 2.0f; 
            return v + uv + uuv;
        }
               
        Vec3d operator* (const Vec3d& v) const{
            Vec3d uv, uuv; 
            Vec3d qvec(Elements[0], Elements[1], Elements[2]);
            uv = qvec ^ v;
            uuv = qvec ^ uv; 
            uv *= ( 2.0f * Elements[3] ); 
            uuv *= 2.0f; 
            return v + uv + uuv;
        }
};    

typedef Quat<float> Quatf;
typedef Quat<double> Quatd;

#endif