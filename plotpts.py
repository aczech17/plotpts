"""
Usage: ./aprox -s spline-file [-p points-file] [ -g gnuplot-file [-f from_x -t to_x -n n_points ] ]
            if points-file is given then
               reads discrete 2D points from points-file
               writes spline approximation to spline-file
               - number of points should be >= 4
            else (points-file not given)
               reads spline from spline-file
            endfi
            if gnuplot-file is given then
               makes table of n_points within <from_x,to_x> range
               - from_x defaults to x-coordinate of the first point in points-file,
               - to_x defaults to x-coordinate of the last point
               - n_points defaults to 100
               - n_points must be > 1
            endif
"""

import os
import sys
import subprocess
import matplotlib.pyplot as plt

if len(sys.argv) < 2:
   print("plotpts.py [input filename] [approx_base_size=10] [points_n=100]")
   quit()

if len(sys.argv) >= 3:
   approx_base_size = sys.argv[2]
else:
   approx_base_size = "10"

if len(sys.argv) >= 4:
   points_n = sys.argv[3]
else:
   points_n = 100

os.environ["APPROX_BASE_SIZE"] = approx_base_size


input_file = sys.argv[1]
input_xs = []
input_ys = []

with open(input_file, "r") as file:
   for line in file:
      (x, y) = (line.split(" "))
      input_xs.append(float(x))
      input_ys.append(float(y))

first_x = input_xs[0]
last_x = input_xs[-1]


print(f"APPROX_BASE_SIZE = {approx_base_size}")
print(f"{points_n} points")
print(f"Plotting from {first_x} to {last_x}.")

subprocess.run(f"aprox/aprox -s spl -p {input_file} -g out -f {first_x} -t {last_x} -n {points_n}".split(" "))

xs = []
ys = []


with open("out", "r") as file:
	for line in file:
		(x, y) = line.split(" ")
		xs.append(float(x))
		ys.append(float(y))


for p in range(0, len(input_xs)):
   plt.plot(input_xs[p], input_ys[p], 'ro')

plt.plot(xs, ys)

plt.show()
