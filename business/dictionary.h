#pragma once

#include "ranked_words.h"

#include <string>
#include <list>
#include <unordered_map>
#include <fstream>

using word_rank=std::pair<std::string, size_t>;

/**
 * @brief MImplementation function reads words from input stream and evaluates the top N frequently used words and additional data
 *
 * @details
 * Method reads the input stream word by word and adds word into the given map (key=word, value=count) to learn count.
 * Then it adds the pair of <word, count> to TopRankedWords instance which manages top ranked words.
 * Functor f(top) is called with the list of top most frequently used words; call is performed every 1024 words
 *
 * @tparam N - count of frequently used words to learn
 * @tparam F - functor f(const std::list<std::pair<std::string, size_t>> &top) to call
 * @param[in] textFile - input stream opened for reading
 * @param[in,out] wordsCounts - map that will contain full histogramm
 * @param[in,out] top - it will contain top N frequently used words
 */
template<size_t N, typename F>
void CountWords(std::istream &textFile, std::unordered_map<std::string, size_t> &wordsCounts, TopRankedWords<N> &top, F &&f) {
    size_t counter{};
    while (!textFile.eof()) {
        std::string s;
        textFile >> s;
        auto count = ++wordsCounts[s];
        top.add(std::move(s), count);
        if (!(++counter % 1024)) // call every 1024 words
        {
            if(!f(top.getTop()))
                return;
        }
    }
}


/**
 * @brief Function reads words from input stream and evaluates the top N frequently used words
 *
 * @details
 * Method creates adiitional map and calls another CountWords function
 * Functor f(top) is called with the list of top most frequently used words; call is performed every 1024 words
 *
 * @tparam N - count of frequently used words to learn
 * @tparam F - functor f(const std::list<std::pair<std::string, size_t>> &top) to call
 * @param[in] textFile - input stream opened for reading
 * @param[in,out] top - it will contain top N frequently used words
 */
template<size_t N, typename F>
std::list<std::pair<std::string, size_t>> CountWords(std::istream &textFile, F &&f) {
    std::unordered_map<std::string, size_t> wordsCounts;
    TopRankedWords<N> top;
    CountWords(textFile, wordsCounts, top, std::forward<F>(f));
    return top.getTop();
}


