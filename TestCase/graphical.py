from ctypes import *
from ctypes.wintypes import *
import ctypes as ct
import matplotlib.pyplot as plt

if __name__ == "__main__":
    sampleCount = ct.c_int(4)
    inputCountPerSample = ct.c_int(2)
    alpha = ct.c_double(0.01)
    epochs = ct.c_int(2000)
    pyYTrain = [-1, 1, 1, 1]
    YTrain = (ct.c_double * len(pyYTrain))(*pyYTrain)
    pyXTrain = [0, 0, 0, 1, 1, 0, 1, 1]
    XTrain = (ct.c_double * len(pyXTrain))(*pyXTrain)


    myDll = CDLL("C:/Users/Dyor/Documents/MachineLearningProject/TestCase/libc.so")
    myDll.create_linear_model.argtypes = [ct.c_int]
    myDll.create_linear_model.restype = ct.POINTER(ct.c_double * 3)
    myDll.fit_classification_rosenblatt_rule.argtypes = [ct.POINTER(ct.c_double * 3), ct.POINTER(ct.c_double * len(pyXTrain)), ct.c_int, ct.c_int, ct.POINTER((ct.c_double))]


    W = myDll.create_linear_model(inputCountPerSample)
    myDll.fit_classification_rosenblatt_rule(W, XTrain, sampleCount, inputCountPerSample, YTrain, alpha, epochs)


    pyX1 = [0, 0]
    X1 = (ct.c_double * len(pyX1))(*pyX1)
    myDDl.predict_regression.argtypes = [ct.POINTER(ct.c_double * 3), ct.POINTER(ct.c_double * len(pyX1)), ct.c_int]
    myDll.predict_regression.restype = ct.c_double


    file = open("res.csv","w")
    XX = []
    XX2 = []
    YY = []
    YY2 = []
    for x in range(0, 100):
        for y in range(0, 100):
            pyX1 = [X/100, Y/100]
            X1 = (ct.c_double * len(pyX1))(*pyX1)
            if (myDll.predict_regression(W, X1, inputCountPerSample) >= 1.0):
                XX .append(X/100)
                YY.append(Y/100)
            else:
                XX2.append(X/100)
                YY2.append(Y/100)
            file.write(str(X) + ',' + str(Y) + ',' + str(myDll.predict_regression(W, X1, inputCountPerSample)) + '\n')


    plt.scatter(XX,YY,c = 'blue')
    plt.scatter(XX2,YY2,c = 'red')
    plt.show
