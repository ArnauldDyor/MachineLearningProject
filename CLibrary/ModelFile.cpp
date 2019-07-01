// FONCTIONS INTERAGISSANT AVEC LE FICHIER "Model.txt"

#include "ModelFile.h"


extern "C"{


      // CONFIGURE Model.txt (pour classif et regresion)
     SUPEREXPORT void configureModelFile(int parametre, int modele){

      ofstream fichier("Model.txt", ios::out | ios::trunc);
      char asci = (char)modele;

        if(fichier){
            fichier << asci << endl << parametre << endl;
            fichier.close();
        }
    }

    // CONFIGURE Model.txt (pour mlp)
    SUPEREXPORT void configureModelFileMlp(int nbNeuronneFirstCouche, int* neuronnePerCouche, int nbCouche, int nbNeuronneLastCouche, char type){

        ofstream fichier("Model.txt", ios::out | ios::trunc);

        if(fichier){

            fichier << type << endl;
            fichier << nbNeuronneFirstCouche + 1 << endl;

            for(int i = 0; i < nbCouche; i += 1){
                fichier << neuronnePerCouche[i] << endl;
            }
            fichier << nbNeuronneLastCouche << endl << "|" << endl;
            fichier.close();

        }

    }

    // ECRIT LE MODELE DANS UN FICHIER
     SUPEREXPORT void writeTrainModel(MatrixXd wMat){

            ofstream fichier("Model.txt", ios::out | ios::app);

            if(fichier){

                for(int i = 0; i < wMat.cols(); i ++){
                    fichier << wMat(0, i) << endl;
                }

                cout << "Ecriture du modèle réussit" << endl;
                fichier.close();
            }
            else {
                    cout << "<<<<<  Erreur lors de la création du fichier Model  <<<<<" << endl;
            }


    }


}






