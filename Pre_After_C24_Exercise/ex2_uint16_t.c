#include <stdio.h>
#include <stdint.h>
#include <conio.h>

void ArrayInput(uint16_t array_enter[], int size)
{
    printf("Nhap gia tri tung phan tu:\n");
    for(int i=0;i<size;i++)
    {
        printf("arr[%d] = ",i);
        scanf("%d", &array_enter[i]);
    }
}                      

void ArrayPrint(uint16_t array_enter[], int size)
{
    printf("arr[] = { ");
    for(int i=0;i<size;i++)
    {
        printf("%d ", array_enter[i]);
    }
    printf("}\n");
}

void ArrayPrintAddress(uint16_t array_enter[], int size)
{
    printf("Dia chi cua tung phan tu: \n");
    for(int i=0;i<size;i++)
    {
        printf("&arr[%d] = %d\n", i, &array_enter[i]);
    }
}

int main()
{
    int size;
    uint16_t arrayEnter[100];
    do
    {
        printf("Nhap so phan tu n: ");
        scanf("%d",&size);
        printf("\n"); 
    } while((size <= 0) || (size > 16));

    printf("Khoi tao mang int arr[%d]\n",size);

    ArrayInput(arrayEnter, size);

    ArrayPrint(arrayEnter, size);
    printf("\n");

    ArrayPrintAddress(arrayEnter, size);
    printf("\n");

    getch();
    return 0;
}