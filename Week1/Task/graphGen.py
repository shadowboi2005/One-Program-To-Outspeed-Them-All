# import numpy as np
import matplotlib.pyplot as plt
import subprocess
import os

import subprocess

def run_executable_with_input(executable_path, input_integer):
    # Run the executable and communicate with it through pipes
    process = subprocess.Popen([executable_path], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    # Send input to the executable
    process.stdin.write(str(input_integer) + '\n')
    process.stdin.flush()

    # Get output from the executable
    output = process.stdout.readline().strip()
    error = process.stderr.readline().strip()

    # Close the input stream
    process.stdin.close()

    # Wait for the process to finish and get the return code
    return_code = process.wait()

    if return_code != 0:
        # If the executable encountered an error, print the error message
        print("Error:", error)
        return None
    else:
        # Split the output into two numbers
        return float(output)

if __name__ == '__main__':

    x = []
    naive = []
    pragma = []

    for i in range(1000,1200):
        if i == 0:
            continue
        timePragma = run_executable_with_input('./Parallel',i)
        timeNaive = run_executable_with_input('./Naive',i)
        x.append(i)
        naive.append(timeNaive)
        pragma.append(timePragma)
        print(i)

    plt.figure()
    plt.plot(x,naive,'r-',label='naive method')
    plt.plot(x,pragma,'b-',label='vectorized method')
    plt.xlabel('size of vector')
    plt.ylabel('time taken by respective methods')
    plt.legend()
    plt.savefig("graph1.png")
