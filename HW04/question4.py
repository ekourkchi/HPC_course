#!/usr/bin/python
import sys
import os
import subprocess
import math
import matplotlib.pyplot as plt
import numpy as np
import pylab as py
from astropy.table import Table, Column 



#attempt = 0.047
#flop = 0.22

#platform_filename = "cluster_1600.xml"
#hostfile_filename = "hostfile_1600.bin"
##code_exec = "./matmul_outerproduct_v3"
#code_exec = "./matmul_outerproduct_v1"



#matrix_size_list = np.arange(800,3280,80)
#num_process = 16

#n_iter = 10
#ave_total_time_list = [] 
#ave_compu_time_list = [] 
#ave_commu_time_list = [] 

#for matrix_size in matrix_size_list:
   #print " "
   #average_total_time = 0
   #average_compu_time = 0
   #average_commu_time = 0
   #for iteration in range(n_iter):
      
      #running_command = ["smpirun","--cfg=smpi/running_power:"+str(attempt),"-platform",platform_filename,"-hostfile",hostfile_filename,"-np",str(num_process),code_exec, '-n', str(matrix_size)]
      ##running_command = ["smpirun","--cfg=smpi/running_power:"+str(attempt),"-platform",platform_filename,"-hostfile",hostfile_filename,"-np",str(num_process),code_exec, '-n', str(matrix_size), '-f', str(flop)]
      #### Run the code
      #FNULL = open(os.devnull, 'w')
      #output = subprocess.check_output(running_command, stderr = FNULL)
      #FNULL.close()

      ##print output

      #lines = output.splitlines()
      #myString = lines[9] # 9 - 6
      #total_Time = myString.split(" ")[6]
      #myString = lines[10] # 10 - 7 
      #computation_Time = myString.split(" ")[4]
      #myString = lines[11] # 11 - 8
      #communication_Time = myString.split(" ")[4]
      ##print total_Time, computation_Time, communication_Time
      
      #average_total_time += float(total_Time)
      #average_compu_time += float(computation_Time)
      #average_commu_time += float(communication_Time)
      #print "size:", matrix_size, "iter #:", iteration, "Tot_time:", total_Time, "Compu_time:", computation_Time, "Commu_time:", communication_Time
   
   #average_total_time /= n_iter
   #average_compu_time /= n_iter
   #average_commu_time /= n_iter
   #ave_total_time_list.append(average_total_time)
   #ave_compu_time_list.append(average_compu_time)
   #ave_commu_time_list.append(average_commu_time)

###print matrix_size_list
###print ave_total_time_list
###print ave_compu_time_list
###print ave_commu_time_list


#myTable = Table()
#myTable.add_column(Column(data=matrix_size_list, name='matrix_size_list'))
#myTable.add_column(Column(data=ave_total_time_list, name='ave_total_time_list'))
#myTable.add_column(Column(data=ave_compu_time_list, name='ave_compu_time_list'))
#myTable.add_column(Column(data=ave_commu_time_list, name='ave_commu_time_list'))
#myTable.write('question4.txt', format='ascii.fixed_width',delimiter=',', bookend=False)
#print "question4.txt was created ..."

inFile = 'question5.txt'
table = np.genfromtxt( inFile , delimiter=',', filling_values=0, names=True, dtype=None)
matrix_size_list      = table['matrix_size_list']
ave_total_time_list   = table['ave_total_time_list']
ave_compu_time_list   = table['ave_compu_time_list']
ave_commu_time_list   = table['ave_commu_time_list']
   
## hostfile_filename = "hostfile_1600.bin"
## Results: 

# question4.txt
# In my first time, everything was done manually. 
#matrix_size_list = np.arange(800,3280,80)
#ave_total_time_list = [0.006, 0.006, 0.007, 0.007, 0.008, 0.008, 0.009, 0.01, 0.011, 0.013, 0.014, 0.014, 0.015100000000000002, 0.017500000000000005, 0.019299999999999998, 0.020499999999999997, 0.022299999999999997, 0.024299999999999995, 0.0256, 0.027800000000000002, 0.03130000000000001, 0.033400000000000006, 0.03570000000000001, 0.0377, 0.0397, 0.04459999999999999, 0.049699999999999994, 0.052000000000000005, 0.054400000000000004, 0.058899999999999994, 0.06439999999999999]
#ave_compu_time_list = [0.001, 0.001, 0.001, 0.002, 0.002, 0.002, 0.003, 0.003, 0.004, 0.005, 0.006, 0.007, 0.007800000000000001, 0.009399999999999999, 0.0101, 0.011099999999999997, 0.0127, 0.0142, 0.015600000000000003, 0.0171, 0.019899999999999998, 0.022099999999999998, 0.023399999999999997, 0.024999999999999998, 0.027500000000000004, 0.030800000000000004, 0.033800000000000004, 0.0373, 0.03849999999999999, 0.04189999999999999, 0.047299999999999995]
#ave_commu_time_list = [0.005, 0.005, 0.006, 0.006, 0.006, 0.006, 0.006, 0.006, 0.007, 0.007, 0.007, 0.007, 0.0081, 0.008200000000000002, 0.0093, 0.009399999999999997, 0.0093, 0.009899999999999999, 0.010199999999999999, 0.010599999999999998, 0.011299999999999998, 0.011499999999999998, 0.012199999999999999, 0.012399999999999998, 0.012199999999999999, 0.0137, 0.0159, 0.014900000000000002, 0.016200000000000003, 0.017300000000000003, 0.0171]



N = np.asarray(matrix_size_list)
t_total = np.asarray(ave_total_time_list)
t_computation = np.asarray(ave_compu_time_list)
t_communication = np.asarray(ave_commu_time_list)

fig = py.figure(figsize=(6, 5), dpi=100)
fig.subplots_adjust(hspace=0.15, top=0.95, bottom=0.15, left=0.15, right=0.95)

ax = fig.add_subplot(111)
plt.minorticks_on()
plt.tick_params(which='major', length=7, width=1.5)
plt.tick_params(which='minor', length=4, color='#000033', width=1.0) 


ax.plot(N, t_total/N**3, '-', markersize = 4, color='blue', label="Total Time",  lw=2) #linestyle="dotted"
ax.plot(N, t_computation/N**3, '-', markersize = 4,  color='red', label="Computation Time",  lw=2) #linestyle="dotted"
ax.plot(N, t_communication/N**3, '-', markersize = 4,  color='green', label="Communication Time", lw=2) #, linestyle="dotted"

#plt.xscale('log')
plt.yscale('log')
plt.xlim(0,30000)
#plt.ylim(0,10)

ax.set_xlabel('Matrix Size (N)', fontsize=14)
ax.set_ylabel('Time/'+r'$N^3$', fontsize=14)
ax.legend( loc=1 )
 
plt.show()



