#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int _1(int *_2, int *_3) {
  int _4 = *_2;
  *_2 = *_3;
  *_3 = _4;
  return 0;
}

int _5(int _6[], int _7, int _8) {
  int _9 = _6[_8];
  int _10 = (_7 - 1);
  int _11;

  for (_11 = _7; _11 < _8; _11++) {
    if (_6[_11] <= _9) {
      _10++;
      _1(&_6[_10], &_6[_11]);
    }
  }

  _1(&_6[_10 + 1], &_6[_8]);
  return (_10 + 1);
}

void _12(int _13[], int _14, int _15) {
  if (_14 >= _15) return;
  int _16 = _5(_13, _14, _15);
  _12(_13, _14, _16 - 1);
  _12(_13, _16 + 1, _15);
}

void _17(int _18[], int _19) {
  int _20;
  for (_20 = 0; _20 < _19; _20++) {
    printf("%d  ", _18[_20]);
  }
  printf("\n");
}

int main(int _21, char *_22[]) {
    int _23;
    int _24[100];

    if (_21 == 1) {
        srand(time(NULL));
        for (_23 = 0; _23 < 100; _23++) {
            _24[_23] = rand() % 1000;
        }
        _23 = 100;
    } else if (_21 > 1) {
        _23 = _21 - 1;
        for (int _25 = 0; _25 < _23; _25++) {
            _24[_25] = atoi(_22[_25 + 1]);
        }
    }

    printf("Unsorted Array\n");
    _17(_24, _23);

    _12(_24, 0, _23 - 1);

    printf("Sorted array in ascending order:\n");
    _17(_24, _23);

    return 0;
}