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
            Couche(int index);
            void addNeuronne(Neuronne neuronne);
            vector<Neuronne> getNeuronnes() const;
            int getIndexCouche() const;

        private:
            vector<Neuronne> neuronnes;
            int indexCouche;

    };


}
