from statistics import median
import random
from math import floor, ceil


THRESHOLD = 19  # higher to 19 avoid maximum recursion depth error
GROUP_SIZE = 5  # must be odd


def median_group(Y):
    Y.sort()
    return Y[floor(len(Y) / 2)]


def select_pivot(X):
    groups = [X[i:i + GROUP_SIZE] for i in range(0, len(X), GROUP_SIZE)]
    medians = [median_group(g) for g in groups]
    return median_of_medians(medians, ceil(len(medians) / 2))


def median_of_medians(X, k):
    if len(X) < THRESHOLD:
        X.sort()
        return X[k - 1]
    else:
        p = select_pivot(X)
        X_l, X_r = [], []
        for x in X:
            if x < p:
                X_l.append(x)
            else:
                X_r.append(x)
        if len(X_l) >= k:
            return median_of_medians(X_l, k)
        elif len(X_l) + 1 < k:
            return median_of_medians(X_r, k - len(X_l))
        else:
            return p


def median_of_medians_median(X):
    return median_of_medians(X, ceil(len(X) / 2))


if __name__ == '__main__':
    # a small example
    n = 7
    X = random.sample(range(n), n)
    print(X)
    print(median(X))
    median_k = ceil(len(X) / 2)
    print(median_of_medians(X, median_k))
