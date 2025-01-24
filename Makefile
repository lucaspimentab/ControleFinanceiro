# Definindo o compilador e as flags
CXX = g++
CXXFLAGS = -Wall -Wextra -g3 -I./include
LDFLAGS = -mconsole

# Diretórios
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Arquivos fontes e objetos
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/sistema_controle_financeiro.exe

# Regra padrão (apenas compila)
all: $(EXEC)

# Como gerar o executável a partir dos objetos
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

# Como compilar arquivos .cpp em .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(OBJDIR)/$(@F)

# Limpeza dos arquivos objetos e executável (mantendo os diretórios)
clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/$(EXEC)

# Regra para rodar o programa após a compilação
run: $(EXEC)
	@echo "Executando o programa..."
	@./$(EXEC)