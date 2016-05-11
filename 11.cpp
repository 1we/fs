/*C++ program to store and retrieve student data from file using hashing.
 Use any collision resolution technique.
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

node * h[29];

void insert()
{
	char name[15];
	char usn[15];
	char buffer[50];
	fstream out;
	out.open("student.txt",ios::app);
	if(!out)
	{
		cout<<"unable to open the file in append mode";
		getch();
		return;
	}
	cout<<"enter the name\n";
	cin>>name;
	cout<<"\nenter the usn\n";
	cin>>usn;
	
	strcpy(buffer,name);
	strcat(buffer,"|");
	strcat(buffer,usn);
	strcat(buffer,"\n");
	out<<buffer;
	out.close();
}

void hash_insert(char name1[],char usn1[],int hash_key)
{
	node * p;
	node * prev;
	node * curr;
	p=new node;
	
	strcpy(p->name,name1);
	strcpy(p->usn,usn1);
	p->link=NULL;
	prev=NULL;
	curr=h[hash_key];
	if(curr==NULL)
	{
		h[hash_key]=p;
		return;
	}
	while(curr!=NULL)
	{
		prev=curr;
		curr=curr->link;
	}
	prev->link=p;
}

void retrieve()
{
	fstream in;
	char name[15];
	char usn[15];
	int j;
	int count;
	node * curr;
	in.open("student.txt",ios::in);
	if(!in)
	{
		cout<<"unable to open the file in read mode\n";
		getch();
		exit(0);
	}
	while(!in.eof())
	{
		in.getline(name,15,'|');
		in.getline(usn,15,'\n');
		count=0;
		for(j=0;j<strlen(usn);j++)
		{
			count=count+usn[j];
		}
		count=count%29;
		hash_insert(name,usn,count);
	}
	cout<<"\nenter the usn\n";
	cin>>usn;
	count=0;
	for(j=0;j<strlen(usn);j++)	
	{
		count=count+usn[j];
	}
	count=count%29;
	curr=h[count];
	if(curr==NULL)
	{
		cout<<"record not found";
		getch();
		return;
	}
	do
	{
		if(strcmp(curr->usn,usn)==0)
		{
			cout<<"\nrecord found: "<<curr->usn<<" " <<curr->name;
			getch();	
			return;
		}
		else
		{
			curr=curr->link;
		}
	}while(curr!=NULL);
	
	if(curr==NULL)
	{
		cout<<"record not found";
		getch();
		return;
	}
}void main()
{
	int choice;
	clrscr();
	fstream out;
	out.open("student.txt",ios::out);
	if(!out)
	{
		cout<<"unable to open the file in append mode\n";	
		getch();
		exit(0);
	}
	for(;;)
	{	
		cout<<"\n1 : insert";
		cout<<"\n2 : retrieve";
		cout<<"\n3 : exit";
		cout<<"\nenter your choice";
		cin>>choice;
		switch(choice)
		{
			case 1:	insert();
				break;
	
			case 2:	retrieve();
				break;

			case 3:	exit(0);
	default:	cout<<"invalid option\n";
				break;
		}
	}
}