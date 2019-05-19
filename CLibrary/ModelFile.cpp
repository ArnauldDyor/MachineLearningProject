// FONCTIONS INTERAGISSANT AVEC LE FICHIER "Model.txt"

#include "ModelFile.h"


extern "C"{


      SUPEREXPORT double useRegLinear(double* X){

        ifstream fichier("Model.txt", ios ::in);
        string line;
        double result = 0;
        int weightSize = 0;

        if(fichier){

            int cursor = 0;

            while(getline(fichier, line)){

                if(cursor == 0 || cursor == 1){
                    cursor += 1;
                    continue;
                }
                else if(cursor == 2){
                    cursor += 1;
                    weightSize = (int)atof(line.c_str());
                    continue;
                }
                // si dernier poids
                else if(cursor - weightSize == 3){
                   result += (double)atof(line.c_str());
                   break;
                }

                result += ((double)atof(line.c_str())) * X[cursor - 3];
                cursor += 1;
            }

            fichier.close();
        }

        return result;
    }

     SUPEREXPORT double useRosenblatt(double* X){

        ifstream fichier("Model.txt", ios ::in);
        string line;
        std::srand(std::time(0));

        double res = 0;
        int weight = 1;
        int counter = 0;
        int inputCountPerResult = 0;
        int inputCountPerSample = 0;

        if(fichier){

            //saut de la premiere ligne
            getline(fichier, line);

            // recuperation hyper-parametre
            if(getline(fichier, line)){

                inputCountPerResult = (int)atof(line.c_str());

                if(getline(fichier, line)){
                    inputCountPerSample = (int)atof(line.c_str());
                }
            }
            else{
                cerr << ">>>>> INVALID STRUCTURE OF Model.txt <<<<<" << endl;
                return 0;
            }

            // On effectue chaque test
            double result[inputCountPerResult];
            int cursorResult = 0;

            while(getline(fichier, line)){

                // centre
                if(weight == 0){

                    result[cursorResult] = ((res - atof(line.c_str())) < 0 ? -1.0 : 1.0);
                    // si choix binaire : return -1 ou 1 sinon return 0, 1, 2
                    if(inputCountPerResult == 1)
                        return result[0];

                    cursorResult += 1;
                    weight = 1;
                    counter = 0;
                }
                if(line == "|"){
                    weight = 0;
                }

                // applique poids
                if(counter < inputCountPerSample - 1)   { res += atof(line.c_str()) * X[counter]; }
                if(counter == inputCountPerSample - 1)  { res += atof(line.c_str()); }
                counter += 1;
            }

            fichier.close();

            return getClasse(result, inputCountPerResult);


        }

        return 0;
    }


      // CONFIGURE MODEL FILE
     SUPEREXPORT void configureModelFile(int inputCountPerResult, int inputCountPerSample, int modele){

      ofstream fichier("Model.txt", ios::out | ios::trunc);
      char asci = (char)modele;

        if(fichier){
            fichier << asci << endl << inputCountPerResult << endl << inputCountPerSample << endl;
            fichier.close();
        }
    }

    // ECRIT LE MODELE DANS UN FICHIER
     SUPEREXPORT void writeTrainModel(MatrixXd wMat, double average){

            ofstream fichier("Model.txt", ios::out | ios::app);
            string line;

            if(fichier){

                for(int i = 0; i < wMat.cols(); i ++){
                    fichier << wMat(0, i) << endl;
                }

                fichier << "|" << endl;

                fichier << average << endl;

                fichier.close();
            }
            else {
                    cerr << "<<<<<  Erreur lors de la création du fichier Model  <<<<<" << endl;
            }

            return;


    }

     // evalue les scores des differents test dans une classification > 2 colonnes
     SUPEREXPORT double getClasse(double result[], int inputCountPerResult){

        double score[inputCountPerResult];
        int match = 0;
        int maxi = -1;
        int index = 0;

        //on intitalise les scores à 0
        for(int i = 0; i < inputCountPerResult; i ++){
            score[i] = 0;
        }
        //on disribue les scores
        for(int i = 0; i < inputCountPerResult; i ++){

            for(int j = i + 1; j < inputCountPerResult; j ++){
                if(result[match] == 1){
                    score[i] = score[i] + 1;
                }
                else{
                    score[j] = score[j] + 1;
                }
                match += 1;
            }
        }
        // on cherche le maximum
        for(int i = 0; i < inputCountPerResult; i ++){
            if(score[i] > maxi){
                maxi = score[i];
                index = i;
            }
        }

        return index;

    }


}



