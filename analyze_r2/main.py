import argparse
import os
import pathlib
import r2pipe


PATH_ROOT = pathlib.Path(__file__).parent.parent.resolve()


def analyze(file_path: str, output_file: str) -> None:
    r2 = r2pipe.open(str(PATH_ROOT / file_path))
    r2.cmd('aaa')
    r2.cmd(f'agCd > {str(PATH_ROOT / output_file)}')
    r2.quit()


def list_all_matching_files(file_path: str) -> list:
    return [str(path) for path in os.listdir(file_path) if 'exe' in path]


if __name__ == '__main__':

    argparse = argparse.ArgumentParser()
    argparse.add_argument('-o', '--output_file', type=str, help='Path to the output file', required=False)
    group = argparse.add_mutually_exclusive_group(required=True)
    group.add_argument('-i', '--file_path', type=str, help='Path to the file to analyze from content root')
    group.add_argument('-b', '--batch', type=str, help='Batch mode', required=False)

    args = argparse.parse_args()

    if args.output_file is None and args.file_path is not None:
        args.output_file = args.file_path + '_graph.dot'
    if args.batch:
        for file in list_all_matching_files(str(PATH_ROOT / args.batch)):
            print(args.batch + '/' + file)
            analyze(args.batch + '/' + file, args.batch + '/' + file + '_graph.dot')
    print(str(PATH_ROOT / args.file_path))
    # analyze(args.file_path, args.output_file)

