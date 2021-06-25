import numpy as np
import h5py
import math
import pandas as pd
import matplotlib.pyplot as plt
import vtk
from vtk.util.numpy_support import vtk_to_numpy


time_step = int(input("Enter the time step at which you want to plot Resultant Velocity : "))
no_of_bodies = int(input("Enter the number of bodies in simulation : "))

time = 'Time_'+str(time_step)

f =  h5py.File('hdf_R0N0.h5', 'r')
ls = list(f.keys())

u_data = f[time]['Ux']
v_data = f[time]['Uy']

#pdata = pd.DataFrame(data)
npu_data = np.array(u_data)
npv_data = np.array(v_data)

cols = list(npu_data.shape)[0]
rows = list(npu_data.shape)[1]

x = np.linspace(0,2.5,cols)
y = np.linspace(0,0.41,rows)

X, Y = np.meshgrid(x,y)

resultant = np.zeros(cols*rows).reshape(cols,rows)

for i in range(0,cols):
	for j in range(0,rows):
		resultant[i][j] = math.sqrt((npu_data[i][j])**2 + (npv_data[i][j])**2)

plt.contourf(X,Y, resultant.T,levels=500, cmap='bwr')
plt.colorbar()

for n in range(no_of_bodies):
	filename = "vtk_out.Body"+str(n)+"."+str(n)+"."+str(time_step)+".vtk"

	reader = vtk.vtkPolyDataReader()
	reader.SetFileName(filename)
	reader.ReadAllScalarsOn()
	reader.Update()

	nodes_vtk_array = reader.GetOutput().GetPoints().GetData()
	nodes_nummpy_array = vtk_to_numpy(nodes_vtk_array)
	x,y = nodes_nummpy_array[:,0] , nodes_nummpy_array[:,1]

	plt.plot(x, y, color = 'k', linewidth=1.5)

#plt.fill_between(circle_x_array, top_y_array, bottom_y_array, interpolate = True, color = 'mintcream')
plt.axes().set_aspect('equal')
plt.savefig(str(time_step)+"_ResultantVel.png", dpi = 300)
