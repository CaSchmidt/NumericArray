cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

### Project ##################################################################

project(NumericArray)

set(NumericArray_HEADERS
  include/cs/Array.h
  include/cs/BinaryOperators.h
  include/cs/ExprBase.h
  include/cs/Functions.h
  include/cs/IndexPolicy.h
  include/cs/NumericArray.h
  include/cs/Types.h
  include/cs/UnaryOperators.h
  include/cs/impl/ArrayImpl.h
  include/cs/impl/BinaryOperatorsImpl.h
  include/cs/impl/FunctionsImpl.h
  include/cs/impl/Indexing.h
  include/cs/impl/IndexPolicyImpl.h
  include/cs/impl/UnaryOperatorsImpl.h
  )

set(NumericArray_3rdparty
  3rdparty/Catch2/include/catch.hpp
  )

### Target ###################################################################

add_executable(NumericArray
  src/main.cpp
  ${NumericArray_HEADERS}
  ${NumericArray_3rdparty}
  )

target_include_directories(NumericArray PRIVATE
  ${NumericArray_SOURCE_DIR}/include
  ${NumericArray_SOURCE_DIR}/3rdparty/Catch2/include
  )

target_link_libraries(NumericArray)
