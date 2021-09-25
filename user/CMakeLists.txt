set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB QRC_FILES "${QRC_DIR}/*.qrc")

add_executable(app
        main.cpp
        ../business/dictionary.h
        ../business/ranked_words.h
        word_rank_model.h
        word_rank_model.cpp
        hist_thread_manager.cpp
        hist_thread_manager.h
        "${CMAKE_CURRENT_SOURCE_DIR}/main.qrc"
        )

find_package(Qt5 COMPONENTS Gui Qml Quick QuickControls2 REQUIRED)
target_link_libraries(app
        PRIVATE
        Qt5::Gui
        Qt5::Qml
        Qt5::Quick
        )
if(NOT ANDROID_NDK)
    target_link_libraries(app PRIVATE pthread)
endif()
target_include_directories(app
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../business
        )
