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

// Function to transform a the logic table structure into a boolean expression
void transformer(logic_table* logic_table){
    char final_expression[MAX_ARRAY_WIDTH*MAX_ARRAY_HEIGHT] = {'('};
    for(int l = 0; l < logic_table->height; l++){   // Loop through each row of the logic table (l = row index)
        char top_expression[MAX_ARRAY_WIDTH] = {'('};
        for(int c = logic_table->input_width-1; c >= 0; c--){   // Loop through each column of the logic table's row, reading the values backwards (Note: This is because the table was parsed backwards to ensure expressions evaluate correctly to logical 1)
            char input_value = logic_table->header[c];  // Get the header (input value) for the current column
            char expression[8] = {};
            if(logic_table->body[l][c] == '0' && c > 0) snprintf(expression, sizeof(expression), "(%c%c)&", '~', input_value);  // Case when the value at [l][c] is '0' and c > 0, format the atomic expression to negate the input (Note: there is an '&' symbol because it is not yet the end of the line)
            if(logic_table->body[l][c] == '0' && c == 0) snprintf(expression, sizeof(expression), "(%c%c)", '~', input_value);
            if(logic_table->body[l][c] == '1' && c > 0) snprintf(expression, sizeof(expression), "(%c)&", input_value);
            if(logic_table->body[l][c] == '1' && c == 0) snprintf(expression, sizeof(expression), "(%c)", input_value); // Case when the value at [l][c] is '1' and c == 0, format the atomic expression for the input without negation (Note: there is no '&' symbol because it is the end of the line)
            strcat(top_expression, expression); // Concatenate the expression to the current expression
        }
        strcat(top_expression, ")");
        if(l < logic_table->height - 1){    // If not the last row, concatenate the current expression with a '|' (OR operator) for joining different rows
            strcat(final_expression, top_expression);
            strcat(final_expression, "|");
        }
        if(l == logic_table->height - 1) strcat(final_expression, top_expression);  // If it's the last row, just concatenate the current expression (without the OR operator)
        printf("CURRENT EXPRESSION:: %s \n", top_expression);
    }
    strcat(final_expression, ")");
    printf("\n---\nCOMPILED EXPRESSION:\n---\n%s \n", final_expression);
}