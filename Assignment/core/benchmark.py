import time

from algorithms.first_fit import first_fit
from algorithms.first_fit_decreasing import first_fit_decreasing
from algorithms.best_fit import best_fit
from algorithms.best_fit_decreasing import best_fit_decreasing

from core.metrics import calculate_metrics


ALGORITHMS = {
    "First Fit": first_fit,
    "First Fit Decreasing": first_fit_decreasing,
    "Best Fit": best_fit,
    "Best Fit Decreasing": best_fit_decreasing
}


def run_algorithm(name, items, capacity, repetitions=5):

    algorithm = ALGORITHMS[name]

    timings = []
    result = None

    for _ in range(repetitions):

        start = time.perf_counter_ns()

        bins = algorithm(items, capacity)

        end = time.perf_counter_ns()

        timings.append(end - start)
        result = bins

    timings.sort()

    median_time = timings[len(timings) // 2]

    metrics = calculate_metrics(
        result,
        capacity,
        len(items)
    )

    metrics["execution_time_ns"] = median_time

    metrics["execution_time_ms"] = round(
        median_time / 1_000_000,
        4
    )

    return {
        "name": name,
        "bins": result,
        "metrics": metrics
    }


def run_comparison(items, capacity):

    results = []

    for name in ALGORITHMS:

        results.append(
            run_algorithm(
                name,
                items,
                capacity
            )
        )

    return results


def run_benchmark(items, capacity, repetitions=7):

    """
    Run every algorithm multiple times on the same
    dataset and return median execution time.
    """

    benchmark_results = []

    for name, algorithm in ALGORITHMS.items():

        timings = []
        bin_count = 0
        utilization = 0

        for _ in range(repetitions):

            start = time.perf_counter_ns()

            bins = algorithm(
                items,
                capacity
            )

            end = time.perf_counter_ns()

            timings.append(end - start)

            bin_count = len(bins)

            metrics = calculate_metrics(
                bins,
                capacity,
                len(items)
            )

            utilization = metrics["utilization"]

        timings.sort()

        median_time = timings[
            len(timings) // 2
        ]

        benchmark_results.append({
            "algorithm": name,
            "bin_count": bin_count,
            "utilization": utilization,
            "time_ns": median_time,
            "time_ms": round(
                median_time / 1_000_000,
                4
            )
        })

    return benchmark_results