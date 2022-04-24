# github.com
# Hello World - GitHub Docs
# csvdic.py
import pandas as pd
url = "https://raw.githubusercontent.com/husthorng/hello-world/horng_1/110hiwinstud.csv"
name_records = pd.read_csv(url,encoding='utf-8')
name_records = name_records.to_dict('records')
print(name_records[0])
for x in name_records:
    print(x)
print(name_records[0]['學號'])
