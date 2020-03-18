#include<iostream>          //Made by Gopal Pandey(me) and Vismit Kumbhalkar
#include<stdio.h>           //used for remove and rename function
#include<fstream>           //used for file handling
#include<stdlib.h>         
#include<conio.h>           //used for getch() function
#include<string.h>          //used for string operations
using namespace::std;       //use system("clear") in linux instead of system("cls")
void create_acc();
void new_emp();
void remove_emp();
void acc_holder();
void emp();
int alphabets(char*);
int nonalphabets(char*);
class account                                   //class for customers of bank   
{
    int acc_no;                  //account no 
    char password[14];           //password 
    float balance;               //balance of account
    char Name[25],Addr[200],ph_no[10];     //Name and Address of account holder     
    public:
    static int counter;          //a counter used to give account number to new accounts
    void initialize();
    void getdata();
    void disp();
    void deposit();
    void login();
    void withdraw();
    void receipt();  
    void storedata();  
    void all();
    void emp_access();
    void forgotpass(int,char*);
    void delacc(int);
    void edit();
    account()                    //constructor for new account object
    {
        balance=0;
    }
};
class employee                                  //class for employees of bank
{
    int emp_id;
    char password[14],Name[25];
    public:
    static int emp_counter;
    void getdata();
    void disp();
    void storedata();
    void login();
    void initialize();
};
int account::counter=1;                         //initializing counter of account to one if no database exists
int employee::emp_counter=1;                    //initializing counter of employee to one if no database exists

void account::initialize()                      //initializes the counter to non zero value if database already contains data
{
    ifstream infile("data.dat",ios::binary|ios::ate);
    if(infile)
    {
        infile.seekg(0, ios::end);
        if (infile.tellg() == 0)               //if empty data file then counter is initialized to 0 rather than garbage value
        { 
            infile.close();   
            return;
        }
        infile.seekg(int(infile.tellg())-sizeof(*this));
        infile.read((char*)this,sizeof(*this));
        account::counter=acc_no+1;
    }
    infile.close();
}
void account::getdata()                         //gets data for new account
{
    acc_no=account::counter;
    account::counter++;
    int i=0;
    int flag1=0,flag2;
    system("cls");
    char pwd[14],ch;
    cout<<"\n\t\t\tYour Account number is: "<<"|"<<acc_no<<"|"<<"\n";  //prints autogenerated account no
    while(true)
    {
        cout<<"\n\t\t\tEnter your name: ";          //Enter Name
        cin.ignore();
        cin.getline(Name,26);
    if(nonalphabets(Name)==0){
    	cout<<"\t\t\tName saved successfully.\n";
    	break;
	}
	else{
		cout<<"\t\t\tEnter a valid name.\n";
	}
    }
    while(flag1==0)              //Enter balance
    {
        cout<<"\n\t\t\tEnter the amount you would like to deposit(Minimum Rs.500): Rs.";
        cin>>balance;
        if(cin.fail()){
        	cout<<"\n\t\t\tERROR!!Character input in intergr input field.";
        	cout<<"\n\t\t\tPress any key";
        	getch();
        	exit(0);
		}
        else if(balance>499){
        	cout<<"\t\t\tDeposit Successful.";
        	cout<<"\n\t\t\tYour current balance is: Rs."<<balance<<"\n";
        	flag1=1;
		}
		else{
			cout<<"\t\t\tDeposit unsuccessful, minimum deposit should be Rs.500.\n";
			flag1=0;
		}
    }
    do                               
    {    
        i=0;        
        cout<<"\n\t\t\tSet a password: ";
        while(i<14)
        {
            ch=getch();
            if(ch==13)  //ascii for enter
                break;
            else if(ch=='\b'&& i>0)
            {
                cout<<"\b \b";
                i--;
            }            
            else
            {
                password[i]=ch;
                cout<<"*";
                i++;
            }        
        }
        password[i]='\0';            
        cout<<"\n\t\t\tConfirm the password: ";
        i=0;
        while(i<14)
        {
            ch=getch();
            if(ch==13)  //ascii for enter
                break;
            else if(ch=='\b'&&i>0)
            {
                cout<<"\b \b";
                i--;
            }            
            else
            {
                pwd[i]=ch;
                cout<<"*";
                i++;
            }        
        }
        pwd[i]='\0';
        if(strcmp(password,pwd)==0)
        {
            cout<<"\n\t\t\tPassword successfully saved.\n";
            break;
        }            
        else
            cout<<"\n\t\t\tPasswords do not match! Try again\n";          
    }while (1);
    do
    {
        cout<<"\n\t\t\tEnter your mobile number(10 digits): ";				//Entering phone number
        cin>>ph_no;
        if(strlen(ph_no)!=10 || alphabets(ph_no)==1){
        	cout<<"\t\t\tError!!! Enter a valid 10 digit phone number.\n";
        	flag2=0;
		}
		else{
			cout<<"\t\t\tPhone number saved successfully.\n";
			flag2=1;
		}
    } while(flag2==0);             //so that phone number is 10 digits long and not contain alphabets
    cout<<"\n\t\t\tEnter your address: ";
    cin.ignore();
    cin.getline(Addr,201);
	cout<<"\t\t\tAddress saved successfully.\n";   
    disp();
}
void account::disp()                            //displays data of account except for password
{
    cout<<"\n\t\t\tAcc no.: "<<acc_no;
    cout<<"\n\t\t\tName: "<<Name;
    cout<<"\n\t\t\tBalance: "<<balance;
    cout<<"\n\t\t\tPhone number: "<<ph_no;
    cout<<"\n\t\t\tAddress: "<<Addr;
    cout<<"\n\t\t\tPress any key to continue...\n";
    getch();
}
void account::login()                           //allows user to login to account and perform transactions
{
    fstream file("data.dat",ios::in|ios::out|ios::ate|ios::binary);
    if(file)
    {
        int acno,i=0,choice;
        char pwd[14],ch;
        cout<<"\n\t\t\tEnter account number: ";
        cin>>acno;
        if(cin.fail()){
        	cout<<"\n\t\t\tERROR!!Character input in integer input field";
        	cout<<"\n\t\t\tPress any key";
        	getch();
        	exit(0);
		}
        file.seekg(0);
        file.read((char*)this,sizeof(*this));
        while(!file.eof())
        {
            if(acc_no==acno)
            {
                cout<<"\n\t\t\tEnter Password: ";
                while(i<14)
                {
                    ch=getch();
                    if(ch==13)  //ascii for enter
                        break;
                    else if(ch=='\b'&&i>0)
                    {
                        cout<<"\b \b";
                        i--;
                    }            
                    else
                    {
                        pwd[i]=ch;
                        cout<<"*";
                        i++;
                    }        
                }
                pwd[i]='\0';
                if(strcmp(pwd,password)==0)
                {
                    system("cls");
                    while(1)
                    {
                        cout<<"\n\t\t\t-------------------------------------------------------------------------";
                        cout<<"\n\t\t\t\t\t\tWelcome to IIIT Nagpur Bank";
                        cout<<"\n\t\t\t-------------------------------------------------------------------------";
                        cout<<"\n\t\t\tAccount number: "<<"|"<<acc_no<<"|";
                        cout<<"\n\t\t\tAccont holder: "<<Name;
                        cout<<"\n\t\t\tPress\n\t\t\t1:To Deposit\n\t\t\t2:To Withdraw\n\t\t\t3:To edit details\n\t\t\t4:To delete account\n\t\t\t5:To logout";
                        cout<<"\n\t\t\tEnter your choice---> ";
                        //choice=5;
                        cin>>choice;
                        switch(choice)
                        {
                            case 1:system("cls");
                            deposit();
                            getch();
                            file.seekp(int(file.tellp())-sizeof(*this));
                            file.write((char*)this,sizeof(*this));
                            break;
                            case 2:system("cls");
                            withdraw();
                            getch();
                            file.seekp(int(file.tellp())-sizeof(*this));
                            file.write((char*)this,sizeof(*this));
                            break;
                            case 3:system("cls");
                            edit();
                            file.seekp(int(file.tellp())-sizeof(*this));
                            file.write((char*)this,sizeof(*this));
                            break;
                            case 4:file.close();
                            delacc(acc_no);
                            return;
                            break;
                            case 5:return;
                            break;
                            default:
                            	 if(cin.fail()){
                        			cout<<"\n\t\t\tERROR!!Character input in integer input field";
                        			cout<<"\n\t\t\tPress any key...";
                        			getch();
                        			exit(0);
								}
								else{
									cout<<"\n\t\t\tEnter correct choice.";
									cout<<"\n\t\t\tPress any key...";
									getch();
								}
                        }
                        system("cls");
                    }   
                }
                else            //if password is incorrect
                {
                	cout<<"\n\t\t\tIncorrect password!";
                	cout<<"\n\t\t\tPress any key to continue";
                	getch();
                    return;
                }
            }
            else{
            	cout<<"\n\t\t\tAccount not found!";
            	cout<<"\n\t\t\tPress any key to continue";
            	getch();
			}
            file.read((char*)this,sizeof(*this));
        }
        file.close();
    }
    else
    {
        cout<<"\n\t\t\tEmpty database! Please make an coount first";
        cout<<"Press any key...";
        getch();
        return;
    }  
}
void account::deposit()                         //function to deposit money to account
{
    int amt;
    cout<<"\n\t\t\tCurrent balance is Rs."<<balance;
    cout<<"\n\t\t\tEnter amount to be deposited: Rs.";
    cin>>amt;
    if(cin.fail()){
    	cout<<"\n\t\t\tERROR!!Character input in integer input fied";
    	cout<<"\n\t\t\tPress any key";
    	getch();
    	exit(0);
	}
    else if(amt>0){
    	balance=balance+amt;    
    	receipt();
	}
	else{
		cout<<"\n\t\t\tDeposit unsuccessful";
	}       
}   
void account::withdraw()                        //function to withdraw money from account
{
    int amt;
    cout<<"\n\t\t\tCurrent balance is Rs."<<balance;
    cout<<"\n\t\t\tEnter amount to be withdrawn: Rs.";
    cin>>amt;
    if(cin.fail()){
    	cout<<"\n\t\t\tERROR!!Character input in integer input fied";
    	cout<<"\n\t\t\tPress any key";
    	getch();
    	exit(0);
	}
    if(amt>0&&(balance-amt>=0)){
    	balance=balance-amt;
        receipt();
	}
    else
    	cout<<"\n\t\t\tWithdrawl unsuccessfull";
}
void account::receipt()                         //gives current balance of account
{
    cout<<"\n\t\t\tCurrent balance is updated to Rs."<<balance; 
}
void account::storedata()                       //writes objjct to file
{
    ofstream fout("data.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    cout<<"\n\t\t\tAbove details have been saved successfully in database.\n";
    cout<<"\n\t\t\tPress Enter";
    fout.close();
    return;
}
void account::forgotpass(int acno,char*mob)     //allows user to reset pwd using acc. no. and phone number
{
    fstream file("data.dat",ios::in|ios::out|ios::ate|ios::binary);
    if(file)
    {
        string mob_s=mob;
        int flag=0,i;
        char ch,pwd[14];    
        file.seekg(0);
        file.read((char*)this,sizeof(*this));
        while(!file.eof())
        {
            string ph_no_s=ph_no;            
            if( acno==acc_no)
            {  
                if(mob_s.compare(ph_no_s)==0 )
                {
                do                               //Entering phone number
                {            
                    cout<<"\n\t\t\tEnter new password: ";
                    i=0;
                    while(i<14)
                    {
                        ch=getch();
                        if(ch==13)  //ascii for enter
                            break;
                        else if(ch=='\b'&&i>0)
                        {
                            cout<<"\b \b";
                            i--;
                        }            
                        else
                        {
                            pwd[i]=ch;
                            cout<<"*";
                            i++;
                        }        
                    }
                    pwd[i]='\0';  
                    i=0;          
                    cout<<"\n\t\t\tConfirm the password: ";
                    while(i<14)
                    {
                        ch=getch();
                        if(ch==13)  //ascii for enter
                            break;
                        else if(ch=='\b'&&i>0)
                        {
                            cout<<"\b \b";
                            i--;
                        }            
                        else
                        {
                            password[i]=ch;
                            cout<<"*";
                            i++;
                        }        
                    }
                    password[i]='\0';
                    if(strcmp(password,pwd)==0)
                        break;            
                    else
                        cout<<"\n\t\t\tPasswords do not match! Try Again\n";          
                }while (1);
                
                file.seekp(int(file.tellp())-sizeof(*this));
                file.write((char*)this,sizeof(*this));
                cout<<"\n\t\t\tPassword updated."; 
                disp();
                flag=1;   
                break;
                return;
                }  
            }
            file.read((char*)this,sizeof(*this));
        }
        if(flag==0)
        {
            cout<<"\n\t\t\tWrong credentials!!";
            cout<<"\n\t\t\tPress any key to continue...";
            getch();
            return;
        }
    } 
    else
    {
        cout<<"\n\t\t\tEmpty database\n\t\t\tPress any key to continue...";
        getch();
        return;
    }       
}
void account::all()                             //prints details of all acounts on the console
{
    ifstream infile("data.dat",ios::binary);
    infile.seekg(0);
    infile.read((char*)this,sizeof(*this));
    while(!infile.eof())
    {        
        disp();
        infile.read((char*)this,sizeof(*this));
    }
}
void account::emp_access()                      //allows employee to access all any account
{
    ifstream infile("data.dat",ios::binary|ios::ate);
    if(infile)
    {
        int acno,flag=0;
        cout<<"\n\t\t\tEnter the acc no: ";
        cin>>acno;
        infile.seekg(0);
        infile.read((char*)this,sizeof(*this));
        while(!infile.eof())
        {
            if(acc_no==acno)
            {
                disp(); 
                flag=1;            
                break;
            }
            infile.read((char*)this,sizeof(*this));
        }
        if(flag==0)
        {
            cout<<"\n\t\t\tNo such account exits!";
        }        
    }
    else
    {
        cout<<"\n\t\t\tEmpty database!";
    }  
}
void account::delacc(int acno)                  //deletes account
{
    int stat1,stat2;
    ifstream infile("data.dat",ios::binary);
    ofstream outfile("temp.dat",ios::binary);
    if(infile)
    {
        infile.seekg(0);
        infile.read((char*)this,sizeof(*this));
        while(!infile.eof())
        {
            if(acc_no!=acno)
            {
                outfile.write((char*)this,sizeof(*this));
            }
            infile.read((char*)this,sizeof(*this));            
        }
        infile.close();
        outfile.close();
        //getch();
        stat1=remove("data.dat");
        stat2=rename("temp.dat","data.dat");
        //cout<<stat1<<" "<<stat2;
        cout<<"\n\t\t\tAccount deleted successfully.";
        cout<<"\n\t\t\tPress any key...";
        getch();
    }
}
void account::edit()                            //allows user to edit name ph no addr 
{
    int choice,flagz=0;
    cout<<"\n\t\t\tChoose what you want to edit\n\t\t\t1: Name\n\t\t\t2: Phone number\n\t\t\t3: Address\n\t\t\tEnter your choice---> ";
    cin>>choice;
    switch(choice)
    {
        case 1:while(true)
			    {
			        cout<<"\n\t\t\tEnter your name: ";          //Enter Name
			        cin.ignore();
			        cin.getline(Name,26);
			    if(nonalphabets(Name)==0){
			    	cout<<"\t\t\tName saved successfully.\n";
			    	break;
				}
				else{
					cout<<"\t\t\tEnter a valid name.\n";
				}
			    }
		/*cout<<"\n\t\t\tEnter Your name: ";     //Enter Name
        cin.ignore();
        cin.getline(Name,26);*/
        cout<<"\n\t\t\tUpdated details are:";
        disp();
        break;
        case 2:do
			    {
			        cout<<"\n\t\t\tEnter your mobile number(10 digits): ";				//Entering phone number
			        cin>>ph_no;
			        if(strlen(ph_no)!=10 || alphabets(ph_no)==1){
			        	cout<<"\t\t\tError!!! Enter a valid 10 digit phone number.\n";
			        	flagz=0;
					}
					else{
						cout<<"\t\t\tPhone number saved successfully.\n";
						flagz=1;
					}
			    } while(flagz==0);
        cout<<"\n\t\t\tUpdated details are:";
        disp();
        break;
        case 3:cout<<"\n\t\t\tEnter your address: ";
        cin.ignore();
        cin.getline(Addr,201);
        cout<<"\n\t\t\tUpdated details are:";
		disp();    
        break;
        default:
        	if(cin.fail()){
        		cout<<"\n\t\t\tERROR!!Characte input in integer input field";
        		cout<<"\n\t\t\tPress any key...";
        		getch();
        		exit(0);
			}
			else{
				cout<<"\n\t\t\tEnter correct choice";
				cout<<"\n\t\t\tPress any key...";
				getch();
			}
    }
}

void employee::initialize()                     //initializes the counter to non-zero value if database already contains data
{
    ifstream infile("emp.dat",ios::binary|ios::ate);
    if(infile)
    {
        infile.seekg(0, ios::end);              //if empty data file then counter is initialized to 0 rather than garbage value
        if (infile.tellg() == 0) 
        { 
            infile.close();   
            return;
        }
        infile.seekg(int(infile.tellg())-sizeof(*this));
        infile.read((char*)this,sizeof(*this));
        employee::emp_counter=emp_id+1;
    }
    infile.close();
}
void employee::login()
{
    fstream file("emp.dat",ios::in|ios::out|ios::ate|ios::binary);
    if(file)
    {
        account obj;
        int empid,i=0,choice,acno;
        char pwd[14],ch;
        cout<<"\n\t\t\tEnter employee id: ";
        cin>>empid;
        file.seekg(0);
        file.read((char*)this,sizeof(*this));
        while(!file.eof())
        {
            if(emp_id==empid)
            {
                cout<<"\n\t\t\tEnter Password: ";
                while(i<14)
                {
                    ch=getch();
                    if(ch==13)  //ascii for enter
                        break;
                    else if(ch=='\b'&&i>0)
                    {
                        cout<<"\b \b";
                        i--;
                    }            
                    else
                    {
                        pwd[i]=ch;
                        cout<<"*";
                        i++;
                    }        
                }
                pwd[i]='\0';
                if(strcmp(pwd,password)==0)
                {
                    system("cls");
                    while(1)
                    {
                        cout<<"\n\t\t\t-------------------------------------------------------------------------";
                        cout<<"\n\t\t\t\t\t\tWelcome to IIIT Nagpur Bank";
                        cout<<"\n\t\t\t-------------------------------------------------------------------------";
                        cout<<"\n\t\t\tEmployee:";
                        cout<<"\n\t\t\tPress\n\t\t\t1: To see all records\n\t\t\t2: To check a paritcular account\n\t\t\t3:To delete an account\n\t\t\t4:To logout ";
                        cout<<"\n\t\t\tEnter your choice:---> ";
                        cin>>choice;
                        switch(choice)
                        {
                            case 1:system("cls");
                            obj.all();
                            getch();
                            break;
                            case 2:system("cls");
                            obj.emp_access();
                            getch();
                            break;
                            case 3:system("cls");
                            cout<<"\n\t\t\tEnter Account no be deleted: ";
                            cin>>acno;
                            obj.delacc(acno);
                            break;
                            case 4:return;
                            break;
                            default:
                            	if(cin.fail()){
									cout<<"\n\t\t\tERROR!!Character input in integer input field";
									cout<<"\n\t\t\tPress any key";
									getch();
									exit(0);
								}
								else{
									cout<<"\n\t\t\tEnter correct choice.";
									cout<<"\n\t\t\tPress any key to continue";
               						getch();
									}
                        }
                        system("cls");
                    }   
                }
                else
                {
                    cout<<"\n\t\t\tWrong credentials!";
                    return;
                }                
            }
            file.read((char*)this,sizeof(*this));
        }
    }
    else
    {
        cout<<"\n\t\t\tEmpty database";
        return;
    }    
}
void employee::getdata()                        //gets data for new employee
{
    emp_id=employee::emp_counter;
    employee::emp_counter++;
    int i=0;
    char pwd[14],ch;     
	while(true)
		{
			    cout<<"\n\t\t\tEnter your name: ";          //Enter Name
			        cin.ignore();
			        cin.getline(Name,26);
			    if(nonalphabets(Name)==0){
			    	cout<<"\t\t\tName saved successfully.\n";
			    	break;
				}
				else{
					cout<<"\t\t\tEnter a valid name.\n";
				}
			    }   
    do                               //Entering phone number
    {            
        cout<<"\n\t\t\tSet a password: ";
        i=0;
        while(i<14)
        {
            ch=getch();
            if(ch==13)  //ascii for enter
                break;
            else if(ch=='\b'&&i>0)
            {
                cout<<"\b \b";
                i--;
            }            
            else
            {
                pwd[i]=ch;
                cout<<"*";
                i++;
            }        
        }
        pwd[i]='\0';  
        i=0;          
        cout<<"\n\t\t\tConfirm the password: ";
        while(i<14)
        {
            ch=getch();
            if(ch==13)  //ascii for enter
                break;
            else if(ch=='\b'&&i>0)
            {
                cout<<"\b \b";
                i--;
            }            
            else
            {
                password[i]=ch;
                cout<<"*";
                i++;
            }        
        }
        password[i]='\0';
        if(strcmp(password,pwd)==0)
        {
            cout<<"\n\t\t\tPassword successfully saved";
            break;
        }            
        else
            cout<<"\n\t\t\tPasswords do not match!";          
    }while (1);
    disp();
}
void employee::disp()                           //displays data of employee
{
    cout<<"\n\t\t\tEmployee id: "<<emp_id;
    cout<<"\n\t\t\tName: "<<Name;
}
void employee::storedata()                      //store data of new employee
{
    ofstream fout("emp.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
    return;
}
int main()                                      //main
{  
    account obj1;   
    employee obj2;     
    int ch;                    //refer readme.txt for understanding
    char mpwd[4],chr;
    system("cls");    
    obj1.initialize(); 
    obj2.initialize(); 
    while(1)
    {
        int i=0;
        cout<<"\n\t\t\t-------------------------------------------------------------------------";
        cout<<"\n\t\t\t\t\t\tWelcome to IIIT Nagpur Bank";
        cout<<"\n\t\t\t-------------------------------------------------------------------------";
        cout<<"\n\t\t\tPress \n\t\t\t1:If you are an Account Holder.\n\t\t\t2:If you are a Bank Employee.\n\t\t\t3:If you want to open a new account.\n\t\t\t4:If you are a new employee.\n\t\t\t5:To Exit.";
        cout<<"\n\t\t\tEnter your choice:--->  ";
        cin>>ch;
        switch(ch)
        {
        	break;
            case 1:acc_holder();
            break;
            case 2:emp();
            break;
            case 3:create_acc();
            getch();  
            break;
            case 4:cout<<"\n\t\t\tEnter bank Master Pin: ";
            //cin>>mpwd;
            while(i<4)
                {
                    //cout<<i;
                    chr=getch();
                    if(chr==13)  //ascii for enter
                        break;
                    else if(chr=='\b'&&i>0)
                    {
                        cout<<"\b \b";
                        i--;
                    }            
                    else
                    {
                        mpwd[i]=chr;
                        cout<<"*";
                        i++;
                    }        
                }
            mpwd[i]='\0';
            //cout<<'\n'<<mpwd;
            if(strcmp(mpwd,"1234")==0)      //This master pin is used so that anyone can't just create a new emmoyee account
                new_emp();     //it will only be known to employees of the bank
            else
                cout<<"\n\t\t\tWrong MasterPin";     
            getch();         
            break;
            case 5:system("cls");
            cout<<"\n\n\t\tMade by....\n\t\tBT18CSE056\tGopal Pandey\n\t\tBT18CSE079\tVismit Kumbhalkar";
            cout<<"\n\t\tUnder the guidance of our OOPS teacher Mrs.Pooja Jain";
            cout<<"\n\t\tPress any key to exit...";
            getch();
            system("cls");
            exit(0);
            break;
            default:
				if(cin.fail()){
					cout<<"\n\t\t\tERROR!!Character input in integer input field";
					cout<<"\n\t\t\tPress any key";
					getch();
					exit(0);
				}
				else{
					cout<<"\n\t\t\tEnter correct choice.";
					cout<<"\n\t\t\tPress any key to continue";
               		getch();
				}
        }
        system("cls");
    }
}
void acc_holder()                               //menu for account holders 
{
    int acno,ch1;
    account obj;
    while(1)
    {
        system("cls");
        cout<<"\n\t\t\t-------------------------------------------------------------------------";
        cout<<"\n\t\t\t\t\t\tWelcome to IIIT Nagpur Bank";
        cout<<"\n\t\t\t-------------------------------------------------------------------------";
         cout<<"\n\t\t\tAccount holder:";
        cout<<"\n\t\t\tPress\n\t\t\t1: To login\n\t\t\t2: Forgot password\n\t\t\t3: Exit\n\t\t\tEnter your choice:---> ";
        cin>>ch1;
        switch(ch1){
        	case 1:obj.login();
        	break;
        	case 2:char mob[10];
            cout<<"\n\t\t\tEnter account number: ";
            cin>>acno;
            cout<<"\n\t\t\tEnter your registered mobile number: ";
            cin>>mob;
            obj.forgotpass(acno,mob);
            break;
            case 3:return;
            default:
            	if(cin.fail()){
					cout<<"\n\t\t\tERROR!!Character input in integer input field";
					cout<<"\n\t\t\tPress any key";
					getch();
					exit(0);
				}
				else{
					cout<<"\n\t\t\tEnter correct choice.";
					cout<<"\n\t\t\tPress any key to continue";
               		getch();
				}
		}
}
}
void create_acc()                               //creates and stores account
{
    account obj;
    obj.getdata();
    obj.storedata(); 
    return; 
}
void emp()                                      //menu for employees
{
    int empid,ch1;
    employee obj;
    while(1)
    {
        system("cls");
        cout<<"\n\t\t\t-------------------------------------------------------------------------";
        cout<<"\n\t\t\t\t\t\tWelcome to IIIT Nagpur Bank";
        cout<<"\n\t\t\t-------------------------------------------------------------------------";
        cout<<"\n\t\t\tEmployee:";
        cout<<"\n\t\t\tPress\n\t\t\t1: To login\n\t\t\t2: To exit\n\t\t\tEnter your choice:---> ";
        cin>>ch1;
        if(cin.fail()){
        	cout<<"\n\t\t\tERROR!!Character input in integer input field";
        	cout<<"\n\t\t\tPress any key...";
        	getch();
        	exit(0);
		}
        else if(ch1==1)
        {
            obj.login();
        }
        else if(ch1==2)
        {
            break;
        }
		else{
			cout<<"\n\t\t\tEnter correct choice";
			cout<<"\n\t\t\tPress any key to continue";
			getch();
		}       
    }
    return;
}
void new_emp()                                  //creates and stores new employee
{
    employee obj;
    obj.getdata();
    obj.storedata();
    return;
}
int alphabets(char*phno)
{
    int i,flag=0;
    for(i=0;i<10;i++)
    {
        if(phno[i]>=48&&phno[i]<=57)
            flag++;
    }
    if(flag==10)
        return(0);
    else
        return(1);
}
int nonalphabets(char*name)
{
    int i, flag=0;
    for(i=0;i<25;i++)
    {
        if(name[i]<65&&name[i]!=32&&name[i]!=0)
            flag=1;
        else if(name[i]>90&&name[i]<97)
            flag=1;
        else if(name[i]>122)
            flag=1;
        else if(name[i]==0)
            break;
    }
    if(i==0)
        flag=1;
    return(flag);
}
