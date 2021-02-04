#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char* data;
    int size;
    int capacity;
} vector;

vector vector_construct()
{
    vector v;
    v.data = (char*)malloc(1 * sizeof(char));
    v.size = 0;
    v.capacity = 1;
    return v;
}

void vector_push_back(vector* v, char c)
{
    if (v->capacity <= v->size)
    {
        v->data = (char*)realloc(v->data, v->size * 2 * sizeof(char));
        v->capacity = v->size * 2;
    }
    v->data[v->size++] = c;
}

void vector_destruct(vector v)
{
    free(v.data);
}


void print_vector(vector v)
{
    printf("{");
    for (int i = 0; i < v.size - 1; ++i)
    {
        printf("%c,", v.data[i]);
    }
    printf("%c}\n", v.data[v.size - 1]);
}

int main(int argc, char** argv)
{
    vector v = vector_construct();
    FILE* f_ptr = fopen("input-data.txt" ,"r");
    char c;
    while (fscanf(f_ptr, "%c", &c) != EOF)
    {
        vector_push_back(&v, c);
    }
    print_vector(v);
    vector_destruct(v);
    return 0;
}