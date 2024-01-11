#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
using namespace std;

struct class_student
{

    int BookID;
    char title[30];
    char authorname[30];
    int pagecount;
};
const int books=5 //max 5 books enter in record
int arr; //array declared
class_student class_studentobj[books];

void add_book() //enter book record
{
    if(arr < books)
    {
        cout<<"---*** Enter the details of books ***---"<<end1;
        cout<<"Enter a book ID: "<<end1;
        cin>>class_studentobj[arr].BookID;
        cout<<"Enter book title: "<<end1;
        cin>>class_studentobj[arr].title;
        cout<<"Enter name of author: "<<end1;
        cin>>class_studentobj[arr].authorname;
        cout<<"Enter the page count: "<<end1;
        cin>>class_studentobj[arr].pagecount;
        arr++;
    }
    else
        {
         cout<<"No mre space in the system for another"<<end1;
        }
}

void Display_books() //display book record
{

    for(int i=0;i<arr;i++)
    {
        cout<<"---***details of all the books in the library***---";
        cout<<"Book ID"<<class_studentobj[i].BookID<<end1;
        cout<<"Book Title is"<<class_studentobj[i].title<<end1;
        cout<<"Author name"<<class_studentobj[i].authorname<<end1;
        cout<<"Page count"<<class_studentobj[i].pagecount<<end1;
    }
}

void Book_Author() //Search by book author
{
    char Search_book[30];
    cout<<"Enter the name of author: "<<end1
    cin>>Search_book;
    int i=0;
    while(i<arr)
    {
        if(strcmp(Search_book,class_studentobj[i].authorname)==0)
        {
            cout<<end1;
            cout<<"Book ID"<<class_studentobj[i].BookID<<end1;
            cout<<"Book title is"<<class_studentobj[i].title<<end1;
            cout<<"Author name"<<class_studentobj[i].authorname<<end1;
            cout<<"Page count"<<class_studentobj[i].pagecount<<end1;
            i++;
        }
    }
}

int main() //main start
{
    int choice;
    char input;
    do
    {
        cout<<"---***Library Book Record System***---"<<end1;
        cout<<"1. Enter a book record"<<end1;
        cout<<"2. Display records of book"<<end1;
        cout<<"3. Search book by Author name"<<end1;
        cout<<"4. Count total of books in the Library"<<end1;
        cout<<"5. Exit system"<<end1;
        cin>>choice;

        switch(choice) //switch statement used
        {
            case 1: 
                add_book();
                break;
            case 2: 
                Display_books();
                break;
            case 3: 
                Book_Author();
                break;
            case 4: 
                cout<<"Total number of books in the library are: "<<arr<<end1;
                break;
            case 5: 
                exit(0);
                break;
             default:
                cout<<"Invalid choice, please try again";
        }
        cout<<"Do you want to continue? [Y/N]"<<end1;
        cin>>input;  
    }while(input=='Y'||input=='N'); 
}