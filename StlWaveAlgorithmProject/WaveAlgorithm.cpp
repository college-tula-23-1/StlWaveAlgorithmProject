#include "WaveAlgorithm.h"

namespace fs = std::filesystem;

enum BorderType
{
	TopLeft,
	TopCenter,
	TopRight,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	BottomLeft,
	BottomCenter,
	BottomRight,
	Vertical,
	Horizontal
};

Border singleBorder{ { 218, 194, 191, 195, 197, 180, 192, 193, 217, 179, 196 } };
Border doubleBorder{ { 201, 203, 187, 204, 206, 185, 200, 202, 188, 186, 205 } };


void WaveAlgorithm::PrintChar(HANDLE console, int row, int column, char symbol)
{
	COORD position{ column, row };
	SetConsoleCursorPosition(console, position);
	std::cout << symbol;
}

void WaveAlgorithm::MazeFileName()
{
	fs::path currentPuth = fs::current_path();

	int filePosition{};

	std::cout << "All map's files for maze:\n";
	for (auto dir_entry : fs::directory_iterator(currentPuth))
		if (dir_entry.path().extension().string() == ".maze")
			std::cout << ++filePosition << ": " 
					  << dir_entry.path().filename().string() 
					  << "\n";

	std::cout << "Input position of file: ";
	std::cin >> filePosition;

	int i{};
	fs::path selectFile;

	for (auto dir_entry : fs::directory_iterator(currentPuth))
		if (dir_entry.path().extension().string() == ".maze")
			if (++i == filePosition)
			{
				selectFile = dir_entry.path();
				break;
			}
	//std::cout << selectFile.string() << "\n";
	this->mazeFileName = selectFile.filename().string();
}

void WaveAlgorithm::CreateMaze()
{
	std::ifstream inStream(this->mazeFileName, std::ios::in);

	if (!inStream.is_open()) return;
	
	int sizeLine{ 1024 };
	char* mazeLine = new char[sizeLine] {};

	while (!inStream.eof())
	{
		inStream.getline(mazeLine, sizeLine);

		maze.push_back(std::vector<int>());
		auto indexLast{ maze.size() - 1 };

		for (auto c : std::string(mazeLine))
		{
			CharType symbol = (CharType)std::tolower(c);

			switch (symbol)
			{
			case CharType::Space:
				maze[indexLast].push_back((int)CellType::Space);
				break;
			case CharType::Wall:
				maze[indexLast].push_back((int)CellType::Wall);
				break;
			case CharType::Start:
				maze[indexLast].push_back((int)CellType::Start);
				startCell.row = indexLast;
				startCell.column = maze[indexLast].size() - 1;
				break;
			case CharType::Finish:
				maze[indexLast].push_back((int)CellType::Finish);
				finishCell.row = indexLast;
				finishCell.column = maze[indexLast].size() - 1;
				break;
			}
		}
	}
}

bool WaveAlgorithm::WaveMove()
{
	std::array<Cell, 4> offsets{ { {-1, 0}, {0, 1}, {1, 0}, {0, -1} } };

	int numberFront{};
	currentFront = 0;
	fronts[currentFront].push_back(startCell);

	bool isFindFinish{ false };

	while (true)
	{
		numberFront++;
		fronts[!currentFront].clear();

		for (auto cellFront : fronts[currentFront])
		{
			for (auto offset : offsets)
			{
				Cell newCell{ cellFront.row + offset.row,
							  cellFront.column + offset.column };
				
				if (newCell == finishCell)
				{
					maze[newCell.row][newCell.column] = numberFront;
					isFindFinish = true;
					break;
				}

				if (maze[newCell.row][newCell.column] == (int)CellType::Space)
				{
					maze[newCell.row][newCell.column] = numberFront;
					fronts[!currentFront].push_back(newCell);
				}
			}
			if (isFindFinish) break;
		}
		if (isFindFinish || !fronts[!currentFront].size()) break;
		
		currentFront = !currentFront;
	}

	return isFindFinish;
}

void WaveAlgorithm::CreatePath()
{
	std::array<Cell, 4> offsets{ { {-1, 0}, {0, 1}, {1, 0}, {0, -1} } };

	path.push_back(finishCell);
	int currentNumber = maze[finishCell.row][finishCell.column];

	while (currentNumber)
	{
		Cell currentCell = path[path.size() - 1];

		for (auto offset : offsets)
		{
			Cell candidat{ currentCell.row + offset.row,
						   currentCell.column + offset.column };
			if (maze[candidat.row][candidat.column] == currentNumber - 1)
			{
				path.push_back(candidat);
				break;
			}
		}

		currentNumber--;
	}

	std::reverse(path.begin(), path.end());
}

void WaveAlgorithm::ShowMaze()
{
	int row{};

	for (auto line : maze)
	{
		int column{};

		for (auto i : line)
		{
			CellType item = (CellType)i;
			switch (item)
			{
			case CellType::Space:
				std::cout << (char)MazeType::Space << (char)MazeType::Space;
				break;
			case CellType::Wall:
				std::cout << (char)MazeType::Wall << (char)MazeType::Wall;
				break;
			case CellType::Start:
				std::cout << std::setw(2) << (char)MazeType::Start;
				break;
			case CellType::Finish:
				std::cout << std::setw(2) << (char)MazeType::Finish;
				break;
			default:
				std::cout << std::setw(2) << maze[row][column];
				break;
			}
			column++;
		}
		row++;

		std::cout << "\n";
	}
}

void WaveAlgorithm::ShowPath()
{
	int row{};
	for (auto line : maze)
	{
		int column{};
		for (auto item : line)
		{
			if(maze[row][column] == (int)CellType::Wall)
				std::cout << (char)MazeType::Wall 
						  << (char)MazeType::Wall;
			else
			{
				Cell cell{ row, column };
				if (std::find(path.begin(), path.end(), cell) != path.end())
					std::cout << std::setw(2) << maze[row][column];
				else
					std::cout << (char)CharType::Space << (char)CharType::Space;
			}
			column++;
		}
		std::cout << "\n";
		row++;
	}

}

void WaveAlgorithm::ShowPathAscii()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	int row{};
	for (auto line : maze)
	{
		int column{};
		for (auto item : line)
		{
			if (maze[row][column] == (int)CellType::Wall)
				std::cout << (char)MazeType::Wall;
				//<< (char)MazeType::Wall;
			else
				std::cout << (char)MazeType::Space;
				//<< (char)MazeType::Space;
			column++;
		}
		std::cout << "\n";
		row++;
	}

	// first cell
	int diffRow = path[0].row - path[1].row;
	int diffColumn = path[0].column - path[1].column;

	if (!diffRow)
	{
		if (diffRow > 0)
		{
			//PrintChar(console, path[0].row, path[0].column - 1, singleBorder[Horizontal]);
			PrintChar(console, path[0].row, path[0].column, singleBorder[MiddleRight]);
		}
			
		else 
		{
			PrintChar(console, path[0].row, path[0].column, singleBorder[MiddleLeft]);
			//PrintChar(console, path[0].row, path[0].column + 1, singleBorder[Horizontal]);
		}
			
	}
	else
	{
		if(diffColumn > 0)
			PrintChar(console, path[0].row, path[0].column, singleBorder[BottomCenter]);
		else
			PrintChar(console, path[0].row, path[0].column, singleBorder[TopCenter]);
	}

	for (int i{ 1 }; i < path.size() - 1; i++)
	{
		Cell curr = path[i];
		Cell prev = path[i - 1];
		Cell next = path[i + 1];

		if(curr.column > prev.column && curr.column < next.column ||
			curr.column < prev.column && curr.column > next.column)
			PrintChar(console, curr.row, curr.column, singleBorder[Horizontal]);

		if (curr.row > prev.row && curr.row < next.row ||
			curr.row < prev.row && curr.row > next.row)
			PrintChar(console, curr.row, curr.column, singleBorder[Vertical]);

		if (curr.column > prev.column && curr.row < next.row ||
			curr.row < prev.row && curr.column > next.column)
			PrintChar(console, curr.row, curr.column, singleBorder[TopRight]);

		if (curr.column < prev.column && curr.row < next.row ||
			curr.row < prev.row && curr.column < next.column)
			PrintChar(console, curr.row, curr.column, singleBorder[TopLeft]);

		if (curr.column > prev.column && curr.row > next.row ||
			curr.row > prev.row && curr.column > next.column)
			PrintChar(console, curr.row, curr.column, singleBorder[BottomRight]);

		if (curr.row > prev.row && curr.column < next.column ||
			curr.column < prev.column && curr.row > next.row)
			PrintChar(console, curr.row, curr.column, singleBorder[BottomLeft]);
	}
	PrintChar(console, maze.size() + 1, 0, '\n');
}
