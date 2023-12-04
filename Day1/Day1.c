#include <stdio.h>
#include <string.h>
#include <math.h>

// Making these definitions global to not have to pass these things into the function
char nine[42];
char eight[42];
char seven[42];
char six[42];
char five[42];
char four[42];
char three[42];
char two[42];
char one[42];

int isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}

// We have maps at home. The maps:
char checkForDigit(char *spelledDigit) {
    if (strstr(spelledDigit, nine) != NULL) {
        return '9';
    }
    if (strstr(spelledDigit, eight) != NULL) {
        return '8';
    }
    if (strstr(spelledDigit, seven) != NULL) {
        return '7';
    }
    if (strstr(spelledDigit, six) != NULL) {
        return '6';
    }
    if (strstr(spelledDigit, five) != NULL) {
        return '5';
    }
    if (strstr(spelledDigit, four) != NULL) {
        return '4';
    }
    if (strstr(spelledDigit, three) != NULL) {
        return '3';
    }
    if (strstr(spelledDigit, two) != NULL) {
        return '2';
    }
    if (strstr(spelledDigit, one) != NULL) {
        return '1';
    }
    return '0';
    
}

int dayOne(int part) {
    FILE *file = fopen("input.txt", "r");
    int c, sum = 0, foundFirst = 0, numDigits = 0;
    char first, last;
    unsigned long long int spelledDigit = 0;
    if (file) {
        while((c = getc(file)) != EOF) {
            if (c == '\n') {
                printf("First: %c, Last: %c, added: %d\n", first, last, (first - '0') * 10 + (last - '0'));
                sum += (first - '0') * 10 + (last - '0');
                foundFirst = 0;
                spelledDigit = 0;
                numDigits = 0;
            }
            else if (isDigit(c)) {
                if (foundFirst == 0) {
                    foundFirst = 1;
                    first = c;
                }
                last = c;
                spelledDigit = 0;
                numDigits = 0;
            }
            else if(part == 2) {
                numDigits++;
                // Lowercase letters vary between 2 and 3 digit ascii codes, but capitals are always two digit
                // Convert the letters to their capital equivalents to make it easier to
                spelledDigit = spelledDigit * 100 + (c - 32);
                char digitString[256];
                sprintf(digitString, "%llu", spelledDigit);
                char digit = checkForDigit(digitString);
                if (digit > '0') {
                    printf("Digit: %c, String: %s\n", digit, digitString);
                    last = digit;
                    if (foundFirst == 0) {
                        first = digit;
                        foundFirst = 1;
                    }
                    spelledDigit = c - 32;
                    numDigits = 1;
                }
                // Prevents integer overflow, keeps 4 digits to make sure no number is missed
                if (numDigits >= 5) {
                    spelledDigit %= 10000000000;
                    numDigits = 4;
                }
            }
        }
    }
    fclose(file);
    return sum;
}

int main() {
    // Predefining the int versions of the numbers as strings
    // I think this is some of the most vile, heinous code I've written tbh
    sprintf(nine, "%d", 'N' * 1000000 + 'I' * 10000 + 'N' * 100 + 'E');
    sprintf(eight, "%llu", 'E' * (unsigned long long int)100000000 + 'I' * 1000000 + 'G' * 10000 + 'H' * 100 + 'T');
    sprintf(seven, "%llu", 'S' * (unsigned long long int)100000000 + 'E' * 1000000 + 'V' * 10000 + 'E' * 100 + 'N');
    sprintf(six, "%d", 'S' * 10000 + 'I' * 100 + 'X');
    sprintf(five, "%d", 'F' * 1000000 + 'I' * 10000 + 'V' * 100 + 'E');
    sprintf(four, "%d", 'F' * 1000000 + 'O' * 10000 + 'U' * 100 + 'R');
    sprintf(three, "%llu", 'T' * (unsigned long long int)100000000 + 'H' * 1000000 + 'R' * 10000 + 'E' * 100 + 'E');
    sprintf(two, "%d", 'T' * 10000 + 'W' * 100 + 'O');
    sprintf(one, "%d", 'O' * 10000 + 'N' * 100 + 'E');
    int part_one_res = dayOne(1);
    int part_two_res = dayOne(2);
    printf("Sum of codes (Part One): %d, Sum of codes (Part Two): %d", part_one_res, part_two_res);
}