'''
Project: prep
File: prep/simpl.py
-----
File Created: Monday, 1st February 2021 4:47:34 pm
Author: Finlay Morrison (morrison.fin02@gmail.com)
-----
Last Modified: Thursday, 18th March 2021 2:29:51 am
Modified By: Finlay Morrison (morrison.fin02@gmail.com)
-----
Copyright (CC BY-SA) 2021 Finlay Morrison
'''

import numpy as np
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

def determine_value(i, j):
    nums = [True] + [False] * 9
    for pos in range(9):
        nums[grid[i][pos]] = True
        nums[grid[pos][j]] = True
    i_0 = 3 * (i // 3)
    j_0 = 3 * (j // 3)
    for pos_i in range(i_0, i_0 + 3):
        for pos_j in range(j_0, j_0 + 3):
            print (pos_i, pos_j)
            nums[grid[pos_i][pos_j]] = True

    found = 0
    for num in range(1, 10):
        if not nums[num]:
            if found:
                return 0
            else:
                found = num
    return found


def solve():
    changed = True
    while changed:
        changed = False
        for i in range(9):
            for j in range(9):
                if not grid[i][j]:
                    grid[i][j] = determine_value(i, j)
                    if grid[i][j]:
                        changed = True

print('\n', np.array(grid), '\n')

start = time.time()
solve()
finish = time.time()

print(np.array(grid), '\n')

determine_value(7, 8)

print(finish - start)