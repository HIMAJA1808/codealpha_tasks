#include <stdio.h>
#include <stdlib.h>
struct Account {
    int accNo;
    char name[50];
    float balance;
};
// Function declarations
void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();
int main() {
    int choice;
    while (1) {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5:
                printf("Thank you! Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}
// Create Account
void createAccount() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "ab");
    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);
    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
    printf("Account Created Successfully!\n");
}
// Deposit Function
void deposit() {
    struct Account acc;
    int accNo, found = 0;
    float amount;
    FILE *fp = fopen("bank.dat", "rb+");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("Deposit Successful! Updated Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Account not found!\n");

    fclose(fp);
}
// Withdraw Function
void withdraw() {
    struct Account acc;
    int accNo, found = 0;
    float amount;
    FILE *fp = fopen("bank.dat", "rb+");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);
            if (acc.balance >= amount) {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("Withdrawal Successful! Remaining Balance: %.2f\n", acc.balance);
            } else {
                printf("Insufficient Balance!\n");
            }
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Account not found!\n");

    fclose(fp);
}
// Balance Enquiry
void balanceEnquiry() {
    struct Account acc;
    int accNo, found = 0;
    FILE *fp = fopen("bank.dat", "rb");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Account Holder: %s\n", acc.name);
            printf("Current Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Account not found!\n");
    fclose(fp);
}
