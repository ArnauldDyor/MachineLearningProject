#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT
#endif

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
#include <vector>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

extern "C"{

    class Neuronne{

        public:
            SUPEREXPORT Neuronne(int nbPoids, int pos);
            SUPEREXPORT int getPosInCouche() const;
            SUPEREXPORT void setPoidsSortant();
            SUPEREXPORT void updatePoidsSortant(vector<Neuronne> neuronnesSortant, double alpha); // mise à jour des poids
            SUPEREXPORT double getPoidsSortant(int i) const;
            SUPEREXPORT void setFirstSortie(double X); // initialisaton des Xi pour la premiere couche
            SUPEREXPORT void setSortie(vector<Neuronne> neuronnesEntrant); // sigmoide
            SUPEREXPORT double getSortie() const;
            SUPEREXPORT void setSigma(char type, bool last, vector<Neuronne> neuronnesSortant, MatrixXd y);  // rétropropagation
            SUPEREXPORT double getSigma() const;
            SUPEREXPORT int getCountPoidsSortant() const;
            SUPEREXPORT double* createLinearModel(int nbWeight);

        private:
            int posInCouche;
            vector<double> poidsSortant;
            double sortie;
            double sigma;
            int countPoidsSortant;

    };

}

