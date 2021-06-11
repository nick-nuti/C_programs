# C_programs
Just basic C programs

1. /FIR FILTER: is a 16-bit fixed-point matrix MAC with added ability to shift in a biasing neuron and apply ReLU to layer outputs
  - fir_test.c
    - testbench for fir filter that contains matrices of variable input size
    - implementation contains two layers:
        - layer 1 = (input matrix) MAC (theta 1 matrix) -> shift in biasing one neuron -> apply ReLU
        - layer 2 = (layer 1 matrix) MAC (theta 2 matrix) -> apply ReLU
  - fir.c
    - contains the function for calculating matrix MAC, function includes an attribute for including a biasing neuron, and end of the function contains ReLU

2. rpn_calc_postfix.c
  - Program that uses linkedlists to achieve the functionality of a reverse-polish notation calculator

3. 
