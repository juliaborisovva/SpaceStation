set(target_name test_lib)

#enable_testing()

################################
# Unit Tests
################################

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

# add test cpp file
target_sources(
        ${target_name}
        PRIVATE
        test.cc
)
# link test executable against gtest & gtest_main
target_link_libraries(
        ${target_name}
        PRIVATE
        libspace
        #gtest
        gtest_main
)

# Add test
add_test( ${target_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target_name} )