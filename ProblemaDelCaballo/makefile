BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

all : $(BIN)/Salta

$(BIN)/Salta: $(OBJ)/Caballo.o $(OBJ)/Tablero.o $(OBJ)/main.o
	@echo Creando el ejecutable $(BIN)/Salta...
	@g++ -I$(INCLUDE) -o $@ $^
	
$(OBJ)/Caballo.o: $(SRC)/Caballo.cpp
	@echo Creando el modulo objeto $(OBJ)/Caballo.o...
	@g++ -c -I$(INCLUDE) -o $(OBJ)/Caballo.o $(SRC)/Caballo.cpp

$(OBJ)/Tablero.o: $(SRC)/Tablero.cpp
	@echo Creando el modulo objeto $(OBJ)/Tablero.o...
	@g++ -c -I$(INCLUDE) -o $(OBJ)/Tablero.o $(SRC)/Tablero.cpp

$(OBJ)/main.o: $(SRC)/main.cpp
	@echo Creando el modulo objeto $(OBJ)/main.o...
	@g++ -c -I$(INCLUDE) -o $(OBJ)/main.o $(SRC)/main.cpp

clean:
	@echo Borrando los ficheros .o del directorio $(OBJ)...
	rm $(OBJ)/*.o $(BIN)/Salta
