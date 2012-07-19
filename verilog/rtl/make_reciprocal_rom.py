#
# Create a table that computes 1/x
# The input and output will be a normalized significand with an implicit leading one.
#

import math

NUM_ENTRIES = 1024	# Must be power of two

WIDTH = int(math.log(NUM_ENTRIES, 2))

print '''
//
// This file is autogenerated by make_reciprocal_rom.py
//

module reciprocal_rom(
	input [''' + str(WIDTH - 1) + ''':0]			addr_i,
	output reg ['''  + str(WIDTH - 1) + ''':0]	data_o);

	always @*
	begin
		case (addr_i)'''


for x in range(0, NUM_ENTRIES):
	significand = NUM_ENTRIES | x
	reciprocal = int((NUM_ENTRIES * NUM_ENTRIES * 2) / significand)
	print '\t\t\t%d\'h%x: data_o = %d\'h%x;' % (WIDTH, x, WIDTH, reciprocal & (NUM_ENTRIES - 1)),
	print '// 1.0 / ' + str(float(significand) / NUM_ENTRIES) + ' = ' + str(float(reciprocal) / NUM_ENTRIES)
	
print '''		endcase
	end
endmodule
'''
