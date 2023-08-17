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


def compare_opcodes(opcodes_X, opcodes_Y):
    matches = defaultdict(list)
    for i in range(len(opcodes_X) - 2):
        subseq_X = tuple(opcodes_X[i:i+3])
        for j in range(len(opcodes_Y) - 2):
            subseq_Y = tuple(opcodes_Y[j:j+3])
            if subseq_X == subseq_Y:
                matches[subseq_X].append((i, j))
    return matches


def calculate_similarity(opcodes_X, opcodes_Y, threshold=5):
    matches = compare_opcodes(opcodes_X, opcodes_Y)
    graph = [[0] * len(opcodes_Y) for _ in range(len(opcodes_X))]

    for match_positions in matches.values():
        if len(match_positions) >= threshold:
            for x, y in match_positions:
                graph[x][y] = 1

    covered_X = sum(any(row) for row in graph)
    covered_Y = sum(any(graph[i][j] for i in range(len(opcodes_X))) for j in range(len(opcodes_Y)))

    similarity_score = (covered_X / len(opcodes_X) + covered_Y / len(opcodes_Y)) / 2
    return similarity_score, graph


def plot_similarity_matrix(matrix, x_ticks, y_ticks, x_labels = '(Program Y)'):
    plt.figure(figsize=(10, 10))
    plt.imshow(matrix, cmap='gray', aspect='auto', origin='lower')
    plt.colorbar()
    plt.xticks(range(len(y_ticks)), y_ticks, rotation=45, ha='right')
    plt.yticks(range(len(x_ticks)), x_ticks)
    plt.xlabel(x_labels)
    plt.ylabel("base version")
    plt.title("Filtered Opcode Similarity Matrix (threshold=2)")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    argparser = argparse.ArgumentParser()
    argparser.add_argument('-i', '--input_file', type=str, help='Path to the input file', required=True)
    args = argparser.parse_args()

    # Specify the bytecode filename and class name
    bytecode_filename = PATH_ROOT / args.input_file
    class_name = "org.example.Main"
    instructions = extract_instructions(bytecode_filename, class_name)

    for i in range(2, 6):
        bytecode_filename2 = str(bytecode_filename).replace("1", str(i))
        program_name = bytecode_filename2.split('\\')[-3]
        instructions2 = extract_instructions(bytecode_filename2, class_name)
        score, graph = calculate_similarity(instructions, instructions2, threshold=2)
        print(f'{program_name}: {score:.2f}')
        plot_similarity_matrix(graph, instructions, instructions2, x_labels=f'Program "{program_name}"')

    # Extract and print the instructions

