
				...
				module mod_exp
					
					...
					`UPDATE: begin
						
						if (exponent_reg != 'd0) begin
							
							if (exponent_reg[0])
								
								result_reg <= result_next;
								
							base_reg <= base_next;
							exponent_reg <= exponent_next;
							state <= `UPDATE;
							
						
					...
					
				endmodule
			
		  	