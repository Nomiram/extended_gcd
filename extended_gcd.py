from numpy import prod
def extended_gcd(a, b):
    '''
    Расширенный алгоритм Евклида
    return НОД, коэф1, коэф2
    '''
    old_r, r = a, b
    old_s, s = 1, 0
    old_t, t = 0, 1
    
    while r != 0:
        quotient = int(old_r/r)
        old_r, r = r, old_r - quotient * r
        old_s, s = s, old_s - quotient * s
        old_t, t = t, old_t - quotient * t
    
    # print("коэффициенты Безу:", (old_s, old_t))
    # print("наибольший общий делитель:", old_r)
    # print("частные от деления на НОД:", (t, s))
    return old_r, old_s, old_t
def chinese_remainder_theorem(a, m):
    '''
    Китайская теорема об остатках
    Arguments - вектор остатков a, вектор модулей m
    Returns - решение системы уравнений
    '''
    assert len(a) == len(m)
    x = 0
    i = 1
    M = prod(m)
    # print("M = ", M)
    for i in range(len(a)):
        b = M/m[i]
        # print("M"+str(i),"= ", b)
        _,c,_ = extended_gcd(b,m[i])
        if c <0: c+=m[i]
        # print(c)
        x += a[i]*b*c
    return x % M
if __name__ == "__main__":
    # extended_gcd(240,46)
    # res = chinese_remainder_theorem([2,15,5],[5,17,12])
    
    res = chinese_remainder_theorem([1,2,6],[2,3,7])
    print("result: ", res)
