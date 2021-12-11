LIBS = -lglut -lGLU -lGL -lm
FLAGS = -Wall -g
FILE = projeto.cpp
OTHERS = stb_image.h

.SILENT:
main: $(FILE)
	g++ -o main $(FILE) $(OTHERS) $(FLAGS) $(LIBS)

.PHONY: clean
clean:
	rm main
