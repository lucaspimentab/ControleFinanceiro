# Nome do executável
EXECUTABLE = output/main.exe

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -g3

# Arquivos-fonte e objetos
SOURCES = main.cpp Usuario.cpp Operacoes.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão (compilar o programa)
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p output
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Regra para compilar arquivos .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Executar o programa
run: all
	./$(EXECUTABLE)