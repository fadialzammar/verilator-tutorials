module counter #(
    parameter BITS = 8) (
    input clk,
    input reset,
    output reg [BITS-1:0] count
    );

    always @ (posedge clk) begin
        if (reset)
            count <= 0;
        else
            count <= count + 1;
        // if (count >= 8'h0F)
        //     $finish;
    end

endmodule
