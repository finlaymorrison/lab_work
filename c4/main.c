#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#define ALPHABET_CHARARECTER_COUNT 26
#define TERMINAL_WIDTH 100

void create_letter_histogram(const char* filename, int* histogram);
void print_array(int const* array, int size);
void print_histogram(int const* histogram, int size, int terminal_width);
void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);

int main(int argc, char** argv)
{
	int histogram[ALPHABET_CHARARECTER_COUNT];
	create_letter_histogram("bee_movie_script.txt", histogram);
	char pp[10];
	char aa[10];
	const char* ppp = "dhjeiqldu";
	encipher(ppp, pp, 1);
	decipher(pp, aa, 1);
	printf("%s\n", aa);
	//print_histogram(histogram, ALPHABET_CHARARECTER_COUNT, TERMINAL_WIDTH);
	return 0;
}

void encipher(const char *p, char *c, const unsigned int offset)
{
	char buffer;
	int index = 0;
	while(buffer = p[index])
	{
		c[index] = buffer + offset;
		++index;
	}
	c[index] = '\0';
}

void decipher(const char *c, char *p, const unsigned int offset)
{
	char buffer;
	int index = 0;
	while(buffer = c[index])
	{
		p[index] = buffer - offset;
		++index;
	}
	p[index] = '\0';
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
	float scale = (float)max_value / terminal_width;
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