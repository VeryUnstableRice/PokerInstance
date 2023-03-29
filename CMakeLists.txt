cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PokerInstance")

# Set the include and library directories
set(WIN_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libraries/windows/include")

# Set the library file depending on the build configuration
set(PHEVAL_LIB_DIR "${CMAKE_SOURCE_DIR}/libraries/windows/lib")
set(PHEVAL_LIB_DEBUG "${PHEVAL_LIB_DIR}/Debug/pheval.lib")
set(PHEVAL_LIB_RELEASE "${PHEVAL_LIB_DIR}/Release/pheval.lib")

# Include the phevaluator include directory
include_directories(${WIN_INCLUDE_DIR})

# Include sub-projects.
add_subdirectory ("PokerInstance")
# PokerInstance/CMakeLists.