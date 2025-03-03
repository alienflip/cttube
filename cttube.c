/*
 *
 *  Copyright(C) 2025 Kai Harris <matchahack@gmail.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any purpose with or
 *  without fee is hereby granted, provided that the above copyright notice and
 *  this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO
 *  THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *  DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 *  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 *  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "cttube.h"

int main(int argc, char *argv[]){
    logic_table logic_table;    // Define struct to hold compilation data and output
    logic_table.height=0;
    char *file_name = NULL;
    if (argc > 1) file_name = argv[1];
    else return printf("No argument provided!\n");
    FILE* file = fopen(file_name, "r");
    if (file == NULL) return fprintf(stderr, "File cannot be opened: %s\n", file_name);
    else {
        printf("START:%s\n***\nPARSING...\n", file_name);
        char line[MAX_ARRAY_WIDTH];
        int counter = 0;
        while (fgets(line, sizeof(line), file)) {
            parser(&logic_table, line, strlen(line), counter);  // Parse input file into the logic table
            counter++;
        }
        fclose(file);
    } 
    printf("COMPILING...\n");
    transformer(&logic_table);  // Process the logic table into a boolean expression.
    FILE *fp = fopen("tests/output_expressions", "ab");
    if (fp != NULL) {
        fputs(file_name, fp);
        fputs(":", fp);
        fputs(logic_table.output_expression, fp);
        fputs("\n", fp);
        fclose(fp);
    }
    printf("COMPILED EXPRESSION:\n%s\n***\nEND\n\n", logic_table.output_expression);
    return 0;
}
