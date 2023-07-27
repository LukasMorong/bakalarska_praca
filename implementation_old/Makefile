# CC = gcc
# CFLAGS = -Werror -g
# LDFLAGS = -L./libs/jsmn -ljsmn

# # List all source files here
# SRCS = main.c ./libs/parser.c

# HS = ./libs/jsmn/jsmn.h ./libs/parser.h

# # Compute object file names by replacing .c with .o
# OBJS = $(SRCS:.c=.o)

# # Define the executable name
# EXEC = main

# all: $(EXEC)

# $(EXEC): $(OBJS)
# 	$(CC) $(CFLAGS) $(HS) $(OBJS) -o $(EXEC)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# run: $(EXEC)
# 	./$(EXEC)

# clean:
# 	rm -f $(EXEC) $(OBJS)
# 	rm -f ./libs/parser.o


CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all: main

main: main.o delta_encoding.o
	$(CC) -o main main.o delta_encoding.o

main.o: main.c
	$(CC) -c main.c -o main.o

delta_encoding.o: libs/data_transformation/delta_encoding.c
	$(CC) -c libs/data_transformation/delta_encoding.c -o delta_encoding.o

run: main
	./main

clean:
	rm -f main.o delta_encoding.o main