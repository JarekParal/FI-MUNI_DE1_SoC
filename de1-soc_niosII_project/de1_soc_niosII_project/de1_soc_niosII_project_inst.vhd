	component de1_soc_niosII_project is
		port (
			clk_clk                                     : in    std_logic                    := 'X'; -- clk
			reset_reset_n                               : in    std_logic                    := 'X'; -- reset_n
			pio_0_output_led_external_connection_export : out   std_logic_vector(7 downto 0);        -- export
			ps2_0_external_interface_CLK                : inout std_logic                    := 'X'; -- CLK
			ps2_0_external_interface_DAT                : inout std_logic                    := 'X'  -- DAT
		);
	end component de1_soc_niosII_project;

	u0 : component de1_soc_niosII_project
		port map (
			clk_clk                                     => CONNECTED_TO_clk_clk,                                     --                                  clk.clk
			reset_reset_n                               => CONNECTED_TO_reset_reset_n,                               --                                reset.reset_n
			pio_0_output_led_external_connection_export => CONNECTED_TO_pio_0_output_led_external_connection_export, -- pio_0_output_led_external_connection.export
			ps2_0_external_interface_CLK                => CONNECTED_TO_ps2_0_external_interface_CLK,                --             ps2_0_external_interface.CLK
			ps2_0_external_interface_DAT                => CONNECTED_TO_ps2_0_external_interface_DAT                 --                                     .DAT
		);

