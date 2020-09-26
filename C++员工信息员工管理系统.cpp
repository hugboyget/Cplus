#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
using namespace std;
//定义员工类
class stall
{
protected:
    char num[60];         //工号
    char name[60];        //姓名
    char sex[20];         //性别

    float salary;         //月工资

    int id;               //工号
    stall *Mynext;        //指向下一个对象
public:
    stall();             //初始化变量
    stall(char num[60],char pname[],char psex[],float salary,int pid);//初始化对象不含指针
    stall(char num[60],char pname[],char psex[],float salary,int pid,stall *next);//初始化对象含指针

    //获得保护数据成员的函数
    char *getnum();
    char *getname();
    char *getsex();

    float getsalary();
    int   getid();

    stall *getnext();//获得节点指针
    void  setnext(stall *next);//设置节点指针
    void updatid();//id自减

};
//类中定义函数的实现

stall::stall()
{
    strcpy(name," ");
    strcpy(sex," ");
    strcpy(num," ");
    salary = 0;

    Mynext = NULL;
    id = 0;
}
stall::stall(char pnum[],char pname[],char psex[],float psalary,int pid)
{
    strcpy(name,pname);
    strcpy(sex,psex);
    strcpy(num,pnum);
    salary = psalary;

    Mynext = NULL;
    id = pid;
}
stall::stall(char pnum[],char pname[],char psex[],float psalary,int pid,stall *next)
{
    strcpy(name,pname);
    strcpy(sex,psex);
    strcpy(num,pnum);
    salary = psalary;

    Mynext = next;
    id = pid;
}
char *stall::getname()
{
    return name;
}
char *stall::getsex()
{
    return sex;
}
char *stall::getnum()
{
    return num;
}
float stall::getsalary()
{
    return salary;
}
stall *stall::getnext()
{
    return Mynext;
}
void stall::setnext(stall *next)
{
    Mynext = next;
}
int stall::getid()
{
    return id;
}
void stall::updatid()
{

    id = id - 1;
}

//定义管理类
class manage
{
private:
    stall *myfirst;
public:
    manage();//初始化
    manage(char npname[],char npsex[],char npnum[],float salary,int npid);//创建对象
    ~manage();

    void Add_stall();//添加
    void Find_stall();//查询
    void Sel_stall(int key);//选择输出指定数据/key=1输出工资最高员工/key=2输出工资最低员工/key=3输出工资平均值
    void Salary_mean();//所有员工工资平均值

    void outall();//输出所有员工信息


};
//类中定义函数的实现
manage::manage()
{
    myfirst = NULL;
}
manage::manage(char npname[],char npsex[],char npnum[],float salary,int npid)
{
    myfirst = new stall(npname,npsex,npnum,salary,npid);
}
manage::~manage()
{
    stall *next = myfirst,*temp;
    while(next != NULL)
    {
        temp = next;
        next = next->getnext();
        delete temp;

    }
    myfirst = NULL;
}
//输出打印所有员工信息功能
void manage::outall()
{
    int i=0;
    stall *head = myfirst;
    if(head == NULL)
    {
        cout<<"[目前暂无数据]"<<endl;
        cout<<endl;


        return;
    }
    cout<<setw(10)<<"序号"<<setw(20)<<"工号"<<setw(20)<<"姓名"<<setw(20)<<"性别"<<setw(20)<<"工资(k/月)"<<endl;
    cout<<"____________________________________________________________________________________________"<<endl;
    while(head)
    {
        i++;
        cout<<"|"<<setw(10)<<head->getid()<<setw(20)<<head->getnum()<<setw(20)<<head->getname()<<setw(20)<<head->getsex()<<setw(20)<<head->getsalary()<<"|"<<endl;

        head = head -> getnext();
    }
    cout<<"|__________________________________________________________________________________________|"<<endl;

    cout<<"总计"<<"-"<<i<<"-"<<"位员工\n\n"<<endl;
    cout<<endl;
    return;
}
//添加员工数据
void manage::Add_stall()
{

    outall();//输出所有数据
    int adid;
    float adsalary;
    char adname[60],adsex[20],adnum[60],flag[5];


    strcpy(flag,"y\0");
    while(strcmp(flag,"y\0") == 0)
    {

        //开始添加
        stall *p = myfirst;
        stall *rpeat = myfirst;//判断录入是否重复

        cout<<"=开始添加员工信息=\n"<<endl;

        cout<<"姓名:"<<endl;
        cin>>adname;

        cout<<"输入工号:"<<endl;
        cin>>adnum;



        while(rpeat)
        {
            if(strcmp(adname,rpeat->getname()) == 0 || strcmp(adnum,rpeat->getnum()) == 0)
            {
                cout<<"姓名:"<<adname<<"/工号:"<<adnum<<"已存在！"<<endl;
                system("pause");
                system("cls");
                return;
            }
            rpeat = rpeat -> getnext();
        }


        cout<<"性别:"<<endl;
        cin>>adsex;
        cout<<"工资(k/月):"<<endl;
        cin>>adsalary;

        if(p == NULL)
        {
            adid = 1;
            myfirst = new stall(adnum,adname,adsex,adsalary,adid);
        }
        else
        {
            while(p->getnext() != NULL)
            {
                p = p->getnext();
            }
            //员工序号
            adid = p->getid() + 1;
            p ->  setnext(new stall(adnum,adname,adsex,adsalary,adid,p->getnext())) ;

        }

        cout<<"保存成功！"<<endl;
        cout<<"是【y】否【n】继续添加员工？"<<endl;
        cin>>flag;
        //system("cls");
        //system("pause");
    }



}
//查询员工信息
void manage::Find_stall()
{
    char dname[60];
    cout<<"请输入要查询的员工姓名:"<<endl;
    cin>>dname;
    stall *head = myfirst;
    stall *fhead = head;//head的前一个
    int flag = 0;

    while(head)
    {

        if(strcmp(head->getname(), dname)==0)
        {
            cout<<"[查询结果]:"<<endl;
            cout<<setw(10)<<"序号"<<setw(20)<<"工号"<<setw(20)<<"姓名"<<setw(20)<<"性别"<<setw(20)<<"工资(k/月)"<<endl;
            cout<<setw(10)<<head->getid()<<setw(20)<<head->getnum()<<setw(20)<<head->getname()<<setw(20)<<head->getsex()<<setw(20)<<head->getsalary()<<endl;
            return;
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

    return;
}
//工资最高/最低员工
void manage::Sel_stall(int key)
{
    int flag = 0;
    float salary_max = 0,salary_min = 0;
    stall *head = myfirst;
    salary_max = head->getsalary();
    salary_min = head->getsalary();
    if(key == 1)//最高工资
    {
        while(head)
        {
            flag = 1;
            salary_min = head->getsalary();
            if(salary_min > salary_max)
            {
                salary_max = salary_min;
            }
            head = head -> getnext();


        }
        cout<<"[查询结果]:"<<"员工最【高】工资【￥:"<<setiosflags(ios::fixed) << setprecision(2)<<salary_max<<"k/月】"<<endl;//保留两位小数
    }
    if(key == 2)//最低工资
    {
        while(head)
        {
            flag = 1;
            salary_max = head->getsalary();
            if(salary_min > salary_max)
            {
                salary_min = salary_max;
            }

            head = head -> getnext();


        }
        cout<<"[查询结果]:"<<"员工最【低】工资【￥:"<<setiosflags(ios::fixed) << setprecision(2)<<salary_min<<"k/月】!"<<endl;//保留两位小数

    }


    if(flag == 0)
    {
        cout<<"暂无数据！"<<endl;
        system("pause");
        system("cls");
    }
    system("pause");
    system("cls");
    return;
}
void manage::Salary_mean()//计算工资平均值
{
    int flag = 0;
    int sum = 0;
    float sal_mean;
    float sal_toutal = 0;
    stall *head = myfirst;
    while(head)
    {
        flag = 1;
        sum++;
        sal_toutal = sal_toutal + head->getsalary();
        head = head->getnext();
    }
    if(flag == 0)
    {
        cout<<"暂无数据"<<endl;
    }
    sal_mean = sal_toutal / sum;
    cout<<"[计算结果]"<<endl<<"所有员工工资平均值为【￥"<<setiosflags(ios::fixed) << setprecision(2)<<sal_mean<<"k/月】"<<endl;
    system("pause");
    system("cls");
}

//主函数
int main()
{
    manage Ios;
    cout<<setiosflags(ios::left);//输出左对齐

    while(1)
    {
        //主菜单
        cout<<"     +--------------------------------------------------+"<<endl;
        cout<<"     |              [职工工资信息管理系统]              |"<<endl;
        cout<<"     |                                                  |"<<endl;
        cout<<"     |              * 1.显示职工信息                    |"<<endl;
        cout<<"     |              * 2.添加职工信息                    |"<<endl;
        cout<<"     |              * 3.查询职工信息                    |"<<endl;
        cout<<"     |              * 4.输出最高员工工资                |"<<endl;
        cout<<"     |              * 5.输出最低员工工资                |"<<endl;
        cout<<"     |              * 6.输出所有员工工资平均值          |"<<endl;
        cout<<"     |                                                  |"<<endl;
        cout<<"     |                                      [ 0.退出]   |"<<endl;
        cout<<"     +--------------------------------------------------+"<<endl;
        int i;
        cout<<".";
        cin>>i;
        switch(i)
        {
        case(1):
            system("cls");
            Ios.outall();
            break;
        case(2):
            system("cls");
            Ios.Add_stall();
            break;
        case(3):
            system("cls");
            Ios.Find_stall();
            break;
        case(4):
            system("cls");
            Ios.Sel_stall(1);
            break;
        case(5):
            system("cls");
            Ios.Sel_stall(2);
            break;
        case(6):
            system("cls");
            Ios.Salary_mean();
            break;
        case(0):
            return 0;
        default:
            cout<<"输入有误！请重新输入..."<<endl;
            system("pause");
            system("cls");
            continue;
        }
    }

}
