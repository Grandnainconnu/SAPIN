#include <stdio.h>
#include <stdlib.h>

#include "sapin.h"

static void print_branch(char separator, char value, int s_size, int v_size)
{
    int i = -1;

    while (++i < s_size)
        printf("%c", separator);
    i = -1;
    while (++i < v_size)
        printf("%c", value);
    printf("\n");
}

static int get_last_line_size(int size)
{
    int i = 0;
    static sapint_t sapin = {0, 4, 2, 1};

    while (++i < sapin.current_bloc_size)
        sapin.last_line_size += 2;
    if (sapin.blocs < (size - 1))
        sapin.last_line_size -= sapin.offset;
    if (sapin.blocs++ % 2)
        sapin.offset += 2;
    sapin.current_bloc_size++;
    return (sapin.blocs < size ? get_last_line_size(size) : sapin.last_line_size);
}

static void tree(int size, int final_line_size)
{
    int i[2] = {-1};
    int current_line_size = 0;
    sapint_t sapin = {-1, 4, 2, 1};

    while (++i[0] < size) {
        i[1] = -1;
        while (++i[1] < sapin.current_bloc_size) {
            current_line_size = (!i[1]) ? sapin.last_line_size : current_line_size + 2;
            print_branch(' ', '*', ((final_line_size - 1) / 2) - ((current_line_size - 1) / 2), current_line_size); 
        }
        sapin.last_line_size = current_line_size - sapin.offset;
        if (i[0] % 2)
            sapin.offset += 2;
        sapin.current_bloc_size++;
    }
    i[0] = -1;
    while (++i[0] < size)
        print_branch(' ', '|', ((final_line_size - 1) / 2) - ((size % 2 ? size - 1 : size) / 2), !(size % 2) ? size + 1 : size);
}

int	main(int argc, char **argv)
{
	if (argc < 2) {
		tree(1, get_last_line_size(1));
	} else {
		int size = atoi(argv[1]);
		
		tree(size, get_last_line_size(size));
	}
}
