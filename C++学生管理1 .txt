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
    void outall(int key);//key=1查看所有成绩key=2平均成绩
    void Add_student();//添加

    void max_min(int key);//key=1最高分key=2最低分
    void Judge_chinese(int key);//key = 2分段统计 key = 1评判成绩
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
//输出所有学生信息key = 1输出所有、key = 2查看平均分
void DataBook::outall(int key)
{
    int i=0;
    student *head = myfirst;
    if(head == NULL)
    {
        cout<<"[目前暂无数据]"<<endl;
        cout<<endl;


        return;
    }
    if(key == 1)
    {
     cout<<setw(15)<<"ID"<<setw(15)<<"姓名"<<setw(15)<<"大学语文"<<setw(15)<<"高等数学"<<setw(15)<<"大学英语"<<setw(15)<<"专业成绩"<<endl;
    cout<<"____________________________________________________________________________________________"<<endl;
    }

    while(head)
    {
        i++;
        if(key == 1)
        {
         cout<<"|"<<setw(15) <<head->getid()<<setw(15) <<head->getna()<<setw(15)<<setprecision(4) <<head->getch()<<setw(15)<<setprecision(4) <<head->getma()<<setw(15)<<setprecision(4) <<head->geten()<<setw(15)<<setprecision(4) <<head->getsp()<<"|"<<endl;

        }
        else
        {
        double all_score,mean_score;
        all_score = head->getch()  +  head->getma()   + head->geten()  + head->getsp();
        mean_score = all_score / 4;
        cout<<"学生姓名："<<setw(15)<<head->getna()<<"学生总分："<<setw(15)<<all_score<<"学生各科平均分："<<setw(5)<<mean_score<<endl;

        }
        head = head -> getnext();

    }
    if (key == 1)
    {cout<<"|__________________________________________________________________________________________|"<<endl;
    //cout<<"____________"<<endl;
    cout<<"总计"<<"-"<<i<<"-"<<"人\n\n"<<endl;
    cout<<endl;return;}

    system("pause");
    system("cls");
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
//评判学生语文成绩/分段统计
void DataBook::Judge_chinese(int key)
{

    int a,b,c,d,e,f;
    a=0;b=0;c=0;d=0;e=0;f=0;
    double score;
    student *head = myfirst;
    if(head == NULL)
    {
        cout<<"[目前暂无数据]"<<endl;
        cout<<endl;


        return;
    }
    if(key == 1)
    {
        cout<<setw(15)<<"ID"<<setw(15)<<"姓名"<<setw(15)<<"语文成绩"<<setw(15)<<"评判结果"<<endl;
    }


    while(head)
    {


        score = head->getch();
        if(key == 1)
        {
         if(score>=90 && score<= 100)
        {
           cout<<"|"<<setw(15) <<head->getid()<<setw(15) <<head->getna()<<setw(15)<<head->getch()<<setw(15)<<"优秀！"<<"|"<<endl;
        }
        else if(score>=75&&score<=89)
        {
           cout<<"|"<<setw(15) <<head->getid()<<setw(15) <<head->getna()<<setw(15)<<head->getch()<<setw(15)<<"良好！"<<"|"<<endl;
        }
        else if(score>=60&&score<=74)
        {
           cout<<"|"<<setw(15) <<head->getid()<<setw(15) <<head->getna()<<setw(15)<<head->getch()<<setw(15)<<"及格！"<<"|"<<endl;
        }
        else if(score<=60)
        {
            cout<<"|"<<setw(15) <<head->getid()<<setw(15) <<head->getna()<<setw(15)<<head->getch()<<setw(15)<<"不及格！"<<"|"<<endl;
        }

        }
        if(key == 2)
        {


        if(score== 100)
        {
            a++;
        }
        else if(score>=90&&score<=99)
        {
            b++;
        }
        else if(score>=80&&score<=89)
        {
            c++;
        }
        else if(score>=70&&score<=79)
        {
            d++;
        }
        else if(score>=60&&score<=69)
        {
            e++;
        }
        else if(score>=0&&score<=59)
        {
            f++;
        }
        }
        head = head -> getnext();
    }



if(key == 2)
    {cout<<"____________成绩分段统计_____________"<<endl;
    cout<<"满分[100]分："<<a<<"位同学！"<<endl;
    cout<<"[00]~[59]分："<<f<<"位同学！"<<endl;
    cout<<"[60]~[69]分："<<e<<"位同学！"<<endl;
    cout<<"[70]~[79]分："<<d<<"位同学！"<<endl;
    cout<<"[80]~[89]分："<<c<<"位同学！"<<endl;
    cout<<"[90]~[99]分："<<b<<"位同学！"<<endl;
    cout<<endl;}
    system("pause");
    system("cls");
    return;
}
//专业成绩最高分最低分
void DataBook::max_min(int key)
{

    int flag = 0;
    float score_max = 0,score_min = 0;
    student *head = myfirst;
    score_max = head->getsp();
    score_min = head->getsp();
    if(key == 1)//最高分
    {
        while(head)
        {
            flag = 1;
            score_min = head->getsp();
            if(score_min > score_max)
            {
                score_max = score_min;
            }
            head = head -> getnext();


        }
        cout<<"[查询结果]:"<<"专业成绩最高分最【高】分【"<<setiosflags(ios::fixed) << setprecision(2)<<score_max<<"】分!"<<endl;//保留两位小数
    }
    if(key == 2)//最低工资
    {
        while(head)
        {
            flag = 1;
            score_max = head->getsp();
            if(score_min > score_max)
            {
                score_min = score_max;
            }

            head = head -> getnext();


        }
        cout<<"[查询结果]:"<<"学生专业成绩最【低】分【"<<setiosflags(ios::fixed) << setprecision(2)<<score_min<<"】分!"<<endl;//保留两位小数

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
        cout<<"     |              * 3.查找学生最高分                  |"<<endl;
        cout<<"     |              * 4.语文成绩评判                    |"<<endl;
        cout<<"     |              * 5.计算学生成绩平均分并输出        |"<<endl;
        cout<<"     |              * 6.查找学生最低分                  |"<<endl;
        cout<<"     |              * 7.学生成绩分段统计                |"<<endl;
        cout<<"     |                                                  |"<<endl;
        cout<<"     |                                 [ * 0.退出 ]     |"<<endl;
        cout<<"     +--------------------------------------------------+"<<endl;
        int i;
        cout<<".";
        cin>>i;
        switch(i)
        {
        case(1):
            system("cls");
            call.outall(1);
            break;
        case(2):
            system("cls");
            call.Add_student();
            break;
        case(3):
            system("cls");
            call.max_min(1);
            break;
        case(4):
            system("cls");
            call.Judge_chinese(1);
            break;
        case(5):
            system("cls");
            call.outall(2);
            break;
        case(6):
            system("cls");
            call.max_min(2);
            break;
        case(7):
            system("cls");
            call.Judge_chinese(2);
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


