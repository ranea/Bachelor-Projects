from statistics import median
import random
from math import ceil


THRESHOLD = 5


def quickselect(X, k):
    if len(X) < THRESHOLD:
        X.sort()
        return X[k - 1]
    else:
        p = random.choice(X)
        X_l, X_r = [], []
        for x in X:
            if x < p:
                X_l.append(x)
            else:
                X_r.append(x)
        if len(X_l) >= k:
            return quickselect(X_l, k)
        elif len(X_l) + 1 < k:
            return quickselect(X_r, k - len(X_l))
        else:
            return p


def quickselect_median(X):
    return quickselect(X, ceil(len(X) / 2))


if __name__ == '__main__':
    # a small example
    n = 5
    X = random.sample(range(n), n)
    print(X)
    print(median(X))
    median_k = ceil(len(X) / 2)
    print(quickselect(X, median_k))
