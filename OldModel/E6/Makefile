CXX = g++
CXXFLAGS = -std=c++11 -Wall

etapa6: parser.tab.o lex.yy.o main.o semantic.o symbols.o funcoes.o ast.o tac.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

lex.yy.cpp: scanner.l parser.tab.hpp
	flex -o lex.yy.cpp scanner.l

lex.yy.o: lex.yy.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c lex.yy.cpp -o lex.yy.o

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c parser.tab.cpp -o parser.tab.o

clean:
	rm -f etapa6 lex.yy.cpp parser.tab.cpp parser.tab.hpp *.o