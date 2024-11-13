#include "device_info.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TYPES 100
#define MAX_NAME_LENGTH 128

// Struct to store each data type with original and formatted names
typedef struct {
  char original[MAX_NAME_LENGTH];
  char formatted[MAX_NAME_LENGTH];
} DataType;

// Function to format the system_profiler data type string
void formatDataType(const char *input, char *output) {
  const char *ptr = (strncmp(input, "SP", 2) == 0) ? input + 2 : input;
  int j = 0;
  for (int i = 0; ptr[i] != '\0'; i++) {
    if (i > 0 && isupper(ptr[i]) && islower(ptr[i + 1])) {
      output[j++] = ' ';
    }
    output[j++] = ptr[i];
  }
  output[j] = '\0';
}

// Function to populate data types from system_profiler into the DataType array
int getDataTypes(DataType dataTypes[]) {
  FILE *fp = popen("system_profiler -listDataTypes", "r");
  if (fp == NULL) {
    fprintf(stderr, "Failed to run system_profiler command\n");
    exit(1);
  }

  int count = 0;
  char line[MAX_NAME_LENGTH];
  while (fgets(line, sizeof(line), fp) != NULL && count < MAX_TYPES) {
    line[strcspn(line, "\n")] = 0; // Remove newline
    strcpy(dataTypes[count].original, line);
    formatDataType(line, dataTypes[count].formatted);
    count++;
  }

  pclose(fp);
  return count;
}

// Function to display options and get user's choice
int displayOptionsAndGetChoice(DataType dataTypes[], int count) {
  printf("Select a data type from the list below:\n");
  for (int i = 0; i < count; i++) {
    printf("%d: %s\n", i + 1, dataTypes[i].formatted);
  }

  int choice = 0;
  printf("\nEnter the number of your choice: ");
  if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
    printf("Invalid choice.\n");
    return -1;
  }
  return choice - 1;
}

void list_connected_devices() {
  DataType dataTypes[MAX_TYPES];
  int count = getDataTypes(dataTypes);

  int choice = displayOptionsAndGetChoice(dataTypes, count);
  if (choice != -1) {
    // Using system_profiler to list connected devices for the chosen data type
    char command[256];
    snprintf(command, sizeof(command), "system_profiler %s",
             dataTypes[choice].original);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
      printf("Failed to run system_profiler command\n");
      return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      printf("%s", buffer);
    }

    pclose(fp);
  }
}

// TODO:Implement Device Info Function
// void display_device_info(const char *device) {
// }
