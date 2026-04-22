CC = gcc
CFLAGS_BASE = -g -std=c99 -Wall -Wconversion -Wtype-limits -Werror -Isrc
CFLAGS_TEST = $(CFLAGS_BASE) -Ipruebas
CFLAGS_MAIN = $(CFLAGS_BASE)
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
EJEC = pruebas_alumno
EJEC_MAIN = calculadora
SRCS_MAIN = main.c src/pila.c src/lista.c 
HDRS_MAIN = src/pila.h src/lista.h 
SRCS = src/lista.c src/pila.c src/cola.c pruebas/pruebas_alumno.c
HDRS = src/lista.h  src/pila.h src/cola.h pruebas/pa2m.h 

# Compilar
all: $(EJEC) $(EJEC_MAIN)

$(EJEC): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS_TEST) $(SRCS) -o $(EJEC)

$(EJEC_MAIN): $(SRCS_MAIN) $(HDRS_MAIN)
	$(CC) $(CFLAGS_MAIN) $(SRCS_MAIN) -o $(EJEC_MAIN)

# Ejecutar las pruebas, sin el binario
run: $(EJEC)
	./$(EJEC)

run-main: $(EJEC_MAIN)
	./$(EJEC_MAIN)

#Ejecutar pruebas con valgrind
valgrind: $(EJEC)
	valgrind $(VFLAGS) ./$(EJEC)

format:
	clang-format -style=file -i main.c src/*.c src/*.h pruebas/*.c

.PHONY: all run valgrind clean format

clean:
	rm -f $(EJEC) $(EJEC_MAIN)
