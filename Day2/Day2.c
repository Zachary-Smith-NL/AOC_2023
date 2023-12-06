#include <stdio.h>
#include <string.h>
#define RED 12
#define GREEN 13
#define BLUE 14

/*
Using this to make code more readable
*/
int checkGame(int r,int g,int b) {
    if (RED - r < 0) return 0;
    if (GREEN - g < 0) return 0;
    if (BLUE - b < 0) return 0;
    return 1;
}

/*
Removing code dupe
*/
int stringToInt(char *string) {
    int value = 0;
    for (int i = 0; i < strlen(string); i++ ) {
        value = value * 10 + string[i] - '0';
    }
    return value;
}

int processGame(char *line, int part) {
    // Copy the line so I can call this once for each part per line
    char lineCopy[strlen(line)];
    strcpy(lineCopy, line);
    // Use pointers for strtok_r memory. There was likely a less awful way to do this but w/e
    char *gameSepPtr, *roundSepPtr;
    // First get the game title (Game Game#)
    char *gameTitleTmp = strtok_r(lineCopy, ":", &gameSepPtr);
    // Then get the main body of the game
    char *game = strtok_r(NULL, ":", &gameSepPtr);
    // Then split the game into rounds
    char *round = strtok_r(game, ";", &roundSepPtr);
    int leastR = 0;
    int leastG = 0;
    int leastB = 0;
    while(round) {
        char *pullSepPtr;
        //Split each round into the pulls
        int r = 0;
        int g = 0;
        int b = 0;
        char *pull = strtok_r(round, ",", &pullSepPtr);
        while(pull) {
            // Pulls are "pull# color", so split with space
            char* textSepPtr;
            char *numPulledTmp = strtok_r(pull, " ", &textSepPtr);
            int numPulled = stringToInt(numPulledTmp);
            char *colorPulledTmp = strtok_r(NULL, " ", &textSepPtr);
            char colorPulled[strlen(colorPulledTmp)];
            strcpy(colorPulled, colorPulledTmp);
            switch(colorPulled[0]) {
                case 'r':
                    r = numPulled;
                    if (numPulled > leastR) {
                        leastR = numPulled;
                    }
                    break;
                case 'g':
                    g = numPulled;
                    if (numPulled > leastG) {
                        leastG = numPulled;
                    }
                    break;
                case 'b':
                    b = numPulled;
                    if (numPulled > leastB) {
                        leastB = numPulled;
                    }
                    break;
            }
            pull = strtok_r(NULL, ",", &pullSepPtr);
        }
        // If game is invalid its number isn't counted in part 1
        if (!checkGame(r,g,b) && part == 1) return 0;
        round = strtok_r(NULL, ";", &roundSepPtr);
    }
    if (part == 1) {
        // Get the game's number
        // First ditch the part of the string that's just "game"
        strtok(gameTitleTmp, " ");
        char *gameNumberTmp = strtok(NULL, " ");
        int gameNumber = stringToInt(gameNumberTmp);
        return gameNumber;
    }
    else {
        return leastR * leastG * leastB;
    }

}

int main() {
    FILE *file = fopen("input.txt", "r");
    int result1 = 0, result2 = 0;
    char line[180];
    while (fgets(line, 180, file) != NULL) {
        result1 += processGame(line, 1);
        result2 += processGame(line, 2);
    }
    fclose(file);
    printf("\nPart 1 Result: %i", result1);
    printf("\nPart 2 Result: %llu", result2);
}