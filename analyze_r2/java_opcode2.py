import argparse
import pathlib
import re
import subprocess
from collections import defaultdict

import numpy as np
from matplotlib import pyplot as plt

PATH_ROOT = pathlib.Path(__file__).parent.parent.resolve()


def parse(lines: [str]):
    regxp = re.compile(r"^ *\d+\:")
    instructions = []
    for line in lines:
        line = line.strip()
        if regxp.match(line):
            line = line.split(":")[1].split()[0]
            instructions.append(line)
    return instructions


def extract_instructions(project_root, class_name):
    try:
        # Run javap command using subprocess and capture output
        command = ["javap", "-c", "-classpath", ".", class_name]
        output = subprocess.check_output(command, stderr=subprocess.STDOUT, universal_newlines=True, cwd=project_root)
        return parse(output.split("\n"))
    except subprocess.CalledProcessError as e:
        return f"Error: {e.output}"


def compare_opcode_sequences(seq_x, seq_y):
    matches = defaultdict(list)

    for i in range(len(seq_x) - 2):
        for j in range(len(seq_y) - 2):
            s1 = seq_x[i:i + 3]
            s2 = seq_y[j:j + 3]
            if set(s1) == set(s2):
                matches[i].append(j)

    return matches


def calculate_similarity(matches, n, m, threshold):
    grid = [[0] * m for _ in range(n)]

    for x, y_list in matches.items():
        for y in y_list:
            grid[x][y] += 1

    similarity_score = 0

    for i in range(n):
        for j in range(m):
            if grid[i][j] >= threshold:
                similarity_score += 1

    similarity_score /= (n + m)

    return similarity_score


def plot_opcode_matrix(matches, n, m, title: str = 'Opcode Matches Matrix',
                       x_lab: str = "Program Y Opcode Number",
                       y_lab: str = "Program X Opcode Number"):
    matrix = np.zeros((n, m))

    for x, y_list in matches.items():
        for y in y_list:
            matrix[x, y] = 1

    plt.figure(figsize=(10, 8))  # Set the figure size (adjust as needed)
    plt.imshow(matrix, cmap='gray', interpolation='none', aspect='auto', origin='lower')
    plt.xlabel(x_lab)
    plt.ylabel(y_lab)
    plt.title(title)
    plt.colorbar()

    plt.show()


if __name__ == "__main__":
    argparser = argparse.ArgumentParser()
    argparser.add_argument('-i', '--input_file', type=str, help='Path to the input file', required=True)
    argparser.add_argument('-b', '--input_file2', type=str, help='Path to the input file', required=True)
    args = argparser.parse_args()

    # Specify the bytecode filename and class name
    bytecode_filename = PATH_ROOT / args.input_file
    bytecode_filename2 = PATH_ROOT / args.input_file2
    class_name = "org.example.Main"

    instructions = extract_instructions(bytecode_filename, class_name)
    instructions2 = extract_instructions(bytecode_filename2, class_name)

    matches = compare_opcode_sequences(instructions, instructions2)

    plot_opcode_matrix(matches, len(instructions), len(instructions2),
                       title='Opcode Matches Matrix for "Quick Sort" java version',
                       x_lab="base version",
                       y_lab="version q_sort5")

    print(instructions)
    print(instructions2)
    # Extract and print the instructions

