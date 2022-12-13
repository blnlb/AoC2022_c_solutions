#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool compareInput(char *left, char *right);

int main(int argc, char **argv)
{
    FILE *fp = fopen("input.txt", "r");
    char *left = malloc(275);
    char *right = malloc(275);
    char *dummy = malloc(2);
    int i = 1;
    int sum = 0;
    while (fgets(left, 275, fp))
    {
        fgets(right, 275, fp);
        fgets(dummy, 2, fp);
        if (compareInput(left, right))
            sum += i;
        ++i;
    }

    printf("%d\n", sum);

    return 0;
}

bool compareInput(char *left, char *right)
{
    bool isSmaller = false;
    int cmp;
    while (strncmp(left, "\0", 1) && strncmp(left, "\n", 1))
    {
        if (!strncmp(right, "\0", 1) || !strncmp(right, "\n", 1))
        {
            return false;
        }
        if (!strncmp(left, "[", 1))
        {
            if (!strncmp(right, "[", 1))
            {
                left += 1;
                right += 1;
            }
            else if (isdigit(right[0]))
            {
                left += 1;
            }
            else if (!strncmp(right, "]", 1)) {
                return false;
            }
            else if (!strncmp(right, ",", 1)) {
                right += 1;
            }
        }
        else if (isdigit(left[0]))
        {
            if (isdigit(right[0]))
            {
                cmp = left[0] - right[0];
                if (cmp > 0)
                    return false;
                else if (cmp < 0)
                    return true;
                else {
                    left += 1;
                    right += 1;
                }
            }
            else if (!strncmp(right, "[", 1))
            {
                right += 1;
            }
            else if (!strncmp(right, "]", 1)) {
                return false;
            }
            else if (right[0] == ',') {
                right +=1;
            }
        }
        else if (!strncmp(left, ",", 1))
        {
            if (!strncmp(right, "]", 1))
            {
                return false;
            }
            else if (!strncmp(right, ",", 1)) {
                right += 1;
                left += 1;
            } else if (!strncmp(right, "[", 1)) {
                left +=1;
            }
            else if (isdigit(right[0])) {
                left += 1;
            }
        }
        else if (!strncmp(left, "]", 1)) {
            if (isdigit(right[0])) {
                return true;
            }
            else if (!strncmp(right, "]", 1)) {
                left += 1;
                right += 1;
            } else if (!strncmp(right, ",", 1)) {
                left += 1;
            }
            else if (!strncmp(right, "[", 1)) {
                return true;
            }
        }
    }
    return true;
}

bool compareInput2(char* left, char* right, int len) {
    char *leftCopy = malloc(strlen(left) + 1);
    memcpy(leftCopy, left, strlen(left));
    leftCopy[strlen(left)] = '\0';
    char *rightCopy = malloc(strlen(right) + 1);
    memcpy(rightCopy, right, strlen(left));
    rightCopy[strlen(right)] = '\0';
    if (len == -1) {
        int numElementsLeft = 0;
        int numElementsRight = 0;
        
    }
}