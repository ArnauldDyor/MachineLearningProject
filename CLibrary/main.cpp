// FONCTIONS PRINCIPALES DE LA LIBRAIRIE, ACCESSIBLE DEPUIS PYTHON

#include "main.h"


extern "C"{


    SUPEREXPORT double* create_linear_model(int inputCountPerSample){

        double* W = new double[inputCountPerSample + 1];
        const int POINT = 100;
        std::srand(std::time(0));

        for (int i = 0; i < inputCountPerSample + 1; i++) {

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

    SUPEREXPORT void fit_classification_rosenblatt_rule(
            double* W,
            double* XTrain,
            int sampleCount,
            int inputCountPerSample,
            int inputCountPerResult,
            double* YTrain,
            double alpha,
            int epochs
        )
        {


            //gère le nombre de catégorie
            if(inputCountPerResult > 1){
                multiRosenblatt(W, XTrain, sampleCount, inputCountPerSample, inputCountPerResult, YTrain, alpha, epochs);
                return;
            }

            MatrixXd xMat = translateTrainingData(XTrain, sampleCount, inputCountPerSample);
            xMat = addBias(xMat);
            MatrixXd yMat = translateTrainingData(YTrain, sampleCount, 1);
            MatrixXd wMat = translateTrainingData(W, 1, inputCountPerSample + 1);

             //on harmonise les sorties
            yMat = harmonoizeResult(translateTrainingData(YTrain, sampleCount, inputCountPerResult));

            for (int i = 0; i < epochs; i++)
            {
                for (int k = 0; k < sampleCount; k++)
                {
                   wMat += alpha * (yMat(k, 0) - predict_classification(wMat.array().data(), ((xMat.row(k)).array()).data(), inputCountPerSample)) * xMat.row(k);
                }

               cout << ">>>>> Rosenblatt classification : Weight after " << i + 1 << " epochs  :"  << wMat << " <<<<<" << endl;
            }

            writeTrainModel(wMat, correctionMean(xMat, wMat));


        }


    SUPEREXPORT void fit_regression(double* W, double* XTrain, int sampleCount, int inputCountPerSample, double* YTrain){

	    MatrixXd xMat = translateTrainingData(XTrain, sampleCount, inputCountPerSample);
	    MatrixXd yMat = translateTrainingData(YTrain, sampleCount, 1);

        xMat = addBias(xMat);
        MatrixXd expr = xMat.transpose() * xMat;

        if(expr.determinant() == 0){
            expr = expr.completeOrthogonalDecomposition().pseudoInverse();
        }
        else{
            expr = expr.inverse();
        }

        MatrixXd wMat = (expr * xMat.transpose()) * yMat;

        writeTrainModel(wMat.transpose(), 0);

	}

	SUPEREXPORT double predict_regression(
		double* W,
		double* XToPredict,
		int inputCountPerSample
	)
	{
        double coef_predict = 0;
        for(int i = 0; i < inputCountPerSample + 1; i ++){
            coef_predict += W[i] * XToPredict[i];
        }

		return coef_predict < 0 ? -1.0 : 1.0;

	}

	SUPEREXPORT double predict_classification(
		double* W,
		double* XToPredict,
		int inputCountPerSample
	)
	{
		return predict_regression(W, XToPredict, inputCountPerSample) >= 0 ? 1.0 : -1.0;
	}

	SUPEREXPORT void delete_linear_model(double* W)
	{
		delete[] W;
	}

	SUPEREXPORT double useTrainModel(double* X){


        ifstream fichier("Model.txt", ios ::in);
        string line;
        string modele = "N";
        double result = -5;

        if(fichier){

            if(getline(fichier, line)){
                modele = line.c_str();
            }

            if(modele == "C"){
                result = useRosenblatt(X);
            }
            else if(modele == "R"){
                result = useRegLinear(X);
            }

            fichier.close();
        }

        return result;
	}

	// FONCTIONS INTERNES //


    //rosenblatt non binaire
    SUPEREXPORT void multiRosenblatt(
            double* W,
            double* XTrain,
            int sampleCount,
            int inputCountPerSample,
            int inputCountPerResult,
            double* YTrain,
            double alpha,
            int epochs
        )
        {
            MatrixXd sousTest(sampleCount, 2);
            MatrixXd yMat = translateTrainingData(YTrain, sampleCount, inputCountPerResult);
            MatrixXd tempXMat;
            MatrixXd  tempYMat;
            double temp;
            int noAnalyse[sampleCount];
            int countNoAnalyse = 0;

            // si la les resultats sont sur deux colonnes -> on binarise
            if(inputCountPerResult == 2){
                for(int i = 0; i < yMat.rows(); i ++){

                    temp = yMat(i, 0) * yMat(i, 0) - yMat(i, 1) * yMat(i, 1);
                    //si temp = 0 alors la categorie n'est pas analyse lors de ce test
                    if(temp == 0){
                        noAnalyse[countNoAnalyse] = i;
                        countNoAnalyse += 1;
                    }
                }

                //on retire les lignes non analysées
                tempXMat = removeLines(translateTrainingData(XTrain, sampleCount, inputCountPerSample) , noAnalyse, countNoAnalyse);
                tempYMat = removeLines(translateTrainingData(YTrain, sampleCount, 1) , noAnalyse, countNoAnalyse);
                //on lance le testCase
                fit_classification_rosenblatt_rule(W, tempXMat.array().data() , tempXMat.rows(), inputCountPerSample, 1, tempYMat.array().data(), alpha, epochs);
                return;
            }

            // si plus de deux classes
            for(int i = 0; i < inputCountPerResult; i ++){

                sousTest.col(0) << yMat.col(i);
                for(int j = i + 1; j < inputCountPerResult; j ++){

                    sousTest.col(1) << yMat.col(j);
                    fit_classification_rosenblatt_rule(W, XTrain, sampleCount, inputCountPerSample, 2, sousTest.array().data(), alpha, epochs);
                }
            }

        }


    int main(){}


}
