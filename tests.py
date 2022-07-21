#!/bin/env python3
import sympy
import subprocess
import random


def generate_equation(n):
    return map(float, [random.triangular(low_coeff, high_coeff, mode_coeff) for i in range(n)])

def solve_symbolic(a, b, c):
    x = sympy.var('x')
    f = a*x**2 + b*x + c
    
    solution = sympy.solve(f, x)

    have_roots = True
    for root in solution:
        if not root.is_real:
            have_roots = False

    if have_roots:
        return map(float, solution)
    else:
        return None

def solve_execuatble(a, b, c, solver):
    solver_output = subprocess.check_output(
        solver,
        input=f"{a} {b} {c}",
        text=True
        )

    return solver_output.split('\n')[1]


high_coeff = 100500
low_coeff = -high_coeff
mode_coeff = 1050
accuracy = 0.001


a, b, c = generate_equation(3)
print(a, b, c)

res = solve_symbolic(a, b, c)
if res != None:
    for root in res:
        print(root, end=' ')
    print('')
else:
    print("No solutions")


print(solve_execuatble(a, b, c, "./quad"))


