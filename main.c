Hotel management system
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* =====================================
   HOTEL MANAGEMENT SYSTEM
   ===================================== */
/* CUSTOMER STRUCTURE */
struct Customer
{
    int customerID;
    char name[50];
    char phone[20];
};
/* ROOM STRUCTURE */
struct Room
{
    int roomNo;
    char roomType[30];
    double price;
    int available;
};
/* BOOKING STRUCTURE */
struct Booking
{
    int bookingID;
    int customerID;
    int roomNo;
    int days;
    double total;
    double paid;
    int active;
};
/* FUNCTION DECLARATIONS */
void registerCustomer(void);
void viewCustomers(void);
void searchCustomer(void);
void addRoom(void);
void viewRooms(void);
void bookRoom(void);
void viewBookings(void);
void recordPayment(void);
void generateReceipt(void);
void checkOut(void);
int customerExists(int id, struct Customer *result);
int roomExists(int number, struct Room *result);
int nextBookingID(void);
int getInteger(char message[]);
double getAmount(char message[]);
void getText(char message[], char value[], int size);
/* =====================================
   INPUT FUNCTIONS
   ===================================== */
int getInteger(char message[])
{
    char input[100];
    int value;
    char extra;
    while(1)
    {
        printf("%s", message);
        if(fgets(input, sizeof(input), stdin) == NULL)
            continue;
        if(sscanf(input, "%d %c", &value, &extra) == 1)
            return value;
        printf("Invalid input! Enter a whole number.\n");
    }
}
double getAmount(char message[])
{
    char input[100];
    double value;
    char extra;
    while(1)
    {
        printf("%s", message);
        if(fgets(input, sizeof(input), stdin) == NULL)
            continue;
        if(sscanf(input, "%lf %c", &value, &extra) == 1
           && value >= 0)
            return value;
        printf("Invalid amount! Try again.\n");
    }
}
void getText(char message[], char value[], int size)
{
    printf("%s", message);
    if(fgets(value, size, stdin) == NULL)
    {
        value[0] = '\0';
        return;
    }
    value[strcspn(value, "\n")] = '\0';
}
/* =====================================
   CUSTOMER FUNCTIONS
   ===================================== */
int customerExists(int id, struct Customer *result)
{
    struct Customer customer;
    FILE *file;
    file = fopen("customers.dat", "rb");
    if(file == NULL)
        return 0;
    while(fread(&customer, sizeof(customer), 1, file) == 1)
    {
        if(customer.customerID == id)
        {
            if(result != NULL)
                *result = customer;
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
void registerCustomer(void)
{
    struct Customer customer;
    FILE *file;
    printf("\n========== CUSTOMER REGISTRATION ==========\n");
    customer.customerID = getInteger("Enter Customer ID: ");
    if(customer.customerID <= 0)
    {
        printf("Customer ID must be positive.\n");
        return;
    }
    if(customerExists(customer.customerID, NULL))
    {
        printf("Customer ID already exists!\n");
        return;
    }
    getText("Enter Customer Name: ",
            customer.name, sizeof(customer.name));
    if(strlen(customer.name) == 0)
    {
        printf("Customer name cannot be empty.\n");
        return;
    }
    getText("Enter Phone Number: ",
            customer.phone, sizeof(customer.phone));
    if(strlen(customer.phone) == 0)
    {
        printf("Phone number cannot be empty.\n");
        return;
    }
    file = fopen("customers.dat", "ab
