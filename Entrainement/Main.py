import TrainModel as tm
import CLibrary as clib
import cv2
import os

REP = ["/home/victor/esgi/L3/Projet2019/MachineLearningProject/Dataset/FR/",
       "/home/victor/esgi/L3/Projet2019/MachineLearningProject/Dataset/US/"]


if __name__ == '__main__':



    # UNCOMENT TO TRAIN
    # TESTER EN DIVISANT PAR LE MAX (XTrain / np.max(XTrain)
    #XTrain, YTrain = tm.create_train_mat(REP)
    #tm.train_model(XTrain, YTrain, len(REP) - 1)



    #utilisation cas france
    os.chdir(REP[0])
    lt = os.listdir(REP[0])
    
    for i in range(0, 50):
        try :
            img = cv2.imread(lt[400 + i])
            img = cv2.resize(img, (100, 100))

            # si division par le max, rajouter / np.max(XTrain)
            tm.use_model(img)
        except Exception:
            print("error")