/*
C++ program to reclaim the free space resulting from the deletion of records using linked lists.
*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<iostream.h>
#include<iomanip.h>

class node
{
	public:	char name[15];
		char usn[15];
		node * link;
};

node * first=NULL;

void writefile()
{
	node * p;
	char buffer[100];
	fstream out;
	out.open("student.txt",ios::app);
	if(!out)
	{
		cout<<"unable to open the file in append mode";
		getch();
		exit(0);
	}
	p=first;
	while(p!=NULL)
	{
		strcpy(buffer,p->name);
		strcat(buffer,"|");
		strcat(buffer,p->usn);
		strcat(buffer,"\n");
		out<<buffer;
		p=p->link;
	}
}

void display()
{
	node * p;
	if(first==NULL)
	{
		cout<<"list is empty";
		return;
	}
	p=first;
	while(p!=NULL)
	{
		cout<<"|"<<p->name<<" "<<p->usn<<"|"<<"->";
		p=p->link;
	}
}

void insert()
{
	char name[20];
	char usn[15];
	node *p;
	node *q;

	cout<<"\nenter the name\n";
	cin>>name;
	cout<<"\nenter the usn\n";
	cin>>usn;
	cout<<"\n\n";
	
	p=new node;
	strcpy(p->name,name);
	strcpy(p->usn,usn);
	p->link=NULL;

	if(first==NULL)
	{
		first=p;
		writefile();
		display();
		return;
	}
	for(q=first;q->link!=NULL;q=q->link)
	{
		;
	}
	q->link=p;
	writefile();
	display();
}

void del()
{
	char usn[15];
	node * curr;
	node * prev;
	node * del;
	if(first==NULL)
	{
		printf("the list is empty.. deletion not possible");
		return;
	}
	cout<<"enter the usn to be deleted = ";
	cin>>usn;
	if(strcmp(first->usn,usn)==0)
	{
		cout<<"record deleted";
		del=first;
		delete(del);
		first=first->link;
		writefile();
		return;
	}
	prev=NULL;
	curr=first;
	while((strcmp(curr->usn,usn)!=0) && curr!=NULL)
	{
		prev=curr;
		curr=curr->link;
	}
	if(curr==NULL)
	{
		cout<<"the student with usn"<<usn<<"is not present";
		return;
	}
	prev->link=curr->link;
	writefile();
	display();
}

void main()
{
	int choice;
	clrscr();
	while(1)
	{
		printf("\n\n1 : insert_rear");
		printf("\n2 : delete_id");
		printf("\n3 : exit");
		printf("\n\nenter the choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:	insert();
				break;

			case 2:	del();
				break;

			case 3:	exit(0);
	
			default:	cout<<"invalid option";
				break;
		}
	}
}	