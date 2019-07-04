#include "rbfNaif.h"
#include <iostream>

extern "C"{

    SUPEREXPORT double getDistance(double* X1, double* X2, int inputCountPerSample){

        double distance = 0;

        for(int i = 0; i < inputCountPerSample; i += 1){
            distance += pow(X1[i] - X2[i], 2);
        }
        return sqrt(distance);
    }

    SUPEREXPORT double* getPhi(double* XTrain, int sampleCount, int inputCountPerSample, double gamma){

        double* phi = new double[sampleCount * sampleCount];
        int cursor = 0;

        for(int i = 0; i < sampleCount; i += 1){
            for(int j = 0; j < sampleCount; j += 1){

                phi[cursor] = exp(-gamma * pow(getDistance(getColonne(XTrain, i, inputCountPerSample), getColonne(XTrain, j, inputCountPerSample), inputCountPerSample), 2));
                cursor += 1;
            }
        }

        return phi;
    }

    SUPEREXPORT MatrixXd getWeight(double* phi, double* YTrain, int sampleCount, int inputCountPerResult){

        MatrixXd phix = translateTrainingData(phi, sampleCount, sampleCount);
        MatrixXd YMat = translateTrainingData(YTrain, sampleCount, inputCountPerResult);

        if(phix.determinant() == 0){
            phix = phix.completeOrthogonalDecomposition().pseudoInverse();
        }
        else{
            phix = phix.inverse();
        }

        MatrixXd res = phix * YMat;

        delete phi;

        return res.transpose();

    }

    // retourne la colonne d'une matrice en tableau
    SUPEREXPORT double* getColonne(double* ytrain, int sampleIndex, int inputCountPerResult){

        double* temp = new double[inputCountPerResult];

        for(int i = 0; i < inputCountPerResult; i += 1){
            temp[i] = ytrain[inputCountPerResult * sampleIndex + i];
        }

        return temp;
    }

    SUPEREXPORT double useNaifRbf(double* X, double* XTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult){

        ifstream fichier("Model.txt");

        string line;
        int cursor = 0;
        double result = 0;
        double* results = new double[inputCountPerResult];
        int indResult = 0;
        char type = '\0';

        if (fichier){

            // hyper parametre
            getline(fichier, line);
            type = line[0];
            getline(fichier, line);
            double gamma = (double)atof(line.c_str());

            // calcul resultat
            while(getline(fichier, line)){

                result += (double)atof(line.c_str()) * exp(-gamma * pow(getDistance(getColonne(X, 0, inputCountPerSample), getColonne(XTrain, cursor % sampleCount, inputCountPerSample), inputCountPerSample), 2));
                cursor += 1;

                // une classe
                if(type == 'C' && inputCountPerResult == 1 && cursor == sampleCount){
                    if(result < 0)
                        return -1.0;
                    if(result >= 0)
                        return 1.0;
                }
                // lecture de chaque modele pour plusieurs classe
                if(type == 'C' && inputCountPerResult > 1 && cursor % sampleCount == 3){
                    results[indResult] = result;
                    result = 0;
                    indResult += 1;
                }
            }

            fichier.close();
        }
        else{
            cout << "<<<<<  Erreur lors de la création du fichier Model  <<<<<" << endl;
        }

        if(type == 'C')
            return getResult(results, inputCountPerResult);

        return result;
    }

    // pour classif multi classe
    SUPEREXPORT double getResult(double* results, int inputCountPerResult){

        int argmax = 0;
        double maxi = results[0];

        for(int i = 1; i < inputCountPerResult; i += 1){
            if(maxi < results[i]){

                maxi = results[i];
                argmax = i;
            }
        }

        return argmax;

    }

}
