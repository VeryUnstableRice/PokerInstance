# CMakeList.txt : CMake project for PokerInstance, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (PokerInstance "main.cpp" "Poker/PokerInstance.cpp" "Poker/AbstractPokerPlayer.cpp" "Poker/PokerCard.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PokerInstance PROPERTY CXX_STANDARD 20)
endif()

# Link the phevaluator library depending on the build configuration
target_link_libraries(PokerInstance debug ${PHEVAL_LIB_DEBUG} optimized ${PHEVAL_LIB_RELEASE})
# TODO: Add tests and install targets if needed.
