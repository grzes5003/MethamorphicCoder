import argparse
import os
import pathlib
from collections import defaultdict
import matplotlib.pyplot as plt
import numpy as np

import capstone
import r2pipe


PATH_ROOT = pathlib.Path(__file__).parent.parent.resolve()


def analyze(file_path: str, output_file: str = None) -> None:
    r2 = r2pipe.open(str(PATH_ROOT / file_path))
    r2.cmd('aaaa')
    r2.cmd(f'pd @@f > {str(PATH_ROOT / output_file)}')
    r2.quit()


def extract_opcodes(program):
    opcodes = []
    opcode_counter = 0

    for line in program:
        line = line.strip()
        if line and not line.startswith(("#", ".", ":", ";")):
            opcodes.append(opcode_counter)
            opcode_counter += 1

    return opcodes


def compare_opcode_sequences(seq_x, seq_y):
    matches = defaultdict(list)

    for i in range(len(seq_x) - 2):
        for j in range(len(seq_y) - 2):
            if seq_x[i:i + 3] == seq_y[j:j + 3]:
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


def extract_opcodes_from_binary(binary_file):
    opcodes = []

    with open(binary_file, 'rb') as f:
        binary_data = f.read()

    # Use the Capstone library to disassemble the binary data
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)

    for insn in md.disasm(binary_data, 0x0):
        opcodes.append(insn.mnemonic + " " + insn.op_str)

    return opcodes


def list_all_matching_files(file_path: str) -> list:
    dir = pathlib.Path(file_path).parent.resolve()
    print(dir)
    return [str(dir / path) for path in os.listdir(str(dir)) if '.' not in path]


def plot_opcode_matrix(matches, n, m):
    matrix = np.zeros((n, m))

    for x, y_list in matches.items():
        for y in y_list:
            matrix[x, y] = 1

    plt.figure(figsize=(10, 8))  # Set the figure size (adjust as needed)
    plt.imshow(matrix, cmap='gray', interpolation='none', aspect='auto', origin='lower')
    plt.xlabel("Program Y Opcode Number")
    plt.ylabel("Program X Opcode Number")
    plt.title("Opcode Matches Matrix")
    plt.colorbar()
    plt.show()


if __name__ == "__main__":
    argparser = argparse.ArgumentParser()
    argparser.add_argument('-i', '--input_file', type=str, help='Path to the input file', required=True)
    args = argparser.parse_args()

    paths = list_all_matching_files(str(PATH_ROOT / args.input_file))
    print(paths)

    opcodes_X = extract_opcodes_from_binary(paths[0])
    n = len(opcodes_X)

    for path in paths[1:2]:
        opcodes_Y = extract_opcodes_from_binary(path)
        matches = compare_opcode_sequences(opcodes_X, opcodes_Y)
        m = len(opcodes_Y)

        plot_opcode_matrix(matches, n, m)
        print(f"{path}: {calculate_similarity(matches, n, m, 2):.4f}")

    # main(paths)
