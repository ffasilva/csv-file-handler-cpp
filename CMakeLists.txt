CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

project(file_handlers)

set (CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Werror=return-type -Wall -Wextra -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

INCLUDE_DIRECTORIES(include)

###############################################################
# DEFINE AND INSTALL LIBRARY AND INCLUDE FOLDER
################################################################

ADD_LIBRARY(${PROJECT_NAME} SHARED
    src/CSVHandler.cpp
    )

SET_TARGET_PROPERTIES(${PROJECT_NAME}
    PROPERTIES PUBLIC_HEADER
    include/file_handlers/CSVHandler.h
    )

INSTALL(TARGETS ${PROJECT_NAME}
# https://stackoverflow.com/questions/21592361/cmake-install-is-not-installing-libraries-on-windows
    RUNTIME DESTINATION "bin"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    PUBLIC_HEADER DESTINATION "include/file_handlers"
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

################################################################
# INSTALL HEADERS IN SUBFOLDERS
################################################################

INSTALL(DIRECTORY
    include/
    DESTINATION "include"
)

################################################################
# INSTALL SOURCE FILES (So that the debugger can find them)
################################################################

INSTALL(DIRECTORY
    src/
    DESTINATION "src/file_handlers"
)

################################################################
# ADD EXECUTABLES FOR THE EXAMPLES
################################################################
add_executable(test_save_csv
    examples/test_save_csv.cpp
    )

TARGET_LINK_LIBRARIES(test_save_csv
    ${PROJECT_NAME}
)

add_executable(test_read_csv
    examples/test_read_csv.cpp
    )

TARGET_LINK_LIBRARIES(test_read_csv
    ${PROJECT_NAME}
)
