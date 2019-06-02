from ctypes import *
import numpy as np
from random import randint

#A MODOFIER
myDll = CDLL("/home/victor/Programmation/C/Shared/main.so")


def create_linear_model(sampleCount):
    myDll.create_linear_model.argtypes = [c_int32]
    myDll.create_linear_model.restype = POINTER(ARRAY(c_double, sampleCount))
    weight = myDll.create_linear_model(sampleCount)
    return weight


def fit_classification_rosenblatt_rule(W, XTrain, sampleCount, inputCountPerSample, inputCountPerResult, YTrain, alpha,
                                       epochs):

    # configuration du fichier Model.txt
    configureModelFile(inputCountPerSample + 1, 67)

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
    configureModelFile(0,  82)

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



def configureModelFile(parametre, modele):
    myDll.configureModelFile.argtype = [c_int32, c_char]

    myDll.configureModelFile.restype = c_void_p
    myDll.configureModelFile(parametre, modele)


### FONCTIONS PUR PYHTON


# Transfor un np array en liste
def toArray(X, sampleCount, inputCountPerSample):
    X = X.tolist()
    if (sampleCount == 1):
        return X
    Xarray = []

    for i in range(0, sampleCount):

        for j in range(0, inputCountPerSample):
            Xarray.append(X[i][j])

    return Xarray


#utilie un modele de rosenblatt
def useRosenblatt(X):

    X = toArray(X, 1, np.size(X))

    #on ajoute biais
    X.append(1)

    #ouverture du fichier
    try:
        file = open("Model.txt", "r")
        contenu = file.readlines()
        file.close()
    except Exception as e:
        print("Impossible d'ouvrir Model.txt")
        return

    #on supprime les saut de lignes
    i = 0
    while(i < len(contenu)):
        contenu[i] = contenu[i][:-1]
        i += 1

    #récupération des hyper parametre
    inputCountPerSample = int(contenu[1])

    #on effectue chaque test
    results = []
    result = 0
    cursor = 0
    i = 2

    while(i < len(contenu)):

        result += float(contenu[i]) * X[cursor]

        cursor += 1

        if cursor == inputCountPerSample:

            if result < 0:
                result = -1
            else:
                result = 1

            results.append(result)
            result = 0
            cursor = 0

        i += 1

    #on renvoie la reponse

    #cas simple
    if(len(results) == 1):
        return results[0]

    #plusieurs classes
    positifs = []
    i = 0
    while i < len(results):
        if(results[i] > 0):
            positifs.append(i)

        i += 1

    if(len(positifs) == 1):
        return positifs[0]
    elif(len(positifs) > 0):
        return  positifs[randint(0, len(positifs) -1)]
    else:
        return randint(0, len(results) -1)

#utilise un modele de regression lineaire
def useRegLinear(X):

    X = toArray(X, 1, np.size(X))

    # on ajoute biais
    X.append(1)

    # ouverture du fichier
    try:
        file = open("Model.txt", "r")
        contenu = file.readlines()
        file.close()
    except Exception as e:
        print("Impossible d'ouvrir Model.txt")
        return

    # on supprime les saut de lignes
    i = 0
    while (i < len(contenu)):
        contenu[i] = contenu[i][:-1]
        i += 1

    #on calcul le resultat
    result = 0
    i = 2
    while i < len(contenu):

        result += float(contenu[i]) * X[i - 2]
        i += 1

    return result;


#utilse un modele
def useTrainModel(X):
    # ouverture du fichier
    try:
        file = open("Model.txt", "r")
        contenu = file.readline(1)
        file.close()
    except Exception as e:
        print("Impossible d'ouvrir Model.txt")
        return

    if contenu == 'R' :
        return useRegLinear(X)
    elif contenu == 'C':
        return useRosenblatt(X)
    else:
        return 0