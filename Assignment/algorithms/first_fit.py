def first_fit(items, capacity):
    """
    First Fit Bin Packing.

    Each item is placed into the first existing bin
    in which it fits. If no bin can accommodate it,
    a new bin is created.
    """

    bins = []

    for item in items:
        placed = False

        for bin_data in bins:
            if bin_data["remaining"] >= item:
                bin_data["items"].append(item)
                bin_data["used"] += item
                bin_data["remaining"] -= item
                placed = True
                break

        if not placed:
            bins.append({
                "items": [item],
                "used": item,
                "remaining": capacity - item
            })

    return bins