#include <iostream>
#include <cassert>//按行读取
#include <fstream>//读写文件
#include <cstring>
#include <ctime>//生成随机种子，用于随机安排配送
#include <iomanip>
#include <stdlib.h>

using namespace std;
//定义系统数据类
class Ios_Data
{
protected:
    char name[60];        //属性1-店铺-客户-配送员-/订单客户
    int  price;           //属性2-店铺价格-客户手机号-配送手机号/订单订单价格合计
    char address[60];     //属性3-店铺菜品-客户地址-配送员评分/订单店铺菜品及数量
    char mill[60];        //属性4-店铺评分-客户下单备注/订单配送员

    int id;               //属性的统计序号/订单编号

    Ios_Data *Mynext;     //指向下一个对象
public:
    Ios_Data();           //初始化变量
    Ios_Data(char pname[],int pprice,char padress[],char pmill[],int pid);//初始化对象不含指针
    Ios_Data(char pname[],int pprice,char padress[],char pmill[],int pid,Ios_Data *next);//初始化对象含指针

    //获得保护数据成员的函数
    char *getname();
    int  getprice();
    char *getadress();
    char *getmill();
    int   getid();

    Ios_Data *getnext();//获得节点指针
    void  setnext(Ios_Data *next);//设置节点指针
    void setprice(int newprice);
    void updatid();//id自减

};
//类中定义函数的实现

Ios_Data::Ios_Data()
{
    strcpy(name,"");
    price = 0;
    strcpy(address,"");
    strcpy(mill,"");
    Mynext = NULL;
    id = 0;
}
Ios_Data::Ios_Data(char pname[],int pprice,char padress[],char pmill[],int pid)
{
    strcpy(name,pname);
    price = pprice;
    strcpy(address,padress);
    strcpy(mill,pmill);
    Mynext = NULL;
    id = pid;
}
Ios_Data::Ios_Data(char pname[],int pprice,char padress[],char pmill[],int pid,Ios_Data *next)
{
    strcpy(name,pname);
    price = pprice;
    strcpy(address,padress);
    strcpy(mill,pmill);
    Mynext = next;
    id = pid;
}
char *Ios_Data::getname()
{
    return name;
}
int Ios_Data::getprice()
{
    return price;
}
char *Ios_Data::getadress()
{
    return address;
}
char *Ios_Data::getmill()
{
    return mill;
}
Ios_Data *Ios_Data::getnext()
{
    return Mynext;
}
void Ios_Data::setnext(Ios_Data *next)
{
    Mynext = next;
}
void Ios_Data::setprice(int newprice)
{
    price = newprice;
}
int Ios_Data::getid()
{
    return id;
}
void Ios_Data::updatid()
{

    id = id - 1;
}

//定义系统类（用于创建 店铺-客户-配送员-订单 管理系统）
class IOS
{
private:
    Ios_Data *myfirst;
public:
    IOS();//初始化
    IOS(char npname[],int npprice,char npadress[],char npmill[],int npid);//创建对象
    ~IOS();
    void Show_Link(int key);//查看
    void Add_Link(int key);//添加
    void Edi_Link(int key);//修改
    void Del_Link(int key);//删除
    int Find_Link(int key);//查询

    void read_txt(int key);//读取数据
    void write_txt(int key);//数据保存

    void outall(int key);//打印当前所有数据


};
//类中定义函数的实现
IOS::IOS()
{
    myfirst = NULL;
}
IOS::IOS(char npname[],int npprice,char npadress[],char npmill[],int npid)
{
    myfirst = new Ios_Data(npname,npprice,npadress,npmill,npid);
}
IOS::~IOS()
{
    Ios_Data *next = myfirst,*temp;
    while(next != NULL)
    {
        temp = next;
        next = next->getnext();
        delete temp;

    }
    myfirst = NULL;
}
//从相应的txt文件读入数据
void IOS::read_txt(int key)
{
    int i = 0;
    int rid = 0,rprice = 0;
    char rname[60],raddress[60],rmill[60];
    ifstream read1("Client_data.txt");
    ifstream read2("Constom_data.txt");
    ifstream read3("Deliver_data.txt");
    ifstream read4("Order_data.txt");
    string line;
    while(getline(read1,line)&& key == 1||getline(read2,line)&& key == 2||getline(read3,line)&& key == 3||getline(read4,line)&& key == 4)
    {
        i++;
        if(i % 4 == 1)//第一行为name
        {
            strcpy(rname,line.c_str());//string类型不能直接赋值给char,要用c_str()转换一下
        }
        if(i % 4 == 2)//第二行为price
        {
            //char b[60];
            //strcpy(b,line.c_str());
            //int rprice = atoi(b);//char型转int型
            srand((int)time(0));
            rprice = rand()%50;
        }
        if(i % 4 == 3)//第三行为address
        {
            strcpy(raddress,line.c_str());
        }
        if(i % 4 == 0)//第四行为mill
        {
            rid++;
            strcpy(rmill,line.c_str());
            //读到完整的一组数据,开始赋值给链表
            Ios_Data *p = myfirst;
            if(p == NULL)
            {
                myfirst = new Ios_Data(rname,rprice,raddress,rmill,rid);
            }
            else
            {
                while(p->getnext() != NULL)
                {
                    p = p->getnext();
                }
                p ->  setnext(new Ios_Data(rname,rprice,raddress,rmill,rid,p->getnext())) ;

            }

        }
    }

}
void IOS::write_txt(int key)
{

    Ios_Data *p = myfirst;
    //以覆盖写的方式打开对应文件
    if(key == 1)
    {
        std::ofstream write("Client_data.txt");
        while(p)
        {
            write<<p->getname()<<"\n"<<p->getprice()<<"\n"<<p->getadress()<<"\n"<<p->getmill()<<"\n";
            p = p->getnext();
        }
        write.close();
    }
    if(key == 2)
    {
        std::ofstream write("Constom_data.txt");
        while(p)
        {
            write<<p->getname()<<"\n"<<p->getprice()<<"\n"<<p->getadress()<<"\n"<<p->getmill()<<"\n";
            p = p->getnext();
        }
        write.close();
    }
    if(key == 3)
    {
        std::ofstream write("Deliver_data.txt");
        while(p)
        {
            write<<p->getname()<<"\n"<<p->getprice()<<"\n"<<p->getadress()<<"\n"<<p->getmill()<<"\n";
            p = p->getnext();
        }
        write.close();
    }
    if(key == 4)
    {
        std::ofstream write("Order_data.txt");
        while(p)
        {
            write<<p->getname()<<"\n"<<p->getprice()<<"\n"<<p->getadress()<<"\n"<<p->getmill()<<"\n";
            p = p->getnext();
        }
        write.close();
    }


}

//输出打印功能
void IOS::outall(int key)
{
    int i=0;
    Ios_Data *head = myfirst;
    if(head == NULL)
    {
        cout<<"[目前暂无数据]"<<endl;
        cout<<endl;


        return;
    }
    if(key == 1)
    {
        cout<<setw(10)<<"ID"<<setw(20)<<"店铺名称"<<setw(20)<<"商品价格"<<setw(20)<<"商品名称"<<setw(20)<<"商品评分"<<endl;
    }
    if(key == 2)
    {
        cout<<setw(10)<<"ID"<<setw(20)<<"客户姓名"<<setw(20)<<"手机号"<<setw(20)<<"客户地址"<<setw(20)<<"下单备注"<<endl;
    }
    if(key == 3)
    {
        cout<<setw(10)<<"ID"<<setw(20)<<"配送员姓名"<<setw(20)<<"手机号"<<setw(20)<<"服务评分"<<setw(20)<<"负责区域"<<endl;
    }
    if(key == 4)
    {
        cout<<setw(10)<<"订单编号"<<setw(20)<<"订单客户姓名"<<setw(20)<<"付款总计"<<setw(20)<<"菜品"<<setw(20)<<"配送人员"<<endl;
    }
    cout<<"____________________________________________________________________________________________"<<endl;
    while(head)
    {
        i++;
        cout<<"|"<<setw(10)<<head->getid()<<setw(20)<<head->getname()<<setw(20)<<head->getprice()<<setw(20)<<head->getadress()<<setw(20)<<head->getmill()<<"|"<<endl;

        head = head -> getnext();
    }
    cout<<"|__________________________________________________________________________________________|"<<endl;

    cout<<"总计"<<"-"<<i<<"-"<<"条数据\n\n"<<endl;
    cout<<endl;
    return;
}
//添加功能
void IOS::Add_Link(int key)
{
    int adid = 0;

    if(key != 0)
    {
        outall(key);   //输出所有数据
    }
    char adname[60],adadress[60],admill[60],flag[5];
    int adprice;


    strcpy(flag,"y\0");
    while(strcmp(flag,"y\0") == 0)
    {


        //开始添加
        Ios_Data *p = myfirst;
        Ios_Data *rpeat = myfirst;//判断录入是否重复
        if(key == 1)
        {
            ifstream in("Client_data.txt");
            cout<<"您需要输入的店铺信息有：\n"<<endl;
            cout<<setw(10)<<setw(20)<<"【1】店铺名称"<<setw(20)<<"【2】商品价格"<<setw(20)<<"【3】商品名称"<<setw(20)<<"【4】店铺评分"<<endl;
        }
        if(key == 2)
        {
            ifstream in("Constom_data.txt");
            cout<<"您需要输入的客户信息有：\n"<<endl;
            cout<<setw(10)<<setw(20)<<"【1】姓名"<<setw(20)<<"【2】手机号"<<setw(20)<<"【3】地址"<<setw(20)<<"【4】下单备注"<<endl;
        }
        if(key == 3)
        {
            ifstream in("Deliver_data.txt");
            cout<<"您需要输入的配送员信息有：\n"<<endl;
            cout<<setw(10)<<setw(20)<<"【1】姓名"<<setw(20)<<"【2】手机号"<<setw(20)<<"【3】服务评分"<<setw(20)<<"【4】负责区域"<<endl;
        }
        if(key == 4)
        {
            ifstream in("Order_data.txt");
            cout<<"您需要输入的订单信息有：\n"<<endl;
            cout<<setw(10)<<"【1】订单客户"<<setw(20)<<"【2】付款金额"<<setw(20)<<"【3】下单商品"<<setw(20)<<"【4】配送人员"<<endl;
        }





        if(key != 0)
        {

            cout<<"\n [开始输入] \n"<<endl;

            cout<<"属性【1】:"<<endl;
            cin>>adname;
            cout<<"属性【2】:"<<endl;
            cin>>adprice;
        }
        while(rpeat)
        {
            if(strcmp(adname,rpeat->getname()) == 0 )
            {
                cout<<"属性【1】"<<adname<<"已存在！"<<endl;
                system("pause");
                system("cls");
                return;
            }
            rpeat = rpeat -> getnext();
        }
        if(key != 0)
        {
            cout<<"属性【3】:"<<endl;
            cin>>adadress;

            cout<<"属性【4】:"<<endl;
            cin>>admill;
        }
        if(key == 0)
        {
            ifstream in("Order_data.txt");
            int b,b_price;
            cout<<"感谢您在本店消费，请输入订单信息：\n"<<endl;
            cout<<"\n [开始输入] \n"<<endl;

            cout<<"您的姓名:"<<endl;
            cin>>adname;
            cout<<"商品名称:"<<endl;
            cin>>adadress;
            cout<<"商品单价:"<<endl;
            cin>>b_price;
            cout<<"商品数量:"<<endl;
            cin>>b;
            adprice = b*b_price;

            //生成订单
            //随机生成配送人员编号,并转换为char型
            srand((int)time(0));
            admill[60] = '0' + rand()%10;
        }


        if(p == NULL)
        {
            adid = 1;
            myfirst = new Ios_Data(adname,adprice,adadress,admill,adid);
        }
        else
        {
            while(p->getnext() != NULL)
            {

                p = p->getnext();
                //生成商品ID
                adid = p->getid() + 1;
            }

            p ->  setnext(new Ios_Data(adname,adprice,adadress,admill,adid,p->getnext())) ;

        }
        system("pause");
        system("cls");
        if(key == 0)
        {
            std::ofstream fout("Order_data.txt",ios::app);//在文件末尾追加
            fout<<adname<<"\n"<<adprice<<"\n"<<adadress<<"\n"<<admill<<"\n";
            fout.close();
            cout<<"订单已生成！"<<endl<<"已自动安排配送人员！"<<endl;
            system("pause");
            system("cls");
            return;
        }

        //以在末尾追加的方式打开相应文件,写入文件每个变量占一行方便读取
        if(key == 1)
        {
            std::ofstream fout("Client_data.txt",ios::app);
            fout<<adname<<"\n"<<adprice<<"\n"<<adadress<<"\n"<<admill<<"\n";
            fout.close();
        }
        if(key == 2)
        {
            std::ofstream fout("Constom_data.txt",ios::app);
            fout<<adname<<"\n"<<adprice<<"\n"<<adadress<<"\n"<<admill<<"\n";
            fout.close();
        }
        if(key == 3)
        {
            std::ofstream fout("Deliver_data.txt",ios::app);
            fout<<adname<<"\n"<<adprice<<"\n"<<adadress<<"\n"<<admill<<"\n";
            fout.close();
        }
        if(key == 4)
        {
            std::ofstream fout("Order_data.txt",ios::app);
            fout<<adname<<"\n"<<adprice<<"\n"<<adadress<<"\n"<<admill<<"\n";
            fout.close();
        }

        cout<<"保存成功！"<<endl;
        cout<<"是【y】否【n】继续添加信息？"<<endl;

        cin>>flag;
        system("cls");

    }



}

//查询功能
int IOS::Find_Link(int key)
{
    char order_name[60];
    if(key == 0)
    {
        cout<<"请输入您要下单的店铺："<<endl;
        cin>>order_name;
        cout<<"[店铺信息]:"<<endl;
        cout<<setw(10)<<"序号ID"<<setw(20)<<"【1】店铺名称"<<setw(20)<<"【2】商品价格"<<setw(20)<<"【3】商品名称"<<setw(20)<<"【4】店铺评分"<<endl;
    }
    if(key == 4)
    {
        cout<<"请输入要查询订单的客户姓名："<<endl;
        cin>>order_name;
        cout<<"[查询结果]:"<<endl;
        cout<<setw(10)<<"订单编号"<<"【1】订单客户"<<setw(20)<<"【2】付款金额"<<setw(20)<<"【3】下单商品"<<setw(20)<<"【4】配送人员"<<endl;
    }


    Ios_Data *head = myfirst;
    while(head)
    {

        if(strcmp(head->getname(), order_name)==0)
        {
            cout<<setw(10)<<head->getid()<<setw(20)<<head->getname()<<setw(20)<<head->getprice()<<setw(20)<<head->getadress()<<setw(20)<<head->getmill()<<endl;
            return head->getprice();
            head = head->getnext();
        }
        if(key == 4)
        {
            cout<<"该订单不存在！"<<endl;
        }
        if(key == 0)
        {
            cout<<"没有该店铺！"<<endl;
        }
        return 1;

    }
    cout<<"暂无数据！"<<endl;
}
//删除功能
void IOS::Del_Link(int key)
{
    char dname[60];
    outall(key);//输出所有商品
    if(key == 1)
    {
        cout<<"请输入要删除的店铺名称:"<<endl;
    }
    if(key == 2)
    {
        cout<<"请输入要删除客户姓名:"<<endl;
    }
    if(key == 3)
    {
        cout<<"请输入要解雇配送员姓名:"<<endl;
    }
    if(key == 4)
    {
        cout<<"请输入要取消的订单客户姓名:"<<endl;
    }
    cin>>dname;
    Ios_Data *head = myfirst;
    Ios_Data *fhead = myfirst;//fhead用于一会指代head的前一个
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
                cout<<dname<<"信息已删除！"<<endl;
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


    //店铺
    IOS client;
    //客户
    IOS constom;
    //配送员
    IOS deliver;
    //订单
    IOS order;

    //读入数据
    client.read_txt(1);
    constom.read_txt(2);
    deliver.read_txt(3);
    order.read_txt(4);

    cout<<setiosflags(ios::left);//输出左对齐


    while(1)
    {
        //主菜单
        cout<<"     +---------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"     |                                          [外卖订餐管理系统]                                       |"<<endl;
        cout<<"     |                                                                                                   |"<<endl;
        cout<<"     |              *666.订餐                                                                            |"<<endl;
        cout<<"     |                                                                                                   |"<<endl;
        cout<<"     |              【提示】退出系统请按 0 正常退出，否则本次操作数据不会被保存！！！                    |"<<endl;
        cout<<"     |                                                                                                   |"<<endl;
        cout<<"     |                                                                                                   |"<<endl;
        cout<<"     |               __________订单管理________                                                          |"<<endl;
        cout<<"     |                                                                                                   |"<<endl;
        cout<<"     |              * 11.查询订单                                                                        |"<<endl;
        cout<<"     |              * 22.添加订单                                                                        |"<<endl;
        cout<<"     |              * 33.取消订单                                                                        |"<<endl;
        cout<<"     |              * 44.查看所有订单                                                                    |"<<endl;
        cout<<"     |                                                                                                   |"<<endl;
        cout<<"     |               ___________系统数据_________                                                        |"<<endl;
        cout<<"     |                                                                                                   |"<<endl;
        cout<<"     |              * 1.查看店铺                 * 4.查看客户               * 7.查看配送员               |"<<endl;
        cout<<"     |              * 2.添加店铺                 * 5.添加客户               * 8.添加配送员               |"<<endl;
        cout<<"     |              * 3.删除店铺                 * 6.删除客户               * 9.解雇配送员               |"<<endl;
        cout<<"     |                                                                                                   |"<<endl;
        cout<<"     |              * 0.退出                                                                             |"<<endl;
        cout<<"     +---------------------------------------------------------------------------------------------------+"<<endl;
        int i;
        cout<<".";
        cin>>i;
        switch(i)
        {
        case(1):
            system("cls");
            client.outall(1);
            system("pause");
            system("cls");
            break;
        case(2):
            system("cls");
            client.Add_Link(1);
            system("pause");
            system("cls");
            break;

        case(3):
            system("cls");
            client.Del_Link(1);
            system("pause");
            system("cls");
            break;
        case(4):
            system("cls");
            constom.outall(2);
            system("pause");
            system("cls");
            break;
        case(5):
            system("cls");
            constom.Add_Link(2);
            system("pause");
            system("cls");
            break;

        case(6):
            system("cls");
            constom.Del_Link(2);
            system("pause");
            system("cls");
            break;
        case(7):
            system("cls");
            deliver.outall(3);
            system("pause");
            system("cls");
            break;
        case(8):
            system("cls");
            deliver.Add_Link(3);
            system("pause");
            system("cls");
            break;

        case(9):
            system("cls");
            deliver.Del_Link(3);
            system("pause");
            system("cls");
            break;
        case(11):
            system("cls");
            order.Find_Link(4);
            system("pause");
            system("cls");
            break;
        case(22):
            system("cls");
            order.Add_Link(4);
            system("pause");
            system("cls");
            break;

        case(33):
            system("cls");
            order.Del_Link(4);
            system("pause");
            system("cls");
            break;
        case(44):
            system("cls");
            order.outall(4);
            system("pause");
            system("cls");
        case(666):
            system("cls");
            client.Find_Link(0);
            order.Add_Link(0);
            system("cls");
            break;
        case(0):
            //读入数据
            client.write_txt(1);
            constom.write_txt(2);
            deliver.write_txt(3);
            order.write_txt(4);
            system("cls");
            cout<<"【本次操作数据已保存】感谢您的使用，祝您用餐愉快！Bye-Bye- …^—^… ！"<<endl;
            return 0;
        default:
            cout<<"输入有误！请重新输入..."<<endl;
            system("pause");
            system("cls");
            continue;


        }
    }

}
