cmake_minimum_required()
project(GameOfLife)

include(../base.cmake)

set(SRC board/board.cpp
        board/board_test.cpp
        cell/cell.cpp
        cell_factory/cell_factory.cpp
        board/cell_factory_mock/cell_factory_mock.cpp
        board/cell_mock/cell_mock.cpp
        cell/cell_test.cpp
        game_test.cpp
        grid/grid.cpp
        grid/grid_test.cpp
        )
add_executable(GameOfLife ${SRC})
target(GameOfLife)
