#include <stdio.h>
#include <conio.h>

void ArrayInput(int array_enter[], int size)
{
    printf("Nhap gia tri tung phan tu:\n");
    for(int i=0;i<size;i++)
    {
        printf("arr[%d] = ",i);
        scanf("%d", &array_enter[i]);
    }
}                      

void ArrayPrint(int array_enter[], int size)
{
    printf("arr[] = { ");
    for(int i=0;i<size;i++)
    {
        printf("%d ", array_enter[i]);
    }
    printf("}\n");
}

void ArrayPrintAddress(int array_enter[], int size)
{
    printf("Dia chi cua tung phan tu: \n");
    for(int i=0;i<size;i++)
    {
        printf("&arr[%d] = %d\n", i, &array_enter[i]);
    }
}

void ArrayFind(int * max, int * min, int arrayfind[], int size)
{   
    * max=arrayfind[0];
    * min=arrayfind[0];

    for(int i=0;i<size;i++)
    {
        if(arrayfind[i] >= *max)
        {
            *max = arrayfind[i];
        }

        else if(arrayfind[i] <= *min)
        {
            *min = arrayfind[i];
        }
    }
}

int main()
{
    int max;
    int min;
    int size;
    int arrayEnter[100];
    do
    {
        printf("Nhap so phan tu n: ");
        scanf("%d", &size);
        printf("\n"); 
    } while ((size <= 5) || (size > 16));

    printf("Khoi tao mang int arr[%d]\n",size);

    ArrayInput(arrayEnter, size);

    ArrayPrint(arrayEnter, size);
    printf("\n");

    ArrayPrintAddress(arrayEnter, size);
    printf("\n");

    ArrayFind(&max, &min, arrayEnter, size);
    printf("Gia tri lon nhat trong mang tren la: %d.\n", max);
    printf("Gia tri nho nhat trong mang tren la: %d.\n", min);

    getch();
    return 0;
}