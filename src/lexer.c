#include "lexer.h"








enum lexer_error lexer_tokenise(FILE *src, struct vector *tokens, int *line) {

    enum lexer_error error = LEX_SUCCESS;
    enum vector_error vec_error = VECTOR_SUCCESS;

    int c; // Current processed character

    struct lexer_token token; // Buffer for the current token.
    token.lexeme = NULL;

    struct vector buffer; // Buffer for the current processed lexeme.
    vec_error = vector_init(&buffer, sizeof(char));
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        goto error_cleanup;
    }

    


    c = getc(src);
    while (c != EOF) {


        if (is_word_character(c)) {
            error = read_word_token(src, &c, &buffer, &token);

        } else if (c == '.') {
            error = read_directive_token(src, &c, &buffer, &token);

        } else if (c == '!') {
            error = read_macro_token(src, &c, &buffer, &token);

        } else if (c == '"') { 
            error = read_string_literal_token(src, &c, &buffer, &token);

        } else if (c == '#') {
            error = read_number_literal_token(src, &c, &buffer, &token);

        } else if (is_punctuation_character(c)) {
            error = read_punctuation_token(src, &c, &buffer, &token);

        } else if (is_whitespace_character(c)) {
            c = getc(src);

        } else if (c == '\n') {
            *line += 1;
            c = getc(src);

        } else if (c == ';') {
            error = read_comment(src, &c);

        } else {
            error = LEX_ERR_SYMBOL;

        }


        if (error != LEX_SUCCESS) {
            goto error_cleanup;
        }

        if (token.lexeme == NULL) {
            continue;
        }

        token.line = *line;
        vec_error = vector_push(tokens, &token);
        if (vec_error != VECTOR_SUCCESS) {
            error = LEX_ERR_MEM;
            goto error_cleanup;
        }

        token.lexeme = NULL;
    }

    

    // Cleanup
    free(token.lexeme);
    vector_deinit(&buffer);
    

    return LEX_SUCCESS;



    // Error cleanup
    error_cleanup:
        free(token.lexeme);
        vector_deinit(&buffer);
        
        return error;

}



bool is_whitespace_character(char c) {
    return (c == ' ')
            || (c == '\t');
}

bool is_punctuation_character(char c) {
    return (c == ':')
            || (c == '{')
            || (c == '}');
}

bool is_word_character(char c) {
    return (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z')
            || (c == '_')
            || (c >= '0' && c <= '9');
}

bool is_number_charater(char c) {
    return (c >= '0' && c <= '9')
            || (c >= 'a' && c <= 'f')
            || (c >= 'A' && c <= 'F');
}

bool is_radix_prefix_charater(char c) {
    return (c == 'b')
            || (c == 'o')
            || (c == 'd')
            || (c == 'x');
}

enum lexer_token_type get_word_type(const char *word) {
    for (int i  = 0; i < instruction_names_count; i++) {
        if (strcmp(instruction_names[i], word) == 0) {
            return LEXER_TOKEN_INSTRUCTION;
        }
    }


    for (int i  = 0; i < register_names_count; i++) {
        if (strcmp(register_names[i], word) == 0) {
            return LEXER_TOKEN_REGISTER;
        }
    }

    for (int i  = 0; i < port_names_count; i++) {
        if (strcmp(port_names[i], word) == 0) {
            return LEXER_TOKEN_PORT;
        }
    }

    for (int i  = 0; i < system_register_names_count; i++) {
        if (strcmp(system_register_names[i], word) == 0) {
            return LEXER_TOKEN_SYSTEM_REGISTER;
        }
    }

    for (int i  = 0; i < condition_code_names_count; i++) {
        if (strcmp(condition_code_names[i], word) == 0) {
            return LEXER_TOKEN_CONDITION_CODE;
        }
    }

    
    return LEXER_TOKEN_IDENTIFIER;
}


bool is_macro_name(const char *word) {
    for (int i  = 0; i < macro_names_count; i++) {
        if (strcmp(macro_names[i], word) == 0) {
            return true;
        }
    }
    
    return false;
}

bool is_directive_name(const char *word) {
    for (int i  = 0; i < directive_names_count; i++) {
        if (strcmp(directive_names[i], word) == 0) {
            return true;
        }
    }

    return false;
}





enum lexer_error read_word_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token) {
    enum lexer_error error = LEX_SUCCESS;
    enum vector_error vec_error = VECTOR_SUCCESS;

    while (*c != EOF && is_word_character(*c)) {
        vec_error = vector_push(buffer, (char*)c);
        if (vec_error != VECTOR_SUCCESS) {
            error = LEX_ERR_MEM;
            return error;
        }

        *c = getc(src);
    }
    
    
    vec_error = vector_push(buffer, "");
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;         
        return error;
    }

    token->type = get_word_type(buffer->ptr);

    token->lexeme = malloc(buffer->count * sizeof(char));
    if (token->lexeme == NULL) {
        error = LEX_ERR_MEM;
        return error;
    }
    vector_copy_unsafe(buffer, token->lexeme);

    vector_empty(buffer);

    
    return LEX_SUCCESS;
}

enum lexer_error read_directive_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token) {
    enum lexer_error error = LEX_SUCCESS;
    enum vector_error vec_error = VECTOR_SUCCESS;

    vec_error = vector_push(buffer, (char*)c);
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }

    *c = getc(src);
    while (*c != EOF && is_word_character(*c)) {
        vec_error = vector_push(buffer, (char*)c);
        if (vec_error != VECTOR_SUCCESS) {
            error = LEX_ERR_MEM;
            return error;
        }

        *c = getc(src);
    }

    vec_error = vector_push(buffer, "");
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;         
        return error;
    }

    if (!is_directive_name(buffer->ptr)) {
        error = LEX_ERR_UNKNOWN_DIRECTIVE;
        return error;
    }

    token->type = LEXER_TOKEN_DIRECTIVE;

    token->lexeme = malloc(buffer->count * sizeof(char));
    if (token->lexeme == NULL) {
        error = LEX_ERR_MEM;
        return error;
    }
    vector_copy_unsafe(buffer, token->lexeme);

    vector_empty(buffer);


    return LEX_SUCCESS;
}

enum lexer_error read_macro_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token) {
    enum lexer_error error = LEX_SUCCESS;
    enum vector_error vec_error = VECTOR_SUCCESS;

    vec_error = vector_push(buffer, (char*)c);
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }

    *c = getc(src);


    while (*c != EOF && is_word_character(*c)) {
        vec_error = vector_push(buffer, (char*)c);
        if (vec_error != VECTOR_SUCCESS) {
            error = LEX_ERR_MEM;
            return error;
        }

        *c = getc(src);
    }

    vec_error = vector_push(buffer, "");
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;         
        return error;
    }

    if (!is_macro_name(buffer->ptr)) {
        error = LEX_ERR_UNKNOWN_MACRO;
        return error;
    }

    token->type = LEXER_TOKEN_MACRO;

    token->lexeme = malloc(buffer->count * sizeof(char));
    if (token->lexeme == NULL) {
        error = LEX_ERR_MEM;
        return error;
    }
    vector_copy_unsafe(buffer, token->lexeme);

    vector_empty(buffer);



    return LEX_SUCCESS;
}

enum lexer_error read_string_literal_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token) {
    enum lexer_error error = LEX_SUCCESS;
    enum vector_error vec_error = VECTOR_SUCCESS;

    vec_error = vector_push(buffer, (char*)c);
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }

    *c = getc(src);


    while (*c != EOF && *c != '"') {
        vec_error = vector_push(buffer, (char*)c);
        if (vec_error != VECTOR_SUCCESS) {
            error = LEX_ERR_MEM;
            return error;
        }

        *c = getc(src);
    }

    if (*c == EOF) {
        error = LEX_ERR_UNTERMINATED_STRING;
        return error;
    }

    vec_error = vector_push(buffer, (char*)c);
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }

    *c = getc(src);

    vec_error = vector_push(buffer, "");
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }


    token->type = LEXER_TOKEN_STRING;

    token->lexeme = malloc(buffer->count * sizeof(char));

    vector_copy_unsafe(buffer, token->lexeme);

    vector_empty(buffer);


    return LEX_SUCCESS;
}

enum lexer_error read_number_literal_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token) {
    enum lexer_error error;
    enum vector_error vec_error;


    vec_error = vector_push(buffer, (char*)c);
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }

    *c = getc(src);


    if (is_radix_prefix_charater(*c)) {
        vec_error = vector_push(buffer, (char*)c);
        if (vec_error != VECTOR_SUCCESS) {
            error = LEX_ERR_MEM;
            return error;
        }

        *c = getc(src);
    }


    if (!is_number_charater(*c)) {
        error = LEX_ERR_INVALID_NUMBER;
        return error;
    }
    


    while (*c != EOF && is_number_charater(*c)) {
        vec_error = vector_push(buffer, (char*)c);
        if (vec_error != VECTOR_SUCCESS) {
            error = LEX_ERR_MEM;
            return error;
        }

        *c = getc(src);
    }

    vec_error = vector_push(buffer, "");
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }


    token->type = LEXER_TOKEN_NUMBER;

    token->lexeme = malloc(buffer->count * sizeof(char));

    vector_copy_unsafe(buffer, token->lexeme);

    vector_empty(buffer);



    return LEX_SUCCESS;
}

enum lexer_error read_punctuation_token(FILE *src, int *c, struct vector *buffer, struct lexer_token *token) {
    enum lexer_error error;
    enum vector_error vec_error;

    vec_error = vector_push(buffer, (char*)c);
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }

    *c = getc(src);


    vec_error = vector_push(buffer, "");
    if (vec_error != VECTOR_SUCCESS) {
        error = LEX_ERR_MEM;
        return error;
    }


    token->type = LEXER_TOKEN_NUMBER;

    token->lexeme = malloc(buffer->count * sizeof(char));

    vector_copy_unsafe(buffer, token->lexeme);

    vector_empty(buffer);
    

    return LEX_SUCCESS;
}

enum lexer_error read_comment(FILE *src, int *c) {
    
    while (*c != '\n' && *c != EOF) {
        *c = getc(src);
    }

    return LEX_SUCCESS;
}