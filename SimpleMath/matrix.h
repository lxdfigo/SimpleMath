#ifndef __MATRIX_H
#define __MATRIX_H
#include "vector.h"

template<class T, int DIMENSION>
class CMatrix
{
private:
	CVector<T,DIMENSION> Rows[DIMENSION];

public:
	CMatrix(){}


	inline CVector<T,DIMENSION> & operator [] (int i) { return Rows[i]; }
	inline CVector<T,DIMENSION>   operator [] (int i) const { return Rows[i]; }

	CVector<T,DIMENSION> operator * (CVector<T,DIMENSION> &vec){
		CVector<T,DIMENSION> result;
		for(int i = 0; i < DIMENSION; ++i){
			result[i] = Rows[i].Dot(vec);
		}
		return result;
	}

	CMatrix operator * (const CMatrix &mat){
		CMatrix result;
		for(int i = 0; i < DIMENSION; ++i){
			for(int j = 0; j < DIMENSION; ++j){
				for(int k = 0; k < DIMENSION; ++k){
					result[i][j] += Rows[i][k] * mat[k][j]; 
				}
			}
		}
		return result;
	}
};

typedef CMatrix<float,2> Mat2x2f;
typedef CMatrix<float,3> Mat3x3f;
typedef CMatrix<float,4> Mat4x4f;
typedef CMatrix<double,3> Mat3x3d;
typedef CMatrix<double,4> Mat4x4d;


template<class T, int DIMENSION>
class CTransform{
private:
	CMatrix<T,DIMENSION> mat;
public:
	CTransform(){
		for(int i = 0; i < DIMENSION; ++i){
			mat[i][i]  = 1.0;
		}
	}

	CTransform& makeMoveTrans(CVector<T,DIMENSION-1>& vec){
		for(int i = 0; i < DIMENSION-1; ++i){
			mat[i][DIMENSION-1] += vec[i];
		}
		return *this;
	}

	CTransform& makeScaleTrans(CVector<T,DIMENSION-1>& vec){
		for(int i = 0; i < DIMENSION-1; ++i){
			mat[i][i] *= vec[i];
		}
		return *this;
	}

	CTransform& makeRotateTrans(Quat<T>& quat){
	
		return *this;
	}
	~CTransform(){}


	CVector<T,DIMENSION-1>& trans(CVector<T,DIMENSION-1>&  vec){
		CVector<T,DIMENSION> tv(1);
		for(int i = 0; i < DIMENSION - 1; ++i){
			tv[i] = vec[i];
		}
		tv = mat * tv;
		for(int i = 0; i < DIMENSION - 1; ++i){
			vec[i] = tv[i];
		}
		return vec;
	}
};
typedef CTransform<double,3> Trans3x3d;
typedef CTransform<float,3> Trans3x3f;
typedef CTransform<double,4> Trans4x4d;
typedef CTransform<float,4> Trans4x4f;

#endif