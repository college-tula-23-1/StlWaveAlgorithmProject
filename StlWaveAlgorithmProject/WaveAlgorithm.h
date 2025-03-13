#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <filesystem>

enum CellType
{
	Space  = -1,
	Wall   = -2,
	Start  = 0,
	Finish = -3
};

struct Cell
{
	int row;
	int column;
};

typedef std::vector<std::vector<int>> Map;
typedef std::array<std::vector<Cell>, 2> Fronts;
typedef std::vector<Cell> Path;

class WaveAlgorithm
{
	std::string mapFileName;
	Map mazeMap;
	
	Cell startCell;
	Cell finishCell;

	Fronts fronts;
	bool currentFront{};

	Path path;

public:
	void MapFileName();
	void CreateMazeMap();
	void WaveMove();
	void CreatePath();

	void ShowMaze();
};

