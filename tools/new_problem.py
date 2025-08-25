#!/usr/bin/env python3
import os
import shutil
import sys
from datetime import datetime

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
TEMPLATE = os.path.join(REPO, 'TEMPLATE')

def copy_template(dst):
    os.makedirs(dst, exist_ok=True)
    # copy main.cpp
    shutil.copy2(os.path.join(TEMPLATE, 'main.cpp'), os.path.join(dst, 'main.cpp'))
    # copy cases dir
    cases_src = os.path.join(TEMPLATE, 'cases')
    cases_dst = os.path.join(dst, 'cases')
    shutil.copytree(cases_src, cases_dst, dirs_exist_ok=True)

def main():
    if len(sys.argv) == 2:
        target = sys.argv[1]
    else:
        today = datetime.now().strftime('%Y-%m-%d')
        target = os.path.join('daily', today)

    dst = os.path.join(REPO, target)
    if os.path.exists(dst) and os.listdir(dst):
        print(f"Target not empty: {dst}", file=sys.stderr)
        sys.exit(1)

    copy_template(dst)
    print(dst)

if __name__ == '__main__':
    main()


