#include "Couche.h"

extern "C" {

    Couche::Couche(int index){
        indexCouche = index;
    }

    void Couche::addNeuronne(Neuronne neuronne){
        neuronnes.push_back(neuronne);
    }

    vector<Neuronne> Couche::getNeuronnes() const{
        return neuronnes;
    }

    int Couche::getIndexCouche() const{
        return indexCouche;
    }

}
