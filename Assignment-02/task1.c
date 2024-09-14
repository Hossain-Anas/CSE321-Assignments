#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

struct Paratha
{
    int unit_price;
    int quantity;
};

struct Vegetable
{
    int unit_price;
    int quantity;
};

struct Mineral_Water
{
    int unit_price;
    int quantity;
};



int main()
{
    struct Paratha paratha1;
    struct Vegetable vegetable1;
    struct Mineral_Water water1;

    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha1.quantity);

    printf("\nUnit Price : ");
    scanf("%d", &paratha1.unit_price);


    printf("\nQuantity Of Vegetable : ");
    scanf("%d", &vegetable1.quantity);

    printf("\nUnit Price : ");
    scanf("%d", &vegetable1.unit_price);
    


    printf("\nQuantity Of Mineral Water: ");
    scanf("%d", &water1.quantity);

    printf("\nUnit Price : ");
    scanf("%d", &water1.unit_price);

    int n;

    printf("\nNumber of people : ");
    scanf("%d", &n);

    float total = paratha1.quantity*paratha1.unit_price
                + vegetable1.quantity*vegetable1.unit_price
                + water1.quantity * water1.unit_price;

    float perHead = total/n;

    printf("\nIndividual people will pay : %.2f tk\n", perHead);


    return 0;
}
