#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"


/* 
    Read from the input and check validity of data. 
    if data is valid continue with other tasks.
        Add all data from input into two arrays, two dimensional for future wall and one dimensional for 
        bricks numbers from current wall(data).
    else
        Stop and return -1 
*/
int readTheArchitecturalPlans(int **wall, int *brickSequence, int rows, int cols){

    seeMessageFromBuilder("enter readTheArchitecturalPlans");

    int i, j, num;
    int result = 0;
    int temp = 0;

    printf("%s\n", "Enter briks numbers and hit Enter");

    for (i = rows; i < (rows*2); i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &num);
            brickSequence[num] = brickSequence[num] + 1;
            wall[i][j] = num;
        }
    }

    /* If any value of index is not even return 1 and exit program */
    int maxNum = ((rows * cols) / 2);
    for (i = 1; i <= maxNum; i++) {
        if(brickSequence[i] % 2 != 0) {
            result = 1;
            break;
        }
    }

    seeMessageFromBuilder("exit readTheArchitecturalPlans");

    return result;
}

/* Logic for brick orientation depending rows and cols count and directions of brick*/
void addBrickToTheWall(int **wall, int row, int col, int brick, int direction, int flag) {

    wall[row][col] = brick;

    if (direction){
        wall[row+1][col] = brick;
    } else {
        wall[row][col+1] = brick;
    }

#if DEBUG_MODE
    char msg1 [100];
    char msg2 [100];
    sprintf(msg1, "Flag %d dir %s wall[%d][%d]=%d", flag, direction == 1 ? "S" : "D", row, col, brick);
    if (direction){
        sprintf(msg2, "Flag %d dir %s wall[%d][%d]=%d", flag, direction == 1 ? "S" : "D", row+1, col, brick);
    } else {
        sprintf(msg2, "Flag %d dir %s wall[%d][%d]=%d", flag, direction == 1 ? "S" : "D", row, col+1, brick);
    }
    seeMessageFromBuilder(msg1);
    seeMessageFromBuilder(msg2);
#endif 
}

/*
    Method for real brick work.
    Depending on how many rows are left changes the order of placing the bricks through the variable "directions".
*/
void buildTheBrickWall(int **wall, int *brickSequence, int rows, int cols) {

    seeMessageFromBuilder("enter buildTheBrickWall");

#if DEBUG_MODE
    showThisBrickBeauty(wall, rows, cols);
#endif

    int row, col, *brickStore;
    brickStore = (int *)malloc((rows * cols) * sizeof(int));

    int i, j;
    for(i = 1, j = 1; i < (rows * cols); i+=2, j++) {
        if(brickSequence[j] > 0){
            brickStore[i-1] = j;
            brickStore[i] = j;
        }
    }

#if DEBUG_MODE
    for(i = 0; i < (rows * cols); i++) {
        printf("%d ", brickStore[i]);
    }

    printf("\n");
#endif

/*  
    For the better stability of the wall we must alternate verticals and horizonticals rows 
    This "directions" show what is the last directions of bricks.
    But first:
    Calculate the direction of the first brick, depending on the last brick on the current wall.
    if last brick is down -> first must be up.
*/

    int directions = 0;

    if(wall[rows][0] == wall[rows][1]){
        directions = 1;
    } 


    int number = 0;

    for(row = 0; row < rows; row+=2){
        for(col = 0; col < cols; col++){
            /* If left one row or col only add only one brick */
            if((rows - 1) == row){
                addBrickToTheWall(wall, row, col, brickStore[number], 0, 1);
            } else if ((cols - 1) == col){
                addBrickToTheWall(wall, row, col, brickStore[number], 1, 2);
            } else {
                /* If left even rows first add upright bricks */
                if(0 == (rows - row) % 2) {
                    if (1 == directions) {
                        addBrickToTheWall(wall, row, col, brickStore[number], directions, 3);
                    } else {
                        addBrickToTheWall(wall, row, col, brickStore[number], directions, 4);
                        number += 2;
                        addBrickToTheWall(wall, row+1, col, brickStore[number], directions, 5);
                        col++;
                    }
                } else {
                    if (1 == directions) {
                        addBrickToTheWall(wall, row, col, brickStore[number], directions, 6);
                        number += 2;
                        addBrickToTheWall(wall, row+1, col, brickStore[number], directions, 7);
                        col++;
                    } else {
                        addBrickToTheWall(wall, row, col, brickStore[number], directions, 8);
                    }
                }
            }

            number += 2;
            directions = !directions;
        }
    }
    

    free(brickStore);
    seeMessageFromBuilder("exit buildTheBrickWall");
}


/* 
    Method for formated output acording tasks
    IS NOT IMPLEMENTED YET
*/
void concatText(int **wall, int rows, int cols, char **textArray, int textArrRows, int textArrCols) {

    seeMessageFromBuilder("enter concatText");

    int i, j;
    int number = 0;
    char snum[2];
    char *temp;
    // char str[24] = {'#'};
    char *str = (char *)malloc((textArrCols + 2)*sizeof(char));
    for(i = 0; i <= textArrCols; i++){
        str[i] = '#';
        number++;
    }

    str[i] = '\0';

    // printf("rows %d cols %d\n", rows, cols);
    textArray[0] = str;

    for(i = 0; i < rows; i++){
        textArray[i][0] = '#';
        for(j = 0; j < cols; j++){
            snprintf(snum, 2, "%d", wall[i][j]);
            strcat(textArray[i], snum);
            // textArray[i][j] = itoa(wall[i][j], snum, 2);
            // printf("%d %s\n",wall[i][j], snum);
        }
        textArray[i][j+1] = '#';
        textArray[i][j+2] = '\0';
    }

    textArray[i] = str;
    free(str);

    seeMessageFromBuilder("exit concatText");

}


/* Print final result */
void showThisBrickBeauty(int **wall, int rows, int cols) {

    seeMessageFromBuilder("enter showThisBrickBeauty");

    printf("%s\n", "There is the result of the work done:");
    
    char msg [100];
    sprintf(msg, "rows %d cols %d\n", rows, cols);
    seeMessageFromBuilder(msg);

    int i, j;
    int isSecond = 0;
    int toPrint;

    for (i = 0; i < (rows * 2); ++i) {
        for (j = 0; j < cols; ++j) {
            printf("%.2d ", wall[i][j]);
        }
        printf("\n");
    }

    seeMessageFromBuilder("exit showThisBrickBeauty");
}


/* For DEBUG_MODE only */
void showWhatIsInBrickStore(int *store, int size) {

    seeMessageFromBuilder("enter showWhatIsInBrickStore");

    int i;

#if DEBUG_MODE
    for (i = 1; i <= size/2; ++i) {
        printf("index %d->%d\n", i, store[i]);
    }
#endif
    seeMessageFromBuilder("exit showWhatIsInBrickStore");
}



int **findAPlaceToLandTheBricks(int rows, int cols) {

    seeMessageFromBuilder("enter findAPlaceToLandTheBricks");
    
    int **wall;
    int i, j, temp;

    wall = (int **)malloc( (rows * 2 ) * sizeof(int *));
    for (i = 0; i < (rows * 2); ++i) {
        wall[i] = (int *)malloc(cols * sizeof(wall[0]));
    }

    seeMessageFromBuilder("exit findAPlaceToLandTheBricks");

    return wall;
}

char **getAreaForPicture(int rows, int cols) {

    seeMessageFromBuilder("enter getAreaForPicture");
    
    char **picture;
    int i, j, temp;

    picture = (char **)malloc(rows * sizeof(char *));
    for (i = 0; i < rows; ++i) {
        picture[i] = (char *)malloc(cols * sizeof(picture[0]));
    }

    seeMessageFromBuilder("exit getAreaForPicture");

    return picture;
}

/* Clean when do the job */
void breakTheWall(int **wall, int rows) {

    seeMessageFromBuilder("enter freePtrArray");

    if(wall != NULL) {  
        int i;
        for(i = 0; i < (rows * 2); i++)
            free(wall[i]);

        free(wall);
    }

    seeMessageFromBuilder("exit freePtrArray");
}

void smashThePicture(char **picture, int rows) {

    seeMessageFromBuilder("enter freePicture");

    if(picture != NULL) {  
        int i;
        for(i = 0; i < (rows); i++)
            free(picture[i]);

        free(picture);
    }

    seeMessageFromBuilder("exit freePicture");
}


/* Print message when DEBUG_MODE  is ON (1) */
void seeMessageFromBuilder(char *message){

#if DEBUG_MODE
    printf("%s\n", message);
#endif

}




