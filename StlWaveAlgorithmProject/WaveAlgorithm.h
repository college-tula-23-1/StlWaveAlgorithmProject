#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

enum class CellType
{
	Space  = -1,
	Wall   = -2,
	Start  = 0,
	Finish = -3
};

enum class MazeChar
{
	Space =  ' ',
	Wall =   '#',
	Start =  's',
	Finish = 'f'
};

struct Cell
{
	int row;
	int column;
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

