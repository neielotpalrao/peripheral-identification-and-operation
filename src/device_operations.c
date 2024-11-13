#include "device_operations.h"
#include <stdio.h>
#include <stdlib.h>

void mount_device(const char* device, const char* mount_point) {
    char command[256];
    snprintf(command, sizeof(command), "mount %s %s", device, mount_point);
    if (system(command) == 0) {
        printf("Device %s mounted at %s\n", device, mount_point);
    } else {
        printf("Error mounting device %s\n", device);
    }
}

void unmount_device(const char* mount_point) {
    char command[256];
    snprintf(command, sizeof(command), "umount %s", mount_point);
    if (system(command) == 0) {
        printf("Device unmounted from %s\n", mount_point);
    } else {
        printf("Error unmounting device\n");
    }
}
