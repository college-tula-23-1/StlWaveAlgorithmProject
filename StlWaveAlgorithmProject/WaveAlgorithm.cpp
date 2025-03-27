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

	COORD position{ 10, 5 };
	
	SetConsoleCursorPosition(console, position);

	std::cout << "Hello world";
}
