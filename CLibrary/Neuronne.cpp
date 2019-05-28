#include "Neuronne.h"

extern "C"{

    Neuronne::Neuronne(double* poids, int nbPoids, int pos){

        posInCouche = pos;

        //initialisation des poids
        for(int i = 0; i < nbPoids; i ++){
            poidsSortant.push_back(poids[i]);
        }

        countPoids = nbPoids;

    }

    int Neuronne::getPosInCouche() const{
        return posInCouche;
    }

    void Neuronne::setPoidsSortant(vector<Neuronne> neuronnesSortant, double alpha){

        for(unsigned int i = 0; i < poidsSortant.size(); i ++){
            poidsSortant.at(i) -= alpha * getSortie() * neuronnesSortant.at(i).getSigma();
        }
    }

    double Neuronne::getPoidsSortant(int i) const{
        return poidsSortant.at(i);
    }

    void Neuronne::setFirstSortie(double X){
        sortie = X;
    }

    // propagation avant
    void Neuronne::setSortie(vector<Neuronne> neuronnesEntrant){

        double somme = 0;

        for(unsigned int i = 0; i < neuronnesEntrant.size(); i ++){
            somme += neuronnesEntrant.at(i).getSortie() * neuronnesEntrant.at(i).getPoidsSortant(getPosInCouche());
        }
        sortie = tanh(somme);
    }

    double Neuronne::getSortie() const{
        return sortie;
    }

    void Neuronne::setSigma(char type, bool last, vector<Neuronne> neuronnesSortant, MatrixXd YTrain){

        double value = 0;

        // si neuronne de sortie
        if(last == true){
            //calcul different pour regression ou classification
            if(type == 'C'){
                value = (1 - pow(getSortie(), 2)) * (getSortie() - YTrain(0, getPosInCouche()));
            }
            else if(type == 'R'){
                value = getSortie() - YTrain(0, getPosInCouche());
            }
            else{
                cerr << "Problème inconue : 'C' classification, 'R' régression" << endl;
            }
            sigma = value;
            return;
        }

        for(unsigned int i = 0; i < neuronnesSortant.size(); i ++){
            value += neuronnesSortant.at(i).getSigma() * getPoidsSortant(i);
        }
        value = (1 - pow(getSigma(), 2)) * value;
        sigma = value;

    }

    double Neuronne::getSigma() const{
        return sigma;
    }
}
