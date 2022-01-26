#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "fixedpoint.h"

// You can remove this once all of the functions are fully implemented
static Fixedpoint DUMMY;

Fixedpoint fixedpoint_create(uint64_t whole) {
  // TODO: implement

  //this can only create non-negative values
  Fixedpoint res;
  res.whole_part = whole;
  res.frac_part = 0;
  res.tag = 1;
  //assert(0);
  return res;
}

Fixedpoint fixedpoint_create2(uint64_t whole, uint64_t frac) {
  // TODO: implement

  //this can only create non-negative values
  Fixedpoint res;
  res.whole_part = whole;
  res.frac_part = frac;
  res.tag = 1;
  //assert(0);
  return res;
}

Fixedpoint fixedpoint_create_from_hex(const char *hex) {
  // TODO: implement

  //find where the '.' occurs to split into who and fractional
  for (int i = 0; i < strlen(hex); i++) {
    if (hex[i] == '.') {
      break
    }
  }
  const char whole[] 

  //here we want to use sscanf and bitsifting to make the conversion
  int store_value;
  sscanf(hex, "%x" , &store_value);

  assert(0);
  return DUMMY;
}

uint64_t fixedpoint_whole_part(Fixedpoint val) {
  //TODO: Do we need to do error handling here?
  return val.whole_part;
}

uint64_t fixedpoint_frac_part(Fixedpoint val) {
  //TODO: Do we need to do error handling here?
  return val.frac_part;
}

Fixedpoint fixedpoint_add(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  assert(0);
  return DUMMY;
}

Fixedpoint fixedpoint_sub(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  assert(0);
  return DUMMY;
}

Fixedpoint fixedpoint_negate(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return DUMMY;
}

Fixedpoint fixedpoint_halve(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return DUMMY;
}

Fixedpoint fixedpoint_double(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return DUMMY;
}

int fixedpoint_compare(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_zero(Fixedpoint val) {
  //Logan - "Don't know if this is right"
  return val.whole_part == 0 && val.frac_part == 0;
}

int fixedpoint_is_err(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_neg(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_overflow_neg(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_overflow_pos(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_underflow_neg(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_underflow_pos(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_valid(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

char *fixedpoint_format_as_hex(Fixedpoint val) {
  // TODO: implement
  assert(0);
  char *s = malloc(20);
  strcpy(s, "<invalid>");
  return s;
}
