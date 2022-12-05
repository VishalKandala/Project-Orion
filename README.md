# Working Title
This C++ code is written by Team Nebula for Project 3 of MEEN 689 Computing Concepts course.

This code simulates the heat conduction in a spherical body with multiple layers of different material compositions of varying thicknesses.

This code is based on the Implicit Solution of the Backward in Time- Central in Space (BTCS) discretization of the One Dimensional heat equation.

$$\frac{\partial T}{\partial t } = \alpha\frac{\partial^{2} T}{\partial x^{2} }$$

$$-{\lambda T_{i+1}^{n+1}}  - \lambda T_{i-1}^{n+1} + (1 + 2\lambda)(T_{i+1}^{n}) = T_{n}^{i}$$

With Neumann Boundary conditions applied at both boundaries. 

$$ Q=-k\frac{\partial T}{\partial x}$$

Discretizing the boundaries using ghost points, we get the following linear system.
$$ A*T^{n+1} = T_{n} + B$$
$$
A 
-2\lambda , 1 +2 , 3 
4 , 5 , 6 
7 , 8 , 9
$$
and $B = [2*Q[0]*\alpha[0]*\Delta x]$


The Linear system obtained from BTCS formulation is solved using an optimized Tridiagonal Matrix Solver based on Thomas Algorithm (TDMA).

  
## Dependencies

- Compiler: g++
- Python3
  - matplotlib
  - Numpy

## Installation

Clone the current git repository and compile using the following commands.
```bash
make all
```
This will output the following, which confirms installation
```bash
g++ -c -o main.o main.cpp
g++ -c -o setup.o setup.cpp
g++ -c -o solver.o solver.cpp
g++ -c -o data.o data.cpp
g++ -o 1dheat main.o setup.o solver.o data.o
rm -f *.o
```
If you want to keep the object files you can use
```bash
make 1dheat
```
## Usage
### Solver
To run a simulation, type in the following:
```bash
./1dheat
```
This would first prompt you to enter how verbose your terminal output would be.
```bash
Please select how verbose you would like the solver output:
```
You could enter the following values:
 
Input: Output

1: Basic information; $\lambda$ , No. of nodes , Grid size $\Delta x$ , Time step $\Delta t$ , No. of time steps , $\frac{Q}{k}$*

2: Matrix A

3: Vector B 

4: Matrix A after forward elimination in TDMA

5: Vectors $T^{n+1}$ $T^{n}$ at desired time step **


*"you can choose the location to display $\frac{Q}{k}$ in main.cpp"

**"You can choose time step to display $T^{n+1}$ $T^{n}$ in Push_T() function in solver.cpp"


Then you would be prompted to input the desired grid size
```bash
How many grid points would you like? (More points equals a finer mesh)
```
Following this, you would be prompted to input the time step size.
```bash
How small would you like your time step size? (seconds)
```
This is followed by asking for the simulation time in seconds.

```bash
How long would you like to run the solver? (seconds)
```

Then you are asked the frequency at which to save the time history, followed by the config file name and the layup choice along with the Boundary condition choice.
```bash
How often would you like the solver to save the data? (Save every X iterations)
What is the name of the config file containing the necessary material properties?
Which material layup would you like to check? (1-4)
What boundary condition are you testing?
BC1: Heat flux applied to one boundary.
BC2: Symmetric heat flux along the surface.
Input 1 for BC1 and 2 for BC2..
```
If you choose BC1 it would apply a heat flux on one end of the 1D domain (i.e radial) and an adiabatic condition on the other end.

If you choose BC2 it would apply a heat flux at both ends and give you an option to add insulation(felt) on both sides of the domain.

```bash
What boundary condition are you testing?
BC1: Heat flux applied to one boundary.
BC2: Symmetric heat flux along the surface.
Input 1 for BC1 and 2 for BC2...
2
Would you like to add more felt insulation? (y/n)
y
Specify the thickness of felt insulation to be added. (meters)
10.0
```
The program would output information based on verbose selection and also outputs the time(seconds) at which the temperature profile is stored in /data folder.

At the end of the run, it would output the CPU time (ms) for the Thomas Algorithm solver averaged over all the time steps.
### Visualization

visualize.py produces a 3D plot of the temperature distribution at a given timestep and at a layer that we choose.

To run this, use the following:
```bash
python3 visualize.py <time> <layer>
```
The two arguments that this takes are:
$<time>$: specifies the time at which the profile is visualized

$<layer>$: specifies the layer which is visualized 
## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
