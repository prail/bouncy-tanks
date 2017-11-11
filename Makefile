TARGET = tb
LIBS = -lallegro-5.0.10-mt -lallegro_image-5.0.10-mt
HEADERS = game_map.h game_object.h camera_object.h tank_object.h
OBJECTS = game_map.o game_object.o camera_object.o tank_object.o main.o
FLAGS = -Os -Wall --std=c99

default: $(TARGET)

%.o: %.c $(HEADERS)
	gcc -c $< $(FLAGS) -o $@ 

$(TARGET): $(OBJECTS)
	gcc $(OBJECTS) $(FLAGS) $(LIBS) -o ./$@
run:
	.\$(TARGET)

clean:
	-del /s/q/f *.o
	-del /s/q/f *.exe