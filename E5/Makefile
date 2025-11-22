# Augusto Mattei Grohmnann - 550429
# Miguel Dutra Fontes Guerra - 342573 

EXEC = etapa4
CC = gcc

CFLAGS = -Wall -g -fsanitize=address

# Ferramentas
LEX = flex
YACC = bison
YFLAGS = -d -v # Gera .tab.h

# Arquivos Fonte
LEX_SRC = scanner.l
YACC_SRC = parser.y
MAIN_SRC = main.c
ASD_SRC = asd.c
TABELA_SRC = tabela.c

# Arquivos Gerados
LEX_OUT = lex.yy.c
YACC_OUT_C = parser.tab.c
YACC_OUT_H = parser.tab.h

# Arquivos Objeto
OBJS = main.o lex.yy.o parser.tab.o asd.o tabela.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

main.o: $(MAIN_SRC) $(YACC_OUT_H) asd.h tabela.h
	$(CC) $(CFLAGS) -c $(MAIN_SRC)

lex.yy.o: $(LEX_OUT) $(YACC_OUT_H) asd.h
	$(CC) $(CFLAGS) -c $(LEX_OUT)

parser.tab.o: $(YACC_OUT_C) asd.h tabela.h
	$(CC) $(CFLAGS) -c $(YACC_OUT_C)
	
asd.o: $(ASD_SRC) asd.h
	$(CC) $(CFLAGS) -c $(ASD_SRC)

tabela.o: $(TABELA_SRC) tabela.h asd.h errors.h
	$(CC) $(CFLAGS) -c $(TABELA_SRC)

$(LEX_OUT): $(LEX_SRC)
	$(LEX) -o $(LEX_OUT) $(LEX_SRC)

# Regra para gerar o parser C e o header a partir do arquivo de gramática
$(YACC_OUT_C) $(YACC_OUT_H): $(YACC_SRC)
	$(YACC) $(YFLAGS) -o $(YACC_OUT_C) $(YACC_SRC)

clean:
	rm -f $(EXEC) $(OBJS) $(LEX_OUT) $(YACC_OUT_C) $(YACC_OUT_H)
