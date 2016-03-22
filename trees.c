#include<stdio.h>
#include<string.h>
struct student
{
	char name[20];
	int score;
	struct student *left;
	struct student *right;
};
#define Len sizeof(struct student)
struct student *seek(struct student *p, char target[]);
struct student *insert(struct student *p, char name[], int mark);
int del(struct student *p, char target[]);
int main()
{
	struct student root = { "head", 100, NULL, NULL }, *p;
	int op, mark;
	char target[20];
	p = &root;
	while (1)
	{
		printf("What are you want to do?\n");
		printf("0-Exit,1-Seek,2-Insert,3-Delete\n");
		scanf("%d", &op);
		if (op == 1)
		{
			printf("Please enter the name you want to find\n");
			scanf("%s", &target);
			printf("%d\n", seek(p, target)->score);
		}
		else if (op == 2)
		{
			printf("Please enter the name:\n");
			scanf("%s", &target);
			printf("Please enter his or her score:\n");
			scanf("%d", &mark);
			p = insert(&root, target, mark);
			printf("%s who's score is %d has been added successfully!\n",
				   p->name, p->score);
			p = &root;
		}
		else if (op == 3)
		{
			printf
				("Please enter the name if the item that you want to delete:\n");
			scanf("%s", &target);
			if (del(p, target) == 0)
				printf("Delete successfully!\n");
		}
		else if (op == 0)
		{
			break;
		}
		getchar();
	}
	return 0;
}

struct student *seek(struct student *p, char target[20])
{
	while (strcmp(target, p->name) != 0)
	{
		if (p->left != NULL || p->right != NULL)
		{
			if (strcmp(target, p->name) < 0)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		else
		{
			printf("We can not find it!\n");
			break;
		}
	}
	printf("seek%s %d\n", p->name, p->score);
	return p;
}

struct student *insert(struct student *p, char target[20], int mark)
{
	static struct student *temp;
	temp = (struct student *)malloc(Len);
	strcpy(temp->name, target);
	temp->score = mark;
	// seek,return the former item of the target
	while (strcmp(p->name, target) != 0)
	{
		if (p->left != NULL && p->right != NULL)
		{
			if (strcmp(target, (p->name)) < 0)
			{
				p = p->left;
				if (strcmp(target, (p->name)) > 0)
				{
					break;
				}
			}
			else if (strcmp(target, (p->name)) > 0)
			{
				p = p->right;
				if (strcmp(target, (p->name)) < 0)
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	// insert
	if (strcmp(target, p->name) == 0)
	{
		printf("The item has been added!\n");
	}
	else
	{

		if (strcmp(target, p->name) < 0)
		{
			temp->right = p->left;
			temp->left = NULL;
			p->left = temp;
			p = p->left;
		}
		else
		{
			temp->left = p->right;
			temp->right = NULL;
			p->right = temp;
			p = p->right;
		}
	}
	return p;
}

int del(struct student *p, char target[])
{
	struct student *temp,*q;
	while (strcmp(target, p->name) != 0)
	{
		q=p;
		if (p->left != NULL || p->right != NULL)
		{
			if (strcmp(target, p->name) < 0)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		else
		{
			printf("The item is not exisit!\n");
			return -1;
		}
	}
		p=q;
	// return p as the former item's pointer
	// delete
	if (strcmp(p->left, target) == 0)
	{
		for (temp = p->left; temp->right != NULL; temp = temp->right)
			;
		temp->right = p->right;
		free(p->left);
		p = p->left;
	}
	else if (strcmp(p->right, target) == 0)
	{
		for (temp = p->right; temp->left != NULL; temp = temp->left)
			;
		temp->left = p->left;
		free(p->right);
		p = p->right;
	}
	return 0;
}
