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
  char hex1[90] = "123xabc.4";
  
  //strip off the negative if there is one
  if (hex1[0] == '-') {
    res.tag = 2; //set value to be valid negative
    //hex1 = hex1 + 1;  //TODO MAKE SURE TO CHANGE BACK TO HEX
  }
  printf("\n(1)\n");

  //split the hex string into two parts
    //char hex1[50] = "-.0";
  char * first_part = strtok(hex1, ".");
  printf("\n(2)\n");
  char * second_part = strtok(NULL, " "); // TODO: Use "\0" or " "

  printf( "|%s|\n", hex1 );
  printf( "|%s|\n", first_part ); //printing the token
  printf("|%s| wowowowowoo\n", second_part);
  

  //deal with special case "0.0", "", etc"
  if (first_part == NULL && second_part == NULL) { //if both are NULL it's invalid
    res.tag = 3;
    printf("Found error value\n\n");
    return res;
  } else if (first_part == NULL && second_part != NULL) { //if the first part is NULL and second part is non-NULL whole part is 0
    first_part = "0\0";
  } else if (second_part == NULL && first_part != NULL) { //if the second part is NULL and the second part is non-NULL frac part is 0
    second_part = "0\0";
  }
  printf("\n(3)\n");

  printf( "|%s|\n", hex1 );
  printf( "|%s|\n", first_part ); //printing the token
  printf("|%s|\n", second_part);

  //check that both strings are valid (error checking)
  //TODO:check that the values are not too BIG

  for (size_t i = 0; i < strlen(first_part); i++) {
    //printf("char is: %c \n", first_part[i]);
    //printf("between a and f: %d\n", (first_part[i] >= 'a' && first_part[i] <= 'f'));
    //printf("between 0 and 9\n", (first_part[i] >= '0' || first_part[i] <= '9'));
    if (!((first_part[i] >= 'a' && first_part[i] <= 'f') || (first_part[i] >= '0' && first_part[i] <= '9'))) {
      res.tag = 3;
      printf("Found error value\n\n");
      return res; //TODO: return res or retun NULL
    }
  }
  for (size_t j = 0; j < strlen(second_part); j++) {
    if (!((second_part[j] >= 'a' && second_part[j] <= 'f') || (second_part[j] >= '0' && second_part[j] <= '9'))) {
      printf("Found error value\n\n");
      res.tag = 3;
      return res; //TODO: return res or retun NULL
    }
  }


  //now we can read in the integers to the whole_part and frac_part
  res.whole_part = strtoul(first_part, NULL, 16);
  res.frac_part = strtoul(second_part, NULL, 16);
  if (res.whole_part == 0 && res.frac_part == 0) res.tag = 1;

  printf("\n\nWhole part is: %ld\nFrac part is: %ld\n", res.whole_part, res.frac_part);
  printf("tag is: %d\n\n\n", res.tag);





  



  
  
  
  

/* 
  //Determine if there's a negative sign
  // bool is_negative = false;
  // if (hex[0] == '-') is_negative = true;

  // TODO: This isn't correct but it's an idea
  printf("got here");

  //Determine if there's a negative sign
  Fixedpoint res;
  if (hex[0] == '-') {
    res.tag = 2;
    hex = hex + 1;  
  }
  


  //Determine if there's a negative sign
  // bool is_negative = false;
  // if (hex[0] == '-') is_negative = true;

  //find whether/where the '.' occurs to split into whole and fractional
  char *hex1 = "-6666666666666666.8888888888888888";
  if (hex1[0] == '-') {
      res.tag = 2;
      hex1 = hex1 + 1;  
      printf("Woo hoo %s", hex1);
  }

  char *dot_char = strchr(hex1, '.');
  int dot_index;
  if (dot_char == NULL) {
    return res;
  } else {
    dot_index = (int)(dot_char - hex1);
    printf("%s %d\n\n\n\n", hex1, dot_index);
  }

  char first[dot_index + 1];
  printf("GOTHERE");
  strncpy(first, hex1, dot_index);
  first[dot_index] = "\0";
  printf("PLEASE: %s END", first);

  uint64_t w;
  uint64_t f;
  char d;

  sscanf(hex1, "%x%c%x", &w, &d, &f);
  printf("Whole:%d    Frac:%d", w,f);

  
  
  

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

  // Reads in whole value
  for (int j = 0; j < dot_index; j++) {
    whole_hex[j] = hex[j];
    if (hex[j] == '-' && j == 0) {
      continue;
    }
    if (!((hex[j] >= 'a' && hex[j] <= 'f') || (hex[j] >= '0' || hex[j] <= '9'))) {
      res.tag = 3;
    }
  }

  // Reads in fractional value
  for (int k = 0; k + dot_index < strlen(hex); k++) {
    
    char x = hex[dot_index + k];
    frac_hex[k] = x;

    if (!((x >= 'a' && x <= 'f') || (x >= '0' || x <= '9'))) {
        res.tag = 3;
      }
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

 */  
}

uint64_t fixedpoint_whole_part(Fixedpoint val) {
  return val.whole_part;
}

uint64_t fixedpoint_frac_part(Fixedpoint val) {
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
