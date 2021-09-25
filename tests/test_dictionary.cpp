#include "dictionary.h"
#include "ranked_words.h"

#include <string>
#include <unordered_map>
#include <gtest/gtest.h>


class TestDictionary : public ::testing::Test {
public:
    void SetUp() { /* called before every test */ }

    void TearDown() { /* called after every test */ }

protected:
    /* none yet */
};


TEST_F(TestDictionary, SingleLine) {
    std::string line{"A B C D B C A D D D D D D A A A B B"};
    std::stringstream ss;
    ss.str(line);

    std::unordered_map<std::string, size_t> wordsCounts;
    TopRankedWords<3> top3;
    CountWords<3>(ss, wordsCounts, top3, [](const auto &) { return true; });
    auto top = top3.getTop();

    ASSERT_EQ(3, top.size());

    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("B", 4ul));
    ASSERT_EQ(*it++, word_rank("A", 5ul));
    ASSERT_EQ(*it++, word_rank("D", 7ul));
}


TEST_F(TestDictionary, English) {
    std::ifstream textFile("/home/tima/prj/exams/2gis/NEWS");
    std::unordered_map<std::string, size_t> wordsCounts;
    TopRankedWords<3> top3;
    CountWords<3>(textFile, wordsCounts, top3, [](const auto &) {
//        auto it = top.rbegin();
//        auto w1 = *it++;
//        auto w2 = *it++;
//        auto w3 = *it++;
//        std::cout << w1.first << " <-> " << w1.second << "\t\t" << w2.first << " <-> " << w2.second << "\t\t"
//                  << w3.first << " <-> " << w3.second << std::endl;
         return true;
    });
    textFile.close();
    auto top = top3.getTop();

    ASSERT_EQ(3, top.size());

    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("OpenSSL", 212ul));
    ASSERT_EQ(*it++, word_rank("and", 218ul));
    ASSERT_EQ(*it++, word_rank("o", 590ul));
}

TEST_F(TestDictionary, RussianUTF8) {
    std::ifstream textFile("/home/tima/prj/exams/2gis/Russian.utf8.txt");
    std::unordered_map<std::string, size_t> wordsCounts;
    TopRankedWords<3> top3;
    CountWords<3>(textFile, wordsCounts, top3, [](const auto &) {
//        auto it = top.rbegin();
//        auto w1 = *it++;
//        auto w2 = *it++;
//        auto w3 = *it++;
//        std::cout << w1.first << " <-> " << w1.second << "\t\t" << w2.first << " <-> " << w2.second << "\t\t"
//                  << w3.first << " <-> " << w3.second << std::endl;
         return true;
    });
    textFile.close();
    auto top = top3.getTop();

    ASSERT_EQ(3, top.size());

    auto it = top.begin();
    ASSERT_EQ(*it++, word_rank("с", 16ul));
    ASSERT_EQ(*it++, word_rank("в", 20ul));
    ASSERT_EQ(*it++, word_rank("и", 36ul));
}
