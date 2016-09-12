`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:31:09 06/04/2009 
// Design Name:    Jose Pablo Pinilla
// Module Name:    PWM 
// Project Name:   
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module PWM #(parameter Bits_counter = 8, Periodo=8'd250)
	 (	input  clk, input reset, output motor, input  [Bits_counter-1:0] duty_cycle);
	//en este modulo hay un conteo de 0 a 100 con la variable timer1 dentro de este conteo tenemos un condicianal
	//con la variable de entrada duty_cicle, si timer1 es menor a duty_cicle la variable PWM_OUTPUT tiene un 
	//valor de 1 y si la valiable timer1 es mayor que la variable duty_cicle cambia de valor con esto se genera
	//el pwm la salida la variable motor es igual a la concatenacion de PWM_OUTPUT con cero, la cual esta
	// es la variable que se le envia al motor.
   reg [Bits_counter-1:0] Timer1=0;
   reg PWM_OUTPUT;
   always @(posedge clk, negedge reset)
	begin
		if(!reset)
		begin
			Timer1 <= 0;
			PWM_OUTPUT<=1'b0;
		end
		else
		 begin
			if (Timer1 >= Periodo)
				begin
						Timer1 <= 0;
						PWM_OUTPUT<=PWM_OUTPUT;
				end		
			else
				begin
					  Timer1 <= Timer1+1; 
					  if (Timer1 >= duty_cycle)
					  begin
							 PWM_OUTPUT<=1'b0;
					  end
					  else
					  begin 
							PWM_OUTPUT <= 1'b1;		  
					  end 
				end
		end	
	end
	
	
	
	assign motor = PWM_OUTPUT; 
	
	
endmodule

