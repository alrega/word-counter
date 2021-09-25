#include "ranked_words.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <gtest/gtest.h>


class TestRankedWords : public ::testing::Test {
public:
    void SetUp() { /* called before every test */ }

    void TearDown() { /* called after every test */ }

protected:
    /* none yet */
};

using word_rank=std::pair<std::string, size_t>;

TEST_F(TestRankedWords, InstantData) {
    TopRankedWords<3> top3;

    top3.add("A", 1);
    top3.add("B", 1);
    top3.add("C", 1);
    top3.add("D", 1);
    auto top = top3.getTop();
    ASSERT_EQ(3, top.size());

    top3.add("A", 2);
    top3.add("B", 2);
    top3.add("A", 3);
    top3.add("C", 2);
    top3.add("D", 2);
    top3.add("D", 3);
    top3.add("D", 4);
    top3.add("D", 5);
    top3.add("A", 4);
    top3.add("C", 3);

    top = top3.getTop();
    ASSERT_EQ(3, top.size());
    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("C", 3ul));
    ASSERT_EQ(*it++, word_rank("A", 4ul));
    ASSERT_EQ(*it++, word_rank("D", 5ul));
}

TEST_F(TestRankedWords, ABCDEF) {
    TopRankedWords<3> top3;
    top3.add("A", 1);
    top3.add("B", 2);
    top3.add("C", 3);
    top3.add("D", 4);
    top3.add("E", 5);
    top3.add("F", 6);

    auto top = top3.getTop();

    ASSERT_EQ(3, top.size());
    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("D", 4ul));
    ASSERT_EQ(*it++, word_rank("E", 5ul));
    ASSERT_EQ(*it++, word_rank("F", 6ul));
}

TEST_F(TestRankedWords, FEDCBA) {
    TopRankedWords<3> top3;
    top3.add("F", 6);
    top3.add("E", 5);
    top3.add("D", 4);
    top3.add("C", 3);
    top3.add("B", 2);
    top3.add("A", 1);

    auto top = top3.getTop();

    ASSERT_EQ(3, top.size());
    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("D", 4ul));
    ASSERT_EQ(*it++, word_rank("E", 5ul));
    ASSERT_EQ(*it++, word_rank("F", 6ul));
}

TEST_F(TestRankedWords, AAAAAB) {
    TopRankedWords<3> top3;
    top3.add("A", 1);
    top3.add("A", 2);
    top3.add("A", 3);
    top3.add("A", 4);
    top3.add("A", 5);
    top3.add("B", 1);

    auto top = top3.getTop();

    ASSERT_EQ(2, top.size());
    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("B", 1ul));
    ASSERT_EQ(*it++, word_rank("A", 5ul));
}

TEST_F(TestRankedWords, BAAAAA) {
    TopRankedWords<3> top3;
    top3.add("B", 1);
    top3.add("A", 1);
    top3.add("A", 2);
    top3.add("A", 3);
    top3.add("A", 4);
    top3.add("A", 5);

    auto top = top3.getTop();

    ASSERT_EQ(2, top.size());
    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("B", 1ul));
    ASSERT_EQ(*it++, word_rank("A", 5ul));
}

TEST_F(TestRankedWords, ABBBBB) {
    TopRankedWords<3> top3;
    top3.add("A", 1);
    top3.add("B", 1);
    top3.add("B", 2);
    top3.add("B", 3);
    top3.add("B", 4);
    top3.add("B", 5);

    auto top = top3.getTop();

    ASSERT_EQ(2, top.size());
    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("A", 1ul));
    ASSERT_EQ(*it++, word_rank("B", 5ul));
}

