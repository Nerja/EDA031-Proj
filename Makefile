# Targets
PROGS = serv

serv: 
	rm -f -R *.o $(PROGS)
	rm -f lib/libclientserver.a
	rm -f server/mainserver
	cd lib && $(MAKE)
	cp lib/libclientserver.a server/
	cd server && $(MAKE)

all: $(PROGS)



# Phony targets
.PHONY: all clean serv

# Standard clean
clean:
	rm -f -R *.o $(PROGS)

# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
