
module DE1_SoC_QSYS (
	clk_clk,
	clk_sdram_clk,
	key_external_connection_export,
	pll_locked_export,
	ps2_0_external_interface_CLK,
	ps2_0_external_interface_DAT,
	reset_reset_n,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	video_vga_controller_0_external_interface_CLK,
	video_vga_controller_0_external_interface_HS,
	video_vga_controller_0_external_interface_VS,
	video_vga_controller_0_external_interface_BLANK,
	video_vga_controller_0_external_interface_SYNC,
	video_vga_controller_0_external_interface_R,
	video_vga_controller_0_external_interface_G,
	video_vga_controller_0_external_interface_B,
	pll_25mhz_locked_export);	

	input		clk_clk;
	output		clk_sdram_clk;
	input	[3:0]	key_external_connection_export;
	output		pll_locked_export;
	inout		ps2_0_external_interface_CLK;
	inout		ps2_0_external_interface_DAT;
	input		reset_reset_n;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output		video_vga_controller_0_external_interface_CLK;
	output		video_vga_controller_0_external_interface_HS;
	output		video_vga_controller_0_external_interface_VS;
	output		video_vga_controller_0_external_interface_BLANK;
	output		video_vga_controller_0_external_interface_SYNC;
	output	[7:0]	video_vga_controller_0_external_interface_R;
	output	[7:0]	video_vga_controller_0_external_interface_G;
	output	[7:0]	video_vga_controller_0_external_interface_B;
	output		pll_25mhz_locked_export;
endmodule
