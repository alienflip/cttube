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
    for(int l = 0; l < logic_table->height; l++){
        char top_expression[MAX_ARRAY_WIDTH] = {'('};
        for(int c = logic_table->input_width-1; c >= 0; c--){   // (Note: table was parsed backwards to ensure expressions evaluate to logical 1)
            char input_value = logic_table->header[c];  // Get the header (input value) for the current column
            char expression[8] = {};
            if(logic_table->body[l][c] == '0' && c > 0) snprintf(expression, sizeof(expression), "(%c%c)&", '~', input_value);  // Not the end of the line => '&' symbol )
            if(logic_table->body[l][c] == '0' && c == 0) snprintf(expression, sizeof(expression), "(%c%c)", '~', input_value);
            if(logic_table->body[l][c] == '1' && c > 0) snprintf(expression, sizeof(expression), "(%c)&", input_value); // Value == '1' => not '~' symbol )
            if(logic_table->body[l][c] == '1' && c == 0) snprintf(expression, sizeof(expression), "(%c)", input_value);
            strncat(top_expression, expression, sizeof(expression));
        }
        strncat(top_expression, ")", sizeof(")"));
        if(l < logic_table->height - 1){    // If not the last row, concatenate the current expression with a '|' (OR operator) for joining different rows
            strncat(logic_table->output_expression, top_expression, sizeof(top_expression));
            strncat(logic_table->output_expression, "|", sizeof("|"));
        }
        if(l == logic_table->height - 1) strncat(logic_table->output_expression, top_expression, sizeof(top_expression));  // Concatenate the current expression (without the OR operator)
    }
}