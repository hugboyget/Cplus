#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
using namespace std;
class student
{
public:


    char name[60];        //姓名





    double chinese;         //语文成绩
    double math;            //高等数学成绩
    double english;         //英语成绩
    double spe;             //专业成绩

     int id;               //数据序号


    student *Mynext;       //指向下一个对象

    student();             //初始化变量
    student(char pname[],double pchinese,double pmath,double penglish,double pspe,int pid);
    student(char pname[],double pchinese,double pmath,double penglish,double pspe,int pid,student *next);

    //获得学生相应数据的函数，用对应变量的前两个字母简写
    char *getna();
    double getch();
    double getma();
    double geten();
    double getsp();
    int    getid();

    student *getnext();//获得下一个节点

    void  setnext(student *next);//设置该节点的下一个节点

    void updatid();//id自减1

};
student::student()
{
    strcpy(name,"");
    chinese = 0;
    math = 0;
    english = 0;
    spe = 0;
    Mynext = NULL;
    id = 0;
}
student::student(char pname[],double pchinese,double pmath,double penglish,double pspe,int pid)
{
    strcpy(name,pname);

    chinese = pchinese;
    math = pmath;
    english = penglish;
    spe = pspe;

    Mynext = NULL;//下一个节点为空
    id = pid;
}
student::student(char pname[],double pchinese,double pmath,double penglish,double pspe,int pid,student *next)
{
    strcpy(name,pname);
    chinese = pchinese;
    math = pmath;
    english = penglish;
    spe = pspe;

    Mynext = next;//下一个节点为传入的变量next
    id = pid;
}
char *student::getna()
{
    return name;
}
double student::getch()
{
    return  chinese;
}
double student::getma()
{
    return  math;
}
double student::geten()
{
    return  english;
}
double student::getsp()
{
    return  spe;
}
student *student::getnext()
{
    return Mynext;
}
void student::setnext(student *next)
{
    Mynext = next;
}
int student::getid()
{
    return id;
}
void student::updatid()
{
    id = id - 1;
}
class DataBook
{
private:
    student *myfirst;
public:
    DataBook();//初始化
    DataBook(char npname[],double pchinese,double pmath,double penglish,double pspe,int npid);//创建对象
    ~DataBook();
    void outall();//查看
    void Add_student();//添加

    void Edi_student();//修改
    void Del_student();//删除
    void Log_Out();//退出


};

DataBook::DataBook()
{
    myfirst = NULL;
}
DataBook::DataBook(char pname[],double pchinese,double pmath,double penglish,double pspe,int pid)
{
    myfirst = new student(pname,pchinese,pmath,penglish,pspe,pid);
}
DataBook::~DataBook()
{
    student *next = myfirst,*temp;
    while(next != NULL)
    {
        temp = next;
        next = next->getnext();
        delete temp;

    }
    myfirst = NULL;
}
//输出所有学生信息
void DataBook::outall()
{
    int i=0;
    student *head = myfirst;
    if(head == NULL)
    {
        cout<<"[目前暂无数据]"<<endl;
        cout<<endl;


        return;
    }
    cout<<setw(15)<<"ID"<<setw(15)<<"姓名"<<setw(15)<<"大学语文"<<setw(15)<<"高等数学"<<setw(15)<<"大学英语"<<setw(15)<<"专业成绩"<<endl;
    cout<<"____________________________________________________________________________________________"<<endl;
    while(head)
    {
        i++;

        cout<<"|"<<setw(15) <<head->getid()<<setw(15) <<head->getna()<<setw(15)<<setprecision(4) <<head->getch()<<setw(15)<<setprecision(4) <<head->getma()<<setw(15)<<setprecision(4) <<head->geten()<<setw(15)<<setprecision(4) <<head->getsp()<<"|"<<endl;
        head = head -> getnext();
    }
    cout<<"|__________________________________________________________________________________________|"<<endl;
    //cout<<"____________"<<endl;
    cout<<"总计"<<"-"<<i<<"-"<<"人\n\n"<<endl;
    cout<<endl;
    return;
}

//添加学生成绩
void DataBook::Add_student()
{


    int adid,tpcode;
    int i = 0;

    char adname[60];
    double adchinese;
    double admath;
    double adenglish;
    double adspe;

    char flag[5];//判断选择状态

    strcpy(flag,"y\0");
    while(strcmp(flag,"y\0") == 0)
    {

        student *p = myfirst;
        cout<<"学生姓名:"<<endl;
        cin>>adname;
        cout<<"大学语文成绩:"<<endl;
        cin>>adchinese;
        cout<<"高等数学成绩:"<<endl;
        cin>>admath;
        cout<<"大学英语成绩:"<<endl;
        cin>>adenglish;
        cout<<"专业成绩:"<<endl;
        cin>>adspe;

        i = i+1;
        adid = i;
        if(p == NULL)
        {
            myfirst = new student(adname,adchinese,admath,adenglish,adspe,adid);
        }
        else
        {
            while(p->getnext() != NULL)
            {
                p = p->getnext();
            }
            p ->  setnext(new student(adname,adchinese,admath,adenglish,adspe,adid,p->getnext())) ;

        }
        cout<<"是【y】否【n】继续添加联系人？"<<endl;
        cin>>flag;

    }
    cout<<"保存成功！"<<endl;

    system("pause");
    system("cls");

}
//删除学生信息
void DataBook::Del_student()
{
    char dname[60];
    outall();//输出所有联系人
    cout<<"请输入要删除的学生姓名:"<<endl;
    cin>>dname;
    student *head = myfirst;
    student *fhead = myfirst;//fhead用于一会指代head的前一个
    int flag = 0;

    while(head)
    {

        if(strcmp(head->getna(), dname)==0)
        {
            cout<<"[DelData]:"<<endl;
             cout<<setw(10)<<head->getid()<<setw(20)<<head->getna()<<setw(20)<<head->getch()<<setw(20)
                <<head->getma()<<setw(20)<<head->geten()<<setw(20)<<head->getsp()<<endl;

            fhead->setnext(head->getnext());//让head的前一个节点指向head的后一个节点；
            head = NULL;

            fhead = fhead->getnext();//从fhead开始ID自减一

            while(fhead)
            {
                //cout<<"进入循环-自减"<<endl;
                fhead->updatid();
                fhead = fhead->getnext();
            }
            //当删除的为第一个联系人时
            if(flag == 0)
            {
                myfirst = myfirst -> getnext();
                cout<<"学生【"<<dname<<"】的成绩删除成功！"<<endl;
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
        cout<<"学生【"<<dname<<"】的成绩删除成功！"<<endl;
        system("pause");
        system("cls");
    }

    return;
}
//修改编辑学生信息
void DataBook::Edi_student()
{
    char ename[60];
    outall();//输出所有联系人
    cout<<"请输入要编辑的联系人的姓名:"<<endl;
    cin>>ename;
    //system("pause");
    system("cls");
    student *head = myfirst;
    int flag = 0;
    while(head)
    {
        if(flag == 2)//修改完成已无需再遍历
        {
            break;
        }

        if(strcmp(head->getna(), ename)==0)
        {

            cout<<"Old-Data:"<<endl;
            cout<<setw(10)<<head->getid()<<setw(20)<<head->getna()<<setw(20)<<head->getch()<<setw(20)
                <<head->getma()<<setw(20)<<head->geten()<<setw(20)<<head->getsp()<<endl;

            while(1)
            {
                int i;
                char ename[20];
                double score;
                cout<<"     +-----------------------------------+"<<endl;
                cout<<"     |   [请继续选择您要修改的内容/退出] |"<<endl;
                cout<<"     |                                   |"<<endl;
                cout<<"     |              - 1.姓名             |"<<endl;
                cout<<"     |              - 2.大学语文成绩     |"<<endl;
                cout<<"     |              - 3.高等数学成绩     |"<<endl;
                cout<<"     |              - 4.大学英语成绩     |"<<endl;
                cout<<"     |              - 5.专业课成绩       |"<<endl;
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
                    cout<<"姓名修改为:"<<endl;
                    cin>>head->name;
                    system("cls");
                    break;
                case 2:
                    cout<<"新大学语文成绩:"<<endl;
                    cin>>head->chinese;
                    system("cls");
                    break;
                case 3:
                    cout<<"新高等数学成绩:"<<endl;
                    cin>>head->math;
                    system("cls");
                    break;
                case 4:
                    cout<<"新大学英语成绩:"<<endl;
                    cin>>head->english;
                    system("cls");
                    break;
                case 5:
                    cout<<"新专业课成绩:"<<endl;
                    cin>>head->spe;
                    system("cls");
                    break;
                }
                //当修改的为第一个人时
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
        cout<<"你还未添加该联系人！"<<endl;
        system("pause");
        system("cls");
    }
    else
    {
        system("cls");
        cout<<"New-Data:"<<endl;
        cout<<setw(10)<<head->getid()<<setw(20)<<head->getna()<<setw(20)<<head->getch()<<setw(20)
                <<head->getma()<<setw(20)<<head->geten()<<setw(20)<<head->getsp()<<endl;
        cout<<"__________"<<endl;
         cout<<"学生【"<<ename<<"】的信息修改成功！"<<endl;
        system("pause");
        system("cls");
    }
    return;
}
//主函数
int main()
{
    DataBook call;
    cout<<setiosflags(ios::left);//输出靠左对齐
    while(1)
    {
        //主菜单
        cout<<"     +--------------------------------------------------+"<<endl;
        cout<<"     |              [学生成绩管理系统]                  |"<<endl;
        cout<<"     |                                                  |"<<endl;
        cout<<"     |              * 1.查看学生成绩                    |"<<endl;
        cout<<"     |              * 2.添加学生成绩                    |"<<endl;
        cout<<"     |              * 3.修改学生成绩                    |"<<endl;
        cout<<"     |              * 4.删除学生成绩                    |"<<endl;
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
            call.Add_student();
            break;
        case(3):
            system("cls");
            call.Edi_student();
            break;
        case(4):
            system("cls");
            call.Del_student();
            break;
        case(0):
            return 0;
        default:
            cout<<"输入有误！请重新输入..."<<endl;
            continue;
        }
    }
    return 0;

}


