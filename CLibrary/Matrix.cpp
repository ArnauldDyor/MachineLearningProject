// ENSEMBLE DE FONCTIONS OPERANT SUR DES MATRICES
#include "Matrix.h"

extern "C"{

    // SUPPRIME UNE COLONNE
    SUPEREXPORT MatrixXd removeColumn(MatrixXd xMat, int rang){

        MatrixXd newMat(xMat.rows(), xMat.cols() - 1);
        int j = 0;

        for(int i = 0; i < xMat.cols(); i ++){

            if(i == rang)
                continue;

            newMat.col(j) << xMat.col(i);
            j ++;
        }

        return newMat;

    }


     // POUR CENTRER LA MATRICE
     SUPEREXPORT double correctionMean(MatrixXd xMat, MatrixXd wMat){

        double mean = 0;

        for(int sampleCount = 0; sampleCount < xMat.rows(); sampleCount ++){

            for(int inputCountPerSample = 0; inputCountPerSample < xMat.cols(); inputCountPerSample ++){
                mean += (xMat(sampleCount, inputCountPerSample) * wMat(0, inputCountPerSample));
            }
        }

        return mean / xMat.rows();
    }



    // TRANSFORME UN TABLEAU EN MATRICE
	 SUPEREXPORT MatrixXd translateTrainingData(double* XTrain,  int sampleCount, int inputCountPerSample){

        MatrixXd xMat(sampleCount, inputCountPerSample);
        int cursor = 0;

        for(int i = 0; i < sampleCount; i ++){

            for(int j = 0; j < inputCountPerSample; j ++){
                xMat.row(i).col(j) << XTrain[cursor];
                cursor += 1;
            }

        }

        return xMat;

	}


	// AJOUTE BIAIS
	 SUPEREXPORT MatrixXd addBias(MatrixXd xMat){

        xMat.conservativeResize(xMat.rows(), xMat.cols() + 1);

        for(int i = 0; i < xMat.rows(); i ++){
            xMat.row(i).col(xMat.cols() - 1) << 1;
        }

        return xMat;
	}


    //SUPPRIME LES LIGNES D'UNE MATRICE DEMANDEES
     MatrixXd removeLines(MatrixXd xMat, int listIndex[], int nbIndex){

        MatrixXd newMat(xMat.rows() - nbIndex, xMat.cols());
        int rows = 0;
        int present;

        for(int i = 0; i < xMat.rows(); i ++){

            present = 0;
            for(int j = 0; j < nbIndex; j ++){

                if(i == listIndex[j]){
                    present = 1;
                    break;
                }
            }

            if(present == 0){
                newMat.row(rows) << xMat.row(i);
                rows += 1;
            }
        }

        return newMat;
    }


     //FUSIONNE DEUX COLONNES -> UNE COLNNE ENTRE -1 ET 1, POUR CLASSIFICATION
    SUPEREXPORT MatrixXd harmonoizeResult(MatrixXd yMat){

        MatrixXd newMat(yMat.rows(), yMat.cols());

         for(int i = 0; i < yMat.rows(); i ++){

            for(int j = 0; j < yMat.cols(); j += 1){
                if(yMat(i, j) == 0){
                    newMat(i, j) = -1.0;
                }
                else{
                    newMat(i, j) = yMat(i, j);
                }
            }

         }

        return newMat;
    }


}

