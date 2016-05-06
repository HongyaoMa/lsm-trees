import numpy as np

n_lines = 3*10**8
max_value = 10**10

A = range(n_lines)
A = np.random.permutation(A)
B = np.random.randint(max_value, size=len(A))

import time
t0 = time.time()

with open("output.txt", 'w') as f:
    for i, b in zip(A, B):
        f.write('{}, {}\n'.format(i, b))

print(time.time() - t0)
