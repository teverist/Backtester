cmake_minimum_required(VERSION 3.16)

project(backtester LANGUAGES CXX VERSION 0.1.0 DESCRIPTION "An event-driven backtester for algorithmic trading")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}-O3")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}-O3")

SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

set(SOURCES_BACKTEST
    src/main.cc
    src/Events/FillEvent.cc
    src/Events/OrderEvent.cc
    src/Data/HistoricCSVDataHandler.cc
    src/Portfolio/Portfolio.cc
    src/Execution/SimpleSimulatedExecutionHandler.cc
    src/Strategy/BuyAndHoldStrategy.cc
    src/Backtest/Backtest.cc
)

add_executable(backtester ${SOURCES_BACKTEST})
target_link_libraries(backtester)
