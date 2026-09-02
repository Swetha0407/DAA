def best_fit(items, capacity):
    """
    Best Fit Bin Packing.

    Each item is placed into the existing bin
    that leaves the smallest remaining space after
    the item is inserted.
    """

    bins = []

    for item in items:
        best_index = -1
        smallest_remaining = capacity + 1

        for index, bin_data in enumerate(bins):

            if bin_data["remaining"] >= item:

                remaining_after = bin_data["remaining"] - item

                if remaining_after < smallest_remaining:
                    smallest_remaining = remaining_after
                    best_index = index

        if best_index != -1:
            bins[best_index]["items"].append(item)
            bins[best_index]["used"] += item
            bins[best_index]["remaining"] -= item

        else:
            bins.append({
                "items": [item],
                "used": item,
                "remaining": capacity - item
            })

    return bins