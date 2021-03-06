import pandas as pd
import numpy as np

def check_age_range(data):
    a = np.array(data["Age"].apply(lambda a : a in range(151)))
    print('Violation: Age not in range 0 to 150')
    if False in a:
        print(len(a) - np.count_nonzero(a), 'violations')
    else:
        print('No violations')
        
def age_greater_years_married(data):
    a = np.array(data[["Age", "yearsmarried"]].apply(lambda x : x[0] > x[1], axis=1))
    print('Violation: Age is less than years married')
    if False in a:
        print(len(a) - np.sum(a), 'violations')
    else:
        print('No violations')
        
def check_status(data):
    check = lambda s : s in ['married', 'single', 'widowed']
    a = np.array(data['status'].apply(check))
    print('Violation: status not married, single or widowed')
    if False in a:
        print(len(a) - np.sum(a), 'violations')
    else:
        print('No violations')
        
def check_agegroup(data):
    
    def check(d):
        age = int(d[0])
        if age < 18:
            return d[1] == 'child'
        elif age >= 18 and age <= 65:
            return d[1] == 'adult'
        elif age > 65:
            return d[1] == 'elderly'

    a = np.array(data[['Age','agegroup']].apply(check, axis = 1))
    print('Violation: age group not according to age')
    if False in a:
        print(len(a) - np.sum(a), 'violations')
    else:
        print('No violations')

rule_set = {
    'check_age_range': check_age_range,
    'age_greater_years_married': age_greater_years_married,
    'check_status': check_status,
    'check_agegroup': check_agegroup
}
