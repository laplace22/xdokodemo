all: xdokodemo

xdokodemo: xdokodemo.c xdokodemo.h
	gcc -O2 -o xdokodemo xdokodemo.c -I /usr/X11R6/include/ -lX11 -lXtst -L /usr/X11R6/lib

install: all
	cp -f ./xdokodemo /usr/local/bin/

clean:
	rm ./xdokodemo
