#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Selects a random ASCII character
    return rand() % 128;
}

char *inputString()
{
    char* validChars = "erst"; // Only allow characters from the target statement
    const int VALID_SIZE = 4; // number of valid characters
    int string_size = rand() % 20 + 2; // Set the size of the string to a random number 2 - 21
    char* result = malloc(sizeof(char) * string_size); // allocate memory for the input string
    int i;
    int pick;
    for(i = 0; i < string_size; i++) {
      pick = rand() % VALID_SIZE; // pick a random character from the validChars string
      result[i] = validChars[pick]; // set it to the ith character in the results string
    }
    result[string_size] = '\0'; // make sure string is null terminated
    return result;
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
      printf("error ");
      exit(200);
    }
    free(s);
    s = NULL;
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
