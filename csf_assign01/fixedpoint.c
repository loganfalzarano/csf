#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "fixedpoint.h"

// You can remove this once all of the functions are fully implemented
//static Fixedpoint DUMMY;

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
  size_t hex_index = 0;
  size_t index = 0;
  while (index < strlen(hex) && hex[hex_index] != '.' && index <= 16) {
    //printf("char is: %c, index is: %d\n", hex[hex_index], index);
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
    if (!((first_part[i] >= 'a' && first_part[i] <= 'f') || (first_part[i] >= 'A' && first_part[i] <= 'F') || (first_part[i] >= '0' && first_part[i] <= '9'))) {
      res.tag = 3;
      //printf("Found error value\n\n");
      return res; //TODO: return res or retun NULL
    }
  }
  for (size_t j = 0; j < strlen(second_part); j++) {
    if (!((second_part[j] >= 'a' && second_part[j] <= 'f') || (first_part[j] >= 'A' && first_part[j] <= 'F') || (second_part[j] >= '0' && second_part[j] <= '9'))) {
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
  // Fixedpoint left1 = fixedpoint_create2(-9, 2);
  // Fixedpoint right1 = fixedpoint_create2(7, 3);
  // //printf("The left most bit is: %d");
  // Fixedpoint res;
  // uint64_t carry = 0;
  // res.frac_part = left1.frac_part + right1.frac_part;
  // if (left1.tag == right1.tag) {
  //   if (res.frac_part < left1.frac_part || res.frac_part < right1.frac_part) {
  //     uint64_t carry = 1;
  //   }
  //   res.whole_part = left1.whole_part + right1.whole_part + carry;  
  //   if (res.whole_part < left1.whole_part || res.whole_part < right1.whole_part) {
  //     res.tag = 4;
  //     //indicate overflow
  //   }
  // } else {
  //   //do subtraction with a negated value instead
  // }


  // printf("\nWhole part is %ld\n", res.whole_part);
  // printf("Frac part is %ld\n\n", res.frac_part);

  Fixedpoint res = left;
  if (left.tag == right.tag) {
    res.whole_part = left.whole_part + right.whole_part;
    res.frac_part = left.frac_part + right.frac_part;

    if (res.frac_part < left.frac_part || res.frac_part < right.frac_part) {
      res.whole_part++;
    }
    if (res.whole_part < left.whole_part || res.whole_part < right.whole_part) {
      res.tag = left.tag + 3; //positive/negative overflow
    }
    return res;
  } else if (fixedpoint_is_neg(left) && !fixedpoint_is_neg(right)) {
    res = fixedpoint_sub(right, fixedpoint_negate(left));
  } else if (!fixedpoint_is_neg(left) && fixedpoint_is_neg(right)) {
    res = fixedpoint_sub(left, fixedpoint_negate(right));
  }
  
  return res;
}

Fixedpoint fixedpoint_sub(Fixedpoint left, Fixedpoint right) {
  Fixedpoint res;
  if (left.tag == right.tag) {
    if (left.whole_part > right.whole_part) {
      res.whole_part = left.whole_part - right.whole_part;
      if (left.frac_part > right.frac_part) {
        res.frac_part = left.frac_part - right.frac_part;
      } else {
        res.frac_part = right.frac_part - left.frac_part;
      }
    } else { // right > left or right == left
      res.whole_part = right.whole_part - left.whole_part;
      if (left.frac_part > right.frac_part) {
        res.frac_part = left.frac_part - right.frac_part;
      } else {
        res.frac_part = right.frac_part - left.frac_part;
      }
    }
    res.tag = left.tag; 
  }
  else if (left.tag == 2 && right.tag ==1) {
    res = fixedpoint_negate(fixedpoint_add(fixedpoint_negate(left), right));
  }
  else if ((left.tag == 1 && right.tag == 2) || (left.tag == 2 && right.tag == 2)) {
    res = fixedpoint_add(left, fixedpoint_negate(right));
  }
  else {
    return res; //Underflow???
  }
  return res;
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
  Fixedpoint res = val;
  //uint64_t carry = 0;

  if (!fixedpoint_is_zero(val)) {
    //res.whole_part = val.whole_part / 2;
    res.whole_part = val.whole_part>>1;
    res.frac_part = val.frac_part>>1;

    if (val.whole_part % 2 != 0) {
      //carry = 1;
      res.frac_part = res.frac_part | 1UL<<63;
    }

    //res.frac_part =  carry + val.frac_part / 2;
    if (val.frac_part % 2 != 0) {
      res.tag = res.tag + 5;
    }
  }
  return res;
}

Fixedpoint fixedpoint_double(Fixedpoint val) {
  Fixedpoint res = val;
  uint64_t carry = 0;

  if (!fixedpoint_is_zero(val)) {
    if (val.frac_part * 2 < val.frac_part)
    {
      carry = 1;
    }
    res.frac_part = val.frac_part * 2;
    if (val.whole_part * 2 < val.whole_part)
    {
      res.tag = res.tag + 3;
    }
    res.whole_part = val.whole_part * 2 + carry;
  }
  return res;
}

int fixedpoint_compare(Fixedpoint left, Fixedpoint right) {

  // no error handling, not sure if we need it

  //int returnVal = 0;
  if (left.whole_part == right.whole_part && left.frac_part == right.frac_part && left.tag == right.tag) {
    return 0;
  }
  if (fixedpoint_is_neg(left) == 0 && fixedpoint_is_neg(right) == 1) {
    // left is positive & right is negative
    return 1;
  } else if (fixedpoint_is_neg(left) == 1 && fixedpoint_is_neg(right) == 0) {
    // left is negative & right is positive
    return -1;
  } else { // left and right have same sign
    if (left.whole_part > right.whole_part) {
      if (fixedpoint_is_neg(left)) {
        // both are negative & left is more negative than right
        return -1;
      } else {
        // both are positive & left is less than right
        return 1;
      }
    } else if (left.whole_part < right.whole_part) {
      if (fixedpoint_is_neg(left)) {
        // both are negative & left is less negative than right
        return 1;
      } else {
        // both are positive & left is greater than right
        return -1;
      }
    } else {
      // whole parts are equal
      if (left.frac_part > right.frac_part) {
        if (fixedpoint_is_neg(left)) {
          // both are negative & left is more negative than right
          return -1;
        } else {
          // both are positive & left is less than right
          return 1;
        }
      } else if (left.frac_part < right.frac_part) {
        if (fixedpoint_is_neg(left)) {
          // both are negative & left is less negative than right
          return 1;
        } else {
          // both are positive & left is greater than right
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
  /* // TODO: implement
  assert(0);
  char *s = malloc(20);
  strcpy(s, "<invalid>");
  return s; */


  // TODO: implement
  char *s = malloc(34);

  //TODO: Deal with issue of trailing zeros
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
  if (is_decimal) {
    for(int i = strlen(s) - 1; i >= 0; i--) {
      if (s[i] != '0') {
        s[i+1] = 0;
        break;
      }
    }
  }
  
  

  //printf("\n\n The string is: %s\n\n", s);
  
  return s;
}
