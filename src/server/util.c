#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Returns the next line of the file in a string */
char *CSVLine(FILE *fp){
  char *line = (char*)malloc(sizeof(char)*2400);
  char character;
  int i = 0;
  char end = 1;
  while((character = fgetc(fp)) != EOF){
      end = 0;
     if (character == '\n')
        break;
     line[i++] = character;
  }
  if (!end)
    return line;
  return NULL;
}


/* Parses a string into tokens, using the delimiter ',', and returns
 * the token of the number "num" */
char *GetField(char *line,int num)
{

  char character;
  char *token = (char*)malloc(sizeof(char)*20);


  /*
   * Indeces: i = index of line, j = index of token list, k = index of individual token string
   */
        int i = 0, j = 1, k = 0;
  while ((character = line[i++]) != '\0')
        {


    /* If a delimiter is encountered, zero the token string index and erase the current token*/
     if (character == ','){
        if (j == num){
            break;
        }
        k = -1;
        free(token);
        token = (char*)malloc(sizeof(char)*20);
        j++;
     }
     else
        token[k] = character;
     k++;
        }
  return token;
}

