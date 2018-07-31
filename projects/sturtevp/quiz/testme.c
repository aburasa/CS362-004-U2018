#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int randChar = rand() % 256;
    
    while (randChar != 32 && randChar != 123
          && randChar != 40 && randChar != 41
          && randChar != 91 && randChar != 93
          && randChar != 97 && randChar != 120
          && randChar != 125 && randChar != 255
          && randChar != 0)
    {
       randChar = rand() % 256;
    }

    return (char)randChar;
}

char *inputString()
{
    int randChar = rand() % 128;
    int currChars = 0;
    int numChars = 6;

    char* randStr = malloc(numChars * sizeof(char));

    while (currChars < numChars)
    {
       if (randChar == 114 || randChar == 101
           || randChar == 115 || randChar == 116
           || randChar == 0)
       {
          randStr[currChars] = randChar;
          currChars++;
       }
       randChar = rand() % 128;
    }

    return randStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      // free allocated memory
      free(s);

      printf("error ");
      exit(200);
    }

    // free allocated memory
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
