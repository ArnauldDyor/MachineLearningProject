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
            double* YTrain,
            double alpha,
            int epochs
        )
        {
            for (int i = 0; i < epochs; i++)
            {
                for (int k = 0; k < inputCountPerSample; k++)
                {
                    W[i] = W[i] + alpha * (YTrain[k] /* - ?? */) * XTrain[k];
                }
            }
        }

    SUPEREXPORT void fit_regression(
		double* W,
		double* XTrain,
		int sampleCount,
		int inputCountPerSample,
		double* YTrain
	)
	{
	    MatrixXd xMat(inputCountPerSample, 1);
	    MatrixXd yMat(inputCountPerSample, 1);

        for(int i = 0; i < inputCountPerSample; i ++){
            yMat.row(i).col(0) << YTrain[i];
        }
        for(int i = 0; i < inputCountPerSample; i ++){
            xMat.row(i).col(0) << XTrain[i];
        }


        MatrixXd expr = xMat.transpose() * xMat;
        expr = expr.inverse();
        MatrixXd result = (expr * xMat.transpose()) * yMat;

        for(int i = 0; i < inputCountPerSample; i ++){
            W[i] = result(i);
        }

	}

	SUPEREXPORT double predict_regression(
		double* W,
		double* XToPredict,
		int inputCountPerSample
	)
	{
	    double predict_coeff = 0;                    //inference bloc
	    for(int i = 0; i < inputCountPerSample; i ++){
            predict_coeff += W[i] * XToPredict[i];
	    }
		return predict_coeff;
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

}


