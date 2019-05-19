from ctypes import *
import numpy as np

myDll = CDLL("/home/victor/Programmation/C/Shared/main.so")


def create_linear_model(sampleCount):
    myDll.create_linear_model.argtypes = [c_int32]
    myDll.create_linear_model.restype = POINTER(ARRAY(c_double, sampleCount))
    weight = myDll.create_linear_model(sampleCount)
    return weight


def fit_classification_rosenblatt_rule(W, XTrain, sampleCount, inputCountPerSample, inputCountPerResult, YTrain, alpha,
                                       epochs):

    # configuration du fichier Model.txt
    configureModelFile(inputCountPerResult, inputCountPerSample + 1, 67)

    XTrainPointer = (c_double * len(XTrain))(*XTrain)
    YTrainPointer = (c_double * len(YTrain))(*YTrain)

    myDll.fit_classification_rosenblatt_rule.argtypes = [POINTER(ARRAY(c_double, inputCountPerSample)),
                                                         POINTER(ARRAY(c_double, len(XTrain))),
                                                         c_int32, c_int32, c_int32,
                                                         POINTER(ARRAY(c_double, len(YTrain))), c_double, c_int32]
    myDll.fit_classification_rosenblatt_rule.restype = c_void_p
    myDll.fit_classification_rosenblatt_rule(W, XTrainPointer, sampleCount, inputCountPerSample, inputCountPerResult,
                                             YTrainPointer, alpha, epochs)


def fit_regression(WPointer, XTrain, sampleCount, inputCountPerSample, YTrain):

    # configuration du fichier Model.txt
    configureModelFile(0, inputCountPerSample, 82)

    XTrainPointer = (c_double * len(XTrain))(*XTrain)
    YTrainPointer = (c_double * len(YTrain))(*YTrain)

    myDll.fit_regression.argtypes = [POINTER(ARRAY(c_double, inputCountPerSample + 1)),
                                     POINTER(ARRAY(c_double, len(XTrain))),
                                     c_int32, c_int32, POINTER(ARRAY(c_double, len(YTrain)))]
    myDll.fit_regression.restype = c_void_p
    myDll.fit_regression(WPointer, XTrainPointer, sampleCount, inputCountPerSample, YTrainPointer)


def predict_regression(WPointer, XTrain, inputCountPerSample):
    XTrainPointer = (c_double * len(XTrain))(*XTrain)

    myDll.predict_regression.argtypes = [POINTER(ARRAY(c_double, inputCountPerSample + 1)),
                                         POINTER(ARRAY(c_double, len(XTrain))), c_int32]
    myDll.predict_regression.restype = c_double
    coef = myDll.predict_regression(WPointer, XTrainPointer, inputCountPerSample)
    return coef


def predict_classification(W, XTrain, sampleCount, inputCountPerSample):
    WPointer = (c_double * len(W))(*W)
    XTrainPointer = (c_double * len(XTrain))(*XTrain)

    myDll.predict_regression.argtypes = [POINTER(ARRAY(c_double, len(W))), POINTER(ARRAY(c_double, len(XTrain))),
                                         c_int32, c_int32]
    myDll.predict_classification.restype = c_double

    coef = myDll.predict_classification(WPointer, XTrainPointer, sampleCount, inputCountPerSample)
    return coef


def delete_linear_model(W):
    WPointer = (c_double * len(W))(*W)

    myDll.delete_linear_model.argtype = POINTER(ARRAY(c_double, len(W)))
    myDll.delete_linear_model.restype = c_void_p
    myDll.delete_linear_model(WPointer)


def useTrainModel(X):
    XPointer = (c_double * len(X))(*X)
    myDll.useTrainModel.argtype = POINTER(ARRAY(c_double, len(X)))
    myDll.useTrainModel.restype = c_double
    res = myDll.useTrainModel(XPointer)
    return res


def configureModelFile(inputCountPerResult, inputCountPerSample, modele):
    myDll.configureModelFile.argtype = [c_int32, c_int32, c_char]

    myDll.configureModelFile.restype = c_void_p
    myDll.configureModelFile(inputCountPerResult, inputCountPerSample, modele)


### FONCTIONS PUR PYHTON


def toArray(X, sampleCount, inputCountPerSample):
    X = X.tolist()
    if (sampleCount == 1):
        return X
    Xarray = []

    for i in range(0, sampleCount):

        for j in range(0, inputCountPerSample):
            Xarray.append(X[i][j])

    return Xarray