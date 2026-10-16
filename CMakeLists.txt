cmake_minimum_required(VERSION 3.14)
project(BlackSmithNetworkTests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Enable testing for the project
enable_testing()

# 2. Add compiler flags for Code Coverage (GCC / Clang)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# 3. Pull in GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows MSVC compatibility with gtest if needed:
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 4. Define your source library or object files (excluding main.cpp so you can test independently)
add_library(blacksmith_lib
    Action.cpp
    Network.cpp
    # Add other implementation .cpp files here (e.g., Scheduler.cpp, etc.)
)

# 5. Add your test executable
add_executable(unit_tests
    tests/test_main.cpp       # Your test cases go here
    tests/test_network.cpp    # Specific tests for Network/Actions
)

# 6. Link GTest, pthread, and your blacksmith library
target_link_libraries(unit_tests
    PRIVATE
        blacksmith_lib
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)