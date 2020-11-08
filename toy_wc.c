#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char get_option(const char option_string);
void wc(FILE* in_file, char* options);
int main(int argc, char** argv)
{
  char* options;
  size_t size = sizeof(*argv);
  options = malloc(sizeof(char) * (size));
  
  argv++; /* equivalent to bash shift */
  argc--; /* to skip command itself */

  if (argc > 0 && **argv == '-')
  {
    unsigned index = 1;
    while (*(*(argv)+index) != '\0')
    {
      options[index - 1] = get_option(*(*(argv)+index));
      /* options[index + 1] = get_option(*(*(argv) + 1));*/

      index++;
    }

    options[index + 1] = '\0';

    argv++;
    argc--;
  }

  if (argc == 0)
  {
    wc(stdin, options);
    
    printf("\n");
  }
  else
  {
    do
    {
      FILE* input_file = fopen(*argv, "r");
      if (input_file == NULL)
      {
        fprintf(stderr, "Cannot open %s\n", *argv);
      }
      else
      {
        wc(input_file, options);
        fclose(input_file);
        printf("%s", *argv);
      }
      printf("\n");
      argv++;
    } while (--argc > 0);
    return 0;
  }
  free(options);
}

char get_option(const char option_string)
{
  char result = '\0';
  switch (option_string)
  {
    case 'l':
      result = 'l';
      break;
    case 'w':
      result = 'w';
      break;
    case 'c':
      result = 'c';
      break;
    default:
      fprintf(stderr, "Bad option %c\n", option_string);
  }
  return result;
}

void wc(FILE* in_file, char* options)
{
  int character;
  unsigned in_word = 0;
  unsigned word_count = 0;
  unsigned line_count = 0;
  unsigned char_count = 0;
  unsigned index = 0;

  while ((character = getc(in_file)) != EOF)
  {
    char_count++;
    if (character == '\n')
    {
      line_count++;
    }
    if (isspace(character))
    {
      in_word = 0;
    }
    else if (!in_word)
    {
      in_word = 1;
      word_count++;
    }
  }

  while (options[index] != '\0')
  {
    if (options[index] == 'l')
    {
      printf("%8d ", line_count);
    }
    else if (options[index] == 'c')
    {
       printf("%8d ", char_count);
    }
    else
    {
       printf("%8d ", word_count);
    }
    index++;
  }
  
}

