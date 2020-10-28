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
	//create_letter_histogram("bee_movie_script.txt", histogram);
	const char* intial_message = "UNENCIPHERED";
	char encipered[13];
	char unenciphered[13];
	printf("initial message: %s\n", intial_message);
	encipher(intial_message, encipered, 5);
	printf("enciphered message: %s\n", encipered);
	decipher(encipered, unenciphered, 5);
	printf("deciphered message: %s\n", unenciphered);
	//print_histogram(histogram, ALPHABET_CHARARECTER_COUNT, TERMINAL_WIDTH);
	return 0;
}

void encipher(const char *p, char *c, const unsigned int offset)
{
	int real_offset = offset % 26;
	char buffer;
	int index = 0;
	while(buffer = p[index])
	{
		if (buffer == ' ')
		{
			c[index] = buffer;
		}
		else
		{
			c[index] = buffer + real_offset;
			if (c[index] > 'Z')
			{
				c[index] = c[index] - ALPHABET_CHARARECTER_COUNT;
			}
		}
		++index;
	}
	c[index] = '\0';
}

void decipher(const char *c, char *p, const unsigned int offset)
{
	int real_offset = offset % 26;
	char buffer;
	int index = 0;
	while(buffer = c[index])
	{
		if (buffer == ' ')
		{
			p[index] = buffer;
		}
		else
		{
			p[index] = buffer - real_offset;
			if (p[index] < 'A')
			{
				p[index] = ALPHABET_CHARARECTER_COUNT + p[index];
			}
		}
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