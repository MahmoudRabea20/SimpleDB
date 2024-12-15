#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef unsigned char uint8;
typedef struct SimpleDB
{
	uint8 student_ID;
	uint8 student_year;
	uint8 course_IDs[3];
	uint8 course_grade[3];
}Database;

Database * student[MAX];
int number_of_entries = -1; //To act indicator of stack
int number;//To obtain the index of id existing from function and use it in other ones

void menu(void);
bool SDB_IsFull(void);
uint8 SDB_GetUsedSize(void);
bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades);
void SDB_DeleteEntry(uint8 id);
bool SDB_ReadEntry(uint8 id, uint8* year, uint8* subjects, uint8* grades);
void SDB_GetIdList(uint8* count, uint8* list);
bool SDB_IsIdExist(uint8 ID);
void Exit(void)
{
    exit(0);
}

int main()
{
	menu();

	return 0;
}
void menu(void)
{
	int choice, id, year, add_again,i,check=0;
	uint8 *count,*list,*id_year,*id_subjects,*id_grades,id_read,id_deleted;

	printf("Please chose one of below choices\n\n");
	printf("1) Add new entry\n"
		   "2) Read entries\n"
		   "3) Get list of entries IDs\n"
		   "4) Delete entry\n"
           "5) Exit\n");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		if (SDB_IsFull())
		{
			printf("The database is full \n\n");
			menu();
		}
		else
		{
			number_of_entries++;
			student[number_of_entries] = (Database*)malloc(sizeof(Database));
			label2:
			printf("enter ID of the student %d : ", number_of_entries + 1);
			scanf("%d", &id);
			for(i=0;i<number_of_entries;i++)
            {
                if(id==student[i]->student_ID)
                {
                    check++;
                }
            }
            if(check !=0)
            {
                printf("Error:there is a student with this id .\n");
                check=0;
                goto label2;
            }
			printf("enter year of the student %d : ", number_of_entries + 1);
			scanf("%d", &year);
			SDB_AddEntry(id, year, &student[number_of_entries]->course_IDs, &student[number_of_entries]->course_grade);
		}
		printf("To return to the main menu or to add another student press 0 : ");
		scanf("%d", &add_again);
		if (add_again == 0)
		{
			menu();
		}
		break;
	case 2:
        if (number_of_entries == -1)
		{
			printf("There is not any ID to read\n");
			menu();
		}
		else
		{
			printf("Please enter the id of the student to read his data : ");
			scanf("%d", &id_read);
			id_year=(uint8*)malloc(sizeof(uint8));
			id_subjects=(uint8*)malloc(3*sizeof(uint8));
			id_grades=(uint8*)malloc(3*sizeof(uint8));
			SDB_ReadEntry(id_read,id_year,id_subjects,id_grades);
			free(id_year);
			free(id_subjects);
			free(id_grades);
		}
		break;
	case 3:
        count=(uint8*)malloc(sizeof(uint8));
        list=(uint8*)malloc((number_of_entries+1)*sizeof(uint8));
        SDB_GetIdList(count,list);
        free(count);
        free(list);
		break;
	case 4:
		if (number_of_entries == -1)
		{
			printf("There is not any student to delete\n");
			menu();
		}
		else
		{
			printf("Please enter the id of the student to delete:");
			scanf("%d", &id_deleted);
			SDB_DeleteEntry(id_deleted);
		}
		break;
    case 5:
        Exit();
	default:
		printf("try again\n");
		menu();
		break;
	}
}

bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades)
{
	int i;

	student[number_of_entries]->student_ID = id;
	student[number_of_entries]->student_year = year;

	for (i = 0; i < 3; i++)
	{
		printf("enter ID of course %d :", i + 1);
		scanf("%d", subjects);
		subjects++;
	}
	for (i = 0; i < 3; i++)
	{
	    label1:
		printf("enter grade of course %d :", i + 1);
		scanf("%d", grades);
		if (!(grades[0] >= 0 && grades[0] <= 100))
		{
			printf("Please enter the grade between 0 and 100\n");
			goto label1;
		}
		else
		{
			grades++;
		}
	}
	if ((student[number_of_entries]->student_ID != 0) && (student[number_of_entries]->student_year != 0) &&
		(student[number_of_entries]->course_IDs[0] != 0) && (student[number_of_entries]->course_IDs[1] != 0) &&
		(student[number_of_entries]->course_IDs[2] != 0) && (student[number_of_entries]->course_grade[0] != 0) &&
		(student[number_of_entries]->course_grade[1] != 0) && (student[number_of_entries]->course_grade[2] != 0))
	{
		printf("\nThe new entry is successfully added\n\n");
		return 1;
	}
	else
	{
	    printf("\nThe new entry is not successfully added\n\n");
	    number_of_entries--;
		return 0;
	}
}

bool SDB_ReadEntry(uint8 id, uint8* year, uint8* subjects, uint8* grades)
{
    int i,j;

    if(!(SDB_IsIdExist(id)))
    {
        printf("Error : there is not student with this id to read,please enter the correct id\n");
		return 0;
    }
    else
    {
       *year=student[number]->student_year;
       for(i=0;i<3;i++)
       {
           subjects[i]=student[number]->course_IDs[i];
           grades[i]=student[number]->course_grade[i];
       }

       printf("ID of the student = %d\n",id);
       printf("Year of the student = %d\n",*year);
       for(j=0;j<3;j++)
       {
           printf("The id of course %d = %d and the grade = %d\n",j+1,subjects[j],grades[j]);

       }
       return 1;
     }
}

void SDB_DeleteEntry(uint8 id)
{
    int i=0,delete_again;

	if (!(SDB_IsIdExist(id)))
	{
		printf("Error : there is not student with this id to delete,please enter the correct id\n");
		menu();
	}
	else
	{
		while (number + i + 1 <=number_of_entries)
		{
			student[number + i] = student[number + i + 1];
			i++;
		}

		printf("Deleted successfully\n");
		free(student[number_of_entries]);
		number_of_entries--;
	}
	printf("To return to the main menu or to delete another student press 0 : ");
	scanf("%d", &delete_again);
	if (delete_again == 0)
	{
		menu();
	}
}

bool SDB_IsFull(void)
{
	if (number_of_entries == MAX-1)//9 10 students
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8 SDB_GetUsedSize()
{
	return (number_of_entries+1);
}

bool SDB_IsIdExist(uint8 id)
{
	int i, flag = 0;

	for (i = 0; i <=number_of_entries; i++)
	{
		if (id == student[i]->student_ID)
		{
			flag++;
			number = i;
			break;
		}
	}
	if (flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void SDB_GetIdList(uint8* count, uint8* list)
{
    int i,j;

    *count=SDB_GetUsedSize();

    printf("The number of entries currently exists in the database = %d\n",*count);

    for(i=0;i<=number_of_entries;i++)
    {
        list[i]=student[i]->student_ID;
    }
    for(j=number_of_entries;j>=0;j--)
    {
        printf("ID of the student %d = %d\n",j+1,list[j]);

    }
    menu();
}
