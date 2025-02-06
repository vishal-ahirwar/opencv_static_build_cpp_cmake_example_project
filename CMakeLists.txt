
#Auto Genrated CMake file by aura CLI
#Copyright 2023 Vishal Ahirwar. #replace with your copyright notice.
cmake_minimum_required(VERSION 3.6...3.31)
project(ADT VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops")
set(COMPANY "Vishal Ahirwar")
string(TIMESTAMP CURRENT_YEAR "%Y")
set(COPYRIGHT "Copyright(c) ${CURRENT_YEAR} ${COMPANY}.")
include_directories(src ${CMAKE_BINARY_DIR})
configure_file(ADTconfig.h.in ADTconfig.h)
#@find Warning: Do not remove this line
find_package(fmt REQUIRED)
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/external/opencv/build)
find_package(OpenCV REQUIRED)
file(GLOB SOURCES "src/*.cpp" "src/*.hpp" "src/*.hxx" "src/*.h" "src/*.cc" "src/*.cxx")
add_executable(${PROJECT_NAME} ${SOURCES})
install(TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
#@link Warning: Do not remove this line
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VENDOR ${COMPANY})
include(CPack)