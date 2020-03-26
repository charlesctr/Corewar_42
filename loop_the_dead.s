.name "loop the dead"
.comment "sdcnkahflierjghv"

start: 		sti r1, %:boucle_end, %1

boucle_end: live %1
			zjmp %:boucle_end
