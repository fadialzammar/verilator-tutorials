---
title:  Verilator Introduction
author: Fadi Alzammar
geometry: margin=1in
colorlinks: true
---

# The OTTER MCU

If you are a Cal Poly student who has taken or is taking CPE 233 or CPE 333, you are definately familiar with the OTTER MCU. It is a RISC-V processor developed by Dr. Joseph Callenes-Sloan, who tragically passed away in December 2023, to replace the proprietary RAT MCU previously used by these courses. This not only taught students a relevant ISA used in academia and industry, but also modernized the course with support for compilers and open-source tools.

This lesson will go over how to integrate Verilator into the OTTER development process, but also should contain information useful for general designs.

# Verilating

In the [Introduction](../Introduction/README.md) lesson, we Verilated our counter with the following command:

```sh
verilator -Wall --trace --exe --build -cc tb.cpp counter.sv
```

We'll need to make a few changes. Firstly, because our design now includes multiple Verilog/SystemVerilog files, we need to inform Verilator on where to find all of them. This is done with the `-I` flag, which stands for include. # TODO

Verilator requires that the module name matches the file name exactly. In other words, for a SystemVerilog file that begins with `module ControlUnit`, the file expected to be named `ControlUnit.sv`. For this reason, it is also preferred to keep one module per file.

You'll know that this is causing a problem if you get an error like the following:

```sh
%Error: src/OTTER_Wrapper.sv:79:4: Cannot find file containing module: 'OTTER_MCU'
   79 |    OTTER_MCU MCU (.RESET(s_reset),.INTR(s_interrupt), .CLK(sclk), 
      |    ^~~~~~~~~
```

In this example, it is looking for a module named `OTTER_MCU` but cannot find it because the file is named `OTTER_CPU.sv`. The easiest solution to this is to rename the file. If you want to rename the module instead, make sure to also update any location where it is instantiated.

You may also encounter warnings like the following:

```sh
%Warning-WIDTHEXPAND: src/CU_Decoder.sv:122:38: Operator ASSIGN expects 4 bits on the Assign RHS, but Assign RHS's CONST '3'h3' generates 3 bits.
                                              : ... In instance OTTER_Wrapper.MCU.CU_DECODER
  122 |                     JAL: CU_PCSOURCE = 3'b011;
      |                                      ^
                      src/OTTER_CPU_baseline.sv:179:1: ... note: In file included from OTTER_CPU_baseline.sv
                      src/OTTER_Wrapper.sv:66:1: ... note: In file included from OTTER_Wrapper.sv
```

In `src/CU_Decoder.sv:122:38`, meaning the 38th character of line 122 in `CU_Decoder.sv`, `CU_PCSOURCE` is 4 bits wide, but gets assigned a 3 bit value. To resolve this, the assigned value should be changed to `4'b0011`. These zeros would normally be padded automatically, but this warning makes sure the RTL is clear, and may bring attention to a problem if this wasn't an expected problem.

Even if you don't have any errors caused by your code or file names, you may still encounter something like this:

```sh
%Error: Exiting due to 68 warning(s)
make: *** [Makefile:16: obj_dir/VOTTER_Wrapper] Error 1
```

Of course, the proper solution would be to address each of the warnings. Many of these warnings give important hints to design bugs that may exist. If there is a warning that truely cannot be resolved, there are ways to block off checking for that specific warning in a given block of code.

Realistically, getting rid of every warning every time may not be reasonable, especially for warnings over stylistic choices or for code that has already been thoroughly tested which you do not want to modify. In such cases, adding the `--Wno-fatal` flag to our command will make sure that warnings are not fatal to the Verilation process.

## Parameterizing the `.mem` file (Optional)
To make testing different programs on the OTTER easier, we can avoid navigating to the memory module of the design to change the file name by turning it into a parameter, and instead specify it as an arguement in our `verilator` command.

Verilator can only change top-level parameters, so you'll need to pass this all the way from the memory module to the wrapper. In my OTTER implementation, that meant adding the following line:

```sv
parameter string MEM_FILE = ""
```

in the module definitions of my `bram_dualport.sv`, `OTTER_CPU.sv`, and `OTTER_Wrapper.sv` files. Your file names, of course, may vary. Thinking about the parameter getting set at the top level, this then needs to float back down through each instantiation. My instantiation of `OTTER_CPU` inside of `OTTER_Wrapper`, for example, looks like:

<!-- #TODO: try ```cpp -->
```sv
OTTER_CPU #(.MEM_FILE(MEM_FILE)) MCU([signals]);
```

Similarly, the parameter will need to be passed down inside the `MCU` ot the `bram_dualport` module instantiation.

With this all done, we can set a value with the `-G` flag in Verilator, in the format `-G<name>=<value>`. Similarly to the `-I` flag, there is so space between the `G` and the parameter name. Putting everything together, this is what our Verilator command should look for a `mul.mem` memory file:

```
verilator -Wall --trace --exe --build -cc --Wno-fatal -I./src -GMEM_FILE='"mul.mem"' otter_tb.cpp OTTER_Wrapper.sv
```

If you're paying close attention, there's a good chance you're wondering why there's a combination of single and double quotes around `mul.mem`. We ultimately want `"mul.mem"` to be the exact value set in our SystemVerilog code, but with just a single set of quotes, the shell will parse this and turn it into `mul.mem` as an unquoted string. To avoid this, a second set of single quotes is added. The shell will parse and remove these, leaving the inner set of double quotes intact.

If you're running Verilator with a Makefile, which I'd highly recommend, we can take things *another* step further and set it as an environment variable. In my example [Makefile](./Makefile), I've included these defines:

```make
PROGRAM ?= mul
PARAMS = -GMEM_FILE='"mem/$(PROGRAM).mem"'
```

Because of the `?=` assignment, an existing environment variable will take precendent over this assignment. In the terminal, we can set this environment variable for just our `make` command by running it as

```sh
PROGRAM=matmul make
```

As a final note, the parameter must be set here during the Verilating process, not in our own C++ testbench. This is because the Verilated C++ model of our hardware depends on this parameter and cannot be built without it. Getting creative with the Makefile parameterization can still allow you to run different testbenches for different memory files without needing to change any code.

# TODO: 
 - changing waveform signal to int
 - reading/asserting internal values
 - running several unit tests together