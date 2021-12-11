LIBS = -lglut -lGLU -lGL -lm  
FLAGS = -Wall
FILE = texturasBasico.cpp

main: $(FILE)
	g++ -o main $(FILE) RgbImage.cpp $(FLAGS) $(LIBS)

.PHONY: clean
clean:
	rm main
