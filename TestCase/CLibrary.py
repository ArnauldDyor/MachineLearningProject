from ctypes import *

myDll = CDLL("C:/Users/utilisateur/Desktop/Projet Annuel/testLibC/bin/Release/testLibC.dll")


def create_linear_model(sampleCount):

    myDll.create_linear_model.argtypes = [c_int32]
    myDll.create_linear_model.restype = POINTER(ARRAY(c_double, sampleCount))
    weight = myDll.create_linear_model(sampleCount)
    return weight

def fit_classification_rosenblatt_rule(W, XTrain, sampleCount, inputCountPerSample, YTrain, alpha, epochs):

    WPointer = (c_double * len(W))(*W)
    XTrainPointer = (c_double * len(XTrain))(*XTrain)
    YTrainPointer = (c_double * len(YTrain))(*YTrain)

    myDll.fit_classification_rosenblatt_rule.argtypes = [POINTER(ARRAY(c_double, len(W))), POINTER(ARRAY(c_double, len(YTrain))),
                                                         c_int32, c_int32, POINTER(ARRAY(c_double, len(XTrain))), c_double, c_int32]
    myDll.fit_classification_rosenblatt_rule.restype = c_void_p
    myDll.fit_classification_rosenblatt_rule(WPointer, XTrainPointer, sampleCount, inputCountPerSample, YTrainPointer, alpha, epochs)

def fit_regression(WPointer, XTrain, sampleCount, inputCountPerSample, YTrain):

    XTrainPointer = (c_double * len(XTrain))(*XTrain)
    YTrainPointer = (c_double * len(YTrain))(*YTrain)

    myDll.fit_regression.argtypes = [POINTER(ARRAY(c_double, inputCountPerSample + 1)), POINTER(ARRAY(c_double, len(XTrain))),
                                     c_int32, c_int32, POINTER(ARRAY(c_double, len(YTrain)))]
    myDll.fit_regression.restype = c_void_p
    myDll.fit_regression(WPointer, XTrainPointer, sampleCount, inputCountPerSample, YTrainPointer)


def predict_regression(WPointer, XTrain, sampleCount, inputCountPerSample):

    XTrainPointer = (c_double * len(XTrain))(*XTrain)

    myDll.predict_regression.argtypes = [POINTER(ARRAY(c_double,  inputCountPerSample + 1)), POINTER(ARRAY(c_double, len(XTrain))), c_int32, c_int32]
    myDll.predict_regression.restype = c_double
    coef = myDll.predict_regression(WPointer, XTrainPointer, sampleCount, inputCountPerSample)
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

def outPointer(pointer, size):

    myDll.outPointer.argtypes = [POINTER(ARRAY(c_double, size)), c_int32]
    myDll.outPointer.restype = c_void_p
    myDll.outPointer(pointer, size)



