all: clean run

main: main.c
	@echo "# COMPILING ###########################################################"
		$(CC) -o main main.c menu.c utils.c

run: main
	@echo "# RUN #################################################################"
	cp ./main /tmp/main
	chmod +x /tmp/main
	/tmp/main

clean:
	rm -f main
