IDIR=include
ODIR=src/server/obj
GPP=g++
CFLAGS = -std=c++11
BIN = ucirc_server
LDLIBS = -lrt -lpthread -lboost_system

#  _DEPS = client.h handler.h messages.h
# DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = handler.o main.o messages.o reply.o simclist.o tec.o \
      crontab.o util.o TEC/MeComAPI/MePort_Linux.o \
      TEC/MeComAPI/private/MeCom.o TEC/MeComAPI/private/MeCRC16.o \
      TEC/MeComAPI/private/MeFrame.o TEC/MeComAPI/private/MeInt.o \
      TEC/MeComAPI/private/MeVarConv.o TEC/ComPort/ComPort_Linux.o \
      TEC/ConsoleIO_Linux.o
 
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: src/server/%.c $(DEPS)
	$(GPP) -c -o $@ $^ -I$(IDIR) -I/home/labuser/Boost/boost_1_62_0 -L/home/labuser/Boost/boost_1_62_0/stage/lib -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/home/labuser/Boost/boost_1_62_0  $(CFLAGS)

$(BIN): $(OBJ) 
	$(GPP) -o $@ -I$(IDIR) -I/home/labuser/Boost/boost_1_62_0 -I/home/labuser/Boost/boost_1_62_0/boost/interprocess -I/home/labuser/Boost/boost_1_62_0/boost/asio -L/home/labuser/Boost/boost_1_62_0/stage/libs -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/home/labuser/Boost/boost_1_62_0 $(OBJ) $(CFLAGS) $(LDLIBS) 

 %.d: %.c 

clean: 
	rm -f $(ODIR)/*.o
	rm -f $(ODIR)/ComPort/*.o
	rm -f $(ODIR)/MeComAPI/*.o
	rm -f $(ODIR)/MeComAPI/private/*.o
	rm -f $(BIN) 
