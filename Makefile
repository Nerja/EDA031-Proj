# Targets
PROGS = serv

serv: 
	rm -f -R *.o $(PROGS)
	rm -f lib/libclientserver.a
	rm -f server/mainserver
	cd lib && $(MAKE)
	cp lib/libclientserver.a server/
	cp lib/libclientserver.a client/
	cd server && $(MAKE)
	cd server && ./mainserver 7778 &
	java -jar automatic.jar 127.0.0.1 7778 > output
	diff -w targetTestServer2 output
	pkill -9 -f ./mainserver
	cd client && $(MAKE)	
	rm -f server/mainserver
	rm -f client/client

all: $(PROGS)



# Phony targets
.PHONY: all clean serv

# Standard clean
clean:
	rm -f -R *.o $(PROGS)

# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
