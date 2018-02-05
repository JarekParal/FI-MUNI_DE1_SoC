
module de1_soc_niosII_project (
	clk_clk,
	reset_reset_n,
	pio_0_output_led_external_connection_export,
	ps2_0_external_interface_CLK,
	ps2_0_external_interface_DAT);	

	input		clk_clk;
	input		reset_reset_n;
	output	[7:0]	pio_0_output_led_external_connection_export;
	inout		ps2_0_external_interface_CLK;
	inout		ps2_0_external_interface_DAT;
endmodule
