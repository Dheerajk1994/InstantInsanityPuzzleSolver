#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MATH_PI 3.1415926535
#define MATH_E  2.7182818284
#define MATH_SQRT_TWO 1.4142135623
#define MATH_SQRT_THREE 1.7320508075
#define NUMBER_OF_CUBES 100

typedef struct Side Side;

struct Side{
	_Bool taken;
	unsigned color;
	Side* adjacentSide;
};

typedef struct{
	Side* sides;
}Cube;

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

void generateCube(Cube** cubes, char puzzle[],int (*calculateFunction)(int)){
	*cubes = (Cube*)malloc(sizeof(Cube) * NUMBER_OF_CUBES);
	unsigned sideIndex = 1;
	Cube* cubeIterator = *cubes;
	Cube* end = *cubes + sizeof(Cube) * NUMBER_OF_CUBES;

	for(end; cubeIterator != end; cubeIterator += sizeof(Cube)){
		cubeIterator->sides = (Side*)malloc(sizeof(Side)*3);

		cubeIterator->sides[0].adjacentSide = &(cubeIterator->sides[1]);
		cubeIterator->sides[1].adjacentSide = &(cubeIterator->sides[2]);
		cubeIterator->sides[2].adjacentSide = &(cubeIterator->sides[0]);

		cubeIterator->sides[0].color = (*calculateFunction)(sideIndex++);
		cubeIterator->sides[1].color = (*calculateFunction)(sideIndex++);
		cubeIterator->sides[2].color = (*calculateFunction)(sideIndex++);
	}

	//FILE* outputFile = fopen("cubes.txt", "w");
	//fprintf(outputFile, "%s:\n", puzzle);
	//cubeIterator = cubes;
	//int counter = 1;
	//for(end; cubeIterator != end; cubeIterator += sizeof(Cube)){
	//	//printf("%i ", cubeIterator->sides[0].color);
	//	//printf("\t%i ", cubeIterator->sides[1].color);
	//	//printf("\t%i\n", cubeIterator->sides[2].color);
	//	fprintf(outputFile, "Cube %d: ", counter++);
	//	fprintf(outputFile, "\t%i\t%i\t%i\n", cubeIterator->sides[0].color, cubeIterator->sides[1].color, cubeIterator->sides[2].color);
	//}
	//fprintf(outputFile, "\n");
	//fclose(outputFile);
}	

void freeUpMemory(Cube** cubes){
	Cube* end = *cubes + sizeof(Cube) * NUMBER_OF_CUBES;
	Cube* cubeIterator = *cubes;

	for(end; cubeIterator != end; cubeIterator += sizeof(Cube)){
		free(cubeIterator->sides);
	}
	free(*cubes);
}

int main(){
	Cube* puzzleSet1;
	Cube* puzzleSet2;
	Cube* puzzleSet3;
	Cube* puzzleSet4;

	generateCube(&puzzleSet1,"Puzzle 1", puzzleOneColorCalculation);
	generateCube(&puzzleSet2, "Puzzle 2", puzzleTwoColorCalculation);
	generateCube(&puzzleSet3, "Puzzle 3", puzzleThreeColorCalculation);
	generateCube(&puzzleSet4, "Puzzle 4", puzzleFourColorCalculation);

	freeUpMemory(&puzzleSet1);
	freeUpMemory(&puzzleSet2);
	freeUpMemory(&puzzleSet3);
	freeUpMemory(&puzzleSet4);
	return 0;
}

