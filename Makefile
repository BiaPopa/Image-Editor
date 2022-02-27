# Copyright 2020 Darius Neatu <neatudarius@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=image_editor

build: $(TARGETS)

run: $(TARGETS)
	./$(TARGETS)

image_editor: image_editor.c load.h load.c filters.h filters.c crop.h crop.c rotire.h rotire.c
	$(CC) $(CFLAGS) image_editor.c load.c filters.c crop.c rotire.c -o image_editor

pack:
	zip -FSr 3XYCA_FirstnameLastname_Tema1.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
