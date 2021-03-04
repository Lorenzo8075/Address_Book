#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Name{
    private:
        string last_name, first_name;
    public:
        static const string DEFAULT_FIRST_NAME;
        static const string DEFAULT_LAST_NAME;

        bool operator== (const Name & other) const;
        string get_last_name() const;
        void set_last_name(string last_name);
        string get_first_name()const;
        void set_first_name(string first_name);
        
        Name();
        Name(string last_name, string first_name);
        ~Name();

};

const string Name::DEFAULT_LAST_NAME = "last";
const string Name::DEFAULT_FIRST_NAME = "first";

class Contact{ //Abstract Class - node class
    private:
        Contact * next;
    protected:
        Name name;
        string phone; 
        string email; 
        int location;
    public:
        static const string DEFAULT_FIRST_NAME;
        static const string DEFAULT_LAST_NAME;
        static const string DEFAULT_PHONE;
        static const string DEFAULT_EMAIL;
        static const int DEFAULT_LOCATION;
        
        Contact * get_next()const;
        void set_next(Contact *p_contact);
        Name get_name()const;
        void set_name(Name name);
        string get_phone()const;
        void set_phone(string phone);
        string get_email()const;
        void set_email(string email);
        int get_location() const;
        void set_location(int location);

        Contact();
        Contact(string last_name, string first_name, string phone, string email, int location);
        virtual ~Contact();
        virtual void ShowContact() = 0; 

};

const string Contact::DEFAULT_PHONE = "1-000-000-0000";
const string Contact::DEFAULT_EMAIL = "default@email.com";
const int Contact::DEFAULT_LOCATION = 0;

class EmployeeContact:public Contact{ //derived Contact class
    private:
        string title;
        string department;
    public:
        static const string DEFAULT_TITLE;
        static const string DEFAULT_DEPARTMENT;

        EmployeeContact();
        EmployeeContact(string last_name, string first_name, string phone, string email, int location, string title, string department);// non default constructor
        virtual ~EmployeeContact();

        string get_title()const;
        void set_title(string title);
        string get_department() const;
        void set_department(string department);
        virtual void ShowContact();
        

};

const string EmployeeContact::DEFAULT_TITLE = "Employee";
const string EmployeeContact::DEFAULT_DEPARTMENT = "Office";

class ContractorContact:public Contact{ //derived Contact class
    private:
        string company;
        int duration_month;

    public:
        static const string DEFAULT_COMPANY;
        static const int DEFAULT_DURATION_MONTH;
        ContractorContact();
        ContractorContact(string last_name, string first_name, string phone, string email, int location, int duration_month, string company);
        ~ContractorContact();
        string get_company()const;
        void set_company(string company);
        int get_duration_month()const;
        void set_duration_month(int duration_month);
        virtual void ShowContact();

};

const string ContractorContact::DEFAULT_COMPANY = "SpaceX";
const int ContractorContact::DEFAULT_DURATION_MONTH = 1;

class ContactList{ //linked list
    private:
        Contact * head;
        Contact * FindContact(const Name& name);
        void Insert(Contact* p_contact);//insert to the front of the list
    public:
        
        void Init();
        void ShowAllContacts();
        void SearchByName(const Name& name);
        void SearchByDepartment(string department);
       
        ContactList();
        ~ContactList();
        
};

class AddressBook{
    private:
        string company;
        ContactList contact_list;
        void Menu();
        int GetUserOption();
        void ShowAllContacts();
        void SearchByName();
        void SearchByDepartment();
        void Quit();
    public:
        static const string DEFAULT_COMPANY_NAME;
        AddressBook();
        AddressBook(string company);
        ~AddressBook();
        void Init();
        void Run();
        
};

const string AddressBook::DEFAULT_COMPANY_NAME = "Mars Society Organization";

int main(){
    AddressBook* p_address_book = new AddressBook();
    p_address_book->Init();
    p_address_book->Run();
    delete p_address_book;
    return 0;
}

//Name definitions
Name::Name():last_name(Name::DEFAULT_LAST_NAME), first_name(Name::DEFAULT_FIRST_NAME){}
Name::Name(string last_name, string first_name):last_name(last_name), first_name(first_name){}
Name::~Name(){cout << "Name destructed..." << endl;}
string Name::get_last_name()const{return last_name;}
string Name::get_first_name()const{return first_name;}
void Name::set_last_name(string last_name){this->last_name = last_name;}
void Name::set_first_name(string first_name){this->first_name = first_name;}
bool Name::operator== (const Name & other) const {    
    if(this->last_name == other.last_name && this->first_name == other.first_name){
        return true;
    }
    return false;
}

//Contact definitions
Contact* Contact::get_next()const{return next;}
void Contact::set_next(Contact * p_contact){next = p_contact;}
Name Contact::get_name()const{return name;}
void Contact::set_name(Name name){this->name = name;}
string Contact::get_phone()const{return phone;}
void Contact::set_phone(string phone){this->phone = phone;}
string Contact::get_email()const{return email;}
void Contact::set_email(string email){this->email = email;}
int Contact::get_location()const{return location;}
void Contact::set_location(int location){this->location = location;}
Contact::Contact(): next(nullptr), name(Name()), 
phone(Contact::DEFAULT_PHONE), email(Contact::DEFAULT_EMAIL), location(Contact::DEFAULT_LOCATION){}
Contact::Contact(string last_name, string first_name, string phone, string email, int location):
next(nullptr),name(Name(last_name, first_name)),phone(phone), email(email),location(location){} 
Contact::~Contact(){cout << name.get_last_name() << " " << name.get_first_name() << " has gone home..." << endl;}

//EmployeeContact definitions
EmployeeContact::EmployeeContact():Contact(),title(EmployeeContact::DEFAULT_TITLE), department(EmployeeContact::DEFAULT_DEPARTMENT){}
EmployeeContact::EmployeeContact(string last_name, string first_name, string phone, string email, int location, string title, string department):
Contact(last_name, first_name, phone, email, location), title(title), department(department){}
EmployeeContact::~EmployeeContact(){}//no-op as described in the assignment
string EmployeeContact::get_title()const{return title;}
void EmployeeContact::set_title(string title){this->title = title;}
string EmployeeContact::get_department()const{return department;}
void EmployeeContact::set_department(string department){this->department = department;}
void EmployeeContact::ShowContact(){
    cout << setw(10) << name.get_last_name() << setw(15) << name.get_first_name() << setw(17) << title << setw(15) <<
    department << setw(10) << "Room " << location << setw(20) << phone << setw(20) << email << endl;
}

//ContractContact definitions

ContractorContact::ContractorContact():Contact(), company(ContractorContact::DEFAULT_COMPANY), duration_month(ContractorContact::DEFAULT_DURATION_MONTH){}
ContractorContact::ContractorContact(string last_name, string first_name, string phone, string email, int location, int duration_month, string company):
Contact(last_name,first_name, phone, email, location),company(company), duration_month(duration_month){}
ContractorContact::~ContractorContact(){}//no-op as described in the assignment
string ContractorContact::get_company()const{return company;}
void ContractorContact::set_company(string company
){this->company = company;}
int ContractorContact::get_duration_month()const{return duration_month;}
void ContractorContact::set_duration_month(int duration_month){this->duration_month = duration_month;}
void ContractorContact::ShowContact(){
    cout << setw(10) << name.get_last_name() << fixed << setw(15) << name.get_first_name() << setw(10) << duration_month << " months (contractor)" << setw(15) <<company
    << setw(10) << "Room " <<location << setw(20) << phone << setw(20) << email << endl; 
}

ContactList::ContactList():head(nullptr){}
ContactList::~ContactList(){
    Contact * curr_node = head;
    Contact * next_node = nullptr;

    while(curr_node != nullptr){
        next_node = curr_node->get_next(); //save link to the next node
        delete curr_node; //delete curr_node safely
        curr_node = next_node;  
    } 
}//delete nodes to avoid memory leak...cout statement was not mentioned in the assignment

Contact* ContactList::FindContact(const Name& name){ //traversing a linked list
    Contact* p_contact = head;

    while(p_contact != nullptr){
        string lower_case_first_name;
        string lower_case_last_name;;
        Name name_copy;
        name_copy = p_contact->get_name();
        
        lower_case_first_name = name_copy.get_first_name();
        for(int i = 0; i < lower_case_first_name.length(); i++){
        lower_case_first_name[i] = tolower(lower_case_first_name[i]);
        }

        lower_case_last_name = name_copy.get_last_name();
        for(int i = 0; i < lower_case_last_name.length(); i++){
        lower_case_last_name[i] = tolower(lower_case_last_name[i]);
        }

        name_copy.set_last_name(lower_case_last_name);
        name_copy.set_first_name(lower_case_first_name); 

        if(name == name_copy){
            return p_contact;
        }
        p_contact = p_contact->get_next();//move to the next node
    }
    return nullptr;
}

void ContactList::Insert(Contact* p_contact){ 
    if(head == nullptr){ //since head is initialized to nullptr, I'll assign head pointing to the next/first node
        head = p_contact; //head is pointing to the next node
    }
    else{ //if the node is not null
        p_contact->set_next(head);
        head = p_contact; //put node in front of the linked list
    }     
} 

void ContactList::Init() {
    Insert(new EmployeeContact("Summer", "David", "1-408-790-1682", "davids@comm", 1,  "Analyst",  "Research"));
    Insert(new EmployeeContact("Hans", "Jenn", "1-408-790-2381", "jenniferh@comm",  2,  "Analyst",  "Sales"));
    Insert(new EmployeeContact("Lee", "Bruce", "1-789-790-2381", "brucelee@comm",  3,  "Director",  "Management"));
    Insert(new EmployeeContact("Berl", "Silvio", "1-393-790-4784", "buonsilvio@comm",  4,  "President",  "Management"));
    Insert(new EmployeeContact("Stein", "Anne", "1-326-145-6352", "anne@comm",  5,  "Chairman",  "Management"));
    Insert(new EmployeeContact("Kim", "Anne", "1-960-740-2380", "hana@comm",  6,  "Accountant",  "Finance"));
    Insert(new EmployeeContact("Auth", "Emily", "1-360-710-2341", "emily@comm",  7,  "Analyst",  "Sales"));
    Insert(new EmployeeContact("Morato", "Emily", "1-740-790-3541", "steven@tcomm",  8,  "Salesman",  "Sales"));
    Insert(new ContractorContact("Pichai", "Sundar", "1-408-874-6354", "sundar@google",  1,  24, "Google"));
    Insert(new ContractorContact("Musk", "Elon", "1-420-696-4242", "elon@tesla",  2,  42, "Tesla"));
    Insert(new ContractorContact("Zuck", "Mark", "1-258-369-1473", "mark@facebook",  3,  36, "Facebook"));
    Insert(new ContractorContact("Naka", "Satoshi", "1-520-654-9874", "satoshi@bitcoin",  1,  48, "Bitcoin"));
    Insert(new ContractorContact("Bezos", "Jeff", "1-951-753-8745", "jeff@amazon",  4,  47, "Amazon"));
    Insert(new ContractorContact("Parker", "Peter", "1-741-258-9632", "pp@nyc",  5,  32, "NY City"));
    Insert(new ContractorContact("Alba", "Jessica", "1-360-626-6054", "jessica@alba",  6,  16, "Universal"));
    Insert(new ContractorContact("Bieber", "Justin", "1-408-874-6354", "justin@bieber",  7,  8, "Studios"));
    }


void ContactList::ShowAllContacts(){
    Contact* p_contact = head;

    while(p_contact != nullptr){
        p_contact->ShowContact();
        p_contact = p_contact->get_next();// move to the next node
    }
}

void ContactList::SearchByName(const Name &name){
    Contact* p_contact = FindContact(name);
    EmployeeContact* p_employee_contact = dynamic_cast<EmployeeContact*>(p_contact);
    ContractorContact* p_contractor_contract = dynamic_cast<ContractorContact*>(p_contact);

    if(p_contact!= nullptr){
        if(p_employee_contact != nullptr){
            p_employee_contact->ShowContact();
        }
        else if(p_contractor_contract != nullptr){
            p_contractor_contract->ShowContact();
        }
    }
    else{
            cout << "Error message! " << endl;
    }
}     

void ContactList::SearchByDepartment(string department){
    Contact* p_contact = head;
    EmployeeContact* p_e_contact = nullptr;
    bool department_found = false;
    int count =0;
    
    while(p_contact != nullptr){
        p_e_contact = dynamic_cast<EmployeeContact*>(p_contact);

        if(p_e_contact != nullptr){
            if(department == p_e_contact->get_department()){
                p_e_contact->ShowContact();
                department_found = true;
            }
        }
        p_contact = p_contact->get_next();
    }
    if(!department_found){
        cout << "Error, department not found" << endl;
    }
}

AddressBook::AddressBook():contact_list(ContactList()), company(AddressBook::DEFAULT_COMPANY_NAME){}
AddressBook::AddressBook(string company):contact_list(ContactList()), company(company){}
AddressBook::~AddressBook(){}//no-op as described in the assignment

void AddressBook::Menu(){
    cout << "\n\t" << DEFAULT_COMPANY_NAME << endl << endl;                
    cout << "1. View all contacts\n\n";
    cout << "2. Search by name\n\n";
    cout << "3. Search by department\n\n";
    cout << "4. Quit\n\n"; 
}

int AddressBook::GetUserOption(){
    int user_option;
    cout << "Select an option (1-4): ";
    cin >> user_option;
    return user_option;
}    

void AddressBook::ShowAllContacts(){
    contact_list.ShowAllContacts();
}

void AddressBook::Quit(){
    cout << "Thanks for using our AddressBook. See you again!\n";
}
void AddressBook::Init(){
    contact_list.Init();
}

void AddressBook::SearchByName(){
    string last_name, first_name;
    cout << "Enter first name: " << endl;
    cin >> first_name;
    cout << "Enter last name: " << endl;
    cin >> last_name;

    string lower_case_first_name;
    string lower_case_last_name;
    Name name;

    lower_case_first_name = first_name;
    for(int i = 0; i < lower_case_first_name.length(); i++){
        lower_case_first_name[i] = tolower(lower_case_first_name[i]);
    }

    lower_case_last_name = last_name;
    for(int i = 0; i < lower_case_last_name.length(); i++){
        lower_case_last_name[i] = tolower(lower_case_last_name[i]);
    }

    name.set_last_name(lower_case_last_name);
    name.set_first_name(lower_case_first_name); 

    contact_list.SearchByName(name);
}

void AddressBook::SearchByDepartment(){
    string department;

    cout << "Enter a department: " << endl;
    cin >> department;
    contact_list.SearchByDepartment(department);
}

void AddressBook::Run(){
    int selected_user_option;

    do{
        Menu();
        selected_user_option = GetUserOption();
            switch(selected_user_option){
                case 1:
                    ShowAllContacts();
                    break;
                case 2:
                    SearchByName();
                    break;
                case 3:
                    SearchByDepartment();
                    break;
                case 4:
                    Quit();
                    break;    

            }
    }
    while(selected_user_option != 4);
}
