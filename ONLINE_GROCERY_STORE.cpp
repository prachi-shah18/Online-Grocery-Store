/*
    Online Grocery Store
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// one node = one item in the cart
struct Node {
    int id;
    char name[50];
    float price;
    int quantity;
    struct Node* next;
};

struct Node* head = NULL;

// -------------------------------------------
//  Create a new cart node
// -------------------------------------------
struct Node* createNode(int id, char name[], float price, int quantity) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->next = NULL;
    return newNode;
}

// -------------------------------------------
//  Add item to cart
//  If item ID already exists, just update qty
// -------------------------------------------
void addItem(int id, char name[], float price, int quantity) {
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            temp->quantity += quantity;
            printf("\n  [UPDATED] Item already in cart. Quantity updated!\n");
            return;
        }
        temp = temp->next;
    }

    // item not found, add new node at front
    struct Node* newNode = createNode(id, name, price, quantity);
    newNode->next = head;
    head = newNode;

    printf("\n  [SUCCESS] '%s' added to cart!\n", name);
}

// -------------------------------------------
//  Remove item by ID
// -------------------------------------------
void removeItem(int id) {
    struct Node *temp = head, *prev = NULL;

    if (temp == NULL) {
        printf("\n  Cart is empty!\n");
        return;
    }

    // if head node is the one to remove
    if (temp->id == id) {
        head = temp->next;
        free(temp);
        printf("\n  [REMOVED] Item removed from cart!\n");
        return;
    }

    // search rest of the list
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\n  [NOT FOUND] No item with ID %d in cart.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("\n  [REMOVED] Item removed from cart!\n");
}

// -------------------------------------------
//  Update quantity of an existing item
// -------------------------------------------
void updateQuantity(int id, int quantity) {
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            temp->quantity = quantity;
            printf("\n  [UPDATED] Quantity changed to %d!\n", quantity);
            return;
        }
        temp = temp->next;
    }

    printf("\n  [NOT FOUND] No item with ID %d in cart.\n", id);
}

// -------------------------------------------
//  Display all cart items with bill
// -------------------------------------------
void displayCart() {
    struct Node* temp = head;
    float total = 0;

    printf("\n  ============================================\n");
    printf("              YOUR SHOPPING CART\n");
    printf("  ============================================\n");

    if (temp == NULL) {
        printf("         Cart is empty!\n");
        printf("  ============================================\n");
        return;
    }

    printf("  %-5s %-15s %-8s %-5s %-10s\n", "ID", "Name", "Price", "Qty", "Subtotal");
    printf("  --------------------------------------------\n");

    while (temp != NULL) {
        float itemTotal = temp->price * temp->quantity;
        total += itemTotal;
        printf("  %-5d %-15s %-8.2f %-5d Rs.%.2f\n",
               temp->id, temp->name, temp->price,
               temp->quantity, itemTotal);
        temp = temp->next;
    }

    printf("  --------------------------------------------\n");
    printf("  Total Bill :  Rs. %.2f\n", total);
    printf("  ============================================\n");
}

// -------------------------------------------
//  Search item by ID
// -------------------------------------------
void searchItem(int id) {
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            printf("\n  [FOUND] %s | Price: Rs.%.2f | Qty: %d\n",
                   temp->name, temp->price, temp->quantity);
            return;
        }
        temp = temp->next;
    }

    printf("\n  [NOT FOUND] No item with ID %d.\n", id);
}

// -------------------------------------------
//  Checkout - show bill then clear cart
// -------------------------------------------
void checkout() {
    if (head == NULL) {
        printf("\n  Cart is empty! Nothing to checkout.\n");
        return;
    }

    displayCart();

    printf("\n  Confirm checkout? (1 = Yes / 0 = No): ");
    int confirm;
    scanf("%d", &confirm);

    if (confirm != 1) {
        printf("\n  Checkout cancelled.\n");
        return;
    }

    // free all nodes
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    printf("\n  [SUCCESS] Order placed! Thank you for shopping.\n");
}

// -------------------------------------------
//  Main menu
// -------------------------------------------
int main() {
    int choice;

    while (1) {
        printf("\n  ===== ONLINE GROCERY STORE =====\n");
        printf("  1. Add Item to Cart\n");
        printf("  2. Remove Item\n");
        printf("  3. Update Quantity\n");
        printf("  4. View Cart\n");
        printf("  5. Search Item\n");
        printf("  6. Checkout\n");
        printf("  7. Exit\n");
        printf("  ================================\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {
                int id, quantity;
                char name[50];
                float price;

                printf("\n  --- Add Item ---\n");
                printf("  Enter Item ID     : ");
                scanf("%d", &id);
                printf("  Enter Item Name   : ");
                scanf(" %[^\n]", name);   // reads full name with spaces
                printf("  Enter Price (Rs.) : ");
                scanf("%f", &price);
                printf("  Enter Quantity    : ");
                scanf("%d", &quantity);

                addItem(id, name, price, quantity);
                break;
            }

            case 2: {
                int id;
                printf("\n  --- Remove Item ---\n");
                printf("  Enter Item ID to remove: ");
                scanf("%d", &id);
                removeItem(id);
                break;
            }

            case 3: {
                int id, quantity;
                printf("\n  --- Update Quantity ---\n");
                printf("  Enter Item ID       : ");
                scanf("%d", &id);
                printf("  Enter New Quantity  : ");
                scanf("%d", &quantity);
                updateQuantity(id, quantity);
                break;
            }

            case 4:
                displayCart();
                break;

            case 5: {
                int id;
                printf("\n  --- Search Item ---\n");
                printf("  Enter Item ID to search: ");
                scanf("%d", &id);
                searchItem(id);
                break;
            }

            case 6:
                checkout();
                break;

            case 7:
                printf("\n  Goodbye! See you again.\n\n");
                exit(0);

            default:
                printf("\n  Invalid choice! Please enter 1-7.\n");
        }
    }

    return 0;
}
