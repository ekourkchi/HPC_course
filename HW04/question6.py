#!/usr/bin/python
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



def outRead(folder, prefix, suffix):
  
    ave_total_time_list = [] 
    ave_compu_time_list = [] 
    ave_commu_time_list = [] 


    average_total_time = []
    average_compu_time = []
    average_commu_time = []
    for size in range(800,10080,80):
    #for size in range(800,880,80):
      
      average_total_time = []
      average_compu_time = []
      average_commu_time = []
      
      all_files = glob.glob(folder+prefix+str(size)+suffix)
      

      #print len(all_files)
      for file in all_files:
	  #print file
	  output = open(file, 'r')
	  lines = output.readlines()
	  myString = lines[9] 
	  total_Time = myString.split(" ")[6]
	  myString = lines[10]
	  computation_Time = myString.split(" ")[4]
	  myString = lines[11] 
	  communication_Time = myString.split(" ")[4]
	  average_total_time.append(float(total_Time))
	  average_compu_time.append(float(computation_Time))
	  average_commu_time.append(float(communication_Time))
      
      average_total_time = np.std(average_total_time) / np.average(average_total_time)
      average_compu_time = np.std(average_compu_time) / np.average(average_compu_time)
      average_commu_time = np.std(average_commu_time) / np.average(average_commu_time)
      ave_total_time_list.append(average_total_time)
      ave_compu_time_list.append(average_compu_time)
      ave_commu_time_list.append(average_commu_time)

    
    t_total = np.asarray(ave_total_time_list)
    t_computation = np.asarray(ave_compu_time_list)
    t_communication = np.asarray(ave_commu_time_list)
    
    return t_total, t_computation, t_communication

####



matrix_size_list = range(800,10080,80)
N = np.asarray(matrix_size_list)

#t_total, t_computation, t_communication = outRead('MPI_uhhpc/','size-','-iter-*-*.txt')
#t_total, t_computation, t_communication = outRead('MPI_mtmoran/','size-','-iter-*-*.txt')
#t_total, t_computation, t_communication = outRead('OMP_mtmoran/','size-','-iter-*-*.omp.txt')



fig = py.figure(figsize=(6, 5), dpi=100)
fig.subplots_adjust(hspace=0.15, top=0.95, bottom=0.15, left=0.15, right=0.95)

ax = fig.add_subplot(111)
plt.minorticks_on()
plt.tick_params(which='major', length=7, width=1.5)
plt.tick_params(which='minor', length=4, color='#000033', width=1.0) 


beta = N**3
beta = 1

#t_total, t_computation, t_communication = outRead('MPI_mtmoran/','size-','-iter-*-*.txt')
t_total, t_computation, t_communication = outRead('MPI_uhhpc/','size-','-iter-*-*.txt')
#t_total, t_computation, t_communication = outRead('OMP_uhhpc/','size-','-iter-*-*.omp.txt')

ax.plot(N, t_total/beta, 'o', markersize = 4, color='black')#, label="Total Time",  lw=2) 
#ax.plot(N, t_computation/beta, 'o', markersize = 4,  color='black') #, label="Computation Time",  lw=1) #linestyle="dotted"
#ax.plot(N, t_communication/beta, 'o', markersize = 4,  color='black') #, label="Communication Time", lw=2) #, linestyle="dotted"


t_total, t_computation, t_communication = outRead('OMP_uhhpc/','size-','-iter-*-*.omp.txt')
#t_total, t_computation, t_communication = outRead('OMP_mtmoran/','size-','-iter-*-*.omp.txt')
#t_total, t_computation, t_communication = outRead('MPI_mtmoran/','size-','-iter-*-*.txt')

ax.plot(N, t_total/beta, 'o', markersize = 4, color='blue')#,  lw=1, linestyle="dashed") 
#ax.plot(N, t_computation/beta, 'o', markersize = 4,  color='blue') #,  lw=1, linestyle="dashed")
#ax.plot(N, t_communication/beta, 'o', markersize = 4,  color='blue') #, lw=1)









#plt.xscale('log')
##plt.yscale('log')
plt.xlim(0,10000)
plt.ylim(0,0.25)

ax.set_xlabel('Matrix Size (N)', fontsize=14)
ax.set_ylabel(r'$\sigma_T / T_{av}$', fontsize=14)
ax.legend( loc=2 )
 
plt.show()



