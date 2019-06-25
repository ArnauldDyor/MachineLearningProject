import cv2
import CLibrary as clib
import numpy as np
import os



#traduit une cv2.image en array
def image_to_array(image):

    list_pixel = []
    for i in range(0, np.size(image, axis= 0)):
        for j in range(0, np.size(image, axis=1)):
            for rgb in image[i, j]:
                list_pixel.append(rgb)

    return list_pixel

#crééer XTrain et YTrain en fonctions d'une liste de répertoire
def create_train_mat(list_path):

    XTrain = []
    YTrain = []
    classe = 0

    if len(list_path) < 2:
        print("Un entrainement nécessite au moins deux catégorie a analyser pour être pertinent")
        return

    for rep in list_path:

        os.chdir(rep)
        list_image = os.listdir('.')
        i = 0
        while i < 300:
            try:
                image = cv2.imread(list_image[i])
                image = cv2.resize(image, (100, 100))
                pixel = image_to_array(image)
                XTrain += pixel
                YTrain.append(classe)
            except Exception:
                print("L'image : ", list_image[i], " du répertoire : " , rep, " est inutilisable.")
            i += 1

        classe += 1

    return XTrain, YTrain

def train_model(XTrain, YTrain, inputCountPerResult):

    sampleCount = int(len(YTrain) / inputCountPerResult)
    inputCountPerSample = int(len(XTrain) / sampleCount)

    W = clib.create_linear_model(inputCountPerSample)
    clib.fit_classification_rosenblatt_rule(W, XTrain, sampleCount, inputCountPerSample, inputCountPerResult, YTrain,
                                            0.01, 100)


def use_model(image):

    res = clib.useTrainModel(np.array(image_to_array(image)))
    if(res < 0):
        print("C'est la France !")
    else:
        print("C'est les USA !")






