# The minimum version of CMake Required
cmake_minimum_required (VERSION 2.6)

# Change project name
project (ehsan_a2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# CMake will create your library, add the cpp files needed
add_library(ranger_lib STATIC rangerfusion.cpp ranger.cpp sonar.cpp laser.cpp)
# Add header files
set_target_properties(ranger_lib  PROPERTIES PUBLIC_HEADER "rangerfusioninterface.h;rangerfusion.h;rangerinterface.h;ranger.h;sonar.h;laser.h")

# CMake will create the cell library that you will need
add_library(cell STATIC cell.cpp)
# Add header files
set_target_properties(cell  PROPERTIES PUBLIC_HEADER "cell.h")

# CMake will create executable add the cpp files needed
add_executable(assignment2 main.cpp)


# Cmake will link against the libraries in final step
# Link libraries with executable
target_link_libraries(assignment2 ranger_lib cell)


set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/${PROJECT_NAME}")
install(TARGETS cell ranger_lib DESTINATION lib PUBLIC_HEADER DESTINATION include)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
