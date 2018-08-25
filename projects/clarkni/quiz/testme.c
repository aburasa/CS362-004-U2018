/* 
 * Random Testing quiz
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//random characters as input

char inputChar()
{
	  int min = 32; //ASCII value for Space
	  int max = 126; //ASCII value
    char c = (char) (rand() % (max - min + 1))+ min;
    
    return c;
}

//random string input

char *inputString()
{
	
    char str[5];
    
    int min = 97; //ASCII for 'a'
    int max = 122; //ASCII for 'z'
    for(int i = 0; i < 5; i++){
       
       char c = (char)(rand() % (max - min + 1) + min);
       str[i] = c;
    }
    str[5] = '\0';
    char *stringFini = str;
    
    return stringFini;
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
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
