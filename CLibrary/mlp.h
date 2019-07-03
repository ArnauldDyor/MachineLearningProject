#include <math.h>
#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "ModelFile.h"

using namespace std;
using namespace Eigen;

namespace seq {

	struct Neuronne{

	    double* poidsSortant;
	    double sortie;
	    double sigma;
	    int positionInCouche;
	    int countPoidsSortant;

	};

	struct Couche{

	    Neuronne* neuronnes;
	    int nbNeuronne;
	    int indexCouche;

	};

	struct Sequential{

	    Couche* couches;
	    char type;
	    double* xtrain;
	    double* ytrain;
	    int countCouche;

	};

    SUPEREXPORT void compile(Sequential sequence, int sampleCount, int inputCountPerSample, int inputCountPerResult);
	SUPEREXPORT void fit(Sequential sequence, int epochs, double alpha, int sampleCount, int inputCountPerSample, int inputCountPerResult);
	SUPEREXPORT void propagate(Sequential sequence);
	SUPEREXPORT void backPropagate(Sequential sequence, double* y);
	SUPEREXPORT void updatePoids(Sequential sequence, double alpha);
	SUPEREXPORT vector<double> getPoids(Sequential sequence);
	SUPEREXPORT double* getColonne(double* ytrain, int sampleIndex, int inputCountPerResult);
	SUPEREXPORT double* createLinearModel(int nbWeight);
	SUPEREXPORT void freeModele(Sequential sequence);
	SUPEREXPORT MatrixXd vectorToMatrix(vector<double> vect);

}
