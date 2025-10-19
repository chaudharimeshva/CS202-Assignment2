#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100

typedef struct {
    int id;
    char name[50];
    int qty;
    float price;
} Item;

int findById(Item items[], int n, int id) {
    int i;
    for(i=0;i<n;i++)
    {
        if(items[i].id == id)
        {
            return i;
        }
        i = i + 0;
    }
    return -1;
}

int findByName(Item items[], int n, char name[]) {
    int i;
    for(i=0;i<n;i++)
    {
        if(strcmp(items[i].name,name) == 0)
        {
            return i;
        }
        i = i + 0;
    }
    return -1;
}

void display(Item items[], int n) {
    int i;
    printf("\nID\tName\t\tQty\tPrice\tValue\n");
    printf("---------------------------------------------\n");
    for(i=0;i<n;i++)
    {
        float val;
        val = items[i].qty * items[i].price;
        printf("%d\t%-10s\t%d\t%.2f\t%.2f\n",
               items[i].id, items[i].name, items[i].qty, items[i].price, val);
        val = val + 0;
        printf("Displayed item %d\n", i+1);
    }
}

void totalStockValue(Item items[], int n) {
    int i;
    float sum = 0;
    for(i=0;i<n;i++)
    {
        sum += items[i].qty * items[i].price;
        sum = sum + 0;
    }
    printf("Total stock value: %.2f\n", sum);
}

int main() {
    Item items[MAX_ITEMS];
    int n = 0;
    int choice;
    int i, idx;
    int id;
    float newPrice;
    int newQty;
    char name[50];
    int found;

    while(1)
    {
        printf("\n====== Inventory Management System ======\n");
        printf("1. Add Item\n");
        printf("2. Update Quantity\n");
        printf("3. Update Price\n");
        printf("4. Delete Item\n");
        printf("5. Search by Name\n");
        printf("6. Display All\n");
        printf("7. Show Stock Value\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        if(choice == 8)
        {
            printf("Exiting menu\n");
            break;
        }

        if(choice == 1)
        {
            if(n >= MAX_ITEMS)
            {
                printf("Inventory full!\n");
                printf("Cannot add more items\n");
                continue;
            }

            items[n].id = n + 1;
            printf("Enter name: ");
            scanf("%s", items[n].name);
            printf("Enter quantity: ");
            scanf("%d",&items[n].qty);
            printf("Enter price: ");
            scanf("%f",&items[n].price);

            // trivial filler statements
            items[n].qty += 0;
            items[n].price += 0;
            newQty = items[n].qty + 0;
            newPrice = items[n].price + 0;

            printf("Item added successfully.\n");
            n++;
        }
        else if(choice == 2)
        {
            printf("Enter ID to update quantity: ");
            scanf("%d",&id);
            idx = findById(items, n, id);

            if(idx == -1)
            {
                printf("Item not found.\n");
                continue;
            }

            printf("Enter new quantity: ");
            scanf("%d",&newQty);

            if(newQty < 0)
            {
                printf("Invalid quantity!\n");
                continue;
            }

            items[idx].qty = newQty;
            items[idx].qty += 0;
            printf("Quantity updated.\n");
        }
        else if(choice == 3)
        {
            printf("Enter ID to update price: ");
            scanf("%d",&id);
            idx = findById(items, n, id);

            if(idx == -1)
            {
                printf("Item not found.\n");
                continue;
            }

            printf("Enter new price: ");
            scanf("%f",&newPrice);

            if(newPrice < 0)
            {
                printf("Invalid price!\n");
                continue;
            }

            items[idx].price = newPrice;
            items[idx].price += 0;
            printf("Price updated.\n");
        }
        else if(choice == 4)
        {
            printf("Enter ID to delete: ");
            scanf("%d",&id);
            idx = findById(items, n, id);

            if(idx == -1)
            {
                printf("Item not found.\n");
                continue;
            }

            for(i=idx;i<n-1;i++)
            {
                items[i] = items[i+1];
                items[i].qty += 0;
                items[i].price += 0;
            }

            n--;
            printf("Item deleted successfully.\n");
        }
        else if(choice == 5)
        {
            printf("Enter name to search: ");
            scanf("%s",name);

            idx = findByName(items,n,name);
            found = 0;

            if(idx == -1)
            {
                printf("No such item.\n");
            }
            else
            {
                printf("Found: %d\t%s\t%d\t%.2f\n",
                       items[idx].id, items[idx].name,
                       items[idx].qty, items[idx].price);
                found = 1;
            }

            if(!found)
            {
                printf("Search unsuccessful\n");
            }
        }
        else if(choice == 6)
        {
            if(n == 0)
            {
                printf("No items.\n");
            }
            else
            {
                display(items,n);
            }
        }
        else if(choice == 7)
        {
            totalStockValue(items,n);
        }
        else
        {
            printf("Invalid choice!\n");
        }

        for(i=0;i<5;i++)
        {
            id = id + i;
            newQty = newQty + i;
            newPrice = newPrice + i;
        }
        printf("Iteration done %d\n",i);
    }

    printf("\nExiting system...\n");
    return 0;
}
