#include<iostream>
#include<fstream>
using namespace std;

class shopping{
    private:
        string pname;
        int choice;
        int pcode;
        double price;
        double discount;
    public :
        int add(){
            fstream data;
            int c;
            string n;
            double p, dp;
            int flag = 0;
            cout<<"\nEnter the name of the product : ";
            cin>>pname;
            cout<<"Enter the product code of the item : ";
            cin>>pcode;
            cout<<"Enter the price of the product : ";
            cin>>price;
            cout<<"Enter the discount on the product : ";
            cin>>discount;
            data.open("database.txt",ios::in);
            if(!data){
                data.open("database.txt",ios::app|ios::out);
                data<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
                data.close();
            }
            else{
                data>>c>>n>>p>>dp;
                while(data.eof()){
                    if(c == pcode) flag++;
                    data>>c>>n>>p>>dp;
                }
                data.close();
                if(flag > 0){
                    cout<<"\nInvalid product code! A product already exists with this code.\n";
                    return -99;
                }
                else{
                    data.open("database.txt",ios::app|ios::out);
                    data<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
                    data.close();
                }
            }
            cout<<"\n\n\t\t\t__________Record Inserted!__________\n";
            return 1;
        }
        void edit(){
            fstream data,data1;
            int c,c1,token = 0;
            double p,dp;
            string n;
            cout<<"Enter the product code for modifications : ";
            cin>>c1;
            data.open("database.txt",ios::in);
            if(!data){
                cout<<"\nFile does not exists!\n";
            }
            else{
                data1.open("database1.txt",ios::app|ios::out);
                data>>pcode>>pname>>price>>discount;
                while(data.eof()){
                    if(c == c1){
                        cout<<"\nEnter the new product code : ";
                        cin>>c;
                        cout<<"\nEnter the new name of the product : ";
                        cin>>n;
                        cout<<"\nEnter the new price of the product : ";
                        cin>>p;
                        cout<<"\nEnter the new discount on the product : ";
                        cin>>dp;
                        data1<<c<<" "<<n<<" "<<p<<" "<<dp<<"\n";
                        cout<<"\n\n\t\t________Record Edited!________";
                        token++;
                    }
                    else{
                        data1<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
                    }
                    data>>pcode>>pname>>price>>discount;
                }
                data.close();
                data1.close();
                remove("database.txt");
                rename("database1.txt","database.txt");
                if(token == 0){
                    cout<<"\nRecord not found!\n";
                }
            }
        }
        void delete(){
            
        }
        void administrator(){
            while(true){
                cout<<"\n\t\t\t\t_______________________________________________\n";
                cout<<"\t\t\t\t                                               \n";
                cout<<"\t\t\t\t             Administrator Menu                \n";
                cout<<"\t\t\t\t                                               \n";
                cout<<"\t\t\t\t_______________________________________________\n";
                cout<<"1. Add an item\n";
                cout<<"2. Delete an Item\n";
                cout<<"3. Modify an Item\n";
                cout<<"4. Back to main menu\n";
                cout<<"Your choice : ";
                cin>>choice;
                switch(choice){
                    case 1 : int a = add();
                             if(a<0)
                                administrator();
                            break;
                    case 2 : delete();
                            break;
                    case 3 : edit();
                            break;
                    case 4 : menu();
                            break;
                    default : cout<<"Please enter a valid choice!\n";
                }
            }
        } 
        void customer(){
            cout<<"\n\t\t\t\t_______________________________________________\n";
            cout<<"\t\t\t\t                                               \n";
            cout<<"\t\t\t\t             Customer Menu                     \n";
            cout<<"\t\t\t\t                                               \n";
            cout<<"\t\t\t\t_______________________________________________\n";
            cout<<"1. Buy Product\n";
            cout<<"2. Go Back\n";
            cout<<"Your choice : ";
            cin>>choice;
            switch(choice){
                case 1 : reciept();
                         break;
                case 2 : menu();
                         break;
                default : cout<<"Enter a valid choice!";
            }
        }
        void menu(){
            while(1){
                string username, password;
                cout<<"\n\t\t\t\t_______________________________________________\n";
                cout<<"\t\t\t\t                                               \n";
                cout<<"\t\t\t\t             Shopping Site                     \n";
                cout<<"\t\t\t\t                                               \n";
                cout<<"\t\t\t\t_______________________________________________\n";
                cout<<"1. Login as Aministrator ";
                cout<<"2. Login as Customer ";
                cout<<"3. Exit ";
                cout<<"Your choice : ";
                cin>>choice;
                switch(choice){
                    case 1 : cout<<"Enter the username :\n";
                            cin>>username;
                            cout<<"Enter the password :\n";
                            cin>>password;
                            if (username == "administrator123" && password == "pass123"){
                                cout<<"\t\t\t\t_______Successfull Login!________\n";
                                administrator();
                            }
                            else
                                cout<<"Invalid credentials!";
                            break;
                    case 2 : cout<<"Enter the username :\n";
                            cin>>username;
                            cout<<"Enter the password :\n";
                            cin>>password;
                            customer();
                            break;
                    case 3 : exit(0);
                    default : cout<<"Enter a valid input!";
                }
            }
        }
};
