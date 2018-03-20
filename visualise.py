import numpy as np
from matplotlib import pyplot as plt



m = np.loadtxt("FILES/vert1.txt",skiprows=1)
# edges = np.loadtxt("ans1.txt",dtype=np.int)

x,y = m.T
plt.plot(x,y)


# plt.plot(x[edges.T], y[edges.T], 'r-')

for x in range(m.shape[0]):
	plt.text(m[x,0] + 0.05,m[x,1]+0.05,str(x))

plt.show()