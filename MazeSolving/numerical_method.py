import numpy as np

from scipy.optimize import fsolve

def equations(vars, m, n, alpha, beta):
    x, y = vars
    eq1 = n**2 - (m - y)**2 - x**2 - (m - y)**2 - (n - x)**2 + 2 * np.sqrt((m - y)**2 + x**2) * np.sqrt((m - y)**2 + (n - x)**2) * np.cos(beta)
    eq2 = m**2 - x**2 - y**2 - x**2 - (m - y)**2 + 2 * np.sqrt(x**2 + y**2) * np.sqrt(x**2 + (m - y)**2) * np.cos(alpha)
    return [eq1, eq2]


m = 27
n = 19  
alpha = 70
beta = 12

initial_guess = [0, 0]
x, y = fsolve(equations, initial_guess, args=(m, n, np.deg2rad(alpha), np.deg2rad(beta)))


print("x =", x)
print("y =", y)