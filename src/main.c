#include <stdlib.h>
#include <stdio.h>


#include "resources.h"
#include "lexer.h"
#include "compiler_error.h"
#include "vector.h"
#include <time.h>
#include <unistd.h>





enum vector_iterator_result free_token_iterator(struct vector *v, int i, void *element) {
	printf("freed token %d\n", i);
	char *lexeme = ((struct lexer_token*)element)->lexeme;
	free(lexeme);
	return VECTOR_ITER_SUCCESS;
}

int main(int argc, char **argv) {
	clock_t c1 = clock();
	
	int line = 1;

	struct vector buffer;
	vector_init(&buffer, sizeof(struct lexer_token));

	int c;
	
	const char *error_string;
	
	FILE *f = fopen("../resources/test.txt", "r");
	error_string = lexer_error_string(lexer_tokenise(f, &buffer, &line));
	fclose(f);

	

	
	
	for (int i = 0; i < buffer.count; i++) {
		struct lexer_token t;
		vector_get(&buffer, i, &t);
		printf("Line: %d, Type: %d, Lexeme: %s\n", t.line, t.type, t.lexeme);
	}
	printf("\n\n*** LINE %d: %s ***\n\n", line, error_string);

	clock_t t1 = clock();

	printf("TIME: %lu, LOC: %lu",(t1 - c1) / CLOCKS_PER_SEC, line);


	vector_iterate(&buffer, &free_token_iterator);
	vector_deinit(&buffer);

	sleep(10);
	

	return 0;
}
