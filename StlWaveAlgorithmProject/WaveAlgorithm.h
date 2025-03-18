#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iomanip>

enum class CellType
{
	Space  = -1,
	Wall   = -2,
	Start  = 0,
	Finish = -3
};

enum class CharType
{
	Space =  ' ',
	Wall =   '#',
	Start =  's',
	Finish = 'f'
};

enum class MazeType
{
	Space  = ' ',
	Wall   = 178,
	Start  = 'S',
	Finish = 'F'
};

struct Cell
{
	int row;
	int column;

	friend bool operator==(const Cell& cellOne, const Cell& cellTwo)
	{
		return cellOne.row == cellTwo.row && cellOne.column == cellTwo.column;
	}
};

typedef std::vector<std::vector<int>> Maze;
typedef std::array<std::vector<Cell>, 2> Fronts;
typedef std::vector<Cell> Path;

class WaveAlgorithm
{
	std::string mazeFileName;
	Maze maze;
	
	Cell startCell;
	Cell finishCell;

	Fronts fronts;
	bool currentFront{};

	Path path;

public:
	void MazeFileName();
	void CreateMaze();
	void WaveMove();
	void CreatePath();

	void ShowMaze();
};

