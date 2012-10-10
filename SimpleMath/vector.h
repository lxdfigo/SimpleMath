
#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

template<class T, int DIMENSION>
class CVector
{
public:
	T Elements[DIMENSION];

	bool operator<(const CVector& Vector) const;
	bool operator>(const CVector& Vector) const;
	CVector& operator=(const CVector& Vector);
	CVector operator+(const CVector& Vector) const;
	inline CVector operator-(const CVector& Vector) const;
	CVector operator* (T ccalar) const;
	CVector operator/ (T ccalar) const;

	CVector& operator+=(const CVector& Vector);
	CVector& operator-=(const CVector& Vector);
	CVector& operator*=(T ccalar);
	CVector& operator/=(T ccalar);

	inline T & operator [] (int i) { return Elements[i]; }
	inline T   operator [] (int i) const { return Elements[i]; }

	CVector(T f = 0){
		for (int i = 0; i < DIMENSION; i++){
			this->Elements[i] = f;
		}
	}
	inline T Length() const;

	inline T Dot(const CVector& Vector) const;
	T Distance(const CVector& Vector) const;
	T SquaredDistance(const CVector& Vector) const;
	void Normalize();
	void UniformRandomHyperSpehere(T rng );

};

template<class T, int DIMENSION>
inline CVector<T,DIMENSION> operator*(T calar, const CVector<T,DIMENSION>& Vector){
	CVector<T,DIMENSION> Result;
	for (int i = 0; i < DIMENSION; i++){
		Result.Elements[i] = Vector.Elements[i] * calar;
	}
	return Result;
}

template<class T, int DIMENSION>
inline CVector<T,DIMENSION>& CVector<T,DIMENSION>::operator=(const CVector& Vector) {
	for (int i = 0; i < DIMENSION; i++){
		this->Elements[i] = Vector.Elements[i];
	}
	return *this;
}

template<class T, int DIMENSION>
inline bool CVector<T,DIMENSION>::operator < (const CVector<T,DIMENSION>& Vector) const {
	bool Result = true;
	for (int i = 0; i < DIMENSION; i++){
		if (this->Elements[i] >=  Vector.Elements[i]){
			Result = false;
			break;
		}
	}
	return Result;
}

template<class T, int DIMENSION>
inline bool CVector<T,DIMENSION>::operator > (const CVector<T,DIMENSION>& Vector) const {
	bool Result = true;
	for (int i = 0; i < DIMENSION; i++){
		if (this->Elements[i] <=  Vector.Elements[i]){
			Result = false;
			break;
		}
	}
	return Result;
}

template<class T, int DIMENSION>
CVector<T,DIMENSION>& CVector<T,DIMENSION>::operator+=(const CVector<T,DIMENSION>& Vector) {
	for (int i = 0; i < DIMENSION; i++){
		this->Elements[i] += Vector.Elements[i];
	}
	return *this;
}

template<class T, int DIMENSION>
CVector<T,DIMENSION>& CVector<T,DIMENSION>::operator-=(const CVector<T,DIMENSION>& Vector) {
	for (int i = 0; i < DIMENSION; i++){
		this->Elements[i] -= Vector.Elements[i];
	}
	return *this;
}

template<class T, int DIMENSION>
CVector<T,DIMENSION>& CVector<T,DIMENSION>::operator*=(T Scalar) {
	for (int i = 0; i < DIMENSION; i++){
		this->Elements[i] *= Scalar;
	}
	return *this;
}

template<class T, int DIMENSION>
CVector<T,DIMENSION>& CVector<T,DIMENSION>::operator/=(T Scalar) {
	for (int i = 0; i < DIMENSION; i++){
		this->Elements[i] /= Scalar;
	}
	return *this;
}

template<class T, int DIMENSION>
inline CVector<T,DIMENSION> CVector<T,DIMENSION>::operator-(const CVector<T,DIMENSION>& Vector) const {
	CVector<T,DIMENSION> Result;
	for (int i = 0; i < DIMENSION; i++){
		Result.Elements[i] = this->Elements[i] - Vector.Elements[i];
	}
	return Result;
}

template<class T, int DIMENSION>
CVector<T,DIMENSION> CVector<T,DIMENSION>::operator*(T Scalar) const{
	CVector<T,DIMENSION> Result;
	for (int i = 0; i < DIMENSION; i++){
		Result.Elements[i] = this->Elements[i] * Scalar;
	}
	return Result;
}

template<class T, int DIMENSION>
CVector<T,DIMENSION> CVector<T,DIMENSION>::operator/(T Scalar) const{
	CVector<T,DIMENSION> Result;
	for (int i = 0; i < DIMENSION; i++){
		Result.Elements[i] = this->Elements[i] / Scalar;
	}
	return Result;
}

template<class T, int DIMENSION>
CVector<T,DIMENSION> CVector<T,DIMENSION>::operator+(const CVector<T,DIMENSION>& Vector) const {
	CVector<T,DIMENSION> Result;
	for (int i = 0; i < DIMENSION; i++){
		Result.Elements[i] = this->Elements[i] + Vector.Elements[i];
	}
	return Result;
}

template<class T, int DIMENSION>
inline T  CVector<T,DIMENSION>::Length() const{
	T Length = 0.0f;
	for (int i = 0; i < DIMENSION; i++){
		Length += this->Elements[i] * this->Elements[i];
	}
	return sqrtf(Length);
}

template<class T, int DIMENSION>
T CVector<T,DIMENSION>::SquaredDistance(const CVector<T,DIMENSION>& Vector) const{
	CVector<T,DIMENSION> Difference = (*this) - Vector;
	return Difference.DotProduct(Difference);
}


template<class T, int DIMENSION>
T CVector<T,DIMENSION>::Distance(const CVector<T,DIMENSION>& Vector) const{
	return sqrtf(this->SquaredDistance(Vector));
}


template<class T, int DIMENSION>
void CVector<T,DIMENSION>::UniformRandomHyperSpehere(T rng){
	do{
		for (int i = 0; i < DIMENSION; i++){
			this->Elements[i] = 2.0f * rng - 1.0f;
		}
	}while (this->DotProduct((*this)) > 1.0f);
}


template<class T, int DIMENSION>
void CVector<T,DIMENSION>::Normalize(){
	T Length = sqrtf(this->DotProduct(*this));
	T Scale = 1.0f / (Length + 1E-20f);

	for (int i = 0; i < DIMENSION; i++){
		this->Elements[i] = this->Elements[i] * Scale;
	}
}

template<class T, int DIMENSION>
inline T CVector<T,DIMENSION>::Dot(const CVector<T,DIMENSION>& Vector) const{
	T Result = 0.0f;
	for (int i = 0; i < DIMENSION; i++){
		Result += this->Elements[i] * Vector.Elements[i];
	}
	return Result;
}


typedef CVector<float,2> Vec2f;
typedef CVector<float,3> Vec3f;
typedef CVector<double,3> Vec3d;
typedef CVector<float,4> Vec4f;
typedef CVector<double,4> Vec4d;

#endif
