import numpy as np

n_lines = 1*10**1
max_value = 10**2

A = range(n_lines)
A = np.random.permutation(A) + 9*n_lines
B = np.random.randint(max_value, size=len(A))

import time
t0 = time.time()

with open("output_small_9.csv", 'w') as f:
    for i, b in zip(A, B):
        f.write('{}, {}\n'.format(i, b))

print(time.time() - t0)
