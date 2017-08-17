## PID implementation
There are two parameter to be controlled, one is the steering wheel angle, another is the throttle. I have individual PID controller instance to be used for each of the parameters. The steering wheel controller's target is make CTE as close as to 0, and the throttle controller's target is make speed close to a predefined target speed (in my case is 60KM/h)


## Tuning the PID Parameters

I approached this problem by going over 2 steps:
1. Initialize the PID and tune it manually until it can run over one lap successfully.
2. Use Twiddle to optimize the parameters to make it behave better

### P, I, D parameters

P causes the controller to response proportional to the error. Its main influence can be seen as the responsiveness of the controller to an error. If the error increases very fast as in a sharp turn, P must be high enough to provide enough reactivity. Too much reactivity will cause an overshoot, causing undesired oscillations.

D is proportional to the error derivative and is aims at flattening the error trajectory into a horizontal line, dampens the action applied, to reduce the oscillations brought by P.

I is proportional to the integral of the error. It is used to increases action in relation not only to the error but also the time for which it has persisted. So, if applied action is not enough to bring the error to zero, I will be increased as time pass. 

### Manually tuning the parameters

First start with P and set I and D to 0. I gradually increase it for 0.1 each time until the car can approach the first corner. At this time, it's overshoot a lot and not sensitive enough.

To make it more sensible to small error, I increase D for 1 each time, until the car can go over the bridge. It's still oscillations a lot.

Finally, I set a small value to I, but the effect the hard to inspect visually. I left it for twiddle.

### Finely optimizing with Twiddle

To get better performances, I implemented twiddle to automatically search for better parameters based on the accumulated squared cross track error, over a fixed number of steps. 

The implementation of twiddle is under the `src/twiddle.cpp` and `src/twiddle.hpp` files. And the invoke of the twiddle class is triggered by a marco in `src/main.cpp` in line 7, by uncomment the define `DO_TWIDDLE`, program will start to do twiddle optimization and restart the simulator also reinitialize the PIDs after 2000 time steps.

First, I started with my manually tuned values for P I D: 0.3, 0.0001, 6.
I ran twiddle over the first 2000 steps with target speed 60km/h, which enough to make the car go over the last corner.

I got as a result for P I D: 0.366776,0.000689087,20.25935. Which reduce the error for the beginning 180 to 24. 


