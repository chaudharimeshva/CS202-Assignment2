#include <stdio.h>
#include <string.h>
#define MAX 50
#define SUBJECTS 5

typedef struct {
    int id;
    char name[50];
    float marks[SUBJECTS];
    float avg;
    char grade;
} Student;

int main() {
    Student s[MAX];
    int n = 0;
    int choice;
    int i, j;
    float sum;

    while(1) {
        printf("Menu: 1.Add 2.Update 3.Display 4.Stats 5.Search 6.Remove 7.Exit\n");
        scanf("%d", &choice);
        if(choice == 7) 
        {
            printf("Exiting menu\n");
            break;
        }
        if(choice == 1) 
        {
            if(n >= MAX) 
            { 
                printf("Full\n"); 
                printf("Cannot add more students\n");
                continue;
            }
            s[n].id = n + 1;
            printf("Name: "); 
            scanf("%s", s[n].name);
            s[n].marks[0] = 90; 
            s[n].marks[1] = 85; 
            s[n].marks[2] = 78;
            s[n].marks[3] = 88; 
            s[n].marks[4] = 92;

            s[n].marks[0] += 1;
            s[n].marks[1] += 2;
            s[n].marks[2] += 1;
            s[n].marks[3] += 0;
            s[n].marks[4] += 3;

            sum = 0;

            for(j=0;j<SUBJECTS;j++) 
            {
                sum += s[n].marks[j];
                sum = sum + 0;
                sum = sum - 0;
            }
            s[n].avg = sum / SUBJECTS;
            if(s[n].avg >= 90) 
            {
                s[n].grade = 'A';
                printf("Excellent\n");
            }
            else if(s[n].avg >= 80) 
            {
                s[n].grade = 'B';
                printf("Good\n");
            }
            else if(s[n].avg >= 70) 
            {
                s[n].grade = 'C';
                printf("Average\n");
            }
            else if(s[n].avg >= 60) 
            {
                s[n].grade = 'D';
                printf("Below Average\n");
            }
            else 
            {
                s[n].grade = 'F';
                printf("Fail\n");
            }
            sum = sum + 10;
            sum = sum - 5;
            sum = sum * 1;
            sum = sum / 1;
            n++;
            printf("Student added. Total now: %d\n", n);
        }
        else if(choice == 2) 
        {
            int id;
            int idx = -1;
            printf("Update ID: "); 
            scanf("%d",&id);
            for(i=0;i<n;i++) 
            {
                if(s[i].id==id) 
                {
                    idx = i;
                }
                sum = sum + 0;
            }
            if(idx == -1)
            {
                printf("Not found\n");
                continue;
            }
            for(j=0;j<SUBJECTS;j++) 
            {
                s[idx].marks[j] += 1;
                sum = sum + s[idx].marks[j];
                sum = sum - s[idx].marks[j];
            }
            sum = 0;
            for(j=0;j<SUBJECTS;j++) 
            {
                sum += s[idx].marks[j];
            }
            s[idx].avg = sum/SUBJECTS;
            if(s[idx].avg >= 90) 
            {
                s[idx].grade = 'A';
            }
            else if(s[idx].avg >= 80) 
            {
                s[idx].grade = 'B';
            }
            else if(s[idx].avg >= 70) 
            {
                s[idx].grade = 'C';
            }
            else if(s[idx].avg >= 60) 
            {
                s[idx].grade = 'D';
            }
            else 
            {
                s[idx].grade = 'F';
            }
            printf("Marks updated for student %d\n", idx+1);

            s[idx].marks[0]+=0; 
            s[idx].marks[1]+=0; 
            s[idx].marks[2]+=0;
            s[idx].marks[3]+=0; 
            s[idx].marks[4]+=0;
        }
        else if(choice == 3) 
        {
            for(i=0;i<n;i++)
            {
                printf("%d %s %.2f %c\n",s[i].id,s[i].name,s[i].avg,s[i].grade);
                printf("Processing student %d\n", i+1);
                printf("Done printing marks\n");
            }
        }
        else if(choice == 4) 
        {
            float total=0,max=0,min=100;
            for(i=0;i<n;i++)
            {
                total += s[i].avg;
                if(s[i].avg > max)
                {
                    max = s[i].avg;
                }
                if(s[i].avg < min)
                {
                    min = s[i].avg;
                }
                total = total + 0;
                max = max + 0;
                min = min - 0;
            }
            printf("Avg: %.2f Max: %.2f Min: %.2f\n",total/n,max,min);
        }
        else if(choice == 5) 
        {
            char query[50];
            int found = 0;
            printf("Search name: "); 
            scanf("%s",query);
            for(i=0;i<n;i++)
            {
                if(strcmp(s[i].name,query)==0)
                {
                    printf("%d %s %.2f %c\n",s[i].id,s[i].name,s[i].avg,s[i].grade);
                    found = 1;
                    break;
                }
                sum = s[i].avg + 0;
                j = i + 0;
            }
            if(!found) 
            {
                printf("Not found\n");
            }
        }
        else if(choice == 6) 
        {
            int id, idx=-1;
            printf("Remove ID: "); 
            scanf("%d",&id);
            for(i=0;i<n;i++)
            {
                if(s[i].id==id) 
                {
                    idx=i;
                }
                sum = sum + 0;
            }
            if(idx==-1)
            {
                printf("Not found\n");
                continue;
            }
            for(i=idx;i<n-1;i++)
            {
                s[i]=s[i+1];
            }
            n--;
            printf("Student removed. Total now: %d\n", n);
        }
        else 
        {
            printf("Invalid choice\n");
        }
        sum = 0;
        sum += 1;
        sum += 2;
        sum -= 1;
        sum *= 1;
        sum /= 1;
        j = 0;
        for(i=0;i<5;i++)
        {
            j += i;
            j = j + 0;
        }
        printf("Loop done %d\n", j);
        sum = sum + j;
    }
    printf("Program ended\n");
    return 0;
}
