import random


def validate_items(items, capacity):
    """Validate that all item sizes are suitable."""

    if capacity <= 0:
        raise ValueError("Bin capacity must be greater than zero.")

    if not items:
        raise ValueError("At least one item is required.")

    if any(item <= 0 for item in items):
        raise ValueError("Item sizes must be positive.")

    if any(item > capacity for item in items):
        raise ValueError(
            "No item can be larger than the bin capacity."
        )


def generate_random_dataset(count, capacity, seed=42):
    """Generate uniformly distributed random item sizes."""

    rng = random.Random(seed)

    return [
        rng.randint(1, capacity)
        for _ in range(count)
    ]


def generate_small_dataset(count, capacity, seed=42):
    """Generate datasets containing mostly small items."""

    rng = random.Random(seed)

    upper = max(1, int(capacity * 0.30))

    return [
        rng.randint(1, upper)
        for _ in range(count)
    ]


def generate_large_dataset(count, capacity, seed=42):
    """Generate datasets containing mostly large items."""

    rng = random.Random(seed)

    lower = max(1, int(capacity * 0.60))

    return [
        rng.randint(lower, capacity)
        for _ in range(count)
    ]


def generate_mixed_dataset(count, capacity, seed=42):
    """
    Generate a mixed distribution containing small,
    medium and large items.
    """

    rng = random.Random(seed)

    items = []

    for _ in range(count):

        category = rng.randint(1, 3)

        if category == 1:
            upper = max(1, int(capacity * 0.30))
            items.append(rng.randint(1, upper))

        elif category == 2:
            lower = max(1, int(capacity * 0.30))
            upper = max(lower, int(capacity * 0.70))
            items.append(rng.randint(lower, upper))

        else:
            lower = max(1, int(capacity * 0.70))
            items.append(rng.randint(lower, capacity))

    return items


def generate_dataset(dataset_type, count, capacity, seed=42):

    generators = {
        "random": generate_random_dataset,
        "small": generate_small_dataset,
        "large": generate_large_dataset,
        "mixed": generate_mixed_dataset
    }

    if dataset_type not in generators:
        raise ValueError("Unknown dataset type.")

    return generators[dataset_type](
        count,
        capacity,
        seed
    )