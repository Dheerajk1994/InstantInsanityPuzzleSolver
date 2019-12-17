#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MATH_PI 3.1415926535
#define MATH_E  2.7182818284
#define MATH_SQRT_TWO 1.4142135623
#define MATH_SQRT_THREE 1.7320508075
#define NUMBER_OF_SIDES 3
#define NUMBER_OF_CUBES 100 
#define MAX_COLOR_RANGE 100

typedef struct Side Side;

struct Side{
	bool taken;
	unsigned color;
};

typedef struct{
	Side* sides;
}Cube;

int puzzleOneColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_PI)% MAX_COLOR_RANGE);
}

int puzzleTwoColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_E)% MAX_COLOR_RANGE);
}

int puzzleThreeColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_SQRT_TWO)% MAX_COLOR_RANGE);
}

int puzzleFourColorCalculation(int sideIndex){
	return 1 + ((int)floor(sideIndex * MATH_SQRT_THREE)% MAX_COLOR_RANGE);
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

void printCubeColors(const Cube* cube){
	for(int i = 0; i < NUMBER_OF_SIDES; ++i){
		printf("%d ", cube->sides[i].color);
	}
	printf("\n");
}

void generateCube(Cube** cubes, int size, int (*calculateFunction)(int)){
	*cubes = malloc(sizeof(Cube) * size);
	Cube* iterator = *cubes;
	Cube* end = iterator + size;
	unsigned sideIndex = 1;
	for(end; iterator != end; ++iterator){
		iterator->sides = malloc(sizeof(Side) * NUMBER_OF_SIDES);
		for(int i = 0; i < NUMBER_OF_SIDES; ++i){
			iterator->sides[i].color = (*calculateFunction)(sideIndex++);
			iterator->sides[i].taken = false;
		}
	}
}	

bool tryToSolvePuzzle(Cube* cubes, Cube* currentCube, Cube* end, int* colorArray){
	if(currentCube == end){
		for(int sideIndex = 0; sideIndex < NUMBER_OF_SIDES; ++sideIndex){
			if(!currentCube->sides[sideIndex].taken && colorArray[currentCube->sides[sideIndex].color - 1] == 0){
				currentCube->sides[sideIndex].taken = true;
				colorArray[currentCube->sides[sideIndex].color - 1] = 1;
				return true;
			}
		}
		return false;
	}
	else{
		for(int sideIndex = 0; sideIndex < NUMBER_OF_SIDES; ++sideIndex){
			if(!currentCube->sides[sideIndex].taken && colorArray[currentCube->sides[sideIndex].color - 1] == 0){
				currentCube->sides[sideIndex].taken = true;
				colorArray[currentCube->sides[sideIndex].color - 1] = 1;
				if(tryToSolvePuzzle(cubes, currentCube + 1, end, colorArray)){
					return true;
				}
				currentCube->sides[sideIndex].taken = false;
				colorArray[currentCube->sides[sideIndex].color - 1] = 0;
			}	
		}
		return false;
	}
	return false;
} 

int* createColorArray(int size){
	int* array = (int*)calloc(size, sizeof(int));
	return array;
}

void freeUpMemory(Cube** cubes, int cubeSetSize){
	Cube* cubeIterator = *cubes;
	Cube* end = cubeIterator + cubeSetSize; 
	
	for(end; cubeIterator != end; ++cubeIterator){
		free(cubeIterator->sides);
	}
	free(*cubes);
}

bool* getCubesThatHaveDecreasingColors(Cube* cubes, int cubeSetSize){
	bool* resultArray = (bool*)calloc(cubeSetSize, sizeof(bool));
	for(int i = 0; i < cubeSetSize; ++i){
		int side1 = (cubes+i)->sides[0].color;	
		int side2 = (cubes+i)->sides[1].color;	
		int side3 = (cubes+i)->sides[2].color;	

		if(side1 < side2 && side2 < side3){
			resultArray[i] = true;
		}
	}
}

bool* getCubesWithRepeatingColors(Cube* cubes, int cubeSetSize){
	bool* resultArray = (bool*)calloc(cubeSetSize, sizeof(bool));
	//TODO this only assumes that you have 3 sides
	//will need adjustments if more than 3 sides are introduced
	int side1Col = 0, side2Col = 0, side3Col = 0;
	for(int i = 0; i < cubeSetSize; ++i){
		side1Col = (cubes + i)->sides[0].color;		
		side2Col = (cubes + i)->sides[1].color;		
		side3Col = (cubes + i)->sides[2].color;		
		if(side1Col == side2Col || side2Col == side3Col || side1Col == side3Col){
			resultArray[i] = true;
		}
	}
	return resultArray;
}

bool* getCubesWithThisColor(Cube* cubes, int cubeSetSize, int color){
	bool* resultArray = (bool*)calloc(cubeSetSize, sizeof(bool));
	int counter = 0;
	for(counter; counter < cubeSetSize; ++counter){
		for(int i = 0; i < NUMBER_OF_SIDES; ++i){
			if((cubes + counter)->sides[i].color == color){
				*(resultArray + counter) = true;
			}	
		}
	}
	return resultArray;
}

int* countColorOccurence(Cube* cubes){
	//array of MAX_COLOR_RANGE ints representing MAX_COLOR_RANGE possible colors
	int* colorOccurenceArray = (int*)calloc(MAX_COLOR_RANGE, sizeof(int));
	Cube* iterator = cubes;
	Cube* end = iterator + NUMBER_OF_CUBES;

	for(end; iterator != end; ++iterator){
		for(int i = 0; i < NUMBER_OF_SIDES; ++i){
			*(colorOccurenceArray + (iterator->sides[i].color - 1)) += 1;	
		}
	}
	for(int i = 0; i < MAX_COLOR_RANGE; ++i){
		//printf("Color  %d : \t%d times\n", i + 1, *(colorOccurenceArray + i));	
	}
	return colorOccurenceArray;
}

Cube* getCopyOfCube(Cube* cube){
	Cube* copy;
	for(int i = 0; i < NUMBER_OF_SIDES; ++i){
		copy->sides[i].color = cube->sides[i].color;	
	}
	return copy;
}


void findPotentialMinObst(Cube* cubes, int cubeSetSize){
	int* colorOccurenceArray = countColorOccurence(cubes);
	bool* potentialConflictCubes = NULL;
	bool* potentialColorRepeatsCubes = NULL;

	//POTENTIAL COLOR REPEATS IN SAME CUBE
	printf("Cubes with repeating colors:\n");
	potentialColorRepeatsCubes = getCubesWithRepeatingColors(cubes, cubeSetSize);
	for(int i = 0; i < cubeSetSize; ++i){
		if(potentialColorRepeatsCubes[i] == true){
			printf("Colors repeat on cube: %d\n", i + 1);
		}
	}
	
	//COLORS THAT APPEAR MORE THAN THREE TIMES
	for(int i = 0; i < MAX_COLOR_RANGE; ++i){
		if(colorOccurenceArray[i] > 3){
			potentialConflictCubes = getCubesWithThisColor(cubes, cubeSetSize, i + 1); 

			printf("A min obstacle - with color %d appearing more than  3 times\n", i + 1);
			for(int i = 0; i < cubeSetSize; ++i){
				if(potentialConflictCubes[i] == true){
					printf("cube: %d\tcolors:\t", i + 1);
					printCubeColors(cubes + i);
				}
			}
			//break;
		}
	}
}

int main(){
	Cube* puzzleSet1 = NULL;
	Cube* puzzleSet2 = NULL;
	Cube* puzzleSet3 = NULL;
	Cube* puzzleSet4 = NULL;
 	
	int* colorArray = createColorArray(NUMBER_OF_CUBES);

 	generateCube(&puzzleSet1, NUMBER_OF_CUBES, puzzleOneColorCalculation);	
 	generateCube(&puzzleSet2, NUMBER_OF_CUBES, puzzleTwoColorCalculation);	
 	generateCube(&puzzleSet3, NUMBER_OF_CUBES, puzzleThreeColorCalculation);	
 	generateCube(&puzzleSet4, NUMBER_OF_CUBES, puzzleFourColorCalculation);	

	printPuzzleSetToFile((Cube const*) puzzleSet1, "Puzzle 1", "cubes.txt", "a");
	printPuzzleSetToFile((Cube const*) puzzleSet2, "Puzzle 2", "cubes.txt", "a");
	printPuzzleSetToFile((Cube const*) puzzleSet3, "Puzzle 3", "cubes.txt", "a");
	printPuzzleSetToFile((Cube const*) puzzleSet4, "Puzzle 4", "cubes.txt", "a");


	//printf("Puzzle 1 solvable: %d\n", tryToSolvePuzzle(puzzleSet1, puzzleSet1, puzzleSet1 + NUMBER_OF_CUBES - 1, colorArray));
	printf("\n\n\nPuzzle 1\n");
	findPotentialMinObst(puzzleSet1, NUMBER_OF_CUBES);
	printf("\n\n\nPUzzle 2\n");
	findPotentialMinObst(puzzleSet2, NUMBER_OF_CUBES);
	printf("\n\n\nPUzzle 3\n");
	findPotentialMinObst(puzzleSet3, NUMBER_OF_CUBES);
	printf("\n\n\nPUzzle 4\n");
	findPotentialMinObst(puzzleSet4, NUMBER_OF_CUBES);

	freeUpMemory(&puzzleSet1, NUMBER_OF_CUBES);
	freeUpMemory(&puzzleSet2, NUMBER_OF_CUBES);
	freeUpMemory(&puzzleSet3, NUMBER_OF_CUBES);
	freeUpMemory(&puzzleSet4, NUMBER_OF_CUBES);
	
	return 0;
}

