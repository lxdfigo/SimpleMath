#include <stdio.h>
#include "SimpleMath.h"

int main(){
	Vec4f vec(1);
	Quatf quat(vec);
	Mat4x4d mat;

	printf("%f\n",mat[2][1]);

	vec += Vec4f();
	vec /= 2.;
	vec *= 3.;
	

	vec = vec - Vec4f(-1);

	vec -= Vec4f(2);
	printf("%f %f",vec.Elements[0],vec.Elements[3]);

	getchar();
	return 0;
}