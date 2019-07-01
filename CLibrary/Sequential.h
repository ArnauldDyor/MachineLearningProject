#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT
#endif

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>
#include "Couche.h"
#include "Matrix.h"
#include "ModelFile.h"
#include "Eigen/Dense"

using namespace Eigen;

extern "C"{

    namespace seq{


        class Sequential{

            public:
                SUPEREXPORT Sequential(char categorie);
                SUPEREXPORT void addCouche(int nbNeuronne);
                SUPEREXPORT void propagate();
                SUPEREXPORT void backPropagate(MatrixXd y);
                SUPEREXPORT void updatePoids(double alpha);
                SUPEREXPORT vector<double> getPoids() const;
                SUPEREXPORT vector<double> getResult() const;
                SUPEREXPORT void compile(double* XTrain, double* YTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult);
                SUPEREXPORT void fit(int epochs, double coef, int sampleCount);

            private:
                vector<Couche> couches;
                MatrixXd xtrain;
                MatrixXd ytrain;
                char type;

        };
    }
}


