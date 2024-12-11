#include "tasks/task_3.h"
#include "common/string.h"
#include "gtest/gtest.h"

using lr6::String;

TEST(task3, one_line) {
  String str = u8"abbb dhdhdh 9090990";
  lr6::task3::Task3 t3;
  t3.MagicSwap(str);
  ASSERT_STREQ(str.AsCString(), "9090990 dhdhdh abbb");
}

TEST(task3, empty) {
  String str = u8"";
  lr6::task3::Task3 t3;
  t3.MagicSwap(str);
  ASSERT_STREQ(str.AsCString(), "");
}

TEST(task3, two_line) {
  String str = u8"hello world\niii jjj kkk\npopopop";
  lr6::task3::Task3 t3;
  t3.MagicSwap(str);
  ASSERT_STREQ(str.AsCString(), "popopop\nkkk jjj iii\nworld hello");
}

TEST(task3, chinese) {
  String str = u8"杯實品要 穴 棵是寺相 會比";
  lr6::task3::Task3 t3;
  t3.MagicSwap(str);
  ASSERT_STREQ(str.AsCString(), "會比 棵是寺相 穴 杯實品要");
}

TEST(task3, arabic) {
  String str =
      u8"التقليدية\n"
      u8"الشّعبين";
  lr6::task3::Task3 t3;
  t3.MagicSwap(str);
  ASSERT_STREQ(str.AsCString(),
               "الشّعبين\n"
               "التقليدية");
}

TEST(task3, very_many_new_lines) {
  String str = u8"\n\n\n\n\n\n\n\na";
  lr6::task3::Task3 t3;
  t3.MagicSwap(str);
  ASSERT_STREQ(str.AsCString(), "a\n\n\n\n\n\n\n\n");
}