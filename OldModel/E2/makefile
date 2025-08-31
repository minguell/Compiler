EXEC = etapa2

LEX = flex
LEX_SRC = scanner.l
LEX_OUT = lex.yy.c

BISON = bison
BISON_SRC = parser.y
BISON_OUT_C = parser.tab.c
BISON_OUT_H = parser.tab.h

CXX = g++
CXXFLAGS = -Wall -g

SRC = $(LEX_OUT) $(BISON_OUT_C) symbol.cpp main.cpp

all: $(EXEC)

$(LEX_OUT): $(LEX_SRC)
	$(LEX) $(LEX_SRC)

$(BISON_OUT_C) $(BISON_OUT_H): $(BISON_SRC)
	$(BISON) -d $(BISON_SRC)

$(EXEC): $(LEX_OUT) $(BISON_OUT_C) $(BISON_OUT_H) main.cpp symbol.cpp
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC) lex.yy.* parser.tab.* *.o
