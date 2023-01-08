import pandas as pd
import numpy as np
from itertools import cycle
from numpy.random import uniform


def generate_fake_dataframe(size, cols, col_names=None, intervals=None, seed=None):

    categories_dict = {'animals': ['cow', 'rabbit', 'duck', 'shrimp', 'pig', 'goat', 'crab', 'deer', 'bee', 'sheep', 'fish', 'turkey', 'dove', 'chicken', 'horse'],
                       'names': ['James', 'Mary', 'Robert', 'Patricia', 'John', 'Jennifer', 'Michael', 'Linda', 'William', 'Elizabeth', 'Ahmed', 'Barbara', 'Richard', 'Susan', 'Salomon', 'Juan Luis'],
                       'cities': ['Stockholm', 'Denver', 'Moscow', 'Marseille', 'Palermo', 'Tokyo', 'Lisbon', 'Oslo', 'Nairobi', 'Río de Janeiro', 'Berlin', 'Bogotá', 'Manila', 'Madrid', 'Milwaukee'],
                       'colors': ['red', 'orange', 'yellow', 'green', 'blue', 'indigo', 'purple', 'pink', 'silver', 'gold', 'beige', 'brown', 'grey', 'black', 'white']
                       }
    default_intervals = {"i": (0, 10), "f": (0, 100), "c": (
        "names", 5), "d": ("2020-01-01", "2020-12-31")}
    rng = np.random.default_rng(seed)

    first_c = default_intervals["c"][0]
    categories_names = cycle(
        [first_c] + [c for c in categories_dict.keys() if c != first_c])
    default_intervals["c"] = (categories_names, default_intervals["c"][1])

    if isinstance(col_names, list):
        assert len(col_names) == len(
            cols), f"The fake DataFrame should have {len(cols)} columns but col_names is a list with {len(col_names)} elements"
    elif col_names is None:
        suffix = {"c": "cat", "i": "int", "f": "float", "d": "date"}
        col_names = [
            f"column_{str(i)}_{suffix.get(col)}" for i, col in enumerate(cols)]

    if isinstance(intervals, list):
        assert len(intervals) == len(
            cols), f"The fake DataFrame should have {len(cols)} columns but intervals is a list with {len(intervals)} elements"
    else:
        if isinstance(intervals, dict):
            assert len(set(intervals.keys()) - set(default_intervals.keys())
                       ) == 0, f"The intervals parameter has invalid keys"
            default_intervals.update(intervals)
        intervals = [default_intervals[col] for col in cols]
    df = pd.DataFrame()
    for col, col_name, interval in zip(cols, col_names, intervals):
        if interval is None:
            interval = default_intervals[col]
        assert (hasattr(interval, '__call__') or (len(interval) == 2 and isinstance(interval, tuple)) or isinstance(
            interval, list))
        if col in ("i", "f", "d"):
            start, end = interval
        if col == "i":
            df[col_name] = rng.integers(start, end, size)
        elif col == "f":
            df[col_name] = rng.uniform(start, end, size)
        elif col == "c":
            if isinstance(interval, list):
                categories = np.array(interval)
                df[col_name] = rng.choice(categories, size, shuffle=True)
            elif hasattr(interval, '__call__'):
                df[col_name] = interval(df)
            else:
                raise ValueError('err')
        elif col == "d":
            df[col_name] = rng.choice(pd.date_range(start, end), size)
    return df

def data_gen(row):
    movement = row['movement']
    unexpected = row['unexpected']
    bpm = row['bpm']
    bpm_growth = row['bpm_growth']
    if unexpected == 'falling':
        return 'high'

    extremly_low_bpm = uniform(38,44)
    extremly_high_bpm = uniform(135,140)
    high_bpm = uniform(85,95)
    low_bpm = uniform(45, 60)
    high_bpm_growth = uniform(12,15)

    if movement == "null" and unexpected == "null":
        return None

    if bpm > extremly_high_bpm:
        return 'high'

    if bpm < extremly_low_bpm:
        return 'uncertain'

    if movement == 'rest':
        if bpm < high_bpm:
            return 'low'
        return 'medium'

    if movement == 'walking':
        if bpm < low_bpm:
            return 'low'
        if bpm < high_bpm:
            return 'medium'
        return 'high'
    

    if bpm < low_bpm:
        return 'uncertain'
    if bpm < high_bpm:
        return 'medium'
    return 'high'

def map_row(df):
    return df.apply(data_gen, axis=1)

def generator(num_rows):
    df = generate_fake_dataframe(
        num_rows,
        cols="ccffc",
        col_names=["movement", "unexpected", "bpm", "bpm_growth", "prediction"],
        intervals=[
            ["null", "rest", "running", "walking"],
            ["null", "erratic", "falling"],
            [35.0, 150.0],
            [-30.0, 35.0],
            map_row
        ]
    )

    return df[df['prediction'].notnull()]

if __name__ == '__main__':
    df = generator(300)
    print(df.to_string())
    df.to_csv('train_data.csv', index=False)
    df = generator(300)
    print(df.to_string())
    df.to_csv('test_data.csv', index=False)