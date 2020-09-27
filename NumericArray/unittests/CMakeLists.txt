macro(cs_unittest target)
  set(sources ${ARGN})
  add_executable(${target} ${sources})
  add_dependencies(${target} NumericArray)
  format_output_name(${target} ${target})
  set_target_properties(${target} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    )
  target_include_directories(${target}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${NumericArray_SOURCE_DIR}/include
    PRIVATE ${NumericArray_SOURCE_DIR}/3rdparty/Catch2/include
    PRIVATE ${NumericArray_SOURCE_DIR}/testutils/include
    )
  target_link_libraries(${target})
endmacro()

### Unit Tests ###############################################################

cs_unittest(unittest_array src/unittest_array.cpp src/unittest_array_main.cpp
  ../testutils/include/TestArrayEqual.h ../testutils/include/TestEquals.h
  )

cs_unittest(unittest_math src/unittest_math.cpp src/unittest_math_impl.cpp
  ../testutils/include/TestEquals.h ../testutils/include/TestFormatter.h
  )
