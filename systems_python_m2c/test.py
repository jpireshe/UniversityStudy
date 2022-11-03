import exrex

regexList = exrex.generate('[a-b]{2}')
a = [next(regexList) for i in range(4)]
print(a)