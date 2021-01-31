#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <functional>

class sudoku_grid
{
private:
    int grid_size; /* size of the sub-grids */
    int board_size; /* size of the entire board */
    std::vector<std::vector<int>> grid;
    bool possible_placment(int y, int x, int num)
    {
        for (int i = 0; i < board_size; ++i)
        {
            if (grid[i][x] == num)
            {
                return false;
            }
        }
        for (int j = 0; j < board_size; ++j)
        {
            if (grid[y][j] == num)
            {
                return false;
            }
        }
        int x_0 = grid_size * (x / grid_size);
        int y_0 = grid_size * (y / grid_size);
        for (int i = 0; i < grid_size; ++i)
        {
            for (int j = 0; j < grid_size; ++j)
            {
                if (grid[y_0 + i][x_0 + j] == num)
                {
                    return false;
                }
            }
        }
        return true;
    }
public:
    sudoku_grid(int grid_size=3) :
        grid_size(grid_size),
        board_size(grid_size * grid_size),
        grid(grid_size * grid_size, std::vector<int>(grid_size * grid_size))
    {}
    sudoku_grid(const std::vector<std::vector<int>>& grid) :
        grid_size(std::sqrt(grid.size())),
        board_size(grid.size()),
        grid(grid)
    {}
    friend std::ostream& operator<< (std::ostream& os, const sudoku_grid& g); /* print out board in ASCII chars */
    friend std::wostream& operator<< (std::wostream& os, const sudoku_grid& g); /* print out board in UTF-16 chars */
    bool is_solved()
    {
        for (int i = 0; i < board_size; ++i)
        {
            for (int j = 0; j < board_size; ++j)
            {
                if (grid[i][j] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool solve()
    {
        for (int i = 0; i < board_size; ++i)
        {
            for (int j = 0; j < board_size; ++j)
            {
                if (grid[i][j] == 0)
                {
                    for (int num = 1; num <= board_size; ++num)
                    {
                        if (possible_placment(i, j, num))
                        {
                            grid[i][j] = num;
                            if (solve())
                            {
                                return true;
                            }
                            grid[i][j] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return is_solved();
    }
};

/*
 * outputs the sudoku grid passed in using ASCII chars to the std::ostream passed in
 */
std::ostream& operator<< (std::ostream& os, const sudoku_grid& g)
{
    /* constants to define the dividers used */
    constexpr char corner = '+';
    constexpr char h_side = '-';
    constexpr char v_side = '|';

    /* creating a divider that can be used later in the function to seperate the rows or grids */
    std::string divider;
    for (int i = 0; i < g.board_size; ++i)
    {
        if (i % g.grid_size == 0)
        {
            divider += corner;
        }
        divider += h_side;
    }
    divider += corner;

    /* prints out the grids, horizontally split by {v_side} and vertically split by {divider} */
    for (int i = 0; i < g.board_size; ++i)
    {
        if (i % g.grid_size == 0)
        {
            os << divider << '\n';
        }
        for (int j = 0; j < g.board_size; ++j)
        {
            if (j % g.grid_size == 0)
            {
                os << v_side;
            }
            os << g.grid[i][j];
        }
        os << v_side << '\n';
    }
    os << divider;
    return os;
}

class timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
    std::function<void(uint64_t)> cb;
public:
    timer(std::function<void(uint64_t)> cb=[](uint64_t ms){std::cout << ms / 1000.0 << "ms" << std::endl;}):
        cb(cb), t_start(std::chrono::high_resolution_clock::now())
    {}
    ~timer()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> t_end = std::chrono::high_resolution_clock::now();
        uint64_t ms = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
        cb(ms);
    }
};

int main(int argc, char** argv)
{
    timer t;
    sudoku_grid grid({{5,3,0,0,7,0,0,0,0},
                      {6,0,0,1,9,5,0,0,0},
                      {0,9,8,0,0,0,0,6,0},
                      {8,0,0,0,6,0,0,0,3},
                      {4,0,0,8,0,3,0,0,1},
                      {7,0,0,0,2,0,0,0,6},
                      {0,6,0,0,0,0,2,8,0},
                      {0,0,0,4,1,9,0,0,5},
                      {0,0,0,0,8,0,0,7,9}});
    grid.solve();
    std::cout << grid << std::endl;
    return 0;
}