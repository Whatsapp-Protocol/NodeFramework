cmake_minimum_required(VERSION 3.5)

include_directories(../scintilla/include ./include)

FILE (GLOB header_files include/*.h)
FILE (GLOB source_files src/*.h src/*.cxx)

add_library(scintilla STATIC
    ${header_files} 
    ${source_files} 
)

