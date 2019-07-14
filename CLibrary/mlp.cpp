#include "mlp.h"

namespace seq {

    // construction du modèle
    SUPEREXPORT void compile(Sequential sequence, int sampleCount, int inputCountPerSample, int inputCountPerResult){

        //dernière couche
        Couche last;
        last.indexCouche = sequence.countCouche - 1;
        last.nbNeuronne = inputCountPerResult;
        last.neuronnes = new Neuronne[last.nbNeuronne];

        for(int i = 0; i < inputCountPerResult; i += 1){
            Neuronne neuronne;
            neuronne.countPoidsSortant = 0;
            neuronne.positionInCouche = i;
            last.neuronnes[i] = neuronne;
        }
        sequence.couches[sequence.countCouche - 1] = last;

        //premiere couche
        Couche first;
        first.indexCouche = 0;
        first.nbNeuronne = inputCountPerSample + 1;
        first.neuronnes = new Neuronne[first.nbNeuronne];

        for(int i = 0; i < inputCountPerSample + 1; i += 1){
            Neuronne neuronne;
            neuronne.countPoidsSortant = sequence.couches[1].nbNeuronne;
            neuronne.positionInCouche = i;
            neuronne.poidsSortant = createLinearModel(neuronne.countPoidsSortant);
            first.neuronnes[i] = neuronne;
        }
        sequence.couches[0] = first;
	
        //couches cachées
        for(int i = 1; i < sequence.countCouche - 1; i += 1){
		
            for(int j = 0; j < sequence.couches[i].nbNeuronne; j += 1){

                Neuronne neuronne;
                neuronne.countPoidsSortant = sequence.couches[i + 1].nbNeuronne;
                neuronne.positionInCouche = j;
                neuronne.poidsSortant = createLinearModel(neuronne.countPoidsSortant);
                sequence.couches[i].neuronnes[j] = neuronne;
		
            }

        }


    }

    // entrainement
    SUPEREXPORT void fit(Sequential sequence, int epochs, double alpha, int sampleCount, int inputCountPerSample, int inputCountPerResult){


        for(int i = 0; i < epochs; i += 1){

            for(int j = 0; j < sampleCount; j += 1){

                // charge next sample

                int k = 0;
                for(int k = 0; k < sequence.couches[0].nbNeuronne - 1; k += 1){
                    sequence.couches[0].neuronnes[k].sortie = sequence.xtrain[j * inputCountPerSample + k];
                }
                // biais
                sequence.couches[0].neuronnes[sequence.couches[0].nbNeuronne - 1].sortie = 1;

                propagate(sequence);

                backPropagate(sequence, getColonne(sequence.ytrain, j, inputCountPerResult));

                updatePoids(sequence, alpha);


            }

            cout << i + 1 << " Itérations => OK" << endl;

        }

    }

    // propagation avant
    SUPEREXPORT void propagate(Sequential sequence){

        for(int i = 1; i < sequence.countCouche; i += 1){

            for(int j = 0; j < sequence.couches[i].nbNeuronne; j += 1){
	
                double somme = 0;
		
                for(int k = 0; k < sequence.couches[i - 1].nbNeuronne; k ++){
                    somme += sequence.couches[i - 1].neuronnes[k].sortie * sequence.couches[i - 1].neuronnes[k].poidsSortant[j];
                }
	
                sequence.couches[i].neuronnes[j].sortie = tanh(somme);
		
            }
        }

    }
	
    // rétro propagation
    SUPEREXPORT void backPropagate(Sequential sequence, double* y){
	
        for(int i = sequence.countCouche - 1; i >= 0; i -= 1){

            for(int j = 0; j < sequence.couches[i].nbNeuronne; j += 1){

                double value = 0;

                // si dernière couche
                if(i == sequence.countCouche - 1){

                    if(sequence.type == 'C'){
                        value = (1 - pow(sequence.couches[i].neuronnes[j].sortie, 2)) * (sequence.couches[i].neuronnes[j].sortie - y[j]);
                    }
                    else if(sequence.type == 'R'){
                        value = sequence.couches[i].neuronnes[j].sortie - y[j];
                    }
                    else{
                        cerr << "Problème inconue : 'C' classification, 'R' régression" << endl;
                    }
                    sequence.couches[i].neuronnes[j].sigma = value;
                }
                else{

                    for(int k = 0; k < sequence.couches[i + 1].nbNeuronne; k += 1){
                        value += sequence.couches[i + 1].neuronnes[k].sigma * sequence.couches[i].neuronnes[j].poidsSortant[k];
                    }
                    value = (1 - pow(sequence.couches[i].neuronnes[j].sortie, 2)) * value;
                    sequence.couches[i].neuronnes[j].sigma = value;
                }
            }
        }

        delete[] y;
    }

    // met à jour les poids
    SUPEREXPORT void updatePoids(Sequential sequence, double alpha){

        for(int i = 0; i < sequence.countCouche - 1; i += 1){

            for(int j = 0; j < sequence.couches[i].nbNeuronne; j += 1){

                for(int k = 0; k < sequence.couches[i].neuronnes[j].countPoidsSortant; k += 1){

                    sequence.couches[i].neuronnes[j].poidsSortant[k] -= alpha * sequence.couches[i].neuronnes[j].sortie * sequence.couches[i + 1].neuronnes[k].sigma;
                }

            }

        }

    }

    // crééer les poids
    SUPEREXPORT double* createLinearModel(int nbWeight){

        double* W = new double[nbWeight];
        const int POINT = 100;

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

   // retourne tous les poids du modèle
   SUPEREXPORT vector<double> getPoids(Sequential sequence){

        vector<double> poids;

        for(int i = 0; i < sequence.countCouche - 1; i += 1){

            for(int j = 0; j < sequence.couches[i].nbNeuronne; j += 1){

                for(int k = 0; k < sequence.couches[i].neuronnes[j].countPoidsSortant; k += 1){

                   poids.push_back(sequence.couches[i].neuronnes[j].poidsSortant[k]);

                }

            }

        }

        return poids;

    }
    
    // retourne un tableau représentant une colonne d'un autre tableau
    SUPEREXPORT double* getColonne(double* ytrain, int sampleIndex, int inputCountPerResult){

        double* temp = new double[inputCountPerResult];

        for(int i = 0; i < inputCountPerResult; i += 1){
            temp[i] = ytrain[inputCountPerResult * sampleIndex + i];
        }

        return temp;
    }
	
    // libère la mémoire alloué
    SUPEREXPORT void freeModele(Sequential sequence){


        for(int i = 0; i < sequence.countCouche - 1; i += 1){

            for(int j = 0; j < sequence.couches[i].nbNeuronne; j += 1){

                // libere poids sortants
		delete[] sequence.couches[i].neuronnes[j].poidsSortant;
            }

            // libere les neuronnes
            delete[] sequence.couches[i].neuronnes;

        }

        // libere le modèle
        delete[] sequence.couches;

    }

    // convertit un vecteur en matrixXd pour écrire le modèle
    SUPEREXPORT MatrixXd vectorToMatrix(vector<double> vect){

        MatrixXd matx(1, vect.size());

        for(unsigned int i = 0; i < vect.size(); i += 1){
            matx.row(0).col(i) << vect.at(i);
        }

        return matx;
    }

}


