#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "src/font.h"

#define PROJECT_NAME "ascii_clock"

int g_random(int min, int max) {
  return (int)arc4random_uniform((uint32_t)(max - min + 1)) + min;
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  const int size = 441;
  char str[size + 1];

  int ms = 0;

  int display[8] = {0, 0, 10, 0, 0, 10, 0, 0};  // 10 = индекс sep в digits
  int index_char = 0;
  while (1) {
    for (int i = 0; i < size; i++) {
      str[i] = 33 + g_random(34, 126) % (126 - 33 + 1);
    }
    str[size] = '\0';

    if (ms == 1000000) {
      ms = 0;
    }
    time_t ms_time = time(NULL);

    struct tm* local = localtime(&ms_time);

    char hour_str[3];
    char min_str[3];
    char sec_str[3];

    strftime(hour_str, sizeof(hour_str), "%H", local);
    strftime(min_str, sizeof(min_str), "%M", local);
    strftime(sec_str, sizeof(sec_str), "%S", local);

    int hf = hour_str[0] - '0';
    int hs = hour_str[1] - '0';
    int m_f = min_str[0] - '0';
    int m_s = min_str[1] - '0';
    int sf = sec_str[0] - '0';
    int ss = sec_str[1] - '0';

    display[0] = hf;
    display[1] = hs;

    display[3] = m_f;
    display[4] = m_s;

    display[6] = sf;
    display[7] = ss;

    for (int row = 0; row < 7; row++) {
      for (int elem = 0; elem < 8; elem++) {
        char* current = digits[display[elem]];

        // Ширина текущего элемента
        int width = (display[elem] == 10) ? 4 : 8;

        for (int col = 0; col < width; col++) {
          if (display[elem] == 10) {
            if (current[row * width + col] == 1) {
              printf("%s", ms == 500000 ? "\033[92m" : "\033[33m");
              printf("%c", str[index_char]);
              printf("\033[0m");

            } else {
              printf("%s", "\033[92m");
              printf("%c", str[index_char]);
              printf("\033[0m");
            }

          } else {
            if (current[row * width + col] == 1) {
              printf("%s", ms == 1000000 ? "\033[92m" : "\033[33m");
              printf("%c", str[index_char]);
              printf("\033[0m");

            } else {
              printf("%s", "\033[92m");
              printf("%c", str[index_char]);
              printf("\033[0m");
            }
          }
        }

        if (elem < 7) {
          printf("%s", "\033[92m");

          printf("%c", str[index_char]);
          printf("\033[0m");
        }
        index_char = (index_char + 1) & 441;
      }
      printf("\n");
    }

    usleep(100000);
    ms += 100000;
    printf("\033[1;1H");
    printf("\033[J");
  }

  printf("%s\n", str);

  return 0;
}
