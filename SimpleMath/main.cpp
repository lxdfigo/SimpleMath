#include <stdio.h>
#include "SimpleMath.h"

int main(){
	Mat4x4d mat;
	Quatf quat(1,1,0,1.57);
	Vec3f vec3;
	vec3.Elements[0] = 1;

	Quatf quat2 = quat * vec3 * quat.inverse();

	printf("%f %f %f",quat2.Elements[0],quat2.Elements[1],quat2.Elements[2]);

	getchar();
	return 0;
}