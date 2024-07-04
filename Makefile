all:
	gcc main.c -o p1 `pkg-config --cflags --libs gtk4`
