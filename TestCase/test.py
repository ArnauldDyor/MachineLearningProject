import numpy as np
import tensorflow as tf
import matplotlib
import CLibrary.py


model = tf.keras.Sequential()
#model.add(tf.keras.layers.Dense(1, activation=tf.keras.activations.sigmoid, input_shape(2,)))


X = np.array([
    [1, 1],
    [2, 3],
    [3, 3]
])
Y = np.array([
    1,
    -1,
    -1
])