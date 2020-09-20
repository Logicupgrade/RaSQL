CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) 

#******* RaSQL Driver************************
RaSQL : RaSQL.o RaSQL_User.o RaSQL_DB.o RaSQL_Table.o RaSQL_Parser.o RaSQL_DB_Manager.o
	$(CC) $(LFLAGS)  RaSQL.o -o RaSQL

RaSQL.o : RaSQL.cpp RaSQL_User.cpp RaSQL_DB.cpp RaSQL_Table.cpp RaSQL_Parser.cpp RaSQL_DB_Manager.cpp
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

RaSQL_User.o : RaSQL_User.cpp RaSQL_DB.cpp RaSQL_Table.cpp
	$(CC) $(CFLAGS)  RaSQL_User.cpp

RaSQL_DB.o : RaSQL_DB.cpp RaSQL_Table.cpp
	$(CC) $(CFLAGS)  RaSQL_DB.cpp

RaSQL_Table.o : RaSQL_Table.cpp
	$(CC) $(CFLAGS)  RaSQL_Table.cpp

RaSQL_Parser.o : RaSQL_Parser.cpp
	$(CC) $(CFLAGS)  RaSQL_Parser.cpp

RaSQL_DB_Manager.o : RaSQL_DB_Manager.cpp RaSQL_Parser.cpp
	$(CC) $(CFLAGS)  RaSQL_DB_Manager.cpp

	

clean:
	\rm *.o RaSQL