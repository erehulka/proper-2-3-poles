## Analysis of proper (2,3)-poles

### About the project

This algorithm generates all proper (2,3)-poles from given snarks, analyzes their colouring
properties and saves the results in csv file. It is used as the main tool in bachelor's thesis by Erik
Řehulka, "Analysis of colouring properties of proper (2, 3)-poles".

To run this program, you need to have the library [ba_graph](https://bitbucket.org/relatko/ba-graph/src/master/) 
installed on your computer.

---

### Installation

First of all, you need to create the Makefile by `cp Makefile.dist Makefile`. Then, 
replace `<path to ba graph library>` with the absolute path to the _ba_graph_ library on your 
computer. Then to compile the program run `make all`.

### Running the analysis

This algorithm uses files with graphs in graph6 format, each on separate line. Usually
you should put these files in the inputs directory, created during installation, or 
inputs_bicritical to analyze bicritical snarks. Then, there are multiple possibilities 
to run the algorithm:
- run `make run_all_inputs`. This will run the algorithm for each file in the inputs folder 
  and save the outputs in the outputs folder.
- run `make run_all_bicritical_inputs`. This will run the algorithm for each file in the 
  inputs_bicritical folder and save the outputs in the outputs_bicritical folder.
- run `./main.out <input file relative path> "<output directory relative path>"`. This will
  run the algorithm for the given file and save the outputs in the provided output directory.
  An example of this may be `./main.out ./inputs/graph.g6 "./outputs/"`.