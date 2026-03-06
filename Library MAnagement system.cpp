#include<iostream>
#include<cstring>
using namespace std;

struct Book{
    int id;
    char title[50];
    float price;
};
struct Shelf{
    int shelfNo;
    int capacity;
    int currentBooks;
    Book* books;
};
void createShelves(Shelf*& shelves,int& shelfCount);
void addShelf(Shelf*& shelves,int& shelfCount);
void addBook(Shelf* shelves,int shelfCount);
void removeBook(Shelf* shelves,int shelfCount);
void display(Shelf* shelves,int shelfCount);
void expensiveBook(Shelf* shelves,int shelfCount);
void mergeShelves(Shelf*& shelves,int& shelfCount);
void removeEmptyShelves(Shelf*& shelves,int& shelfCount);
int main(){
    Shelf* shelves = NULL;
    int shelfCount = 0;
    int choice;
    do{
        cout<<"\n====== FAST LIBRARY SYSTEM ======\n";
        cout<<"1. Create Initial Shelves\n";
        cout<<"2. Add New Shelf\n";
        cout<<"3. Add Book to Shelf\n";
        cout<<"4. Remove Book by ID\n";
        cout<<"5. Display All Shelves\n";
        cout<<"6. Find Most Expensive Book\n";
        cout<<"7. Merge Two Shelves\n";
        cout<<"8. Remove Empty Shelves\n";
        cout<<"9. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;
    switch(choice){
    	case 1:{
        createShelves(shelves, shelfCount);
        break;
    	}
    	case 2:{
        addShelf(shelves, shelfCount);
        break;
    	}
    	case 3:{
        addBook(shelves, shelfCount);
        break;
    	}
    case 4:{
        removeBook(shelves, shelfCount);
        break;
   		}
    case 5:{
        display(shelves, shelfCount);
        break;
    	}
    case 6:{
        expensiveBook(shelves, shelfCount);
        break;
    	}
    case 7:{
        mergeShelves(shelves, shelfCount);
        break;
    	}
    case 8:{
        removeEmptyShelves(shelves, shelfCount);
        break;
    	}
    case 9:{
        cout << "Exiting program..." << endl;
        break;
    	}

    default:{
        cout << "Invalid choice. Try again." << endl;
    }
}

    }while(choice!=9);

    for(int i=0;i<shelfCount;i++){
        delete[] shelves[i].books;
    }
    delete[] shelves;
    return 0;
}

void createShelves(Shelf*& shelves,int& shelfCount){
    cout<<"Enter the number of the shelves: ";
    cin>>shelfCount;
    shelves = new Shelf[shelfCount];
    for(int i=0;i<shelfCount;i++)
    {
        cout<<"Shelf number: ";
        cin>>shelves[i].shelfNo;
        cout<<"Capacity: ";
        cin>>shelves[i].capacity;
        shelves[i].currentBooks=0;
        shelves[i].books = new Book[shelves[i].capacity];
    }
}
void addShelf(Shelf*& shelves,int& shelfCount){
    Shelf* temp = new Shelf[shelfCount+1];
    for(int i=0;i<shelfCount;i++)
        temp[i] = shelves[i];
    cout<<"Enter shelf number: ";
    cin>>temp[shelfCount].shelfNo;
    cout<<"Enter capacity: ";
    cin>>temp[shelfCount].capacity;
    temp[shelfCount].currentBooks=0;
    temp[shelfCount].books = new Book[temp[shelfCount].capacity];
    delete[] shelves;
    shelves=temp;
    shelfCount++;

    cout<<"Shelf added\n";
}
void addBook(Shelf* shelves,int shelfCount){
    int num;
    cout<<"Enter shelf number: ";
    cin>>num;
    for(int i=0;i<shelfCount;i++) {
    	if(shelves[i].shelfNo==num){
            if(shelves[i].currentBooks < shelves[i].capacity){
                int index=shelves[i].currentBooks;
                cout<<"Book ID: ";
                cin>>shelves[i].books[index].id;
                cout<<"Title: ";
                cin.ignore();
                cin.getline(shelves[i].books[index].title,50);
                cout<<"Price: ";
                cin>>shelves[i].books[index].price;
                shelves[i].currentBooks++;
                cout<<"Book added\n";
            }
            else{
                Book* temp = new Book[shelves[i].capacity+1];
                for(int j=0;j<shelves[i].capacity;j++)
                    temp[j]=shelves[i].books[j];
                delete[] shelves[i].books;
                shelves[i].books=temp;
                shelves[i].capacity++;

                cout<<"Shelf resized, add book again\n";
            }
            return;
        }
    }

    cout<<"Shelf not found\n";
}
void removeBook(Shelf* shelves,int shelfCount){
    int id;
    cout<<"Enter book ID: ";
    cin>>id;
    for(int i=0;i<shelfCount;i++){
        for(int j=0;j<shelves[i].currentBooks;j++){
            if(shelves[i].books[j].id==id){
                Book* temp=new Book[shelves[i].currentBooks-1];
                int k=0;
                for(int x=0;x<shelves[i].currentBooks;x++){
                    if(x!=j)
                        temp[k++]=shelves[i].books[x];
                }
                delete[] shelves[i].books;
                shelves[i].books=temp;
                shelves[i].currentBooks--;
                shelves[i].capacity--;

                cout<<"Book removed\n";
                return;
            }
        }
    }

    cout<<"Book not found\n";
}
void display(Shelf* shelves,int shelfCount){
    if(shelfCount==0){
        cout<<"No shelves\n";
        return;
    }
    for(int i=0;i<shelfCount;i++){
        cout<<"\nShelf "<<shelves[i].shelfNo<<endl;
        cout<<"Capacity "<<shelves[i].capacity<<endl;
        cout<<"Books "<<shelves[i].currentBooks<<endl;

        for(int j=0;j<shelves[i].currentBooks;j++){
            cout<<"ID: "<<shelves[i].books[j].id<<endl;
            cout<<"Title: "<<shelves[i].books[j].title<<endl;
            cout<<"Price: "<<shelves[i].books[j].price<<endl;
            cout<<endl;
        }
    }
}
void expensiveBook(Shelf* shelves,int shelfCount){
    float max=0;
    int shelf=-1;
    Book b;

    for(int i=0;i<shelfCount;i++){
        for(int j=0;j<shelves[i].currentBooks;j++){
            if(shelves[i].books[j].price>max){
                max=shelves[i].books[j].price;
                b=shelves[i].books[j];
                shelf=shelves[i].shelfNo;
            }
        }
    }
    if(max==0)
        cout<<"No books\n";
    else
    {
        cout<<"Most expensive book\n";
        cout<<"ID "<<b.id<<endl;
        cout<<"Title "<<b.title<<endl;
        cout<<"Price "<<b.price<<endl;
        cout<<"Shelf "<<shelf<<endl;
    }
}
void mergeShelves(Shelf*& shelves,int& shelfCount){
    int s1,s2;
    cout<<"Enter first shelf number: ";
    cin>>s1;
    cout<<"Enter second shelf number: ";
    cin>>s2;
    int i1=-1,i2=-1;
    for(int i=0;i<shelfCount;i++){
        if(shelves[i].shelfNo==s1) i1=i;
        if(shelves[i].shelfNo==s2) i2=i;
    }

    if(i1==-1 || i2==-1){
        cout<<"Shelf not found\n";
        return;
    }
    int total = shelves[i1].currentBooks + shelves[i2].currentBooks;
    Book* temp = new Book[total];
    int k=0;
    for(int i=0;i<shelves[i1].currentBooks;i++){
        temp[k++]=shelves[i1].books[i];
}
    for(int i=0;i<shelves[i2].currentBooks;i++){
        temp[k++]=shelves[i2].books[i];
}
    delete[] shelves[i1].books;
    shelves[i1].books=temp;
    shelves[i1].currentBooks=total;
    shelves[i1].capacity=total;

    delete[] shelves[i2].books;
    Shelf* newShelves=new Shelf[shelfCount-1];
    int x=0;
    for(int i=0;i<shelfCount;i++){
        if(i!=i2)
            newShelves[x++]=shelves[i];
    }
    delete[] shelves;
    shelves=newShelves;
    shelfCount--;
    cout<<"Shelves merged\n";
}
void removeEmptyShelves(Shelf*& shelves,int& shelfCount){
    for(int i=0;i<shelfCount;i++){
        if(shelves[i].currentBooks==0){
            delete[] shelves[i].books;
            Shelf* temp=new Shelf[shelfCount-1];
            int k=0;
            for(int j=0;j<shelfCount;j++){
                if(j!=i){
                    temp[k++]=shelves[j];
                }
            }

            delete[] shelves;
            shelves=temp;
            shelfCount--;
            cout<<"Empty shelf removed\n";
            return;
        }
    }
    cout<<"No empty shelf\n";
}
