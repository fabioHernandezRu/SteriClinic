module frecGen(reset,clock,IN,OUT);
input clock,reset;
input [31:0]IN;
output OUT;
reg [31:0]conteo;
reg out_tmp;
always @(posedge clock, negedge reset)
begin
	if(!reset)
	begin
		conteo<=32'd0;
	end
	else
	begin
		if (conteo >=IN) conteo<= 0;
		else conteo <= conteo+1;
	end
end	

always @(posedge clock, negedge reset)
begin
	if(!reset)
	begin
		out_tmp=1'b0;
	end
	else
	begin
		if (conteo >=IN) out_tmp<=!out_tmp;
		else out_tmp <= out_tmp;
	end
end

assign OUT = out_tmp;


endmodule