macro(cs_test target)
  set(sources ${ARGN})
  add_executable(${target} ${sources})
  add_dependencies(${target} NumericArray N4)
  format_output_name(${target} ${target})
  set_target_properties(${target} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    )
  target_include_directories(${target}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${NumericArray_SOURCE_DIR}/include
    )
  target_link_libraries(${target})
endmacro()

### Tests ####################################################################

cs_test(test_array src/test_array.cpp)
cs_test(test_meta src/test_meta.cpp)
cs_test(test_simd src/test_simd.cpp)
