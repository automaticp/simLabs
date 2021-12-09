# simLabs
Solutions to labs I had as part of the "Simulations of installations and experiments in physics" course at my uni. 

Contains three tiny libraries: distribution, histogram and simulation.

* 'Distribution' is a static lib that provides the capability to model some of more common statistical distributions in particle-matter interaction physics (Discrete, Exponential, Gaussian, Compton) through the virtual `getValue()` method.


* 'Histogram' is a header-only lib that can plot simple ASCII histograms through `cout`. Can work directly with objects from 'Distribution' through use of `USE_DISTRIBUTION` compile definition.


* 'Simulation' runs one-dimensional simulation of passage of gamma-particles through homogeneous matter of finite length. Models Compton scattering, photoelectric effect and pair production. Uses fairly primitive physics and quite limiting assumptions.

The `main` executable just plots a bunch of distibutions in console, and also plots the histogram of the deposited energy as a result of simulation runs.


# Why?
It's mostly a dummy project that I used to learn project management with cmake, git, github and such. 

Probably don't use this for anything serious.
