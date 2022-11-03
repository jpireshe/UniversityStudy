import ray
import time

ray.init(log_to_driver=False)

@ray.remote
def foo(x):
    time.sleep(5)
    #print(x*x)
    return(x*x)

#f1r = foo(5)

f1 = foo.remote(5)
f2 = foo.remote(6)

f1r = ray.get(f1)
f2r = ray.get(f2)

print(f1r)
print(f2r)

