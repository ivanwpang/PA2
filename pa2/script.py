import subprocess
import statistics

# Number of times to run the C program
num_runs = 30

# Lists to store the average times for each run
average_times = []

for _ in range(num_runs):
    # Run the C program and capture its output
    output = subprocess.check_output(["./FCFS"], universal_newlines=True)

    # Parse the output to extract the average response time
    lines = output.split('\n')
    avg_response_line = lines[-2]  # The line that contains the average response time
    avg_response = float(avg_response_line.split()[-1])  # Extract the average time

    average_times.append(avg_response)

# Calculate the average and standard deviation of the average times
average_average_time = statistics.mean(average_times)
standard_deviation = statistics.stdev(average_times)

print(f"Average of Average Response Times: {average_average_time:.9f} seconds")
print(f"Standard Deviation: {standard_deviation:.9f} seconds")
