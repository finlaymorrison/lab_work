#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define ALPHABET_CHARARECTER_COUNT 26
#define TERMINAL_WIDTH 100

void create_letter_histogram(const char* cypher_text, int* histogram);
void print_array(int const* array, int size);
void print_histogram(int const* histogram, int size, int terminal_width);
void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);
void new_encipher(const char *p, char *c, char* sub_map);
void new_decipher(const char *c, char *p, char* sub_map);
swap_map(char* sub_map, char* new_map, int size);
int find_key(const char* cypher_text);
float correctness(float* probabilities);

int main(int argc, char** argv)
{
	const char* text = "THIS TEXT IS JUST TO TEST HOW THE DECYPT THING WORKS IT DOES NOT ACTUALLY MEAN ANYTHING AND I AM TYPING IN CAPS SINCE THAT IS THE ONLY THING THAT THE PROGRAM CAN UNDERSTAND AND I CAN NOT BE BOTHERED TO MAKE ANOTHER FUNCTION THAT WILL TURN SOME EXISTING TEXT INTO CAPS EVEN THOUGH THAT WOULD PROBABLY TAKE LESS TIME THAN IT TOOK TO TYPE THIS TEXT BUT WHO CARES SINCE I HAVE ALMOST FINISHED TYPING THIS TEXT NOW AND IT IS A DECENT LENGTH AND SHOULD HOPEFULLY ALLOW ME TO WORK OUT THE KEY USING THE DISTRIBUTION OF THE CHARACTERS THAT I TYPE";
	char cyphered[1000];
	encipher(text, cyphered, 5);
	printf("%d\n", find_key(cyphered));
	return 0;
}

void new_encipher(const char *p, char *c, char* sub_map)
{
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
			c[index] = sub_map[buffer];
			if (c[index] > 'Z')
			{
				c[index] = c[index] - ALPHABET_CHARARECTER_COUNT;
			}
		}
		++index;
	}
	c[index] = '\0';
}

swap_map(char* sub_map, char* new_map, int size)
{
	for (int i = 0; i < size; ++i)
	{
		new_map[sub_map[i]] = i;
	}
}

void new_decipher(const char *c, char *p, char* sub_map)
{
	char new_map[ALPHABET_CHARARECTER_COUNT];
	swap_map(sub_map, new_map, ALPHABET_CHARARECTER_COUNT);
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
			p[index] = new_map[buffer];
			if (p[index] < 'A')
			{
				p[index] = ALPHABET_CHARARECTER_COUNT + p[index];
			}
		}
		++index;
	}
	p[index] = '\0';
}

float correctness(float* probabilities)
{
	float correct_distribution[ALPHABET_CHARARECTER_COUNT] = 
	{
		0.0812, 0.0149, 0.0271, 0.0432, 0.1202, 
		0.023,  0.0203, 0.0592, 0.0731, 0.001, 
		0.0069, 0.0398, 0.0261, 0.0695, 0.0768, 
		0.0182, 0.0011, 0.0602, 0.0628, 0.091, 
		0.0288, 0.0111, 0.0209, 0.0017, 0.0211, 0.0007
	};
	float total_error = 0.0f;
	for (int i = 0; i < ALPHABET_CHARARECTER_COUNT; ++i)
	{
		float difference = fabs(probabilities[i] - correct_distribution[i]);
		total_error += difference; /// correct_distribution[i];
	}
	printf("%f\n", total_error);
	return total_error;
}

int find_key(const char* cypher_text)
{
	int buffer_size = strlen(cypher_text) + 1;
	float letter_frequencies[ALPHABET_CHARARECTER_COUNT][ALPHABET_CHARARECTER_COUNT];
	for (int i = 0; i < ALPHABET_CHARARECTER_COUNT; ++i)
	{
		char cypher[buffer_size];
		int histogram[ALPHABET_CHARARECTER_COUNT];
		decipher(cypher_text, cypher, i);
		create_letter_histogram(cypher, histogram);
		int letter_count = 0;
		for (int j = 0; j < ALPHABET_CHARARECTER_COUNT; ++j)
		{
			letter_count += histogram[j];
		}
		for (int j = 0; j < ALPHABET_CHARARECTER_COUNT; ++j)
		{
			letter_frequencies[i][j] = (float)histogram[j] / letter_count;
		}
	}
	float correctnesses[ALPHABET_CHARARECTER_COUNT];
	for (int i = 0; i < ALPHABET_CHARARECTER_COUNT; ++i)
	{
		correctnesses[i] = correctness(letter_frequencies[i]);
	}
	float min_correctness = FLT_MAX;
	int min_correctness_key;
	for (int i = 0; i < ALPHABET_CHARARECTER_COUNT; ++i)
	{
		if (correctnesses[i] < min_correctness)
		{
			min_correctness = correctnesses[i];
			min_correctness_key = i;
		}
	}
	return min_correctness_key;
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

void create_letter_histogram(const char* cypher_text, int* histogram)
{
	for (int i = 0; i < ALPHABET_CHARARECTER_COUNT; ++i)
	{
		histogram[i] = 0;
	}
	char buffer;
	int index = 0;
	while(buffer = cypher_text[index++])
	{
		if (isalpha(buffer))
		{
			histogram[toupper(buffer) - 65]++;
		}
	}
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