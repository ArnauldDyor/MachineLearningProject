#include "Sequential.h"

extern "C"{

    namespace seq {

        SUPEREXPORT Sequential::Sequential(char categorie){
            type = categorie;
        }

        SUPEREXPORT void Sequential::addCouche(int nbNeuronne){
            Couche couche(nbNeuronne, couches.size() + 1);
            couches.push_back(couche);
            cout << ">>>>> Couche cachée " << couches.size() << " à " << nbNeuronne << " neuronnes >>>>>" << endl;
        }

        SUPEREXPORT void Sequential::propagate(){

            for(unsigned int i = 1; i < couches.size(); i ++){

                for(unsigned int j = 0; j < couches.at(i).getNeuronnes().size(); j ++){

                    Neuronne temp = couches.at(i).getNeuronnes().at(j);
                    temp.setSortie(couches.at(i - 1).getNeuronnes());
                    couches.at(i).replaceNeuronne(temp, j);

                }
                cout << ">>>>> Propagation avant couche: " << i + 1 << " >>>>>" << endl;
            }
        }

        SUPEREXPORT void Sequential::backPropagate(MatrixXd y){

            for(int i = couches.size() - 1; i >= 0; i -= 1){

                for(unsigned int j = 0; j < couches.at(i).getNeuronnes().size(); j ++){
                    // si dernierne couche, il 'y  a pas de neuronnes sortant
                    if(i == couches.size() - 1){

                        Neuronne temp = couches.at(i).getNeuronnes().at(j);
                        temp.setSigma(type, true, couches.at(0).getNeuronnes(), y);
                        couches.at(i).replaceNeuronne(temp, j);
                    }
                    else{

                        Neuronne temp = couches.at(i).getNeuronnes().at(j);
                        temp.setSigma(type, false, couches.at(i + 1).getNeuronnes(), y);
                        couches.at(i).replaceNeuronne(temp, j);

                    }

                }

                cout << ">>>>> Rétro-propagation couche: " << i + 1 << " >>>>>" << endl;
            }
        }

        SUPEREXPORT void Sequential::updatePoids(double alpha){

            for(unsigned int i = 0; i < couches.size() - 1; i ++){

                for(unsigned int j = 0; j < couches.at(i).getNeuronnes().size(); j ++){

                    Neuronne temp = couches.at(i).getNeuronnes().at(j);
                    temp.updatePoidsSortant(couches.at(i + 1).getNeuronnes(), alpha);
                    couches.at(i).replaceNeuronne(temp, j);

                }
                cout << ">>>>> Mise à jour des poids couche: " << i << " >>>>>" << endl;
            }

        }

        SUPEREXPORT vector<double> Sequential::getPoids() const{

            vector<double> weight;

            for(unsigned int i = 0; i < couches.size() - 1; i ++){

                for(unsigned int j = 0; j < couches.at(i).getNeuronnes().size(); j ++){

                    for(int k = 0; k < couches.at(i).getNeuronnes().at(j).getCountPoidsSortant(); k ++){

                        weight.push_back(couches.at(i).getNeuronnes().at(j).getPoidsSortant(k));

                    }
                }

            }

            return weight;
        }

        SUPEREXPORT vector<double> Sequential::getResult() const{

            vector<double> result;
            for(unsigned int i = 0; i < couches.at(couches.size() - 1).getNeuronnes().size(); i ++){

                result.push_back(couches.at(couches.size() - 1).getNeuronnes().at(i).getSortie());
            }

            return result;
        }

        SUPEREXPORT void Sequential::compile(double* XTrain, double* YTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult){

            ytrain = translateTrainingData(YTrain, sampleCount, inputCountPerResult);
            xtrain = translateTrainingData(XTrain, sampleCount, inputCountPerSample);

            //dernière couche
            Couche lastCouche(inputCountPerResult, couches.size());
            for(int i = 0; i < inputCountPerResult; i ++){
                Neuronne neuronne(0, i);
                lastCouche.addNeuronne(neuronne);
            }
            couches.push_back(lastCouche);
            cout << ">>>>> Couche sortie initialisée >>>>>" << endl;

            //premiere couche
            Couche firstCouche(inputCountPerSample + 1, 0);
            for(int i = 0; i < inputCountPerSample + 1; i ++){
                Neuronne neuronne(couches.at(0).getNbNeuronne(), i);
                neuronne.setPoidsSortant();
                firstCouche.addNeuronne(neuronne);
            }
            couches.insert(couches.begin(), firstCouche);
            cout << ">>>>> Couche d'entrée initialisée >>>>" << endl;

            //couches cachées
            for(unsigned int i = 1; i < couches.size() - 1; i += 1){

                for(int j = 0; j < couches.at(i).getNbNeuronne(); j += 1){
                    Neuronne neuronne(couches.at(i + 1).getNbNeuronne(), j);
                    neuronne.setPoidsSortant();
                    couches.at(i).addNeuronne(neuronne);

                }
                cout << ">>>>> " << i + 1 << "ème couche initilisé"  << " >>>>>"<< endl;
            }

        }

        SUPEREXPORT void Sequential::fit(int epochs, double alpha, int sampleCount){

            for(int i = 0; i < epochs; i ++){

                for(int l = 0; l < sampleCount; l += 1){

                    // charge next sample
                    int m = 0;
                    for(m = 0; m < couches.at(0).getNbNeuronne() - 1; m += 1){
                        Neuronne temp = couches.at(0).getNeuronnes().at(m);
                        temp.setFirstSortie(xtrain(l, m));
                        couches.at(0).replaceNeuronne(temp, m);
                    }
                    // biais
                    Neuronne temp = couches.at(0).getNeuronnes().at(m);
                    temp.setFirstSortie(1);
                    couches.at(0).replaceNeuronne(temp, m);
                    cout << ">>>>> Sample " << l + 1 << " charged  >>>>>" << endl;

                    Sequential::propagate();
                    cout << ">>>>> Epochs: " << i << " : Propagation avant de l'entrainement  " << l + 1 << " => OK >>>>>" << endl;

                    backPropagate(ytrain.row(l));
                    cout << ">>>>> Epochs: " << i << " : Rétro-propagation de l'entrainement  " << l + 1 << " => OK >>>>>" << endl;

                    updatePoids(alpha);
                    cout << ">>>>> Epochs: " << i << " : Mise à jour des poids de l'entrainement " << l + 1 << " => OK >>>>>" << endl;

                }
            }

            // écriture du modèle
            vector<double> poids = getPoids();
            MatrixXd poidx(1, poids.size());

            for(unsigned int i = 0; i < poids.size(); i += 1){
                poidx.row(0).col(i) << poids.at(i);
            }
            writeTrainModel(poidx);
        }
    }
}
