// StlWaveAlgorithmProject
#include <iostream>
#include "WaveAlgorithm.h"

namespace fs = std::filesystem;

int main()
{
    WaveAlgorithm wa;
    wa.MazeFileName();
    wa.CreateMaze();
    wa.ShowMaze();
    wa.WaveMove();
    wa.ShowMaze();
}
