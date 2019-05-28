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

     SUPEREXPORT int findColinear(MatrixXd xMat);
     SUPEREXPORT MatrixXd removeColumn(MatrixXd xMat, int rang);
     SUPEREXPORT MatrixXd removeLines(MatrixXd xMat, int listIndex[], int nbIndex);
     SUPEREXPORT MatrixXd harmonoizeResult(MatrixXd yMat);
     SUPEREXPORT double correctionMean(MatrixXd xMat, MatrixXd wMat);
     SUPEREXPORT MatrixXd translateTrainingData(double* XTrain,  int sampleCount, int inputCountPerSample);
     SUPEREXPORT MatrixXd addBias(MatrixXd xMat);

}





