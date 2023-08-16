import argparse
import os
import pathlib
from pathlib import Path

import networkx as nx

PATH_ROOT = pathlib.Path(__file__).parent.parent.resolve()


def list_all_matching_files(file_path: str) -> list:
    dir = Path(file_path).parent.resolve()
    print(dir)
    return [str(dir / path) for path in os.listdir(str(dir)) if '.dot' in path]


def cmp_graphs(graph, graph2) -> bool:
    return nx.graph_edit_distance(graph, graph2)


def nmatch(n1, n2):
    return True


def read_dot(path: str) -> nx.DiGraph:
    return nx.drawing.nx_pydot.read_dot(path)


def cmp_all(target, paths):
    g0 = read_dot(target)
    print('graph loaded')
    for path in paths:
        g1 = read_dot(path)
        print(f"Comparing {target} and {path}")
        res = cmp_graphs(g0, g1)
        print(f"{path}, {res}")


if __name__ == '__main__':
    argparser = argparse.ArgumentParser()
    argparser.add_argument('-i', '--input_file', type=str, help='Path to the input file', required=True)
    args = argparser.parse_args()

    paths = list_all_matching_files(str(PATH_ROOT / args.input_file))
    print(paths)

    cmp_all(str(PATH_ROOT / args.input_file), paths)
