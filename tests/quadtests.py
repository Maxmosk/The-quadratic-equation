#!/bin/env python3
import sympy
import subprocess
import random
import wolframalpha
import os.path
import sys
from math import sqrt as sqrt



def generate_equation(n, low, high, mode):
    return map(float,
            [random.triangular(low, high, mode) for i in range(n)])


def solve_symbolic(a, b, c):
    x = sympy.var('x')
    f = a*x**2 + b*x + c
    
    solution = sympy.solve(f, x)

    have_roots = True
    for root in solution:
        if not root.is_real:
            have_roots = False

    if have_roots:
        return list(map(str, solution))
    else:
        return None


def solve_execuatble(a, b, c, solver):
    assert os.path.exists(solver), f'*** ERROR! File "{solver}" does not exists!!! ***'

    solver_output = subprocess.check_output(
        solver,
        input=f"{a} {b} {c}",
        text=True
        )
    
    if solver_output.split('\n')[1][0].isdigit() or solver_output.split('\n')[1][0] == '-':
        return list(solver_output.split('\n')[1].split())
    else:
        return None


def float_equal(x_1, x_2, accuracy):
    return abs(float(x_1) - float(x_2)) < accuracy


def is_equal(sol_1, sol_2, accuracy):
    if sol_1 == sol_2 and sol_1 == None:
        return True

    elif len(sol_1) == len(sol_2):
        if len(sol_1) == 1:
            return float_equal(sol_1[0], sol_2[0], accuracy)
        elif len(sol_1) == 2:
            return (float_equal(sol_1[0], sol_2[0], accuracy) and   \
                    float_equal(sol_1[1], sol_2[1], accuracy)) or   \
                    (float_equal(sol_1[1], sol_2[0], accuracy) and  \
                    float_equal(sol_1[0], sol_2[1], accuracy))

    else:
        for x in sol_1:
            for y in sol_2:
                if float_equal(x, y, accuracy):
                    return True
        
        return False


def parse_web_root(sol):
    start = max(sol.find('='), sol.find('≈')) + 1
    return str(eval(sol[start::]))


def solve_web(a, b, c):
    AppID = '5LR4QK-YPVPKAA9G5'
    client = wolframalpha.Client(AppID)
    response = client.query(f'{a}x^2 + {b}x + {c} = 0')

    if 'Solution' in response.details.keys():
        return parse_web_root(response.details['Solution'])

    elif 'Solutions' in response.details.keys():
        roots_sum = str(eval(response.details['Sum of roots']))
        root_1 = parse_web_root(response.details['Solutions'])
        return [root_1, str(float(roots_sum) - float(root_1))]

    else:
        return None


def run_test(test_file, test_n=None):
    high_coeff = 3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545885393053328527589376
    low_coeff = -high_coeff
    mode_coeff = 0
    accuracy = 0.001
   
    a, b, c = generate_equation(3, low_coeff, high_coeff, mode_coeff)
    
    sol_sym = solve_symbolic(a, b, c)
    sol_exe = solve_execuatble(a, b, c, test_file)
    sol_web = solve_web(a, b, c)

    if is_equal(sol_sym, sol_exe, accuracy) and is_equal(sol_sym, sol_web, accuracy) \
            and is_equal(sol_exe, sol_web, accuracy):
        print(f"TEST {test_n} OK" if test_n != None else "TEST OK")
        return True

    else:
        print(a, b, c, sol_sym, sol_exe, sol_web)
        return False


if len(sys.argv) != 2:
    print("*** ERROR IN COMMAND LINE ARGS ***")
    exit(0)

exe_file = sys.argv[1]
for i in range(1, 25 + 1):
    run_test(exe_file, i)

