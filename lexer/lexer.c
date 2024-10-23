#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WHITESPACE ' '
#define MAX_TOKEN_LEN 10

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
  text_in_file[size + 1] = '\0';
  size = fread(text_in_file, 1, size, fptr);

  return text_in_file;
}

void throw_error(char error_type) {
  if (error_type == 'T') {
    printf("E\e[31m ERROR \e[0m: Test error \n");
    exit(1);
  }
}

typedef enum {
  TOKEN_IDENTIFIER,
  TOKEN_INT,
  TOKEN_LPAREN,     // (
  TOKEN_RPAREN,     // )
  TOKEN_LBRACE,     // {
  TOKEN_RBRACE,     // }
  TOKEN_SMCOLON,    // ;
  TOKEN_RTN,        // return
  TOKEN_INT_LITERAL //
} token_type;

typedef struct {
  token_type *array;
  int dA_len;
  int len_used;
} dArray;

void init_dArray(dArray *dAp, int initial_size) {
  printf("\t STARTING dArray INITIALIZATION \n");
  dAp->dA_len = initial_size;
  printf(" ->Set dAp.dA_len to %i \n", initial_size);
  dAp->array = malloc(initial_size * sizeof(token_type));
  printf(" ->MEMALLOCATED: location - %p size - %lu\n", dAp,
         initial_size * sizeof(token_type));
  dAp->len_used = 0;
}

void insert_dArray(dArray *dAp, token_type token) {
  printf("\t STARTING insert_dArray PROCEDURE \n");
  printf(" ->len_used: %i \n ->dA_len: %i \n", dAp->len_used, dAp->dA_len);
  if (dAp->len_used == dAp->dA_len) {
    dAp->dA_len++;
    dAp->array = realloc(dAp->array, dAp->len_used * sizeof(token_type));
  }
  printf(" ->Adding to array \n");
  dAp->array[dAp->len_used++] = token;
  printf(" ->Mem used after addition: %i \n", dAp->len_used);
  printf(" ->Array len after addition: %i \n", dAp->dA_len);
}

void free_dArray(dArray *dAp) {
  free(dAp->array);
  dAp->len_used = 0;
  dAp->dA_len = 0;
  dAp = NULL;
}

bool is_single_char_token(char c) { return true; }

int main(int argc, char **argv) {

  if (argc != 2) {
    printf(" \e[31m ERROR \e[0m: LEXER accepts only 1 argument -> FILENAME \n");
    return 1;
  }

  FILE *fptr = fopen(argv[1], "r");
  char *text_in_file = read_file(argv[1]);

  /*
   * Read next char
   * add char to buff[0]
   *
   * if is_single_char_token(char) -> tokenlist add singlechartoken(c)
   * while token_not_generated
   *  move to next char
   *  if is_keyword(buffer)
   *    tokenlist add keywordtoken(buffer)
   *    clearbuffer(*buffer)
   *    token_not_generated = false
   *  else
   *    move to next char
   *    add char to buffer
   * */
  int i = 0;
  char c;
  char *token_buffer[MAX_TOKEN_LEN];
  bool token_generated = false;
  dArray TOKENS;
  init_dArray(&TOKENS, 1);
  printf("\t STARTING MAIN TOKENIZER LOOP \n");
  while (c != '\0') {
    c = text_in_file[i];
    printf("Curr C: %c \n", c);
    if (c == '(' || c == 'n') {
      printf("Adding ( to TOKENS\n");
      insert_dArray(&TOKENS, TOKEN_LPAREN);
    }
    i++;
  }

  free(text_in_file);
  return 0;
}
