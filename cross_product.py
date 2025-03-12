import numpy as numpy

def cross_product(x, y):
  x = np.zeros(3,3)
  x[0,1] = -x[2]
  x[0,2] = x[1]


  z = np.dot(x,y)
  return z


def identify_rot(R):
  r0 = R[0,:]
  r1 = R[1,:]
  //길이 1인지 판단.
  //내적 0인지 판다.
  pass;