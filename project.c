#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCentered(const char* text, int lineWidth) {
    int len = strlen(text);
    int spaces = (lineWidth - len) / 2;
    for (int i = 0; i < spaces; i++) {
        printf(" ");  // Print leading spaces
    }
    printf("%s\n", text);  // Print the actual text
}

typedef struct {
    char item_code[10];
    char description[100];
    float price;
} Item;

Item items[] = {
    {"i1", "Rice Bag 1KG", 40.0},
    {"i2", "Wheat Flour 1KG", 35.0},
    {"i3", "Sugar 1KG", 45.0},
    {"i4", "Salt 1KG", 20.0}
};
int num_items = sizeof(items) / sizeof(items[0]);

Item* find_item(char *code) {
    for (int i = 0; i < num_items; i++) {
        if (strcmp(items[i].item_code, code) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

void print_centered(FILE *file, const char *text) {
    int len = strlen(text);
    int pos = (70 - len) / 2;  // Adjust width for centering
    for (int i = 0; i < pos; i++) {
        fprintf(file, " ");
    }
    fprintf(file, "%s\n", text);
}

void generate_bill(char *payment_type, char *upi_id) {
    FILE *file;
    file = fopen("supermarket_bill.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Printing headers and user information
    print_centered(file, "****************************************************************************");
    print_centered(file, "WELCOME TO MORE MEGA STORE");
    print_centered(file, "Address: City Center, Sector-10, Rohini, Delhi");
    print_centered(file, "Phone: 011-12712712");
    fprintf(file, "\n");
    print_centered(file, "Counter:2");

    print_centered(file, "Cashier: Tanuj");
    fprintf(file, "\n");

    // Headers for items
    fprintf(file, "%-10s %-25s %10s %10s %10s\n", "Item Code", "Description", "Price", "Quantity", "Total");

    float total = 0, gst, grand_total;
    char code[10];
    int qty;
    Item *item;

    while (1) {
        printf("Enter item code ('done' to finish): ");
        scanf("%s", code);
        if (strcmp(code, "done") == 0) {
            break;
        }

        item = find_item(code);
        if (item == NULL) { 
            printf("Invalid item code. Please try again.\n");
            continue;
        }

        printf("Enter quantity for %s: ", item->description);
        scanf("%d", &qty);

        float item_total = item->price * qty;
        total += item_total;

        fprintf(file, "%-10s %-25s %10.2f %10d %10.2f\n", item->item_code, item->description, item->price, qty, item_total);
    }

    gst = total * 0.18;  // 18% GST
    grand_total = total + gst;

    fprintf(file, "\nSub Total: %46.2f\n", total);
    fprintf(file, "GST (18%%): %46.2f\n", gst);
    fprintf(file, "Grand Total: %46.2f\n", grand_total);
    fprintf(file, "\n");

    fprintf(file, "Payment type: %s\n", payment_type);
    if (strcmp(payment_type, "UPI") == 0) {
        fprintf(file, "UPI ID: %-50s\n", upi_id);
    }
    else{fprintf(file, "Cash");}
    print_centered(file, "THANK YOU FOR SHOPPING WITH US!");
    print_centered(file, "****************************************************************************");

    fclose(file);
    printf("Bill has been saved. Please check 'supermarket_bill.txt'.\n");
}

int main() {
    char payment_type[20], upi_id[50];  // Adjusted size to 20 for the longer input

    printCentered("****************************************************************************", 70);
    printCentered("MORE MEGA STORE", 70);
    printCentered("Counter no:2", 70);
    printCentered("Cashier: Tanuj", 70);
    printf("Enter payment type (Cash or UPI): ");
    scanf("%s", payment_type);

    if (strcmp(payment_type, "UPI") == 0) {
        printf("Enter UPI ID: ");
        scanf("%s", upi_id);
        generate_bill("UPI", upi_id); // Pass "UPI" directly
    } else {
        generate_bill("Cash", ""); // Pass "Cash" directly
    }

#ifdef _WIN32
    system("start supermarket_bill.txt");
#endif

    return 0;
}
