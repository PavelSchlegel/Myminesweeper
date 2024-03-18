cmake_minimum_required(VERSION 3.12)

project(Myminensweeper LANGUAGES CXX C)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    sfml
    URL https://github.com/SFML/SFML/archive/refs/tags/2.6.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_MakeAvailable(sfml)

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME}

PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS YES
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS YES
)

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-window sfml-system sfml-graphics)