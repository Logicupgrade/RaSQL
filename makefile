CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) 

#******* RaSQL Driver************************
RaSQL : RaSQL.o RaSQL_User.o RaSQL_DB.o RaSQL_DB_Table.o
	$(CC) $(LFLAGS)  RaSQL.o -o RaSQL

RaSQL.o : RaSQL.cpp RaSQL_User.cpp RaSQL_DB.cpp RaSQL_DB_Table.cpp 
	$(CC) $(CFLAGS)  RaSQL.cpp
# **********************************************************
# *******Testing Graph************************
##links o files
# GraphTest : GraphTest.o  Graph.o Path.o
# 	$(CC) $(LFLAGS)  GraphTest.o  -o GraphTest
##Creates Driver o file
# GraphTest.o : GraphTest.cpp Graph.cpp Path.cpp
# 	$(CC) $(CFLAGS)  GraphTest.cpp
# *******************************************
# *******Testing Path************************
# PathTest : PathTest.o  Path.o
# 	$(CC) $(LFLAGS)  PathTest.o  -o PathTest

# PathTest.o : PathTest.cpp Path.cpp
# 	$(CC) $(CFLAGS)  PathTest.cpp
# *******************************************

RaSQL_User.o : RaSQL_User.cpp RaSQL_DB.cpp RaSQL_DB_Table.cpp
	$(CC) $(CFLAGS)  RaSQL_User.cpp

RaSQL_DB.o : RaSQL_DB.cpp RaSQL_DB_Table.cpp
	$(CC) $(CFLAGS)  RaSQL_DB.cpp

RaSQL_DB_Table.o : RaSQL_DB_Table.cpp
	$(CC) $(CFLAGS)  RaSQL_DB_Table.cpp
	

clean:
	\rm *.o RaSQL