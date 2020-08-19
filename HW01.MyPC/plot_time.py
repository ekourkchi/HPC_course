from time import time
import sys
import os
import numpy as np
from math import *
import glob
from astropy.table import Table, Column 
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator, FormatStrFormatter
import pylab as py



#################################################################

      
if __name__ == '__main__':
  
  
  b = np.arange(1,301,1)
  time_av = np.zeros((300,), dtype=np.dtype('float64'))
  dcache_av = np.zeros((300,), dtype=np.dtype('int64'))

  
  all_files = glob.glob('./output.*.txt')
  for filename in all_files:
    

    
    mytable = Table.read(filename, format='ascii', delimiter=',')
    time  = mytable['time']
    time_av += time
    
    dcache = mytable['L1-dcache-load-misses']
    dcache_av += dcache
    

  time_av /= len(all_files)
  dcache_av /= len(all_files)
  
  fig = py.figure(figsize=(10, 8), dpi=100) # 8 -> 12
  fig.subplots_adjust(hspace=0.2, top=0.95, bottom=0.10, left=0.15, right=0.95)
  
  
  

  ax2 = fig.add_subplot(211)
  ax2.plot(b, dcache_av, 'r.', linewidth=2)
  ax2.set_ylabel('L1-dcache-load-misses', fontsize=12)

  ax2.minorticks_on()
  ax2.tick_params(which='major', length=7, width=1.5)
  ax2.tick_params(which='minor', length=4, color='#000033', width=1.0) 
  ax2.xaxis.set_major_locator(MultipleLocator(50))
  ax2.xaxis.set_minor_locator(MultipleLocator(10))  
  ax2.plot([13,13], [1.0E8,5.0E8], '--', linewidth=1, color='black') 
  ax2.plot([-5,301], [333275724.7, 333275724.7], linestyle='dotted', linewidth=1, color='black') 
  plt.xlim(-5,301)
  ##############################################################
  
  ax3 = fig.add_subplot(212)
  ax3.plot(b, time_av, 'b.', linewidth=2)
  ax3.set_ylabel('Time [sec]', fontsize=12)
  ax3.set_xlabel('tile size (b)', fontsize=12)
  
  ax3.minorticks_on()
  ax3.tick_params(which='major', length=7, width=1.5)
  ax3.tick_params(which='minor', length=4, color='#000033', width=1.0) 
  ax3.xaxis.set_major_locator(MultipleLocator(50))
  ax3.xaxis.set_minor_locator(MultipleLocator(10))  
  ax3.plot([13,13], [0,1.6], '--', linewidth=1, color='black') 
  ax3.plot([-5,301], [0.563, 0.563], linestyle='dotted', linewidth=1, color='black')
  plt.xlim(-5,301)
  plt.ylim(0, 1.5)
  ##############################################################
  print "Min_time: ", min(time_av), time_av[13], dcache_av[13]
  
  plt.savefig('HW01_desktop.png', dpi=100)
  plt.show()