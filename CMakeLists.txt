cmake_minimum_required(VERSION 3.12.4)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(hw3_doxygen VERSION ${PROJECT_VESRION})

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC_PATH "src/")
set(CMAKE_EXE_LINKER_FLAGS " -static")
include_directories("src/")
include_directories("include/")

add_executable(doxy ${SRC_PATH}/main.cpp)
target_link_libraries(doxy -static-libgcc -static-libstdc++)

# enable_testing()
# add_subdirectory(test)
install(TARGETS doxy RUNTIME DESTINATION bin)

# target doc
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)
    add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile)
    message(STATUS "INFO: doxygen found - target \"doc\" must be available")
else()
    message(STATUS "WARNING: doxygen not found - target \"doc\" will not be available")
endif()

#target package
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
