#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "main.h"

// Финансов планер
void personalExpenses() {
  // Описание на операцията
  printf("\n Вие сте избрали опцията за създаване на финансов планер. Този планер включва всички данни за вашите приходи и разходи.");

  // Продължителност на плана (до 1 година)
  int months;
  // За смятане на натрупан баланс
  float carriedBalance = 0.0f;

  // Въвеждане на стойност и проверка за валидност
  do {
    printf("\n Въведете продължителността на плана от 1 до 12 месеца: ");
    scanf("%d", &months);
  } while (months < 1 || months > 12);

  // Конструктор за име и стойност
  typedef struct {
    char name[50];
    float value;
  } Record;

  // Данни за месеца
  typedef struct {
    Record *income;
    int incomeCount;

    Record *expense;
    int expenseCount;

    float incomeTotal;
    float expenseTotal;
    float balance;
    float carriedBalance;
  } MonthData;

  typedef struct {
    char name[50];
    float total;
  } SummaryRecord;


  // Отделяне на памет за данните за всички месеци
  MonthData *data = malloc(months * sizeof(MonthData));

  // Въвеждане на данни
  for (int m = 0; m < months; m++) {
    printf("\n \n Въвеждане на данни за месец %d", m + 1);

    // Въвеждане на приходи
    printf("\n-- Въвеждане на приходи --\n");
    data[m].incomeCount = 0;
    data[m].income = NULL;

    int addSource;

    do {
      // Добавяне на нов приход и преотделяне на място за него
      data[m].incomeCount++;
      data[m].income = realloc(data[m].income, data[m].incomeCount * sizeof(Record));

      do {
        printf("\n Въведете име и стойност на приход: ");
        scanf("%s %f", &data[m].income[data[m].incomeCount-1].name, &data[m].income[data[m].incomeCount-1].value);

        if (data[m].income[data[m].incomeCount-1].value <= 0) {
          printf("\n Моля въведете положителна стойност.");
        }
      } while (data[m].income[data[m].incomeCount-1].value < 1);


      do {
        printf("\nЖелаете ли да добавите още приходи?\n Въведете 1 за потвърждение, 0 за отказ: ");
        scanf("%d", &addSource);
      } while (addSource < 0 || addSource > 1);

    } while (addSource == 1);

    // Въвеждане на разходи
    printf("\n-- Въвеждане на разходи --\n");
    data[m].expenseCount = 0;
    data[m].expense = NULL;

    addSource = 0;

    do {
      // Добавяне на нов приход и преотделяне на място за него
      data[m].expenseCount++;
      data[m].expense = realloc(data[m].expense, data[m].expenseCount * sizeof(Record));

      do {
        printf("\n Въведете име и стойност на разход: ");
        scanf("%s %f", &data[m].expense[data[m].expenseCount-1].name, &data[m].expense[data[m].expenseCount-1].value);

        if (data[m].expense[data[m].expenseCount-1].value <= 0) {
          printf("\n Моля въведете положителна стойност.");
        }
      } while (data[m].expense[data[m].expenseCount-1].value < 1);

      do {
        printf("\nЖелаете ли да добавите още разходи?\n Въведете 1 за потвърждение, 0 за отказ: ");
        scanf("%d", &addSource);
      } while (addSource < 0 || addSource > 1);

    } while (addSource == 1);

    // Създаване на таблица за месеца
    printf("\n -- Данни за месец %d -- \n", m+1);
    printf("--------------------------------------------------------------------------\n");
    printf("%-20s | %-12s | %-20s | %-12s\n", "Приход", "Стойност", "Разход", "Стойност");
    printf("--------------------------------------------------------------------------\n");

    // Определяне на броя редове
    int rows;
    if (data[m].incomeCount > data[m].expenseCount) {
      rows = data[m].incomeCount;
    }
        
    else {
      rows = data[m].expenseCount;
    }

    float monthIncomeTotal = 0;
    float monthExpenseTotal = 0;


    for (int i = 0; i < rows; i++) {
      // Изписване на приходи
      if (i < data[m].incomeCount) {
        printf("%-20s | %-12.2f | ", data[m].income[i].name, data[m].income[i].value);
        monthIncomeTotal += data[m].income[i].value;
        data[m].incomeTotal = monthIncomeTotal;
      } 
            
      // Ако има празни редове
      else {
        printf("%-20s | %-12s | ", "-", "-");
      }

      // Изписване на разходи
      if (i < data[m].expenseCount) {
        printf("%-20s | %-12.2f\n", data[m].expense[i].name, data[m].expense[i].value);
        monthExpenseTotal += data[m].expense[i].value;
        data[m].expenseTotal = monthExpenseTotal;
      } 
            
      // Ако има празни редове
      else {
        printf("%-20s | %-12s\n", "-", "-");
      }
    }

    // Калкулиране на натрупан баланс
    data[m].balance = monthIncomeTotal - monthExpenseTotal;

    if (m == 0) {
      data[m].carriedBalance = data[m].balance;
    }

    else {
      data[m].carriedBalance = data[m - 1].carriedBalance + data[m].balance;
    }

    float monthBalance = monthIncomeTotal - monthExpenseTotal;
    carriedBalance += monthBalance;

    printf("Общо приходи: %.2f | Общо разходи: %.2f\n", monthIncomeTotal, monthExpenseTotal);
    printf("Баланс: %.2f\n", monthBalance);

    if (m >= 1) {
      printf("Натрупан баланс: %.2f\n", carriedBalance);
    }
  }

  // Създаване на обща таблица с всички данни
  printf("\n\n -- Обща таблица за периода --\n");
  printf("--------------------------------------------------------------------------\n");
  printf("%-8s | %-14s | %-14s | %-10s | %-15s\n", "Месец", "Приходи", "Разходи", "Баланс", "Натрупан баланс");
  printf("--------------------------------------------------------------------------\n");

  float totalIncomeAll = 0;
  float totalExpenseAll = 0;

  for (int m = 0; m < months; m++) {
    printf("%-8d | %-14.2f | %-14.2f | %-10.2f | %-15.2f\n", m + 1, data[m].incomeTotal, data[m].expenseTotal, data[m].balance, data[m].carriedBalance);
    totalIncomeAll += data[m].incomeTotal;
    totalExpenseAll += data[m].expenseTotal;
  }

  printf("--------------------------------------------------------------------------\n");
  printf("Общо     | %-14.2f | %-14.2f | %-10.2f\n", totalIncomeAll, totalExpenseAll, totalIncomeAll - totalExpenseAll);
  printf("\n Край на програмата.");
}