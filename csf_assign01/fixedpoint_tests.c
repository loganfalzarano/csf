#include <stdio.h>
#include <stdlib.h>
#include "fixedpoint.h"
#include "tctest.h"

// Test fixture object, has some useful values for testing
typedef struct {
  Fixedpoint zero;
  Fixedpoint one;
  Fixedpoint one_half;
  Fixedpoint one_fourth;
  Fixedpoint large1;
  Fixedpoint large2;
  Fixedpoint max;
} TestObjs;

// functions to create and destroy the test fixture
TestObjs *setup(void);
void cleanup(TestObjs *objs);

//provided tests
void test_whole_part(TestObjs *objs);
void test_frac_part(TestObjs *objs);
void test_create_from_hex(TestObjs *objs);
void test_format_as_hex(TestObjs *objs);
void test_negate(TestObjs *objs);
void test_add(TestObjs *objs);
void test_sub(TestObjs *objs);
void test_is_overflow_pos(TestObjs *objs);
void test_is_err(TestObjs *objs);
//Our tests
//create functions
void test_fixedpoint_create(TestObjs *objs);
void test_fixedpoint_create2(TestObjs *objs);
//create from hex
void test_create_from_hex_leading_and_trailing_zeros(TestObjs *objs);
void test_create_from_hex_special_cases(TestObjs *objs);
//add function
void test_add_fractions_carry_over(TestObjs *objs);
void test_add_with_second_value_negative(TestObjs *objs);
void test_add_with_both_values_positive(TestObjs *objs);
void test_add_with_both_values_negative(TestObjs *objs);
void test_add_with_opposite_signs_causes_carry(TestObjs *objs);
void test_add_frac_part_causes_pos_overflow_in_whole_part(TestObjs *objs);
void test_add_frac_part_causes_neg_overflow_in_whole_part(TestObjs *objs);
//subtract function
void test_sub_with_two_positive_values(TestObjs *objs);
void test_sub_with_two_negative_values(TestObjs *objs);
void test_sub_with_opposite_signs_neg_first(TestObjs *objs);
void test_sub_with_opposite_signs_pos_first(TestObjs *objs);
//negate function
void test_fixedpoint_negate(TestObjs *objs);
//halve function
void test_fixedpoint_halve(TestObjs *objs);
void test_fixedpoint_halve_negative_value(TestObjs *objs);
void test_fixedpoint_halve_causes_pos_underflow(TestObjs *objs);
void test_fixedpoint_halve_causes_neg_underflow(TestObjs *objs);
//double function
void test_fixedpoint_double(TestObjs *objs);
void test_fixedpoint_double_negative_value(TestObjs *objs);
void test_fixedpoint_double_causes_overflow_pos(TestObjs *objs);
void test_fixedpoint_double_causes_overflow_neg(TestObjs *objs);
//compare function
void test_fixedpoint_compare_pos_vals(TestObjs *objs);
void test_fixedpoint_compare_neg_vals(TestObjs *objs);
void test_fixedpoint_compare_opposite_signs(TestObjs *objs);
//is zero function
void test_fixedpoint_is_zero(TestObjs *objs);
//is err function
void test_fixedpoint_is_err(TestObjs *objs);
//tag tests
void tag_test_is_neg(TestObjs *objs);
void tag_test_is_overflow_neg(TestObjs *objs);
void tag_test_is_overflow_pos(TestObjs *objs);
void tag_test_is_underflow_neg(TestObjs *objs);
void tag_test_is_underflow_pos(TestObjs *objs);
void tag_test_is_valid(TestObjs *objs);
//format as hex functions
void test_fixedpoint_format_as_hex_positives(TestObjs *objs);
void test_fixedpoint_format_as_hex_negatives(TestObjs *objs);
void test_format_as_hex_edges_cases(TestObjs *objs);


int main(int argc, char **argv) {
  // if a testname was specified on the command line, only that
  // test function will be executed
  if (argc > 1) {
    tctest_testname_to_execute = argv[1];
  }

  TEST_INIT();
  //provided tests
  TEST(test_whole_part);
  TEST(test_frac_part);
  TEST(test_create_from_hex);
  TEST(test_format_as_hex);
  TEST(test_negate);
  TEST(test_add);
  TEST(test_sub);
  TEST(test_is_overflow_pos);
  TEST(test_is_err);
  //\/--Test Functions we wrote--\/
  //create functions
  TEST(test_fixedpoint_create);
  TEST(test_fixedpoint_create2);
  //create from hex
  TEST(test_create_from_hex_special_cases);
  TEST(test_create_from_hex_leading_and_trailing_zeros);
  //add function
  TEST(test_add_fractions_carry_over);
  TEST(test_add_with_second_value_negative);
  TEST(test_add_with_both_values_positive);
  TEST(test_add_with_both_values_negative);
  TEST(test_add_with_opposite_signs_causes_carry);
  TEST(test_add_frac_part_causes_pos_overflow_in_whole_part);
  TEST(test_add_frac_part_causes_neg_overflow_in_whole_part);
  //subtract function
  TEST(test_sub_with_two_positive_values);
  TEST(test_sub_with_two_negative_values);
  TEST(test_sub_with_opposite_signs_neg_first);
  TEST(test_sub_with_opposite_signs_pos_first);
  //negate function
  TEST(test_fixedpoint_negate);
  //halve function
  TEST(test_fixedpoint_halve);
  TEST(test_fixedpoint_halve_negative_value);
  TEST(test_fixedpoint_halve_causes_pos_underflow);
  TEST(test_fixedpoint_halve_causes_neg_underflow);
  //double function
  TEST(test_fixedpoint_double);
  TEST(test_fixedpoint_double_negative_value);
  TEST(test_fixedpoint_double_causes_overflow_pos);
  TEST(test_fixedpoint_double_causes_overflow_neg);
  //compare function
  TEST(test_fixedpoint_compare_pos_vals);
  TEST(test_fixedpoint_compare_neg_vals);
  TEST(test_fixedpoint_compare_opposite_signs);
  //is zero function
  TEST(test_fixedpoint_is_zero);
  //is err function
  TEST(test_fixedpoint_is_err);
  //tag functions
  TEST(tag_test_is_neg);
  TEST(tag_test_is_overflow_neg);
  TEST(tag_test_is_overflow_pos);
  TEST(tag_test_is_underflow_neg);
  TEST(tag_test_is_underflow_pos);
  TEST(tag_test_is_valid);
  //format as hex functions
  TEST(test_fixedpoint_format_as_hex_positives);
  TEST(test_fixedpoint_format_as_hex_negatives);
  TEST(test_format_as_hex_edges_cases);


  // IMPORTANT: if you add additional test functions (which you should!),
  // make sure they are included here.  E.g., if you add a test function
  // "my_awesome_tests", you should add
  //
  //   TEST(my_awesome_tests);
  //
  // here. This ensures that your test function will actually be executed.

  TEST_FINI();
}

TestObjs *setup(void) {
  TestObjs *objs = malloc(sizeof(TestObjs));

  objs->zero = fixedpoint_create(0UL);
  objs->one = fixedpoint_create(1UL);
  objs->one_half = fixedpoint_create2(0UL, 0x8000000000000000UL);
  objs->one_fourth = fixedpoint_create2(0UL, 0x4000000000000000UL);
  objs->large1 = fixedpoint_create2(0x4b19efceaUL, 0xec9a1e2418UL);
  objs->large2 = fixedpoint_create2(0xfcbf3d5UL, 0x4d1a23c24fafUL);
  objs->max = fixedpoint_create2(0xFFFFFFFFFFFFFFFFUL, 0xFFFFFFFFFFFFFFFFUL);

  return objs;
}

void cleanup(TestObjs *objs) {
  free(objs);
}

void test_whole_part(TestObjs *objs) {
  ASSERT(0UL == fixedpoint_whole_part(objs->zero));
  ASSERT(1UL == fixedpoint_whole_part(objs->one));
  ASSERT(0UL == fixedpoint_whole_part(objs->one_half));
  ASSERT(0UL == fixedpoint_whole_part(objs->one_fourth));
  ASSERT(0x4b19efceaUL == fixedpoint_whole_part(objs->large1));
  ASSERT(0xfcbf3d5UL == fixedpoint_whole_part(objs->large2));
}

void test_frac_part(TestObjs *objs) {
  ASSERT(0UL == fixedpoint_frac_part(objs->zero));
  ASSERT(0UL == fixedpoint_frac_part(objs->one));
  ASSERT(0x8000000000000000UL == fixedpoint_frac_part(objs->one_half));
  ASSERT(0x4000000000000000UL == fixedpoint_frac_part(objs->one_fourth));
  ASSERT(0xec9a1e2418UL == fixedpoint_frac_part(objs->large1));
  ASSERT(0x4d1a23c24fafUL == fixedpoint_frac_part(objs->large2));
}

void test_create_from_hex(TestObjs *objs) {
  (void) objs;

  Fixedpoint val1 = fixedpoint_create_from_hex("f6a5865.00f2");

  ASSERT(fixedpoint_is_valid(val1));

  ASSERT(0xf6a5865UL == fixedpoint_whole_part(val1));

  ASSERT(0x00f2000000000000UL == fixedpoint_frac_part(val1));
}

void test_format_as_hex(TestObjs *objs) {
  char *s;

  s = fixedpoint_format_as_hex(objs->zero);
  ASSERT(0 == strcmp(s, "0"));
  free(s);

  s = fixedpoint_format_as_hex(objs->one);
  ASSERT(0 == strcmp(s, "1"));
  free(s);

  s = fixedpoint_format_as_hex(objs->one_half);
  ASSERT(0 == strcmp(s, "0.8"));
  free(s);

  s = fixedpoint_format_as_hex(objs->one_fourth);
  ASSERT(0 == strcmp(s, "0.4"));
  free(s);

  s = fixedpoint_format_as_hex(objs->large1);
  ASSERT(0 == strcmp(s, "4b19efcea.000000ec9a1e2418"));
  free(s);

  s = fixedpoint_format_as_hex(objs->large2);
  ASSERT(0 == strcmp(s, "fcbf3d5.00004d1a23c24faf"));
  free(s);
}

void test_negate(TestObjs *objs) {
  // none of the test fixture objects are negative
  ASSERT(!fixedpoint_is_neg(objs->zero));
  ASSERT(!fixedpoint_is_neg(objs->one));
  ASSERT(!fixedpoint_is_neg(objs->one_half));
  ASSERT(!fixedpoint_is_neg(objs->one_fourth));
  ASSERT(!fixedpoint_is_neg(objs->large1));
  ASSERT(!fixedpoint_is_neg(objs->large2));

  // negate the test fixture values
  Fixedpoint zero_neg = fixedpoint_negate(objs->zero);
  Fixedpoint one_neg = fixedpoint_negate(objs->one);
  Fixedpoint one_half_neg = fixedpoint_negate(objs->one_half);
  Fixedpoint one_fourth_neg = fixedpoint_negate(objs->one_fourth);
  Fixedpoint large1_neg = fixedpoint_negate(objs->large1);
  Fixedpoint large2_neg = fixedpoint_negate(objs->large2);

  // zero does not become negative when negated
  ASSERT(!fixedpoint_is_neg(zero_neg));

  // all of the other values should have become negative when negated
  ASSERT(fixedpoint_is_neg(one_neg));
  ASSERT(fixedpoint_is_neg(one_half_neg));
  ASSERT(fixedpoint_is_neg(one_fourth_neg));
  ASSERT(fixedpoint_is_neg(large1_neg));
  ASSERT(fixedpoint_is_neg(large2_neg));

  // magnitudes should stay the same
  ASSERT(0UL == fixedpoint_whole_part(objs->zero));
  ASSERT(1UL == fixedpoint_whole_part(objs->one));
  ASSERT(0UL == fixedpoint_whole_part(objs->one_half));
  ASSERT(0UL == fixedpoint_whole_part(objs->one_fourth));
  ASSERT(0x4b19efceaUL == fixedpoint_whole_part(objs->large1));
  ASSERT(0xfcbf3d5UL == fixedpoint_whole_part(objs->large2));
  ASSERT(0UL == fixedpoint_frac_part(objs->zero));
  ASSERT(0UL == fixedpoint_frac_part(objs->one));
  ASSERT(0x8000000000000000UL == fixedpoint_frac_part(objs->one_half));
  ASSERT(0x4000000000000000UL == fixedpoint_frac_part(objs->one_fourth));
  ASSERT(0xec9a1e2418UL == fixedpoint_frac_part(objs->large1));
  ASSERT(0x4d1a23c24fafUL == fixedpoint_frac_part(objs->large2));
}

void test_add(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, sum;

  lhs = fixedpoint_create_from_hex("-c7252a193ae07.7a51de9ea0538c50");
  rhs = fixedpoint_create_from_hex("d09079.1e6d601000000000");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(fixedpoint_is_neg(sum));
  ASSERT(0xc7252a0c31d8eUL == fixedpoint_whole_part(sum));
  ASSERT(0x5be47e8ea0538c50UL == fixedpoint_frac_part(sum));
}

void test_sub(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, diff;

  lhs = fixedpoint_create_from_hex("-ccf35aa3a04a3b.b105000000000000");
  rhs = fixedpoint_create_from_hex("f676e8.5800000000000000");
  diff = fixedpoint_sub(lhs, rhs);
  ASSERT(fixedpoint_is_neg(diff));
  ASSERT(0xccf35aa496c124UL == fixedpoint_whole_part(diff));
  ASSERT(0x0905000000000000UL == fixedpoint_frac_part(diff));
}

void test_is_overflow_pos(TestObjs *objs) {
  Fixedpoint sum;

  sum = fixedpoint_add(objs->max, objs->one);
  ASSERT(fixedpoint_is_overflow_pos(sum));

  sum = fixedpoint_add(objs->one, objs->max);
  ASSERT(fixedpoint_is_overflow_pos(sum));

  Fixedpoint negative_one = fixedpoint_negate(objs->one);

  sum = fixedpoint_sub(objs->max, negative_one);
  ASSERT(fixedpoint_is_overflow_pos(sum));

  Fixedpoint lhs, rhs;
  lhs = fixedpoint_create_from_hex("FFFFFFFFFFFFFFFF.b105");
  rhs = fixedpoint_create_from_hex("FFFFFFFF.58");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(fixedpoint_is_overflow_pos(sum));
}

void test_is_err(TestObjs *objs) {
  (void) objs;

  // too many characters
  Fixedpoint err1 = fixedpoint_create_from_hex("88888888888888889.6666666666666666");
  ASSERT(fixedpoint_is_err(err1));

  // too many characters
  Fixedpoint err2 = fixedpoint_create_from_hex("6666666666666666.88888888888888889");
  ASSERT(fixedpoint_is_err(err2));

  // this one is actually fine
  Fixedpoint err3 = fixedpoint_create_from_hex("-6666666666666666.8888888888888888");
  ASSERT(fixedpoint_is_valid(err3));
  ASSERT(!fixedpoint_is_err(err3));

  // whole part is too large
  Fixedpoint err4 = fixedpoint_create_from_hex("88888888888888889");
  ASSERT(fixedpoint_is_err(err4));

  // fractional part is too large
  Fixedpoint err5 = fixedpoint_create_from_hex("7.88888888888888889");
  ASSERT(fixedpoint_is_err(err5));

  // invalid hex digits in whole part
  Fixedpoint err6 = fixedpoint_create_from_hex("123xabc.4");
  ASSERT(fixedpoint_is_err(err6));

  // invalid hex digits in fractional part
  Fixedpoint err7 = fixedpoint_create_from_hex("7.0?4");
  ASSERT(fixedpoint_is_err(err7));
}


//OUR TESTS
void test_fixedpoint_create(TestObjs *objs) {
  (void) objs;

  Fixedpoint val1 = fixedpoint_create(7);
  ASSERT(fixedpoint_whole_part(val1) == 7);
  ASSERT(fixedpoint_frac_part(val1) == 0);

  //Can create max value for whole part
  Fixedpoint val2 = fixedpoint_create(0xFFFFFFFFFFFFFFFFUL);
  ASSERT(fixedpoint_whole_part(val2) == 0xFFFFFFFFFFFFFFFFUL);
  ASSERT(fixedpoint_frac_part(val2) == 0);

  //Can create 0 value for whole part
  Fixedpoint val3 = fixedpoint_create(0);
  ASSERT(fixedpoint_whole_part(val3) == 0);
  ASSERT(fixedpoint_frac_part(val3) == 0);
}

void test_fixedpoint_create2(TestObjs *objs) {
  (void) objs;
  
  Fixedpoint val1 = fixedpoint_create2(7, 2);
  ASSERT(fixedpoint_whole_part(val1) == 7);
  ASSERT(fixedpoint_frac_part(val1) == 2);

  //whole part zero
  Fixedpoint val2 = fixedpoint_create2(0, 2);
  ASSERT(fixedpoint_whole_part(val2) == 0);
  ASSERT(fixedpoint_frac_part(val2) == 2);

  //whole part max value
  Fixedpoint val3 = fixedpoint_create2(0xFFFFFFFFFFFFFFFFUL, 2);
  ASSERT(fixedpoint_whole_part(val3) == 0xFFFFFFFFFFFFFFFFUL);
  ASSERT(fixedpoint_frac_part(val3) == 2);

  //both parts zero
  Fixedpoint val4 = fixedpoint_create2(0, 0);
  ASSERT(fixedpoint_whole_part(val4) == 0);
  ASSERT(fixedpoint_frac_part(val4) == 0);

  //frac part zero
  Fixedpoint val5 = fixedpoint_create2(7, 0);
  ASSERT(fixedpoint_whole_part(val5) == 7);
  ASSERT(fixedpoint_frac_part(val5) == 0);

  //both parts max value
  Fixedpoint val6 = fixedpoint_create2(0xFFFFFFFFFFFFFFFFUL, 0xFFFFFFFFFFFFFFFFUL);
  ASSERT(fixedpoint_whole_part(val6) == 0xFFFFFFFFFFFFFFFFUL);
  ASSERT(fixedpoint_frac_part(val6) == 0xFFFFFFFFFFFFFFFFUL);
}

void test_create_from_hex_special_cases(TestObjs *objs) {
  (void) objs;

  //special cases for 0
  Fixedpoint val1 = fixedpoint_create_from_hex("0.0");
  ASSERT(fixedpoint_is_valid(val1));
  ASSERT(0x0UL == fixedpoint_whole_part(val1));
  ASSERT(0x0UL == fixedpoint_frac_part(val1));

  Fixedpoint val2 = fixedpoint_create_from_hex("0.");
  ASSERT(fixedpoint_is_valid(val2));
  ASSERT(0x0UL == fixedpoint_whole_part(val2));
  ASSERT(0x0UL == fixedpoint_frac_part(val2));

  Fixedpoint val3 = fixedpoint_create_from_hex("-0.0");
  ASSERT(fixedpoint_is_valid(val3));
  ASSERT(0x0UL == fixedpoint_whole_part(val3));
  ASSERT(0x0UL == fixedpoint_frac_part(val3));

  Fixedpoint val4 = fixedpoint_create_from_hex("-.0");
  ASSERT(fixedpoint_is_valid(val4));
  ASSERT(0x0UL == fixedpoint_whole_part(val4));
  ASSERT(0x0UL == fixedpoint_frac_part(val4));

  Fixedpoint val5 = fixedpoint_create_from_hex("0.0");
  ASSERT(fixedpoint_is_valid(val5));
  ASSERT(0x0UL == fixedpoint_whole_part(val5));
  ASSERT(0x0UL == fixedpoint_frac_part(val5));

  //Can handle upper case as well
  Fixedpoint val6 = fixedpoint_create_from_hex("A.A");
  ASSERT(fixedpoint_is_valid(val6));
  ASSERT(0xAUL == fixedpoint_whole_part(val6));
  ASSERT(0xA000000000000000UL == fixedpoint_frac_part(val6));

  //Can handle upper case as well
  Fixedpoint val7 = fixedpoint_create_from_hex("ABCDEF.ABCDEF");
  ASSERT(fixedpoint_is_valid(val7));
  ASSERT(0xABCDEFUL == fixedpoint_whole_part(val7));
  ASSERT(0xABCDEF0000000000UL == fixedpoint_frac_part(val7));

  Fixedpoint val8 = fixedpoint_create_from_hex("-.ABCDEF");
  ASSERT(fixedpoint_is_valid(val8));
  ASSERT(0x0UL == fixedpoint_whole_part(val8));
  ASSERT(0xABCDEF0000000000UL == fixedpoint_frac_part(val8));
}

void test_create_from_hex_leading_and_trailing_zeros(TestObjs *objs) {
  (void) objs;

  //Leading and trailing zeros in fractional part
  Fixedpoint val8 = fixedpoint_create_from_hex(".0990");
  ASSERT(fixedpoint_is_valid(val8));
  ASSERT(0x0UL == fixedpoint_whole_part(val8));
  ASSERT(0x0990000000000000UL == fixedpoint_frac_part(val8));

  //Leading and trailing zeros in whole part
  Fixedpoint val9 = fixedpoint_create_from_hex("09234.");
  ASSERT(fixedpoint_is_valid(val9));
  ASSERT(0x9234UL == fixedpoint_whole_part(val9));
  ASSERT(0x0UL == fixedpoint_frac_part(val9));
}

void test_add_fractions_carry_over(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, sum;

  lhs = fixedpoint_create_from_hex("0.ffff000000000000");
  rhs = fixedpoint_create_from_hex("0.ffff000000000000");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(1 == fixedpoint_whole_part(sum));
  ASSERT(0xFFFE000000000000UL == fixedpoint_frac_part(sum));
}

void test_add_with_second_value_negative(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, sum;

  lhs = fixedpoint_create_from_hex("d7da66a1cd2297b.a050000000000000");
  rhs = fixedpoint_create_from_hex("-e2fed30121a5.72e0000000000000");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(!fixedpoint_is_neg(sum));
  ASSERT(0xd7cc36b49d107d6UL == fixedpoint_whole_part(sum));
  ASSERT(0x2d70000000000000UL == fixedpoint_frac_part(sum));
}

void test_add_with_both_values_positive(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, sum;

  lhs = fixedpoint_create_from_hex("124867e1da6.f130000000000000");
  rhs = fixedpoint_create_from_hex("ba40b4aa.281d05542a000000");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(!fixedpoint_is_neg(sum));
  ASSERT(0x12540bed251UL == fixedpoint_whole_part(sum));
  ASSERT(0x194d05542a000000UL == fixedpoint_frac_part(sum));
}

void test_add_with_both_values_negative(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, sum;

  lhs = fixedpoint_create_from_hex("-b764aa2d4.56a0000000000000");
  rhs = fixedpoint_create_from_hex("-61a4f.caf3731700000000");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(fixedpoint_is_neg(sum));
  ASSERT(0xb7650bd24UL == fixedpoint_whole_part(sum));
  ASSERT(0x2193731700000000UL == fixedpoint_frac_part(sum));
}

void test_add_frac_part_causes_pos_overflow_in_whole_part(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, sum;

  lhs = fixedpoint_create_from_hex("FFFFFFFFFFFFFFFF.8000000000000000");
  rhs = fixedpoint_create_from_hex("0.8000000000000000");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(fixedpoint_is_overflow_pos(sum));
}

void test_add_frac_part_causes_neg_overflow_in_whole_part(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, sum;

  lhs = fixedpoint_create_from_hex("-FFFFFFFFFFFFFFFF.8000000000000000");
  rhs = fixedpoint_create_from_hex("-0.8000000000000000");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(fixedpoint_is_overflow_neg(sum));
}

void test_add_with_opposite_signs_causes_carry(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, sum;

  lhs = fixedpoint_create_from_hex("79b625c0.8a51a890d0000000");
  rhs = fixedpoint_create_from_hex("-1e10.d000000000000000");
  sum = fixedpoint_add(lhs, rhs);
  ASSERT(!fixedpoint_is_neg(sum));
  ASSERT(0x79b607afUL == fixedpoint_whole_part(sum));
  ASSERT(0xba51a890d0000000UL == fixedpoint_frac_part(sum));
}

void test_sub_with_two_positive_values(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, diff;

  lhs = fixedpoint_create_from_hex("5f.4360086000000000");
  rhs = fixedpoint_create_from_hex("8e338ab0e6598d.e9a3d54020000000");
  diff = fixedpoint_sub(lhs, rhs);
  ASSERT(fixedpoint_is_neg(diff));
  ASSERT(0x8e338ab0e6592eUL == fixedpoint_whole_part(diff));
  ASSERT(0xa643cce020000000UL == fixedpoint_frac_part(diff));
}

void test_sub_with_two_negative_values(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, diff;

  lhs = fixedpoint_create_from_hex("-815645984d1068a.8200000000000000");
  rhs = fixedpoint_create_from_hex("-fbd6a.2f7ee2c0ccb4e000");
  diff = fixedpoint_sub(lhs, rhs);
  ASSERT(fixedpoint_is_neg(diff));
  ASSERT(0x815645984c14920UL == fixedpoint_whole_part(diff));
  ASSERT(0x52811d3f334b2000UL == fixedpoint_frac_part(diff));
}

void test_sub_with_opposite_signs_neg_first(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, diff;

  lhs = fixedpoint_create_from_hex("-a9345bbd9e30.6d8d475a89000000");
  rhs = fixedpoint_create_from_hex("912205c68.3c482e617c4030e0");
  diff = fixedpoint_sub(lhs, rhs);
  ASSERT(fixedpoint_is_neg(diff));
  ASSERT(0xa93d6dddfa98UL == fixedpoint_whole_part(diff));
  ASSERT(0xa9d575bc054030e0UL == fixedpoint_frac_part(diff));
}

void test_sub_with_opposite_signs_pos_first(TestObjs *objs) {
  (void) objs;

  Fixedpoint lhs, rhs, diff;

  lhs = fixedpoint_create_from_hex("b.c000000000000000");
  rhs = fixedpoint_create_from_hex("-ecb31c7c737.c1011ae200000000");
  diff = fixedpoint_sub(lhs, rhs);
  ASSERT(!fixedpoint_is_neg(diff));
  ASSERT(0xecb31c7c743UL == fixedpoint_whole_part(diff));
  ASSERT(0x81011ae200000000UL == fixedpoint_frac_part(diff));
}

void test_fixedpoint_negate(TestObjs *objs) {
  (void) objs;

  //negatinga postive
  Fixedpoint val1 = fixedpoint_create_from_hex("5f.4360086000000000");
  val1 = fixedpoint_negate(val1);
  ASSERT(fixedpoint_is_neg(val1));

  //negating a negative
  Fixedpoint val2 = fixedpoint_create_from_hex("-af.2460086000000000");
  val2 = fixedpoint_negate(val2);
  ASSERT(!fixedpoint_is_neg(val2));

  //negating zero tested in test_negate
}

void test_fixedpoint_halve(TestObjs *objs) {
  (void) objs;

  Fixedpoint res;

  res = fixedpoint_create_from_hex("8AB.0000000000000000");
  res  = fixedpoint_halve(res);
  ASSERT(res.whole_part == 1109);
  ASSERT(res.frac_part == 0x8000000000000000UL);

  //when whole part 'overflows into' fractional part
  Fixedpoint res1 = fixedpoint_create_from_hex("1.0");
  res1  = fixedpoint_halve(res1);
  ASSERT(res1.whole_part == 0);
  ASSERT(res1.frac_part == 0x8000000000000000UL);

  //halve 0
  Fixedpoint res2 = fixedpoint_create_from_hex("0.0");
  res2  = fixedpoint_halve(res2);
  ASSERT(res2.whole_part == 0);
  ASSERT(res2.frac_part == 0);
}

void test_fixedpoint_halve_negative_value(TestObjs *objs) {
  (void) objs;

  Fixedpoint res;

  res = fixedpoint_create_from_hex("-8AB.0000000000000000");
  res  = fixedpoint_halve(res);
  ASSERT(fixedpoint_is_neg(res));
  ASSERT(res.whole_part == 1109);
  ASSERT(res.frac_part == 0x8000000000000000UL);
}

void test_fixedpoint_halve_causes_pos_underflow(TestObjs *objs) {
  (void) objs;

  Fixedpoint res;

  res = fixedpoint_create_from_hex("8AB.0000000000000001");
  res  = fixedpoint_halve(res);
  ASSERT(fixedpoint_is_underflow_pos(res));
}

void test_fixedpoint_halve_causes_neg_underflow(TestObjs *objs) {
  (void) objs;

  Fixedpoint res;

  res = fixedpoint_create_from_hex("-8AB.0000000000000001");
  res  = fixedpoint_halve(res);
  ASSERT(fixedpoint_is_underflow_neg(res));
}

void test_fixedpoint_double(TestObjs *objs) {
  (void) objs;

  Fixedpoint res = fixedpoint_create_from_hex("8aba.2000000000000000");
  res = fixedpoint_double(res);
  ASSERT(res.whole_part == 71028);
  ASSERT(res.frac_part == 0x4000000000000000UL);

  //frac into whole_part
  Fixedpoint res1 = fixedpoint_create_from_hex("0.8000000000000000");
  res1 = fixedpoint_double(res1);
  ASSERT(res1.whole_part == 1);
  ASSERT(res1.frac_part == 0x0000000000000000UL);

  //frac into whole_part
  Fixedpoint res2 = fixedpoint_create_from_hex("0.0");
  res2 = fixedpoint_double(res2);
  ASSERT(res2.whole_part == 0);
  ASSERT(res2.frac_part == 0);
}

void test_fixedpoint_double_negative_value(TestObjs *objs) {
  (void) objs;

  Fixedpoint res;

  res = fixedpoint_create_from_hex("-8aba.2000000000000000");
  res  = fixedpoint_halve(res);
  ASSERT(fixedpoint_is_neg(res));
  ASSERT(res.whole_part == 17757);
  ASSERT(res.frac_part == 0x1000000000000000UL);
}

void test_fixedpoint_double_causes_overflow_pos(TestObjs *objs) {
  (void) objs;

  Fixedpoint res;

  res = fixedpoint_create_from_hex("FFFFFFFFFFFFFFFF.2000000000000000");
  res  = fixedpoint_double(res);
  ASSERT(fixedpoint_is_overflow_pos(res));
}

void test_fixedpoint_double_causes_overflow_neg(TestObjs *objs) {
  (void) objs;

  Fixedpoint res;

  res = fixedpoint_create_from_hex("-FFFFFFFFFFFFFFFF.2000000000000000");
  res  = fixedpoint_double(res);
  ASSERT(fixedpoint_is_overflow_neg(res));
}

void test_fixedpoint_compare_pos_vals(TestObjs *objs) {
  (void) objs;
  //compare integers
  Fixedpoint a = fixedpoint_create_from_hex("bc4");
  Fixedpoint b = fixedpoint_create_from_hex("a76");
  ASSERT(fixedpoint_compare(a, b) == 1);
  ASSERT(fixedpoint_compare(b, a) == -1);

  Fixedpoint c = fixedpoint_create_from_hex("bc768999");
  Fixedpoint d = fixedpoint_create_from_hex("bc768999");
  ASSERT(fixedpoint_compare(c, d) == 0);
  ASSERT(fixedpoint_compare(d, c) == 0);

  //compare vals with non-zero fractions
  Fixedpoint e = fixedpoint_create_from_hex("a.8980000000000000");
  Fixedpoint f = fixedpoint_create_from_hex("a.4970000000000000");
  ASSERT(fixedpoint_compare(e, f) == 1);
  ASSERT(fixedpoint_compare(f, e) == -1);

  Fixedpoint g = fixedpoint_create_from_hex("aaa777.8980000000000000");
  Fixedpoint h = fixedpoint_create_from_hex("aaa777.8980000000000000");
  ASSERT(fixedpoint_compare(g, h) == 0);
  ASSERT(fixedpoint_compare(h, g) == 0);
}

void test_fixedpoint_compare_neg_vals(TestObjs *objs) {
  (void) objs;
  //compare integers
  Fixedpoint a = fixedpoint_create_from_hex("-2c4");
  Fixedpoint b = fixedpoint_create_from_hex("-a76");
  ASSERT(fixedpoint_compare(a, b) == 1);
  ASSERT(fixedpoint_compare(b, a) == -1);

  Fixedpoint c = fixedpoint_create_from_hex("-bc768999");
  Fixedpoint d = fixedpoint_create_from_hex("-bc768999");
  ASSERT(fixedpoint_compare(c, d) == 0);
  ASSERT(fixedpoint_compare(d, c) == 0);

  //compare vals with non-zero fractions
  Fixedpoint e = fixedpoint_create_from_hex("-a.4980000000000000");
  Fixedpoint f = fixedpoint_create_from_hex("-a.9970000000000000");
  ASSERT(fixedpoint_compare(e, f) == 1);
  ASSERT(fixedpoint_compare(f, e) == -1);

  Fixedpoint g = fixedpoint_create_from_hex("-c78777.8980000000000000");
  Fixedpoint h = fixedpoint_create_from_hex("-c78777.8980000000000000");
  ASSERT(fixedpoint_compare(g, h) == 0);
  ASSERT(fixedpoint_compare(h, g) == 0);
}

void test_fixedpoint_compare_opposite_signs(TestObjs *objs) {
  (void) objs;
  //compare integers
  Fixedpoint a = fixedpoint_create_from_hex("2c765");
  Fixedpoint b = fixedpoint_create_from_hex("-a76");
  ASSERT(fixedpoint_compare(a, b) == 1);
  ASSERT(fixedpoint_compare(b, a) == -1);

  Fixedpoint c = fixedpoint_create_from_hex("bc768999");
  Fixedpoint d = fixedpoint_create_from_hex("-bc768999");
  ASSERT(fixedpoint_compare(c, d) != 0);
  ASSERT(fixedpoint_compare(d, c) != 0);

  //compare vals with non-zero fractions
  Fixedpoint e = fixedpoint_create_from_hex("a.4980000000000000");
  Fixedpoint f = fixedpoint_create_from_hex("-a.9970000000000000");
  ASSERT(fixedpoint_compare(e, f) == 1);
  ASSERT(fixedpoint_compare(f, e) == -1);

  Fixedpoint g = fixedpoint_create_from_hex("c78777.8980000000000000");
  Fixedpoint h = fixedpoint_create_from_hex("-c78777.8980000000000000");
  ASSERT(fixedpoint_compare(g, h) != 0);
  ASSERT(fixedpoint_compare(h, g) != 0);
}

void test_fixedpoint_is_zero(TestObjs *objs) {
  (void) objs;
  Fixedpoint val1 = fixedpoint_create(0);
  ASSERT(fixedpoint_is_zero(val1));
  Fixedpoint val2 = fixedpoint_create2(0, 0);
  ASSERT(fixedpoint_is_zero(val2));
}

void test_fixedpoint_is_err(TestObjs *objs) {
  (void) objs;
  //whole too long
  Fixedpoint val1 = fixedpoint_create_from_hex("aaaaaaaaaaaaaaaaa");
  ASSERT(fixedpoint_is_err(val1));
  //frac too long
  Fixedpoint val2 = fixedpoint_create_from_hex("0.aaaaaaaaaaaaaaaaa");
  ASSERT(fixedpoint_is_err(val2));
  //invalid characters in whole
  Fixedpoint val3 = fixedpoint_create_from_hex("aaUaaaapaaaaoaaaa.");
  ASSERT(fixedpoint_is_err(val3));
  //invalid characters in frac
  Fixedpoint val4 = fixedpoint_create_from_hex("0.aaUaaaapaaaaoaaaa");
  ASSERT(fixedpoint_is_err(val4));
}

void tag_test_is_neg(TestObjs *objs) {
  (void) objs;
  Fixedpoint res;
  res.tag = 2; 
  ASSERT(fixedpoint_is_neg(res));
}

void tag_test_is_overflow_neg(TestObjs *objs) {
  (void) objs;
  Fixedpoint res;
  res.tag = 5; 
  ASSERT(fixedpoint_is_overflow_neg(res));
}

void tag_test_is_overflow_pos(TestObjs *objs) {
  (void) objs;
  Fixedpoint res;
  res.tag = 4; 
  ASSERT(fixedpoint_is_overflow_pos(res));
}

void tag_test_is_underflow_neg(TestObjs *objs) {
  (void) objs;
  Fixedpoint res;
  res.tag = 7; 
  ASSERT(fixedpoint_is_underflow_neg(res));
}

void tag_test_is_underflow_pos(TestObjs *objs) {
  (void) objs;
  Fixedpoint res;
  res.tag = 6;
  ASSERT(fixedpoint_is_underflow_pos(res));
}

void tag_test_is_valid(TestObjs *objs) {
  (void) objs;
  Fixedpoint res;
  res.tag = 1;
  ASSERT(fixedpoint_is_valid(res));
  res.tag = 2;
  ASSERT(fixedpoint_is_valid(res));
}

void test_format_as_hex_edges_cases(TestObjs *objs) {

  (void) objs;
  
  char *s;
  Fixedpoint val1 = fixedpoint_create2(0x0UL, 0x0UL);
  val1.tag = 1;
  s = fixedpoint_format_as_hex(val1);
  ASSERT(0 == strcmp(s, "0"));
  free(s);

  //if the value is zero no negative sign is included
  Fixedpoint val2 = fixedpoint_create2(0x0UL, 0x0UL);
  val2.tag = 2;
  s = fixedpoint_format_as_hex(val2);
  ASSERT(0 == strcmp(s, "0"));
  free(s);
}

void test_fixedpoint_format_as_hex_positives(TestObjs *objs) {
  
  (void) objs;
  
  char *s;
  Fixedpoint val1 = fixedpoint_create2(0x0UL, 0x8000000000000000UL);
  s = fixedpoint_format_as_hex(val1);
  ASSERT(0 == strcmp(s, "0.8"));
  free(s);

  Fixedpoint val2 = fixedpoint_create2(0x1UL, 0x8000000000000000UL);
  s = fixedpoint_format_as_hex(val2);
  ASSERT(0 == strcmp(s, "1.8"));
  free(s);

  //integer value does not display fractional part
  Fixedpoint val3 = fixedpoint_create2(0x1234UL, 0x0000000000000000UL);
  s = fixedpoint_format_as_hex(val3);
  ASSERT(0 == strcmp(s, "1234"));
  free(s);

  //all hex characters used
  Fixedpoint val4 = fixedpoint_create2(0x1UL, 0xabcdef0123456789UL);
  s = fixedpoint_format_as_hex(val4);
  ASSERT(0 == strcmp(s, "1.abcdef0123456789"));
  free(s);
}

void test_fixedpoint_format_as_hex_negatives(TestObjs *objs) {
  
  (void) objs;
  
  char *s;
  Fixedpoint val1 = fixedpoint_create2(0x0UL, 0x8000000000000000UL);
  val1.tag = 2;
  s = fixedpoint_format_as_hex(val1);
  ASSERT(0 == strcmp(s, "-0.8"));
  free(s);

  Fixedpoint val2 = fixedpoint_create2(0x1UL, 0x8000000000000000UL);
  val2.tag = 2;
  s = fixedpoint_format_as_hex(val2);
  ASSERT(0 == strcmp(s, "-1.8"));
  free(s);

  //integer value does not display fractional part
  Fixedpoint val3 = fixedpoint_create2(0x1234UL, 0x0000000000000000UL);
  val3.tag = 2;
  s = fixedpoint_format_as_hex(val3);
  ASSERT(0 == strcmp(s, "-1234"));
  free(s);

  //all hex characters used
  Fixedpoint val4 = fixedpoint_create2(0x1UL, 0xabcdef0123456789UL);
  val4.tag = 2;
  s = fixedpoint_format_as_hex(val4);
  ASSERT(0 == strcmp(s, "-1.abcdef0123456789"));
  free(s);
}

