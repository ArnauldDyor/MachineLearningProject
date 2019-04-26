import Graphique as grp

# Ensemble de cas de test pour la régression

import CLibrary as clib

# case 1
def caseOne():
    X = [1, 2]
    Y = [2, 3]
    W = clib.create_linear_model(2)
    clib.fit_regression(W, X, 2, 1, Y)

# case 2
def caseTwo():

    X = [1, 2, 3]
    Y = [2, 3, 2.5]
    W = clib.create_linear_model(2)
    clib.fit_regression(W, X, 3, 1, Y)


def caseThree():

    X = [1, 2, 3]
    X1 = [2, 3, 2.5]
    Y = [2, 3, 2.5]
    W = clib.create_linear_model(3)
    clib.fit_regression(W, X + X1, 3, 2, Y)

def caseFour():

    X = [1, 2, 3]
    X1 = [1, 2, 3]
    Y = [1, 2, 3]
    W = clib.create_linear_model(3)
    clib.fit_regression(W, X + X1, 3, 2, Y)

def caseFive():
    X = [1, 0, 1, 0]
    X1 = [0, 1, 1, 0]
    Y = [2, 1, -2, 1]
    W = clib.create_linear_model(3)
    clib.fit_regression(W, X + X1, 3, 2, Y)









