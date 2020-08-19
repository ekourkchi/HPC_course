#/*****************************************************************
#//
#//  NAME:		Ehsan Kourkchi
#//
#//  HOMEWORK:		1
#//
#//  CLASS:		ICS 632
#//
#//  INSTRUCTOR:	Henri Casanova
#//
#//  DATE:		September 14, 2015           
#//
#//  FILE:		plot_time.py
#//
#//  DESCRIPTION:	This contains the program for making plots of the exersise 1
#//
#//****************************************************************/


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
  LLC_av = np.zeros((300,), dtype=np.dtype('int64'))

  
  all_files = glob.glob('./output.*.txt')
  for filename in all_files:
    

    
    mytable = Table.read(filename, format='ascii', delimiter=',')
    time  = mytable['time']
    time_av += time
    
    dcache = mytable['L1-dcache-load-misses']
    dcache_av += dcache
    LLC = mytable['LLC-load-misses']
    LLC_av += LLC
    

  time_av /= len(all_files)
  dcache_av /= len(all_files)
  LLC_av  /= len(all_files)
  
  fig = py.figure(figsize=(10, 10), dpi=100) # 8 -> 12
  fig.subplots_adjust(hspace=0.2, top=0.95, bottom=0.10, left=0.15, right=0.95)
  
  
  
  ax = fig.add_subplot(311)
  
  ax.plot(b, LLC_av, 'g.', linewidth=2)  
  ax.set_ylabel('LLC-load-misses', fontsize=12)
  
  ax.minorticks_on()
  ax.tick_params(which='major', length=7, width=1.5)
  ax.tick_params(which='minor', length=4, color='#000033', width=1.0) 
  ax.xaxis.set_major_locator(MultipleLocator(50))
  ax.xaxis.set_minor_locator(MultipleLocator(10))
  
  ax.plot([20,20], [4.0E7,7.5E7], '--', linewidth=1, color='black')  
  ax.plot([-5,301], [43683663.9, 43683663.9], linestyle='dotted', linewidth=1, color='black') 
  plt.xlim(-5,301)
  ##############################################################
  ax2 = fig.add_subplot(312)
  ax2.plot(b, dcache_av, 'r.', linewidth=2)
  ax2.set_ylabel('L1-dcache-load-misses', fontsize=12)

  ax2.minorticks_on()
  ax2.tick_params(which='major', length=7, width=1.5)
  ax2.tick_params(which='minor', length=4, color='#000033', width=1.0) 
  ax2.xaxis.set_major_locator(MultipleLocator(50))
  ax2.xaxis.set_minor_locator(MultipleLocator(10))  
  ax2.plot([20,20], [1.5E8,5.0E8], '--', linewidth=1, color='black') 
  ax2.plot([-5,301], [453080894.5, 453080894.5], linestyle='dotted', linewidth=1, color='black') 
  plt.xlim(-5,301)
  ##############################################################
  print "Min_time: ", min(time_av), time_av[19], dcache_av[19], LLC_av[19]
  ax3 = fig.add_subplot(313)
  ax3.plot(b, time_av, 'b.', linewidth=2)
  ax3.set_ylabel('Time [sec]', fontsize=12)
  ax3.set_xlabel('tile size (b)', fontsize=12)
  
  ax3.minorticks_on()
  ax3.tick_params(which='major', length=7, width=1.5)
  ax3.tick_params(which='minor', length=4, color='#000033', width=1.0) 
  ax3.xaxis.set_major_locator(MultipleLocator(50))
  ax3.xaxis.set_minor_locator(MultipleLocator(10))  
  ax3.plot([20,20], [1.5,2.4], '--', linewidth=1, color='black') 
  ax3.plot([-5,301], [2.01, 2.01], linestyle='dotted', linewidth=1, color='black')
  plt.xlim(-5,301)
  ##############################################################
  
  
  plt.savefig('HW01_cluster.png', dpi=100)
  plt.show()