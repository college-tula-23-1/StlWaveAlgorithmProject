// StlWaveAlgorithmProject
#include <iostream>
#include "WaveAlgorithm.h"

namespace fs = std::filesystem;

int main()
{
    WaveAlgorithm wa;
    wa.MapFileName();

    /*fs::path cpath = fs::current_path();

    for (auto dir_entry : fs::directory_iterator(cpath))
        if(dir_entry.path().extension().string() == ".cpp")
            std::cout << dir_entry.path().filename().string() << "\n";*/
}
