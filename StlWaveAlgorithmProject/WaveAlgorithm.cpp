#include "WaveAlgorithm.h"

namespace fs = std::filesystem;

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


void WaveAlgorithm::WaveMove()
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
