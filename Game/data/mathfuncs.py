def factorial(N):
    if N == 0:
        return 1
    else:
        return N * factorial(N-1)

def P(N, K):
    return (factorial(N)//factorial(N-K))
    
def C(N, K):
    return (factorial(N)//factorial(N-K)*factorial(K))
