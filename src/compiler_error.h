#ifndef COMPILER_ERROR_HEADER
#define COMPILER_ERROR_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


enum lexer_error {
    LEX_SUCCESS = 0,
    LEX_ERR_MEM,
    LEX_ERR_SYMBOL,
    LEX_ERR_UNKNOWN_DIRECTIVE,
    LEX_ERR_UNKNOWN_MACRO,
    LEX_ERR_UNTERMINATED_STRING,
    LEX_ERR_UNKNOWN_RADIX,
    LEX_ERR_INVALID_NUMBER
};


const char *lexer_error_string(enum lexer_error result);

enum parser_error {
    PARSE_SUCCESS = 0
};


const char *parser_error_string(enum parser_error result);

#endif