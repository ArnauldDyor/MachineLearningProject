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

#include "Matrix.h"
#include "ModelFile.h"


using namespace Eigen;
using namespace std;

extern "C" {

    SUPEREXPORT double* create_linear_model(int inputCountPerSample);
    SUPEREXPORT void fit_classification_rosenblatt_rule(double* W, double* XTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult,double* YTrain, double alpha, int epochs);
    SUPEREXPORT void fit_regression(double* W, double* XTrain, int sampleCount, int inputCountPerSample, double* YTrain);
    SUPEREXPORT double predict_regression(double* W, double* XToPredict, int inputCountPerSample);
    SUPEREXPORT double predict_classification(double* W, double* XToPredict, int inputCountPerSample);
    SUPEREXPORT void delete_linear_model(double* W);
    SUPEREXPORT double useTrainModel(double* X);
    SUPEREXPORT void multiRosenblatt(double* W, double* XTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult, double* YTrain, double alpha, int epochs);

}
