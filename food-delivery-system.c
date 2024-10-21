#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User details for sign-up
struct userDetails {
    int age;
    char userName[100];
    char email[100];
    char mobile[20];
    char password[20];
};

// Hotel details & their food details
struct hotelDetails {
    char hotel_name[100];
    char first_food[50];
    char second_food[50];
    char third_food[50];
    int first_price, second_price, third_price;
};

// Cart structure
struct cartItem {
    char foodName[50];
    int price;
    int quantity;
};

// Initialize the hotels & user details
struct hotelDetails hotel[6];
struct userDetails user[100];
struct cartItem cart[100];

// Declarations of functions
void signup();
void account_check();
int is_valid();
void login();
void browse_restaurants();
void show_menu(int hotel_choice);
void hotel_initialize();
void add_to_cart(int hotel_choice, int item_choice);
void view_cart();
void confirm_order();

// Global variables
int user_count = 0, cart_count = 0;
char temp_name[100], temp_password1[20], temp_password2[20], temp_email[100], temp_mobile[20];
int temp_age, total = 0;

// Food Ordering system
int main() {
    int choice;
    hotel_initialize();  // Initialize hotels at the start

    while (1) {
        printf("\n\n\t\tWelcome to our Food Ordering System\n");
        printf("\n1. Sign-up\n2. Login\n3. Exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            signup();
            break;
        case 2:
            login();
            break;
        case 3:
            exit(0);
        default:
            printf("\nPlease enter a valid choice\n");
            break;
        }
    }
    return 0;
}

// Function signup
void signup() {
    printf("\n\n***********SIGNUP************\n\n");
    while ((getchar()) != '\n');  // Clear input buffer

    printf("Enter Your Name: ");
    scanf("%[^\n]%*c", temp_name);

    printf("Enter Your Age: ");
    scanf("%d", &temp_age);

    printf("Enter Your Email: ");
    scanf("%s", temp_email);

    printf("Enter Password: ");
    scanf("%s", temp_password1);

    printf("Confirm Password: ");
    scanf("%s", temp_password2);

    printf("Enter Your Mobile Number: ");
    scanf("%s", temp_mobile);

    int validate = is_valid();
    if (validate == 1) {
        account_check();
    }
}

// Function to check if the account already exists
void account_check() {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(temp_email, user[i].email) == 0) {
            printf("\n\nAccount Already Exists. Please Login!\n");
            return;
        }
    }

    // Account does not exist, create a new one
    strcpy(user[user_count].userName, temp_name);
    strcpy(user[user_count].password, temp_password1);
    strcpy(user[user_count].email, temp_email);
    strcpy(user[user_count].mobile, temp_mobile);
    user[user_count].age = temp_age;
    user_count++;

    printf("\n\nAccount Successfully Created!\n\n");
}

// Function to validate the user account for signing-up
int is_valid() {
    // Validate name
    for (int i = 0; temp_name[i] != '\0'; i++) {
        if (!((temp_name[i] >= 'a' && temp_name[i] <= 'z') || (temp_name[i] >= 'A' && temp_name[i] <= 'Z') || temp_name[i] == ' ')) {
            printf("\nPlease enter a valid name\n");
            return 0;
        }
    }

    // Validate email
    int At = -1, Dot = -1;
    if (!((temp_email[0] >= 'a' && temp_email[0] <= 'z') || (temp_email[0] >= 'A' && temp_email[0] <= 'Z'))) {
        printf("\nPlease enter a valid email address.\n");
        return 0;
    }
    for (int i = 0; temp_email[i] != '\0'; i++) {
        if (temp_email[i] == '@') At = i;
        if (temp_email[i] == '.') Dot = i;
    }
    if (At == -1 || Dot == -1 || At > Dot || Dot >= (strlen(temp_email) - 1)) {
        printf("\nPlease enter a valid email address.\n");
        return 0;
    }

    // Validate password
    if (strcmp(temp_password1, temp_password2) != 0 || strlen(temp_password1) < 8 || strlen(temp_password1) > 12) {
        printf("\nPasswords do not match or do not meet length criteria.\n");
        return 0;
    }

    // Validate mobile number (11 digits for Bangladesh)
    if (strlen(temp_mobile) != 11) {
        printf("\nPlease enter a valid mobile number.\n");
        return 0;
    }
    for (int i = 0; i < 11; i++) {
        if (temp_mobile[i] < '0' || temp_mobile[i] > '9') {
            printf("\nPlease enter a valid mobile number.\n");
            return 0;
        }
    }

    // Validate age
    if (temp_age <= 0) {
        printf("\nPlease enter a valid age.\n");
        return 0;
    }

    return 1;
}

// Function for user login
void login() {
    char login_email[100], login_password[20];
    printf("\n\n****************LOGIN*****************\n\n");
    printf("\nEnter Your Email: ");
    scanf("%s", login_email);

    printf("Enter Your Password: ");
    scanf("%s", login_password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(user[i].email, login_email) == 0) {
            if (strcmp(user[i].password, login_password) == 0) {
                printf("\n\nWelcome! You have successfully logged in :)\n\n");

                int choice;
                while (1) {
                    printf("\n1. Browse Restaurants\n2. View Cart\n3. Confirm Order\n4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    if (choice == 1) {
                        browse_restaurants();
                    } else if (choice == 2) {
                        view_cart();
                    } else if (choice == 3) {
                        confirm_order();
                    } else if (choice == 4) {
                        printf("Logging out...\n");
                        return;
                    } else {
                        printf("Invalid choice. Please try again.\n");
                    }
                }
                return;
            } else {
                printf("\nInvalid password! Please try again.\n");
                return;
            }
        }
    }
    printf("\nThis account doesn't exist. Please sign up to create your account!\n");
}

// Function to browse restaurants
void browse_restaurants() {
    printf("\n\n*** List of Restaurants ***\n\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, hotel[i].hotel_name);
    }
    int hotel_choice;
    printf("\nEnter the number of the restaurant to view the menu: ");
    scanf("%d", &hotel_choice);

    if (hotel_choice >= 1 && hotel_choice <= 3) {
        show_menu(hotel_choice - 1);
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}

// Function to display the menu of a chosen restaurant and add to cart
void show_menu(int hotel_choice) {
    printf("\n\n*** Menu of %s ***\n\n", hotel[hotel_choice].hotel_name);
    printf("1. %s - $%d\n", hotel[hotel_choice].first_food, hotel[hotel_choice].first_price);
    printf("2. %s - $%d\n", hotel[hotel_choice].second_food, hotel[hotel_choice].second_price);
    printf("3. %s - $%d\n", hotel[hotel_choice].third_food, hotel[hotel_choice].third_price);

    int item_choice;
    printf("\nEnter the number of the food item to add to cart: ");
    scanf("%d", &item_choice);

    if (item_choice >= 1 && item_choice <= 3) {
        add_to_cart(hotel_choice, item_choice);
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}

// Function to add selected food item to the cart
void add_to_cart(int hotel_choice, int item_choice) {
    int quantity;
    printf("\nEnter the quantity: ");
    scanf("%d", &quantity);

    switch (item_choice) {
        case 1:
            strcpy(cart[cart_count].foodName, hotel[hotel_choice].first_food);
            cart[cart_count].price = hotel[hotel_choice].first_price * quantity;
            cart[cart_count].quantity = quantity;
            break;
        case 2:
            strcpy(cart[cart_count].foodName, hotel[hotel_choice].second_food);
            cart[cart_count].price = hotel[hotel_choice].second_price * quantity;
            cart[cart_count].quantity = quantity;
            break;
        case 3:
            strcpy(cart[cart_count].foodName, hotel[hotel_choice].third_food);
            cart[cart_count].price = hotel[hotel_choice].third_price * quantity;
            cart[cart_count].quantity = quantity;
            break;
    }

    total += cart[cart_count].price;
    cart_count++;
    printf("\nItem successfully added to cart.\n");
}

// Function to view the cart
void view_cart() {
    if (cart_count == 0) {
        printf("\nYour cart is empty!\n");
    } else {
        printf("\n\n*** Your Cart ***\n\n");
        for (int i = 0; i < cart_count; i++) {
            printf("%d. %s - Quantity: %d - Total: $%d\n", i + 1, cart[i].foodName, cart[i].quantity, cart[i].price);
        }
        printf("\nTotal: $%d\n", total);
    }
}

// Function to confirm the order
void confirm_order() {
    if (cart_count == 0) {
        printf("\nYour cart is empty! Please add some items first.\n");
    } else {
        printf("\n*** Order Confirmed ***\n\n");
        printf("Thank you for your order! Here's your order summary:\n");
        for (int i = 0; i < cart_count; i++) {
            printf("%d. %s - Quantity: %d - Total: $%d\n", i + 1, cart[i].foodName, cart[i].quantity, cart[i].price);
        }
        printf("\nTotal Amount: $%d\n", total);
        printf("\nYour order will be delivered soon. Enjoy your meal!\n");

        // Reset cart and total after confirmation
        cart_count = 0;
        total = 0;
    }
}

// Function to initialize hotel details
void hotel_initialize() {
    // Hotel 1
    strcpy(hotel[0].hotel_name, "Restaurant A");
    strcpy(hotel[0].first_food, "Burger");
    hotel[0].first_price = 5;
    strcpy(hotel[0].second_food, "Pizza");
    hotel[0].second_price = 10;
    strcpy(hotel[0].third_food, "Pasta");
    hotel[0].third_price = 8;

    // Hotel 2
    strcpy(hotel[1].hotel_name, "Restaurant B");
    strcpy(hotel[1].first_food, "Fried Chicken");
    hotel[1].first_price = 7;
    strcpy(hotel[1].second_food, "Noodles");
    hotel[1].second_price = 6;
    strcpy(hotel[1].third_food, "Salad");
    hotel[1].third_price = 4;

    // Hotel 3
    strcpy(hotel[2].hotel_name, "Restaurant C");
    strcpy(hotel[2].first_food, "Tacos");
    hotel[2].first_price = 3;
    strcpy(hotel[2].second_food, "Sandwich");
    hotel[2].second_price = 4;
    strcpy(hotel[2].third_food, "Fries");
    hotel[2].third_price = 2;
}
