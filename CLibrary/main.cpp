#include "main.h"

// NE PAS HESITER A CORRIGER OU COMPARER AVEC DES CONNAISSANCES, JE NE SUI SUR DE RIEN
// TROUVER UN MOYEN DE RECUP LES W DANS LE CODE PYTHON SERAIT BIENVENUE

extern "C"{

    SUPEREXPORT double* create_linear_model(int sampleCount){

        double* W = new double[sampleCount + 1];
        const int POINT = 100;
        std::srand(std::time(0));

        for (int i = 0; i < sampleCount + 1; i++) {

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

    // A TESTER ET CORRIGER, GROS DOUTES
    SUPEREXPORT void fit_classification_rosenblatt_rule(
            double* W,
            double* XTrain,
            int sampleCount,
            int inputCountPerSample,
            double* YTrain,
            double alpha,
            int epochs
        )
        {
            for (int i = 0; i < epochs; i++)
            {
                for (int k = 0; k < sampleCount; k++)
                {
                    W[i] = W[i] + alpha * (YTrain[k]  - predict_classification(W, XTrain, sampleCount, inputCountPerSample)) * XTrain[k];
                }
            }
        }

    // SEMBLE BIEN FONCTIONNER

    SUPEREXPORT void fit_regression(
		double* W,
		double* XTrain,
		int sampleCount,
		int inputCountPerSample,
		double* YTrain
	)
	{
	    MatrixXd xMat = translateTrainingData(XTrain, sampleCount, inputCountPerSample);
	    xMat = addBias(xMat);
	    MatrixXd yMat(sampleCount, 1);

        for(int i = 0; i < sampleCount; i ++){
            yMat.row(i).col(0) << YTrain[i];
        }

        MatrixXd expr = xMat.transpose() * xMat;
        expr = expr.inverse();
        MatrixXd result = (expr * xMat.transpose()) * yMat;

        // SORTIE TEMPORAIRE, POUR VOIRE RAPIDEMENT LES POIDS
        cout << result;

        for(int i = 0; i < result.cols(); i ++){
            W[i] = result(i);
        }

	}

    // SEMBLE FONCTIONNER MAIS A QUOI SERT - ELLE ??
	SUPEREXPORT double predict_regression(
		double* W,
		double* XToPredict,
		int sampleCount,
		int inputCountPerSample
	)
	{
		MatrixXd xMat = translateTrainingData(XToPredict, sampleCount, inputCountPerSample);
		xMat = addBias(xMat);

		MatrixXd wMat = translateTrainingData(W, sampleCount, 1);

		MatrixXd result = wMat.transpose() * xMat;

		double coef_predict = result(0, 0);

		return coef_predict < 0 ? -1.0 : 1.0;

	}

	SUPEREXPORT double predict_classification(
		double* W,
		double* XToPredict,
		int inputCountPerSample,
		int sampleCount
	)
	{
		return predict_regression(W, XToPredict, sampleCount, inputCountPerSample) >= 0 ? 1.0 : -1.0;
	}

	SUPEREXPORT void delete_linear_model(double* W)
	{
		delete[] W;
	}

	// FONCTIONS INTERNES //

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


}


