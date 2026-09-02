from .best_fit import best_fit


def best_fit_decreasing(items, capacity):
    """
    Best Fit Decreasing.

    Items are sorted in decreasing order and then
    processed using Best Fit.
    """

    sorted_items = sorted(items, reverse=True)

    return best_fit(sorted_items, capacity)