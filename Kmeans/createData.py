from __future__ import print_function
import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.distance import cdist
import random
np.random.seed(18)
means = [[2, 2], [8, 3], [3, 6]]
cov = [[1, 0], [0, 1]]
N = 500
X0 = np.random.multivariate_normal(means[0], cov, N)
X1 = np.random.multivariate_normal(means[1], cov, N)
X2 = np.random.multivariate_normal(means[2], cov, N)
X = np.concatenate((X0, X1, X2), axis = 0)
K = 3 # 3 clusters
original_label = np.asarray([0]*N + [1]*N + [2]*N).T

data_with_labels = np.hstack((X, original_label.reshape(-1, 1)))
np.savetxt("data_with_labels.txt", data_with_labels, fmt="%.6f %.6f %d")

# Vẽ các cụm dữ liệu bằng scatter plot
#plt.figure(figsize=(8, 6))

#plt.scatter(X0[:, 0], X0[:, 1], c='r', label='Cluster 0')
#plt.scatter(X1[:, 0], X1[:, 1], c='g', label='Cluster 1')
#plt.scatter(X2[:, 0], X2[:, 1], c='b', label='Cluster 2')

#plt.title("Synthetic Gaussian Data (3 Clusters)")
#plt.xlabel("X1")
#plt.ylabel("X2")
#plt.legend()
#plt.grid(True)
#plt.show()
