#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "fixedpoint.h"

Fixedpoint fixedpoint_create(uint64_t whole) {
  //this can only create non-negative values
  Fixedpoint res = {.whole_part = whole, .frac_part = 0, .tag = 1};
  return res;
}

Fixedpoint fixedpoint_create2(uint64_t whole, uint64_t frac) {
  //this can only create non-negative values
  Fixedpoint res = {.whole_part = whole, .frac_part = frac, .tag = 1};
  return res;
}

Fixedpoint fixedpoint_create_from_hex(const char *hex) {
  //initialize object to be returned and reassign hex
  Fixedpoint res = fixedpoint_create(0);

  char first_part[18] = "\0";
  size_t hex_index = 0;
  size_t index = 0;
  while (index < strlen(hex) && hex[hex_index] != '.' && index <= 16) {
    if (hex[hex_index] == '-') { // Second statement ensures we don't continue if there is a dash in the middle of the number
      res.tag = 2;
      hex_index++;
      continue;
    }
    first_part[index] = hex[hex_index];
    index++;
    hex_index++;
  }
  first_part[index] = 0;
  char second_part[18] = "\0";
  hex_index++;
  index = 0;
  while (hex_index < strlen(hex) && index <= 16) {
    second_part[index] = hex[hex_index];
    index++;
    hex_index++;
  }
  second_part[index] = 0;
  //check that all characters are valid hex characters
  if (!check_valid_hex_characters(first_part, second_part)) {
    res.tag = 3;
    return res;
  }
  //now we can read in the integers to the whole_part and frac_part
  if (strlen(first_part) == 0) {
    res.whole_part = 0;
  } else {
    res.whole_part = (uint64_t)strtoul(first_part, NULL, 16); //automatically returns 0 if string is emtpy
  }
  if (strlen(second_part) == 0) {
    res.frac_part = 0;
  } else {
    uint64_t before_padding = (uint64_t)strtoul(second_part, NULL, 16);
    //add leading zeros
    res.frac_part = before_padding << (64 - 4 * strlen(second_part));
  }
  uint64_t before_padding = (uint64_t)strtoul(second_part, NULL, 16);
  res.frac_part = before_padding << (64 - 4 * strlen(second_part));
  if (res.whole_part == 0 && res.frac_part == 0) {
    res.tag = 1;
  }
  return res;
}

int check_valid_hex_characters(const char *first_part, const char *second_part) {
  if (strlen(first_part) > 16 || strlen(second_part) > 16) {
    return 0;
  }
  for (size_t i = 0; i < strlen(first_part); i++) {
    if (!((tolower(first_part[i]) >= 'a' && tolower(first_part[i]) <= 'f') || (first_part[i] >= '0' && first_part[i] <= '9'))) {
      return 0;
    }
  }
  for (size_t j = 0; j < strlen(second_part); j++) {
    if (!((tolower(second_part[j]) >= 'a' && tolower(second_part[j]) <= 'f') || (second_part[j] >= '0' && second_part[j] <= '9'))) {
      return 0;
    }
  }
  return 1;
}

uint64_t fixedpoint_whole_part(Fixedpoint val) {
  return val.whole_part;
}

uint64_t fixedpoint_frac_part(Fixedpoint val) {
  return val.frac_part;
}

Fixedpoint fixedpoint_add(Fixedpoint left, Fixedpoint right) {
  Fixedpoint res = left;
  //if tags are the same just magnitude
  if (left.tag == right.tag) {
    res.whole_part = left.whole_part + right.whole_part;
    res.frac_part = left.frac_part + right.frac_part;
    if ((res.frac_part < left.frac_part) || (res.frac_part < right.frac_part)) {
      res.whole_part++;
    }
    if ((res.whole_part < left.whole_part) || (res.whole_part < right.whole_part)) {
      res.tag = left.tag + 3; //positive/negative overflow
    }
    return res;
  } else {
    //ensure greater magnitude on the left
    if (right.whole_part > left.whole_part || (left.whole_part == right.whole_part && right.whole_part > left.whole_part)) {
      res = right;
      right = left;
      left = res;
    }
    //do subtraction
    res.frac_part = left.frac_part - right.frac_part;
    res.whole_part = left.whole_part - right.whole_part;
    if (right.frac_part > left.frac_part) {
      res.whole_part--;
    }
    return res;
  }
}

Fixedpoint fixedpoint_sub(Fixedpoint left, Fixedpoint right) {
  return fixedpoint_add(left, fixedpoint_negate(right));
}

Fixedpoint fixedpoint_negate(Fixedpoint val) {
  //don't switch sign for a zero value
  if (!fixedpoint_is_zero(val)) {
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
  if ((val.frac_part & 1UL) == 1UL) {
    //underflow
    val.tag += 5;
    return val;
  }
  //using bit shifting to halve
  if ((val.whole_part & 1UL) == 1UL) {
    val.frac_part = val.frac_part >> 1;
    val.frac_part = val.frac_part | (1UL << 63);
    val.whole_part = val.whole_part >> 1;
  } else {
    val.frac_part = val.frac_part >> 1;
    val.whole_part = val.whole_part >> 1;
  }
  return val;
}

Fixedpoint fixedpoint_double(Fixedpoint val) {
  Fixedpoint res = val;
  uint64_t carry = 0;

  if (!fixedpoint_is_zero(val)) {
    if (val.frac_part * 2 < val.frac_part) {
      //overflow from frac to whole
      carry = 1;
    }
    res.frac_part = val.frac_part * 2;
    if (val.whole_part * 2 < val.whole_part) {
      //overflow
      res.tag = res.tag + 3;
    }
    res.whole_part = val.whole_part * 2 + carry;
  }
  return res; 
}

int fixedpoint_compare(Fixedpoint left, Fixedpoint right) {
  //int returnVal = 0;
  if (left.whole_part == right.whole_part && left.frac_part == right.frac_part && left.tag == right.tag) {
    return 0;
  }
  if (fixedpoint_is_neg(left) == 0 && fixedpoint_is_neg(right) == 1) {
    return 1; // left is positive & right is negative
  } else if (fixedpoint_is_neg(left) == 1 && fixedpoint_is_neg(right) == 0) {
    return -1; // left is negative & right is positive
  } else { // left and right have same sign
    if (left.whole_part > right.whole_part) {
      if (fixedpoint_is_neg(left)) { // both are negative & left is more negative than right
        return -1; 
      } else { // both are positive & left is less than right
        return 1;
      }
    } else if (left.whole_part < right.whole_part) {
      if (fixedpoint_is_neg(left)) { // both are negative & left is less negative than right
        return 1;
      } else { // both are positive & left is greater than right
        return -1;
      }
    } else { // whole parts are equal
      if (left.frac_part > right.frac_part) {
        if (fixedpoint_is_neg(left)) { // both are negative & left is more negative than right
          return -1;
        } else { // both are positive & left is less than right
          return 1;
        }
      } else if (left.frac_part < right.frac_part) {
        if (fixedpoint_is_neg(left)) { // both are negative & left is less negative than right
          return 1;
        } else { // both are positive & left is greater than right
          return -1;
        }
      } else {
        return  0;
      }
    }
  }
}

int fixedpoint_is_zero(Fixedpoint val) {
  return fixedpoint_is_valid(val) && val.whole_part == 0 && val.frac_part == 0;
}

int fixedpoint_is_err(Fixedpoint val) {
  return val.tag == 3;
}

int fixedpoint_is_neg(Fixedpoint val) {
  return val.tag == 2;
}

int fixedpoint_is_overflow_neg(Fixedpoint val) {
  return val.tag == 5;
}

int fixedpoint_is_overflow_pos(Fixedpoint val) {
  return val.tag == 4;
}

int fixedpoint_is_underflow_neg(Fixedpoint val) {
  return val.tag == 7;
}

int fixedpoint_is_underflow_pos(Fixedpoint val) {
  return val.tag == 6;
}

int fixedpoint_is_valid(Fixedpoint val) {
  return val.tag == 1 || val.tag == 2;
}

char *fixedpoint_format_as_hex(Fixedpoint val) {
  //allocated string for returning
  char *s = malloc(34);
  //using sprintf to format as hex
  int is_decimal = 0;
  if (fixedpoint_is_zero(val)) {
    strcpy(s, "0");
  } else if (val.tag == 1 && val.frac_part == 0) {
    sprintf(s, "%lx", val.whole_part);
  } else if (val.tag == 2 && val.frac_part == 0) {
    sprintf(s, "-%lx", val.whole_part);
  } else if (val.tag == 1 && val.frac_part != 0) {
    sprintf(s, "%lx.%016lx", val.whole_part, val.frac_part);
    is_decimal = 1;
  } else if (val.tag == 2 && val.frac_part != 0) {
    sprintf(s, "-%lx.%016lx", val.whole_part, val.frac_part);
    is_decimal = 1;
  }
  //trimming trailing zeros
  if (is_decimal) {
    for(int i = strlen(s) - 1; i >= 0; i--) {
      if (s[i] != '0') {
        s[i+1] = 0;
        break;
      }
    }
  }
  return s;
}
