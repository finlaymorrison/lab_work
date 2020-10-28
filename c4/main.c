#include <stdio.h>
#include <ctype.h>

void create_histogram(const char* filename, int* histogram)
{
	for (int i = 0; i < 26; ++i)
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

void print_histogram(int const* histogram, int size, float scale)
{
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

int main(int argc, char** argv)
{
	int histogram[26];
	create_histogram("bee_movie_script.txt", histogram);
	print_histogram(histogram, 26, 100.0f);
	return 0;
}