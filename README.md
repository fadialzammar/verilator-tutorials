# Verilator Tutorials

This repository contains a series of tutorials on using Verilator. Most of the examples can be generalized to any SystemVerilog design, but some are tailored specifically to the OTTER MCU.

The OTTER MCU is a RISC-V processor developed by the late Dr. Joseph Callenes-Sloan for the CPE 233 and 333 computer architecture courses at California Polytechnic State University, San Luis Obispo.

## Navigation

These tutorials are intended to be followed in the following order:

1. [Verilator Introduction](Introduction/README.md)
2. [Using Cocotb](Cocotb/README.md)
3. 

## Building

To build the documentation:

```sh
sudo apt install pandoc texlive-latex-recommended texlive-latex-extra
# build all documents
make all
# or, to build just a specific lesson
make FOLDER_NAME
```
