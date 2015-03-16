
CXX = g++
CXXFLAGS = -O3 -g -Wall -MMD -std=c++11
EXEC = fordfulkerson
OBJECTS = main.o Graph.o FordFulkerson.o GomoryHu.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJECTS} 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
