#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union
{
    int watts;
    char *expiration_date;
} Specifications;

typedef struct
{
    char name[30];
    int type; // 0 = Electronic, 1 = Food
    Specifications spec;
} Item;

int main()
{
    int n;
    char buffer[200];

    printf("Enter number of products: ");
    scanf("%d", &n);
    getchar();

    Item *items = (Item*)malloc(n * sizeof(Item));

    if(items == NULL)
    {
        perror("Memory allocation error");
        return 1;
    }

    for(int i = 0; i < n; i++)
    {
        printf("\nProduct name %d: ", i + 1);
        fgets(items[i].name, 30, stdin);
        items[i].name[strcspn(items[i].name, "\n")] = 0;

        printf("Type (0 = Electronic, 1 = Food): ");
        scanf("%d", &items[i].type);
        getchar();

        if(items[i].type == 0)
        {
            printf("Power consumption (Watts): ");
            scanf("%d", &items[i].spec.watts);
            getchar();
        }
        else
        {
            printf("Expiration date: ");
            fgets(buffer, 200, stdin);
            buffer[strcspn(buffer, "\n")] = 0;

            items[i].spec.expiration_date = (char*)malloc(strlen(buffer) + 1);
            strcpy(items[i].spec.expiration_date, buffer);
        }
    }

    printf("\n--- FOOD PRODUCTS ---\n");

    for(int i = 0; i < n; i++)
    {
        if(items[i].type == 1)
        {
            printf("Product: %s | Expires on: %s\n",
                   items[i].name,
                   items[i].spec.expiration_date);
        }
    }

    for(int i = 0; i < n; i++)
    {
        if(items[i].type == 1)
        {
            free(items[i].spec.expiration_date);
        }
    }

    free(items);

    return 0;
}
