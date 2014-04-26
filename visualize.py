#!/usr/bin/env python
import sys
import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    if len (sys.argv) < 2:
        print 'usage: %s <out.txt>' % sys.argv[0]
        sys.exit (0)

    data = np.loadtxt (sys.argv[1])

    fig = plt.figure ()
    ax = fig.add_subplot (111)

    ax.imshow (data, cmap=plt.cm.gray_r)
    ax.axis ('off')

    plt.show ()

    fig.savefig ('out.png', dpi=fig.dpi, bbox_inches='tight')

    sys.exit (0)
