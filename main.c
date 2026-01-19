#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "main.h"

/* !!!!!!!!!!!!!!!!!!! ВАЖНО
chcp 65001
$OutputEncoding = [Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
gcc main.c personalExpenses.c futureValue.c -o finance.exe -lm
*/

int operationSelector;
int operationConfirm;

int main() {

  // Начално меню
  printf("Добре дошли в програмата за планиране на финанси! За да започнете, въведете число, кореспондиращо на името на операцията: \n 1) Създаване на финансов планер \n 2) Калкулиране на бъдеща стойност \n 3) Изход от програмата\n");

  // Проверка за валидност
  do {
    printf("\n Вашият отговор: ");
    scanf("%d", &operationSelector);
  } while (operationSelector < 1 || operationSelector > 4);

  // Потвърждение на избор
  printf("\nИзбрахте опция: %d", operationSelector);

  do {
    printf("\n\nЖелаете ли да продължите с тази операция? \n Въведете 1 за да продължите, 0 за отказ. \n Вашият отговор: ");
    scanf("%d", &operationConfirm);
  } while (operationConfirm < 0 || operationConfirm > 1);

  if (operationConfirm == 0 ) {
    printf("\nВръщане към началното меню.\n\n");
    main();
  }

  // Изпълнение на избраната операция
  if (operationConfirm == 1) {
    switch (operationSelector) {
      case 1: personalExpenses(); break;
      case 2: futureValue(); break;
      case 3: printf("Програмата е затворена."); break;
    }
  }

  return 0;
}




