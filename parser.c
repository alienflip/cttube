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

// Function to build a logic table from a .tb file
void parser(logic_table* logic_table, char* line, int len, int line_counter){
    char io_flag = 'o'; // A flag to determine whether we're processing inputs ('i') or outputs ('o')
    int input_counter = 0;  // Counters for inputs and outputs to track how many inputs and outputs are processed
    int output_counter = 0;
    for(int i = len-1; i >=0; i--){ // Iterate through the line starting from the end (from right to left)
        if(line[i] == '|') io_flag = 'i';   // If the current character is '|', switch the io_flag to 'i' for input (everything before '|' is output)
        if(line[i] == ' ' || line[i] == '|' || line[i] == '\n') continue;   // Skip spaces, '|' (delimiter), and newline characters (these are not part of the data)
        if(line_counter == 0) { // header
            if(io_flag == 'o') {
                logic_table->header[output_counter] = line[i];  // If it's an output, store the character in the header at the current input index
                output_counter++;   // Increment the output index
            }
            else {
                logic_table->header[input_counter] = line[i];
                input_counter++;
            }
            logic_table->input_width = input_counter;   // After processing all inputs and outputs, update the input and output widths
            logic_table->output_width = output_counter; 
        }
        if(line_counter > 1) {  // body
            if(line[len-2] != '1') break;   // expression must evaluate to logic 1
            if(io_flag == 'o') continue;    // dont include output elements in the body
            logic_table->body[logic_table->height][input_counter] = line[i];
            input_counter++;
            if(i==0) logic_table->height++; // If we reached the beginning of the line, increment the height to move to the next row in the body
        }
    }
}