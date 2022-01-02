cmake_minimum_required(VERSION 3.0.0)
project(splist VERSION 0.1.0 LANGUAGES CXX)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(CTest)
enable_testing()

add_subdirectory(cpp)

add_executable(Test_TreeList cpp/tests/Test_TreeList.cpp)
target_link_libraries(Test_TreeList PUBLIC splist_cpplib gtest_main)
target_include_directories(Test_TreeList PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/cpp")

add_executable(Test_TreeListIterator cpp/tests/Test_TreeListIterator.cpp)
target_link_libraries(Test_TreeListIterator PUBLIC splist_cpplib gtest_main)
target_include_directories(Test_TreeListIterator PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/cpp")

include(GoogleTest)
gtest_discover_tests(Test_TreeList)
gtest_discover_tests(Test_TreeListIterator)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
