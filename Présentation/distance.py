import os
import cv2
import TrainModel as tm

#chemin de l'actuel projet
PROJECT_PATH = "/home/victor/Programmation/python/testGit/"


# recoit une liste de rgb et l'écrit dans Model.txt
def writeModel(franceRgb, usaRgb):
    # ouverture du fichier

    os.chdir(PROJECT_PATH)
    os.remove("Model.txt")

    with open("Model.txt", "a") as model:
        for rgb in franceRgb:
            model.write(str(rgb) + "\n")

        model.write("|\n")

        for rgb in usaRgb:
            model.write(str(rgb) + "\n")


# recoit les chemins des representants et eccrit le modele
def distanceModel(francePath, usaPath):
    try:
        francePicture = cv2.imread(francePath)
        francePicture = cv2.resize(francePicture, (100, 100))
        franceRgb = tm.image_to_array(francePicture)
    except cv2.error:
        print("Impossible de trouver: ", francePath)
        return -1

    try:
        usaPicture = cv2.imread(usaPath)
        usaPicture = cv2.resize(usaPicture, (100, 100))
        usaRgb = tm.image_to_array(usaPicture)
    except cv2.error:
        print("Impossible de trouver: ", usaPath)
        return -1

    writeModel(franceRgb, usaRgb)


# recoit une array de rgb et retourne le resultat
def useDistance(X):
    try:
        file = open("Model.txt", "r")
        contenu = file.readlines()
        file.close()
    except Exception as e:
        print("Impossible d'ouvrir Model.txt")
        return

    distUsa = 0
    distFrance = 0
    activeDist = 0
    i = 0
    cursor = 0

    while i < len(contenu):

        if contenu[i] == "|\n":
            distFrance = activeDist
            activeDist = 0
            cursor = 0
            i += 1
            continue

        activeDist += (X[cursor] - float(contenu[i])) ** 2
        i += 1
        cursor += 1

    distUsa = activeDist

    print("Distance euclidienne avec la france : ", round(distFrance, 2))
    print("Distance euclidienne avec les USA : ", round(distUsa, 2))

    if distFrance ** 0.5 < distUsa ** 0.5:
        print("C'est la france")
        return -1
    else:
        print("C'est les USA")
        return 1