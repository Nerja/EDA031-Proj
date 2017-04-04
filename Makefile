# Targets
PROGS = build

build:
	cd src/lib && $(MAKE) all
	cp src/lib/libclientserver.a src/server/
	cp src/lib/libclientserver.a src/client/
	cd src/server && $(MAKE) all
	cd src/client && $(MAKE) all

install:
	cp src/server/mainserver bin/
	cp src/server/memorymainserver bin/
	cp src/client/client bin/
	
test: 
	rm -f -R src/server/newsgroups
	cp -R src/server/newsgroups_def src/server/newsgroups
	rm -f -R *.o $(PROGS) all
	rm -f src/lib/libclientserver.a
	rm -f src/server/mainserver
	cd src/lib && $(MAKE) all
	cp src/lib/libclientserver.a src/server/
	cp src/lib/libclientserver.a src/client/
	cd src/server && $(MAKE) all
	cd src/server && ./mainserver 7888 &
	sleep 2
	rm -f output
	java -jar automatic.jar 127.0.0.1 7888 > output
	diff -w targetTestServer2 output
	pkill -9 -f ./mainserver
	sleep 1
	rm -f -R src/server/newsgroups
	cp -R src/server/newsgroups_def src/server/newsgroups
	cd src/client && $(MAKE) all
	cd src/server && ./mainserver 7889 &
	sleep 2
	cd src/client && ./client 127.0.0.1 7889 > output < testClientInput 
	diff -w src/client/corrCli13Output src/client/output
	pkill -9 -f ./mainserver
	rm -f src/server/mainserver
	rm -f src/client/client
	rm -f output
	rm -f -R src/server/newsgroups
	cp -R src/server/newsgroups_def src/server/newsgroups
	
all: $(PROGS)



# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f -R *.o $(PROGS)
	cd src/client && $(MAKE) clean
	cd src/server && $(MAKE) clean

# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
