from statistics import median
import random
from math import sqrt, ceil, floor


THRESHOLD = 17  # for n < 16, sqrt(n) is greater that 0.5 n^(3/4)


def sampling_and_sorting(S):
    if len(S) < THRESHOLD:
        S.sort()
        return S[floor(len(S) / 2)]

    while True:
        n = len(S)
        samplesize = ceil(n**(3 / 4))
        R = [random.choice(S) for j in range(samplesize)]
        R.sort()
        aux = 0.5 * n ** (3 / 4)
        d = R[floor(aux - sqrt(n)) - 1]
        u = R[ceil(aux + sqrt(n)) - 1]
        C = []
        l_d, l_u = 0, 0
        for x in S:
            if x < d:
                l_d += 1
            elif x > u:
                l_u += 1
            else:
                C.append(x)
        if l_d > n / 2 or l_u > n / 2:
            continue
        if len(C) > 4 * n**(3 / 4):
            continue
        C.sort()
        return C[floor(n / 2) - l_d + 1 - 1]


if __name__ == '__main__':
    # a small example
    n = 13
    X = random.sample(range(n), n)
    print(X)
    print(median(X))
    print(sampling_and_sorting(X))
