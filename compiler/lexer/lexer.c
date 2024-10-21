#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc != 2) {
    printf(" \e[31m ERROR \e[0m: LEXER accepts only 1 argument -> FILENAME \n");
    return 1;
  }

  FILE *fptr = fopen(argv[1], "r");
  char *text_in_file = read_file(argv[1]);

  free(text_in_file);
  return 0;
}
