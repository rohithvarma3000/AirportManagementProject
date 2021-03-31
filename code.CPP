/* This is the Airport Management System
Created by Rohith Varma,M Kruthic Vignesh,
Narasimhan Srikanth and Nilesh Balu of class 12A5
*/
#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <conio.h>
int gater[15], countr[30], busr[15], bgr[5];
class aeroplane
{
	char FlNo[6];
	char Aname[50];
	char AD;
	char org[50];
	char dest[50];
public:
	void disp()
	{
		cout << "Flight Number: " << FlNo << endl;
		cout << "Airlines Name: " << Aname << endl;
		cout << "Origin       : " << org << endl;
		cout << "Destination  : " << dest;
	}
	char* retflno()
	{
		return FlNo;
	}
	char retAD()
	{
		return AD;
	}
	char* retaname() {
		return Aname;
	}
	void write();
	void modify();

}aero;



void aeroplane::write() //writes onto file
{
	ofstream fout("planedetails.dat", ios::binary | ios::app);
	if (!fout) { cout << "FNF"; return; }
	char rep;
	do {
		aeroplane ob;
		cout << "Enter Plane Details \n";
		cout << "Flight Number:";
		gets(ob.FlNo);
		cout << "Airlines Name:";
		gets(ob.Aname);
		cout << "Arrival(A)or Departure(D):";
		cin >>ob.AD;
		if (ob.AD != 'A' && ob.AD != 'D') {
			cout << "Error please provide code again:";
			cin >> ob.AD;
		}
		cout << "Origin       :";
		gets(ob.org);
		cout << "Destination  :";
		gets(ob.dest);
		fout.write((char*)&ob, sizeof(ob));
		cout << "Continue writing?";
		cin >> rep;
	} while (rep == 'y');
}

void aeroplane::modify()  //allows user to modify
{
	char flno[6];
	aeroplane ob, ob1;
	cout << "Enter Flight Number:";
	gets(flno);
	fstream fin("planedetails.dat", ios::binary | ios::in | ios::out | ios::beg);
	int f = 0;
	while (fin.read((char*)&ob, sizeof(ob)))
	{
		if (!strcmpi(ob.retflno(), flno))
		{
			cout << "Enter New Details\n";
			strcpy(ob1.FlNo, flno);
			cout << "Airlines Name:";
			gets(ob1.Aname);
			cout << "Arrival(A)or Departure(D):";
			cin >> ob1.AD;
			if (ob1.AD != 'A' && ob1.AD != 'D') {
				cout << "Error please provide code again:";
				cin >> ob1.AD;
			}
			cout << "Origin       :";
			gets(ob1.org);
			cout << "Destination  :";
			gets(ob1.dest);
			fin.seekp(-1 * ((int)sizeof(ob)), ios::cur);
			fin.write((char*)&ob1, sizeof(ob1));
			break;
		}
		else
			f++;
	}
	if (f != 0)
		cout << "Record not found\n";
}

class allo
{
	int NC, AC[10], AG, NB, AB[10], ABG, stat;
	char fno[6];
public:
	allo();
	void assignment();   //Funtion that calls all the below functions
	int gate();          //To allocate gate
	int bus(int[], int &);     //To allocate buses
	int baggage();       //To allocate baggage terminal
	int counter(int[], int &); //To allocate counters
	void deassignment(); //To deallocate
	void output();
	void reassign();
	char* retflnoallo()
	{
		return fno;
	}
	int retstat() {
		return stat;
	}
}al;
allo::allo()
{
		strcpy(fno, "NULL");
		stat = 0;
		NC = 0;
		AG = 0;
		NB = 0;
		ABG = 0;
		for (int i = 0; i < 10; i++)
		{
			AC[i] = 0;
			AB[i] = 0;
		}

}
void allo::assignment()
{
	allo ob;
	ob.stat = 0;
	aeroplane r;
	cout << "Enter Flight no:";
	gets(ob.fno);
	ifstream a("planedetails.dat", ios::binary | ios::beg);
	ofstream b("allocation.dat", ios::binary|ios::app);
	while (a.read((char*)&r, sizeof(r)))
	{
		if (strcmpi(ob.fno, r.retflno()) == 0)
		{
			ob.stat++;
			break;
		}
	}
	if (ob.stat == 0)
	{
		cout << "Flight not found\n";
		return;
	}

	ob.AG = gate();
	cout << "Enter the no of buses to be alloted\n";
	cin >> ob.NB;
	bus(ob.AB, ob.NB);
	if (r.retAD() == 'A')
	{
		ob.ABG = baggage();
		ob.NC = 0;
	}
	if (r.retAD() == 'D')
	{
		cout << "Enter the no of counters to be alloted\n";
		cin >> ob.NC;
		counter(ob.AC, ob.NC);
		ob.ABG = 0;
	}
	b.write((char*)&ob, sizeof(ob));

}
int allo::gate()
{
	int i, flag = 0;
	for (i = 0; i<15; i++)
	{
		if (gater[i] == 0)
		{
			gater[i] = 1;
			flag = 1;
			return i + 1;
		}
	}
	if (flag == 0)
	{
		cout << "No gates are available\n";
	}
	return 0;

}
int allo::bus(int z[], int &y)  //To allocate buses
{
	int i, flag = 0;
	for (i = 0; i<y; i++)
		for (int j = 0; j<15; j++)
		{
			if (z[i] > 0)
				continue;
			if (busr[j] == 0)
			{
				busr[j] = 1;
				z[i] = j + 1;
				flag++;
			}

		}
	if (flag != y)
	{
		cout << "Not enough buses\n";
		y = flag;
	}
	return 0;
}
int allo::baggage()
{
	int i, flag = 0;
	for (i = 0; i<5; i++)
	{
		if (bgr[i] == 0)
		{
			bgr[i] = 1;
			flag = 1;
			return i + 1;
		}
	}
	if (flag == 0)
	{
		cout << "No baggage terminals are available\n";
		return 0;
	}

	return 0;
}
int allo::counter(int d[], int &e)
{
	int i, flag = 0;
	for (i = 0; i<e; i++)
		for (int j = 0; j<30; j++)
		{
			if (d[i] > 0)
				continue;
			if (countr[j] == 0)
			{
				countr[j] = 1;
				d[i] = j + 1;
				flag++;
			}

		}
	if (flag != e)
	{
		cout << "Not enough counters\n";
		e = flag;
	}
	return 0;

}
void allo::deassignment()
{

	fstream a("allocation.dat", ios::binary | ios::in | ios::out | ios::beg);
	allo ob;
	cout << "Enter the Flight No:";
	gets(fno);
	while (a.read((char*)&ob, sizeof(ob)))
	{
		if (strcmpi(ob.fno,fno) == 0)
		{
			if (ob.stat == 0)
			{
				cout << "Flight already deallocated\n";
				return;
			}
			else
			{
				gater[ob.AG - 1] = 0;
				if (ob.ABG != 0) bgr[ob.ABG - 1] = 0;
		/*		ob.ABG = 0;
				ob.AG = 0;   */

				for (int i = 0; i < ob.NC; i++)
				{
					countr[ob.AC[i] - 1] = 0;
				}
			 /*	for (int j = 0; j < ob.NC; j++)
				{
					ob.AC[j] = 0;
				}           */
				for (int k = 0; k < ob.NB; k++)
				{
					busr[ob.AB[k] - 1] = 0;
				}
			    /*	for (int l = 0; l < ob.NB; l++)
				{
					ob.AB[l] = 0;
				}
				ob.NC = 0;
				ob.NB = 0; */
				ob.stat = 0;
			}
			a.seekp(-1 * ((int)sizeof(ob)), ios::cur);
			a.write((char*)&ob, sizeof(ob));
			break;
		}
	}

}

void allo::output()
{

	if (NC != 0)
	{
		cout << "\nNo of alloted counters:" << NC;
		cout << "\nCounters Allocated:";
		for (int i = 0; AC[i] != '\0'; i++)
			cout << AC[i] <<" ";
	}
	cout << "\nGATE:" << AG << "\nNo of alloted buses:" << NB;
	cout << "\nBuses Allocated: ";
	for (int i = 0; AB[i] != '\0'; i++)
		cout << AB[i] <<" ";
	if (ABG != 0)
	{
		cout << "\nBaggage terminal:" << ABG<<"\n";
	}
	if(stat==0)cout<<"The flight has been deallocated\n";
}
void allo::reassign()
{
	allo ob;
	ifstream fin("allocation.dat", ios::binary | ios::beg);
	while (fin.read((char*)&ob, sizeof(ob)))
	{
		if (ob.stat != 0)
		{
			gater[ob.AG - 1] = 1;
			if (ob.ABG != 0)bgr[ob.ABG - 1] = 1;
			for (int i = 0; i<ob.NB; i++)
			{
				busr[ob.AB[i] - 1] = 1;
			}
			for (int j = 0; j<ob.NC; j++)
			{
				countr[ob.AC[j] - 1] = 1;
			}
		}
	}
}

class accounting {
	char Flno[20];
	int NF;
	float CF, DT, AF, CFU, TC;
public:
	char* retflno() {
		return Flno;
	}
	void assigncost();
	void totalrevenue();
	void display() {                  //This is the function to display details from account.dat when flno is passed as arguement
		cout << "\nNumber of units of food:" << NF;
		cout << "\nCost of food:" << CF;
		cout << "\nTotal distance travelled in km:" << DT;
		cout << "\nAmount of fuel:" << AF;
		cout << "\nCost of fuel:" << CFU;
		cout << "\nTotal cost:" << TC;
	}
	void modcost();
}acco;
void accounting::assigncost(){            //this is the function to assign cost

	accounting ob1;
	char str[6];
	int flag = 0;
	cout << "Enter the flight number";
	gets(str);
	aeroplane ob;                                     //object of aeroplane is created here
	ifstream fin("planedetails.dat", ios::binary | ios::beg);
	if (!fin) {
		cout << "FNF"; return;
	}
	while (fin.read((char*)&ob, sizeof(ob)))
	{
		if (strcmpi(ob.retflno(), str) == 0) {
			flag = 1; break;
		}
	}
	fin.close();
	if (flag == 0) {
		cout << "Flight not found \n"; return;
	}

	strcpy(ob1.Flno, str);
	cout << "Enter number of unit of food required:";
	cin >> ob1.NF;
	cout << "Enter the distance to be travelled:";
	cin >> ob1.DT;
	ob1.CF = ob1.NF * 200.0;                        //Calculation occur here
	ob1.AF = ob1.DT * 5 + 5000;
	ob1.CFU = ob1.AF * 10;
	ob1.TC = 500000 + ob1.CF + ob1.CFU;
	ofstream fout("accounts.dat", ios::app | ios::binary);
	fout.write((char*)&ob1, sizeof(ob1));
	fout.close();
}
void accounting::totalrevenue(){    //This is the funtion to find the total revenue for admin
	accounting ob;
	ifstream fin("accounts.dat", ios::binary | ios::beg);
	if (!fin) {
		cout << "FNF"; return;
	}
	float sum = 0;
	while (fin.read((char*)&ob, sizeof(ob))) {
		sum += ob.TC;
	}
	cout << "\nThe total revenue is " << sum<<"\n";
	fin.close();
}
void accounting::modcost(){
	accounting ob1;
	char str[6];
	int flag = 0;
	cout << "Enter the flight number";
	gets(str);

	fstream fin("accounts.dat", ios::binary | ios::beg | ios::in | ios::out);
	if (!fin) {
		cout << "FNF"; return;
	}
	while (fin.read((char*)&ob1, sizeof(ob1)))
	{
		if (strcmpi(ob1.Flno, str) == 0) {
			flag = 1; break;
		}
	}
	if (flag == 0) {
		cout << "Flight not found in accounts file\n"; return;
	}
	strcpy(ob1.Flno, str);
	cout << "Enter nunber of unit of food required:";
	cin >> ob1.NF;
	cout << "Enter the distance to be travelled:";
	cin >> ob1.DT;
	ob1.CF = ob1.NF * 200.0;                        //Calculation occur here
	ob1.AF = ob1.DT * 5 + 5000;
	ob1.CFU = ob1.AF * 10;
	ob1.TC = 500000 + ob1.CF + ob1.CFU;
	fin.seekg((-1) * sizeof(ob1), ios::cur);
	fin.write((char*)&ob1, sizeof(ob1));
	fin.close();
}
class admin
{
public:
	void showall();
	void searchplane(char a[10]);
	void allostatus();
	void deallocateall();
	void serairline();
}adm;

void admin::showall()
{
	aeroplane ob;
	accounting ob1;
	allo ob2;
	int flag1 = 0, flag2 = 0;
	ifstream fin("planedetails.dat", ios::binary);
	ifstream fin1("accounts.dat", ios::binary);
	ifstream fin2("allocation.dat", ios::binary);
	fin.seekg(0, ios::beg);
	while (fin.read((char*)&ob, sizeof(ob)))
	{
		flag1 = 0; flag2 = 0;
		ob.disp();     //function to display the datamembers of object of aeroplane
		fin1.seekg(0, ios::beg);
		while (fin1.read((char*)&ob1, sizeof(ob1)))
		{
			if (!strcmpi(ob.retflno(), ob1.retflno()))
			{
				{
				ob1.display();                  /*to print the corresponding account details of the same flight*/
				flag1++;
				break;
				}
			}
		}
		if (flag1 == 0) {
			cout << "\nFlight not found in accounts file \n";
		}
		fin2.seekg(0, ios::beg);
		while (fin2.read((char*)&ob2, sizeof(ob2)))
		{
			if (!strcmpi(ob.retflno(), ob2.retflnoallo()))
			{
				flag2++;
				ob2.output();    /*to print the corresponding allocation details (like counters, baggages) of the same flight*/
					break;
			}

		}
		if (flag2 == 0) {
				cout << "Flight not found in allocation file\n";
			}
			getch();
	}
	fin.close();
	fin1.close();
	fin2.close();
}
void admin::searchplane(char a[10])  /*the flight number is given as an argument to search and display the details*/
{
	int flag = 0, flag1 = 0, flag2 = 0;
	aeroplane obj;
	accounting obj1;
	allo obj2;
	ifstream f("planedetails.dat", ios::binary);
	ifstream f1("accounts.dat", ios::binary);
	ifstream f2("allocation.dat", ios::binary);
	f.seekg(0, ios::beg);
	while (f.read((char*)&obj, sizeof(obj)))
	{
		flag1 = 0; flag2 = 0;
		if (!strcmpi(a, obj.retflno()))

	      {
		obj.disp();     /*function to display the datamembers (of class aeroplane) of the object that is being searched*/
			flag++;
			f1.seekg(0, ios::beg);
			while (f1.read((char*)&obj1, sizeof(obj1)))
			{
				if (!strcmpi(a, obj1.retflno()))
				{	obj1.display();    /*to print the corresponding account details of the same flight*/
				flag1++;
				break;
				}
			}
			if (flag1 == 0) {
				cout << "Flight not found in accounts file\n";
			}
			f2.seekg(0, ios::beg);
			while (f2.read((char*)&obj2, sizeof(obj2)))
			{
				if (!strcmpi(a, obj2.retflnoallo()))
			    {
				flag2++;
				if(obj2.retstat()==0)flag2--;
				else
					{obj2.output();    /*to print the corresponding allocation details (like counters, baggages) of the same flight*/
					break;}
			    }
			}
			if (flag2 == 0) {
				cout << "Flight not found in allocation file\n";
			}
			break;
		}
	}
	if (flag == 0)
		cout << "Plane details not found\n";
	f.close();
	f1.close();
	f2.close();
}
void admin::deallocateall()
{
	for (int i = 0; i<30; i++)
	{
		countr[i] = 0;
	}
	for (int j = 0; j<15; j++)
	{
		busr[j] = 0;
	}
	for (int k = 0; k<15; k++)
	{
		gater[k] = 0;
	}
	for (int l = 0; l<5; l++)
	{
		bgr[l] = 0;
	}
	remove("allocation.dat");
}
void admin::allostatus()
{
	int c = 0, g = 0, bt = 0, b = 0;    /*c stands for number of counters, g for number of gates, bt for baggage terminals, b for buses*/
	for (int i = 0; i<30; i++)
	{
		if (countr[i] == 0)
			c++;
	}
	for (int j = 0; j<15; j++)
	{
		if (busr[j] == 0)
			b++;
	}
	for (int k = 0; k<15; k++)
	{
		if (gater[k] == 0)
			g++;
	}
	for (int l = 0; l<5; l++)
	{
		if (bgr[l] == 0)
			bt++;
	}
	cout << "Number of counters unoccupied:" << c << "\n";
	cout << "Number of gates unoccupied:" << g << "\n";
	cout << "Number of baggage terminals unoccupied:" << bt << "\n";
	cout << "Number of buses unoccupied:" << b << "\n";
}
void admin::serairline()
{
	int flag = 0, flag1 = 0, flag2 = 0;
	aeroplane obj;
	accounting obj1;
	allo obj2;
	char str[10];
	cout << "Enter Airlines Name";
	gets(str);
	ifstream f("planedetails.dat", ios::binary);
	ifstream f1("accounts.dat", ios::binary);
	ifstream f2("allocation.dat", ios::binary);
	f.seekg(0, ios::beg);
	while (f.read((char*)&obj, sizeof(obj)))
	{
		if (!strcmpi(str, obj.retaname()))
		{
			flag1 = 0; flag2 = 0;
			obj.disp();     /*function to display the datamembers (of class aeroplane) of the object that is being searched*/
			flag++;
			f1.seekg(0, ios::beg);
			while (f1.read((char*)&obj1, sizeof(obj1)))
			{
				if (!strcmpi(obj.retflno(), obj1.retflno()))
				{	obj1.display();    /*to print the corresponding account details of the same flight*/
				flag1++;
				break;
				}
			}
			if (flag1 == 0) {
				cout << "Flight not found in accounts file\n";
			}
			f2.seekg(0, ios::beg);
			while (f2.read((char*)&obj2, sizeof(obj2)))
			{
				if (!strcmpi(obj.retflno(), obj2.retflnoallo()))
				{
				flag2++;
				if(obj2.retstat()==0)flag2--;
				else
					{
					obj2.output();    /*to print the corresponding allocation details (like counters, baggages) of the same flight*/
					break;}
				}
			}
			if (flag2 == 0) {
				cout << "Flight not found in allocation file\n";
			}
			getch();
		}
	}
	if (flag == 0)
	cout << "Plane details not found\n";
	f.close();
	f1.close();
	f2.close();
}
void usermodule() {
	clrscr();
	int ch;
	char rep = 'y';

	do {
		clrscr();
		cout<<"                    User Module";
		cout << "\nEnter Code\n1.Add Plane Details\n2.Modify Plane Details \n3.Assign gate,buses,baggage terminals,counters\n4.Deassign Gate,buses,baggage terminals,counters\n5.Enter cost details\n6.Modify Cost Details\n7.Return to Main Menu:";
		cin >> ch;
		if (ch == 1)
			aero.write();  //Funtion to add detials from class aeroplane
		else if (ch == 2)
			aero.modify();   //Function to modify plane detial in class aeroplane
		else if (ch == 3)
			al.assignment();   //Funtion to assign Gate,buses,baggage terminals,counters form class allocat
		else if (ch == 4)
			al.deassignment();   //Funtion to deassign Gate,buses,baggage terminals,counters form class allocat
		else if (ch == 5)
			acco.assigncost();//Funtion to assign cost
		else if (ch == 6)
			acco.modcost();
		else if (ch == 7)
			return;
		else cout << "Invalid Choice";
		cout << "Do you want to continue in user module:";
		cin >> rep;
	} while (rep == 'y');
	return;
}

void adminmodule() {
	int ch;
	char rep = 'y';
	do {    clrscr();
		cout<<"                    Admin Module";
		cout << "\nEnter Code\n1.Total Revenue\n2.Search And Display by Plane Number \n3.Search And Display By Airlines Name \n4.Display Details of all Planes\n5.Allocation Status\n6.Deassign all Gate,buses,baggage terminals,counters\n7.Return to Main Menu:";
		cin >> ch;
		if (ch == 1)
			acco.totalrevenue();  //Funtion to to give sum all total costs from class accounting
		else if (ch == 2)
		{
			char str[6];
			cout << "Enter Flight Number:";
			gets(str);
			adm.searchplane(str);   //Function to search and display details of a given class in class admin
		}
		else if (ch == 3) {
			adm.serairline();
		}
		else if (ch == 4)
			adm.showall();   //Funtion to display details of all planes form class allocat
		else if (ch == 5)
			adm.allostatus();   //Funtion to number of Gate,buses,baggage terminals,counters available form class admin
		else if (ch == 6)
			adm.deallocateall();//Funtion to deassign all Gate,buses,baggage terminals,counters
		else if (ch == 7)
			return;
		else cout << "Invalid Choice";
		cout << "Do you want to continue in admin module?";
		cin >> rep;
	} while (rep == 'y');
	return;
}

int main()
{
	clrscr();
	int ch;
	al.reassign();
	char rep = 'y';
	do {
		clrscr();
		cout << "                   Welcome to Airport Management System\n";
		cout << "Enter code \n1.User\n2.Admin";
		cin >> ch;
		if (ch == 1)usermodule();
		else if (ch == 2) {
			int pass;
			cout << "Enter Password:";
			cin >> pass;
			if (pass == 1234) adminmodule();
			else
				cout << "Password Is Incorrect\n";
		}
		else if (ch == 3) {
				remove("accounts.dat");
				remove("planedetails.dat");
				remove("allocation.dat");
				adm.deallocateall();
		}
		else cout << "Invalid Choice";
		cout << "Do you want to continue in the program?";
		cin >> rep;
	} while (rep == 'y');
	return 0;
}
