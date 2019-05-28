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
            Neuronne(double* poids, int nbPoids, int pos);
            int getPosInCouche() const;
            void setPoidsSortant(vector<Neuronne> neuronnesSortant, double alpha); // mise à jour des poids
            double getPoidsSortant(int i) const;
            void setFirstSortie(double X); // initialisaton des Xi pour la premiere couche
            void setSortie(vector<Neuronne> neuronnesEntrant); // sigmoide
            double getSortie() const;
            void setSigma(char type, bool last, vector<Neuronne> neuronnesSortant, MatrixXd XTrain);  // rétropropagation
            double getSigma() const;
            double getCountPoids() const;

        private:
            int posInCouche;
            vector<double> poidsSortant;
            double sortie;
            double sigma;
            int countPoids;

    };

}
