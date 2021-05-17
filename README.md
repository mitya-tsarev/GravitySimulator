## Gravity Simulator Engine
This project is a  multi-purpose package for solving n-body problems numerically. It takes in a user-written script with a description of parameters of the simulation, such as the initial state conditions, the choice of integration scheme, the timestep of integration, and the frequency and the format of the output.
## Installation, building, and running.

## Documentation.
The first line of the input script must specify an integration scheme. Currently, Simple Euler, Simple Runge-Kutta, Barnes-Hut Euler, and Barnes-Hut are available. Simple integrator evaluates the accelerations of each body each timestep using pairwise interactions, spending n^2 operations. Euler and Runge-Kutta are the methods of performing a step once the accelerations of the bodies are calculated. The first line must start with the keyword ```method```. Next keywords must specify the integrator. Possible lines are:<br />
```method Simple Euler```<br />
```method Simple RungeKutta```<br />
```method Barnes-Hut Euler 0.05```<br />
```method Barnes-Hut RungeKutta 0.1```<br />
If the Barnes-Hut integrator is chosen, you have to specify the tolerance parameter tau of the Barnes-Hut scheme.
