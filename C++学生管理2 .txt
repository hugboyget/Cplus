#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
using namespace std;
class person
{
public:


    char name[60];          //姓名

    double yuwen;         //语文成绩
    double shuxue;            //数学成绩
    double yingyu;         //英语成绩

    double score;           //总成绩

    int num;                //自动生成学号


    person *mynext;       //指向下一个对象

    person();             //初始化变量
    person(char the_name[],double the_yuwen,double the_shuxue,double the_yingyu,double the_score,int num);
    person(char the_name[],double the_yuwen,double the_shuxue,double the_yingyu,double score,int num,person *next);



    char *getname();

    double getyw();//获得语文成绩
    double getsx();//获得数学成绩
    double getyy();//获得英语成绩

    double getsc();//获得总成绩

    int    getnum();//获得语学号

    person *getnext();//获得下一个节点

    void  setnext(person *next);//设置下一个节点

    void updatid();//学号更新

};
person::person()
{
    strcpy(name,"");
    yuwen = 0;
    shuxue = 0;
    yingyu = 0;
    score = 0;
    mynext = NULL;
    num = 190100;
}
person::person(char the_name[],double the_yuwen,double the_shuxue,double the_yingyu,double the_score,int the_num)

{
    strcpy(name,the_name);

    yuwen = the_yuwen;
    shuxue = the_shuxue;
    yingyu = the_yingyu;
    score = the_score;

    mynext = NULL;//下一个节点为空
    num = the_num;
}
//初始化
person::person(char the_name[],double the_yuwen,double the_shuxue,double the_yingyu,double the_score,int the_num,person *next)
{
    strcpy(name,the_name);

    yuwen = the_yuwen;
    shuxue = the_shuxue;
    yingyu = the_yingyu;
    score = the_score;

    mynext = next;
    num = the_num;
}
char *person::getname()
{
    return name;
}
double person::getyw()
{
    return  yuwen;
}
double person::getsx()
{
    return  shuxue;
}
double person::getyy()
{
    return  yingyu;
}
double person::getsc()
{
    return  score;
}
person *person::getnext()
{
    return mynext;
}
void person::setnext(person *next)
{
    mynext = next;
}
int person::getnum()
{
    return num;
}
void person::updatid()
{
    num = num - 1;
}
//定义功能表类
class Func_Table
{
private:
    person *myfirst;
public:
    //初始化函数
    Func_Table();
    Func_Table(char jname[],double jyuwen,double jshuxue,double jyingyu,double jscore,int jnum);
    ~Func_Table();

    //功能函数
    void output_student(int flg);//输出学生信息
    void New_student();//在有序的系统中加入学生信息
    void Find_max_min();//查找最高分学生
    void Display_chinese(int flg);//成绩情况、分段统计

};

Func_Table::Func_Table()
{
    myfirst = NULL;
}
Func_Table::Func_Table(char jname[],double jyuwen,double jshuxue,double jyingyu,double jscore,int jnum)
{
    myfirst = new person(jname,jyuwen,jshuxue,jyingyu,jscore,jnum);
}
Func_Table::~Func_Table()
{
    person *next = myfirst,*temp;
    while(next != NULL)
    {
        temp = next;
        next = next->getnext();
        delete temp;

    }
    myfirst = NULL;
}
//查找最高分学生
void Func_Table::Find_max_min()
{
    int max_score = 0;
    int min_score = 0;
    person *head1 = myfirst;
    person *f1 = myfirst;
    while(head1!=NULL)
    {
        if(head1->getsc() > max_score)
        {
            max_score = head1 -> getsc();
            f1 = head1;
        }

        head1 = head1->getnext();

    }
    person *head2 = myfirst;
    person *f2 = myfirst;
    while(head2!=NULL)
    {
        if(head2->getsc() < max_score)
        {
            min_score = head2 -> getsc();
            f2 = head2;
        }

        head2 = head2->getnext();

    }

    cout<<"总分最高分["<<max_score<<"]分！该学生信息如下："<<endl;
    cout<<"_学号_________姓名___________语文___________数学___________英语___________总分_"<<endl;
    cout<<setw(15) <<f1->getnum()<<setw(15) <<f1->getname()<<setw(15)<<f1->getyw()<<
    setw(15)<<f1->getsx()<<setw(15)<<f1->getyy()<<setw(15)<<f1->getsc()<<endl;
    cout<<endl<<endl<<endl;
    cout<<"总分最低分["<<min_score<<"]分！该学生信息如下："<<endl;
    cout<<"_学号_________姓名___________语文___________数学___________英语___________总分_"<<endl;
    cout<<setw(15) <<f2->getnum()<<setw(15) <<f2->getname()<<setw(15)<<f2->getyw()<<
    setw(15)<<f2->getsx()<<setw(15)<<f2->getyy()<<setw(15)<<f2->getsc()<<endl;
    return;
}

//输出学生信息
void Func_Table::output_student(int flg)
{
    int i=0;
    double totall,mean;
    person *head = myfirst;
    if(head == NULL)
    {
        cout<<"数据为空！"<<endl;
        cout<<endl;


        return;
    }
    if(flg == 1)
    {
     cout<<"_学号_________姓名___________语文___________数学___________英语___________总分_"<<endl;
    }
    if(flg == 2)
    {
     cout<<"_学号_________姓名___________总分___________三科平均分_"<<endl;
    }
    while(head)
    {
        i++;
        if(flg == 1)
        {cout<<setw(15) <<head->getnum()<<setw(15) <<head->getname()<<setw(15)<<head->getyw()
        <<setw(15)<<head->getsx()<<setw(15)<<head->getyy()<<setw(15)<<head->getsc()<<endl;
        }
        if(flg == 2)
        {
            mean = head->getsc()  /  3;
            cout<<setw(15) <<head->getnum()<<setw(15) <<head->getname()<<setw(15)<<head->getsc()
            <<setw(15)<<mean<<endl;
        }
        head = head -> getnext();
    }
    if(flg == 1){return;}
    cout<<endl;
    system("pause");
    system("cls");
    return;
}

//录入学生信息
void Func_Table::New_student()
{



    int nnum;
   int i = 190100;//用于自动生成学号

    //用于存放输入的数据
    char nna[60];
    double nyw;
    double nsx;
    double nyy;
    double nsc;

    person *p = myfirst;

    cout<<"姓名:"<<endl;
    cin>>nna;
    cout<<"语文成绩:"<<endl;
    cin>>nyw;
    cout<<"数学成绩:"<<endl;
    cin>>nsx;
    cout<<"英语成绩:"<<endl;
    cin>>nyy;

    nsc = nyw + nsx + nyy;//计算总分

    if(p == NULL)
    {
        nnum =  i;//生成学号编号
        myfirst = new person(nna,nyw,nsx,nyy,nsc,nnum);
    }
    else
    {
        nnum = i + 1;
        while(p->getnext() != NULL)
        {

            p = p->getnext();
        }
        nnum = p->getnum() + 1;
        p ->  setnext(new person(nna,nyw,nsx,nyy,nsc,nnum,p->getnext())) ;

    }

    cout<<"保存成功！"<<endl;
    system("pause");
    system("cls");

}
//成绩情况成绩统计
void Func_Table::Display_chinese(int flg)
{
    int i=0;
    double yw;//语文成绩
    double mean = 0,a = 0,b = 0,c = 0,d = 0,e = 0,f = 0;
    person *head = myfirst;
    if(head == NULL)
    {
        cout<<"数据为空！"<<endl;
        cout<<endl;


        return;
    }
    if(flg == 1)
    {
     cout<<"_____________________________|语文成绩情况|______________________________"<<endl;
      cout<<setw(15)<<"学号"<<setw(15)<<"姓名"<<setw(15)<<"语文成绩"<<setw(15)<<"成绩情况"<<endl;
    }
    if(flg == 2)
    {
     cout<<"_____________________________|成绩分段统计|______________________________"<<endl;
    }
    while(head)
    {
        i++;
        if(flg == 1)
        {
          yw = head->getyw();
         if(yw>=90 && yw<= 100)
        {
           cout<<"|"<<setw(15) <<head->getnum()<<setw(15) <<head->getname()<<setw(15)<<head->getyw()<<setw(15)<<"优秀！"<<"|"<<endl;
        }
        else if(yw>=75&&yw<=89)
        {
          cout<<"|"<<setw(15) <<head->getnum()<<setw(15) <<head->getname()<<setw(15)<<head->getyw()<<setw(15)<<"良好！"<<"|"<<endl;
        }
        else if(yw>=60&&yw<=74)
        {
           cout<<"|"<<setw(15) <<head->getnum()<<setw(15) <<head->getname()<<setw(15)<<head->getyw()<<setw(15)<<"及格！"<<"|"<<endl;
        }
        else if(yw<=60)
        {
           cout<<"|"<<setw(15) <<head->getnum()<<setw(15) <<head->getname()<<setw(15)<<head->getyw()<<setw(15)<<"不及格！"<<"|"<<endl;
        }

        }
        if(flg == 2)
        {
            mean = head->getsc()  /  3;

           if(mean== 100)
        {
            a++;
        }
        else if(mean>=90&&mean<=99)
        {
            b++;
        }
        else if(mean>=80&&mean<=89)
        {
            c++;
        }
        else if(mean>=70&&mean<=79)
        {
            d++;
        }
        else if(mean>=60&&mean<=69)
        {
            e++;
        }
        else if(mean>=0&&mean<=59)
        {
            f++;
        }

        }

        head = head -> getnext();
    }
    if(flg == 2)
    {
        cout<<"<满分人数>"<<a<<"人"<<endl;
        cout<<"90-99分数段:"<<b<<"人"<<endl;
        cout<<"80-89分数段:"<<c<<"人"<<endl;
        cout<<"70-79分数段:"<<d<<"人"<<endl;
        cout<<"60-69分数段:"<<e<<"人"<<endl;
        cout<<"00-60分数段:"<<f<<"人"<<endl;

    }
    cout<<endl;
    system("pause");
    system("cls");
    return;
}

//主函数
int main()
{
    Func_Table Ios;
    cout<<setiosflags(ios::left);//输出靠左对齐
    while(1)
    {
        //主菜单
        cout<<"==============================================================================="<<endl;
        cout<<"  |                            >>>学生成绩管理系统<<<                       |  "<<endl;
        cout<<"==============================================================================="<<endl;
        cout<<"                                                                               "<<endl;
        cout<<"                                                                               "<<endl;
        cout<<"【1】.浏览学生信息                   【4】.语文成绩情况                        "<<endl;
        cout<<"【2】.录入学生信息                   【5】.浏览学生平均分                      "<<endl;
        cout<<"【3】.查找最高分/最低分学生          【6】.成绩统计                            "<<endl;
        cout<<"                                                                               "<<endl;
        cout<<"                                                                   【0.退出】  "<<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        int i;
        cout<<".";
        cin>>i;
        switch(i)
        {
        case(1):
            system("cls");
            Ios.output_student(1);
            system("pause");
            system("cls");
            break;
        case(2):
            system("cls");
            Ios.New_student();
            break;
        case(3):
            system("cls");
            Ios.Find_max_min();
            system("pause");
            system("cls");
            break;
        case(4):
            system("cls");
            Ios.Display_chinese(1);
            break;
        case(5):
            system("cls");
            Ios.output_student(2);
            break;
        case(6):
            system("cls");
             Ios.Display_chinese(2);
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



