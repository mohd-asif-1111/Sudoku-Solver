#include <iostream>
#include <utility>
#include <vector>

using Cell = std::pair<int, int>;
using Board = std::vector<std::vector<int>>;

constexpr Cell None{-1, -1};

int calls = 0;
int backtracks = 0;

bool debug = true;

void printBoard(const Board &sudoku)
{
	for (const std::vector<int> &row : sudoku)
	{
		for (const int &col : row)
		{
			std::cout << col << ' ';
		}
		std::cout << '\n';
	}
}

bool valid(const Board &sudoku, const Cell &cell, int num)
{
	int r = cell.first;
	int c = cell.second;
	for (const int row : sudoku[r])
	{
		if (row == num)
		{
			return false;
		}
	}
	for (const std::vector<int> &row : sudoku)
	{
		if (row[c] == num)
		{
			return false;
		}
	}
	int box_row = (r / 3) * 3;
	int box_col = (c / 3) * 3;
	for (int i = box_row; i < box_row + 3; i++)
	{
		for (int j = box_col; j < box_col + 3; j++)
		{
			if (sudoku[i][j] == num)
			{
				return false;
			}
		}
	}
	return true;
}

std::vector<int> candidates(const Board &sudoku, const Cell &cell)
{
	std::vector<int> cands;
	for (int num = 1; num <= 9; num++)
	{
		if (valid(sudoku, cell, num))
		{
			cands.push_back(num);
		}
	}
	return cands;
}

Cell bestEmptyCell(const Board &sudoku)
{
	Cell bestCell;
	std::vector<int> bestCands;
	std::vector<int> cands;

	bestCell = None;
	bestCands = {0};

	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (sudoku[r][c] == 0)
			{
				cands = candidates(sudoku, {r, c});
				if (cands.size() == 1)
				{
					bestCell = {r, c};
					return bestCell;
				}

				if (bestCell == None)
				{
					bestCell = {r, c};
					bestCands = cands;
				}
				else if (cands.size() < bestCands.size())
				{
					bestCell = {r, c};
					bestCands = cands;
				}
			}
		}
	}
	return bestCell;
}

bool solve(Board &sudoku)
{
	calls++;
	Cell empty_cell = bestEmptyCell(sudoku);
	if (empty_cell == None)
	{
		return true;
	}
	int r = empty_cell.first;
	int c = empty_cell.second;

	std::vector<int> cands;
	cands = candidates(sudoku, empty_cell);

   if(cands.empty()){
      return false;
   }

	for (int &cand : cands)
	{
		sudoku[r][c] = cand;

		if (solve(sudoku))
		{
			return true;
		}

		sudoku[r][c] = 0;

		backtracks++;
	}
	return false;
}

int main()
{
	Board sudoku;
	sudoku = {
		{1, 2, 0, 0, 9, 0, 0, 0, 5},
		{0, 6, 0, 0, 0, 0, 0, 2, 0},
		{0, 4, 0, 7, 2, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 7, 0},
		{0, 3, 0, 0, 6, 0, 0, 0, 0},
		{0, 7, 0, 0, 0, 0, 0, 0, 8},
		{2, 0, 0, 0, 5, 0, 0, 0, 3},
		{0, 8, 0, 4, 0, 0, 0, 9, 0},
		{0, 5, 0, 0, 0, 3, 0, 0, 1}};

	if (solve(sudoku))
	{
		std::cout << "Solved!\n";
	}
	else
	{
		std::cout << "Not Solved!\n";
	}

	printBoard(sudoku);

	if (debug)
	{
		std::cout << "Calls: " << calls;
		std::cout << '\n';
		std::cout << "Backtracks: " << backtracks;
	}
}