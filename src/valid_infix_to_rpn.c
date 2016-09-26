#include "rpn_infix_utilities.h"
#include "valid_infix_to_rpn.h"

#include <string.h>

static int number_of_operands(const char *infix) {
  int i;
  const int infix_length = strlen(infix);
  int count = 0;

  for( i=0; i < infix_length; ++i ) {
    if(is_operand(infix[i])) {
      ++count;
    }
  }
  return count;
}

static bool push_to_stack(const char token, char *stack, const int stack_buffersize) {
  return append_string(token, stack, stack_buffersize);
}

char pop_from_stack(char *stack) {
  int stack_length = strlen(stack);
  const char token = stack[stack_length-1];
  stack[stack_length-1] = '\0';
  return token;
}

bool valid_infix_to_rpn(const char *infix, char *rpn, const int rpn_buffersize) {
  bool was_buffer_exceeded = true;
  int i;
  const int infix_length = strlen(infix);
  int operator_stack_length;
  char tmp_token;
  const int operator_stack_buffersize = infix_length - number_of_operands(infix) + 1;
  char operator_stack[operator_stack_buffersize];
  strcpy(operator_stack,"");

  for( i=0; i < infix_length; ++i ) {
    if( is_operand(infix[i]) ) {
      was_buffer_exceeded = push_to_stack(infix[i], rpn, rpn_buffersize);
    }
    else if( is_open_paren(infix[i]) || is_closed_paren(infix[i]) ) {
      was_buffer_exceeded = push_to_stack(infix[i], operator_stack, operator_stack_buffersize);
    }
    else if( is_operator(infix[i]) ) {
      operator_stack_length = strlen(operator_stack);

      if(operator_stack_length > 1) {
        was_buffer_exceeded = push_to_stack(pop_from_stack(operator_stack), operator_stack, operator_stack_buffersize);
      }
      was_buffer_exceeded = push_to_stack(infix[i], operator_stack, operator_stack_buffersize);
    }
  }

  operator_stack_length = strlen(operator_stack);

  while( operator_stack_length ) {
    tmp_token = pop_from_stack(operator_stack);
    if( is_open_paren(tmp_token) || is_closed_paren(tmp_token) ) {
      continue;
    }
    else if( is_operator(tmp_token) ) {
        was_buffer_exceeded = push_to_stack(tmp_token, rpn, rpn_buffersize);
    }
    operator_stack_length = strlen(operator_stack);
  }
  return was_buffer_exceeded;
}
