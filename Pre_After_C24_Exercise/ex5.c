<<<<<<< HEAD
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>

struct infor
{
    char name[32];
    char mssv[8];
    uint8_t course_c;
};

void infor_input(struct infor * stu_infor)
{
    int c_course;
    printf("Nhap ho va ten sinh vien: ");
    scanf("%[^\n]%*c", stu_infor -> name); // %[^\n]%*: until enter is pressed, unless continue reading char

    printf("Nhap ma so sinh vien: ");
    scanf("%[^\n]%*c", stu_infor -> mssv);

    printf("Nhap khoa C da tham gia: ");
    scanf("%d", &c_course);
    stu_infor -> course_c = (uint8_t) c_course;

    printf("\n");   
}

void infor_print(struct infor * stu_infor)
{
    printf("Ho va ten sinh vien: %s\n", stu_infor -> name);
    printf("Ma so sinh vien: %s\n", stu_infor -> mssv);
    printf("Khoa C ma sinh vien da tham gia: %d\n", (int)(stu_infor -> course_c));
}

int main(void)
{
    struct infor NMH_info;
    infor_input(&NMH_info);
    infor_print(&NMH_info);

    getch();
    return 0;
}
