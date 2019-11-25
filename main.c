#include <stdlib.h>
#include <stdio.h>
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
	struct Cube* cubeIterator = cubes;

	for(cubeIndex = 0; cubeIndex < 100; ++cubeIndex){
		cubeIterator->sides = (struct Side*)malloc(sizeof(struct Side)*3);
		cubeIterator->sides[0].color = (1 + ((int)floor(sideIndex++ * MATH_PI)%100));
		cubeIterator->sides[1].color = (1 + ((int)floor(sideIndex++ * MATH_PI)%100));
		cubeIterator->sides[2].color = (1 + ((int)floor(sideIndex++ * MATH_PI)%100));
		cubeIterator += sizeof(struct Cube);
	}

	struct Cube* end = &(cubes + (sizeof(struct Cube) * 99));
	cubeIterator = cubes;
	printf("%i", cubeIterator->sides[2].color);
	while(cubeIterator != end){
		printf("%i", cubeIterator->sides[0].color);
		cubeIterator += sizeof(struct Cube);
	}
}

int main(){
	generateCube();
	return 0;
}
