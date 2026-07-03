#include <iostream>
#include <utility>
#include <vector>

void printBoard(const std::vector<std::vector<int>> &sudoku)
{
	for (const std::vector<int>& row : sudoku)
	{
		for (const int& col : row)
		{
			std::cout << col << ' ';
		}
		std::cout << '\n';
	}
}

std::pair<int, int> findEmpty(const std::vector<std::vector<int>> &sudoku)
{
	std::pair<int, int> cell;
	cell = {-1, -1};
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				cell = {i, j};
				return cell;
			}
		}
	}
	return cell;
}

bool valid(const std::vector<std::vector<int>> &sudoku, std::pair<int, int> cell, int num)
{
	int r = cell.first;
	int c = cell.second;
	for (const int& row : sudoku[r])
	{
		if (row == num)
		{
			return false;
		}
	}
	for (const std::vector<int>& row : sudoku)
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

bool solve(std::vector<std::vector<int>> &sudoku)
{
	std::pair<int, int> empty_cell = findEmpty(sudoku);
	std::pair<int, int> None = {-1, -1};
	if (empty_cell == None)
	{
		return true;
	}
	int r = empty_cell.first;
	int c = empty_cell.second;

	for (int num = 1; num <= 9; num++)
	{
		if (valid(sudoku, empty_cell, num))
		{
			sudoku[r][c] = num;
			
			if (solve(sudoku))
			{
				return true;
			}
			
			sudoku[r][c] = 0;
		}
	}
	return false;
}

int main()
{
	std::vector<std::vector<int>> sudoku;
	sudoku = {
		{1, 2, 2, 0, 9, 0, 0, 0, 5},
		{0, 6, 0, 0, 0, 0, 0, 2, 0},
		{0, 4, 0, 7, 2, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 7, 0},
		{0, 3, 0, 0, 6, 0, 0, 0, 0},
		{0, 7, 0, 0, 0, 0, 0, 0, 8},
		{2, 0, 0, 0, 5, 0, 0, 0, 3},
		{0, 8, 0, 4, 0, 0, 0, 9, 0},
		{0, 5, 0, 0, 0, 3, 0, 0, 1}
	};

	if (solve(sudoku))
	{
		std::cout << "Solved!\n";
	}
	else
	{
		std::cout << "Not Solved!\n";
	}

	printBoard(sudoku);
}