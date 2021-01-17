#ifndef FUNCTIONS_H__
#define FUNCTIONS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define DEBUG_MODE 0

int **findAPlaceToLandTheBricks(int rows, int cols);
char **getAreaForPicture(int rows, int cols);
int readTheArchitecturalPlans(int **wall, int *brickSequence, int rows, int cols);
void addBrickToTheWall(int **wall, int row, int col, int brick, int direction, int flag);
void buildTheBrickWall(int **wall, int *brickSequence, int rows, int cols);
void showThisBrickBeauty(int **wall, int rows, int cols);
void showWhatIsInBrickStore(int *wall, int size);

void breakTheWall(int **wall, int rows);
void smashThePicture(char **wall, int rows);
void seeMessageFromBuilder(char *message);

void concatText(int **wall, int rows, int cols, char **textArray, int textArrRows, int textArrCols);

#endif  // FUNCTIONS_H__