import unittest
import random
from statistics import median

from hypothesis import given
import hypothesis.strategies as st

from quickselect import quickselect
from median_of_medians import median_of_medians
from sampling_and_sorting import sampling_and_sorting

MAX_SIZE = 10000


class TestMedianAlgorithms(unittest.TestCase):
    @given(st.integers(min_value=1, max_value=MAX_SIZE))
    def test_quickselect(self, n):
        if n % 2 == 0:
            n = n - 1

        X = random.sample(range(n), n)

        median_k = int((len(X) + 1) / 2)

        assert median(X) == quickselect(X, median_k)

    @given(st.integers(min_value=1, max_value=MAX_SIZE))
    def test_median_of_medians(self, n):
        if n % 2 == 0:
            n = n - 1

        X = random.sample(range(n), n)

        median_k = int((len(X) + 1) / 2)

        assert median(X) == median_of_medians(X, median_k)

    @given(st.integers(min_value=1, max_value=MAX_SIZE))
    def test_sampling_and_sorting(self, n):
        if n % 2 == 0:
            n = n - 1

        X = random.sample(range(n), n)

        assert median(X) == sampling_and_sorting(X)


if __name__ == '__main__':
    unittest.main()
