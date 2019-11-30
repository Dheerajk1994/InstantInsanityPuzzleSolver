#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MATH_PI 3.1415926535
#define MATH_E  2.7182818284
#define MATH_SQRT_TWO 1.4142135623
#define MATH_SQRT_THREE 1.7320508075
#define NUMBER_OF_CUBES 100 

typedef struct Side Side;

struct Side{
	bool taken;
	unsigned color;
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

void printPuzzleSetToFile(const Cube* cubes, char* puzzleName, char* fileName, char* readWriteState){
	FILE* outPutFile = fopen(fileName, readWriteState);
	fprintf(outPutFile, "%s:\n", puzzleName);
	int counter = 1;
	const Cube* cubeIterator = cubes;
	const Cube* endCube = cubeIterator + NUMBER_OF_CUBES;	 

	for(endCube; cubeIterator != endCube; cubeIterator++){
		fprintf(outPutFile, "Cube %d: ", counter++);
		fprintf(outPutFile, "\t%i\t%i\t%i\n", cubeIterator->sides[0].color, cubeIterator->sides[1].color, cubeIterator->sides[2].color);
	}
	
	fprintf(outPutFile, "\n");
	fclose(outPutFile);
}

void generateCube(Cube** cubes, int size, int (*calculateFunction)(int)){
	*cubes = malloc(sizeof(Cube) * size);
	Cube* iterator = *cubes;
	Cube* end = iterator + size;
	unsigned sideIndex = 1;
	for(end; iterator != end; ++iterator){
		iterator->sides = malloc(sizeof(Side) * 3);

		iterator->sides[0].color = (*calculateFunction)(sideIndex++);
		iterator->sides[1].color = (*calculateFunction)(sideIndex++);
		iterator->sides[2].color = (*calculateFunction)(sideIndex++);
	}
}	

bool tryToSolvePuzzle(Cube* cubes, Cube* currentCube, Cube* end, int* colorArray){
	if(currentCube == end){
		printf("%x %x\n", currentCube, end);
		printf("reached base case\n");
		return true;
	}
	else{
		for(int sideIndex = 0; sideIndex < 3; ++sideIndex){
			if(!currentCube->sides[sideIndex].taken && colorArray[currentCube->sides[0].color - 1] == 0){
				currentCube->sides[sideIndex].taken = true;
				colorArray[currentCube->sides[sideIndex].color - 1] = 1;
				if(tryToSolvePuzzle(cubes, currentCube += 1, end, colorArray)){
					return true;
				}
				currentCube->sides[sideIndex].taken = false;
				colorArray[currentCube->sides[sideIndex].color - 1] = 0;
			}	
		
		}
		return false;
	}
} 

int* createColorArray(int size){
	int* array = (int*)calloc(size, sizeof(int));
	return array;
}
void freeUpMemory(Cube** cubes){
	Cube* cubeIterator = *cubes;
	Cube* end = cubeIterator + NUMBER_OF_CUBES; 
	
	for(end; cubeIterator != end; ++cubeIterator){
		free(cubeIterator->sides);
	}
	free(*cubes);
}


int main(){
	Cube* puzzleSet1 = NULL;
	//Cube* puzzleSet2 = NULL;
	//Cube* puzzleSet3 = NULL;
	//Cube* puzzleSet4 = NULL;
 	
	int* colorArray = createColorArray(NUMBER_OF_CUBES);
	
 	generateCube(&puzzleSet1, NUMBER_OF_CUBES, puzzleOneColorCalculation);	
	//generateCube(&puzzleSet2, "Puzzle 2", puzzleTwoColorCalculation);
	//generateCube(&puzzleSet3, "Puzzle 3", puzzleThreeColorCalculation);
	//generateCube(&puzzleSet4, "Puzzle 4", puzzleFourColorCalculation);

	printPuzzleSetToFile((Cube const*) puzzleSet1, "Puzzle 1", "cubes.txt", "w");
	printf("Puzzle 1 solvable: %d\n", tryToSolvePuzzle(puzzleSet1, puzzleSet1, puzzleSet1 + NUMBER_OF_CUBES, colorArray));

	freeUpMemory(&puzzleSet1);
	//freeUpMemory(&puzzleSet2);
	//freeUpMemory(&puzzleSet3);
	//freeUpMemory(&puzzleSet4);
	return 0;
}

