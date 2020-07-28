target := TCP_Server TCP_Client UDP_Server UDP_Client 

all: $(target)

clean :
	rm -f $(target) 
