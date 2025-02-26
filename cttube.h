#include "stdio.h"
#include <string.h>

#define MAX_ARRAY_WIDTH     128
#define MAX_ARRAY_HEIGHT    1024

typedef struct {
    int input_width;
    int output_width;
    int height;
    char header[MAX_ARRAY_WIDTH];
    char body[MAX_ARRAY_HEIGHT][MAX_ARRAY_WIDTH];
} logic_table;

void parser(logic_table* logic_table, char* line, int len, int counter);
void transformer(logic_table* logic_table);