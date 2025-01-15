CXX = g++
CXXFLAGS = -Wall -Wextra -g3 -I.
LDFLAGS = -mconsole

SOURCES = main.cpp Operacoes.cpp Compra.cpp Relatorio.cpp Usuario.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = sistema_controle_financeiro.exe

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXEC)
