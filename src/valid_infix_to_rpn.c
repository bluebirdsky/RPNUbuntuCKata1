#include "rpn_infix_utilities.h"
#include "valid_infix_to_rpn.h"

#include <string.h>

#define INDEX_SKIP_BRACKETTED_OPERAND 4

static bool expand_parened_operand(const int open_paren_index, const char *infix,
  char *rpn, const int rpn_buffersize) {

  bool was_buffer_exceeded = true;
  const int first_operand_index = open_paren_index + 1;
  const int operator_index = open_paren_index + 2;
  const int second_operand_index = open_paren_index + 3;

  was_buffer_exceeded = append_string(infix[first_operand_index], rpn, rpn_buffersize);
  was_buffer_exceeded = append_string(infix[second_operand_index], rpn, rpn_buffersize);
  was_buffer_exceeded = append_string(infix[operator_index], rpn, rpn_buffersize);
}

bool valid_infix_to_rpn(const char *infix, char *rpn, const int rpn_buffersize) {
  bool was_buffer_exceeded = true;
  int i;
  const int infix_length = strlen(infix);

  for( i=0; i < infix_length; ++i ) {
    if( is_operand(infix[i]) ) {
      was_buffer_exceeded = append_string(infix[i], rpn, rpn_buffersize);
    }
    else if( is_open_paren(infix[i]) ) {
      was_buffer_exceeded = expand_parened_operand(i, infix, rpn, rpn_buffersize);
      i += INDEX_SKIP_BRACKETTED_OPERAND;
    }
  }

  for( i=0; i < infix_length; ++i ) {
    if( is_open_paren(infix[i]) ) {
      i += INDEX_SKIP_BRACKETTED_OPERAND;
    }
    else if( is_operator(infix[i]) ) {
      was_buffer_exceeded = append_string(infix[i], rpn, rpn_buffersize);
    }
  }

  return was_buffer_exceeded;
}
