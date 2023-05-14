---
title:  Verilator Introduction
author: Fadi Alzammar
date: \today
geometry: margin=1in
colorlinks: true
---

# Introduction

## What is Verilator?

Verilator is a free, open-source tool for converting Verilog and SystemVerilog code to a cycle-accurate C++[^1] model. This model can then be run to simulate the behavior of our circuit. Simulating this way, as opposed to the traditional timestep-based approach directly from HDL in tools such as Xilinx Vivado, has several advantages:

- The simulation only needs to update each signal when there is a change to it, rather than every timestep. This means that simulations run *much* faster.
- We have the full power of C++ available to us. Though waveforms are definately useful, we can also port our data into any program we can make to analyze the data, including even a [[VGA simulator]]!
	- Similarly, programming our testbenches in C++ allows us to easily complex scenerios that would be a huge pain to do in (System)Verilog
- It is easy to analyse [[code coverage]], showing you what parts of your HDL are most commonly used (if at all!). This is a great process for determining where you should place your focus when trying to impove the performance of a circuit.

# Installing Verilator

Verilator can easily be installed from most package managers. For Debain/Ubuntu-based operating systems, this can be done with: 

```sh
sudo apt install verilator
```

If you have specific requirements beyond the scope of these guides, you may need to follow instructions on Verilator's [installation page](https://veripool.org/guide/latest/install.html) to build from source.

## Other Software

In addition to Verilator, we will be using GTKWave, an open-source waveform viewer, after running our simulations. Similarly, it can be installed with:

```sh
sudo apt install gtkwave
```

I will also be including instructions to integrate Verilator into Visual Studio Code, a popular code editor. I'd recommend installing this directly from [their website](https://code.visualstudio.com/) for more frequent updates than a package manager.

# Our First Verilated Module

## The HDL

As a simple example, let's begin with a simple counter. Below is the SystemVerilog code for the module.

```systemverilog
module counter #(
    parameter BITS = 8) (
    input clk,
    input reset,
    output logic [BITS-1:0] count
    );

    always_ff @ (posedge clk) begin
        if (reset)
            count <= 0;
        else
            count <= count + 1;
    end
endmodule
```

## C++ Testbench

Now for the actual Verilator part. I will include my full testbench below, then deep-dive into what each part is doing.

```cpp

```
# Verilating the Otter



[^1]: Verilator can also convert to SystemC, but that will be outside the scope of these guides.