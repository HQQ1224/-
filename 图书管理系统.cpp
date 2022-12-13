#include<iostream>
#include<string>
#include<cstdlib>
#define FILENAME "userfile.txt"
#define FILENAME1 "bookfile.txt"
#include<fstream>
using namespace std;
#define User_MAX 1000
#define Book_MAX 100000
//系统的图书总数和用户总数受系统设置最大量的限制

//问题描述： 设计并实现一个图书管理系统。能模拟图书管理系统的部分功能，包括读者注册，读者借阅，图书管理，用户管理等。
//功能说明：
// (1） 模拟图书管理系统的流程 包括读者注册、读者借阅、图书管理、用户管理等功能。
//（2） 进行统计分析 随时进行统计分析，以便了解当前的借阅情况和相关的资料状态，统计分析包含：借阅排行榜，资料状态统计和到期未还图书的统计等。
//（4） 借阅图书数目受系统设置最大借阅量的限制



// 图书类
//图书信息包含：书号，书名，作者，出版社，出版时间，价格等。
class Book
{
public:
    friend class System;
    //构造函数
    Book() 
    {
        Is_lend = 0;
    }
    Book(int n, string a, string au, string p, string t, double pr,int i) :num(n), name(a), author(au), press(p), time(t), price(pr),Is_lend(i) {};
    void display();
private:
    int num;//书号
    string name;//书名
    string author;//作者
    string press;//出版社
    string time;//出版时间
    double price;//价格
    int Is_lend;//是否被借出的标志
};

void Book::display()
{
    cout << "图书书号：" << num << "\t书名：" << name << "\t作者：" << author <<"\t出版社：" <<press<<"\t出版时间："<<time<<"\t价格："<<price<<"\t是否被借出："<<Is_lend << endl;
}

//用户类
class User
{
public:
    friend class System;
    //构造函数 默认用户为读者类型
    User() { identity = 1;  }; 
    User(int a,string n, string k,int i) :account(a),name(n), key(k),identity(i){};
    virtual void display()=0;//显示用户的信息
protected:
    int account;//用户账号
    string name;//用户姓名
    string key;//用户密码
    int identity;//判断用户类型 1为读者 0为管理员
};

class Reader :public User
{
public:
    friend class System;
    //构造函数 
    Reader(){ identity = 1; }
    Reader(int a,string n, string k,int i) :User(a,n, k,i){};
    void display();//显示读者的信息
};

void Reader::display()
{
    cout <<"用户账号："<<account << "\t用户姓名：" << name << "\t密码：" << key << endl;
}

class Librarian :public User
{
public:
    friend class System;
    //构造函数 
    Librarian() { identity = 0; key = 123456; }//设置管理员初始密码
    Librarian(int a, string n, string k, int i) :User(a, n, k, i) {};
    void display();//显示管理员的信息
};

void Librarian::display()
{
    cout << "用户账号：" << account << "\t用户姓名：" << name << "\t密码：" << key  << endl;
}

class System
{
public:
    System();//构造函数
    void change_key(User &user);//修改用户密码
    void User_register();//用户注册
    void Reader_Sign(Reader& user);//读者登录
    int Librarian_Sign(Librarian& user);//管理员登录
    void Book_borrow();//图书借阅
    void Book_lend();//图书归还
    void Add_Book();//添加图书
    int Search_Book();//查找图书 并且返回书号
    void Del_Book();//删除图书
    void Search_User();//查找用户
    void Del_User();//删除用户
    void Alter_User();//修改用户权限
    void Exit_system();//退出系统
    void save_user();//保存文件
    void save_book();
    int get_user_num();//统计人数
    int get_book_num();//统计图书数量
    void init_user();//初始化账户
    void init_book();//初始化图书
    int IsExist(int account);//判断用户是否存在
    int IsExist_book(int num);//判断图书是否存在
    ~System();//析构函数
private:
    int User_num;//用户总数
    User** User_Array;//定义二级指针，将每个账户所存放信息的地址依次存入数组，再通过二级指针依次访问其中的信息
    int Book_num;//图书总数
    Book** Book_Array;//定义二级指针，将每本书所存放信息的地址依次存入数组，再通过二级指针依次访问其中的信息
    bool File_userIsEmpty;//标志文件是否为空
    bool File_bookIsEmpty;//标志文件是否为空
};

void System::Add_Book()
{
    //每次只能存入一本书
    int newSize = this->Book_num + 1;//计算新空间大小
    if (newSize >= Book_MAX)
    {
        cout << "图书库存数量已满，无法继续添加图书，请清理库存后再次尝试！" << endl;
    }
    else
    {
        Book** newSpace = new Book * [newSize];//开辟新空间
        //将原空间下内容存放到新空间下
        if (this->Book_Array != NULL)
        {
            for (int i = 0; i < this->Book_num; i++)
            {
                newSpace[i] = this->Book_Array[i];
            }
        }
        //临时变量用于接收图书信息
        int num;//书号
        string name;//书名
        string author;//作者
        string press;//出版社
        string time;//出版时间
        double price;//价格
        cout << "请输入书号：";  cin >> num;
        cout << "请输入书名："; cin >> name;
        cout << "请输入作者："; cin >> author;
        cout << "请输入出版社："; cin >> press;
        cout << "请输入出版时间："; cin >> time;
        cout << "请输入价格："; cin >> price;
        //利用构造函数创建图书
        Book *str = new Book(num,name,author,press,time,price,0);
        //将图书地址存入数组中并且更新系统中的图书数量
        newSpace[this->Book_num] = str;
        //释放原有空间
        delete[] this->Book_Array;
        //更改新空间的指向
        this->Book_Array = newSpace;
        //更新新的用户个数
        this->Book_num = newSize;
        //更新文件不为空标志
        this->File_bookIsEmpty = false;
        cout << "图书添加成功！"<<endl;
        //将图书信息存入文件中
        this->save_book();
        //按任意键后清屏回到上级目录
        system("pause");
        system("cls");
    }
}


void System::Exit_system()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

//注册账户
void System::User_register()
{
    //每次注册只能开一个
    int newSize = this->User_num + 1;//计算新空间大小
    if (newSize >= User_MAX)
    {
        cout << "系统用户数量已满，无法继续注册，请联系管理员！" << endl;
    }
    else
    {
        User** newSpace = new User * [newSize];//开辟新空间
        //将原空间下内容存放到新空间下
        if (this->User_Array != NULL)
        {
            for (int i = 0; i < this->User_num; i++)
            {
                newSpace[i] = this->User_Array[i];
            }
        }
        //临时变量用于接收用户信息
        string n;//用户姓名 
        string k;//用户密码
        int i;//用户类型
        cout << "请输入您的姓名以便进行注册：";  cin >> n;
        cout << "请设置您的密码："; cin >> k;
        cout << "请输入您要注册身份：0、管理员 1、读者"; cin >> i;
        //利用构造函数创建用户并赋值
        User* str;
        if (i == 0)
        {
            str = new Librarian(this->User_num, n, k,i);
        }
        else
        {
            str = new Reader(this->User_num, n, k,i);
        }
        //将账户地址存入数组中并且更新系统中的用户人数
        newSpace[this->User_num] = str;
        //释放原有空间
        delete[] this->User_Array;
        //更改新空间的指向
        this->User_Array = newSpace;
        //更新新的用户个数
        this->User_num = newSize;
        //更新文件不为空标志
        this->File_userIsEmpty = false;
        cout << "开通账户成功，您的账户为：" << str->account << endl;
        //将用户信息存入文件中
        this->save_user();
        //按任意键后清屏回到上级目录
        system("pause");
        system("cls");
    }
}

System::System()
{
    ifstream ifs,ifs1;
    ifs.open(FILENAME, ios::in);
    ifs1.open(FILENAME1, ios::in);
    //文件不存在情况
    if (!ifs.is_open()&& !ifs1.is_open())
    {
        cout << "用户文件不存在" << endl;//测试输出
        this->User_num = 0;//初始化人数
        this->User_Array = NULL;//初始化数组指针
        this->File_userIsEmpty = true;//初始化文件为空标志
        ifs.close();//关闭文件
        cout << "图书文件不存在" << endl;//测试输出
        this->Book_num = 0;//初始化人数
        this->Book_Array = NULL;//初始化数组指针
        this->File_bookIsEmpty = true;//初始化文件为空标志
        ifs1.close();//关闭文件
        return;
    }
    else 
    {
        //文件存在并且没有记录
        //定义一个字符数据类型ch将文件末尾的字符读出再用eof进行判断
        //文件为空时文件末尾会有一个字符
        char ch;
        ifs >> ch;
        if (ifs.eof())//eof为判断文件是否为空函数
        {
            cout << "用户文件为空！" << endl;
            this->User_num = 0;
            this->User_Array = NULL;
            this->File_userIsEmpty = true;
            ifs.close();
        }
        ifs1 >> ch;
        if (ifs1.eof())//eof为判断文件是否为空函数
        {
            cout << "图书文件为空！" << endl;
            this->Book_num = 0;
            this->Book_Array = NULL;
            this->File_bookIsEmpty = true;
            ifs1.close();
        }
        //用户文件存在并记录数据
        int num = this->get_user_num();
        this->User_num = num;
        cout << "用户数量为：" << num << endl;
        //开辟空间
        this->User_Array = new User * [this->User_num];
        this->init_user();
        //图书文件存在并记录数据
        int num1 = this->get_book_num();
        this->Book_num = num1;
        cout << "图书数量为：" << num1 << endl;

        //开辟空间
        this->Book_Array = new Book * [this->Book_num];
        this->init_book();
        //将文件中的数据存到数组中
    }
}

int System::IsExist(int account)
{
    int index = 0;
    for (int i = 0; i < this->User_num; i++)
    {
        if (this->User_Array[i]->account == account)
        {
            index = i;
            break;
        }
    }
    return index;
}

int System::IsExist_book(int num)
{
    int index = -1;
    for (int i = 0; i < this->Book_num; i++)
    {
        if (this->Book_Array[i]->num == num)
        {
            index = i;
            break;
        }
    }
    return index;
}

//读者登录
void System::Reader_Sign(Reader &user)
{
    if (this->File_userIsEmpty)
    {
        cout << "文件不存在！" << endl;
    }
    //用于接受用户输入信息，另一个用于接收文件中找到的信息
    int account;
    string key;
    cout << "请输入您的账号与密码以登录账号：" << endl;
    cin >> account >> key;
    user.account = account;//将账号传给user，接着用user.password接收文件中存放对应账号的密码
    //在文件中查找对应账户，如果不存在则提醒用户注册账户
    //核对账户密码是否与用户输入的相同，相同输出用户信息，不相同提醒用户重试
    int i = IsExist(user.account);
    user.account= this->User_Array[i]->account;
    user.name = this->User_Array[i]->name;
    user.key = this->User_Array[i]->key;
    if (key == user.key)
    {
        cout << "登陆成功，用户信息为："; user.display();//显示用户登录信息
    }
    else
    {
        cout << "密码错误，请重试" << endl;
    }
    system("pause");
    system("cls");
}

void System::Book_borrow()//图书借阅
{
    int i=Search_Book();//查找所要借阅的图书
    char ch;
    cout << "是否借阅您所查找的图书? y/n" << endl;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        this->Book_Array[i]->Is_lend = 1;//更新书籍借出标志
        this->save_book();//更新文件中数据
        cout << "借阅成功！记得按时归还并且好好爱护书籍！" << endl;
    }
    else
    {
        cout << "有其他书籍供您借阅，可以多看看！" << endl;
    }
    system("pause");
    system("cls");
}

void System::Book_lend()//归还图书
{
    cout << "请输入您要归还的图书书号：" << endl;
    int num; char ch;
    cin >> num;
    cout << "请问您确认归还本书吗？ y/n"<<endl;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        this->Book_Array[num]->Is_lend = 0;//更新书籍借出标志
        this->save_book();//更新文件中数据
        cout << "感谢您的借阅！希望有给您带来良好的体验！欢迎下次借阅！" << endl;
    }
    else
    {
        cout << "您可以继续阅读，但请注意归还时间" << endl;
    }
    system("pause");
    system("cls");
}

int System::Search_Book()
{
    if (this->File_bookIsEmpty)
    {
        cout << "库内无图书！" << endl;
        return -1;
    }
    //书号
    int num=0;
    cout << "请输入您所要查找的图书的书号：" << endl;
    cin >> num;
    int i = IsExist_book(num);//判断图书是否存在
    if (i != -1)
    {
        cout << "您所查找的图书信息如下：" << endl;
        cout << "图书书号：" << this->Book_Array[i]->num << "\t书名：" << this->Book_Array[i]->name << "\t作者：" << this->Book_Array[i]->author
            << "\t出版社：" << this->Book_Array[i]->press << "\t出版时间：" << this->Book_Array[i]->time << "\t价格：" << this->Book_Array[i]->price
            << "\t是否被借出：" << this->Book_Array[i]->Is_lend << endl;
    }
    else
    {
        cout << "不好意思，库内无此图书" << endl;
    }
    return i;
}

void System::Search_User()
{
    if (this->File_userIsEmpty)
    {
        cout << "无用户存在！" << endl;
    }
    //用户账号
    int account;
    cout << "请输入您所要查找的用户的账号：" << endl;
    cin >> account;
    int i = IsExist(account);
    if (i != -1)
    {
        cout << "您所查找的用户信息如下：" << endl;
        cout << "用户账户为：" << this->User_Array[i]->account << "用户姓名：" << this->User_Array[i]->name
            << "\t密码：" << this->User_Array[i]->key << "\t身份：" << this->User_Array[i]->identity << endl;
    }
    else
    {
        cout << "不好意思，系统内无此用户" << endl;
    }
}

void System::Alter_User()//修改用户权限
{
    //用户账号
    int account;
    cout << "请输入您所要修改权限的用户的账号：" << endl;
    cin >> account;
    int i = IsExist(account);//获取用户信息
    cout << "该用户的身份为：" << this->User_Array[i]->identity << endl;;
    cout << "请输入您要将其身份修改成什么? 0——管理员 1——读者" << endl;
    int iden;
    cin >> iden;
    this->User_Array[i]->identity = iden;//更新数组中的身份
    //数据同步更新到文件中
    this->save_user();
    cout << "更改权限成功" << endl;
    system("pause");
    system("cls");
}

void System::Del_Book()
{
    //数组中删除数据，本质就是数据前移
    if (this->File_bookIsEmpty)
    {
        cout << "库内无图书可删除！" << endl;
    }
    else
    {
        //按照图书书号进行删除
        cout << "请输入想要删除的图书的书号：" << endl;
        int num = 0;
        cin >> num;
        int index = this->IsExist_book(num);
        if (index != -1)//说明图书存在
        {
            //数据前移
            for (int i = index; i < this->Book_num - 1; i++)
            {
                this->Book_Array[i] = this->Book_Array[i + 1];
            }
            this->Book_num--;//更新数组中记录的账户数据
            //数据同步更新到文件中
            this->save_book();
            cout << "删除成功！" << endl;
        }
        else
        {
            cout << "删除失败，未找到图书信息" << endl;
        }
    }
    system("pause");
    system("cls");
}

//管理员登录
int System::Librarian_Sign(Librarian& user)
{
    if (this->File_userIsEmpty)
    {
        cout << "文件不存在！" << endl;
    }
    //用于接受用户输入信息，另一个用于接收文件中找到的信息
    int account;
    string key;
    cout << "请输入您的账号与密码以登录账号：" << endl;
    cin >> account >> key;
    user.account = account;//将账号传给user，接着用user.key接收文件中存放对应账号的密码
    //在文件中查找对应账户，如果不存在则提醒用户注册账户
    //核对账户密码是否与用户输入的相同，相同输出用户信息，不相同提醒用户重试
    int i = IsExist(user.account);
    user.account = this->User_Array[i]->account;
    user.name = this->User_Array[i]->name;
    user.key = this->User_Array[i]->key;
    user.identity = this->User_Array[i]->identity;
    if (key == user.key&&(user.identity==0))
    {
        cout << "登陆成功，用户信息为："; user.display();//显示用户登录信息
        system("pause");
        system("cls");
        return 1;
    }
    else
    {
        cout << "密码错误/您不是管理员！请重试" << endl;
        system("pause");
        system("cls");
        return 0;
       
    }
}

//修改密码
void System::change_key(User& user)
{
    string old_key, new_key;
    cout << "请输入您原本的密码：" << endl;
    cin >> old_key;
    if (old_key == user.key)
    {
        cout << "请输入您想要设置的新的密码：" << endl;
        cin >> new_key;
        user.key = new_key;
        cout << "您的密码修改成功" << endl;
    }
    else
    {
        cout << "密码错误，请重新输入" << endl;
    }
    this->User_Array[user.account]->key = user.key;//更新数组中的密码
    //数据同步更新到文件中
    this->save_user();
    system("pause");
    system("cls");
}

void System::Del_User()
{
    //数组中删除数据，本质就是数据前移
    if (this->File_userIsEmpty)
    {
        cout << "文件不存在！" << endl;
    }
    else
    {
        //按照用户账号进行删除
        cout << "请输入想要删除的账号：" << endl;
        int account = 0;
        cin >> account;
        int index = this->IsExist(account);
        if (index != -1)//说明账户存在
        {
            //数据前移
            for (int i = index; i < this->User_num - 1; i++)
            {
                this->User_Array[i] = this->User_Array[i + 1];
            }
            this->User_num--;//更新数组中记录的账户数据
            //数据同步更新到文件中
            this->save_user();
            cout << "删除成功！" << endl;
        }
        else
        {
            cout << "删除失败，未找到账户信息" << endl;
        }
    }
    system("pause");
    system("cls");
}

//保存文件
void System::save_user()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->User_num; i++)
    {
        ofs <<this->User_Array[i]->account<<" " << this->User_Array[i]->name << " " << this->User_Array[i]->key << " "
            << this->User_Array[i]->identity << endl;
    }
    ofs.close();
}

//保存文件
void System::save_book()
{
    ofstream ofs;
    ofs.open(FILENAME1, ios::out);
    for (int i = 0; i < this->Book_num; i++)
    {
        ofs << this->Book_Array[i]->num << " " << this->Book_Array[i]->name << " " << this->Book_Array[i]->author << " "
            << this->Book_Array[i]->press<<" "<< this->Book_Array[i]->time<<" "<< this->Book_Array[i]->price<<" "<< this->Book_Array[i]->Is_lend << endl;
    }
    ofs.close();
}

int System::get_user_num()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int g_account;
    string g_name;
    string g_key;
    int g_identity;
    int num = 0;
    while (ifs >> g_account&&ifs>>g_name && ifs >> g_key && ifs >> g_identity)
    {
        //记录人数
        num++;
    }
    ifs.close();
    return num;
}

int System::get_book_num()
{
    ifstream ifs;
    ifs.open(FILENAME1, ios::in);
    int g_num;
    string g_name;
    string g_author;
    string g_press;
    string g_time;
    double g_price;
    int g_is_lend;
    int num = 0;
    while (ifs >> g_num && ifs >> g_name && ifs >> g_author && ifs >> g_press && ifs>>g_time && ifs>>g_price && ifs>>g_is_lend)
    {
        //记录图书数量
        num++;
    }
    ifs.close();
    return num;
}

void System::init_user()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int g_account;
    string g_name;
    string g_key;
    int g_identity;
    int index = 0;//下标索引
    while (ifs >> g_account &&ifs >> g_name && ifs >> g_key && ifs >> g_identity)
    {
        User* user;
        if (g_identity == 0)
        {
            user = new Librarian(g_account,g_name, g_key,g_identity);
        }
        else
        {
            user = new Reader(g_account, g_name, g_key,g_identity);
        }
        this->User_Array[index] = user;
        index++;
    }
    ifs.close();
}

void System::init_book()
{
    ifstream ifs;
    ifs.open(FILENAME1, ios::in);
    int g_num;
    string g_name;
    string g_author;
    string g_press;
    string g_time;
    double g_price;
    int g_is_lend;
    int index = 0;
    while (ifs >> g_num && ifs >> g_name && ifs >> g_author && ifs >> g_press && ifs >> g_time && ifs >> g_price && ifs >> g_is_lend)
    {
        Book* book = new Book(g_num, g_name, g_author, g_press, g_time, g_price,g_is_lend);
        this->Book_Array[index] = book;
        index++;
    }
    ifs.close();

}


System::~System()
{
    if (this->User_Array != NULL)
    {
        delete[] this->User_Array;
        this->User_Array = NULL;
    }
    if (this->Book_Array != NULL)
    {
        delete[] this->Book_Array;
        this->Book_Array = NULL;
    }
}

//读者注册、读者借阅、图书管理、用户管理
void menu1()
{
    cout << "**************" << endl;
    cout << "1、用户注册" << endl;
    cout << "2、读者登录" << endl;
    cout << "3、管理员登录" << endl;
    cout << "4、退出系统" << endl;
    cout << "**************" << endl;
}
void menu2()
{
    cout << "**************" << endl;
    cout << "1、图书借阅" << endl;
    cout << "2、图书归还" << endl;
    cout << "3、修改密码" << endl;
    cout << "4、退出系统" << endl;
    cout << "**************" << endl;
}
void menu3()
{
    cout << "**************" << endl;
    cout << "1、图书管理" << endl;
    cout << "2、用户管理" << endl;
    cout << "3、修改密码" << endl;
    cout << "4、退出系统" << endl;
    cout << "**************" << endl;
}

void menu4()
{
    cout << "**************" << endl;
    cout << "1、查找图书" << endl;
    cout << "2、删除图书" << endl;
    cout << "3、添加图书" << endl;
    cout << "4、退出系统" << endl;
    cout << "**************" << endl;
}

void menu5()
{
    cout << "**************" << endl;
    cout << "1、查找用户" << endl;
    cout << "2、删除用户" << endl;
    cout << "3、修改用户权限" << endl;
    cout << "4、退出系统" << endl;
    cout << "**************" << endl;
}

int main()
{
    System s;
    int select;//选择
    while (1)
    {
        menu1();
        cout << "请输入您的选择:" << endl;
        cin >> select;
        switch (select)
        {
        case 1://用户注册
        {
            s.User_register();
            break;
        }
        case 2://读者登录
        {
            Reader user;//定义读者类
            s.Reader_Sign(user);
            int choosen = 0;
            while (true)
            {
                cout << "请输入接下来的操作：" << endl;
                menu2();
                cin >> choosen;
                switch (choosen)
                {
                case 1://图书借阅
                {
                    s.Book_borrow();
                    break;
                }
                case 2://图书归还
                {
                    s.Book_lend();
                    break;
                }
                case 3://修改密码
                {
                    s.change_key(user);
                    break;
                }
                case 4://退出系统
                {
                    s.Exit_system();
                    break;
                }
                }
                break;
            }
            break;
        }
        case 3://管理员登录
        {
            Librarian user;
            while (s.Librarian_Sign(user))
            {
                int choosen = 0;
                while (true)
                {
                    cout << "请输入接下来的操作：" << endl;
                    menu3();
                    cin >> choosen;
                    switch (choosen)
                    {
                    case 1://图书管理
                    {
                        int choosen1 = 0;
                        while (true)
                        {
                            cout << "请输入接下来的操作：" << endl;
                            menu4();
                            cin >> choosen1;
                            switch (choosen1)
                            {
                            case 1://查找图书
                            {
                                s.Search_Book();
                                break;
                            }
                            case 2://删除图书
                            {
                                s.Del_Book();
                                break;
                            }
                            case 3://添加图书
                            {
                                s.Add_Book();
                                break;
                            }
                            case 4:
                            {
                                s.Exit_system();
                                break;
                            }
                            }
                        }
                        break;
                    }
                    case 2://用户管理
                    {
                        int choosen2 = 0;
                        while (true)
                        {
                            cout << "请输入接下来的操作：" << endl;
                            menu5();
                            cin >> choosen2;
                            switch (choosen2)
                            {
                            case 1://查找用户
                            {
                                s.Search_User();
                                break;
                            }
                            case 2://删除用户
                            {
                                s.Del_User();
                                break;
                            }
                            case 3://修改用户权限
                            {
                                s.Alter_User();
                                break;
                            }
                            case 4:
                            {
                                s.Exit_system();
                                break;
                            }
                            }
                        }
                        break;
                    }
                    case 3://修改密码
                    {
                        s.change_key(user);
                        break;
                    }
                    case 4://退出系统
                    {
                        s.Exit_system();
                        break;
                    }
                    }

                }
            }
            break;
        }
        case 4://退出系统
        {
            s.Exit_system();
            break;
        }
        }
    }
    return 0;
}