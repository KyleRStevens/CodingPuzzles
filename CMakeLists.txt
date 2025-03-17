cmake_minimum_required(VERSION 3.5.0...3.31.3)
project(CodingPuzzles VERSION 0.1.0)


###############
# BUILD STUFF #
###############

# Set up the compiler
#set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Configure Debug and Release builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")  # Add debug-specific definitions
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")  # Enable optimization for Release

# Set output directories (must be done before add_executable/add_library)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin ) # Executable
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin ) # Dynamic/shared libraries
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin ) # Static libraries
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} ) # Same but for specified configurations
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
	string( TOLOWER OUTPUTCONFIGLOWER OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_LIST_DIR}/bin/${OUTPUTCONFIGLOWER} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_LIST_DIR}/bin/${OUTPUTCONFIGLOWER} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_LIST_DIR}/bin/${OUTPUTCONFIGLOWER} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# Laxy file inclusion (not recommended for serious projects)
file(GLOB HEADER_FILES_LEETCODE_GLOB "include/LeetCode/*.h")
file(GLOB HEADER_FILES_META_GLOB "include/Meta/*.h")
file(GLOB HEADER_FILES_MYSTUFF_GLOB "include/MyStuff/*.h")
file(GLOB SOURCE_FILES_GLOB "src/Lazy/*.cpp")

# Source files to compile
set(SOURCE_FILES
    src/main.cpp
	${SOURCE_FILES_GLOB}
)

# Header files
set(HEADER_FILES
    ${HEADER_FILES_LEETCODE_GLOB}
    ${HEADER_FILES_META_GLOB}
    ${HEADER_FILES_MYSTUFF_GLOB}
)

# Group header files into different categories
source_group("LeetCode\\include" FILES ${HEADER_FILES_LEETCODE_GLOB})
source_group("MetaPuzzles\\include" FILES ${HEADER_FILES_META_GLOB})
source_group("MyStuff\\include" FILES ${HEADER_FILES_MYSTUFF_GLOB})

# Group source files into different categories
source_group("MyStuff\\src" FILES ${SOURCE_FILES_GLOB})

# Add project output target (executable or library)
add_executable(CodingPuzzles
    ${SOURCE_FILES}

    ${HEADER_FILES}
)

# Set the subsystem
set_target_properties(CodingPuzzles PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
#set_target_properties(CodingPuzzles PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

# Set the Startup Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CodingPuzzles)

# Include Directories
target_include_directories(CodingPuzzles
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/LeetCode
    ${CMAKE_CURRENT_LIST_DIR}/include/Meta
    ${CMAKE_CURRENT_LIST_DIR}/include/MyStuff
)

# Submodules
#add_subdirectory(dependencies/Example)
#target_link_libraries(CodingPuzzles PRIVATE Example)

# Third-party library directories
#link_directories(lib)

# Third-party libraries to link
target_link_libraries(CodingPuzzles
    PRIVATE
    #Example
)


#################
# INSTALL STUFF #
#################

# Set install directories (packaging for distribution)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/install)

# Install headers to the "include" subdirectory
install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
	PATTERN third.party EXCLUDE
)

# Install the library to the respective subfolder based on the configuration
install(
    TARGETS CodingPuzzles
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)


###############
# CLEAN STUFF #
###############

# Define custom targets for cleaning
#add_custom_target(CLEAN-OUTPUT
#    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_LIST_DIR}/bin"
#    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_LIST_DIR}/install"
#    COMMENT "Cleaning output folders..."
#)


# Add a dependency to ensure custom targets are executed when you clean the project (disabled as "clean" isn't actually a built in target to depend on...)
#add_dependencies(clean clean-bin)
#add_dependencies(clean clean-install)
