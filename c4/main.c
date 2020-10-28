#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#define ALPHABET_CHARARECTER_COUNT 26
#define TERMINAL_WIDTH 100

void create_letter_histogram(const char* filename, int* histogram);
void print_array(int const* array, int size);
void print_histogram(int const* histogram, int size, int terminal_width);

int main(int argc, char** argv)
{
	int histogram[ALPHABET_CHARARECTER_COUNT];
	create_letter_histogram("bee_movie_script.txt", histogram);
	print_histogram(histogram, ALPHABET_CHARARECTER_COUNT, TERMINAL_WIDTH);
	return 0;
}

void create_letter_histogram(const char* filename, int* histogram)
{
	for (int i = 0; i < ALPHABET_CHARARECTER_COUNT; ++i)
	{
		histogram[i] = 0;
	}
	FILE* file = fopen(filename, "r");
	char buffer;
	while((buffer = fgetc(file)) != EOF)
	{
		if (isalpha(buffer))
		{
			histogram[toupper(buffer) - 65]++;
		}
	}
	fclose(file);
}

void print_array(int const* array, int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d\n", array[i]);
	}
}

void print_histogram(int const* histogram, int size, int terminal_width)
{
	int max_value = INT_MIN;
	for (int i = 0; i < size; ++i)
	{
		if (histogram[i] > max_value)
		{
			max_value = histogram[i];
		}
	}
	float scale = max_value / terminal_width;
	for (int i = 0; i < size; ++i)
	{
		int bar_size = histogram[i] / scale;
		printf("%d : ", i);
		for (int j = 0; j < bar_size; ++j)
		{
			printf("*");
		}
		printf("\n");
	}
}