#include <stdio.h>
#include <stdbool.h>

bool validateString() {
    char ch;
    bool seenA = false, seenFirstB = false, seenSecondB = false;

    while ((ch = getchar()) != '\n') {
        if (ch == 'a') 
        {
            if (seenFirstB || seenSecondB) 
            {
                return false; 
            }
            seenA = true;
        } 
        else if (ch == 'b') 
        {
            if (!seenFirstB) 
            {
                seenFirstB = true; 
            } 
            else if (!seenSecondB) 
            {
                seenSecondB = true; 
            } 
            else 
            {
                return false; 
            }
        } 
        else 
        {
            return false; 
        }
    }

    
    return seenFirstB && seenSecondB;
}

int main() {
    printf("Enter a string: ");
    
    if (validateString()) 
    {
        printf("Valid String\n");
    } 
    else 
    {
        printf("Invalid String\n");
    }

    return 0;
}
