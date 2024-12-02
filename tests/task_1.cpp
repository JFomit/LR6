#include "tasks/task_1.h"
#include "common/string.h"
#include "gtest/gtest.h"

TEST(task_1, simple1) {
  lr6::task1::Task1 t1;
  auto result = t1.FindEven("0000 10 01010 00");
  ASSERT_STREQ(result.AsCString(), "0000 \n10 \n00\n");
}

TEST(task_1, simple2) {
  lr6::task1::Task1 t1;
  auto result = t1.FindEven("000");
  ASSERT_STREQ(result.AsCString(), "");
}

TEST(task_1, simple3) {
  lr6::task1::Task1 t1;
  auto result = t1.FindEven("10");
  ASSERT_STREQ(result.AsCString(), "10\n");
}

TEST(task_1, simple4) {
  lr6::task1::Task1 t1;
  auto result = t1.FindEven("000 10 01010 00");
  ASSERT_STREQ(result.AsCString(), "10 \n00\n");
}

TEST(task_1, simple5) {
  lr6::task1::Task1 t1;
  auto result = t1.FindEven("000000000000000000000000000000000000");
  ASSERT_STREQ(result.AsCString(), "000000000000000000000000000000000000\n");
}

TEST(task_1, empty) {
  lr6::task1::Task1 t1;
  auto result = t1.FindEven("");
  ASSERT_STREQ(result.AsCString(), "");
}

TEST(task_1, quirk) {
  lr6::task1::Task1 t1;
  auto result = t1.FindEven("fhu hh");
  ASSERT_STREQ(result.AsCString(), "hh\n");
}

TEST(strings, append) {
  lr6::String str;
  str.Append(
      u8"支毛點空有五紅里幸錯松片？朋片今聽常什綠天父跳已雪造借工三尼、八乾坡經"
      u8"唱泉！來長食、戶三固手身亭媽都高牙許語就松斗看木面，錯竹足兄親歌經空");
  str.Append(u8"من قبل اغلب برامج التصميم مث");
  str.Append("Железная дорога");

  ASSERT_STREQ(
      str.AsCString(),
      "支毛點空有五紅里幸錯松片？朋片今聽常什綠天父跳已雪造借工三尼、八乾坡經唱"
      "泉！來長食、戶三固手身亭媽都高牙許語就松斗看木面，錯竹足兄親歌經空"
      "من قبل اغلب برامج التصميم مث"
      "Железная дорога");
}

TEST(strings, append2) {
  lr6::String str = u8"🎲☘︎✧˖📷fhjsh";
  str.Append("АБА");
  ASSERT_STREQ(str.AsCString(), "🎲☘︎✧˖📷fhjshАБА");
}

TEST(strings, growth) {
  lr6::String str = lr6::String(2UL);
  str.Append(u8"аоыаршгыпауцпагуцпашуциауциацуагуршг");
  ASSERT_STREQ(str.AsCString(), "аоыаршгыпауцпагуцпашуциауциацуагуршг");
}