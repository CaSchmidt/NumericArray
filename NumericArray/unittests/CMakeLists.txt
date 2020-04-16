macro(cs_unittest target)
  set(sources ${ARGN})
  add_executable(${target} ${sources})
  add_dependencies(${target} NumericArray)
  format_output_name(${target} ${target})
  if(MSVC)
    target_compile_options(${target}
      PRIVATE /source-charset:UTF-8 /execution-charset:UTF-8 /validate-charset
      )
  endif()
  target_include_directories(${target}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${NumericArray_SOURCE_DIR}/include
    PRIVATE ${NumericArray_SOURCE_DIR}/3rdparty/Catch2/include
    PRIVATE ${NumericArray_SOURCE_DIR}/testutils/include
    )
  target_link_libraries(${target})
endmacro()

### Unit Tests ###############################################################

cs_unittest(unittest_math src/unittest_math.cpp src/unittest_math_impl.cpp
  ../testutils/include/TestFormatter.h ../testutils/include/TestEquals.h
  )
