#include <stdio.h>
#include <stdlib.h>
#include "device_info.h"
#include "device_operations.h"
#include <strings.h>

void show_help() {
    printf("Usage: [option]\n");
    printf("Options:\n");
    printf("  -u         List connected USB devices\n");
    printf("  -a         List all connected peripherals (USB, Thunderbolt, etc.)\n");
    printf("  -h         Show this help message\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid usage. Please provide a single option.\n");
        show_help();
        return 1;
    }

    if (strcmp(argv[1], "-u") == 0) {
        list_connected_devices();
    } else if (strcmp(argv[1], "-a") == 0) {
        // TODO: implement device info function
        return 0;
    } else if (strcmp(argv[1], "-h") == 0) {
        show_help();
    } else {
        printf("Unknown option: %s\n", argv[1]);
        show_help();
        return 1;
    }

    return 0;
}
//
// void display_menu() {
//     printf("\nPeripheral Management System\n");
//     printf("1. List connected devices\n");
//     printf("2. Show device info\n");
//     printf("3. Mount device\n");
//     printf("4. Unmount device\n");
//     printf("5. Exit\n");
//     printf("Enter your choice: ");
// }
//
// int main() {
//     int choice;
//     char device[256], mount_point[256];
//
//     while (1) {
//         display_menu();
//         // scanf("%d", &choice);
//         if (scanf("%d", &choice) != 1) {
//             // Clear invalid input from stdin
//             while (getchar() != '\n'); // Discard invalid input
//
//             printf("Invalid input! Please enter a number.\n");
//             continue;
//         }
//
//         switch (choice) {
//             case 1:
//                 list_connected_devices();
//                 break;
//             case 2:
//                 printf("Enter device name (e.g., sda): ");
//                 scanf("%s", device);
//                 display_device_info(device);
//                 break;
//             case 3:
//                 printf("Enter device (e.g., /dev/sda1): ");
//                 scanf("%s", device);
//                 printf("Enter mount point (e.g., /mnt): ");
//                 scanf("%s", mount_point);
//                 mount_device(device, mount_point);
//                 break;
//             case 4:
//                 printf("Enter mount point to unmount (e.g., /mnt): ");
//                 scanf("%s", mount_point);
//                 unmount_device(mount_point);
//                 break;
//             case 5:
//                 printf("Exiting...\n");
//                 return 0;
//             default:
//                 printf("Invalid choice! Try again.\n");
//         }
//     }
// }
