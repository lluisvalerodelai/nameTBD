#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  int_type,
  return_type,
} keyword_type;

typedef enum {
  IDENTIFIER,
} identifier_type;

typedef enum {
  open_paren,
  close_paren,
  open_brace,
  close_brace,
  semicolon,
} separator_type;

typedef struct {
  keyword_type type;
  char *value;
} keyword_token;

typedef struct {
  separator_type type;
  char *value;
} separator_token;

char peek_next_char(FILE *file) {
  // Save the current position
  long current_pos = ftell(file);

  // Get the next character
  char next_char = fgetc(file);

  // Restore the original position
  fseek(file, current_pos, SEEK_SET);

  return next_char; // Return the character that was peeked
}

void lexer(FILE *fptr) {

  if (fptr == NULL) {
    printf("\e[31m ERROR \e[0m: file could not be found \n");
  }

  char c;

  while (c != EOF) {
    c = fgetc(fptr);
    if (iscntrl(c) || c == ' ') {
      printf("found space, breaking\n");
      continue;
    }
    if (c == '{') {
      printf("Found Token: { \n");
    } else if (c == '}') {
      printf("Found Token: } \n");
    } else if (c == '(') {
      printf("Found Token: ( \n");
    } else if (c == ')') {
      printf("Found Token: ) \n");
    } else if (c == ';') {
      printf("Found Token: ; \n");
    } else {
      int i = 1;
      char *buffer = malloc((sizeof(char) * i) + 1);
      while (isalpha(c) && c != EOF) {
        buffer[i - 1] = c;
        i++;
        buffer = realloc(buffer, i + 1);
        char next_c = peek_next_char(fptr);
        if (isalpha(next_c)) {
          c = fgetc(fptr);
        } else {
          break;
        }
      }

      if (strcmp(buffer, "main") == 0) {
        printf("Found buffer: main \n");
      } else if (strcmp(buffer, "return") == 0) {
        printf("Found buffer: return\n");
      } else if (strcmp(buffer, "int") == 0) {
        printf("Found buffer: int \n");
      } else {
        printf("Found identifier buffer: %s \n", buffer);
      }
    }
  }
}

int main(int argc, char **argv) {

  if (argc != 2) {
    printf(" \e[31m ERROR \e[0m: LEXER accepts only 1 argument -> FILENAME \n");
    return 1;
  }
  FILE *fptr = fopen(argv[1], "r");

  lexer(fptr);

  return 0;
}
