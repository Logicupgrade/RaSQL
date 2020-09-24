CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) 

#******* RaSQL Driver************************
RaSQL : RaSQL.o RaSQL_Parser.o RaSQL_DB_Manager.o #RaSQL_User.o RaSQL_DB.o RaSQL_Table.o
	$(CC) $(LFLAGS)  RaSQL.o -o RaSQL

RaSQL.o : RaSQL.cpp RaSQL_Parser.cpp RaSQL_DB_Manager.cpp # RaSQL_User.cpp RaSQL_DB.cpp RaSQL_Table.cpp
	$(CC) $(CFLAGS)  RaSQL.cpp

# **********************************************************

# RaSQL_User.o : RaSQL_User.cpp RaSQL_DB.cpp RaSQL_Table.cpp
# 	$(CC) $(CFLAGS)  RaSQL_User.cpp

# RaSQL_DB.o : RaSQL_DB.cpp RaSQL_Table.cpp
# 	$(CC) $(CFLAGS)  RaSQL_DB.cpp

# RaSQL_Table.o : RaSQL_Table.cpp
# 	$(CC) $(CFLAGS)  RaSQL_Table.cpp

RaSQL_DB_Manager.o : RaSQL_DB_Manager.cpp RaSQL_Parser.cpp
	$(CC) $(CFLAGS)  RaSQL_DB_Manager.cpp

RaSQL_Parser.o : RaSQL_Parser.cpp
	$(CC) $(CFLAGS)  RaSQL_Parser.cpp

	
clean:
	\rm *.o RaSQL

#deletes RaSQL's DBs and Tables
reset:
	# make
	# ./RaSQL<PA1_test.sql
	
	#removes database files
	cd RaSQL_dbs; \rm *.txt
	#removes table files
	cd RaSQL_tables; \rm *txt