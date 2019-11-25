#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MATH_PI 3.1415926535


struct Side{
	_Bool taken;
	unsigned color;
	struct Side* adjacentSide;
};

struct Cube{
	struct Side* sides;
};

void generateCube(){
	struct Cube* cubes = (struct Cube*)malloc(sizeof(struct Cube) * 100);
	unsigned cubeIndex = 0;
	unsigned sideIndex = 1;
	for(cubeIndex = 0; cubeIndex < 100; ++cubeIndex){
		cubes->sides = (struct Side*)malloc(sizeof(struct Side)*3);
		cubes->sides[0].color = (1 + ((int)floor(sideIndex++ * MATH_PI)%100));
		cubes->sides[1].color = (1 + ((int)floor(sideIndex++ * MATH_PI)%100));
		cubes->sides[2].color = (1 + ((int)floor(sideIndex++ * MATH_PI)%100));
		cubes += sizeof(struct Cube);
	}

	struct Cube* end = &cubes[99];
	cubes = &cubes[0];

	while(cubes != end){
		printf("%i", cubes->sides[0].color);
		cubes += sizeof(struct Cube);
	}
}


int main(){
	generateCube();
	return 0;
}
