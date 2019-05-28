#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT
#endif


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Eigen/Dense"

using namespace Eigen;
using namespace std;

extern "C"{

    SUPEREXPORT double useRosenblatt(double* X);
    SUPEREXPORT double useRegLinear(double* X);
    SUPEREXPORT void writeTrainModel(MatrixXd wMat, double average);
    SUPEREXPORT void configureModelFile(int inputCountPerResult, int inputCountPerSample, int modele);
    SUPEREXPORT double getClasse(double result[], int inputCountPerResult);

}

