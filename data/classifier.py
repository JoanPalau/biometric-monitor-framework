from micromlgen import port
from sklearn.tree import DecisionTreeClassifier
from sklearn.datasets import load_iris
import csv

def get_x_y(path):

    with open('train_data.csv', newline='') as f:
        reader = csv.reader(f)
        data = list(reader)[1:]

    mov = ["null", "rest", "running", "walking"]
    err = ["null", "erratic", "falling"]
    cls = ["uncertain", "low", "medium", "high"]

    def map_row(row):
        a, a2, b, c, d = row
        return (mov.index(a), err.index(a2), float(b), float(c)), cls.index(d)

    def mapped_to_X(row):
        return row[0]

    def mapped_to_Y(row):
        return row[1]
    data = list(map(map_row, data))
    X = list(map(mapped_to_X, data))
    y = list(map(mapped_to_Y, data))
    return X, y


clf = DecisionTreeClassifier(max_depth=4)
# X, y = load_iris(return_X_y=True)
X, y = get_x_y('train_data.csv')
# print(X)
# print(y)
clf.fit(X, y)
X, y = get_x_y('test_data.csv')
print('Score', clf.score(X, y))
# print(port(clf))
with open('code.ino', 'w+') as f:
    f.write(port(clf))