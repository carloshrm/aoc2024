#include <stdio.h>
#include <stdlib.h>

typedef struct inputData
{
    size_t line_size;
    size_t line_count;
    char **data;
} InputData;

typedef struct vector2
{
    int x;
    int y;
} Vector2;

const char XMAS[4] = {'X', 'M', 'A', 'S'};
const Vector2 DIRECTIONS[] = {{-1, 0},   // U
                              {1, 0},    // D
                              {0, -1},   // R
                              {0, 1},    // L
                              {1, 1},    // D L
                              {1, -1},   // D R
                              {-1, 1},   // U L
                              {-1, -1}}; // U R
const size_t N_DIR = 8;

size_t swapLetter(const size_t l)
{
    return l == 1 ? 3 : 1;
}

InputData readInput(const char *path)
{
    FILE *input_file = NULL;
    input_file = fopen(path, "r");
    if (input_file == NULL)
    {
        printf(" ( ｀ー´)ノ Input? \n");
        exit(1);
    }

    size_t line_length = 0;
    size_t line_count = 0;

    size_t width_count = 0;
    char temp;
    while ((temp = fgetc(input_file)) != EOF)
    {
        if (temp == '\n')
        {
            line_length = width_count;
            width_count = 0;
            line_count++;
        }
        width_count++;
    }
    rewind(input_file);

    char **word_search = calloc(line_count + 1, sizeof(char *));

    size_t i = 0;
    size_t j = 0;
    while ((temp = fgetc(input_file)) != EOF)
    {
        if (temp == '\n')
        {
            i++;
            j = 0;
        }
        else
        {
            if (word_search[i] == NULL)
                word_search[i] = calloc(line_length + 1, sizeof(char));

            word_search[i][j] = temp;
            j++;
        }
    }
    fclose(input_file);

    return (InputData){line_length, line_count, word_search};
}

int findXmas(const Vector2 pos, const Vector2 *offset, const size_t l, const InputData *word_search)
{
    if (word_search->data[pos.y][pos.x] != XMAS[l])
        return 0;

    if (l == 3)
        return 1;

    Vector2 next_pos = {pos.x + offset->x, pos.y + offset->y};
    if (next_pos.x < 0 || next_pos.x > word_search->line_size || next_pos.y < 0 || next_pos.y > word_search->line_count)
        return 0;

    return findXmas(next_pos, offset, l + 1, word_search);
}

int partOne(const InputData *word_search)
{
    int result = 0;
    for (size_t i = 0; i <= word_search->line_count; i++)
    {
        for (size_t j = 0; j < word_search->line_size; j++)
        {
            if (word_search->data[i][j] == 'X')
            {
                Vector2 pos = {j, i};
                for (size_t dir_i = 0; dir_i < N_DIR; dir_i++)
                    result += findXmas(pos, &DIRECTIONS[dir_i], 0, word_search);
            }
        }
    }
    return result;
}

int findMas(const Vector2 *pos, const Vector2 *offset, const size_t l, const InputData *word_search)
{
    Vector2 first_letter = {pos->x + offset->x, pos->y + offset->y};
    Vector2 last_letter = {pos->x - offset->x, pos->y - offset->y};

    if (first_letter.x < 0 || first_letter.x > word_search->line_size || first_letter.y < 0 || first_letter.y > word_search->line_count ||
        last_letter.x < 0 || last_letter.x > word_search->line_size || last_letter.y < 0 || last_letter.y > word_search->line_count)
        return 0;

    return (word_search->data[first_letter.y][first_letter.x] == XMAS[l] &&
            word_search->data[last_letter.y][last_letter.x] == XMAS[swapLetter(l)]);
}

int partTwo(const InputData *word_search)
{
    const Vector2 *right_diagonal = &DIRECTIONS[4];
    const Vector2 *left_diagonal = &DIRECTIONS[5];

    int result = 0;
    for (size_t i = 0; i <= word_search->line_count; i++)
    {
        for (size_t j = 0; j < word_search->line_size; j++)
        {
            if (word_search->data[i][j] == 'A')
            {
                Vector2 pos = {j, i};
                if (findMas(&pos, right_diagonal, 1, word_search) || findMas(&pos, right_diagonal, 3, word_search))
                {
                    if (findMas(&pos, left_diagonal, 1, word_search) || findMas(&pos, left_diagonal, 3, word_search))
                        result++;
                }
                else if (findMas(&pos, left_diagonal, 1, word_search) || findMas(&pos, left_diagonal, 3, word_search))
                {
                    if (findMas(&pos, right_diagonal, 1, word_search) || findMas(&pos, right_diagonal, 3, word_search))
                        result++;
                }
            }
        }
    }
    return result;
}

int main()
{
    InputData word_search = readInput(".\\inputs\\Day4.txt");

    int p_one = partOne(&word_search);
    int p_two = partTwo(&word_search);

    printf("\n part 1: %d\n\n", p_one);
    printf("\n part 2: %d\n\n", p_two);

    return 0;
}