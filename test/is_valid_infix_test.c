#include <check.h>
#include "../src/is_valid_infix.h"

START_TEST(WhenGivenEmptyStringReturnsTrue)
{
  bool return_value = is_valid_infix("");
  ck_assert(return_value == true);
}
END_TEST

START_TEST(WhenGivenNullReturnsFalse)
{
  bool return_value = is_valid_infix(0);
  ck_assert(return_value == false);
}
END_TEST

START_TEST(WhenGiven_1_ReturnFalse)
{
  bool return_value = is_valid_infix("1");
  ck_assert(return_value == false);
}
END_TEST

START_TEST(WhenGiven_2_ReturnFalse)
{
  bool return_value = is_valid_infix("2");
  ck_assert(return_value == false);
}
END_TEST

START_TEST(WhenGiven_3_ReturnFalse)
{
  bool return_value = is_valid_infix("3");
  ck_assert(return_value == false);
}
END_TEST

START_TEST(WhenGiven_a_ReturnTrue)
{
  bool return_value = is_valid_infix("a");
  ck_assert(return_value == true);
}
END_TEST

START_TEST(WhenGiven_a_PLUS_b_ReturnTrue)
{
  bool return_value = is_valid_infix("a+b");
  ck_assert(return_value == true);
}
END_TEST

START_TEST(WhenGiven_a_PLUS_b_PLUS_c_ReturnTrue)
{
  bool return_value = is_valid_infix("a+b+c");
  ck_assert(return_value == true);
}
END_TEST

START_TEST(WhenGiven_d_PLUS_e_PLUS_f_PLUS_g_PLUS_h_PLUS_i_ReturnTrue)
{
  bool return_value = is_valid_infix("d+e+f+g+h+i");
  ck_assert(return_value == true);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("is_valid_infix_tests");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, WhenGivenEmptyStringReturnsTrue);
    tcase_add_test(tc1_1, WhenGivenNullReturnsFalse);
    tcase_add_test(tc1_1, WhenGiven_1_ReturnFalse);
    tcase_add_test(tc1_1, WhenGiven_2_ReturnFalse);
    tcase_add_test(tc1_1, WhenGiven_3_ReturnFalse);
    tcase_add_test(tc1_1, WhenGiven_a_ReturnTrue);
    tcase_add_test(tc1_1, WhenGiven_a_PLUS_b_ReturnTrue);
    tcase_add_test(tc1_1, WhenGiven_a_PLUS_b_PLUS_c_ReturnTrue);
    tcase_add_test(tc1_1, WhenGiven_d_PLUS_e_PLUS_f_PLUS_g_PLUS_h_PLUS_i_ReturnTrue);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
