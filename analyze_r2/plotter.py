import pandas as pd


def csv_to_df(path):
    df = pd.read_csv(path)
    df.dropna(inplace=True)
    return df


def prepare_df(df: pd.DataFrame, var):
    cols = ['jLZJD', 'ssdeep', 'matrix']
    df[cols] = df[cols] / df[cols].min()
    df['var'] = var
    return df


if __name__ == '__main__':
    path = (r"C:\Users\xgg\PycharmProjects\mgr-polymorphic\tested_programs"
            r"\keylogger\compiled_programs\plots\results_comb.csv")

    df = csv_to_df(path)
    prepare_df(df, 'keylogger')

    path = (r"C:\Users\xgg\PycharmProjects\mgr-polymorphic\tested_programs"
            r"\keylogger\compiled_programs\plots\results_comb.csv")

    df = csv_to_df(path)
    prepare_df(df, 'keylogger')

    path = (r"C:\Users\xgg\PycharmProjects\mgr-polymorphic\tested_programs"
            r"\keylogger\compiled_programs\plots\results_comb.csv")

    df = csv_to_df(path)
    prepare_df(df, 'keylogger')

    path = (r"C:\Users\xgg\PycharmProjects\mgr-polymorphic\tested_programs"
            r"\keylogger\compiled_programs\plots\results_comb.csv")

    df = csv_to_df(path)
    prepare_df(df, 'keylogger')

