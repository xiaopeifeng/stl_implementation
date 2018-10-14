 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${XTL_IMPL_SOURCE_DIR}/include)
 

# Link runTests with what we want to test and the GTest and pthread library
add_executable(tAllocator test.cc)
target_link_libraries(tAllocator gtest gtest_main)