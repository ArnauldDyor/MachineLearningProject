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
#include "Neuronne.h"

using namespace std;

extern "C"{

    class Couche{

        public:
            SUPEREXPORT Couche(int countNeuronne, int index);
            SUPEREXPORT void addNeuronne(Neuronne neuronne);
            SUPEREXPORT vector<Neuronne> getNeuronnes() const;
            SUPEREXPORT int getIndexCouche() const;
            SUPEREXPORT int getNbNeuronne() const;
            SUPEREXPORT void replaceNeuronne(Neuronne neuronne, int pos);

        private:
            vector<Neuronne> neuronnes;
            int indexCouche;
            int nbNeuronne;

    };


}

