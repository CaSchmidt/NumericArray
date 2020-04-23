macro(cs_test target)
  set(sources ${ARGN})
  add_executable(${target} ${sources})
  add_dependencies(${target} NumericArray)
  format_output_name(${target} ${target})
  target_include_directories(${target}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${NumericArray_SOURCE_DIR}/include
    )
  target_link_libraries(${target})
endmacro()

### Tests ####################################################################

cs_test(test_array src/test_array.cpp)
