OPTIONS=-O3 -DNDEBUG -Wall -Wextra

all: build/res

debug: OPTIONS=-O0 -g -DDEBUG -Wall -Wextra
debug: build/res

build/res: build/res.o tools/main.cpp
	gcc ${OPTIONS} tools/main.cpp -o build/res -I include/ build/res.o

build/res.o: src/json.cpp include/json.hpp
	gcc ${OPTIONS} -c src/json.cpp -o build/res.o -I include/

clean:
	rm -rf build/*.o build/res
