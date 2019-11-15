/* a program of Canteen Management containg the list to :
	1.) Add new items.
	2.) All items list.
	3.) Edit item list.
	4.) Delete items.
	5.) Search item By Id.
	6.) Search item By Name.
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std ;

void menu() ;
void addItems() ;
void itemsList() ;
void editList() ;
void deleteItem() ;
void searchById() ;
void searchByName() ;

class Canteen
{
	private:
		char s1[255] ;
		char quantity[255] ;
		int id ;
		char price[255] ;
	public :
		// giving id number of item .
		int give_id()
		{
			return id ;
		}
		// giving name of item .
		string give_name()
		{
			return s1 ;
		}
		void store_data() ;
		void print_data() ;
} ; // class of Canteen
// for storing the data of item
void Canteen :: store_data() 
{
	cout << "Item id : " ;
	cin >> id ;
	cout << "Item name : " ;
	cin.ignore() ;
	cin.getline(s1,255) ;
	cout << "Price : " ;
	cin.getline(price,255) ;
	cout << "Quantity : " ;
	cin.getline(quantity,255) ;
	return ;
}
// for printing the data of item
void Canteen :: print_data()
{
	cout << "Item id : " << id ;
	cout << "\nItem name : " << s1 ;
	cout << "\nPrice : " << price ;
	cout << "\nQuantity : " << quantity << endl ;
	return ;
}

int main()
{
	while(1)
	{
		menu() ;
		cout << "\n Write number you want: " ;
		char option ;
		cin >> option ;
		switch(option)
		{
			case '1' :	cout << endl ;
						addItems() ;         //calling addItems function.
						break ;
			case '2' :  cout << endl ;
						itemsList() ;		//calling itemsList function.
						break ;
			case '3' :  cout << endl ;
						editList() ;		//calling editList function.
						break ;
			case '4' :	cout << endl ;
						deleteItem() ;		//calling deleteItem function.
						break ;
			case '5' :	cout << endl ;
						searchById() ;		//calling searchById function.
						break ;
			case '6' :  cout << endl ;
						searchByName() ;	//calling searchByName function.
						break ;
			default  : cout << "Please write number that is in list." ;
						exit(100) ;
		}
		system("pause") ;
		system("cls") ;			
	}
	return 0 ;
}
// menu of Canteen
void menu() 
{
	cout << "MENU OF CANTEEN..\n" ;
	cout << "1.) Add new items.\n" ;
	cout << "2.) All items list.\n" ;
	cout << "3.) Edit item list.\n" ;
	cout << "4.) Delete items.\n" ;
	cout << "5.) Search item By Id.\n" ;
	cout << "6.) Search item By Name.\n" ;
}
// showing option to add items in item list of canteen
void addItems()
{
	Canteen obj;
	ofstream send ;
	send.open("CanteenManagement.dat",ios::app | ios::binary) ;
	obj.store_data() ;
	send.write((char*)&obj,sizeof(Canteen)) ;
	send.close() ;
	return ;
}
// showing item list of canteen
void itemsList()
{
	Canteen obj;
	ifstream readFile ;
	readFile.open("CanteenManagement.dat",ios::binary) ;
	while(readFile.read((char*)&obj,sizeof(obj)))
	{
		obj.print_data() ;
		cout << endl ;
	}
	readFile.close() ;
	return ;
}
// showing option to edit item list of canteen
void editList()
{
	Canteen obj ;
	int n , found = 0  ;
	cout << "Write item id : " ;
	cin >> n ;
	fstream file ;
	file.open("CanteenManagement.dat",ios::in|ios::out|ios::binary) ;
	while(file.read((char*)&obj,sizeof(Canteen))&&found == 0)
	{
		if(obj.give_id()==n)
		{
			obj.print_data() ;
			cout << "\nWrite new details : \n" ;
			obj.store_data() ;
			int pos =-1*sizeof(obj) ;
			file.seekp(pos,ios::cur) ;
			file.write((char*)&obj,sizeof(Canteen)) ;
			found = 1 ;
		}
	}
	file.close() ;
	return  ;
}
// showing option to delete item from item list of canteen
void deleteItem() 
{
	Canteen obj ;
	int n , found = 0  ;
	cout << "Write item id to delete : " ;
	cin >> n ;
	fstream file1;
	file1.open("Copy.dat",ios::out|ios::binary) ;
	fstream file ;
	file.open("CanteenManagement.dat",ios::in|ios::out|ios::binary) ;
	while(file.read((char*)&obj,sizeof(Canteen))&&found == 0)
	{
		if(obj.give_id()!=n)
		{
			file1.write((char*)&obj,sizeof(Canteen)) ;
		}
	}
	file1.close() ;
	file.close() ;
	remove("CanteenManagement.dat") ;
	rename("Copy.dat","CanteenManagement.dat") ;
	return ;	
}
// showing option to search item from item list of canteen By writing item id  
void searchById() 
{
	Canteen obj ;
	int n , found = 0  ;
	cout << "Write item id : " ;
	cin >> n ;
	fstream file ;
	file.open("CanteenManagement.dat",ios::in|ios::out|ios::binary) ;
	while(file.read((char*)&obj,sizeof(Canteen))&&found == 0)
	{
		if(obj.give_id()==n)
		{
			cout << "\nyour item is : \n" ;
			obj.print_data() ;
			found = 1 ;
		}
	}
	if(found==0)
	{
		cout << "\nItem id written by you is not in the list .\n" ;
	}
	file.close() ;
	return  ;
}
// showing option to search item from item list of canteen By writing item name 
void searchByName() 
{
	Canteen obj ;
	int found = 0  ;
	char name_item[255] ;
	cout << "Write item name : " ;
	cin.ignore() ;
	cin.getline(name_item,255) ;
	fstream file ;
	file.open("CanteenManagement.dat",ios::in|ios::out|ios::binary) ;
	while(file.read((char*)&obj,sizeof(Canteen))&&found == 0)
	{
		if(obj.give_name()==name_item)
		{
			cout << "\nyour item is : \n" ;
			obj.print_data() ;
			found = 1 ;
		}
	}
	if(found==0)
	{
		cout << "\nItem name written by you is not in the list .\n" ;
	}
	file.close() ;
	return  ;
}
