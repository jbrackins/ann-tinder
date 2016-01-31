# T.I.N.D.E.R.
C++ Artificial Neural Network T.I.N.D.E.R. TINDER stands for Tree Intelligence Network for Determining Ember Risk and is, to our knowledge, probably the first software program to ever have this name. Any other similarities in name are purely coincidental and are in no relation to the TINDER project and its morals or values.

TINDER stands for **T**ree **I**ntelligence **N**etwork for **D**etermining **E**mber **R**isk and is, to our knowledge, probably the first software program to ever have this name. Any other similarities in name are purely coincidental and are in no relation to the TINDER project and its morals or values.

# Repository Access
TINDER is hosted on a private git repository located at [https://github.com/jbrackins/ann-tinder](https://github.com/jbrackins/ann-tinder). To avoid compromising academic integrity, this project repo will remain private until a given point as per professor's request.

# Downloading TINDER
`git clone https://github.com/jbrackins/ann-tinder.git`

should suffice, but if you're stubborn you can always just download the .zip...
TINDER is not available on iPhone or Android, jeez, stop asking....

# Building TINDER
The following make scripts can be used for compilation: 

`make` will compile all three executables

`make ANNtrain` will compile the ANNtrain executable, the program for training the neural net on a given PDSI data set.

`make ANNtest` will compile the ANNtest executable, the program for testing the neural net to determine fire severity.

`make CrossValidate` will compile the CrossValidate executable, the program for testing the neural net using cross validation.

# Running TINDER
`./ANNtrain <parameterfile>`

`./ANNtest <parameterfile>`

`./CrossValidate<parameterfile>`

#Project Developers
* Julian B.
* Samuel C.
* Alex N.
