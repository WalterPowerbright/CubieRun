build:
	gcc src/main.c -std=c99 -Wall -Werror -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o builds/game

web-build:
	emcc src/main.c libraylib.web.a -I/usr/local/include -sUSE_GLFW=3 -o builds/web/index.html --preload-file assets

run:
	./builds/game
