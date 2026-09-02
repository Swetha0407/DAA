from flask import Flask, render_template, request, jsonify, Response

from core.dataset import (
    validate_items,
    generate_dataset
)

from core.benchmark import run_comparison

from core.benchmark_lab import run_scaling_experiment


app = Flask(__name__)


# ============================================================
# HOME PAGE
# ============================================================

@app.route("/")
def home():
    return render_template("index.html")


# ============================================================
# ALGORITHM COMPARISON
# ============================================================

@app.route("/api/analyze", methods=["POST"])
def analyze():

    try:

        data = request.get_json()

        if not data:
            raise ValueError("No input data received.")

        capacity = int(
            data.get("capacity", 100)
        )

        items = data.get(
            "items",
            []
        )

        if not isinstance(items, list):
            raise ValueError(
                "Items must be provided as a list."
            )

        items = [
            int(item)
            for item in items
        ]

        validate_items(
            items,
            capacity
        )

        results = run_comparison(
            items,
            capacity
        )

        return jsonify({
            "success": True,
            "capacity": capacity,
            "items": items,
            "results": results
        })

    except (ValueError, TypeError) as error:

        return jsonify({
            "success": False,
            "error": str(error)
        }), 400


# ============================================================
# DATASET GENERATION
# ============================================================

@app.route("/api/generate", methods=["POST"])
def generate():

    try:

        data = request.get_json()

        if not data:
            raise ValueError(
                "No dataset configuration received."
            )

        capacity = int(
            data.get("capacity", 100)
        )

        count = int(
            data.get("count", 20)
        )

        dataset_type = data.get(
            "dataset",
            "random"
        )

        seed = int(
            data.get("seed", 42)
        )


        if capacity <= 0:

            raise ValueError(
                "Bin capacity must be greater than zero."
            )


        if count <= 0:

            raise ValueError(
                "Number of items must be greater than zero."
            )


        if count > 100000:

            raise ValueError(
                "Maximum dataset size is 100000 items."
            )


        items = generate_dataset(
            dataset_type,
            count,
            capacity,
            seed
        )


        return jsonify({

            "success": True,

            "items": items,

            "count": len(items),

            "dataset": dataset_type,

            "capacity": capacity,

            "seed": seed

        })


    except (ValueError, TypeError) as error:

        return jsonify({

            "success": False,

            "error": str(error)

        }), 400


# ============================================================
# SINGLE BENCHMARK
# ============================================================

@app.route("/api/benchmark", methods=["POST"])
def benchmark():

    try:

        data = request.get_json()

        if not data:
            raise ValueError(
                "No benchmark configuration received."
            )


        capacity = int(
            data.get("capacity", 100)
        )


        dataset_type = data.get(
            "dataset",
            "random"
        )


        seed = int(
            data.get("seed", 42)
        )


        repetitions = int(
            data.get("repetitions", 5)
        )


        sizes = data.get(
            "sizes",
            [
                100,
                250,
                500,
                1000,
                2500,
                5000
            ]
        )


        if capacity <= 0:

            raise ValueError(
                "Bin capacity must be greater than zero."
            )


        if repetitions < 1 or repetitions > 15:

            raise ValueError(
                "Repetitions must be between 1 and 15."
            )


        valid_sizes = []


        for size in sizes:

            size = int(size)


            if size <= 0:

                raise ValueError(
                    "Dataset sizes must be positive."
                )


            if size > 5000:

                raise ValueError(
                    "Benchmark dataset size cannot exceed 5000."
                )


            valid_sizes.append(size)


        results = run_scaling_experiment(

            capacity=capacity,

            dataset_type=dataset_type,

            sizes=valid_sizes,

            seed=seed,

            repetitions=repetitions

        )


        return jsonify({

            "success": True,

            "capacity": capacity,

            "dataset": dataset_type,

            "seed": seed,

            "repetitions": repetitions,

            "results": results

        })


    except (ValueError, TypeError) as error:

        return jsonify({

            "success": False,

            "error": str(error)

        }), 400


# ============================================================
# FULL EXPERIMENT
# ============================================================

@app.route("/api/full-experiment", methods=["POST"])
def full_experiment():

    try:

        data = request.get_json()

        if not data:
            raise ValueError(
                "No experiment configuration received."
            )


        capacity = int(
            data.get("capacity", 100)
        )


        seed = int(
            data.get("seed", 42)
        )


        repetitions = int(
            data.get("repetitions", 5)
        )


        distributions = [

            "random",

            "small",

            "large",

            "mixed"

        ]


        sizes = [

            100,

            250,

            500,

            1000,

            2500,

            5000

        ]


        if capacity <= 0:

            raise ValueError(
                "Bin capacity must be greater than zero."
            )


        if repetitions < 1 or repetitions > 15:

            raise ValueError(
                "Repetitions must be between 1 and 15."
            )


        all_results = {}


        for distribution in distributions:

            all_results[distribution] = (

                run_scaling_experiment(

                    capacity=capacity,

                    dataset_type=distribution,

                    sizes=sizes,

                    seed=seed,

                    repetitions=repetitions

                )

            )


        return jsonify({

            "success": True,

            "capacity": capacity,

            "seed": seed,

            "repetitions": repetitions,

            "sizes": sizes,

            "distributions": distributions,

            "results": all_results

        })


    except (ValueError, TypeError) as error:

        return jsonify({

            "success": False,

            "error": str(error)

        }), 400


# ============================================================
# CSV EXPORT
# ============================================================

@app.route("/api/export", methods=["POST"])
def export_results():

    try:

        data = request.get_json()

        if not data:

            raise ValueError(
                "No benchmark data received."
            )


        results = data.get(
            "results",
            []
        )


        if not results:

            raise ValueError(
                "No benchmark results available."
            )


        rows = [

            "Distribution,Input Size,Algorithm,"
            "Bins,Utilization (%),Median Time (ms)"

        ]


        for entry in results:

            distribution = entry.get(
                "distribution",
                "unknown"
            )


            size = entry.get(
                "size",
                ""
            )


            for result in entry.get(
                "results",
                []
            ):

                rows.append(

                    f'"{distribution}",'
                    f'{size},'
                    f'"{result["algorithm"]}",'
                    f'{result["bin_count"]},'
                    f'{result["utilization"]},'
                    f'{result["time_ms"]}'

                )


        csv_data = "\n".join(rows)


        return Response(

            csv_data,

            mimetype="text/csv",

            headers={

                "Content-Disposition":
                    "attachment; "
                    "filename=binpack_benchmark.csv"

            }

        )


    except (ValueError, TypeError, KeyError) as error:

        return jsonify({

            "success": False,

            "error": str(error)

        }), 400


# ============================================================
# APPLICATION START
# ============================================================

if __name__ == "__main__":

    app.run(

        host="127.0.0.1",

        port=5000,

        debug=True

    )