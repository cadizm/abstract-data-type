#include <string>

#include "ordered_symbol_table.h"

#include "gtest/gtest.h"

using std::string;
using std::vector;

class OrderedSymbolTableTest : public ::testing::Test {
 protected:
  void SetUp() override {
    st.put("09:00:00", "Chicago");
    st.put("09:00:03", "Phoenix");
    st.put("09:00:13", "Houston");
    st.put("09:00:59", "Chicago");
    st.put("09:01:10", "Houston");
    st.put("09:03:13", "Chicago");
    st.put("09:10:11", "Seattle");
    st.put("09:10:25", "Seattle");
    st.put("09:14:25", "Phoenix");
    st.put("09:19:32", "Chicago");
    st.put("09:19:46", "Chicago");
    st.put("09:21:05", "Chicago");
    st.put("09:22:43", "Seattle");
    st.put("09:22:54", "Seattle");
    st.put("09:25:52", "Chicago");
    st.put("09:35:21", "Chicago");
    st.put("09:36:14", "Seattle");
    st.put("09:37:44", "Phoenix");
  }

  OrderedSymbolTable<string, string> st;
};

TEST_F(OrderedSymbolTableTest, GetTest) {
  ASSERT_EQ(*st.get("09:00:03"), "Phoenix");
  ASSERT_EQ(st.get("JUMANJI"), nullptr);
}

TEST_F(OrderedSymbolTableTest, RemoveTest) {
  ASSERT_EQ(st.remove("09:22:43"), 1);
  ASSERT_EQ(st.remove("bad key"), 0);
}

TEST_F(OrderedSymbolTableTest, ContainsTest) {
  ASSERT_TRUE(st.contains("09:22:43"));
  ASSERT_FALSE(st.contains("bad key"));
}

TEST_F(OrderedSymbolTableTest, SizeAndEmptyTest) {
  ASSERT_EQ(st.size(), 18);

  OrderedSymbolTable<int, int> temp;
  ASSERT_TRUE(temp.isEmpty());
}

TEST_F(OrderedSymbolTableTest, MinMaxTest) {
  ASSERT_EQ(*st.min(), "09:00:00");
  ASSERT_EQ(*st.max(), "09:37:44");

  OrderedSymbolTable<int, int> temp;
  ASSERT_EQ(temp.min(), nullptr);
  ASSERT_EQ(temp.max(), nullptr);
}

TEST_F(OrderedSymbolTableTest, FloorCeilingTest) {
  ASSERT_EQ(*st.floor("09:05:00"), "09:03:13");
  ASSERT_EQ(*st.ceiling("09:30:00"), "09:35:21");
}

TEST_F(OrderedSymbolTableTest, RankSelectTest) {
  ASSERT_EQ(st.rank("08:00:00"), 0);
  ASSERT_EQ(st.rank("09:10:25"), 7);

  ASSERT_EQ(*st.select(7), "09:10:25");
  ASSERT_EQ(*st.select(0), "09:00:00");
  ASSERT_EQ(st.select(-1), nullptr);
}

TEST_F(OrderedSymbolTableTest, SizeTest) {
  ASSERT_EQ(st.size("09:15:00", "09:25:00"), 5);
  ASSERT_EQ(st.size("09:00:00", "09:37:44"), 18);
}

TEST_F(OrderedSymbolTableTest, KeysLowHighTest) {
  vector<string> keys = st.keys("09:15:00", "09:25:00");
  ASSERT_EQ(static_cast<int>(keys.size()), 5);
  ASSERT_EQ(*keys.begin(), "09:19:32");
  ASSERT_EQ(*(--keys.end()), "09:22:54");
}

TEST_F(OrderedSymbolTableTest, KeysTest) {
  vector<string> keys = st.keys();
  ASSERT_EQ(static_cast<int>(keys.size()), 18);
  ASSERT_EQ(*keys.begin(), "09:00:00");
  ASSERT_EQ(*(--keys.end()), "09:37:44");
}
