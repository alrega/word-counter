#pragma once

#include <string>
#include <list>
#include <set>
#include <vector>
#include <map>
#include <cassert>

/**
 * @brief Manages the list of size N of words with the higest rank
 * @details Class is not thread safe
 */
template<size_t N>
class TopRankedWords {
public:
    /**
     * @brief Attempts to add the word with its current rank
     * @details Word may not be aded if it doesn't meet top N level
     */
    void add(std::string word, size_t rank) {
        if (rank < minRank && rankedWords.size() == N)
            return;

        // Attempt to find the word in the collection and erase the old data
        for (auto itPairs = rankedWords.begin(); itPairs != rankedWords.end(); ++itPairs) {
            if (itPairs->second == word) {
                rankedWords.erase(itPairs);
                break;
            }
        }

        rankedWords.emplace(rank, word);
        cutExtra();
    }

    /**
     * @brief getTop
     * @details returns std::list<std::pair<std::string, size_t>> top N
     */
    auto getTop() {
        std::list<std::pair<std::string, size_t>> top;

        auto it = rankedWords.rbegin();
        for (size_t i = 0; i < N && it != rankedWords.rend(); i++) {
            top.emplace_front(it->second, it->first);
            ++it;
        }

        return top;
    }

private:
    void cutExtra() {
        std::set<size_t> ranks;
        for (const auto &it : rankedWords) {
            ranks.template emplace(it.first);
        }
        while (ranks.size() > N) {
            auto level = *ranks.begin();
            rankedWords.erase(level);
            ranks.erase(level);
        }
        minRank = rankedWords.begin()->first;
    }

private:
    std::multimap<size_t, std::string> rankedWords;
    size_t minRank{};
};

