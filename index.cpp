
                            //==================        About this project          ===================//

                                          //------ ====== <<<<< Name >>>>> ===== --------//

                        //   <<<<  Library Management System — C++ | OOP | Design Patterns | SOLID    >>>>>>   //

                                            //------ ====== <<<<< Description >>>>> ===== --------//
                //   <<<<   Developed an object-oriented library system using C++ to manage members and books (EBook, HardCopy). Applied SOLID 
                //          principles and implemented key design patterns including Singleton, Strategy, and Factory Method.   >>>>>    //

                                //   <<<<   Designed extensible class hierarchy using abstract classes (Book, User)    >>>>  //
                                //   <<<<   Enabled runtime polymorphism for unified book operations                   >>>>  //
                                //   <<<<   Implemented BookSearchStrategy to support flexible, pluggable search logic >>>>  //
                                //   <<<<   Used Singleton pattern for Library instance management                     >>>>  //
                                //   <<<<   Applied exception handling and modular command logic                       >>>>  //
                                //   <<<<   Documented code with clear structure and extensibility in mind             >>>>  //


#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


using namespace std;


//-----Used in auto BOOK ID generation--------//
int Bookisbn=2500;

//-----Used in auto User ID generation--------//
int UserId=2500001;

class HardCopy;
class EBook;
class BookSearchStrategy;

//------Book class Super class of all type of books---------//

class Book
{
    private:

    int BookISBN;
    string Title;
    string AuthorName;
    double Price;
    string Publisher;
    

    protected:

    string type;
    int Edition;
        
    public:

    Book() {

    }
    Book(string,string,double,string);

    int get_BookISBN();
    void set_Title(string);
    string get_Title();
    
    void set_AuthorName(string);
    string get_AuthorName();

    void set_Publisher(string);
    string get_Publisher();

    void set_price(int);
    int get_price();

    

    virtual string get_Type() = 0;
    virtual int  get_Edition() = 0;
    virtual void DisplayDetsils() = 0;
    virtual void set_TotalCopies(int) = 0;
    virtual void set_AvailableCopies(int) = 0;
    virtual int get_TotalCopies() = 0;
    virtual int get_AvailableCopies() = 0;

};

class EBook:public Book
{
    private:
    string DownloadLink;
    public:
    
    EBook(string,string,double,int,string,string);
    void set_DownloadLink(string);
    string get_DownloadLink();
    
    void set_Edition(int);
    int get_Edition();  
    
    string get_Type(); 
    void DisplayDetsils(); 

//------EBOOK does not  required these functions so these are
// implemented just to complete the abstract class 
//---implemented by only a return statement so that we can use 
//these class by overriding the virtual function of incomplete super class


    void set_TotalCopies(int){return;};
     int get_TotalCopies(){return 1;};

    void set_AvailableCopies(int){return;};
    int get_AvailableCopies(){return 1;};
};

//---HardCopy of Books------//

class HardCopy:public Book
{
    private:
    int TotalCopies=0;
    int AvailableCopies=0;

    public:
    HardCopy():Book(){

    }
    HardCopy(string,string,double,string,int);

    void set_TotalCopies(int);
    int get_TotalCopies();
    
    void set_AvailableCopies(int);
    int get_AvailableCopies();

    int get_Edition();

    string get_Type(); 

    void DisplayDetsils();  
    
};

class User
{
    private:
    int userId;
    string Password;
    protected:
    string name;
    public:

    User(string name) {
        this->userId =++UserId;
        this->name=name;
    }

    int get_userId(){
        return userId;
    }

    Book* search(BookSearchStrategy *strategy,vector<Book*>,string);
    bool  isAvailable(int,vector<Book*>);

    virtual void  ViewInformation()=0;

//----These function is not implemented now it can be implemented when 
// i add Authentication feature in LIBRARY MANAGENEMENT SYSTEM , but in this 
// project i want to showcase my OOPs concept so i didn't implement it for now
// i will do it later.......
    void Login();
    void LohOut();
    void ChangePassword();
    
};

//---Member class it stores information about member or user who is a 
// student of library it means one object of class Member is an student of library 
// who can borrow book and return it and can see the details of book he borrowed 

class Member:public User
{
    private:
    vector<Book*> Borrowed;

    public:
    Member(string name_):User(name_){
        
    }
    void set_Name(string);
    void set_StudentId(int);

    void set_BorrowedBook(Book*);
    vector<Book*>& get_BorrowedBook();
     
    int get_userid(){
        return get_userId();
    }

    string get_Name();
    
    void DisplayDetails();
    
    void viewBorrowedBook();
    void ViewInformation(){
        cout<<endl<<"name : "<<name<<endl;
        cout<<"user id : "<<get_userId()<<endl;
    };
};


//----========="OWNER" IT MEANS " ADMIN OF LIBRARY "=========----//

// owner has power to operate whole library an owner or admin can 
// Add new Books, Remove Books , Add new Member in library, Remove the
// members from library , can see all the members of library , can 
// see all the books of library, issue book to a student (member) of library ,
// collect the issued bool , see details of all the book borrowed by a specific maner (student) 

// --in future it can be scalable if Owner want to add some staff in 
//library in different position he can add staffs remove staffs see their 
// details....etc......

class Owner:public User
{
    public:
    Owner(string name):User(name){

    }

    int get_userid(){
        return get_userId();
    }

    void ViewInformation(){
        cout<<endl<<"name : "<<name<<endl;
        cout<<"user id : "<<get_userId()<<endl;
    };

    void AddBooks(vector<Book*> &,string,string,double,string,string,int,string);
    void RemoveBook(vector<Book*> &,int,string);
    
    User* FindMemberById(int,vector<User*> &);
    void RegisterMember(string,vector<User*> &);
    void RemoveMember(vector<User*> &);

    void ViewAllBook(vector<Book*> &);
    void ViewAllMembers(vector<User*> &);

    void UpdateInformation(vector<Book*>&);

    void IssueBook(Book &,Member &,vector<Book*>&);
    void Collect_Book(Member &,vector<Book*> &);
};

//=====================LIBRARY==================//

//------The central management system of LIBRARY it is a singelton class
//  it means only one library's instance can be formed 
// it stores detail about all the user of library and books available in library

//  it hold an instance of owner who is only owner of library and performed
// all the owner's behaviour , there is no other owner and method to add a
// new owner in future to make it scalable if owner want can add different staffs 
// and assign them their access  

class Library
{
    private:

    //=============== " CREATIONAL DESIGN PATERN " ===================//
            //==========" SINGELTON "============//


    //------By making private constructor and add a function to get instance 
    // Library become a singletion class and only one instance of library can
    //  be formed in whole programme  
    static Library* instance;
    Library() : o1("Anmol") {
       
    }

    public:

    static Library* getInstance() {
    if (!instance)
        instance = new Library();
    return instance;
    }

    vector<Book*> Books;
    vector<User*> AllMembers;
    Owner o1;

    Book* FindBookByISBN(int);
    User* FindMemberById(int);

    void DisplayAllAvailableBooks();

};

Library* Library::instance = nullptr;

//=============== " DESIGN PATERN " ===================//
        //==========" STRATEGY "============//

//--BookSearcgStrategy class is a strategy (super) class of searching 
// by making its subclass we can implement different type of searching 
// but we didn't require to change our existing code to search book by 
// different way by author by , by isbn number, by title,etc.....
// in this way by implementing strategy patern  we follow  :- 
//
//             "---===== " Open/Closed principle" =======-----" 
//        "---===== " sinle responsibility principle " ======----"
//
//  in my project 

class BookSearchStrategy
{
    public:
    virtual Book* search(vector<Book*>& books, const string& query) = 0;

};

class SearchByTitle : public BookSearchStrategy {
public:
    Book* search(vector<Book*>& books, const string& query) override {
        for (auto b : books)
            if (b->get_Title() == query) return b;
        return nullptr;
    }
};

class SearchByIsbn : public BookSearchStrategy {
public:
    Book* search(vector<Book*>& books, const string& query) override {
        int isbn = stoi(query);
        for (auto b : books)
            if (b->get_BookISBN() == isbn) return b;
        return nullptr;
    }
};

//------------------------------------------------------Book-------------------------------------------------------------------------//

Book :: Book(string title,string authorName,double price,string publisher) {
    BookISBN=++Bookisbn;
    this->Title=title;
    this->AuthorName=authorName;
    this->Price=price;
    this->Publisher=publisher;
    
}

void Book::set_Title(string s)
{
    Title=s;
}

void Book::set_AuthorName(string s)
{
    AuthorName=s;
}

void Book::set_Publisher(string s)
{
    Publisher=s;
}


void Book::set_price(int n)
{
    Price=n;
}

int Book::get_BookISBN()
{
    return BookISBN;
}

string Book::get_Publisher()
{
    return Publisher;
}

string Book::get_Title()
{
    return Title;
}

string Book::get_AuthorName()
{
    return AuthorName;
}

int Book::get_price()
{
    return Price;
}


//------------------------------------------------------------------EBook---------------------------------------------------------------//

EBook::EBook(string title,string author,double price,int edition,string publisher,string link) : Book(title,author,price,publisher)
{
    try
    {
        set_Edition(edition);
        type="ebook";
        this->DownloadLink=link;
    }
    catch(...)
    {
        cout<<endl<<"there is some exception in setting book "<<endl;
    }
}

void EBook::set_DownloadLink(string s)
{
    DownloadLink=s;
};

string EBook::get_Type()
{
    return type;
}

string EBook::get_DownloadLink()
{
    return DownloadLink;
}

void EBook::set_Edition(int n)
{
    Edition=n;
}

int EBook::get_Edition()
{
    return Edition;
}

//---- display details of book -----//

void EBook::DisplayDetsils()
{
    cout<<endl<<"details of this book are given below : "<<endl;

    cout<<endl<<"Type : EBook";
    cout<<endl<<"title : "<<get_Title();
    cout<<endl<<"author : "<<get_AuthorName();
    cout<<endl<<"ISBN number : "<<get_BookISBN();
    cout<<endl<<"publisher name : "<<get_Publisher();
    cout<<endl<<"edition year : "<<get_Edition();
    cout<<endl<<"price : "<<get_price()<<endl;
}


//---------------------------------------------------------HardCopy---------------------------------------------------------------//

HardCopy::HardCopy(string title,string author,double price,string publisher,int edition) : Book(title,author,price,publisher)
{
    try
    {
        this->Edition=edition;
        type="hardcopy";
    }
    catch(...)
    {
        cout<<endl<<"there is some exception in setting book "<<endl;
    }
    
}

void HardCopy::set_TotalCopies(int n)
{
    TotalCopies=n;
}

void HardCopy::set_AvailableCopies(int n)
{ 
    AvailableCopies=n;
}

int HardCopy::get_TotalCopies()
{
    return TotalCopies;
}

int HardCopy::get_AvailableCopies()
{
    return AvailableCopies;
}

int HardCopy::get_Edition()
{
    return Edition;
}

void HardCopy::DisplayDetsils()
{
    cout<<endl<<"details of this book are given below : "<<endl;
    
    cout<<endl<<"Type : HardCopy";
    cout<<endl<<"title : "<<get_Title();
    cout<<endl<<"author : "<<get_AuthorName();
    cout<<endl<<"ISBN number : "<<get_BookISBN();
    cout<<endl<<"publisher name : "<<get_Publisher();
    cout<<endl<<"edition year : "<<get_Edition();
    cout<<endl<<"price : "<<get_price()<<endl;
}


string HardCopy::get_Type()
{
    return type;
}


//----------------------------------------------------------Member-------------------------------------------------------------------------//


void Member::set_Name(string s)
{
    name=s;
}

string Member::get_Name()
{
    return name;
}

void Member::DisplayDetails()
{
    cout<<endl<<"name : "<<get_Name();
    cout<<endl<<"student id : "<<get_userid()<<endl;
}

void Member::set_BorrowedBook(Book* h1)
{
    Borrowed.push_back(h1);
    cout<<endl<<"pushed"<<endl;
}

void Member::viewBorrowedBook()
{
    cout<<endl<<"details of borrowed books are given below : "<<endl;
    for(auto x:Borrowed)
    {
        x->DisplayDetsils();
    }
}

vector<Book*>& Member::get_BorrowedBook()
{
    return Borrowed;
}

//---------------------------------------------------------------------User----------------------------------------------------------------//

Book* User::search(BookSearchStrategy *strategy,vector<Book*> arr,string isbn)
{
    return strategy->search(arr,isbn );
}

//----check the availability of book by isbn number-----//

bool User::isAvailable(int isbn,vector<Book*> arr)
{
        for(auto x:arr)
        {
            if(x->get_BookISBN()==isbn)
            return true;
        }
        return false;
}


//---------------------------------------------------------Owner--------------------------------------------------------------------//


void Owner::AddBooks(vector<Book*> &arr,string title,string author,double price,string publisher,string type,int edition,string link="")
{
    //=============== " DESIGN PATERN " ===================//
        //==========" STRATEGY "============//
    
//------By implementing book by this type we follow  partial factory method 
//  we need to do aome smal change in this method if we add a new type of book 
//  eg. AudioBook (new sub class of book) 

// we can make it fully factory method but ther se some sort of issue
// that each time we need to change the availablecopies and totalcopies 
// of hardbook so if book is hardcopy implemntation somehow varies...
// so it is partial factory method design patern
    
    if(type=="hardcopy")
    {
        
        Book *newBook=new HardCopy(title,author,price,publisher,edition);
        arr.push_back(newBook);
        cout<<"Hard copy of book added successfully"<<endl;
        
        int count=0;
        for(auto x:arr)
        {
            if(title==x->get_Title())
            {
                if(count<x->get_AvailableCopies())
                   count+=1;
                x->set_AvailableCopies(x->get_AvailableCopies()+1);
                
            }
        }
        newBook->set_AvailableCopies(newBook->get_AvailableCopies()+count);
        cout<<"Hardcopy added successfully"<<endl;
        
    }
    else if(type=="ebook")
    {


        Book *newBook=new EBook(title,author,price,edition,publisher,link);
        for(auto x:arr)
        {
            if(title==x->get_Title()&&edition==x->get_Edition()){
                Bookisbn--;
                throw 2;
            }
        }
        arr.push_back(newBook);
        cout<<"Ebook added successfully"<<endl;
        
    }
}

void Owner::RemoveBook(vector<Book*> &arr,int isbn,string type)
{
    try
    {

//----check availability of book ---------//
        if(!isAvailable(isbn,arr))
            throw 3;
    
//----if available we get the book so that we can get title and change (decrease) 
// Availablecopies and TotalCopies of all book have same title --------//

        BookSearchStrategy *bs=new SearchByIsbn();
        Book *h1= search(bs,arr,to_string(isbn));
        int count=0;
        for(auto x:arr)
        {
            if(x->get_BookISBN()==isbn)
            {
                arr.erase(arr.begin()+count);
                cout<<endl<<"book removed successfully"<<endl;

                if(type=="hardcopy")
                {
                    
                    for(auto x:arr){
                        if(h1->get_Title()==x->get_Title()){
                            x->set_AvailableCopies(x->get_AvailableCopies()-1);
                            x->set_TotalCopies(x->get_TotalCopies()-1);
                        }
                    }
                }
                break;
            }
            count++;
        }
    }
    catch(int e)
    {
        if(e==3){cout<<endl<<"book not found in EBook"<<endl;}        
    }
    catch(...)
    {
        cout<<endl<<"there is some exception in remove function"<<endl;
    }
}

void  Owner::RegisterMember(string name,vector<User*> &AllMembers)
{
    Member *mem=new Member(name);
    AllMembers.push_back(mem);

    cout<<endl<<"membered registered "<<endl;
    
}

void Owner::RemoveMember(vector<User*> &AllMembers)
{
    int id;
    cout<<endl<<"enter the id of member you want to remove : ";
    cin>>id;
    User *mem=FindMemberById(id,AllMembers);
    if(!mem)
       throw 7;
    Member* m = dynamic_cast<Member*>(mem);
    if(m->get_BorrowedBook().size()!=0)
       throw 8;
    int count=0;
    for(auto x:AllMembers)
    {
        if(x->get_userId()==id)
        {
           AllMembers.erase(AllMembers.begin()+count);
           break;
        }
        count++;
    }
    cout<<endl<<"member removed sucessfully"<<endl;
}

User* Owner::FindMemberById(int id,vector<User*> &AllMembers)
{
    for(auto x:AllMembers)
    {
        if(x->get_userId()==id)
           return x;
    }
    return nullptr;
}

void Owner::ViewAllBook(vector<Book*> &arr)
{
    for(auto x:arr)
    {
        x->DisplayDetsils();
    }
}

void Owner::ViewAllMembers(vector<User*> &mem)
{
    for(auto x:mem)
        x->ViewInformation();
}

void Owner::IssueBook(Book &h1,Member &mem,vector<Book*> &arr)
{
    RemoveBook(arr,h1.get_BookISBN(),"hardcopy");
    mem.set_BorrowedBook(&h1);//----set book in member's borrowed book list
    cout<<endl<<"book issued successfully"<<endl;
}



void Owner::Collect_Book(Member &mem,vector<Book*> &arr)
{ 

    string isbn;
    
    cout<<endl<<"enter the isbn id of book you want to return : ";
    cin>>isbn;
    BookSearchStrategy *bs=new SearchByIsbn();
    Book *b1=mem.search(bs,mem.get_BorrowedBook(),isbn);//---if the book is not borrowed by that member than throw an int instance
    if(!b1)
       throw 4;
    
    AddBooks(arr,b1->get_Title(),b1->get_AuthorName(),b1->get_price(),b1->get_Publisher(),"hardcopy",b1->get_Edition());


//-----removed the book from the list of borrowed book of that member -------//
   int count1=0;
   for(auto x:mem.get_BorrowedBook())
   {
       if(x->get_BookISBN()==b1->get_BookISBN())
          mem.get_BorrowedBook().erase(mem.get_BorrowedBook().begin()+count1);
        count1++;

   }
   cout<<endl<<"book collected successfully"<<endl;
}

void Owner::UpdateInformation(vector<Book*> &arr)
{
    string isbn;
    cout<<endl<<"enter the isbn of book you want to update : ";
    cin>>isbn;
    BookSearchStrategy *bs=new SearchByIsbn();
    Book *b1=search(bs,arr,isbn);
    if(b1==nullptr)
       throw 5;
    int select;
    cout<<endl<<"1. update title : ";
    cout<<endl<<"2. update author name  : ";
    cout<<endl<<"3. update publisher name : ";
    cout<<endl<<"4. update price : ";
    cout<<endl<<"5. Update edition  : "<<endl;

    cout<<endl<<"please select what you want to delete : ";
    cin>>select;

    switch(select)
    {
        case 1:
        {
        cout<<endl<<"enter the new title : ";
        string title;
        cin>>title;
        b1->set_Title(title);
        break;
        }
        case 2:
        {
        cout<<endl<<"enter the new author name : ";
        string author_name;
        cin>>author_name;
        b1->set_AuthorName(author_name);
        break;
        }         
        case 3:
        {
        cout<<endl<<"enter the new publisher : ";
        string publisher;
        cin>>publisher;
        b1->set_Publisher(publisher);
        break;
        }
        case 4:
        {
        cout<<endl<<"enter the new price : ";
        int price;
        cin>>price;
        b1->set_price(price);
        break;
        }
        case 5:
        {
        cout<<endl<<"enter the new edition : ";
        int edition;
        cin>>edition;
        break;
        }
    }
}


//----------------------------------------------------------------------Library--------------------------------------------------------------//


Book* Library::FindBookByISBN(int id)
{
    for(auto x:Books)
    {
        if(x->get_BookISBN()==id)
           return x;
    }
    return nullptr;
}

User* Library::FindMemberById(int id)
{
    for(auto x:AllMembers)
    {
        if(x->get_userId()==id)
           return x;
    }
    return nullptr;
}

void Library::DisplayAllAvailableBooks()
{
    cout<<endl<<endl<<"--------- available e books are-----------------"<<endl<<endl;
    for(auto x:Books)
       x->DisplayDetsils();
}


int main()
{
  
    Library *lib=Library::getInstance();
    int option;
    while(1)
    {

        cout<<endl<<"functions in library : "<<endl;

        cout<<endl<<"1. RegisterMenber";
        cout<<endl<<"2. RemoveMember";
        cout<<endl<<"3. DisplayAllAvailableBooks";
        cout<<endl<<"4. AddBooks";
        cout<<endl<<"5. RemoveBook";
        cout<<endl<<"6. ViewAllBooks";
        cout<<endl<<"7. ViewAllMembers";
        cout<<endl<<"8. IssueBook";
        cout<<endl<<"9. CollectBook";
        cout<<endl<<"10. UpdateInformation";
        cout<<endl<<"11. View detail of specific Book";
        cout<<endl<<"12. View Detail of borroewed book by a member";
        cout<<endl<<"13. Exit"<<endl;

    
        cout<<endl<<"select option : ";
        cin>>option;


        switch(option)
        {
            case 1:
                cout << endl<<"Registering member..." << endl;
                try{
                   string name;
                   cout<<endl<<"enter your name"<<endl;
                   cin>>name;
                   lib->o1.RegisterMember(name,lib->AllMembers);
                }
                catch(int e)
                {
                    if(e==6){cout<<endl<<"A member ia already registered with this id"<<endl;}
                }
                break;
            
            case 2:
                cout << "\nRemoving a member..." << endl;
                try{
                lib->o1.RemoveMember(lib->AllMembers); // INPUT 5
                }
                catch(int e)
                {
                    if(e==7){cout<<endl<<"this memeber is not registered with library"<<endl;}
                    if(e==8){cout<<endl<<"This member borowed some book collect book before to remove"<<endl;}
                }
                break;
            
            case 3:
                cout << "\nViewing all available books..." << endl;
                lib->DisplayAllAvailableBooks();
                break;
            
            case 4:
                cout << "\nAdding an Ebook or a HardCopy book..." << endl;
                try{
                cout<<endl<<"enter the title : ";
                string title;
                cin>>title;

                cout<<endl<<"enter the author name : ";
                string author;
                cin>>author;

                cout<<endl<<"enter the new publisher : ";
                string publisher;
                cin>>publisher;

                cout<<endl<<"enter the new price : ";
                double price;
                cin>>price;

                cout<<endl<<"enter the type of book : ";
                string type;
                cin>>type;

                cout<<endl<<"enter the new edition : ";
                int edition;
                cin>>edition;

                string link="";
                if(type=="Ebook"){
                    cout<<endl<<"enter the link : ";
                    cin>>link;
                }
                lib->o1.AddBooks(lib->Books,title,author,price,publisher,type,edition,link);
                }
                catch(int e)
                {
                    if(e==2){cout<<endl<<"A book is already present in library with this id"<<endl;}
                }
                break;
            
            case 5:
            {
                cout << "\nRemoving a book by ISBN..." << endl;
                int removeISBN;
                cout << "Enter ISBN to remove: ";
                cin >> removeISBN;
                string type;
                cout<<endl<<"enter teh type of books : ";
                cin>>type;
                lib->o1.RemoveBook(lib->Books, removeISBN,type);
                break;
            }
            case 6:
                lib->o1.ViewAllBook(lib->Books);
                break;

            case 7:
                cout << "\nViewing all registered members..." << endl;
                lib->o1.ViewAllMembers(lib->AllMembers);
                break; 

            case 8:
            {
                cout << "\nIssuing a hard copy book to a member..." << endl;
                int hardCopyISBN;
                cout <<endl<<"Enter ISBN of the hardcopy book to issue: ";
                cin >> hardCopyISBN;
                int userId;
                cout << "Enter user ID of the member: ";
                cin >> userId;

                Book* bookPtr = lib->FindBookByISBN(hardCopyISBN);
                User* memberPtr = lib->FindMemberById(userId);
                if (bookPtr && memberPtr) 
                    lib->o1.IssueBook(*bookPtr, *dynamic_cast<Member*>(memberPtr),lib->Books);
                else
                    cout<<endl<<"member or book not found"<<endl;
                break;
            }
            case 9:
            {
                cout<<endl<<"collecting book...................."<<endl;
                cout << "Enter student ID of the member: ";
                int userId;
                cin>>userId;
                try{
                User* memberstr = lib->FindMemberById(userId);
                if(!memberstr)
                   throw 10;
                lib->o1.Collect_Book(*dynamic_cast<Member*>(memberstr),lib->Books);
                }
                catch(int e)
                {
                    if(e==4){cout<<endl<<"this book is not borrowed by this member"<<endl;}
                    if(e==10){cout<<endl<<"this member is not present"<<endl;}
                }
                break;
            }
            case 10:
                cout<<endl<<"information updating......................."<<endl;
                try{
                lib->o1.UpdateInformation(lib->Books);
                }
                catch(int e)
                {
                    if(e==5){cout<<endl<<"This book is not preent in library";}
                }
                break;
            
            case 11:
            {
                cout << "\nSearch by:\n1. Title\n2. ISBN\nChoose option: ";
                int searchType;
                cin >> searchType;

                BookSearchStrategy* strategy = nullptr;
                string query;
                cout << "Enter your search value: ";
                cin.ignore(); 
                getline(cin, query);

                if (searchType == 1)
                    strategy = new SearchByTitle();
                else if (searchType == 2)
                    strategy = new SearchByIsbn();

                if (strategy) {
                    Book* found = lib->o1.search(strategy, lib->Books, query);
                    if (found)
                        found->DisplayDetsils();
                    else
                        cout << "\nBook not found.\n";
                }
                delete strategy; 
                break;
            }
            case 12:
            {
                cout << "Enter student ID of the member: ";
                int studentid;
                cin>>studentid;
                User* memberstr = lib->FindMemberById(studentid);
                Member *m=dynamic_cast<Member*>(memberstr);
                if(m)
                {
                    if(m->get_BorrowedBook().size()>0)
                        for(auto x:m->get_BorrowedBook())
                            x->DisplayDetsils();
                    else
                        cout<<endl<<"no book is borrowed by this member"<<endl;
                }
                else
                    cout<<endl<<"book not found"<<endl;
                break;
            }
            case 13:
                return 0;
        }
    }
    return 0;
}