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
		std::cout << mazeLine << "\n";
	}
}
