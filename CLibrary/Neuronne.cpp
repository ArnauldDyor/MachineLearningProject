#include "Neuronne.h"

extern "C"{

    SUPEREXPORT Neuronne::Neuronne(int nbPoids, int pos){

        posInCouche = pos;
        countPoidsSortant = nbPoids;

    }

    SUPEREXPORT int Neuronne::getPosInCouche() const{
        return posInCouche;
    }

    SUPEREXPORT void Neuronne::setPoidsSortant(){

        double* poids = createLinearModel(countPoidsSortant);

        for(int i = 0; i < countPoidsSortant; i ++){
            poidsSortant.push_back(poids[i]);
        }

        free(poids);

    }

    SUPEREXPORT void Neuronne::updatePoidsSortant(vector<Neuronne> neuronnesSortant, double alpha){

        for(unsigned int i = 0; i < poidsSortant.size(); i ++){
            poidsSortant.at(i) -= alpha * getSortie() * neuronnesSortant.at(i).getSigma();
        }

    }

    SUPEREXPORT double Neuronne::getPoidsSortant(int i) const{
        return poidsSortant.at(i);
    }

    SUPEREXPORT void Neuronne::setFirstSortie(double X){
        sortie = X;
    }

    // propagation avant
    SUPEREXPORT void Neuronne::setSortie(vector<Neuronne> neuronnesEntrant){

        double somme = 0;

        for(unsigned int i = 0; i < neuronnesEntrant.size(); i ++){
            somme += neuronnesEntrant.at(i).getSortie() * neuronnesEntrant.at(i).getPoidsSortant(getPosInCouche());
        }
        sortie = tanh(somme);
    }

    SUPEREXPORT double Neuronne::getSortie() const{
        return sortie;
    }

    SUPEREXPORT void Neuronne::setSigma(char type, bool last, vector<Neuronne> neuronnesSortant, MatrixXd y){

        double value = 0;

        // si neuronne de sortie
        if(last == true){
            //calcul different pour regression ou classification
            if(type == 'C'){
                value = (1 - pow(getSortie(), 2)) * (getSortie() - y(0, getPosInCouche()));
            }
            else if(type == 'R'){
                value = getSortie() - y(0, getPosInCouche());
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
        value = (1 - pow(getSortie(), 2)) * value;
        sigma = value;

    }

    SUPEREXPORT double Neuronne::getSigma() const{
        return sigma;
    }

    SUPEREXPORT int Neuronne::getCountPoidsSortant() const{
        return countPoidsSortant;
    }

    SUPEREXPORT  double* Neuronne::createLinearModel(int nbWeight){

        double* W = new double[nbWeight];
        const int POINT = 100;
        //std::srand(std::time(0));

        for (int i = 0; i < nbWeight; i++) {

            double randVal = std::rand() % POINT;
            int powerCount = std::rand() % POINT;

            while (powerCount > 0) {
                randVal *= -1;
                powerCount -= 1;
            }

            W[i] = randVal / POINT;
        }
        cout << ">>>>> " << nbWeight << " poids crées >>>>>" << endl;
        return W;
    }
}

