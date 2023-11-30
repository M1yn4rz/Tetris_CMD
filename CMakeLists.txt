# CMakeList.txt: projekt CMake dla elementu Tetris_CMD, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

# Włącz przeładowywanie kodu XAML na gorąco dla kompilatorów MSVC, jeśli jest to obsługiwane.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Tetris_CMD")

# Dodaj źródło do pliku wykonywalnego tego projektu.

set(SRC 
	Core/Src/Board.cpp 
	Core/Src/Cub.cpp 
	Core/Src/Play.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${SRC})
add_executable(${PROJECT_NAME} Tetris_CMD.cpp Tetris_CMD.h)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tetris_CMD PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
