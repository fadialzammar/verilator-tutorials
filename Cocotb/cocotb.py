import cocotb
from cocotb.triggers import FallingEdge, Timer
from cocotb.clock import Clock

@cocotb.test()
async def count_10(dut):
    cocotb.start_soon(Clock(dut.clk, 1, units="ns").start())

    # await Timer(5, units="ns")  # wait a bit
    # await FallingEdge(dut.clk)  # wait for falling edge/"negedge"

    dut._log.info("my_signal_1 is %s", dut.my_signal_1.value)
    assert dut.my_signal_2.value[0] == 0, "my_signal_2[0] is not 0!"