LIB=-lboost_program_options -lboost_serialization
EXEC=todoer
OBJ=main.o Task.o TaskManager.o BoostSerializer.o ConsolePrinter.o
FLAGS=-g -std=c++0x

$(EXEC): $(OBJ)
	$(CXX) $(FLAGS) $^ $(LIB) -o $@

.cpp.o:
	$(CXX) $(FLAGS) -c $<

clean:
	$(RM) $(EXEC) $(OBJ)

