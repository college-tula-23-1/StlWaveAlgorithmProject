#include "WaveAlgorithm.h"

namespace fs = std::filesystem;

void WaveAlgorithm::MapFileName()
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
	std::cout << selectFile.string() << "\n";
}
