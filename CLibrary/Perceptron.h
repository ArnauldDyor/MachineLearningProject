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
#include "Eigen/Dense"

using namespace Eigen;

extern "C"{

    class Perceptron{

        public:
            Perceptron(MatrixXd XTrain, MatrixXd YTrain, int nbCoucheCache, int neuronnePerCouche, double coef, int iteration, char modele);
            Perceptron(vector<double> poidsAfterTrain, MatrixXd XTrain, int nbCoucheCache, int neuronnePerCouche, int nbSortie); // inserer modele entraine pour utilisation
            void addCouche(Couche couche);
            void propagate();
            void backPropagate();
            void updatePoids();
            vector<double> getPoids() const;
            vector<double> getResult() const;
            double* createLinearModel(int nbWeight);


        private:
            vector<Couche> couches;
            MatrixXd Y;
            double alpha;
            int epochs;
            char type;

    };
}
