all:
	gcc -o stun-client stun-client.c `pkg-config --cflags --libs nice`
