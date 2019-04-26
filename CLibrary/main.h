#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT
#endif


#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Eigen/Dense"


using namespace Eigen;
using namespace std;

extern "C" {
    SUPEREXPORT double* create_linear_model(int inputCountPerSample);
    SUPEREXPORT void fit_classification_rosenblatt_rule(double* W, double* XTrain, int sampleCount, int inputCountPerSample, double* YTrain, double alpha, int epochs);
    SUPEREXPORT void fit_regression(double* W, double* XTrain, int sampleCount, int inputCountPerSample, double* YTrain);
    SUPEREXPORT double predict_regression(double* W, double* XToPredict, int sampleCount, int inputCountPerSample);
    SUPEREXPORT double predict_classification(double* W, double* XToPredict,int sampleCount, int inputCountPerSample);
    SUPEREXPORT void delete_linear_model(double* W);
    SUPEREXPORT MatrixXd translateTrainingData(double* XTrain,  int sampleCount, int inputCountPerSample);
    SUPEREXPORT MatrixXd addBias(MatrixXd xMat);
}
