#Augusto Mattei Grohmnann - 550429
#Miguel Dutra Fontes Guerra - 342573 

EXEC = etapa1

LEX = flex
LEX_SRC = scanner.l
LEX_OUT = lex.yy.cpp

CXX = g++
CXXFLAGS = -Wall -g

all: $(EXEC)

$(LEX_OUT): $(LEX_SRC)
	$(LEX) -o $(LEX_OUT) $(LEX_SRC)

$(EXEC): $(LEX_OUT)
	$(CXX) $(CXXFLAGS) $(LEX_OUT) -o $(EXEC)

clean:
	rm -f $(EXEC) $(LEX_OUT)
