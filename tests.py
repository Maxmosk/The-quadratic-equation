#!/bin/env python3
import sympy
import subprocess
import random


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

def run_test(test_n):
    high_coeff = 10005000
    low_coeff = -high_coeff
    mode_coeff = 100500
    accuracy = 0.001
    
    
    a, b, c = generate_equation(3, low_coeff, high_coeff, mode_coeff)
    
    sol_sym = solve_symbolic(a, b, c)
    sol_exe = solve_execuatble(a, b, c, "./quad")
    
    if is_equal(sol_sym, sol_exe, accuracy):
        print("TEST OK")
    else:
        print(a, b, c, sol_sym, sol_exe)


for i in range(1, 51):
    run_test(i)

