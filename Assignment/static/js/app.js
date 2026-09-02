let analysisResults = [];
let currentCapacity = 100;


/* ------------------------------
   GENERATE DATASET
------------------------------ */

async function generateDataset() {

    hideError();

    const capacity =
        Number(document.getElementById("capacity").value);

    const count =
        Number(document.getElementById("itemCount").value);

    const dataset =
        document.getElementById("datasetType").value;

    const seed =
        Number(document.getElementById("seed").value);


    try {

        const response = await fetch(
            "/api/generate",
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({
                    capacity,
                    count,
                    dataset,
                    seed
                })
            }
        );


        const data = await response.json();


        if (!data.success) {

            showError(data.error);

            return;
        }


        document.getElementById("items").value =
            data.items.join(", ");


        updateItemSummary(data.items);

    }

    catch (error) {

        showError(
            "Unable to generate the dataset."
        );
    }
}


/* ------------------------------
   RUN ANALYSIS
------------------------------ */

async function runAnalysis() {

    hideError();

    const capacity =
        Number(document.getElementById("capacity").value);


    const rawItems =
        document.getElementById("items").value;


    const items =
        rawItems
            .split(",")
            .map(value => value.trim())
            .filter(value => value !== "")
            .map(Number);


    if (!items.length) {

        showError(
            "Please generate or enter a dataset first."
        );

        return;
    }


    if (
        items.some(
            item =>
                !Number.isInteger(item) ||
                item <= 0
        )
    ) {

        showError(
            "All item sizes must be positive integers."
        );

        return;
    }


    try {

        const response = await fetch(
            "/api/analyze",
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({
                    capacity,
                    items
                })
            }
        );


        const data = await response.json();


        if (!data.success) {

            showError(data.error);

            return;
        }


        analysisResults =
            data.results;

        currentCapacity =
            data.capacity;


        renderResults();

        updateItemSummary(items);

    }

    catch (error) {

        showError(
            "Unable to complete the analysis."
        );
    }
}


/* ------------------------------
   RESULT CARDS
------------------------------ */

function renderResults() {

    const section =
        document.getElementById(
            "resultsSection"
        );


    section.classList.remove("hidden");


    const cards =
        document.getElementById(
            "algorithmCards"
        );


    cards.innerHTML = "";


    const bestBins =
        Math.min(
            ...analysisResults.map(
                result =>
                    result.metrics.bin_count
            )
        );


    analysisResults.forEach(result => {

        const metrics =
            result.metrics;


        const isWinner =
            metrics.bin_count === bestBins;


        const card =
            document.createElement("div");


        card.className =
            `algorithm-card ${
                isWinner ? "winner" : ""
            }`;


        card.innerHTML = `

            <div class="algorithm-name">
                ${result.name}
                ${isWinner ? " · BEST PACKING" : ""}
            </div>

            <div class="bin-number">
                ${metrics.bin_count}
            </div>

            <div class="bin-label">
                bins required
            </div>

            <div class="card-stats">

                <div class="stat">
                    <span>Utilization</span>
                    <strong>
                        ${metrics.utilization}%
                    </strong>
                </div>

                <div class="stat">
                    <span>Time</span>
                    <strong>
                        ${metrics.execution_time_ms} ms
                    </strong>
                </div>

            </div>

        `;


        cards.appendChild(card);

    });


    renderRecommendation(bestBins);

    renderComparisonTable();

    populateAlgorithmSelector();

    displayPacking();

    section.scrollIntoView({
        behavior: "smooth",
        block: "start"
    });
}


/* ------------------------------
   RECOMMENDATION
------------------------------ */

function renderRecommendation(bestBins) {

    const winners =
        analysisResults.filter(
            result =>
                result.metrics.bin_count === bestBins
        );


    const names =
        winners.map(
            result => result.name
        ).join(" and ");


    const recommendation =
        document.getElementById(
            "recommendation"
        );


    recommendation.innerHTML = `

        <strong>
            Current observation:
        </strong>

        ${names} achieved the lowest bin count
        for this dataset, using ${bestBins}
        bin${bestBins === 1 ? "" : "s"}.
        This comparison describes the behaviour
        of the selected input; it does not assume
        that the same strategy will always perform
        best on every dataset.

    `;
}


/* ------------------------------
   ALGORITHM SELECT
------------------------------ */

function populateAlgorithmSelector() {

    const select =
        document.getElementById(
            "algorithmSelect"
        );


    select.innerHTML = "";


    analysisResults.forEach(
        (result, index) => {

            const option =
                document.createElement("option");

            option.value = index;

            option.textContent =
                result.name;

            select.appendChild(option);

        }
    );
}


/* ------------------------------
   VISUAL PACKING
------------------------------ */

function displayPacking() {

    if (!analysisResults.length)
        return;


    const index =
        Number(
            document.getElementById(
                "algorithmSelect"
            ).value
        );


    const result =
        analysisResults[index];


    const container =
        document.getElementById(
            "binsContainer"
        );


    container.innerHTML = "";


    result.bins.forEach(
        (bin, index) => {

            const row =
                document.createElement("div");

            row.className =
                "bin-row";


            const utilization =
                (
                    bin.used /
                    currentCapacity *
                    100
                ).toFixed(1);


            const itemsHTML =
                bin.items.map(
                    item => {

                        const width =
                            (
                                item /
                                currentCapacity *
                                100
                            );


                        return `
                            <div
                                class="bin-item"
                                style="width:${width}%"
                                title="Item size: ${item}"
                            >
                                ${item}
                            </div>
                        `;

                    }
                ).join("");


            row.innerHTML = `

                <div class="bin-label">
                    BIN ${String(index + 1).padStart(2, "0")}
                </div>

                <div class="bin-track">
                    ${itemsHTML}
                </div>

                <div class="bin-utilization">
                    ${utilization}%
                </div>

            `;


            container.appendChild(row);

        }
    );
}


/* ------------------------------
   COMPARISON TABLE
------------------------------ */

function renderComparisonTable() {

    const body =
        document.getElementById(
            "comparisonBody"
        );


    body.innerHTML = "";


    analysisResults.forEach(result => {

        const metrics =
            result.metrics;


        const row =
            document.createElement("tr");


        row.innerHTML = `

            <td>
                ${result.name}
            </td>

            <td>
                ${metrics.bin_count}
            </td>

            <td>
                ${metrics.total_used}
            </td>

            <td>
                ${metrics.unused_space}
            </td>

            <td>
                ${metrics.utilization}%
            </td>

            <td>
                ${metrics.execution_time_ms} ms
            </td>

        `;


        body.appendChild(row);

    });
}


/* ------------------------------
   INPUT SUMMARY
------------------------------ */

function updateItemSummary(items) {

    const summary =
        document.getElementById(
            "itemSummary"
        );


    if (!items.length) {

        summary.textContent =
            "No dataset loaded";

        return;
    }


    const total =
        items.reduce(
            (sum, item) =>
                sum + item,
            0
        );


    summary.textContent =
        `${items.length} items · total size ${total}`;
}


/* ------------------------------
   CLEAR
------------------------------ */

function clearItems() {

    document.getElementById(
        "items"
    ).value = "";


    document.getElementById(
        "itemSummary"
    ).textContent =
        "No dataset loaded";


    document.getElementById(
        "resultsSection"
    ).classList.add("hidden");
}


/* ------------------------------
   ERRORS
------------------------------ */

function showError(message) {

    const box =
        document.getElementById(
            "errorBox"
        );


    box.textContent =
        message;


    box.classList.remove(
        "hidden"
    );
}


function hideError() {

    document.getElementById(
        "errorBox"
    ).classList.add(
        "hidden"
    );
}
/* =========================================================
   BENCHMARK LAB
========================================================= */

let timeChart = null;
let binChart = null;
let utilizationChart = null;


async function runBenchmark() {

    hideError();

    const button =
        document.getElementById(
            "benchmarkButton"
        );

    const capacity =
        Number(
            document.getElementById(
                "benchmarkCapacity"
            ).value
        );

    const dataset =
        document.getElementById(
            "benchmarkDataset"
        ).value;

    const repetitions =
        Number(
            document.getElementById(
                "benchmarkRepetitions"
            ).value
        );


    button.disabled = true;

    button.innerHTML =
        "Running experiment <span>…</span>";


    showBenchmarkStatus(
        "Running the algorithms on progressively larger datasets..."
    );


    try {

        const response = await fetch(
            "/api/benchmark",
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({

                    capacity,

                    dataset,

                    repetitions,

                    seed: 42,

                    sizes: [
                        100,
                        250,
                        500,
                        1000,
                        2500,
                        5000
                    ]

                })
            }
        );


        const data =
            await response.json();


        if (!data.success) {

            showError(data.error);

            return;
        }


        renderBenchmark(data);

        showBenchmarkStatus(
            `Experiment completed using ${data.repetitions} repetitions per measurement.`
        );

    }

    catch (error) {

        showError(
            "The benchmark could not be completed."
        );

    }

    finally {

        button.disabled = false;

        button.innerHTML =
            "Run benchmark <span>→</span>";

    }
}


/* ---------------------------------------------------------
   RENDER BENCHMARK
--------------------------------------------------------- */

function renderBenchmark(data) {

    const section =
        document.getElementById(
            "benchmarkResults"
        );


    section.classList.remove(
        "hidden"
    );


    const datasets =
        data.results;


    const sizes =
        datasets.map(
            entry => entry.size
        );


    const algorithmNames = [
        "First Fit",
        "First Fit Decreasing",
        "Best Fit",
        "Best Fit Decreasing"
    ];


    const datasetsByAlgorithm = {};


    algorithmNames.forEach(
        name => {

            datasetsByAlgorithm[name] = {
                time: [],
                bins: [],
                utilization: []
            };

        }
    );


    datasets.forEach(entry => {

        entry.results.forEach(result => {

            datasetsByAlgorithm[
                result.algorithm
            ].time.push(
                result.time_ms
            );

            datasetsByAlgorithm[
                result.algorithm
            ].bins.push(
                result.bin_count
            );

            datasetsByAlgorithm[
                result.algorithm
            ].utilization.push(
                result.utilization
            );

        });

    });


    drawTimeChart(
        sizes,
        datasetsByAlgorithm
    );


    drawBinChart(
        sizes,
        datasetsByAlgorithm
    );


    drawUtilizationChart(
        sizes,
        datasetsByAlgorithm
    );


    renderBenchmarkTable(
        datasets
    );


    renderBenchmarkObservation(
        datasets
    );
}


/* ---------------------------------------------------------
   CHART DATA
--------------------------------------------------------- */

function createChartDataset(
    label,
    values
) {

    return {

        label,

        data: values,

        borderWidth: 2,

        pointRadius: 3,

        tension: 0.25,

        fill: false

    };
}


/* ---------------------------------------------------------
   TIME CHART
--------------------------------------------------------- */

function drawTimeChart(
    sizes,
    data
) {

    if (timeChart)
        timeChart.destroy();


    const ctx =
        document.getElementById(
            "timeChart"
        );


    timeChart = new Chart(
        ctx,
        {

            type: "line",

            data: {

                labels: sizes,

                datasets: [

                    createChartDataset(
                        "First Fit",
                        data["First Fit"].time
                    ),

                    createChartDataset(
                        "First Fit Decreasing",
                        data["First Fit Decreasing"].time
                    ),

                    createChartDataset(
                        "Best Fit",
                        data["Best Fit"].time
                    ),

                    createChartDataset(
                        "Best Fit Decreasing",
                        data["Best Fit Decreasing"].time
                    )

                ]

            },

            options: {

                responsive: true,

                maintainAspectRatio: false,

                plugins: {

                    legend: {
                        position: "bottom"
                    }

                },

                scales: {

                    x: {
                        title: {
                            display: true,
                            text: "Number of items"
                        }
                    },

                    y: {

                        title: {
                            display: true,
                            text: "Median execution time (ms)"
                        },

                        beginAtZero: true

                    }

                }

            }

        }
    );
}


/* ---------------------------------------------------------
   BIN COUNT CHART
--------------------------------------------------------- */

function drawBinChart(
    sizes,
    data
) {

    if (binChart)
        binChart.destroy();


    const ctx =
        document.getElementById(
            "binChart"
        );


    binChart = new Chart(
        ctx,
        {

            type: "line",

            data: {

                labels: sizes,

                datasets: [

                    createChartDataset(
                        "First Fit",
                        data["First Fit"].bins
                    ),

                    createChartDataset(
                        "First Fit Decreasing",
                        data["First Fit Decreasing"].bins
                    ),

                    createChartDataset(
                        "Best Fit",
                        data["Best Fit"].bins
                    ),

                    createChartDataset(
                        "Best Fit Decreasing",
                        data["Best Fit Decreasing"].bins
                    )

                ]

            },

            options: {

                responsive: true,

                maintainAspectRatio: false,

                plugins: {

                    legend: {
                        position: "bottom"
                    }

                },

                scales: {

                    x: {
                        title: {
                            display: true,
                            text: "Number of items"
                        }
                    },

                    y: {

                        title: {
                            display: true,
                            text: "Bins used"
                        },

                        beginAtZero: true

                    }

                }

            }

        }
    );
}


/* ---------------------------------------------------------
   UTILIZATION CHART
--------------------------------------------------------- */

function drawUtilizationChart(
    sizes,
    data
) {

    if (utilizationChart)
        utilizationChart.destroy();


    const ctx =
        document.getElementById(
            "utilizationChart"
        );


    utilizationChart = new Chart(
        ctx,
        {

            type: "line",

            data: {

                labels: sizes,

                datasets: [

                    createChartDataset(
                        "First Fit",
                        data["First Fit"].utilization
                    ),

                    createChartDataset(
                        "First Fit Decreasing",
                        data["First Fit Decreasing"].utilization
                    ),

                    createChartDataset(
                        "Best Fit",
                        data["Best Fit"].utilization
                    ),

                    createChartDataset(
                        "Best Fit Decreasing",
                        data["Best Fit Decreasing"].utilization
                    )

                ]

            },

            options: {

                responsive: true,

                maintainAspectRatio: false,

                plugins: {

                    legend: {
                        position: "bottom"
                    }

                },

                scales: {

                    x: {
                        title: {
                            display: true,
                            text: "Number of items"
                        }
                    },

                    y: {

                        title: {
                            display: true,
                            text: "Utilization (%)"
                        },

                        min: 0,

                        max: 100

                    }

                }

            }

        }
    );
}


/* ---------------------------------------------------------
   BENCHMARK TABLE
--------------------------------------------------------- */

function renderBenchmarkTable(
    datasets
) {

    const body =
        document.getElementById(
            "benchmarkTableBody"
        );


    body.innerHTML = "";


    datasets.forEach(entry => {

        entry.results.forEach(result => {

            const row =
                document.createElement("tr");


            row.innerHTML = `

                <td>
                    ${entry.size}
                </td>

                <td>
                    ${result.algorithm}
                </td>

                <td>
                    ${result.bin_count}
                </td>

                <td>
                    ${result.utilization}%
                </td>

                <td>
                    ${result.time_ms} ms
                </td>

            `;


            body.appendChild(row);

        });

    });
}


/* ---------------------------------------------------------
   OBSERVATION GENERATOR
--------------------------------------------------------- */

function renderBenchmarkObservation(
    datasets
) {

    const observation =
        document.getElementById(
            "benchmarkObservation"
        );


    if (!datasets.length)
        return;


    const largest =
        datasets[datasets.length - 1];


    const bestPacking =
        [...largest.results]
            .sort(
                (a, b) =>
                    a.bin_count - b.bin_count
            )[0];


    const fastest =
        [...largest.results]
            .sort(
                (a, b) =>
                    a.time_ms - b.time_ms
            )[0];


    observation.innerHTML = `

        <span class="eyebrow">
            EXPERIMENTAL OBSERVATION
        </span>

        <p>
            For the largest tested dataset of
            <strong>${largest.size}</strong> items,
            <strong>${bestPacking.algorithm}</strong>
            produced the smallest bin count
            (${bestPacking.bin_count} bins), while
            <strong>${fastest.algorithm}</strong>
            recorded the shortest median execution time
            (${fastest.time_ms} ms).
            The result reflects this particular input
            distribution and should not be treated as a
            universal ranking of the algorithms.
        </p>

    `;
}


/* ---------------------------------------------------------
   STATUS
--------------------------------------------------------- */

function showBenchmarkStatus(
    message
) {

    const status =
        document.getElementById(
            "benchmarkStatus"
        );


    status.textContent =
        message;


    status.classList.remove(
        "hidden"
    );
}
/* =========================================================
   FULL EXPERIMENT
========================================================= */

async function runFullExperiment() {

    hideError();

    const capacity =
        Number(
            document.getElementById(
                "benchmarkCapacity"
            ).value
        );

    const repetitions =
        Number(
            document.getElementById(
                "benchmarkRepetitions"
            ).value
        );


    showBenchmarkStatus(
        "Running the complete experiment across four dataset distributions..."
    );


    try {

        const response = await fetch(
            "/api/full-experiment",
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({
                    capacity,
                    repetitions,
                    seed: 42
                })
            }
        );


        const data =
            await response.json();


        if (!data.success) {

            showError(data.error);

            return;
        }


        window.fullExperimentResults =
            data.results;


        /*
         * Display the random dataset first.
         * The complete dataset remains available
         * for export and later analysis.
         */

        const randomResults =
            data.results.random;


        renderBenchmark({
            results: randomResults
        });


        showBenchmarkStatus(
            "Full experiment completed. Results for all four distributions are available for export."
        );

    }

    catch (error) {

        showError(
            "The full experiment could not be completed."
        );

    }
}


/* =========================================================
   CSV EXPORT
========================================================= */

async function exportBenchmark() {

    const allResults =
        window.fullExperimentResults;


    if (!allResults) {

        showError(
            "Run the full experiment before exporting results."
        );

        return;
    }


    /*
     * Combine all distributions into one export structure.
     */

    const combined = [];


    Object.entries(
        allResults
    ).forEach(
        ([distribution, results]) => {

            results.forEach(entry => {

                combined.push({

                    distribution,

                    size:
                        entry.size,

                    results:
                        entry.results

                });

            });

        }
    );


    /*
     * Build CSV directly in the browser.
     */

    let csv =
        "Distribution,Input Size,Algorithm,Bins,Utilization (%),Median Time (ms)\n";


    combined.forEach(entry => {

        entry.results.forEach(result => {

            csv +=
                `"${entry.distribution}",` +
                `${entry.size},` +
                `"${result.algorithm}",` +
                `${result.bin_count},` +
                `${result.utilization},` +
                `${result.time_ms}\n`;

        });

    });


    const blob =
        new Blob(
            [csv],
            {
                type: "text/csv;charset=utf-8;"
            }
        );


    const url =
        URL.createObjectURL(blob);


    const link =
        document.createElement("a");


    link.href = url;

    link.download =
        "binpack_full_experiment.csv";


    document.body.appendChild(link);

    link.click();

    document.body.removeChild(link);

    URL.revokeObjectURL(url);

}