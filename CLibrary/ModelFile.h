#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT
#endif


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "Eigen/Dense"

using namespace Eigen;
using namespace std;

extern "C"{

    SUPEREXPORT void writeTrainModel(MatrixXd wMat);
    SUPEREXPORT void configureModelFile(int parametre, int modele);
}

