import pandas as pd
import numpy as np

def check_species(data):
    violations = np.array(data["Species"].apply(lambda a : a not in ['setosa', 'versicolor', 'virginica']))
    print('Constraint: Species should be one of the following values: setosa, versicolor or virginica.')
    violation_count = np.count_nonzero(violations)
    if violation_count:
        print(violation_count, 'violations')
    else:
        print('No violations')
    return violation_count

def check_positive(data):
    violations = data.drop('Species', axis=1) < 0
    print('Constraint: All measured numerical properties of an iris should be positive.')
    violation_count = np.count_nonzero(violations)
    if violation_count:
        print(violation_count, 'violations')
    else:
        print('No violations')
    return violation_count

def check_petal_length(data):
    violations = np.array(data['Petal.Length'] < data['Petal.Width'] * 2)
    print('Constraint: The petal length of an iris is atleast 2 times its petal width.')
    violation_count = np.count_nonzero(violations)
    if violation_count:
        print(violation_count, 'violations')
    else:
        print('No violations')
    return violation_count

def check_sepal_length(data):
    violations = np.array(data['Sepal.Length'] > 30 )
    print('Constraint: The sepal length of an iris cannot exceed 30cm.')
    violation_count = np.count_nonzero(violations)
    if violation_count:
        print(violation_count, 'violations')
    else:
        print('No violations')
    return violation_count

def check_sepal_petal_length(data):
    violations = np.array(data['Sepal.Length'] <= data['Petal.Length'] )
    print('Constraint: The sepals of an iris are longer than its petals.')
    violation_count = np.count_nonzero(violations)
    if violation_count:
        print(violation_count, 'violations')
    else:
        print('No violations')
    return violation_count


rule_set = {
    'check_species': check_species,
    'check_positive': check_positive,
    'check_petal_length': check_petal_length,
    'check_sepal_length': check_sepal_length,
    'check_sepal_petal_length': check_sepal_petal_length
}
