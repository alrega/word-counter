
add_executable(test_ranked_words test_ranked_words.cpp ../business/dictionary.h)
target_link_libraries(test_ranked_words PRIVATE gtest gtest_main)
target_include_directories(test_ranked_words PRIVATE ../business)

add_executable(test_dictionary test_dictionary.cpp ../business/dictionary.h)
target_link_libraries(test_dictionary PRIVATE gtest gtest_main)
target_include_directories(test_dictionary PRIVATE ../business)