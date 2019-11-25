#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MATH_PI 3.1415926535
#define MATH_E  2.7182818284
#define MATH_SQRT_TWO 1.4142135623
#define MATH_SQRT_THREE 1.7320508075
#define NUMBER_OF_CUBES 100

struct Side{
	_Bool taken;
	unsigned color;
	struct Side* adjacentSide;
};

struct Cube{
	struct Side* sides;
};

int puzzleOneColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_PI)%100);
}

int puzzleTwoColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_E)%100);
}

int puzzleThreeColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_SQRT_TWO)%100);
}

int puzzleFourColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_SQRT_THREE)%100);
}

void generateCube(char puzzle[],int (*calculateFunction)(int)){
	struct Cube* cubes = (struct Cube*)malloc(sizeof(struct Cube) * NUMBER_OF_CUBES);
	unsigned sideIndex = 1;
	struct Cube* cubeIterator = cubes;
	struct Cube* end = cubes + sizeof(struct Cube) * NUMBER_OF_CUBES;

	for(end; cubeIterator != end; cubeIterator += sizeof(struct Cube)){
		cubeIterator->sides = (struct Side*)malloc(sizeof(struct Side)*3);
		cubeIterator->sides[0].color = (*calculateFunction)(sideIndex++);
		cubeIterator->sides[1].color = (*calculateFunction)(sideIndex++);
		cubeIterator->sides[2].color = (*calculateFunction)(sideIndex++);
	}

	FILE* outputFile = fopen("cubes.txt", "a");
	fprintf(outputFile, "%s:\n", puzzle);
	cubeIterator = cubes;
	int counter = 1;
	for(end; cubeIterator != end; cubeIterator += sizeof(struct Cube)){
		//printf("%i ", cubeIterator->sides[0].color);
		//printf("\t%i ", cubeIterator->sides[1].color);
		//printf("\t%i\n", cubeIterator->sides[2].color);
		fprintf(outputFile, "Cube %d: ", counter++);
		fprintf(outputFile, "\t%i\t%i\t%i\n", cubeIterator->sides[0].color, cubeIterator->sides[1].color, cubeIterator->sides[2].color);
	}
	fprintf(outputFile, "\n");
	fclose(outputFile);

	free(cubes);
}	

int main(){
	generateCube("Puzzle 1", puzzleOneColorCalculation);
	generateCube("Puzzle 2", puzzleTwoColorCalculation);
	generateCube("Puzzle 3", puzzleThreeColorCalculation);
	generateCube("Puzzle 4", puzzleFourColorCalculation);
	return 0;
}
