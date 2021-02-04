#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <functional>
#include <utility>
#include <cmath>
#include <fstream>

class sudoku_grid
{
private:
    int grid_size; /* size of the sub-grids */
    int board_size; /* size of the entire board */
    std::vector<std::vector<int>> grid;
    bool possible_placment(int y, int x, int num) const
    {
        for (int pos = 0; pos < board_size; ++pos)
        {
            if (grid[pos][x] == num || grid[y][pos] == num)
            {
                return false;
            }
        }
        int x_0 = grid_size * (x / grid_size);
        int y_0 = grid_size * (y / grid_size);
        for (int i = y_0; i < y_0 + grid_size; ++i)
        {
            for (int j = x_0; j < x_0 + grid_size; ++j)
            {
                if (grid[i][j] == num)
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
    sudoku_grid(const sudoku_grid& s_grid) :
        grid_size(s_grid.grid_size), 
        board_size(s_grid.board_size),
        grid(s_grid.grid)
    {}
    sudoku_grid& operator= (const sudoku_grid& s_grid)
    {
        grid_size = s_grid.grid_size;
        board_size = s_grid.board_size;
        grid = s_grid.grid;
        return *this;
    }
    sudoku_grid(const sudoku_grid&& s_grid) noexcept:
        grid_size(s_grid.grid_size), 
        board_size(s_grid.board_size),
        grid(std::move(s_grid.grid))
    {}
    sudoku_grid& operator= (const sudoku_grid&& s_grid) noexcept
    {
        grid_size = s_grid.grid_size;
        board_size = s_grid.board_size;
        grid = std::move(s_grid.grid);
        return *this;
    }
    ~sudoku_grid() = default;

    friend std::ostream& operator<< (std::ostream& os, const sudoku_grid& g); /* print out board in UTF-16 chars encoded in UTF-8 */

    bool solve()
    {
        int s_i=-1, s_j=-1;
        for (int i = 0; i < board_size; ++i)
        {
            for (int j = 0; j < board_size; ++j)
            {
                if (grid[i][j] == 0)
                {
                    s_i = i; 
                    s_j = j;
                    goto exit; /* the only clean way to break out a doubly-nested for loop efficiently */
                }
            }
        }
        return true;
    exit:

        for (int num = 1; num <= board_size; ++num)
        {
            if (possible_placment(s_i, s_j, num))
            {
                grid[s_i][s_j] = num;
                if (solve())
                {
                    return true;
                }
                grid[s_i][s_j] = 0;
            }
        }
        return false;
    }

    void set_puzzle(const std::vector<std::vector<int>>& new_puzzle)
    {
        for (int i = 0; i < board_size; ++i)
        {
            std::copy(new_puzzle[i].begin(), new_puzzle[i].end(), grid[i].begin());
        }
    }

    bool check_solution(const std::vector<std::vector<int>>& solution)
    {
        for (int i = 0; i < board_size; ++i)
        {
            for (int j = 0; j < board_size; ++j)
            {
                if (grid[i][j] != solution[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
};

std::string create_divider(const char* first, const char*  mid, const char*  div, const char*  last, int len)
{
    /* no point in using a stringstream since the string will not be long enough for it to make a difference */
    std::string out;
    out += first;
    for (int i = 0; i < len; ++i)
    {
        out += mid;
        for (int j = 0; j < len; ++j)
        {
            out += mid; out += mid;
        }
        out += (i < len - 1) ? div : last; 
    }
    return out;
}

/*
 * outputs the sudoku grid passed in using UTF-16 chars encoded in UTF-8 chars to the std::ostream passed in
 */
std::ostream& operator<< (std::ostream& os, const sudoku_grid& g)
{
    /* line characters */
    const char *h_line="\u2500", *v_line="\u2502";
    /* corner characters */
    const char *tl_corner="\u250c", *tr_corner="\u2510", *bl_corner="\u2514", *br_corner="\u2518";
    /* 3-way intersection */
    const char *t_int="\u252c", *l_int="\u251c", *r_int="\u2524", *b_int="\u2534";
    /* 4-way intersection */
    const char *m_int="\u253c";
    /* empty gridspace */
    const char *space="\u2581";
    /* character set */
    const char *char_set="_123456789ABCDEF";

    os << create_divider(tl_corner, h_line, t_int, tr_corner, g.grid_size) << '\n';

    std::string m_divider = create_divider(l_int, h_line, m_int, r_int, g.grid_size);

    for (int i = 0; i < g.board_size; ++i)
    {
        if (i % g.grid_size == 0 && i != 0)
        {
            os << m_divider << '\n';
        }
        for (int j = 0; j < g.board_size; ++j)
        {
            if (j % g.grid_size == 0)
            {
                os << v_line;
                os << ' ';
            }
            os << char_set[g.grid[i][j]];
            os << ' ';
        }
        os << v_line << '\n';
    }
    os << create_divider(bl_corner, h_line, b_int, br_corner, g.grid_size);
    return os;
}

class timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
    std::function<void(uint64_t)> cb;
public:
    timer(std::function<void(uint64_t)> cb=[](uint64_t ms){std::cout << "execution time: " << ms / 1000.0 << "ms" << std::endl;}):
        cb(cb), t_start(std::chrono::high_resolution_clock::now())
    {}
    ~timer()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> t_end = std::chrono::high_resolution_clock::now();
        uint64_t ms = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
        cb(ms);
    }
};

struct puzzle
{
    std::vector<std::vector<int>> start;
    std::vector<std::vector<int>> finish;
};

puzzle load_puzzle(const std::string& raw)
{
    std::string symbols="0123456789ABCDEF";

    constexpr int board_size = 9;
    puzzle p;
    p.start.resize(board_size);
    p.finish.resize(board_size);
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            p.start[i].push_back(symbols.find(raw[i * board_size + j]));
            p.finish[i].push_back(symbols.find(raw[i * board_size + j + board_size * board_size + 1]));
        }
    }
    return p;
}

std::vector<puzzle> load_puzzles(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<puzzle> puzzles;
    std::string line;
    while (std::getline(file, line))
    {
        if (isdigit(line[0]))
        {
            puzzles.push_back(load_puzzle(line));
        }
    }
    return puzzles;
}

int main(int argc, char** argv)
{
    timer t;

    //std::vector<puzzle> puzzles = load_puzzles("sudoku.csv");

    sudoku_grid g(3);

    g.set_puzzle({{0,2,0,8,0,0,0,0,0},
                  {9,0,1,0,0,0,0,0,0},
                  {0,7,0,2,4,6,0,0,0},
                  {2,0,9,0,0,5,0,0,4},
                  {0,0,5,0,8,0,0,6,0},
                  {0,0,0,0,6,1,0,0,0},
                  {0,0,0,0,0,0,0,5,7},
                  {3,0,0,0,0,0,8,0,0},
                  {0,0,0,3,2,7,0,0,0}});

    std::cout << g << std::endl;

    g.solve();

    std::cout << g << std::endl;

    /*
    for (int i = 0; i < puzzles.size(); ++i)
    {
        g.set_puzzle(puzzles[i].start);

        g.solve();
        if (!g.check_solution(puzzles[i].finish))
        {
            std::cout << "failed puzzle " << i << std::endl;
        }
    }
    */

    return 0;
}