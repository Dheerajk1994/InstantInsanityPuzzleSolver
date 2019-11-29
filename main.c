#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MATH_PI 3.1415926535
#define MATH_E  2.7182818284
#define MATH_SQRT_TWO 1.4142135623
#define MATH_SQRT_THREE 1.7320508075
#define NUMBER_OF_CUBES 3

typedef struct Side Side;

struct Side{
	bool taken;
	unsigned color;
	Side* adjacentSide;
};

typedef struct{
	Side* sides;
}Cube;

int puzzleOneColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_PI)% NUMBER_OF_CUBES);
}

int puzzleTwoColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_E)% NUMBER_OF_CUBES);
}

int puzzleThreeColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_SQRT_TWO)% NUMBER_OF_CUBES);
}

int puzzleFourColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_SQRT_THREE)% NUMBER_OF_CUBES);
}

void printPuzzleSetToFile(const Cube** cubes, char* puzzleName, char* fileName, char* readWriteState){
	FILE* outPutFile = fopen(fileName, readWriteState);
	fprintf(outPutFile, "%s:\n", puzzleName);
	const Cube* cubeIterator = *cubes;
	const Cube* end = *cubes + sizeof(Cube) * NUMBER_OF_CUBES;
	int counter = 1;

	for(end; cubeIterator != end; cubeIterator += sizeof(Cube)){
		fprintf(outPutFile, "Cube %d: ", counter++);
		fprintf(outPutFile, "\t%i\t%i\t%i\n", cubeIterator->sides[0].color, cubeIterator->sides[1].color, cubeIterator->sides[2].color);
	}
	fprintf(outPutFile, "\n");
	fclose(outPutFile);
}

Cube* generateCube(int size, int (*calculateFunction)(int)){
	Cube* cubes = (Cube*)malloc((sizeof(Cube) + sizeof(Side)* 3)* size);
	unsigned sideIndex = 1;
	Cube* cubeIterator = &cubes[0];
	Cube* end = cubes + (sizeof(Cube) * NUMBER_OF_CUBES);

	for(end; cubeIterator != end; cubeIterator += sizeof(Cube)){
		//PROBABLY NOT NECESSARY
		//cubeIterator->sides[0].adjacentSide = &(cubeIterator->sides[1]);
		//cubeIterator->sides[1].adjacentSide = &(cubeIterator->sides[2]);
		//cubeIterator->sides[2].adjacentSide = &(cubeIterator->sides[0]);
		///

		cubeIterator->sides[0].color = (*calculateFunction)(sideIndex++);
		cubeIterator->sides[1].color = (*calculateFunction)(sideIndex++);
		cubeIterator->sides[2].color = (*calculateFunction)(sideIndex++);
		//printf("\t%d\t%d\t%d\n", cubeIterator->sides[0].color, cubeIterator->sides[1].color, cubeIterator->sides[2].color);
	}
	return cubes;
}	

bool tryToSolvePuzzle(Cube** cubes, Cube* currentCube, Cube* end, int* colorArray){
		if(currentCube == end){
			printf("reached base case\n");
			return true;
		}
		else{
			printf("recursive try to solve called\n");
			//printf("%d\n", colorArray[currentCube->sides[0].color]);
			tryToSolvePuzzle(cubes, currentCube + sizeof(Cube), end, colorArray);
			//if(!currentCube->sides[0].taken && colorArray[currentCube->sides[0].color - 1] + 1 == 1){
			//	printf("inside first check");
			//	currentCube->sides[0].taken = true;
			//	colorArray[currentCube->sides[0].color - 1] = 1;
			//	if(tryToSolvePuzzle(cubes, currentCube + sizeof(Cube), end, colorArray)){
			//		return true;
			//	}
			//	currentCube->sides[0].taken = false;
			//	colorArray[currentCube->sides[0].color - 1] = 0;
			//}
			//if(!currentCube->sides[1].taken&& colorArray[currentCube->sides[1].color + 1] + 1 == 1){
			//	currentCube->sides[1].taken = true;
			//	colorArray[currentCube->sides[1].color + 1] = 1;
			//	if(tryToSolvePuzzle(cubes, currentCube, end, colorArray)){
			//		return true;
			//	}
			//	currentCube->sides[1].taken = false;
			//	colorArray[currentCube->sides[1].color + 1] = 0;
			//}
			//if(!currentCube->sides[2].taken && colorArray[currentCube->sides[2].color + 1] + 1 == 1){
			//	currentCube->sides[2].taken = true;
			//	colorArray[currentCube->sides[2].color + 1] = 1;
			//	if(tryToSolvePuzzle(cubes, currentCube, end, colorArray)){
			//		return true;
			//	}
			//	currentCube->sides[2].taken = false;
			//	colorArray[currentCube->sides[2].color + 1] = 0;
			//}
			//return false;
		}
} 

int* createColorArray(int size){
	int* array = (int*)calloc(size, sizeof(int));
	return array;
}
void freeUpMemory(Cube** cubes){
	Cube* end = *cubes + sizeof(Cube) * NUMBER_OF_CUBES;
	Cube* cubeIterator = *cubes;

	for(end; cubeIterator != end; cubeIterator += sizeof(Cube)){
		free(cubeIterator->sides);
	}
	free(*cubes);
}

void freeUpColorArray(int** colorArray){
	free(*colorArray);
}

int main(){
	Cube* puzzleSet1 = NULL;
	Cube* puzzleSet2 = NULL;
	Cube* puzzleSet3 = NULL;
	Cube* puzzleSet4 = NULL;
 	
	int* colorArray = createColorArray(NUMBER_OF_CUBES);

 	puzzleSet1 = generateCube(NUMBER_OF_CUBES, puzzleOneColorCalculation);	
	//generateCube(&puzzleSet2, "Puzzle 2", puzzleTwoColorCalculation);
	//generateCube(&puzzleSet3, "Puzzle 3", puzzleThreeColorCalculation);
	//generateCube(&puzzleSet4, "Puzzle 4", puzzleFourColorCalculation);



	printPuzzleSetToFile((Cube const**) &puzzleSet1, "Puzzle 1", "cubes.txt", "w");
	Cube* currentCube = NULL;
	currentCube = puzzleSet1;
	tryToSolvePuzzle(&puzzleSet1, currentCube, puzzleSet1 + sizeof(Cube) * NUMBER_OF_CUBES, colorArray);

	//freeUpMemory(&puzzleSet1);
	//freeUpMemory(&puzzleSet2);
	//freeUpMemory(&puzzleSet3);
	//freeUpMemory(&puzzleSet4);
	return 0;
}

