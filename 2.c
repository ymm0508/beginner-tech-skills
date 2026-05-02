#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int id;           // 学号
    char name[20];    // 姓名
    float score;      // 分数
} Student;

void input(Student *s)
{
    static int i;
    printf("请输入学生信息：\n");
    for(i=0;i<5;i++)
    {
        scanf("%d %s %f",&s[i].id,s[i].name,&s[i].score);
    }
}
void output(Student *s)
{
    static int i;
    printf("学生信息如下：\n");
    for(i=0;i<5;i++)
    {
        printf("学号：%d 名字：%s 成绩：%.2f\n",s[i].id,s[i].name,s[i].score);
    }
}
float avaragescore(Student *s, float average)
{
    static int i;
    
    for(i=0;i<5;i++)
    {
        average += s[i].score;
    }
    average = average/5;
    return average;
}
void writefile(Student *s,float aver)
{
    FILE *fp;
    fp = fopen("students.txt","w");
    if(fp == NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    fprintf(fp,"%-10s %-20s %-10s\n","学号","姓名","分数");
    for(int i=0;i<5;i++)
    {
        fprintf(fp,"%-10d %-20s %-10.2f\n",s[i].id,s[i].name,s[i].score);
    }
    fprintf(fp,"平均成绩为：%f\n",aver);
    fclose(fp);
}
int main()
{
    float average = 0.0, aver = 0.0;
    Student students[5];
    input(students);
    output(students);
    aver = avaragescore(students, average);
    writefile(students, aver);
    printf("平均成绩为：%.2f\n", aver);
    return 0;
}
// “学生管理系统”V1.0 (120min)
// 1. 用C语言结构体定义“学生”（学号、姓名、分数）
// 2. 实现功能：录入5个学生信息，并计算平均分
// 3. 进阶：将数据写入到 students.txt文件中