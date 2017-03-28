# Targets
PROGS = serv

serv: 
	rm -f -R server/newsgroups
	cp -R server/newsgroups_def server/newsgroups
	rm -f -R *.o $(PROGS)
	rm -f lib/libclientserver.a
	rm -f server/mainserver
	cd lib && $(MAKE)
	cp lib/libclientserver.a server/
	cp lib/libclientserver.a client/
	cd server && $(MAKE)
	cd server && ./mainserver 7788 &
	rm -f output
	java -jar automatic.jar 127.0.0.1 7788 > output
	diff -w targetTestServer2 output
	pkill -9 -f ./mainserver
	cd client && $(MAKE)
	cd server && ./mainserver 8888 &
	cd client && ./client 127.0.0.1 8888 > output < testClientInput 
	diff -w client/corrCli13Output client/output
	pkill -9 -f ./mainserver
	rm -f server/mainserver
	rm -f client/client
	rm -f output
	rm -f client/output

all: $(PROGS)



# Phony targets
.PHONY: all clean serv

# Standard clean
clean:
	rm -f -R *.o $(PROGS)

# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
