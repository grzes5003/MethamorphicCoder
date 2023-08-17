import argparse
import os
import pathlib
import platform
from collections import defaultdict
import matplotlib.pyplot as plt
import numpy as np

import pefile

import capstone

PATH_ROOT = pathlib.Path(__file__).parent.parent.resolve()


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


def extract_opcodes_from_binary(binary_file):
    opcodes = []

    with open(binary_file, 'rb') as f:
        binary_data = f.read()

    # Use the Capstone library to disassemble the binary data
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)

    for insn in md.disasm(binary_data, 0x0):
        opcodes.append(insn.mnemonic)

    return opcodes


def extract_opcodes_from_binary_windows(binary_file):
    opcodes = []
    pe = pefile.PE(binary_file)

    eop = pe.OPTIONAL_HEADER.AddressOfEntryPoint
    code_section = pe.get_section_by_rva(eop)

    code_dump = code_section.get_data()

    code_addr = pe.OPTIONAL_HEADER.ImageBase + code_section.VirtualAddress

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)

    for i in md.disasm(code_dump, code_addr):
        opcodes.append(i.mnemonic + " " + i.op_str)

    return opcodes


def list_all_matching_files(file_path: str) -> list:
    dir = pathlib.Path(file_path).parent.resolve()
    print(dir)
    return [str(dir / path) for path in os.listdir(str(dir))
            if '.dot' not in path
            and 'plots' not in path
            and 'toml' not in path
            and 'csv' not in path]


def plot_opcode_matrix(matches, n, m, similarity_score, title: str = 'Opcode Matches Matrix',
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

    # plt.text(0.5, -0.1, f"Similarity Score: {similarity_score:.2f}",
    #          horizontalalignment='center', verticalalignment='center', transform=plt.gca().transAxes)

    plt.show()


if __name__ == "__main__":
    argparser = argparse.ArgumentParser()
    argparser.add_argument('-i', '--input_file', type=str, help='Path to the input file', required=True)
    args = argparser.parse_args()

    paths = list_all_matching_files(str(PATH_ROOT / args.input_file))
    print(paths)

    split_char = '/'
    exact_function = extract_opcodes_from_binary
    if platform.platform().startswith('Windows'):
        exact_function = extract_opcodes_from_binary_windows
        split_char = '\\'

    opcodes_X = exact_function(paths[0])
    n = len(opcodes_X)

    for path in paths:
        opcodes_Y = exact_function(path)
        matches = compare_opcode_sequences(opcodes_X, opcodes_Y)
        m = len(opcodes_Y)
        score = calculate_similarity(matches, n, m, 1)
        plot_opcode_matrix(matches, n, m,
                           score,
                           title=f'Opcode Matches Matrix for keylogger',
                           x_lab="base version",
                           y_lab=f"version {path.split(split_char)[-1].split('.')[0]}")
        print(f"{path}: {score:.4f}")

    # main(paths)
