## Gravity Simulator Engine
This project is a  multi-purpose package for solving n-body problems numerically. It takes in a user-written script with a description of parameters of the simulation, such as the initial state conditions, the choice of integration scheme, the timestep of integration, and the frequency and the format of the output.

**`Ubuntu`**  | [![Build Status](https://travis-ci.com/mitya-tsarev/GravitySimulator.svg?branch=master)](https://travis-ci.com/mitya-tsarev/GravitySimulator)

## Installation, building, and running
This project can be built with CMake. To do this, go into the project's root directory and perform the standard 
```
mkdir build
cd build
cmake ..
make
```
You can now run the GravitySimulator executable, passing an input file as a flag. For example, you can run a script from the examples repository:
```
cd ../examples/
../build/GravitySimulator figure-eight.in 
```

## Documentation
### Units
We use the "Astronomical Unit, Solar Mass, Year" units. The constant G equals to 4π<sup>2</sup> in this units system. All the quantitative input has to be expressed in this unit system, and all the output is represented in this unit system.
### The first line of the input script must specify an integration scheme.
Currently, Simple Euler, Simple Runge-Kutta, Barnes-Hut Euler, and Barnes-Hut Runge-Kutta are available. Simple integrator evaluates the accelerations of each body each timestep using pairwise interactions, spending n<sup>2</sup> operations. Euler and Runge-Kutta are the methods of performing a step once the accelerations of the bodies are calculated. The first line must start with the keyword ```method```. Next keywords must specify the integrator. Possible lines are:<br />
```method Simple Euler```<br />
```method Simple RungeKutta```<br />
```method Barnes-Hut Euler 0.05```<br />
```method Barnes-Hut RungeKutta 0.1```<br />
If the Barnes-Hut integrator is chosen, you have to specify the tolerance parameter tau of the Barnes-Hut scheme.
### The second line must specify the timestep of integration. 
The line has to start with ```timestep``` keyword followed by a number. Expample:<br />
```timestep 0.0001```<br />
### Creating bodies
There are two possible ways of creating bodies in the simulation. The first one is ```create body``` command. It must be followed by 7 numbers specifying the mass, three coordinates, and three velocities. The second option is ```create cluster``` command, which creates a cluster of bodies with the specified distributions of masses, coordinates, and velocities. In this case, you have to specify mass distribution using the keyword ```mass``` followed by a keyword for the type of distribution. Currently, ```constant``` and ```uniform``` distributions are available. Constant distribution means the mass of all the bodies in the cluster would be the same. The keyword ```constant``` must be followed with one number, and the ```uniform``` keyword must be followed with two numbers specifying the boundaries of the distribution. Same as for the ```mass```, one has to specify the distributions of ```x```, ```y```, ```z```, ```vx```, ```vy```, and ```vz```. Example:<br />
```create cluster n 100 mass constant 0 x uniform 3 4 y constant 0 z constant 0 vx constant 0 vy uniform 3.1 3.6 vz constant 0```
### Setting the position of barycenter and momentum of the existing system
```set barycenter``` command followed by three numbers sets the barycenter of the existing bodies to the specified coordinates by shifting the whole system. ```set momentum``` command followed by three numbers sets the components momentum of the existing bodies to the three values by adding the same vector to the velocities of all the bodies. Note: if any bodies are added after the ```set``` command, the quantities that were set could change. Example: <br />
```set barycenter 0 0 0```<br />
```set momentum 0 0 0```
### Generating output
The package gives two kinds of output: per body output and global output. Per body output is saved in .vtu files and contains the positions of bodies and scalar properties for each body. The command is ```save perbody``` followed by a filename and (possibly) several keywords specifying the scalar per-body output. ```mass``` and ```velocity``` keywords are currently available. Example:<br />
```save perbody myPerbodyFilename mass velocity```<br />
Global output is characteristics of the entire system, such as kinetic energy or total momentum. Global output is saved in a single file and printed out in the console. The command is ```save global``` followed by a filename and (possibly) several keywords specifying the output. ```time```, ```potentialenergy```, ```kineticenergy```, ```totalenergy```, ```momentumx```, ```momentumy```, ```momentumz```, ```barycenterx```, ```barycentery```, ```barycenterz``` keywords are currently available. Example:<br />
```save global myGlobalFilename time potentialenergy kineticenergy totalenergy momentumy barycenterz```<br />
The frequency of the output is defined by ```nframes``` command. It has to be followed by an integer specifying the number of output frames during the simulation. Example:<br />
```nframes 1000```
### Running
The length of the simulation is defined by ```run``` command followed by the desired time of simulation. Example:<br />
```run 10```














