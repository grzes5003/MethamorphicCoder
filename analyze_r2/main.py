import argparse
import pathlib
import r2pipe


PATH_ROOT = pathlib.Path(__file__).parent.parent.resolve()


def analyze(file_path: str, output_file: str) -> None:
    r2 = r2pipe.open(str(PATH_ROOT / file_path))
    r2.cmd('aaa')
    r2.cmd(f'agCd > {output_file}')
    r2.quit()


if __name__ == '__main__':
    argparse = argparse.ArgumentParser()
    argparse.add_argument('-i', '--file_path', type=str, required=True, help='Path to the file to analyze from content root')
    argparse.add_argument('-o', '--output_file', type=str, help='Path to the output file', required=False)

    args = argparse.parse_args()

    if args.output_file is None:
        args.output_file = args.file_path + '_graph.dot'

    print(str(PATH_ROOT / args.file_path))
    analyze(args.file_path, args.output_file)

