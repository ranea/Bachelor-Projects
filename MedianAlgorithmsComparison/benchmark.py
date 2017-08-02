import sys
from timeit import Timer
from functools import partial
import csv

from algorithms.quickselect import quickselect_median
from algorithms.median_of_medians import median_of_medians_median
from algorithms.sampling_and_sorting import sampling_and_sorting

REPEATS = 3
NUMBER = 1
FUNCTIONS = [quickselect_median, median_of_medians_median, sampling_and_sorting]

results = [["algorithm", "size", "time"]]


if __name__ == '__main__':
    if len(sys.argv) <= 2:
        raise ValueError("benchmark.py requires two argument")

    with open(sys.argv[1], newline='') as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        vectors = list(reader)
        for f in FUNCTIONS:
            for v in vectors:
                time = min(Timer(partial(f, v)).repeat(repeat=REPEATS, number=NUMBER))
                results.append([f.__name__, len(v), time])

    with open(sys.argv[2], 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerows(results)
