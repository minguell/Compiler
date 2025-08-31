# CXX = g++
# CXXFLAGS = -std=c++11 -Wall

# target: etapa3

# etapa3: lex.yy.o main.o symbols.o funcoes.o parser.tab.o ast.o
# 	$(CXX) $(CXXFLAGS) lex.yy.o main.o symbols.o funcoes.o parser.tab.o ast.o -o etapa3

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# lex.yy.cpp: scanner.l parser.tab.hpp
# 	flex -o lex.yy.cpp scanner.l

# parser.tab.cpp parser.tab.hpp: parser.ypp
# 	bison -d parser.ypp

# clean:
# 	rm -f etapa3 lex.yy.cpp parser.tab.cpp parser.tab.hpp *.o

CXX = g++
CXXFLAGS = -std=c++11 -Wall

target: etapa3

etapa3: parser.tab.o lex.yy.o main.o symbols.o funcoes.o ast.o
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
	rm -f etapa3 lex.yy.cpp parser.tab.cpp parser.tab.hpp *.o