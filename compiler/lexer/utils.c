#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// move data from file onto own region in mem
char *read_file(char *file_path) {
  FILE *fptr = fopen(file_path, "r");

  if (fptr == NULL) {
    printf("\e[31m ERROR \e[0m: file could not be found \n");
    return NULL;
  }

  fseek(fptr, 0, SEEK_END);
  int size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  char *text_in_file = malloc(size + 1); //+1 for the end of string
  size = fread(text_in_file, 1, size, fptr);

  return text_in_file;
}

void throw_error(char error_type) {
  if (error_type == 'T') {
    printf("E\e[31m ERROR \e[0m: Test error \n");
    exit(1);
  }
}
