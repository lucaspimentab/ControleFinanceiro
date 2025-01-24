CXX = g++
CXXFLAGS = -Wall -Wextra -g3 -I./include
LDFLAGS = -mconsole

# Diretórios
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Arquivos fontes
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/sistema_controle_financeiro.exe

# Regra padrão
all: $(EXEC)

# Como gerar o executável a partir dos objetos
$(EXEC): $(OBJECTS)
	@mkdir -p $(BINDIR)  # Cria o diretório bin se não existir
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

# Como compilar arquivos .cpp em .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)  # Cria o diretório obj se não existir
	$(CXX) $(CXXFLAGS) -c $< -o $(OBJDIR)/$(@F)  # $(@F) usa o nome do arquivo sem o diretório

# Limpeza dos arquivos objetos e executável
clean:
	rm -rf $(OBJDIR) $(BINDIR)
