from core.dataset import generate_dataset
from core.benchmark import run_benchmark


DEFAULT_SIZES = [
    100,
    250,
    500,
    1000,
    2500,
    5000
]


def run_scaling_experiment(
    capacity,
    dataset_type,
    sizes=None,
    seed=42,
    repetitions=5
):

    if sizes is None:
        sizes = DEFAULT_SIZES

    experiment = []

    for size in sizes:

        items = generate_dataset(
            dataset_type,
            size,
            capacity,
            seed
        )

        results = run_benchmark(
            items,
            capacity,
            repetitions
        )

        experiment.append({
            "size": size,
            "results": results
        })

    return experiment