#include <iostream>
#include <math.h>
#include "Eigen/Dense"
#include "Matrix.h"

using namespace Eigen;
using namespace std;

extern "C"{

    SUPEREXPORT double getDistance(double* X1, double* X2, int inputCountPerSample);
    SUPEREXPORT double* getColonne(double* ytrain, int sampleIndex, int inputCountPerResult);
    SUPEREXPORT double* getPhi(double* XTrain, int sampleCount, int inputCountPerSample, double gamma);
    SUPEREXPORT MatrixXd getWeight(double* phi, double* YTrain, int sampleCount, int inputCountPerResult);
    SUPEREXPORT void trainNaifRbf(double* XTrain, double* YTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult, double gamma);
    SUPEREXPORT double useNaifRbf(double* X, double* XTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult);
    SUPEREXPORT double getResult(double* results, int inputCountPerResult);

}
