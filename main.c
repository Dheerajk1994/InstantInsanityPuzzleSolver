#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MATH_PI 3.1415926535

typedef struct Side Side;

struct Side{
	_Bool taken;
	unsigned color;
	Side* adjacentSide;
};

typedef struct{
	struct Side* sides;
}Cube;

void generateCube(){
	struct Cube* cubes = (Cube*)malloc(sizeof(Cube) * 100);
	unsigned cubeIndex = 0;
	unsigned sideIndex = 1;
	for(cubeIndex = 0; cubeIndex < 100; ++cubeIndex){
		*cubes->sides = (Side*)malloc(sizeof(Side)*3);
		*cubes->sides[0].color = (1 + (floor(sideIndex++ * MATH_PI)%100));
		*cubes->sides[1].color = (1 + (floor(sideIndex++ * MATH_PI)%100));
		*cubes->sides[2].color = (1 + (floor(sideIndex++ * MATH_PI)%100));
	}

}


int main(){
	generateCube();
	return 0;
}
