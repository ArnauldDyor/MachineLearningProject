from ctypes import *
import numpy as np
import os
import sys
from random import randint
import time
import cv2

# A MODOFIER
myDll = CDLL("../Shared/main.so")
PROJECT_PATH = "../."


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
    configureModelFile(0, 82)

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
    os.chdir(PROJECT_PATH)

    myDll.configureModelFile.argtype = [c_int32, c_char]

    myDll.configureModelFile.restype = c_void_p
    myDll.configureModelFile(parametre, modele)

def configureModelFileMlp(nbNeuronneFirstCouche, neuronnePerCouche, nbCouche, nbNeuronneLastCouche, type):
    os.chdir(PROJECT_PATH)

    nbNeurPointer = (c_int32 * len(neuronnePerCouche))(*neuronnePerCouche)

    myDll.configureModelFileMlp.argtype = [c_int32, POINTER(ARRAY(c_int32, len(neuronnePerCouche))), c_int32, c_int32, c_char]
    myDll.configureModelFileMlp.restype = c_void_p

    myDll.configureModelFileMlp(nbNeuronneFirstCouche, nbNeurPointer, nbCouche, nbNeuronneLastCouche, type)


def perceptron_multicouche(type, XTrain, YTrain, sampleCount, inputCountPerSample, inputCountPerResult,
                           nbNeuronnePerCouche, epochs, alpha):

    
    nbNeurPointer = (c_int32 * len(nbNeuronnePerCouche))(*nbNeuronnePerCouche)
    XTrainPointer = (c_double * len(XTrain))(*XTrain)
    YTrainPointer = (c_double * len(YTrain))(*YTrain)

    configureModelFileMlp(inputCountPerSample + 1, nbNeuronnePerCouche, len(nbNeuronnePerCouche), inputCountPerResult, ord(type))

    myDll.perceptron_multicouche.argtype = [c_char, POINTER(ARRAY(c_double, len(XTrain))),
                                            POINTER(ARRAY(c_double, len(YTrain))),
                                            c_int32, c_int32, c_int32,
                                            POINTER(ARRAY(c_int32, len(nbNeuronnePerCouche))),
                                            c_int32, c_int32, c_double]

    myDll.perceptron_multicouche.restype = c_void_p

    myDll.perceptron_multicouche(ord(type), XTrainPointer, YTrainPointer, sampleCount, inputCountPerSample,
                                 inputCountPerResult, nbNeurPointer, len(nbNeuronnePerCouche), epochs, c_double(alpha))

def trainNaifRbf(type, XTrain, YTrain, sampleCount, inputCountPerSample, inputCountPerResult, gamma):

    configureModelFile(gamma, ord(type))

    XTrainPointer = (c_double * len(XTrain))(*XTrain)
    YTrainPointer = (c_double * len(YTrain))(*YTrain)

    myDll.trainNaifRbf.argtype = [POINTER(ARRAY(c_double, len(XTrain))), POINTER(ARRAY(c_double, len(YTrain))), c_int32, c_int32, c_int32, c_double]
    myDll.trainNaifRbf.restype = c_void_p

    myDll.trainNaifRbf(XTrainPointer, YTrainPointer, sampleCount, inputCountPerSample, inputCountPerResult, c_double(gamma))

def useNaifRbf(X, XTrain, sampleCount, inputCountPerSample, inputCountPerResult):

    X = toArray(X, 1, inputCountPerSample)
    XTrain = toArray(XTrain, sampleCount, inputCountPerSample)

    XTrainPointer = (c_double * len(XTrain))(*XTrain)
    XPointer = (c_double * len(X))(*X)

    myDll.useNaifRbf.argtype = [POINTER(ARRAY(c_double, len(X))), POINTER(ARRAY(c_double, len(XTrain))), c_int32, c_int32, c_int32]
    myDll.useNaifRbf.restype = c_double

    return myDll.useNaifRbf(XPointer, XTrainPointer, sampleCount, inputCountPerSample, inputCountPerResult)


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


# utilie un modele de rosenblatt
def useRosenblatt(X):
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
    while i < len(contenu):
        contenu[i] = contenu[i][:-1]
        i += 1

    # récupération des hyper parametre
    inputCountPerSample = int(contenu[1])

    # on effectue chaque test
    results = []
    result = 0
    cursor = 0
    i = 2

    while i < len(contenu):

        result += float(contenu[i]) * X[cursor]

        cursor += 1

        if cursor == inputCountPerSample:

            results.append(result)
            result = 0
            cursor = 0

        i += 1

    #choix binaire
    if len(results) == 1:
        if results[0] < 0:
            return -1
        else:
            return 1
    else:
        return np.argmax(np.array(results))




# utilise un modele de regression lineaire
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
    while i < len(contenu):
        contenu[i] = contenu[i][:-1]
        i += 1

    # on calcul le resultat
    result = 0
    i = 2
    while i < len(contenu):
        result += float(contenu[i]) * X[i - 2]
        i += 1

    return result


# utilse un modele
def useTrainModel(X):
    os.chdir(PROJECT_PATH)

    # ouverture du fichier
    try:
        file = open("Model.txt", "r")
        contenu = file.readline(1)
        file.close()
    except Exception as e:
        print("Impossible d'ouvrir Model.txt")
        return

    if contenu == 'R':
        return useRegLinear(X)
    elif contenu == 'C':
        return useRosenblatt(X)
    else:
        return 0

def useMLP(X):
    os.chdir(PROJECT_PATH)

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
    while i < len(contenu):
        contenu[i] = contenu[i][:-1]
        i += 1

    #récupération hyper parametres
    type = contenu[0]
    nbNeuronnePerCouche = []

    cursor = 1
    while cursor < len(contenu):
        if contenu[cursor] == "|":
            cursor += 1
            break
        nbNeuronnePerCouche.append(int(contenu[cursor]))
        cursor += 1

    currentOut = X

    for couche in nbNeuronnePerCouche[1:]:

        temp = []
        for i in range(0, couche):

            result = 0
            for j in range(0, len(currentOut)):

                result += currentOut[j] * float(contenu[cursor + couche * j])

            temp.append(result)

            cursor += 1

        cursor += len(currentOut) * couche - couche
        temp = np.tanh(np.array(temp))
        currentOut = temp

    result = np.array(currentOut)

    if type == "C":
        return mlp_classif_get_classe(np.tanh(result))

    if type == "R":
        return result



# retourne classe pour classif mlp à plusiseurs classes
def mlp_classif_get_classe(results):

    #si binaire
    if len(results) == 1:
        if results[0] < 0:
            return -1
        else:
            return 1

    # si plusieurs classes

    return np.argmax(np.array(results))



def image_to_array(image):

    list_pixel = []
    for i in range(0, np.size(image, axis= 0)):
        for j in range(0, np.size(image, axis=1)):
            for rgb in image[i, j]:
                list_pixel.append(rgb)

    return list_pixel

def main():
  data = cv2.imread("../WebAPI/upload/img")
  image = image_to_array(data)
  print(useTrainModel(np.array(image)))
  sys.stdout.flush()
main()