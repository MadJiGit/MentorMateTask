#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// #include "functions.h"
#include "functions.c"

/*
    The program start with message to enter cols and rows size for current wall.
    After that enter all numbers of bricks and hit "Enter".
*/

int main(int argc, char **argv){

    int returnState = 0;
    int **wall;
    int *brickSequence;
    int rows, cols;

    printf("%s\n", "Enter rows and cols size: ");
    scanf("%d", &rows);
    scanf("%d", &cols);

    int sizeArr = (rows * cols);

    /* Allocate 1 index more because counting from 1 */
    brickSequence = (int *)malloc(((sizeArr/2)+1) * sizeof(int));
    wall = findAPlaceToLandTheBricks(rows, cols);

    int result = readTheArchitecturalPlans(wall, brickSequence, rows, cols);

    /* If result is -1 End of programme */
    if (result) {
        printf("%s\n", "The input is not valid. Programme is over.");

        returnState = -1;
        goto exitProgramme;
    }

    buildTheBrickWall(wall, brickSequence, rows, cols);

    showThisBrickBeauty(wall, rows, cols);

    // TODO
    /* **textArray will contains formated output */
    char **picture;
    int pictureRows = ((rows*4)+1);
    int pictureCols = (cols*3);
    picture = getAreaForPicture(pictureRows, pictureCols);

    /* goto FLAG */
    exitProgramme:
    
    breakTheWall(wall, rows);
    smashThePicture(picture, pictureRows);

    printf("%s\n", "Bye,\nI hope to see you soon :)\n\nMladen Raykov\n\nraykovmladen@gmail.com");

    return returnState;
}

