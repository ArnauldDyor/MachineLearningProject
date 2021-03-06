// FONCTIONS PRINCIPALES DE LA LIBRAIRIE, ACCESSIBLE DEPUIS PYTHON

#include "main.h"


extern "C"{


    SUPEREXPORT double* create_linear_model(int inputCountPerSample){

        double* W = new double[inputCountPerSample + 1];
        const int POINT = 100;

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
                   double* weight = translateMatriceData(wMat);
                   double* sample = translateMatriceData(xMat.row(k));

                   wMat += alpha * (yMat(k, 0) - predict_classification(weight, sample, inputCountPerSample))  * xMat.row(k);

                   delete_linear_model(weight);
                   delete_linear_model(sample);
                }

               cout << ">>>>> Rosenblatt classification : Weight after " << i + 1  << " epochs  :"  << wMat << " <<<<<" << endl;
            }

            writeTrainModel(wMat);

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

        writeTrainModel(wMat.transpose());

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


	SUPEREXPORT void perceptron_multicouche(char type,
                                            double* XTrain,
                                            double* YTrain,
                                            int sampleCount,
                                            int inputCountPerSample,
                                            int inputCountPerResult,
                                            int* nbNeuronnePerCouche,
                                            int nbCouche,
                                            int epochs,
                                            double alpha
       )
       {
        // création de la séquence
        seq::Sequential sequence;
        sequence.countCouche = nbCouche + 2;
        sequence.type = type;
        sequence.xtrain = XTrain;
        sequence.ytrain = YTrain;
        sequence.couches = new Couche[sequence.countCouche];

        // créeation couche cachées
        for(int i = 0; i < nbCouche; i += 1){

            Couche couche;
            couche.indexCouche = i + 1;
            couche.nbNeuronne = nbNeuronnePerCouche[i];
            couche.neuronnes = new Neuronne[couche.nbNeuronne];

            sequence.couches[i + 1] = couche;
        }

        compile(sequence, sampleCount, inputCountPerSample, inputCountPerResult);
        fit(sequence, epochs, alpha, sampleCount, inputCountPerSample, inputCountPerResult);
        writeTrainModel(vectorToMatrix(getPoids(sequence)));
        freeModele(sequence);

    }

    SUPEREXPORT void delete_linear_model(double* W)
	{
		delete[] W;
	}

	SUPEREXPORT void trainNaifRbf(double* XTrain, double* YTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult, double gamma){

        if(inputCountPerResult > 1){
            multiRbfNaif(XTrain, YTrain, sampleCount, inputCountPerSample, inputCountPerResult, gamma);
            return;
        }

        // on remplace les 0 par -1

        for(int i = 0; i < sampleCount; i += 1){
            if(YTrain[i] < 0.001 && YTrain[i] > -0.001){
                YTrain[i] = -1.0;
            }
        }

        MatrixXd weight = getWeight(getPhi(XTrain, sampleCount, inputCountPerSample, gamma), YTrain, sampleCount, inputCountPerResult);
        writeTrainModel(weight);

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

            MatrixXd Y = translateTrainingData(YTrain, sampleCount, inputCountPerResult);
            for(int i = 0; i < inputCountPerResult; i ++){
                fit_classification_rosenblatt_rule(W, XTrain, sampleCount, inputCountPerSample, 1, translateMatriceData(Y.col(i)), alpha, epochs);
            }


        }

    // rbf naif non biniare

    SUPEREXPORT void multiRbfNaif(double* XTrain, double* YTrain, int sampleCount, int inputCountPerSample, int inputCountPerResult, double gamma){
        MatrixXd Y = translateTrainingData(YTrain, sampleCount, inputCountPerResult);
        for(int i = 0; i < inputCountPerResult; i ++){
            trainNaifRbf(XTrain, translateMatriceData(Y.col(i)), sampleCount, inputCountPerSample, 1, gamma);
        }
    }


}
