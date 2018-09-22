.name "zork"
.comment "just a basic living prog"
		
	ld	%-112,r1 
	ld	%120,r2 
	sub r1,r2,r6
	and r1,r2,r3
	or	r1,r2,r4
	xor r1,r2,r5
	st	r1, 115
	st	r3, 111
	st	r4, 106
	st	r5, 102
