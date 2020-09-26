#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
using namespace std;
//定义商品货物类
class goods
{
protected:
    char name[60];        //商品名称
    char price[20];       //商品价格
    char adress[60];      //商品产地
    char mill[60];        //生产厂商
    int id;               //编号
    goods *Mynext;        //指向下一个对象
public:
    goods();             //初始化变量
    goods(char pname[],char pprice[],char padress[],char pmill[],int pid);//初始化对象不含指针
    goods(char pname[],char pprice[],char padress[],char pmill[],int pid,goods *next);//初始化对象含指针

    //获得保护数据成员的函数
    char *getname();
    char *getprice();
    char *getadress();
    char *getmill();
    int   getid();

    goods *getnext();//获得节点指针
    void  setnext(goods *next);//设置节点指针
    void updatid();//id自减

};
//类中定义函数的实现

goods::goods()
{
    strcpy(name,"");
    strcpy(price,"");
    strcpy(adress,"");
    strcpy(mill,"");
    Mynext = NULL;
    id = 0;
}
goods::goods(char pname[],char pprice[],char padress[],char pmill[],int pid)
{
    strcpy(name,pname);
    strcpy(price,pprice);
    strcpy(adress,padress);
    strcpy(mill,pmill);
    Mynext = NULL;
    id = pid;
}
goods::goods(char pname[],char pprice[],char padress[],char pmill[],int pid,goods *next)
{
    strcpy(name,pname);
    strcpy(price,pprice);
    strcpy(adress,padress);
    strcpy(mill,pmill);
    Mynext = next;
    id = pid;
}
char *goods::getname()
{
    return name;
}
char *goods::getprice()
{
    return price;
}
char *goods::getadress()
{
    return adress;
}
char *goods::getmill()
{
    return mill;
}
goods *goods::getnext()
{
    return Mynext;
}
void goods::setnext(goods *next)
{
    Mynext = next;
}
int goods::getid()
{
    return id;
}
void goods::updatid()
{

    id = id - 1;
}

//定义商品库类
class AddressBook
{
private:
    goods *myfirst;
public:
    AddressBook();//初始化
    AddressBook(char npname[],char npprice[],char npadress[],char npmill[],int npid);//创建对象
    ~AddressBook();
    void Show_Link();//查看
    void Add_Link();//添加

    void Edi_Link();//修改
    void Del_Link();//删除
    void Log_Out();//退出


    void outall();//打印当前所有数据


};
//类中定义函数的实现
AddressBook::AddressBook()
{
    myfirst = NULL;
}
AddressBook::AddressBook(char npname[],char npprice[],char npadress[],char npmill[],int npid)
{
    myfirst = new goods(npname,npprice,npadress,npmill,npid);
}
AddressBook::~AddressBook()
{
    goods *next = myfirst,*temp;
    while(next != NULL)
    {
        temp = next;
        next = next->getnext();
        delete temp;

    }
    myfirst = NULL;
}
//输出打印商品功能
void AddressBook::outall()
{
    int i=0;
    goods *head = myfirst;
    if(head == NULL)
    {
        cout<<"[目前暂无数据]"<<endl;
        cout<<endl;


        return;
    }
    cout<<setw(10)<<"商品ID"<<setw(20)<<"商品名称"<<setw(20)<<"商品价格"<<setw(20)<<"商品产地"<<setw(20)<<"生产厂商"<<endl;
    cout<<"____________________________________________________________________________________________"<<endl;
    while(head)
    {
        i++;
        cout<<"|"<<setw(10)<<head->getid()<<setw(20)<<head->getname()<<setw(20)<<head->getprice()<<setw(20)<<head->getadress()<<setw(20)<<head->getmill()<<"|"<<endl;

        head = head -> getnext();
    }
    cout<<"|__________________________________________________________________________________________|"<<endl;

    cout<<"总计"<<"-"<<i<<"-"<<"种商品\n\n"<<endl;
    cout<<endl;
    return;
}
//添加商品功能
void AddressBook::Add_Link()
{

    outall();//输出所有数据
    int adid;


    char adname[60],adprice[20],adadress[60],admill[60],flag[5];


    strcpy(flag,"y\0");
    while(strcmp(flag,"y\0") == 0)
    {

        //开始添加
        goods *p = myfirst;
        goods *rpeat = myfirst;//判断录入是否重复

        cout<<"=开始添加商品信息=\n"<<endl;
        cout<<"商品名称:"<<endl;
        cin>>adname;

        cout<<"商品价格:"<<endl;
        cin>>adprice;
        while(rpeat)
        {
            if(strcmp(adname,rpeat->getname()) == 0 || strcmp(adprice,rpeat->getprice()) == 0)
            {
                cout<<"商品:"<<adname<<"/价格:"<<adprice<<"已存在！"<<endl;
                system("pause");
                system("cls");
                return;
            }
            rpeat = rpeat -> getnext();
        }

        cout<<"输入商品产地:"<<endl;
        cin>>adadress;

        cout<<"输入生产厂商:"<<endl;
        cin>>admill;


        if(p == NULL)
        {
            adid = 1;
            myfirst = new goods(adname,adprice,adadress,admill,adid);
        }
        else
        {
            while(p->getnext() != NULL)
            {

                p = p->getnext();
                //生成商品ID
                adid = p->getid() + 1;
            }

            p ->  setnext(new goods(adname,adprice,adadress,admill,adid,p->getnext())) ;

        }
        system("pause");
        system("cls");
        cout<<"保存成功！"<<endl;
        cout<<"是【y】否【n】继续添加商品？"<<endl;

        cin>>flag;
        system("cls");

    }



}

//修改编辑商品功能
void AddressBook::Edi_Link()
{
    int n;//计数
    char ename[60];
    outall();//输出所有商品信息
    cout<<"请输入要编辑的商品名称:"<<endl;
    cin>>ename;
    system("cls");
    goods *head = myfirst;
    int flag = 0;
    while(head)
    {
        if(flag == 2)//修改完成已无需再遍历
        {
            break;
        }

        if(strcmp(head->getname(), ename)==0)
        {

            cout<<"Old-Data:"<<endl;
            cout<<setw(10)<<head->getid()<<setw(20)<<head->getname()<<setw(20)<<head->getprice()<<setw(20)<<head->getadress()<<setw(20)<<head->getmill()<<endl;

            while(1)
            {
                int i;
                char enew[60];
                cout<<"     +-----------------------------------+"<<endl;
                cout<<"     |   [请继续选择您要修改的内容/退出] |"<<endl;
                cout<<"     |                                   |"<<endl;
                cout<<"     |              - 1.商品名称         |"<<endl;
                cout<<"     |              - 2.商品价格         |"<<endl;
                cout<<"     |              - 3.商品产地         |"<<endl;
                cout<<"     |              - 4.生产产商         |"<<endl;
                cout<<"     |              - 0.退出             |"<<endl;
                cout<<"     +-----------------------------------+"<<endl;
                cout<<".";
                cin>>i;
                if(i > 4 || i < 0)
                {
                    cout<<"输入错误！重新输入..."<<endl;
                    system("pause");
                    system("cls");
                    continue;
                }
                if(i == 0)
                {
                    system("cls");
                    break;
                }
                switch(i)
                {
                case 1:
                    cout<<"商品名称修改为:"<<endl;
                    cin>>enew;
                    strcpy(head->getname(),enew);
                    system("cls");
                    break;
                case 2:
                    cout<<"新价格:"<<endl;
                    cin>>enew;
                    strcpy(head->getprice(),enew);
                    system("cls");
                    break;
                case 3:
                    cout<<"新产地:"<<endl;
                    cin>>enew;
                    strcpy(head->getadress(),enew);
                    system("cls");
                    break;
                case 4:
                    cout<<"新产商 :"<<endl;
                    cin>>enew;
                    strcpy(head->getmill(),enew);
                    system("cls");
                    break;
                }
                //当修改的为第一个商品时
                if(flag == 0)
                {
                    myfirst = head;
                }
                flag = 2;//此状态代表修改操作完成
            }


        }
        else
        {
            flag = 1;//代表head已经不是第一个节点了
            head = head -> getnext();
        }

    }
    if(flag != 2)
    {
        cout<<"你还未添加任何商品！"<<endl;
        system("pause");
        system("cls");
    }
    else
    {
        system("cls");
        cout<<"New-Data:"<<endl;
        cout<<setw(10)<<head->getid()<<setw(20)<<head->getname()<<setw(20)<<head->getprice()<<setw(20)<<head->getadress()<<setw(20)<<head->getmill()<<endl;
        cout<<"__________"<<endl;
        cout<<ename<<"修改成功！"<<endl;
        system("pause");
        system("cls");
    }
    return;
}
//删除下架商品功能
void AddressBook::Del_Link()
{
    char dname[60];
    outall();//输出所有商品
    cout<<"请输入要下架的商品名称:"<<endl;
    cin>>dname;
    goods *head = myfirst;
    goods *fhead = myfirst;//fhead用于一会指代head的前一个
    int flag = 0;

    while(head)
    {

        if(strcmp(head->getname(), dname)==0)
        {
            cout<<"[DelData]:"<<endl;
            cout<<setw(10)<<head->getid()<<setw(20)<<head->getname()<<setw(20)<<head->getprice()<<setw(20)<<head->getadress()<<setw(20)<<head->getmill()<<endl;

            fhead->setnext(head->getnext());//让head的前一个节点指向head的后一个节点；
            head = NULL;

            fhead = fhead->getnext();//从fhead开始ID自减一

            while(fhead)
            {
                //cout<<"进入循环-自减"<<endl;
                fhead->updatid();
                fhead = fhead->getnext();
            }
            //当删除的为第一个商品时
            if(flag == 0)
            {
                myfirst = myfirst -> getnext();
                cout<<dname<<"商品已下架！"<<endl;
                cout<<"__________"<<endl;
                system("pause");
                system("cls");
                return;
            }
        }
        else
        {
            flag = 1;
            fhead = head;
            head = head -> getnext();

        }

    }
    if(flag == 0)
    {
        cout<<"暂无数据！"<<endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout<<"__________"<<endl;
        cout<<dname<<"商品已下架！"<<endl;
        system("pause");
        system("cls");
    }

    return;
}


//主函数
int main()
{
    AddressBook call;
    cout<<setiosflags(ios::left);//输出左对齐

    //system("color 0F");//原味
    system("color 06");//黄
    //system("color 04");//红
    //system("color 05");//粉
    while(1)
    {
        //主菜单
        cout<<"     +--------------------------------------------------+"<<endl;
        cout<<"     |              [商品管理系统]                      |"<<endl;
        cout<<"     |                                                  |"<<endl;
        cout<<"     |              * 1.查看所有商品                    |"<<endl;
        cout<<"     |              * 2.添加新商品                      |"<<endl;
        cout<<"     |              * 3.修改商品信息                    |"<<endl;
        cout<<"     |              * 4.下架删除商品                    |"<<endl;
        cout<<"     |                                                  |"<<endl;
        cout<<"     |              * 0.退出                            |"<<endl;
        cout<<"     +--------------------------------------------------+"<<endl;
        int i;
        cout<<".";
        cin>>i;
        switch(i)
        {
        case(1):
            system("cls");
            call.outall();
            break;
        case(2):
            system("cls");
            call.Add_Link();
            break;
        case(3):
            system("cls");
            call.Edi_Link();
            break;
        case(4):
            system("cls");
            call.Del_Link();
            break;
        case(0):
            cout<<"感谢您的使用，祝您购物愉快！Bye-Bye- …^—^… ！"<<endl;
            return 0;
        default:
            cout<<"输入有误！请重新输入..."<<endl;
            system("pause");
            system("cls");
            continue;
        }
    }

}
