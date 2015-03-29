CPLEX_LIB = /opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic/libcplex.a
CPLEX_INCLUDE = /opt/ibm/ILOG/CPLEX_Studio1261/cplex/include/ilcplex

CXX = g++
CXXFLAGS = -O3 -g -Wall -MMD -std=c++11 -I$(CPLEX_INCLUDE)
EXEC1 = perfect_matching
EXEC2 = data_reduction
OBJECTS1 = main.o Graph.o FordFulkerson.o GomoryHu.o PadbergRao.o lp.o util.o RelaxedLP.o DFS.o Heuristics1.o Bimap.o
DEPENDS1 = ${OBJECTS1:.o=.d}

OBJECTS2 = reduction_main.o redata.o util.o
DEPENDS2 = ${OBJECTS2:.o=.d}

all: $(EXEC1) $(EXEC2)

${EXEC1}: ${OBJECTS1}
	${CXX} ${CXXFLAGS} -o ${EXEC1} ${OBJECTS1} $(CPLEX_LIB) -lm -lpthread
-include ${DEPENDS1}

${EXEC2}: ${OBJECTS2}
	${CXX} ${CXXFLAGS} -o ${EXEC2} ${OBJECTS2} 
-include ${DEPENDS2}

.PHONY: clean

clean:
	rm *.o *d ${EXEC2} ${EXEC1}

