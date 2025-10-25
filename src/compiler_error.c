#include "compiler_error.h"


const char *lexer_error_string(enum lexer_error result) {
    switch (result) {
        case LEX_SUCCESS:
        return "Lexer success.";

        case LEX_ERR_MEM:
        return "Lexer memory error.";

        case LEX_ERR_SYMBOL:
        return "Lexer error: invalid character found.";

        case LEX_ERR_UNKNOWN_DIRECTIVE:
        return "Lexer error: unknown directive found.";

        case LEX_ERR_UNKNOWN_MACRO:
        return "Lexer error: unknown macro found.";

        case LEX_ERR_UNTERMINATED_STRING:
        return "Lexer error: unterminated string literal found.";

        case LEX_ERR_UNKNOWN_RADIX:
        return "Lexer error: unknown radix prefix found.";

        case LEX_ERR_INVALID_NUMBER:
        return "Lexer error: invalid number literal found.";

        default:
        return "Unknown lexer error code.";
    }
}

const char *parser_error_string(enum parser_error result) {
    switch (result) {
        case PARSE_SUCCESS:
        return "Parser success.";

        default:
        return "Unknown parser error code.";
    }
}