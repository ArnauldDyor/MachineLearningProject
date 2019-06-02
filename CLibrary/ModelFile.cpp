// FONCTIONS INTERAGISSANT AVEC LE FICHIER "Model.txt"

#include "ModelFile.h"


extern "C"{


      // CONFIGURE MODEL FILE
     SUPEREXPORT void configureModelFile(int parametre, int modele){

      ofstream fichier("Model.txt", ios::out | ios::trunc);
      char asci = (char)modele;

        if(fichier){
            fichier << asci << endl << parametre << endl;
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

                fichier.close();
            }
            else {
                    cerr << "<<<<<  Erreur lors de la création du fichier Model  <<<<<" << endl;
            }


    }


}





