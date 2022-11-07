from itertools import product
from math import prod

def chinese_remainder(primes, a):
    sum, mod = 0, prod(primes)
    for p_i, a_i in zip(primes, a):
        n = mod // p_i
        print("mul", mul_inv(n, p_i))
        sum += a_i * mul_inv(n, p_i) * n
    return sum % mod
 
def mul_inv(a, b):
# extended Euclid algo. Return x such ax = 1 (mod b)
    b0 = b
    x0, x1 = 0, 1
    if b == 1: return 1
    while a > 1:
        q = a // b
        a, b = b, a%b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0: x1 += b0
    return x1

print(chinese_remainder([5,17,12],[2,15,5]))
# m = [[1], [2,1], [3,2], [3,2], [10,3], [11,9], [9,8,7,6]]
# primes = [2, 3, 5, 7, 11, 13, 17]

# res = list(product(*m))
# for i, v in enumerate(sorted([chinese_remainder(primes, x) for x in res]), 1):
    # print(i,v)