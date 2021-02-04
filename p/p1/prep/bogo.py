import numpy as np
import random
import time

# 0's represent an empty space
grid = [[0,0,4,3,0,0,2,0,9],
        [0,0,5,0,0,9,0,0,1],
        [0,7,0,0,6,0,0,4,3],
        [0,0,6,0,0,2,0,8,7],
        [1,9,0,0,0,7,4,0,0],
        [0,5,0,0,8,3,0,0,0],
        [6,0,0,0,0,0,1,0,5],
        [0,0,4,5,0,8,6,9,0],
        [0,4,2,9,1,0,3,0,0]]

# implements sudoku the rules to determine wether a number is in a valid position
def valid_position(y, x):
    # horisontal and vertical rules
    num = grid[y][x]
    grid[y][x] = 0
    for pos in range(9):
        if grid[pos][x] == num or grid[y][pos] == num:
            grid[y][x] = num
            return False

    # sub-grid rules
    x_0 = 3 * (x // 3)
    y_0 = 3 * (y // 3)
    for i in range(y_0, y_0 + 3):
        for j in range(x_0, x_0 + 3):
            if grid[i][j] == num:
                grid[y][x] = num
                return False
    grid[y][x] = num
    return True

class pos:
    def __init__(self, i, j):
        self.i = i
        self.j = j

# checks every square for the rules
def is_solved():
    for i in range(9):
        for j in range(9):
            if not valid_position(i, j):
                return False
    return True

def solve():
    # determine the indices of the squares to be calculated
    positions = []
    for i in range(9):
        for j in range(9):
            if not grid[i][j]:
                positions.append(pos(i, j))

    # randomising board untill it is correct
    while not is_solved():
        for coord in positions:
            grid[coord.i][coord.j] = random.randint(1, 9)


solve()