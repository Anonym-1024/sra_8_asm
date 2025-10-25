#ifndef LEXER_HEADER
#define LEXER_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "resources.h"
#include "compiler_error.h"
#include "vector.h"

enum lexer_token_type {
    LEXER_TOKEN_DIRECTIVE,
    LEXER_TOKEN_INSTRUCTION,
    LEXER_TOKEN_MACRO,
    LEXER_TOKEN_IDENTIFIER,
    LEXER_TOKEN_NUMBER,
    LEXER_TOKEN_STRING,
    LEXER_TOKEN_REGISTER,
    LEXER_TOKEN_SYSTEM_REGISTER,
    LEXER_TOKEN_PORT,
    LEXER_TOKEN_CONDITION_CODE,
    LEXER_TOKEN_PUNCTUATION
};


struct lexer_token {
    char *lexeme;
    enum lexer_token_type type;
    int line;
};





/**
 * @brief Create a token stream from the given file.
 * 
 * @param src Source file
 * @param tokens Array of tokens
 * @param line Current line being processed
 * @return enum lexer_error Returns LEX_SUCCESS if successful
 */
enum lexer_error lexer_tokenise(FILE *src, struct vector *tokens, int *line);


bool is_whitespace_character(char c);


bool is_punctuation_character(char c);


bool is_word_character(char c);


bool is_number_charater(char c);


bool is_radix_prefix_charater(char c);


enum lexer_token_type get_word_type(const char *word);


bool is_macro_name(const char *word);


bool is_directive_name(const char *word);


enum lexer_error read_word_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token);


enum lexer_error read_directive_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token);


enum lexer_error read_macro_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token);


enum lexer_error read_string_literal_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token);


enum lexer_error read_number_literal_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token);


enum lexer_error read_punctuation_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token);


enum lexer_error read_comment(FILE *src, int *c);



#endif