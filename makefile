objs = getword.o sio.o table_lookup.o prep.o
dir = table_lookup

prep : $(objs)
	gcc -o prep $(objs) 
getword.o : getword.c
	gcc -c getword.c
prep.o : $(dir)/table_lookup.h
table_lookup.o : $(dir)/table_lookup.h $(dir)/table_lookup.c
	gcc -c $(dir)/table_lookup.c
sio.o : sio.h

clean :
	rm $(objs)
