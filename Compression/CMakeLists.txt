cmake_minimum_required(VERSION 3.10)

project(DNAWork)
file(GLOB source_files
            "*.h"
            "*.cpp"
            "src/*.cpp"
            "include/*.h"
    )
include_directories(./include)
add_executable(DNAWork.exe ${source_files})
