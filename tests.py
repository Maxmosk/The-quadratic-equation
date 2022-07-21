#!/bin/env python3
import sympy
import subprocess
import random

high_coeff = 100500
low_coeff = -high_coeff
mode_coeff = 1050
accuracy = 0.001

a = random.triangular(low_coeff, high_coeff, mode_coeff)
b = random.triangular(low_coeff, high_coeff, mode_coeff)
c = random.triangular(low_coeff, high_coeff, mode_coeff)
print(a, b, c)

x = sympy.var('x')
f = a*x**2 + b*x + c

solution = sympy.solve(f, x)

have_roots = True
for root in solution:
    if not root.is_real:
        have_roots = False

if have_roots:
    sympy.pprint(solution)

solver_output = subprocess.check_output(
        "./quad",
        input=f"{a} {b} {c}",
        text=True
        )

print(solver_output)

