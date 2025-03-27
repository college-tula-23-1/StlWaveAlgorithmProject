// StlWaveAlgorithmProject
#include <iostream>
#include "WaveAlgorithm.h"

namespace fs = std::filesystem;

int main()
{
    WaveAlgorithm wa;

    /*wa.MazeFileName();
    wa.CreateMaze();
    wa.ShowMaze();
    wa.WaveMove();
    std::cout << "\n";
    wa.ShowMaze();
    std::cout << "\n";
    wa.CreatePath();
    wa.ShowPath();*/

    wa.ShowPathAscii();
}
