cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

### Project ##################################################################

project(NumericArray)

# Custom CMake utilities
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(FormatOutputName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTS "Enable tests" OFF)
option(ENABLE_UNITTESTS "Enable unit tests" OFF)

### NumericArray #############################################################

list(APPEND NumericArray_HEADERS
  include/cs/Array.h
  include/cs/ArrayPolicy.h
  include/cs/ArrayTraits.h
  include/cs/BinaryOperators.h
  include/cs/ExprBase.h
  include/cs/Functions.h
  include/cs/Geometry.h
  include/cs/ListAssign.h
  include/cs/Manipulator.h
  include/cs/Math.h
  include/cs/Meta.h
  include/cs/NumericArray.h
  include/cs/NumericTraits.h
  include/cs/SIMD.h
  include/cs/UnaryOperators.h
  include/cs/impl/ArrayImpl.h
  include/cs/impl/BinaryOperatorsImpl.h
  include/cs/impl/FunctionsImpl.h
  include/cs/impl/GeometryImpl.h
  include/cs/impl/IndexingImpl.h
  include/cs/impl/UnaryOperatorsImpl.h
  )

### N4 #######################################################################

list(APPEND N4_HEADERS
  include/N4/BinaryOperators.h
  include/N4/Color3f.h
  include/N4/Dispatch.h
  include/N4/ExprBase.h
  include/N4/ExprCast.h
  include/N4/Functions.h
  include/N4/Manipulator.h
  include/N4/Math.h
  include/N4/Matrix4f.h
  include/N4/N4.h
  include/N4/Normal3f.h
  include/N4/Optics.h
  include/N4/SIMD.h
  include/N4/TypeTraits.h
  include/N4/UnaryOperators.h
  include/N4/Util.h
  include/N4/Vector4f.h
  include/N4/Vertex4f.h
  )

### Target ###################################################################

add_custom_target(NumericArray
  SOURCES ${NumericArray_HEADERS}
  )

add_custom_target(N4
  SOURCES ${N4_HEADERS}
  )

### Tests ####################################################################

if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()

if(ENABLE_UNITTESTS)
  add_subdirectory(unittests)
endif()
