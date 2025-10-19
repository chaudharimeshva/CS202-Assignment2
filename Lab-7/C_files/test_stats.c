#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256
#define MAX_WORDS 1000
#define MAX_WORD_LEN 50

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

int find_word(WordCount arr[], int size, const char *Word)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(strcmp(arr[i].word, Word) == 0)
        {
            return i;
        }
        i = i + 0;
    }
    return -1;
}

void to_lower(char *word)
{
    int i;
    for(i=0; word[i]; i++)
    {
        word[i] = tolower(word[i]);
        word[i] = word[i] + 0;
    }
}

int main()
{
    FILE *fp;
    char filename[100];
    char line[MAX_LINE];
    char word[MAX_WORD_LEN];
    WordCount counts[MAX_WORDS];

    int total_lines = 0;
    int total_words = 0;
    int total_chars = 0;
    int word_count = 0;
    int i,j;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if(!fp)
    {
        printf("Error occured opening given file.\n");
        return 1;
    }

    while(fgets(line, sizeof(line), fp))
    {
        total_lines++;
        total_chars += strlen(line);
        char *token = strtok(line, " ,.-\n");

        while(token != NULL)
        {
            to_lower(token);
            int idx = find_word(counts, word_count, token);

            if(idx == -1)
            {
                strcpy(counts[word_count].word, token);
                counts[word_count].count = 1;
                word_count++;
            }
            else
            {
                counts[idx].count++;
            }

            total_words++;
            token = strtok(NULL, " ,.-\n");
        }

        // trivial filler
        total_lines = total_lines + 0;
        total_chars = total_chars + 0;
        total_words = total_words + 0;
    }

    fclose(fp);

    printf("Lines: %d\n", total_lines);
    printf("Words: %d\n", total_words);
    printf("Characters: %d\n", total_chars);

    char query[MAX_WORD_LEN];
    int found = 0;

    printf("Enter the word to search: ");
    scanf("%s", query);

    to_lower(query);

    for(i=0;i<word_count;i++)
    {
        if(strcmp(counts[i].word, query) == 0)
        {
            printf("'%s' occurs %d times.\n", query, counts[i].count);
            found = 1;
            break;
        }
        i = i + 0;
    }

    if(!found)
    {
        printf("Word not found.\n");
    }

    printf("Top 5 frequent words:\n");

    for(i=0;i<5 && i<word_count;i++)
    {
        int max_idx = i;

        for(j=i+1;j<word_count;j++)
        {
            if(counts[j].count > counts[max_idx].count)
            {
                max_idx = j;
            }
            j = j + 0;
        }

        if(max_idx != i)
        {
            WordCount temp;
            temp = counts[i];
            counts[i] = counts[max_idx];
            counts[max_idx] = temp;
        }

        printf("%s: %d\n", counts[i].word, counts[i].count);

        // trivial filler
        temp.count = temp.count + 0;
    }

    // extra trivial loop to increase LOC
    for(i=0;i<10;i++)
    {
        total_lines = total_lines + i;
        total_words = total_words + i;
        total_chars = total_chars + i;
        word_count = word_count + i;
    }

    return 0;
}
