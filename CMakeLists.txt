cmake_minimum_required(VERSION 3.0.0)
project(Timer VERSION 0.1.0)

include(CTest)
enable_testing()

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG "v2.13.9"
)

FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG "v3.2.1"
)

IF (WIN32)
    set(wxBUILD_SHARED OFF)
ENDIF()


FetchContent_MakeAvailable(Catch2 wxWidgets)

# Get all src files
file(GLOB_RECURSE TIMER_SRC CONFIGURE_DEPENDS src/*.cpp)

# Make Test src without main
set(TEST_SRC ${TIMER_SRC})
list(REMOVE_ITEM TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

include_directories(include)


IF (WIN32)
    add_executable(Timer WIN32 ${TIMER_SRC})
    target_link_libraries(Timer wx::net wx::core wx::base)
    #target_link_libraries(Timer ${wxWidgets_LIBRARIES})

    add_executable(tests test/test.cpp ${TEST_SRC})
    target_link_libraries(tests Catch2::Catch2 wx::net wx::core wx::base)
ELSE()
    add_executable(Timer ${TIMER_SRC})
    target_link_libraries(Timer wx::net wx::core wx::base)
    #target_link_libraries(Timer ${wxWidgets_LIBRARIES})

    add_executable(tests test/test.cpp ${TEST_SRC})
    target_link_libraries(tests Catch2::Catch2 wx::net wx::core wx::base)
ENDIF()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
