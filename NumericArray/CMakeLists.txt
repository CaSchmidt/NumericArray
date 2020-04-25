cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

### Project ##################################################################

project(NumericArray)

# Custom CMake utilities
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(FormatOutputName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### NumericArray #############################################################

list(APPEND NumericArray_HEADERS
  include/cs/Array.h
  include/cs/ArrayPolicy.h
  include/cs/ArrayTraits.h
  include/cs/BinaryOperators.h
  include/cs/ExprBase.h
  include/cs/Functions.h
  include/cs/ListAssign.h
  include/cs/Math.h
  include/cs/NumericArray.h
  include/cs/TypeTraits.h
  include/cs/UnaryOperators.h
  include/cs/impl/ArrayImpl.h
  include/cs/impl/BinaryOperatorsImpl.h
  include/cs/impl/FunctionsImpl.h
  include/cs/impl/Indexing.h
  include/cs/impl/UnaryOperatorsImpl.h
  )

### Target ###################################################################

add_custom_target(NumericArray
  SOURCES ${NumericArray_HEADERS}
  )

### Tests ####################################################################

add_subdirectory(tests)
add_subdirectory(unittests)
