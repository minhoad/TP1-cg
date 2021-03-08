CC=gcc
jogo: main.c 
	$(CC) $? -o $@ -lSOIL -lGL -lGLEW -lglut -lGLU 
	
run: jogo
	./jogo	
	
clean: 
	rm jogo 

