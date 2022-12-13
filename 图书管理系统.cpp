#include<iostream>
#include<string>
#include<cstdlib>
#define FILENAME "userfile.txt"
#define FILENAME1 "bookfile.txt"
#include<fstream>
using namespace std;
#define User_MAX 1000
#define Book_MAX 100000
//ϵͳ��ͼ���������û�������ϵͳ���������������

//���������� ��Ʋ�ʵ��һ��ͼ�����ϵͳ����ģ��ͼ�����ϵͳ�Ĳ��ֹ��ܣ���������ע�ᣬ���߽��ģ�ͼ������û�����ȡ�
//����˵����
// (1�� ģ��ͼ�����ϵͳ������ ��������ע�ᡢ���߽��ġ�ͼ������û�����ȹ��ܡ�
//��2�� ����ͳ�Ʒ��� ��ʱ����ͳ�Ʒ������Ա��˽⵱ǰ�Ľ����������ص�����״̬��ͳ�Ʒ����������������а�����״̬ͳ�ƺ͵���δ��ͼ���ͳ�Ƶȡ�
//��4�� ����ͼ����Ŀ��ϵͳ������������������



// ͼ����
//ͼ����Ϣ��������ţ����������ߣ������磬����ʱ�䣬�۸�ȡ�
class Book
{
public:
    friend class System;
    //���캯��
    Book() 
    {
        Is_lend = 0;
    }
    Book(int n, string a, string au, string p, string t, double pr,int i) :num(n), name(a), author(au), press(p), time(t), price(pr),Is_lend(i) {};
    void display();
private:
    int num;//���
    string name;//����
    string author;//����
    string press;//������
    string time;//����ʱ��
    double price;//�۸�
    int Is_lend;//�Ƿ񱻽���ı�־
};

void Book::display()
{
    cout << "ͼ����ţ�" << num << "\t������" << name << "\t���ߣ�" << author <<"\t�����磺" <<press<<"\t����ʱ�䣺"<<time<<"\t�۸�"<<price<<"\t�Ƿ񱻽����"<<Is_lend << endl;
}

//�û���
class User
{
public:
    friend class System;
    //���캯�� Ĭ���û�Ϊ��������
    User() { identity = 1;  }; 
    User(int a,string n, string k,int i) :account(a),name(n), key(k),identity(i){};
    virtual void display()=0;//��ʾ�û�����Ϣ
protected:
    int account;//�û��˺�
    string name;//�û�����
    string key;//�û�����
    int identity;//�ж��û����� 1Ϊ���� 0Ϊ����Ա
};

class Reader :public User
{
public:
    friend class System;
    //���캯�� 
    Reader(){ identity = 1; }
    Reader(int a,string n, string k,int i) :User(a,n, k,i){};
    void display();//��ʾ���ߵ���Ϣ
};

void Reader::display()
{
    cout <<"�û��˺ţ�"<<account << "\t�û�������" << name << "\t���룺" << key << endl;
}

class Librarian :public User
{
public:
    friend class System;
    //���캯�� 
    Librarian() { identity = 0; key = 123456; }//���ù���Ա��ʼ����
    Librarian(int a, string n, string k, int i) :User(a, n, k, i) {};
    void display();//��ʾ����Ա����Ϣ
};

void Librarian::display()
{
    cout << "�û��˺ţ�" << account << "\t�û�������" << name << "\t���룺" << key  << endl;
}

class System
{
public:
    System();//���캯��
    void change_key(User &user);//�޸��û�����
    void User_register();//�û�ע��
    void Reader_Sign(Reader& user);//���ߵ�¼
    int Librarian_Sign(Librarian& user);//����Ա��¼
    void Book_borrow();//ͼ�����
    void Book_lend();//ͼ��黹
    void Add_Book();//���ͼ��
    int Search_Book();//����ͼ�� ���ҷ������
    void Del_Book();//ɾ��ͼ��
    void Search_User();//�����û�
    void Del_User();//ɾ���û�
    void Alter_User();//�޸��û�Ȩ��
    void Exit_system();//�˳�ϵͳ
    void save_user();//�����ļ�
    void save_book();
    int get_user_num();//ͳ������
    int get_book_num();//ͳ��ͼ������
    void init_user();//��ʼ���˻�
    void init_book();//��ʼ��ͼ��
    int IsExist(int account);//�ж��û��Ƿ����
    int IsExist_book(int num);//�ж�ͼ���Ƿ����
    ~System();//��������
private:
    int User_num;//�û�����
    User** User_Array;//�������ָ�룬��ÿ���˻��������Ϣ�ĵ�ַ���δ������飬��ͨ������ָ�����η������е���Ϣ
    int Book_num;//ͼ������
    Book** Book_Array;//�������ָ�룬��ÿ�����������Ϣ�ĵ�ַ���δ������飬��ͨ������ָ�����η������е���Ϣ
    bool File_userIsEmpty;//��־�ļ��Ƿ�Ϊ��
    bool File_bookIsEmpty;//��־�ļ��Ƿ�Ϊ��
};

void System::Add_Book()
{
    //ÿ��ֻ�ܴ���һ����
    int newSize = this->Book_num + 1;//�����¿ռ��С
    if (newSize >= Book_MAX)
    {
        cout << "ͼ���������������޷��������ͼ�飬����������ٴγ��ԣ�" << endl;
    }
    else
    {
        Book** newSpace = new Book * [newSize];//�����¿ռ�
        //��ԭ�ռ������ݴ�ŵ��¿ռ���
        if (this->Book_Array != NULL)
        {
            for (int i = 0; i < this->Book_num; i++)
            {
                newSpace[i] = this->Book_Array[i];
            }
        }
        //��ʱ�������ڽ���ͼ����Ϣ
        int num;//���
        string name;//����
        string author;//����
        string press;//������
        string time;//����ʱ��
        double price;//�۸�
        cout << "��������ţ�";  cin >> num;
        cout << "������������"; cin >> name;
        cout << "���������ߣ�"; cin >> author;
        cout << "����������磺"; cin >> press;
        cout << "���������ʱ�䣺"; cin >> time;
        cout << "������۸�"; cin >> price;
        //���ù��캯������ͼ��
        Book *str = new Book(num,name,author,press,time,price,0);
        //��ͼ���ַ���������в��Ҹ���ϵͳ�е�ͼ������
        newSpace[this->Book_num] = str;
        //�ͷ�ԭ�пռ�
        delete[] this->Book_Array;
        //�����¿ռ��ָ��
        this->Book_Array = newSpace;
        //�����µ��û�����
        this->Book_num = newSize;
        //�����ļ���Ϊ�ձ�־
        this->File_bookIsEmpty = false;
        cout << "ͼ����ӳɹ���"<<endl;
        //��ͼ����Ϣ�����ļ���
        this->save_book();
        //��������������ص��ϼ�Ŀ¼
        system("pause");
        system("cls");
    }
}


void System::Exit_system()
{
    cout << "��ӭ�´�ʹ��" << endl;
    system("pause");
    exit(0);
}

//ע���˻�
void System::User_register()
{
    //ÿ��ע��ֻ�ܿ�һ��
    int newSize = this->User_num + 1;//�����¿ռ��С
    if (newSize >= User_MAX)
    {
        cout << "ϵͳ�û������������޷�����ע�ᣬ����ϵ����Ա��" << endl;
    }
    else
    {
        User** newSpace = new User * [newSize];//�����¿ռ�
        //��ԭ�ռ������ݴ�ŵ��¿ռ���
        if (this->User_Array != NULL)
        {
            for (int i = 0; i < this->User_num; i++)
            {
                newSpace[i] = this->User_Array[i];
            }
        }
        //��ʱ�������ڽ����û���Ϣ
        string n;//�û����� 
        string k;//�û�����
        int i;//�û�����
        cout << "���������������Ա����ע�᣺";  cin >> n;
        cout << "�������������룺"; cin >> k;
        cout << "��������Ҫע����ݣ�0������Ա 1������"; cin >> i;
        //���ù��캯�������û�����ֵ
        User* str;
        if (i == 0)
        {
            str = new Librarian(this->User_num, n, k,i);
        }
        else
        {
            str = new Reader(this->User_num, n, k,i);
        }
        //���˻���ַ���������в��Ҹ���ϵͳ�е��û�����
        newSpace[this->User_num] = str;
        //�ͷ�ԭ�пռ�
        delete[] this->User_Array;
        //�����¿ռ��ָ��
        this->User_Array = newSpace;
        //�����µ��û�����
        this->User_num = newSize;
        //�����ļ���Ϊ�ձ�־
        this->File_userIsEmpty = false;
        cout << "��ͨ�˻��ɹ��������˻�Ϊ��" << str->account << endl;
        //���û���Ϣ�����ļ���
        this->save_user();
        //��������������ص��ϼ�Ŀ¼
        system("pause");
        system("cls");
    }
}

System::System()
{
    ifstream ifs,ifs1;
    ifs.open(FILENAME, ios::in);
    ifs1.open(FILENAME1, ios::in);
    //�ļ����������
    if (!ifs.is_open()&& !ifs1.is_open())
    {
        cout << "�û��ļ�������" << endl;//�������
        this->User_num = 0;//��ʼ������
        this->User_Array = NULL;//��ʼ������ָ��
        this->File_userIsEmpty = true;//��ʼ���ļ�Ϊ�ձ�־
        ifs.close();//�ر��ļ�
        cout << "ͼ���ļ�������" << endl;//�������
        this->Book_num = 0;//��ʼ������
        this->Book_Array = NULL;//��ʼ������ָ��
        this->File_bookIsEmpty = true;//��ʼ���ļ�Ϊ�ձ�־
        ifs1.close();//�ر��ļ�
        return;
    }
    else 
    {
        //�ļ����ڲ���û�м�¼
        //����һ���ַ���������ch���ļ�ĩβ���ַ���������eof�����ж�
        //�ļ�Ϊ��ʱ�ļ�ĩβ����һ���ַ�
        char ch;
        ifs >> ch;
        if (ifs.eof())//eofΪ�ж��ļ��Ƿ�Ϊ�պ���
        {
            cout << "�û��ļ�Ϊ�գ�" << endl;
            this->User_num = 0;
            this->User_Array = NULL;
            this->File_userIsEmpty = true;
            ifs.close();
        }
        ifs1 >> ch;
        if (ifs1.eof())//eofΪ�ж��ļ��Ƿ�Ϊ�պ���
        {
            cout << "ͼ���ļ�Ϊ�գ�" << endl;
            this->Book_num = 0;
            this->Book_Array = NULL;
            this->File_bookIsEmpty = true;
            ifs1.close();
        }
        //�û��ļ����ڲ���¼����
        int num = this->get_user_num();
        this->User_num = num;
        cout << "�û�����Ϊ��" << num << endl;
        //���ٿռ�
        this->User_Array = new User * [this->User_num];
        this->init_user();
        //ͼ���ļ����ڲ���¼����
        int num1 = this->get_book_num();
        this->Book_num = num1;
        cout << "ͼ������Ϊ��" << num1 << endl;

        //���ٿռ�
        this->Book_Array = new Book * [this->Book_num];
        this->init_book();
        //���ļ��е����ݴ浽������
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

//���ߵ�¼
void System::Reader_Sign(Reader &user)
{
    if (this->File_userIsEmpty)
    {
        cout << "�ļ������ڣ�" << endl;
    }
    //���ڽ����û�������Ϣ����һ�����ڽ����ļ����ҵ�����Ϣ
    int account;
    string key;
    cout << "�����������˺��������Ե�¼�˺ţ�" << endl;
    cin >> account >> key;
    user.account = account;//���˺Ŵ���user��������user.password�����ļ��д�Ŷ�Ӧ�˺ŵ�����
    //���ļ��в��Ҷ�Ӧ�˻�������������������û�ע���˻�
    //�˶��˻������Ƿ����û��������ͬ����ͬ����û���Ϣ������ͬ�����û�����
    int i = IsExist(user.account);
    user.account= this->User_Array[i]->account;
    user.name = this->User_Array[i]->name;
    user.key = this->User_Array[i]->key;
    if (key == user.key)
    {
        cout << "��½�ɹ����û���ϢΪ��"; user.display();//��ʾ�û���¼��Ϣ
    }
    else
    {
        cout << "�������������" << endl;
    }
    system("pause");
    system("cls");
}

void System::Book_borrow()//ͼ�����
{
    int i=Search_Book();//������Ҫ���ĵ�ͼ��
    char ch;
    cout << "�Ƿ�����������ҵ�ͼ��? y/n" << endl;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        this->Book_Array[i]->Is_lend = 1;//�����鼮�����־
        this->save_book();//�����ļ�������
        cout << "���ĳɹ����ǵð�ʱ�黹���Һúð����鼮��" << endl;
    }
    else
    {
        cout << "�������鼮�������ģ����Զ࿴����" << endl;
    }
    system("pause");
    system("cls");
}

void System::Book_lend()//�黹ͼ��
{
    cout << "��������Ҫ�黹��ͼ����ţ�" << endl;
    int num; char ch;
    cin >> num;
    cout << "������ȷ�Ϲ黹������ y/n"<<endl;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        this->Book_Array[num]->Is_lend = 0;//�����鼮�����־
        this->save_book();//�����ļ�������
        cout << "��л���Ľ��ģ�ϣ���и����������õ����飡��ӭ�´ν��ģ�" << endl;
    }
    else
    {
        cout << "�����Լ����Ķ�������ע��黹ʱ��" << endl;
    }
    system("pause");
    system("cls");
}

int System::Search_Book()
{
    if (this->File_bookIsEmpty)
    {
        cout << "������ͼ�飡" << endl;
        return -1;
    }
    //���
    int num=0;
    cout << "����������Ҫ���ҵ�ͼ�����ţ�" << endl;
    cin >> num;
    int i = IsExist_book(num);//�ж�ͼ���Ƿ����
    if (i != -1)
    {
        cout << "�������ҵ�ͼ����Ϣ���£�" << endl;
        cout << "ͼ����ţ�" << this->Book_Array[i]->num << "\t������" << this->Book_Array[i]->name << "\t���ߣ�" << this->Book_Array[i]->author
            << "\t�����磺" << this->Book_Array[i]->press << "\t����ʱ�䣺" << this->Book_Array[i]->time << "\t�۸�" << this->Book_Array[i]->price
            << "\t�Ƿ񱻽����" << this->Book_Array[i]->Is_lend << endl;
    }
    else
    {
        cout << "������˼�������޴�ͼ��" << endl;
    }
    return i;
}

void System::Search_User()
{
    if (this->File_userIsEmpty)
    {
        cout << "���û����ڣ�" << endl;
    }
    //�û��˺�
    int account;
    cout << "����������Ҫ���ҵ��û����˺ţ�" << endl;
    cin >> account;
    int i = IsExist(account);
    if (i != -1)
    {
        cout << "�������ҵ��û���Ϣ���£�" << endl;
        cout << "�û��˻�Ϊ��" << this->User_Array[i]->account << "�û�������" << this->User_Array[i]->name
            << "\t���룺" << this->User_Array[i]->key << "\t��ݣ�" << this->User_Array[i]->identity << endl;
    }
    else
    {
        cout << "������˼��ϵͳ���޴��û�" << endl;
    }
}

void System::Alter_User()//�޸��û�Ȩ��
{
    //�û��˺�
    int account;
    cout << "����������Ҫ�޸�Ȩ�޵��û����˺ţ�" << endl;
    cin >> account;
    int i = IsExist(account);//��ȡ�û���Ϣ
    cout << "���û������Ϊ��" << this->User_Array[i]->identity << endl;;
    cout << "��������Ҫ��������޸ĳ�ʲô? 0��������Ա 1��������" << endl;
    int iden;
    cin >> iden;
    this->User_Array[i]->identity = iden;//���������е����
    //����ͬ�����µ��ļ���
    this->save_user();
    cout << "����Ȩ�޳ɹ�" << endl;
    system("pause");
    system("cls");
}

void System::Del_Book()
{
    //������ɾ�����ݣ����ʾ�������ǰ��
    if (this->File_bookIsEmpty)
    {
        cout << "������ͼ���ɾ����" << endl;
    }
    else
    {
        //����ͼ����Ž���ɾ��
        cout << "��������Ҫɾ����ͼ�����ţ�" << endl;
        int num = 0;
        cin >> num;
        int index = this->IsExist_book(num);
        if (index != -1)//˵��ͼ�����
        {
            //����ǰ��
            for (int i = index; i < this->Book_num - 1; i++)
            {
                this->Book_Array[i] = this->Book_Array[i + 1];
            }
            this->Book_num--;//���������м�¼���˻�����
            //����ͬ�����µ��ļ���
            this->save_book();
            cout << "ɾ���ɹ���" << endl;
        }
        else
        {
            cout << "ɾ��ʧ�ܣ�δ�ҵ�ͼ����Ϣ" << endl;
        }
    }
    system("pause");
    system("cls");
}

//����Ա��¼
int System::Librarian_Sign(Librarian& user)
{
    if (this->File_userIsEmpty)
    {
        cout << "�ļ������ڣ�" << endl;
    }
    //���ڽ����û�������Ϣ����һ�����ڽ����ļ����ҵ�����Ϣ
    int account;
    string key;
    cout << "�����������˺��������Ե�¼�˺ţ�" << endl;
    cin >> account >> key;
    user.account = account;//���˺Ŵ���user��������user.key�����ļ��д�Ŷ�Ӧ�˺ŵ�����
    //���ļ��в��Ҷ�Ӧ�˻�������������������û�ע���˻�
    //�˶��˻������Ƿ����û��������ͬ����ͬ����û���Ϣ������ͬ�����û�����
    int i = IsExist(user.account);
    user.account = this->User_Array[i]->account;
    user.name = this->User_Array[i]->name;
    user.key = this->User_Array[i]->key;
    user.identity = this->User_Array[i]->identity;
    if (key == user.key&&(user.identity==0))
    {
        cout << "��½�ɹ����û���ϢΪ��"; user.display();//��ʾ�û���¼��Ϣ
        system("pause");
        system("cls");
        return 1;
    }
    else
    {
        cout << "�������/�����ǹ���Ա��������" << endl;
        system("pause");
        system("cls");
        return 0;
       
    }
}

//�޸�����
void System::change_key(User& user)
{
    string old_key, new_key;
    cout << "��������ԭ�������룺" << endl;
    cin >> old_key;
    if (old_key == user.key)
    {
        cout << "����������Ҫ���õ��µ����룺" << endl;
        cin >> new_key;
        user.key = new_key;
        cout << "���������޸ĳɹ�" << endl;
    }
    else
    {
        cout << "�����������������" << endl;
    }
    this->User_Array[user.account]->key = user.key;//���������е�����
    //����ͬ�����µ��ļ���
    this->save_user();
    system("pause");
    system("cls");
}

void System::Del_User()
{
    //������ɾ�����ݣ����ʾ�������ǰ��
    if (this->File_userIsEmpty)
    {
        cout << "�ļ������ڣ�" << endl;
    }
    else
    {
        //�����û��˺Ž���ɾ��
        cout << "��������Ҫɾ�����˺ţ�" << endl;
        int account = 0;
        cin >> account;
        int index = this->IsExist(account);
        if (index != -1)//˵���˻�����
        {
            //����ǰ��
            for (int i = index; i < this->User_num - 1; i++)
            {
                this->User_Array[i] = this->User_Array[i + 1];
            }
            this->User_num--;//���������м�¼���˻�����
            //����ͬ�����µ��ļ���
            this->save_user();
            cout << "ɾ���ɹ���" << endl;
        }
        else
        {
            cout << "ɾ��ʧ�ܣ�δ�ҵ��˻���Ϣ" << endl;
        }
    }
    system("pause");
    system("cls");
}

//�����ļ�
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

//�����ļ�
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
        //��¼����
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
        //��¼ͼ������
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
    int index = 0;//�±�����
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

//����ע�ᡢ���߽��ġ�ͼ������û�����
void menu1()
{
    cout << "**************" << endl;
    cout << "1���û�ע��" << endl;
    cout << "2�����ߵ�¼" << endl;
    cout << "3������Ա��¼" << endl;
    cout << "4���˳�ϵͳ" << endl;
    cout << "**************" << endl;
}
void menu2()
{
    cout << "**************" << endl;
    cout << "1��ͼ�����" << endl;
    cout << "2��ͼ��黹" << endl;
    cout << "3���޸�����" << endl;
    cout << "4���˳�ϵͳ" << endl;
    cout << "**************" << endl;
}
void menu3()
{
    cout << "**************" << endl;
    cout << "1��ͼ�����" << endl;
    cout << "2���û�����" << endl;
    cout << "3���޸�����" << endl;
    cout << "4���˳�ϵͳ" << endl;
    cout << "**************" << endl;
}

void menu4()
{
    cout << "**************" << endl;
    cout << "1������ͼ��" << endl;
    cout << "2��ɾ��ͼ��" << endl;
    cout << "3�����ͼ��" << endl;
    cout << "4���˳�ϵͳ" << endl;
    cout << "**************" << endl;
}

void menu5()
{
    cout << "**************" << endl;
    cout << "1�������û�" << endl;
    cout << "2��ɾ���û�" << endl;
    cout << "3���޸��û�Ȩ��" << endl;
    cout << "4���˳�ϵͳ" << endl;
    cout << "**************" << endl;
}

int main()
{
    System s;
    int select;//ѡ��
    while (1)
    {
        menu1();
        cout << "����������ѡ��:" << endl;
        cin >> select;
        switch (select)
        {
        case 1://�û�ע��
        {
            s.User_register();
            break;
        }
        case 2://���ߵ�¼
        {
            Reader user;//���������
            s.Reader_Sign(user);
            int choosen = 0;
            while (true)
            {
                cout << "������������Ĳ�����" << endl;
                menu2();
                cin >> choosen;
                switch (choosen)
                {
                case 1://ͼ�����
                {
                    s.Book_borrow();
                    break;
                }
                case 2://ͼ��黹
                {
                    s.Book_lend();
                    break;
                }
                case 3://�޸�����
                {
                    s.change_key(user);
                    break;
                }
                case 4://�˳�ϵͳ
                {
                    s.Exit_system();
                    break;
                }
                }
                break;
            }
            break;
        }
        case 3://����Ա��¼
        {
            Librarian user;
            while (s.Librarian_Sign(user))
            {
                int choosen = 0;
                while (true)
                {
                    cout << "������������Ĳ�����" << endl;
                    menu3();
                    cin >> choosen;
                    switch (choosen)
                    {
                    case 1://ͼ�����
                    {
                        int choosen1 = 0;
                        while (true)
                        {
                            cout << "������������Ĳ�����" << endl;
                            menu4();
                            cin >> choosen1;
                            switch (choosen1)
                            {
                            case 1://����ͼ��
                            {
                                s.Search_Book();
                                break;
                            }
                            case 2://ɾ��ͼ��
                            {
                                s.Del_Book();
                                break;
                            }
                            case 3://���ͼ��
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
                    case 2://�û�����
                    {
                        int choosen2 = 0;
                        while (true)
                        {
                            cout << "������������Ĳ�����" << endl;
                            menu5();
                            cin >> choosen2;
                            switch (choosen2)
                            {
                            case 1://�����û�
                            {
                                s.Search_User();
                                break;
                            }
                            case 2://ɾ���û�
                            {
                                s.Del_User();
                                break;
                            }
                            case 3://�޸��û�Ȩ��
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
                    case 3://�޸�����
                    {
                        s.change_key(user);
                        break;
                    }
                    case 4://�˳�ϵͳ
                    {
                        s.Exit_system();
                        break;
                    }
                    }

                }
            }
            break;
        }
        case 4://�˳�ϵͳ
        {
            s.Exit_system();
            break;
        }
        }
    }
    return 0;
}