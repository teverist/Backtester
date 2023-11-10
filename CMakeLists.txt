project(backtester)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)

# Source files
file(GLOB SOURCES_BACKTEST "src/*.cc" "src/Data/*.cc" "src/Events/*.cc" "src/Backtest/*.cc"  "src/Execution/*.cc" "src/Portfolio/*.cc" "src/Strategy/*.cc" )

add_executable(backtester ${SOURCES_BACKTEST})

# Include directories
target_include_directories(backtester PUBLIC ${CMAKE_SOURCE_DIR}/include)
