#include <stdio.h>
#include <stdlib.h>
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

float ArrayAverage(int array_enter[], int size)
{   
    float result;
    float sum = 0;
    for(int i=0; i< size; i++)
    {
        sum += (float) array_enter[i];
    }

    return result = sum / size;
}

int main(void)
{
    int size;
    int arrayEnter[100];
    float average_result;

    do
    {
        printf("Nhap so phan tu n: ");
        scanf("%d",&size);
    } while((size <= 5) || (size > 16));

    printf("Khoi tao mang int arr[%d]\n",size);

    ArrayInput(arrayEnter, size);

    ArrayPrint(arrayEnter, size);
    printf("\n");

    ArrayPrintAddress(arrayEnter, size);
    printf("\n");

    average_result = ArrayAverage(arrayEnter, size);
    printf("Gia tri trung binh cua mang tren la: %.3f \n",average_result);

    getch();
    return 0;
}