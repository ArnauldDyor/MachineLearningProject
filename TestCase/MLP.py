import CLibrary as clib
import numpy as np
import matplotlib.pyplot as plt


# classif
def case_one_classif():


    X = np.array([
        [1, 2],
        [2, 3],
        [3, 3]
    ])
    Y = np.array([
        1,
        -1,
        -1
    ])

    # affichage
    plt.scatter(X[0, 0], X[0, 1], color='blue')
    plt.scatter(X[1:3, 0], X[1:3, 1], color='red')
    plt.show()
    plt.clf()

    clib.perceptron_multicouche('C', clib.toArray(X, 3, 2), clib.toArray(Y, 1, 3), 3, 2, 1, [], 100, 0.1)
    for i in range(10, 30):
        for j in range(10, 30):
            res = clib.useMLP(np.array([i / 10, j / 10]))
            if (res > 0):
                plt.scatter(i / 10, j / 10, color="blue")
            else:
                plt.scatter(i / 10, j / 10, color="red")

    plt.show()

def case_two_classif():

    X = np.concatenate(
        [np.random.random((50, 2)) * 0.9 + np.array([1, 1]), np.random.random((50, 2)) * 0.9 + np.array([2, 2])])
    Y = np.concatenate([np.ones((50, 1)), np.ones((50, 1)) * -1.0])

    #affichage
    plt.scatter(X[0:50, 0], X[0:50, 1], color='blue')
    plt.scatter(X[50:100, 0], X[50:100, 1], color='red')
    plt.show()
    plt.clf()

    clib.perceptron_multicouche('C', clib.toArray(X, 100, 2), clib.toArray(Y, 100, 1), 100, 2, 1, [], 300, 0.1)

    SEP = np.array([[a / 10, b / 10] for a in range(10, 30) for b in range(10, 30)])
    for case in SEP:
        res = clib.useMLP(case)
        if (res > 0):
            plt.scatter(case[0], case[1], color='blue')
        else:
            plt.scatter(case[0], case[1], color='red')

    plt.show()
    plt.clf()

def case_three_classif():
    X = np.array([[1, 0], [0, 1], [0, 0], [1, 1]])
    Y = np.array([1, 1, -1, -1])

    #affichage
    plt.scatter(X[0:2, 0], X[0:2, 1], color='blue')
    plt.scatter(X[2:4, 0], X[2:4, 1], color='red')
    plt.show()
    plt.clf()

    clib.perceptron_multicouche('C', clib.toArray(X, 4, 2), clib.toArray(Y, 1, 4), 4, 2, 1, [2], 500, 0.1)

    SEP = np.array([[a / 10, b / 10] for a in range(10) for b in range(10)])
    for case in SEP:
        res = clib.useMLP(case)
        if (res < 0):
            plt.scatter(case[0], case[1], color='red')
        else:
            plt.scatter(case[0], case[1], color='blue')

    plt.show()
    plt.clf()


def case_four_classif():
    X = np.random.random((500, 2)) * 2.0 - 1.0
    Y = np.array([1 if abs(p[0]) <= 0.3 or abs(p[1]) <= 0.3 else -1 for p in X])

    plt.scatter(np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]] == 1, enumerate(X)))))[:, 0],
                np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]] == 1, enumerate(X)))))[:, 1],
                color='blue')
    plt.scatter(np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]] == -1, enumerate(X)))))[:, 0],
                np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]] == -1, enumerate(X)))))[:, 1],
                color='red')
    plt.show()
    plt.clf()

    clib.perceptron_multicouche('C', clib.toArray(X, 500, 2), clib.toArray(Y, 1, 500), 500, 2, 1, [4], 1000, 0.01)

    SEP = np.array([[a / 10, b / 10] for a in range(-10, 10) for b in range(-10, 10)])
    for case in SEP:
        res = clib.useMLP(case)
        if (res < 0):
            plt.scatter(case[0], case[1], color='red')
        else:
            plt.scatter(case[0], case[1], color='blue')

    plt.show()
    plt.clf()


def case_five_classif():
    X = np.random.random((500, 2)) * 2.0 - 1.0
    Y = np.array([[1, -1, -1] if -p[0] - p[1] - 0.5 > 0 and p[1] < 0 and p[0] - p[1] - 0.5 < 0 else
                  [-1, 1, -1] if -p[0] - p[1] - 0.5 < 0 and p[1] > 0 and p[0] - p[1] - 0.5 < 0 else
                  [-1, -1, 1] if -p[0] - p[1] - 0.5 < 0 and p[1] < 0 and p[0] - p[1] - 0.5 > 0 else
                  [-1, -1, -1] for p in X])

    plt.scatter(np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]][0] == 1, enumerate(X)))))[:, 0],
                np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]][0] == 1, enumerate(X)))))[:, 1],
                color='blue')
    plt.scatter(np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]][1] == 1, enumerate(X)))))[:, 0],
                np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]][1] == 1, enumerate(X)))))[:, 1],
                color='red')
    plt.scatter(np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]][2] == 1, enumerate(X)))))[:, 0],
                np.array(list(map(lambda elt: elt[1], filter(lambda c: Y[c[0]][2] == 1, enumerate(X)))))[:, 1],
                color='green')
    plt.show()
    plt.clf()

    clib.perceptron_multicouche('C', clib.toArray(X, 500, 2), clib.toArray(Y, 500, 3), 500, 2, 3, [], 100, 0.1)
    SEP = np.array([[a / 10, b / 10] for a in range(-10, 10) for b in range(-10, 10)])
    for case in SEP:
        res = clib.useMLP(case)
        if (res == 0):
            plt.scatter(case[0], case[1], color='blue')
        elif (res == 1):
            plt.scatter(case[0], case[1], color='red')
        elif (res == 2):
            plt.scatter(case[0], case[1], color='green')

    plt.show()
    plt.clf()


# très long
def case_six_classif():
    X = np.random.random((1000, 2)) * 2.0 - 1.0
    Y = np.array([[1, 0, 0] if abs(p[0] % 0.5) <= 0.25 and abs(p[1] % 0.5) > 0.25 else [0, 1, 0] if abs(
        p[0] % 0.5) > 0.25 and abs(p[1] % 0.5) <= 0.25 else [0, 0, 1] for p in X])

    clib.perceptron_multicouche('C', clib.toArray(X, 1000, 2), clib.toArray(Y, 1000, 3), 1000, 2, 3, [8, 8], 1000, 0.01)

    SEP = np.array([[a / 10, b / 10] for a in range(-10, 10) for b in range(-10, 10)])
    for case in SEP:
        res = clib.useMLP(case)
        if (res == 0):
            plt.scatter(case[0], case[1], color='blue')
        elif (res == 1):
            plt.scatter(case[0], case[1], color='red')
        elif (res == 2):
            plt.scatter(case[0], case[1], color='green')

    plt.show()
    plt.clf()

# REGRESSION KO

def case_one_reg():
    X = np.array([[1], [2]])
    Y = np.array([2, 3])
    clib.perceptron_multicouche('R', clib.toArray(X, 2, 1), clib.toArray(Y, 1, 2), 2, 1, 1, [], 12, 0.01)

    abscisse = np.array([[0], [1], [2], [3]])
    ordonne = []
    for abs in abscisse:
        ordonne.append(clib.useMLP(abs))

    # points initiaux
    plt.scatter(X, Y)

    plt.plot(abscisse, ordonne)
    plt.show()

def case_two_reg():
    X = np.array([
        [1],
        [2],
        [3]
    ])
    Y = np.array([
        2,
        3,
        2.5
    ])

    clib.perceptron_multicouche('R', clib.toArray(X, 3, 1), clib.toArray(Y, 1, 3), 3, 1, 1, [3], 1, 0.1)


    abscisse = np.array([[0], [1], [2], [3]])
    ordonne = []
    for abs in abscisse:
        ordonne.append(clib.useMLP(abs))

    # points initiaux
    plt.scatter(X, Y)

    plt.plot(abscisse, ordonne)
    plt.show()

