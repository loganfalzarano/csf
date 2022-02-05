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
  //this can only create non-negative values
  Fixedpoint res;
  res.whole_part = whole;
  res.frac_part = 0;
  res.tag = 1;
  return res;
}

Fixedpoint fixedpoint_create2(uint64_t whole, uint64_t frac) {
  //this can only create non-negative values
  Fixedpoint res;
  res.whole_part = whole;
  res.frac_part = frac;
  res.tag = 1;
  return res;
}

Fixedpoint fixedpoint_create_from_hex(const char *hex) {
  // TODO: implement

  // TODO: Consider special case for

  //initialize object to be returned and reassign hex
  Fixedpoint res;

  res.tag = 1; //Assume it's valid unless we see otherwise

  //const char * hex = "0.d";

  char first_part[17];
  int hex_index = 0;
  int index = 0;
  while (index < strlen(hex) && hex[hex_index] != '.' && index <= 16) {
    //printf("char is: %c, index is: %d\n", hex[hex_index], index);
    if (hex[hex_index] == '-') {
      res.tag = 2;
      hex_index++;
      continue;
    }
    first_part[index] = hex[hex_index];
    index++;
    hex_index++;
  }
  first_part[index] = 0;
  char second_part[17];
  hex_index++;
  index = 0;
  while (hex_index < strlen(hex) && index <= 16) {
    //printf("second part: char is: %c, index is: %d\n", hex[hex_index], index);
    second_part[index] = hex[hex_index];
    index++;
    hex_index++;
  }
  second_part[index] = 0;

  //printf("FIRSRT PART IS: |%s|", first_part);
  //printf("SECOND PART IS: |%s|", second_part);
  
  //check that all characters are valid hex characters
  if (strlen(first_part) > 16 || strlen(second_part) > 16) {
    res.tag = 3;
    //printf("Error, too many characters");
  }
  for (size_t i = 0; i < strlen(first_part); i++) {
    if (!((first_part[i] >= 'a' && first_part[i] <= 'f') || (first_part[i] >= '0' && first_part[i] <= '9'))) {
      res.tag = 3;
      //printf("Found error value\n\n");
      return res; //TODO: return res or retun NULL
    }
  }
  for (size_t j = 0; j < strlen(second_part); j++) {
    if (!((second_part[j] >= 'a' && second_part[j] <= 'f') || (second_part[j] >= '0' && second_part[j] <= '9'))) {
      //printf("Found error value\n\n");
      res.tag = 3;
      return res; //TODO: return res or retun NULL
    }
  }

  //now we can read in the integers to the whole_part and frac_part
  res.whole_part = (uint64_t)strtoul(first_part, NULL, 16); //automatically returns 0 if string is emtpy
  uint64_t before_padding = (uint64_t)strtoul(second_part, NULL, 16);
  //add leading zeros
  res.frac_part = before_padding << (64 - 4 * strlen(second_part));
  if (res.whole_part == 0 && res.frac_part == 0) res.tag = 1;

  //printf("\n\nWhole part is: %ld\nFrac part is: %ld\n", res.whole_part, res.frac_part);
  //printf("tag is: %d\n\n\n", res.tag);
  return res;
}

uint64_t fixedpoint_whole_part(Fixedpoint val) {
  return val.whole_part;
}

uint64_t fixedpoint_frac_part(Fixedpoint val) {
  return val.frac_part;
}

Fixedpoint fixedpoint_add(Fixedpoint left, Fixedpoint right) {
  Fixedpoint left1 = fixedpoint_create2(-9, 2);
  Fixedpoint right1 = fixedpoint_create2(7, 3);
  //printf("The left most bit is: %d");
  Fixedpoint res;
  uint64_t carry = 0;
  res.frac_part = left1.frac_part + right1.frac_part;
  if (left1.tag == right1.tag) {
    if (res.frac_part < left1.frac_part || res.frac_part < right1.frac_part) {
      uint64_t carry = 1;
    }
    res.whole_part = left1.whole_part + right1.whole_part + carry;  
    if (res.whole_part < left1.whole_part || res.whole_part < right1.whole_part) {
      res.tag = 4;
      //indicate overflow
    } 
  } else {
    //do subtraction with a negated value instead
  }


  printf("\nWhole part is %ld\n", res.whole_part);
  printf("Frac part is %ld\n\n", res.frac_part);

  
  return res;
}

Fixedpoint fixedpoint_sub(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  assert(0);
  return DUMMY;
}

Fixedpoint fixedpoint_negate(Fixedpoint val) {
  //don't switch sign for a zero value
  if (!fixedpoint_is_zero) {
    //toggle negative to positve and vice a verse
    if (val.tag == 1) {
      val.tag = 2;
    } else if (val.tag == 2) {
      val.tag = 1;
    }
  }
  return val;
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
  /* // TODO: implement
  assert(0);
  char *s = malloc(20);
  strcpy(s, "<invalid>");
  return s; */


  // TODO: implement
  char *s = malloc(34);

  //TODO: Deal with issue of trailing zeros

  if (fixedpoint_is_zero(val)) {
    strcpy(s, "0");
  } else if (val.tag == 1 && val.frac_part == 0) {
    sprintf(s, "%lx", val.whole_part);
  } else if (val.tag == 2 && val.frac_part == 0) {
    sprintf(s, "-%lx", val.whole_part);
  } else if (val.tag == 1 && val.frac_part != 0) {
    sprintf(s, "%lx.%016lx", val.whole_part, val.frac_part);
  } else if (val.tag == 2 && val.frac_part != 0) {
    sprintf(s, "-%lx.%016lx", val.whole_part, val.frac_part);
  }

  printf("\n\n The string is: %s\n\n", s);
  
  return s;
}
