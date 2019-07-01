#include "Couche.h"

extern "C" {

    SUPEREXPORT Couche::Couche(int countNeuronne, int index){
        indexCouche = index;
        nbNeuronne = countNeuronne;
    }

    SUPEREXPORT void Couche::addNeuronne(Neuronne neuronne){
        neuronnes.push_back(neuronne);
    }

    SUPEREXPORT vector<Neuronne> Couche::getNeuronnes() const{
        return neuronnes;
    }

    SUPEREXPORT int Couche::getIndexCouche() const{
        return indexCouche;
    }

    SUPEREXPORT int Couche::getNbNeuronne() const{
        return nbNeuronne;
    }


    SUPEREXPORT void Couche::replaceNeuronne(Neuronne neuronne, int pos){
        neuronnes[pos] = neuronne;
    }

}

