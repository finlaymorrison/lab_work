'''
Project: prep
File: prep/algorithm.py
-----
File Created: Monday, 1st February 2021 1:20:37 pm
Author: Finlay Morrison (morrison.fin02@gmail.com)
-----
Last Modified: Thursday, 18th March 2021 2:29:12 am
Modified By: Finlay Morrison (morrison.fin02@gmail.com)
-----
Copyright (CC BY-SA) 2021 Finlay Morrison
'''

import numpy as np
import time

# 0's represent an empty space
grid = [[5,3,0,0,7,0,0,0,0],
        [6,0,0,1,9,5,0,0,0],
        [0,9,8,0,0,0,0,6,0],
        [8,0,0,0,6,0,0,0,3],
        [4,0,0,8,0,3,0,0,1],
        [7,0,0,0,2,0,0,0,6],
        [0,6,0,0,0,0,2,8,0],
        [0,0,0,4,1,9,0,0,5],
        [0,0,0,0,8,0,0,7,9]]

def valid_move(x, y, num):
    # horisontal and vertical rules
    for pos in range(9):
        if grid[pos][x] == num or grid[y][pos] == num:
            return False

    # sub-grid rules
    x_0 = 3 * (x // 3)
    y_0 = 3 * (y // 3)
    for i in range(y_0, y_0 + 3):
        for j in range(x_0, x_0 + 3):
            if grid[i][j] == num:
                return False
    return True

def recursive_solve():
    print(np.array(grid), '\n')
    time.sleep(0.001)
    # finding the next empty space
    x = -1
    y = -1
    find = False
    for i in range(9):
        for j in range(9):
            if grid[i][j] == 0:
                x = j
                y = i
                find = True
                break
        if find:
            break
    if not find:
        # sudoku has been solved since no spaces remain
        return True

    # checking the puzzle for the numbers 1 to 9 in grid[y][x]
    for num in range(1, 10):
        if valid_move(x, y, num):
            grid[y][x] = num
            if recursive_solve():
                # if previous function returns true, the puzzle is solved
                return True
            grid[y][x] = 0
    return False
                

print('\n', np.array(grid), '\n')

start = time.time()
recursive_solve()
end = time.time()

print(np.array(grid), '\n')
print(end - start, '\n')