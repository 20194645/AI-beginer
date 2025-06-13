from __future__ import print_function
import numpy as np
from time import time

# Kích thước: 100 chiều, 1000 điểm
d, N = 100, 1000

# Sinh dữ liệu ngẫu nhiên
X = np.random.randn(N, d)  # Ma trận X: 1000 x 100
z = np.random.randn(d)     # Vector z: 100 chiều

# Lưu ma trận X vào file
np.savetxt('X.txt', X, fmt='%.6f')

# Lưu vector z vào file (1 dòng, 100 cột)
np.savetxt('z.txt', z.reshape(1, -1), fmt='%.6f')
