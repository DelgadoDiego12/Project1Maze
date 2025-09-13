#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <string>

class Maze {
public:
    Maze(const std::string& filename) {
        loadFromFile(filename);
    }
    void print() const {
        for (const auto& row : grid) {
            for (int cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
    }

    std::tuple<int, int> findStart() {
        if(grid.empty() || grid[0].empty()) {
            return {-1,-1};
        }
        const int rows = static_cast<int>(grid.size());
        const int cols = static_cast<int>(grid[0].size());

        for (int j = 0; j < cols; ++j) {
            if (grid[0][j] == 0) {
                return {0,j};
            }
            if (grid[rows - 1][j] == 0) {
                return {rows - 1, j};
            }
        }
        for (int i = 1; i < rows - 1; ++i) {
            if (grid[i][0] == 0) {
                return {i,0};
            }
            if (grid[i][cols - 1] == 0) {
                return {i,cols - 1};
            }
        }
        return {-1,-1};

    }

    bool isOpen(int row, int col) const {
        int R = static_cast<int>(grid.size());
        int C = static_cast<int>(grid[0].size());
        return (row >= 0 && row < R && col >= 0 && col < C && grid[row][col] == 0);
    }

    bool isBoundary(int row, int col) const {
        int R = static_cast<int>(grid.size());
        int C = static_cast<int>(grid[0].size());
        return (row == 0 || row == R - 1 || col == 0 || col == C - 1);
    }

    std::vector<std::tuple<int, int>> findPath() {
        auto [startingRow, startingCol] = findStart();
        if (startingRow == -1 || startingCol == -1) {
            return {};
        }
        const int R = static_cast<int>(grid.size());
        const int C = static_cast<int>(grid[0].size());
        std::vector<std::vector<bool>> explored(R, std::vector<bool>(C, false));

        std::stack<std::tuple<int, int>> stack;
        stack.push({startingRow, startingCol});
        explored[startingRow][startingCol] = true;

        const int moveRow[4] = {1,-1,0,0};
        const int moveCol[4] = {0,0,1,-1};

        while (!stack.empty()) {
            auto [currentRow, currentCol] = stack.top();

            if(isBoundary(currentRow, currentCol) && !(currentRow == startingRow && currentCol == startingCol)) {
                std::vector<std::tuple<int, int>> reversed;
                while(!stack.empty()) {
                    reversed.push_back(stack.top());
                    stack.pop();
                }
                std::vector<std::tuple<int, int>> path(reversed.rbegin(), reversed.rend());
                return path;
            }
            bool moved = false;
            for(int k = 0; k < 4; ++k) {
                int nextRow = currentRow + moveRow[k];
                int nextCol = currentCol + moveCol[k];
                if(isOpen(nextRow, nextCol) && !explored[nextRow][nextCol]) {
                    explored[nextRow][nextCol] = true;
                    stack.push({nextRow, nextCol});
                    moved = true;
                    break;
                }
            }
            if(!moved) {
                stack.pop();
            }
        }
        return {};
    }
private:
    std::vector<std::vector<int>> grid;

    void loadFromFile(const std::string& filename) {
        std::ifstream input(filename);

        std::string line;
        while(std::getline(input,line)) {
            std::vector<int> row;
            for (char c : line) {
                if (c == '0' || c == '1') {
                    row.push_back(c -'0');
                }
            }
            if(!row.empty()) {
                grid.push_back(row);
            }
        }
    }
};



int main() {
    Maze maze("Input.txt");

    maze.print();
    auto [sx, sy] = maze.findStart();
    std::cout << sx << ' ' << sy << '\n';

    auto path = maze.findPath();
    if(path.empty()) {
        std::cout << 'No path found\n';
    } else {
        for (auto [r, c] : path) std::cout << "(" << r << "," << c << ") ";
        std::cout << "\n";
    }
    return 0;
}


