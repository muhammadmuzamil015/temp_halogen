# Copyright 2024 10xEngineers

import csv
from quickchart import QuickChart

# Function to read CSV file and return test names and times for all targets
def read_csv(filename):
    test_names = []
    qemu_aarch64_times = []
    qemu_riscv64_times = []
    spike_times = []
    bpif3_times = []
    raspi4_times = []
    
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        next(reader)  # Skip header
        for row in reader:
            test_names.append(row[0])
            qemu_aarch64_times.append(float(row[1]))
            qemu_riscv64_times.append(float(row[2]))
            spike_times.append(float(row[3]))
            bpif3_times.append(float(row[4]))
            raspi4_times.append(float(row[5]))
    
    return test_names, qemu_aarch64_times, qemu_riscv64_times, spike_times, bpif3_times, raspi4_times

# Read the CSV file
csv_file = 'combined_performance_results.csv'
test_names, qemu_aarch64_times, qemu_riscv64_times, spike_times, bpif3_times, raspi4_times = read_csv(csv_file)

# Initialize QuickChart
qc = QuickChart()
qc.width = 1200
qc.height = 800

# Create the chart configuration with bright/dark colors
qc.config = {
    "type": "bar",
    "data": {
        "labels": test_names,
        "datasets": [
            {
                "label": "QEMU AARCH64",
                "data": qemu_aarch64_times,
                "backgroundColor": "rgba(255, 69, 0, 0.85)"  # Dark Orange
            },
            {
                "label": "QEMU RISCV64",
                "data": qemu_riscv64_times,
                "backgroundColor": "rgba(0, 0, 205, 0.85)"  # Dark Blue
            },
            {
                "label": "SPIKE",
                "data": spike_times,
                "backgroundColor": "rgba(34, 139, 34, 0.85)"  # Dark Green
            },
            {
                "label": "BPIF3",
                "data": bpif3_times,
                "backgroundColor": "rgba(255, 215, 0, 0.85)"  # Bright Gold
            },
            {
                "label": "RASPI4",
                "data": raspi4_times,
                "backgroundColor": "rgba(128, 0, 128, 0.85)"  # Dark Purple
            }
        ]
    },
    "options": {
        "scales": {
            "yAxes": [{
                "ticks": {
                    "beginAtZero": True,
                    "suggestedMax": max(qemu_aarch64_times + qemu_riscv64_times + spike_times + bpif3_times + raspi4_times) * 1.1
                },
                "scaleLabel": {
                    "display": True,
                    "labelString": "Time (us)"
                }
            }]
        },
        "title": {
            "display": True,
            "text": "Performance Comparison Across Targets"
        },
        "plugins": {
            "datalabels": {
                "display": True,
                "align": "top",
                "anchor": "end",
                "color": "black",
                "font": {
                    "weight": "bold"
                },
                "formatter": "function(value) { return value.toFixed(3) + ' us'; }"
            }
        }
    }
}

# Save the chart to a file
output_filename = 'performance_comparison_across_targets.png'
qc.to_file(output_filename)
print(f"Performance comparison chart saved to '{output_filename}'")
