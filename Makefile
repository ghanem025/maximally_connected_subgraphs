SOURCE = a3.c
OUTPUT = graph.out

main: $(SOURCE)
	gcc $(SOURCE) -o $(OUTPUT)

run:
	./$(OUTPUT)

clean:
	rm ./$(OUTPUT)

