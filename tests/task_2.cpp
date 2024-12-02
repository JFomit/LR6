#include "common/string.h"
#include "gtest/gtest.h"

TEST(task2, insert_begin) {
  lr6::String str = u8", world!";
  str.Insert(u8"Hello", 0);
  ASSERT_STREQ(str.AsCString(), "Hello, world!");
}

TEST(task2, insert_end) {
  lr6::String str = u8"Привет, ";
  str.Insert(u8"МИР!", 8);
  ASSERT_STREQ(str.AsCString(), "Привет, МИР!");
}

TEST(task2, insert) {
  lr6::String str = u8"木掃道";
  str.Insert(u8"МИР!", 2);
  ASSERT_STREQ(str.AsCString(), "木掃МИР!道");
}

TEST(task2, insert_empty) {
  lr6::String str = u8"АБРАКАДАБРА";
  str.Insert(u8"", 4);
  ASSERT_STREQ(str.AsCString(), "АБРАКАДАБРА");
}

TEST(task2, very_long) {
  lr6::String str = u8"F";
  str.Insert(u8"Some chinese chars for u: 實詞來邊背乙燈中卜麻拉", 0);
  ASSERT_STREQ(str.AsCString(),
               "Some chinese chars for u: 實詞來邊背乙燈中卜麻拉F");
}

TEST(task2, different_sizes) {
  lr6::String str =
      u8"Lorem (ένας) ipsum dolor sit amet, consectetur adipiscing κοινά "
      u8"παραδεκτό "
      u8"ότι elit, sed do";
  str.Insert(u8"यह एक लंबा स्थापित तथ्य", 9);
  ASSERT_STREQ(str.AsCString(),
               "Lorem (ένयह एक लंबा स्थापित तथ्यας) ipsum dolor sit amet, "
               "consectetur adipiscing κοινά "
               "παραδεκτό "
               "ότι elit, sed do");
}

TEST(task2, outofbounds) {
  lr6::String str = u8"Lorem ipsum dolor sit amet";
  ASSERT_FALSE(str.Insert(
      u8"Lorem 😂😂 ipsum 🕵️‍♂️dolor sit✍️ amet, "
      u8"consectetur "
      u8"adipiscing😇😇🤙 "
      u8"elit, sed do eiusmod🥰 tempor 😤😤🏳️‍🌈incididunt ut "
      u8"👏labore "
      u8"👏et👏 dolore 👏magna👏 aliqua. Ut enim ad minim "
      u8"🐵✊🏿veniam,❤️😤😫😩💦💦 quis nostrud 👿🤮exercitation ullamco "
      u8"🧠👮🏿‍♀️🅱️laboris nisi ut aliquip❗️ ex ea "
      u8"commodo "
      u8"consequat. "
      u8"💯Duis "
      u8"aute💦😂😂😂 irure dolor 👳🏻‍♂️🗿in "
      u8"reprehenderit "
      u8"🤖👻👎in "
      u8"voluptate velit esse cillum dolore 🙏🙏eu fugiat🤔 nulla pariatur. "
      u8"🙅‍♀️🙅‍♀️Excepteur sint "
      u8"occaecat🤷‍♀️🤦‍♀️ "
      u8"cupidatat💅 "
      u8"non💃 "
      u8"proident,👨‍👧 sunt🤗 in culpa😥😰😨 qui "
      u8"officia🤩🤩 "
      u8"deserunt "
      u8"mollit 🧐anim id est laborum.🤔🤔 ",
      1000));
  ASSERT_STREQ(str.AsCString(), "Lorem ipsum dolor sit amet");
}

TEST(task2, emojis) {
  lr6::String str =
      u8"Lorem 😂😂 ipsum 🕵️‍♂️dolor sit✍️ amet, "
      u8"consectetur "
      u8"adipiscing😇😇🤙 "
      u8"elit, sed do eiusmod🥰 tempor 😤😤🏳️‍🌈incididunt ut "
      u8"👏labore ";
  str.Insert(u8"👺🌽🔁🍍💒🍳🔵 🕥🐟🔳💋 🐥", 7);
  ASSERT_STREQ(
      str.AsCString(),
      "Lorem 😂👺🌽🔁🍍💒🍳🔵 🕥🐟🔳💋 🐥😂 ipsum "
      "🕵️‍♂️dolor "
      "sit✍️ "
      "amet, "
      "consectetur "
      "adipiscing😇😇🤙 "
      "elit, sed do eiusmod🥰 tempor 😤😤🏳️‍🌈incididunt ut "
      "👏labore ");
}

TEST(task2, middle_of_char) {
  lr6::String str = u8"كتابة مفهومة من قبل";
  str.Insert(u8"Я думаю, что вставлюсь после 1 байта", 1);

  ASSERT_STREQ(str.AsCString(),
               "كЯ думаю, что вставлюсь после 1 байтаتابة مفهومة من قبل");
}

TEST(task2, insert_all) {
  lr6::String str = u8"HةLएकL😇लं-)ПОвичз";
  str.Insert(u8"掃", 5);
  str.Insert(u8"掃", 16);
  ASSERT_STREQ(str.AsCString(), "HةLएक掃L😇लं-)ПОви掃чз");
}