#!/usr/bin/python
import sys
import os
import subprocess
import math
import matplotlib.pyplot as plt
import numpy as np
import pylab as py



#attempt = 0.047
#platform_filename = "cluster_1600_ideal.xml"
##platform_filename = "cluster_1600.xml"
#hostfile_filename = "hostfile_1600.bin"
#code_exec = "./matmul_outerproduct_v1"



#matrix_size = 1600
#num_process_list = [1, 4, 16, 64, 100, 400, 1600]

#n_iter = 10
#ave_time_list = [] 

#for num_process in num_process_list:
   #print " "
   #average = 0
   #for iteration in range(n_iter):
      
      #running_command = ["smpirun","--cfg=smpi/running_power:"+str(attempt),"-platform",platform_filename,"-hostfile",hostfile_filename,"-np",str(num_process),code_exec, '-n', str(matrix_size)]
      #### Run the code
      #FNULL = open(os.devnull, 'w')
      #output = subprocess.check_output(running_command, stderr = FNULL)
      #FNULL.close()

      ## print output

      #lines = output.splitlines()
      #myString = lines[9]
      #total_Time = myString.split(" ")[6]
      #myString = lines[10]
      #computation_Time = myString.split(" ")[4]
      #myString = lines[11]
      #communication_Time = myString.split(" ")[4]
      ##print total_Time, computation_Time, communication_Time
      
      #average += float(total_Time)
      #print "np:", num_process, "iter #:", iteration, "time:", total_Time
   
   #average /= n_iter
   #ave_time_list.append(average)

#print num_process_list
#print ave_time_list



## hostfile_filename = "hostfile_1600.bin"
## Results: 
## [1, 4, 16, 64, 100, 400, 1600]
## [0.152, 0.028, 0.013, 0.021, 0.025, 0.021, 0.042]

### platform_filename = "cluster_1600_ideal.xml"
### [1, 4, 16, 64, 100, 400, 1600]
### [0.153, 0.024, 0.007, 0.002, 0.001, 0.0, 0.0]

t0 = 0.152
n_process = np.asarray([1, 4, 16, 64, 100, 400, 1600])
t = np.asarray([0.152, 0.028, 0.013, 0.021, 0.025, 0.021, 0.042])
t_ideal = np.asarray([0.152, 0.024, 0.007, 0.002, 0.001, 0.0, 0.0])


fig = py.figure(figsize=(6, 5), dpi=100)
fig.subplots_adjust(hspace=0.15, top=0.95, bottom=0.15, left=0.15, right=0.95)

ax = fig.add_subplot(111)
plt.minorticks_on()
plt.tick_params(which='major', length=7, width=1.5)
plt.tick_params(which='minor', length=4, color='#000033', width=1.0) 


ax.plot(n_process, t0/t, 'o', markersize = 4, color='blue', label="real", linestyle="dotted", lw=2)
ax.plot(n_process, t0/t_ideal, 'o', markersize = 4,  color='red', label="ideal", linestyle="dotted", lw=2)

plt.xscale('log')
plt.yscale('log')

ax.set_xlabel('# of prcoess', fontsize=14)
ax.set_ylabel('Speed-up', fontsize=14)
ax.legend( loc=1 )
 
plt.show()

