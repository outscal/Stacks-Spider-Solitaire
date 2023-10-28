cmake_minimum_required(VERSION 3.22)
project(SpiderSolitaireSFML)

# Set C++ options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add SFML as a dependency
set(WARNINGS_AS_ERRORS OFF)
set(SFML_INSTALL_XCODE_TEMPLATES OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/SFML)

# Get all the C++ files
# in the sources recursively
file(GLOB_RECURSE SPIDERSOLITAIRE_SOURCES
    ${CMAKE_SOURCE_DIR}/source/*.cpp
)

# Create the project
add_executable(SpiderSolitaire ${CMAKE_SOURCE_DIR}/main.cpp ${SPIDERSOLITAIRE_SOURCES})
target_include_directories(SpiderSolitaire PRIVATE 
    ${CMAKE_SOURCE_DIR}/header/
)

# Link SFML
target_link_libraries(SpiderSolitaire PUBLIC
    sfml-window
    sfml-graphics
    sfml-audio
)

# Windows fiasco
if (WIN32)
  add_custom_command(TARGET SpiderSolitaire POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/deps/SFML/extlibs/bin/x64/openal32.dll $<TARGET_FILE_DIR:SpiderSolitaire>
  )
  add_custom_command(TARGET SpiderSolitaire POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:SpiderSolitaire>/assets
  )
  set_target_properties(SpiderSolitaire PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:SpiderSolitaire>)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SpiderSolitaire)

else()
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
message("-- Using libasan")
# Enable address sanitizer and Extra warnings
target_compile_options(SpiderSolitaire PRIVATE
    -Wall -Wextra
    -fsanitize=address
)
target_link_options(SpiderSolitaire PRIVATE -fsanitize=address)
endif()