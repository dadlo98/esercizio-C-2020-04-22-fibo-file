#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

unsigned long * fibonacci_array(unsigned int n) {

	unsigned long fib_n, fib_n_1, fib_n_2;
	unsigned long * result;
	if (n < 0) {
		return NULL;
	}
	result = malloc(sizeof(unsigned long) * (n+1));
	if (result == NULL)
		return NULL;

	switch (n) {
	case 0:
		result[0] = 0;
		return result;
	case 1:
		result[0] = 0;
		result[1] = 1;
		return result;
	default:
		fib_n_2 = 0;
		fib_n_1 = 1;
		result[0] = 0;
		result[1] = 1;

		for (unsigned int i = 2; i <= n; i++) {
			fib_n = fib_n_1 + fib_n_2;
			fib_n_2 = fib_n_1;
			fib_n_1 = fib_n;

			result[i] = fib_n;
		}

		return result;
	}
}

int min_string_len(int number) {
	int result =  (int)( ceil( log10( labs(number) )) + 1 ) * sizeof(char);
	if (number == 0 || number == 1)
		result = 2;
	
	return result;
}

char * itoa_printf(int number) {
	char * result;
	int length = min_string_len(number);
	result = calloc(length, sizeof(char));
	snprintf(result, length, "%d", number);
	
	return result;
}

int main(int argc, char *argv[]) {
	unsigned long * fibonacci_result = fibonacci_array(39);
	char * file_name = "fibonacci.txt";
	char * text_to_write;
	int text_to_write_len;
	printf("scrivo nel file %s\n", file_name);
    	int fd = open(file_name,
        O_CREAT | O_TRUNC | O_WRONLY,
        S_IRUSR | S_IWUSR
        );
    if (fd == -1) {
        perror("open()");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<40; i++){
        char * str = itoa_printf(fibonacci_result[i]);
        text_to_write = strcat(str, "\n");
        text_to_write_len = strlen(text_to_write);
        int res = write(fd, text_to_write, text_to_write_len);
        if (res == -1) {
            perror("write()");
            exit(EXIT_FAILURE);
        }
        free(str);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
    free(fibonacci_result);
    
    return 0;
}
