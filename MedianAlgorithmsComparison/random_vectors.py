import sys
import random
import csv
from itertools import chain

random.seed('randomnessalgorithms')

steps = 10000
iterations = 9


if __name__ == '__main__':
    if len(sys.argv) <= 1:
        raise ValueError("random_vector.py requires one argument")

    sizes = chain(
        range(10001, 10000 + steps * iterations, steps),  # end = 100000
        range(100001, 100000 + (steps // 10) * iterations, steps // 10),  # end = 109000
        range(109001, 109000 + (steps // 100) * (iterations + 1), steps // 100)
    )

    vectors = [random.sample(range(n), n) for n in sizes]

    with open(sys.argv[1], 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerows(vectors)
