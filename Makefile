CPLEX_LIB = /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libcplex.a
CPLEX_INCLUDE = /opt/ibm/ILOG/CPLEX_Studio1261/cplex/include/ilcplex

CXX = g++
CXXFLAGS = -O3 -g -Wall -MMD -std=c++11 -I$(CPLEX_INCLUDE)
EXEC = co759_project
OBJECTS = main.o Graph.o FordFulkerson.o GomoryHu.o PadbergRao.o lp.o util.o RelaxedLP.o DFS.o Heuristics1.o Bimap.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJECTS} $(CPLEX_LIB) -lm -lpthread

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
