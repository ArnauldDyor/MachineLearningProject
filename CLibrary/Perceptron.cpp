#include "Perceptron.h"

extern "C"{

    Perceptron::Perceptron(MatrixXd XTrain, MatrixXd YTrain, int nbCoucheCache, int neuronnePerCouche, double coef, int iteration, char modele){

        // couche d'entrée
        Couche entre(0);
        for(int i = 0; i < XTrain.cols(); i ++){
            Neuronne neuronne(createLinearModel(neuronnePerCouche), neuronnePerCouche, i);
            neuronne.setFirstSortie(XTrain(0, i));
            entre.addNeuronne(neuronne);
        }
        addCouche(entre);

        //couches cachées
        for(int i = 1; i < nbCoucheCache; i++){

            Couche cache(i);
            for(int j = 0; j < neuronnePerCouche; j++){
                Neuronne neuronne(createLinearModel(neuronnePerCouche), neuronnePerCouche, j);
                cache.addNeuronne(neuronne);
            }
            addCouche(cache);
        }

        //avant derniere couche cache
        if(nbCoucheCache > 1){
            Couche cache(nbCoucheCache);
            for(int j = 0; j < neuronnePerCouche; j++){
                Neuronne neuronne(createLinearModel(YTrain.cols()), YTrain.cols(), j);
                cache.addNeuronne(neuronne);
            }
            addCouche(cache);
        }
        //derniere couche
        Couche sortie(nbCoucheCache + 1);
        for(int i = 0; i < YTrain.cols(); i++){
            Neuronne neuronne(createLinearModel(0), 0, i);
            sortie.addNeuronne(neuronne);
        }
        addCouche(sortie);

        //taux d'apprentissage
        alpha = coef;

        //nombre d'occrence
        epochs = iteration;

        //type de probleme
        type = modele;

        //sortie
        Y = YTrain;

    }

    Perceptron::Perceptron(vector<double> poidsAfterTrain, MatrixXd XTrain, int nbCoucheCache, int neuronnePerCouche, int nbSortie){

        int indexPoids = 0;

        // couche d'entrée
        Couche entre(0);
        for(int i = 0; i < XTrain.cols(); i ++){

            Neuronne neuronne(&poidsAfterTrain[indexPoids], neuronnePerCouche, i);
            neuronne.setFirstSortie(XTrain(0, i));
            entre.addNeuronne(neuronne);
            indexPoids += neuronnePerCouche;
        }
        addCouche(entre);

        //couches cachées
        for(int i = 1; i < nbCoucheCache; i++){

            Couche cache(i);
            for(int j = 0; j < neuronnePerCouche; j++){
                Neuronne neuronne(&poidsAfterTrain[indexPoids], neuronnePerCouche, j);
                cache.addNeuronne(neuronne);
                indexPoids += neuronnePerCouche;
            }
            addCouche(cache);
        }

        //avant derniere couche
        if(nbCoucheCache > 1){
            Couche cache(nbCoucheCache);
            for(int j = 0; j < neuronnePerCouche; j++){
                Neuronne neuronne(&poidsAfterTrain[indexPoids], nbSortie, j);
                cache.addNeuronne(neuronne);
                indexPoids += nbSortie;
            }
            addCouche(cache);
        }
        //derniere couche
        Couche sortie(nbCoucheCache + 1);
        for(int i = 0; i < nbSortie; i++){
            Neuronne neuronne(createLinearModel(0), 0, i);
            sortie.addNeuronne(neuronne);
        }
        addCouche(sortie);

    }

    void Perceptron::addCouche(Couche couche){
        couches.push_back(couche);
    }

    void Perceptron::propagate(){

        for(unsigned int i = 1; i < couches.size(); i ++){

            for(unsigned int j = 0; j < couches.at(i).getNeuronnes().size(); j ++){

                couches.at(i).getNeuronnes().at(j).setSortie(couches.at(i - 1).getNeuronnes());
            }
        }
    }

    void Perceptron::backPropagate(){

        bool last = true;

        for(unsigned int i = couches.size() - 1; i > 0; i --){

            // pour le calul de a derniere couche
            if(i < couches.size() - 1){
                last = false;
            }

            for(unsigned int j = 0; j < couches.at(i).getNeuronnes().size(); j ++){

                couches.at(i).getNeuronnes().at(j).setSigma(type, last, couches.at(i - 1).getNeuronnes(), Y);
            }
        }
    }

    void Perceptron::updatePoids(){

        for(unsigned int i = 0; i < couches.size() - 1; i ++){

            for(unsigned int j = 0; j < couches.at(i).getNeuronnes().size(); j ++){

                couches.at(i).getNeuronnes().at(j).setPoidsSortant(couches.at(i + 1).getNeuronnes(), alpha);
            }
        }

    }

    vector<double> Perceptron::getPoids() const{

        vector<double> weight;

        for(unsigned int i = 0; i < couches.size() - 1; i ++){

            for(unsigned int j = 0; j < couches.at(i).getNeuronnes().size(); j ++){

                for(unsigned int k = 0; k < couches.at(i).getNeuronnes().at(j).getCountPoids(); k ++){

                    weight.push_back(couches.at(i).getNeuronnes().at(j).getPoidsSortant(k));
                }
            }

        }

        return weight;
    }

    vector<double> Perceptron::getResult() const{

        vector<double> result;
        for(unsigned int i = 0; i < couches.at(couches.size() - 1).getNeuronnes().size(); i ++){

            result.push_back(couches.at(couches.size() - 1).getNeuronnes().at(i).getSortie());
        }

        return result;
    }

    double* Perceptron::createLinearModel(int nbWeight){

        double* W = new double[nbWeight];
        const int POINT = 100;
        std::srand(std::time(0));

        for (int i = 0; i < nbWeight; i++) {

            double randVal = std::rand() % POINT;
            int powerCount = std::rand() % POINT;

            while (powerCount > 0) {
                randVal *= -1;
                powerCount -= 1;
            }

            W[i] = randVal / POINT;
        }
        return W;
    }
}
