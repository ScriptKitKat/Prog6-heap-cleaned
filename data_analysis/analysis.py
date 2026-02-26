import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# ── Load data ──
csv_file = sys.argv[1] if len(sys.argv) > 1 else "data.csv"
df = pd.read_csv(csv_file, header=None, skipinitialspace=True,
                 names=["type", "size", "time_ns", "allocated", "system", "metadata"])

df_malloc = df[df["type"] == "malloc"].copy()
df_free   = df[df["type"] == "free"].copy()

fig, axes = plt.subplots(2, 2, figsize=(14, 10))
fig.suptitle("Memory Allocator Statistics (First Fit)", fontsize=14, fontweight="bold")

# ── 1. % Memory Utilization Over Time ──
ax = axes[0, 0]
utilization = df["allocated"] / df["system"] * 100
ax.plot(df.index, utilization, linewidth=0.3, color="steelblue")
ax.set_title("Memory Utilization Over Time")
ax.set_xlabel("Request #")
ax.set_ylabel("Utilization (%)")
ax.set_ylim(0, 100)

# Add average line
avg_util = utilization.mean()
ax.axhline(y=avg_util, color="red", linestyle="--", linewidth=1, label=f"Average: {avg_util:.2f}%")
ax.legend()

# ── 2. % Memory Utilization vs Allocation Size ──
ax = axes[0, 1]
malloc_util = df_malloc["allocated"] / df_malloc["system"] * 100
ax.scatter(df_malloc["size"], malloc_util, s=0.1, alpha=0.5, color="steelblue")
ax.set_title("Memory Utilization vs Allocation Size")
ax.set_xlabel("Allocation Size (bytes)")
ax.set_ylabel("Utilization (%)")
ax.set_xscale("log")
ax.set_ylim(0, 100)

# ── 3. Speed of malloc/free vs Size (log scale) ──
ax = axes[1, 0]
ax.scatter(df_malloc["size"], df_malloc["time_ns"], s=0.2, alpha=0.4, label="t_malloc", color="steelblue")
ax.scatter(df_free["size"],   df_free["time_ns"],   s=0.2, alpha=0.4, label="t_free", color="coral")
ax.set_title("Allocation / Free Speed vs Size")
ax.set_xlabel("Size (bytes, log scale)")
ax.set_ylabel("Time (ns)")
ax.set_xscale("log")
ax.set_yscale("log")
ax.legend(markerscale=10)

# ── 4. Metadata Overhead Over Time ──
ax = axes[1, 1]
overhead_pct = df["metadata"] / df["system"] * 100
ax.plot(df.index, df["metadata"], linewidth=0.3, color="steelblue", label="Metadata (bytes)")
ax.set_title("Data Structure Overhead Over Time")
ax.set_xlabel("Request #")
ax.set_ylabel("Metadata Size (bytes)")

# Secondary y-axis for percentage
ax2 = ax.twinx()
ax2.plot(df.index, overhead_pct, linewidth=0.3, color="coral", alpha=0.6, label="% of system")
ax2.set_ylabel("Overhead (% of system)")
ax.legend(loc="upper left")
ax2.legend(loc="upper right")

plt.tight_layout()
plt.savefig("allocator_stats.png", dpi=200)
plt.show()
print(f"\nSaved to allocator_stats.png")
print(f"Average memory utilization: {avg_util:.2f}%")
print(f"Total data points: {len(df)}")