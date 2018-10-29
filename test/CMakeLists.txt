 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${XTL_IMPL_SOURCE_DIR}/include)
 

# Link runTests with what we want to test and the GTest and pthread library
add_executable(tallocator testAllocator.cc)
add_executable(tistreamIt testIstreamIterator.cc)
add_executable(tostreamIt testOstreamIterator.cc)
add_executable(tbackIterator testBackInserterIterator.cc)
add_executable(tfrontIterator testFrontInserterIterator.cc)

target_link_libraries(tallocator gtest gtest_main)
target_link_libraries(tistreamIt gtest gtest_main)
target_link_libraries(tostreamIt gtest gtest_main)
target_link_libraries(tbackIterator gtest gtest_main)
target_link_libraries(tfrontIterator gtest gtest_main)
