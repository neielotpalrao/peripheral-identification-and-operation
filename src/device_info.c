#include "device_info.h"
#include <stdio.h>
#include <stdlib.h>

void list_connected_devices() {
    printf("Listing connected USB devices on macOS...\n");

    // Using ioreg to list connected USB devices
    FILE *fp = popen("ioreg -p IOUSB -l -w 0", "r");
    if (fp == NULL) {
        printf("Failed to run ioreg command\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
}

void display_device_info(const char* device) {
    char path[256];
    FILE *file;
    char buffer[1024];

    // Access device vendor info
    snprintf(path, sizeof(path), "/sys/class/block/%s/device/vendor", device);
    file = fopen(path, "r");
    if (file == NULL) {
        printf("Error reading device info for %s\n", device);
        return;
    }
    fgets(buffer, sizeof(buffer), file);
    printf("Device: %s\n", device);
    printf("Vendor: %s\n", buffer);
    fclose(file);

    // Access device model info
    snprintf(path, sizeof(path), "/sys/class/block/%s/device/model", device);
    file = fopen(path, "r");
    if (file == NULL) {
        printf("Error reading device model for %s\n", device);
        return;
    }
    fgets(buffer, sizeof(buffer), file);
    printf("Model: %s\n", buffer);
    fclose(file);
}
