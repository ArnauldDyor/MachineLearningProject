import cv2
import CLibrary as clib
import numpy as np
import os

# à changer : Chemin du dossier où se situe l'executable
PROJECT_PATH = "/home/victor/Programmation/python/FlagAnalyse/"
# à changer : Crééer 2 dossiers pour l'entrainement et y placer les 50 dernières images de chaques pays du Dataset
# Il est important que REP_TEST[0] = France et [1] = USA
REP_TEST = ["/home/victor/esgi/L3/Projet2019/MachineLearningProject/Train/FR/",
            "/home/victor/esgi/L3/Projet2019/MachineLearningProject/Train/US/"]


# traduit une cv2.image en array
def image_to_array(image):
    list_pixel = []
    for i in range(0, np.size(image, axis=0)):
        for j in range(0, np.size(image, axis=1)):
            for rgb in image[i, j]:
                list_pixel.append(rgb / 255)

    return list_pixel


# crééer XTrain et YTrain en fonctions d'une liste de répertoire
def create_train_mat(list_path, picturePerRep):
    XTrain = []
    YTrain = []
    classe = -1

    if len(list_path) < 2:
        print("Un entrainement nécessite au moins deux catégorie a analyser pour être pertinent")
        return

    for rep in list_path:

        os.chdir(rep)
        list_image = os.listdir('.')
        i = 0
        # nombre de photos analyser par répertoire
        while i < picturePerRep:
            try:
                image = cv2.imread(list_image[i])
                image = cv2.resize(image, (100, 100))
                pixel = image_to_array(image)
                XTrain += pixel
                YTrain.append(classe)
            except cv2.error:
                print("L'image : ", list_image[i], " du répertoire : ", rep, " est inutilisable.")
            i += 1

        classe = 1

    return XTrain, YTrain


""" MLP """


# Entraine un perceptron multicouche : neuronnes par couche, epochs et apha à modifier
def train_mlp(XTrain, YTrain, inputCountPerResult):
    sampleCount = int(len(YTrain) / inputCountPerResult)
    inputCountPerSample = int(len(XTrain) / sampleCount)
    clib.perceptron_multicouche('C', XTrain, YTrain, sampleCount, inputCountPerSample, inputCountPerResult, [2, 2],
                                10000, 0.1)


# recoit une array de pixel et rtorne le resultat
def use_mlp(image):
    res = clib.useMLP(np.array(image_to_array(image)))
    if res < 0:
        print("C'est la France !")
    else:
        print("C'est les USA !")


# évalue un mlp sur des données de test
def evaluateMlpOnTest():
    error = 0
    read = 0
    answer = -1.0

    for rep in REP_TEST:
        for i in range(0, 50):

            # utilisation cas france
            os.chdir(rep)
            lt = os.listdir(rep)

            try:
                img = cv2.imread(lt[i])
                img = cv2.resize(img, (100, 100))
                res = clib.useMLP(np.array(image_to_array(img)))
                if (res > 0 > answer) or (res < 0 < answer):
                    error += 1
                read += 1
            except cv2.error:
                print("Unreadable picture")

        answer = 1

    print("Erreur on test data: ", round((error / read) * 100, 2), "%")


# évalue un mlp sur des données d'entrainement
def evaluateMlpOnTrain(REP):
    error = 0
    read = 0
    answer = -1.0

    for rep in REP:
        for i in range(0, 50):

            # utilisation cas france
            os.chdir(rep)
            lt = os.listdir(rep)

            try:
                img = cv2.imread(lt[i])
                img = cv2.resize(img, (100, 100))
                res = clib.useMLP(np.array(image_to_array(img)))
                if (res > 0 > answer) or (res < 0 < answer):
                    error += 1
                read += 1
            except cv2.error:
                print("Unreadable picture")

        answer = 1

    print("Erreur on training data: ", round((error / read) * 100, 2), "%")


""" RBF NAIF """


# entraine un rbf, gamma à changer et la taille de XTrain !
def trainRbfNaif(rep, inputCountPerResult):
    XTrain, YTrain = create_train_mat(rep, 3)
    sampleCount = int(len(YTrain) / inputCountPerResult)
    inputCountPerSample = int(len(XTrain) / sampleCount)
    clib.trainNaifRbf('C', XTrain, YTrain, sampleCount, inputCountPerSample, inputCountPerResult, 500)

    for i in range(0, 20):
        os.chdir(rep[1])
        lt = os.listdir(rep[1])

        img = cv2.imread(lt[300 + i])
        img = cv2.resize(img, (100, 100))

        os.chdir(PROJECT_PATH)
        print(clib.useNaifRbf(np.array(image_to_array(img)), XTrain, inputCountPerSample, sampleCount,
                              inputCountPerResult))


""" ROSENBLAT """


# entraiine un modèle linéaire : à changer epochs et alpha
def train_model(XTrain, YTrain, inputCountPerResult):
    sampleCount = int(len(YTrain) / inputCountPerResult)
    inputCountPerSample = int(len(XTrain) / sampleCount)

    W = clib.create_linear_model(inputCountPerSample)
    clib.fit_classification_rosenblatt_rule(W, XTrain, sampleCount, inputCountPerSample, inputCountPerResult, YTrain,
                                            0.1, 1000)


# recoit une array de pixel et rtorne le resultat
def use_model(image):
    res = clib.useTrainModel(np.array(image_to_array(image)))
    if (res < 0):
        print("C'est la France !")
    else:
        print("C'est les USA !")


# évalue rosenblatt sur des données de test
def evaluateRosenblattOnTest():
    error = 0
    read = 0
    answer = -1.0

    for rep in REP_TEST:
        for i in range(0, 50):

            # utilisation cas france
            os.chdir(rep)
            lt = os.listdir(rep)

            try:
                img = cv2.imread(lt[i])
                img = cv2.resize(img, (100, 100))
                res = clib.useTrainModel(np.array(image_to_array(img)))
                if (res > 0 > answer) or (res < 0 < answer):
                    error += 1
                read += 1
            except cv2.error:
                print("Unreadable picture")

        answer = 1

    print("Erreur on test data: ", round((error / read) * 100, 2), "%")


# évalue rosenblatt sur des données d'entrainement
def evaluateRosenblattOnTrain(REP):
    error = 0
    read = 0
    answer = -1.0

    for rep in REP:
        for i in range(0, 50):

            # utilisation cas france
            os.chdir(rep)
            lt = os.listdir(rep)

            try:
                img = cv2.imread(lt[i])
                img = cv2.resize(img, (100, 100))
                res = clib.useTrainModel(np.array(image_to_array(img)))
                if (res > 0 > answer) or (res < 0 < answer):
                    error += 1
                read += 1
            except cv2.error:
                print("Unreadable picture")

        answer = 1

    print("Erreur on training data: ", round((error / read) * 100, 2), "%")
