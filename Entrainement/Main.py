import TrainModel as tm
import cv2
import os

REP = ["/home/victor/esgi/L3/Projet2019/MachineLearningProject/Dataset/FR/",
       "/home/victor/esgi/L3/Projet2019/MachineLearningProject/Dataset/US/"]


if __name__ == '__main__':


    # UNCOMENT TO TRAIN

    XTrain, YTrain = tm.create_train_mat(REP, 500)


    #rosenblatt
    #tm.train_model(XTrain, YTrain, len(REP) - 1)
    tm.evaluateRosenblattOnTest()
    tm.evaluateRosenblattOnTrain(REP)

    #mlp
    tm.train_mlp(XTrain, YTrain, len(REP) - 1)
    # tm.evaluateMlpOnTest()
    # tm.evaluateMlpOnTrain(REP)

    #rbfNaif
    #tm.trainRbfNaif(REP, 1)
    

