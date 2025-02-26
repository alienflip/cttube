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
    logic_table logic_table;    // define in-program struct for compilation
    logic_table.height=0;
    char *file_name = NULL; // read file into program
    if (argc > 1) file_name = argv[1];
    else return printf("No argument provided!\n");
    FILE* file = fopen(file_name, "r");
    if (file != NULL) {
        printf("---\nPARSING...\n---\n");
        char line[MAX_ARRAY_WIDTH];
        int counter = 0;
        while (fgets(line, sizeof(line), file)) {   // parse input file line by line
            parser(&logic_table, line, strlen(line), counter);
            counter++;
        }
        printf("META:: in:%d|out:%d|height:%d\n", 
            logic_table.input_width, logic_table.output_width, logic_table.height); // After parsing, print out some meta information about the logic table.
        printf("HEAD:: %s\n", logic_table.header);
        for(int i = 0; i < logic_table.height; i++) printf("BODY:: %s\n", logic_table.body[i]);
        fclose(file);
    } else {
        fprintf(stderr, "File cannot be opened: %s\n", file_name);
    }
    printf("\n---\nTRANSFORMING...\n---\n");
    transformer(&logic_table);  // Call the 'transformer' function to process the logic table into a boolean expression.
    return 0;
}
