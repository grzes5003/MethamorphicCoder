import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


def csv_to_df(path):
    df = pd.read_csv(path)
    df.dropna(inplace=True)
    return df


def prepare_df(df: pd.DataFrame, var):
    cols = ['jLZJD', 'ssdeep', 'matrix']
    df[cols] = df[cols] / df[cols].max()
    df['var'] = var
    return df


def plot_barplots(df: pd.DataFrame, y: str = 'jLZJD'):
    # plot_order = df.sort_values(by=y, ascending=False)['var'].values
    sns.barplot(data=df, x='var', y='jLZJD') #, order=plot_order)
    plt.title('Average jLZJD score for each program')
    plt.ylabel('jLZJD')
    plt.xlabel('Program')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()


def plot_barplots1(df: pd.DataFrame, y: str = 'jLZJD'):
    cols = ['jLZJD', 'ssdeep', 'matrix']
    df_group = df.groupby(['type'])[cols].mean()
    palette = sns.color_palette("rocket")

    plot_order = df_group.sort_values(by=y, ascending=False).index.values
    sns.barplot(data=df_group, x=df_group.index, y=y, order=plot_order, palette=palette)
    plt.title(f'Average {y} score for each program')
    plt.ylabel(y)
    plt.xlabel('Variant')
    plt.xticks(rotation=-90)
    plt.tight_layout()
    plt.show()


def plot(df: pd.DataFrame):
    cols = ['jLZJD', 'ssdeep', 'matrix']
    df_group = df.groupby(['type'])[cols].mean()
    df_group = df_group.sort_values(by=cols, ascending=True)
    sns.heatmap(data=df_group, annot=True, cmap=sns.cm.rocket_r)
    plt.title('Average score for each tool/input')
    plt.ylabel('Tool/Input')
    plt.xlabel('Metric')
    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    prefix = r"C:\Users\xgg\PycharmProjects\mgr-polymorphic\tested_programs"
    path = (prefix + r"\keylogger\compiled_programs\plots\results_comb.csv")

    df1 = csv_to_df(path)
    prepare_df(df1, 'keylogger')

    path = (prefix + r"\q_sort_java\results\results_comb.csv")

    df2 = csv_to_df(path)
    prepare_df(df2, 'q_sort_java')

    path = (prefix + r"\q-sort\compiled-programs\plots\results_comb.csv")

    df3 = csv_to_df(path)
    prepare_df(df3, 'q_sort_c')

    path = (prefix + r"\sample-program\compiled_code\plots\results_comb.csv")

    df4 = csv_to_df(path)
    prepare_df(df4, 'sample_program_c')

    path = (prefix + r"\sample_java\results\results_comb.csv")

    df5 = csv_to_df(path)
    prepare_df(df5, 'sample_program_java')

    df = pd.concat([df1, df2, df3, df4, df5])

    df['type'] = df['tool'] + '/' + df['input'].astype(str)
    plot(df)

    # plot_barplots1(df, 'jLZJD')
    # plot_barplots1(df, 'ssdeep')
    # plot_barplots1(df, 'matrix')
    ...
