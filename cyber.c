#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Service {
    char name[50];
    int price;
};

struct Service services[] = {
    {"Printing", 5},
    {"Scanning", 7},
    {"Coffee", 10},
    {"Tea", 8},
    {"Online Form Fill", 20},
    {"Laminate", 15},
    {"Gaming Hour", 25}
};

int serviceCount = 7;

double totalRevenue = 0;
int totalCustomers = 0;
int totalSessions = 0;

int getUserCategory() {
    int c;
    printf("\nSelect Your Category:\n");
    printf("1) Student (10%% Discount)\n");
    printf("2) Senior Citizen (50%% Discount)\n");
    printf("3) Corporate User (+20%% Extra)\n");
    printf("4) Gamer (+10 Rs Extra)\n");
    printf("5) General Customer\n");
    printf("Choose Category: ");
    scanf("%d", &c);
    return c;
}

void logSession(const char *user, double serviceCost, double total) {
    printf("\n--- Session Logged Successfully ---\n");
    totalRevenue += total;
    totalCustomers++;
    totalSessions++;
}

int authenticate(const char *u, const char *p, int *isAdmin) {
    if(strcmp(u, "admin") == 0 && strcmp(p, "adminpass") == 0){
        *isAdmin = 1;
        return 1;
    }
    if(strcmp(u, "omkar") == 0 && strcmp(p, "password123") == 0){
        *isAdmin = 0;
        return 1;
    }
    return 0;
}

int main() {
    char username[50], password[50];
    int choice, isAdmin = 0;

    double serviceCost = 0;
    int category = 5;

start:
    printf("\n1) Login\n2) Guest Login\n3) Exit\nChoose: ");
    scanf("%d", &choice);

    if(choice == 1){
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if(authenticate(username, password, &isAdmin)){
            category = getUserCategory();
        } else {
            printf("Invalid Login!");
            goto start;
        }
    }
    else if(choice == 2){
        strcpy(username, "guest");
        category = getUserCategory();
    }
    else return 0;

mainmenu:
    printf("\n=== MAIN MENU ===\n");
    printf("1) Order Services\n");
    printf("2) Generate Bill\n");
    if(isAdmin) printf("3) ADMIN: View Totals\n");
    printf("0) Exit\n");
    printf("Choose: ");
    scanf("%d", &choice);

    if(choice == 1){
        printf("\nAvailable Services:\n");
        for(int i=0;i<serviceCount;i++){
            printf("%d) %s - %d Rs\n", i+1, services[i].name, services[i].price);
        }

        int s;
        serviceCost = 0;
        printf("\nSelect multiple services (0 to stop):\n");
        while(1){
            printf("Service No: ");
            scanf("%d", &s);
            if(s == 0) break;
            if(s>=1 && s<=serviceCount){
                serviceCost += services[s-1].price;
            }
        }
    }

    else if(choice == 2){
        double total = serviceCost;

        if(category == 1) total *= 0.90;
        else if(category == 2) total *= 0.50;
        else if(category == 3) total *= 1.20;
        else if(category == 4) total += 10;

        printf("\n=== BILL ===\n");
        printf("Services   : %.2f\n", serviceCost);
        printf("Total Bill : %.2f\n", total);

        logSession(username, serviceCost, total);
    }

    else if(choice == 3 && isAdmin){
        printf("\n--- SYSTEM TOTAL ---\n");
        printf("Customers: %d\n", totalCustomers);
        printf("Sessions : %d\n", totalSessions);
        printf("Revenue  : %.2f\n", totalRevenue);
    }

    else if(choice == 0){
        return 0;
    }

    goto mainmenu;
}