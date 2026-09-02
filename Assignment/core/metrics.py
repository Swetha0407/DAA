def calculate_metrics(bins, capacity, item_count):
    """Calculate packing quality metrics."""

    bin_count = len(bins)

    total_used = sum(
        bin_data["used"]
        for bin_data in bins
    )

    total_capacity = bin_count * capacity

    unused_space = total_capacity - total_used

    utilization = (
        (total_used / total_capacity) * 100
        if total_capacity > 0
        else 0
    )

    average_fill = (
        total_used / bin_count
        if bin_count > 0
        else 0
    )

    return {
        "bin_count": bin_count,
        "item_count": item_count,
        "total_used": total_used,
        "total_capacity": total_capacity,
        "unused_space": unused_space,
        "utilization": round(utilization, 2),
        "average_fill": round(average_fill, 2)
    }