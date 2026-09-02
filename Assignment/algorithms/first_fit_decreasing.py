from .first_fit import first_fit


def first_fit_decreasing(items, capacity):
    """
    First Fit Decreasing.

    Items are sorted in decreasing order and then
    processed using First Fit.
    """

    sorted_items = sorted(items, reverse=True)

    return first_fit(sorted_items, capacity)