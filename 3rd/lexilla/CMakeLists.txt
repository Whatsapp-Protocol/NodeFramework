cmake_minimum_required(VERSION 3.5)

include_directories(../scintilla/include ./include ./lexlib)

FILE (GLOB header_files include/*.h)

file(GLOB lexers lexers/*.cxx lexers/*.h lexers/*.cpp)
source_group("lexers" FILES ${lexers})

file(GLOB lexlib lexlib/*.cxx lexlib/*.h lexlib/*.cpp)
source_group("lexlib" FILES ${lexlib})



add_library(lexilla STATIC
    ${header_files} 
    ${source_files} 
    ${lexers}
    ${lexlib}
)

