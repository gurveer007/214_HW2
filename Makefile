OUTPUT = find ls tree
CFLAGS = -g -fsanitize=address

%: %.c 
		gcc $(CFLAGS) -o $@ $^

all: $(OUTPUT)

clean:
		rm -f $(OUTPUT) 
		
