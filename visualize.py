#!/usr/bin/env python
import sys
import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    if len (sys.argv) < 2:
        print 'usage: %s <out.txt>' % sys.argv[0]
        sys.exit (0)

    data = np.loadtxt (sys.argv[1])

    plt.imshow (data)
    plt.show ()

    sys.exit (0)
