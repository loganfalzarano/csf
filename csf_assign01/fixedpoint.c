#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
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
  // TODO: This isn't correct but it's an idea

  //Determine if there's a negative sign
  Fixedpoint res;
  if (hex[0] == '-') res.tag = 2;


  //Determine if there's a negative sign
  // bool is_negative = false;
  // if (hex[0] == '-') is_negative = true;

  // int len = strlen(hex);
  // if (len > 34) {
  //   hex.tag = 3;
  // }

  //find whether/where the '.' occurs to split into whole and fractional
  int dot_index = -1;
  for (; dot_index < strlen(hex); dot_index++) {
    if (hex[dot_index] == '.') {
      break;
    }
  }
  //if we can't find a dot
  if (dot_index == -1) {
    //read only the whole part and deal with the negative
  }


  //Otherwise there is a dot and split the hex string into two strings 
  char whole_hex[dot_index];
  char frac_hex[strlen(hex) - dot_index];
  for (int j = 0; j < dot_index; j++) {
    whole_hex[j] = hex[j];
  }
  for (int k = 0; k + dot_index < strlen(hex); k++) {
    frac_hex[k] = hex[dot_index + k];
  }

  uint64_t whole_val;
  uint64_t frac_val;

  sscanf(whole_hex, "%x", &whole_hex);
  sscanf(frac_hex, "%x", &frac_val);

  //here we want to use sscanf and bitshifting to make the conversion
  //int store_value;
  //sscanf(hex, "%x" , &store_value);

  //Fixedpoint res;
  res.whole_part = whole_hex;
  res.frac_part = frac_val;
  //res.tag = 1;

  assert(0);
  return res;
}

uint64_t fixedpoint_whole_part(Fixedpoint val) {
  //TODO: Do we need to do error handling here? -- I don't think so-Tal
  return val.whole_part;
}

uint64_t fixedpoint_frac_part(Fixedpoint val) {
  //TODO: Do we need to do error handling here? -- I don't think so-Tal
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
  return fixedpoint_is_valid(val) && val.whole_part == 0 && val.frac_part == 0;
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
  return val.tag == 1 || val.tag == 2;
}

char *fixedpoint_format_as_hex(Fixedpoint val) {
  // TODO: implement
  assert(0);
  char *s = malloc(20);
  strcpy(s, "<invalid>");
  return s;
}
