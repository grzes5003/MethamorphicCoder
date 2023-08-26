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
            if '.dot' not in path and 'plots' not in path and 'toml' not in path and 'csv' not in path and 'txt' not in path]


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

    plt.text(0.5, -0.1, f"Similarity Score: {similarity_score:.2f}",
             horizontalalignment='center', verticalalignment='center', transform=plt.gca().transAxes)

    plt.show()


def plot_similarity_matrix(matrix, x_labels, y_labels):
    plt.figure(figsize=(10, 6))
    plt.imshow(matrix, cmap='coolwarm', aspect='auto')
    plt.colorbar()
    plt.xticks(range(len(y_labels)), y_labels, rotation='vertical')
    plt.yticks(range(len(x_labels)), x_labels)
    plt.xlabel("Opcode Numbers (Program Y)")
    plt.ylabel("Opcode Numbers (Program X)")
    plt.title("Opcode Similarity Matrix")
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

    for path in paths:
        opcodes_Y = exact_function(path)
        score, graph = calculate_similarity(opcodes_X, opcodes_Y)
        plot_similarity_matrix(graph, opcodes_X, opcodes_Y)
        # plot_opcode_matrix(matches, n, m,
        #                    score,
        #                    title=f'Opcode Matches Matrix for keylogger',
        #                    x_lab="base version",
        #                    y_lab=f"version {path.split(split_char)[-1].split('.')[0]}")
        print(f"{path}: {score:.4f}")

    # main(paths)
