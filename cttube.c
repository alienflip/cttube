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
    logic_table logic_table;    // define struct to hold compilation of output boolean expression
    logic_table.height=0;
    char *file_name = NULL;
    if (argc > 1) file_name = argv[1];
    else return printf("No argument provided!\n");
    FILE* file = fopen(file_name, "r");
    if (file == NULL) return fprintf(stderr, "File cannot be opened: %s\n", file_name);
    else {
        printf("PARSING...\n");
        char line[MAX_ARRAY_WIDTH];
        int counter = 0;
        while (fgets(line, sizeof(line), file)) {
            parser(&logic_table, line, strlen(line), counter);  // parse input file into the logic table
            counter++;
        }
        fclose(file);
    } 
    printf("COMPILING...\n");
    transformer(&logic_table);  // Process the logic table into a boolean expression.
    FILE *fp = fopen("output_expression", "ab");
    if (fp != NULL) {
        fputs(logic_table.output_expression, fp);
        fclose(fp);
    }
    printf("---\nCOMPILED EXPRESSION:\n---\n%s \n", logic_table.output_expression);
    return 0;
}
