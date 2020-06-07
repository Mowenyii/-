#include <iostream>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <tchar.h>
using namespace std;

#define C 60
#define L 20
#define Class_NUM 200
#define prime 13

//��Ҫ������ʹ����wchar_t*��delete[]�ͷ��ڴ�
wchar_t *multiByteToWideChar(const string &pKey)
{

    const char *pCStrKey = pKey.c_str();

    //��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�

    int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);

    wchar_t *pWCStrKey = new wchar_t[pSize];

    //�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���

    MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);

    return pWCStrKey;
}
class Matcher
{
public:
    Matcher(wchar_t s1[], int n1, wchar_t s2[], int n2)
    {
        this->s1 = s1;
        this->s2 = s2;
        this->n1 = n1;
        this->n2 = n2;
        buf = new int *[n1 + 1];
        for (int i = 0; i <= n1; i++)
        {
            buf[i] = new int[n2 + 1];
            for (int j = 0; j <= n2; j++)
            {
                buf[i][j] = 0;
            }
        }
    }

    ~Matcher()
    {
        for (int i = 0; i <= n1; i++)
        {
            delete[] buf[i];
        }
        delete[] buf;
    }

    /*�������ƶ�*/
    double match()
    {
        //���Ÿ���
        sort(s1, s1 + n1);
        sort(s2, s2 + n2);

        int maxCommonLen = matchAct(n1, n2);
        return 2 * maxCommonLen * 1.0 / (n1 + n2);
    }

private:
    wchar_t *s1;
    wchar_t *s2;
    int n1;
    int n2;
    int **buf;

    /*��������������г���*/
    int matchAct(int n1, int n2)
    {
        if (n1 <= 0 || n2 <= 0)
        {
            return 0;
        }

        //Dynamic Planning--���ȥ����������if��������ͨ�ķ���
        if (buf[n1 - 1][n2 - 1] == 0)
        {
            buf[n1 - 1][n2 - 1] = matchAct(n1 - 1, n2 - 1);
        }

        if (buf[n1 - 1][n2] == 0)
        {
            buf[n1 - 1][n2] = matchAct(n1 - 1, n2);
        }

        if (buf[n1][n2 - 1] == 0)
        {
            buf[n1][n2 - 1] = matchAct(n1, n2 - 1);
        }

        if (s1[n1 - 1] == s2[n2 - 1])
        {
            return buf[n1 - 1][n2 - 1] + 1;
        }

        return max(buf[n1 - 1][n2],
                   buf[n1][n2 - 1]);
    }
};
class StuHomework
{
public:
    int stuNo;
    string stuWork;
    StuHomework *next;
    StuHomework()
    {
        next = NULL;
    }
    StuHomework(int n, string s)
    {
        stuNo = n;
        stuWork = s;
        next = NULL;
    }
    StuHomework(int n, string s, StuHomework *p)
    {
        stuNo = n;
        stuWork = s;
        next = p;
    }
};
void append(StuHomework *&head, int n, string s)
{
    head->next = new StuHomework(n, s, head->next);
}

//ջ��ADT
template <typename E>
class Stack
{
public:
    Stack() {}
    virtual ~Stack() {}

    virtual void clear() = 0;

    virtual void push(const E &it) = 0;

    virtual E pop() = 0;

    virtual const E &topValue() const = 0;

    virtual int length() const = 0;
};
//˳��ջ���ʵ��
template <typename E>
class AStack : public Stack<E>
{
private:
    int maxSize;
    int top;
    E *listArray;

public:
    AStack(int size = 50)
    {
        maxSize = size;
        top = 0;
        listArray = new E[size];
    }

    ~AStack() { delete[] listArray; }

    void clear() { top = 0; }

    void push(const E &it)
    {

        listArray[top++] = it;
    }

    E pop()
    {

        return listArray[--top];
    }

    const E &topValue() const
    {

        return listArray[top - 1];
    }

    int length() const { return top; }

    bool isEmpty()
    {
        if (top == 0)
            return true;
        else
            return false;
    }
};
class GradeNode
{
public:
    int sno;
    int Ugrade;
    int Fgrade;
    double Grade;

    GradeNode *lc;
    GradeNode *rc;
    GradeNode()
    {
        sno = -1;
        Ugrade = -1;
        Fgrade = -1;
        Grade = -1;
    }
    GradeNode(int s, int u, int f, double g)
    {
        sno = s;
        Ugrade = u;
        Fgrade = f;
        Grade = 1.0 * g;
        lc = NULL;
        rc = NULL;
    }
    ~GradeNode() {}
    void setVal(int rate, int u, int f)
    {
        Fgrade = f;
        Ugrade = u;
        Grade = 1.0 * (u * rate + f * (100 - rate)) / 100;
    }
};
class GBST
{
public:
    GradeNode *root;
    GBST() { root = NULL; }
    ~GBST() {}
    void insert(int n, int u, int f, double g)
    {
        GradeNode *s = new GradeNode(n, u, f, g);
        if (root == NULL)
            root = s;
        else
        {
            GradeNode *temp = root;
            while (temp != NULL)
            {
                if (n < temp->sno)
                {
                    if (temp->lc == NULL)
                    {
                        temp->lc = s;
                        return;
                    }
                    else
                    {
                        temp = temp->lc;
                    }
                }
                if (n > temp->sno)
                {
                    if (temp->rc == NULL)
                    {
                        temp->rc = s;
                        return;
                    }
                    else
                        temp = temp->rc;
                }
                if(n==temp->sno)break;
            }
        }
    }
};

class CnoNode
{
public:
    int cno;
    int rate;
    GradeNode *next;
    CnoNode(int c, int r)
    {
        cno = c;
        rate = r;
        next = NULL;
    }
    CnoNode()
    {
        cno = -1;
        rate = -1;
        next = NULL;
    }
    ~CnoNode() {}
};

int h1(int s)
{
    return s % Class_NUM;
}
int h2(int k)
{
    return (prime - k % prime);
}

typedef struct _users
{
    char id[9];
    char passwds[9];
} MANuser;
class HashNode
{
public:
    string id;
    string passwds;
    HashNode *next;
    HashNode(string d, string s)
    {
        id = d;
        passwds = s;
        next = NULL;
    }
    HashNode()
    {
        next = NULL;
    }
    ~HashNode() {}
};
int h(string s, int k)
{
    int sum = 0;
    for (int i = 0; i < strlen(s.c_str()); i++)
    {
        sum *= 10;
        sum += (int(s[i]) - 49);
    }
    return sum % k;
}
MANuser Mo;
MANuser Wenyi;
bool isAdded;
int Cno;
int rate;
CnoNode *cnohash = new CnoNode[Class_NUM];
GBST *mybst = new GBST[Class_NUM];
HashNode *myhash = new HashNode[2000];
void welcomeUI();              //��ӭ����
void Setcursors(int x, int y); //���ù��
void HideCursor();
void PlayUsers();                 //�û�ע�� ��¼����
void RemoveScreen();              //����
void UserPassword(MANuser &mans); //ע��
void Login(MANuser &mans);        //��¼
void TeacherDo();                 //��ʦ����
void SetCnoRate();                //���ÿγ̺�������ʱ�ı���
void SetGrade();                  //�޸ĳɼ�
void Continue_End();              //�����޸ĳɼ����˳�
void Check_Grade();               
void PublishHomework();           //������ҵ
void Homework_Cal();              //ͳ����ҵ���
void Homework_Check();            //�ж���ҵ�Ƿ�Ϯ
void welcomeUI()
{

    //Setcursors(1,0);
    for (int i = 1; i < L - 1; ++i)
    {
        Setcursors(1, 0 + i);
        for (int j = 1; j < C - 1; ++j)
        {
            if (i == 1 || i == L - 2)
            {
                cout << "-";
            }
            else if (i == 3)
            {
                cout << "-";
            }
            if (i != 1 && (j == 1 || j == (C - 2)))
            {
                Setcursors(0 + j, 0 + i);
                cout << "|";
            }
        }
    }
}
void Setcursors(int x, int y)
{
    HANDLE handle;
    COORD coord = {x, y};
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, coord);
}
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void Homework_Check()//��Ϯ���
{
    fstream file(".\\Plagiarist.txt", ios::out);
        
    Setcursors(15, 5);
    cout << "                                        ";
    Setcursors(15, 4);
    cout << "                                        ";
    Setcursors(15, 4);
    cout << "�������Plagiarist.txt�鿴";
    Setcursors(20, 17);
    cout << "������ɰ��س���";

    Setcursors(8, 8);
    cout << ">>";
    Setcursors(12, 8);
    cout << " �� �� �� �� :";
    while (cin >> Cno)
    {

        if (Cno < 200000 || Cno >= 200200)
        {
            Setcursors(28, 8);
            cout << " ��ΧΪ[200000,200200)";
            Sleep(1000);
            Setcursors(28, 8);
            cout << "                        ";
        }

        else
            break;

        Setcursors(28, 8);
    }

    StuHomework *head = new StuHomework;

    //�ҵ�hash�±�
    int i = 0;
    int newindex = 0;
    int pos = h1(Cno);
    if (cnohash[pos].cno != Cno)
    {
        i = 0;
        newindex = 0;
        while (1)
        {
            i++;
            newindex = (pos + i * h2(Cno)) % Class_NUM;
            if (cnohash[newindex].cno == Cno)
            {
                break;
            }
        }
    }
    string Path = ".\\HandedHomeWork\\";

    char c[10];
    itoa(Cno, c, 10);
    string ccs = c;
    Path.append(ccs);
    Path.append("\\");

    //BST
    if (i == 0)
    {
        GradeNode *p = cnohash[pos].next;
        p = cnohash[pos].next;
        AStack<GradeNode *> s;

        //�����ң�ǰ�����
        while (s.isEmpty() == false || p != NULL)
        {
            while (p != NULL)
            {

                char cc[8];
                itoa(p->sno, cc, 10);
                string newpath;
                newpath = Path;
                string ss = cc;
                newpath.append(ss);
                newpath.append(".txt");

                ifstream inFile(newpath.c_str(), ios::in);
                if (inFile.is_open())
                {
                    string shomework;
                    string temp;
                    while (getline(inFile, temp))
                    {
                        shomework.append(temp);
                    }
                    append(head, p->sno, shomework);
                }
                inFile.close();
                s.push(p);
                p = p->lc;
            }
            if (s.isEmpty() == false)
            {
                p = s.topValue();
                s.pop();
                p = p->rc;
            }
        }
    }
    else
    {
        GradeNode *p = cnohash[newindex].next;
        p = cnohash[newindex].next;
        AStack<GradeNode *> s;
        //�����ң�ǰ�����
        while (s.isEmpty() == false || p != NULL)
        {
            while (p != NULL)
            {
                char cc[8];
                itoa(p->sno, cc, 10);
                string ss = cc;
                string newpath;
                newpath = Path;

                newpath.append(ss);
                newpath.append(".txt");
                //cout << newpath;
                ifstream inFile(newpath.c_str(), ios::in);
                if (inFile.is_open())
                {
                    string shomework;
                    string temp;
                    while (getline(inFile, temp))
                    {
                        shomework.append(temp);
                    }
                    append(head, p->sno, shomework);
                }
                inFile.close();
                s.push(p);
                p = p->lc;
            }
            if (s.isEmpty() == false)
            {
                p = s.topValue();
                s.pop();
                p = p->rc;
            }
        }
    }
	StuHomework *p = head->next;
	for (; p != NULL; p = p->next)
	{
		StuHomework *q = p;
		StuHomework *r = p->next;
		//cout << q->stuNo << endl;
		for (; r != NULL; )
		{
			//cout << r->stuNo << endl;
			string a = p->stuWork;
			string b = r->stuWork;
			Matcher m(multiByteToWideChar(a), a.length(), multiByteToWideChar(b), b.length());
			//cout << p->stuNo << " and " << r->stuNo << "���ƶ�:" << m.match() << endl;

			if (m.match() > 0.8)
			{
                ofstream fout(".\\Plagiarist.txt", ios::app);
				fout << p->stuNo << " �� " << r->stuNo << " ��ҵ���ƶȴ���80% ��" << endl;
				fout.close();
                q->next=r->next;
				delete r;
				r=q->next;
				
			}
			else{
				q = q->next;
				r = q->next;
			}
		}
	}
}
void Homework_Cal()//��ҵû�����
{ 
    fstream file(".\\Unsubmit.txt", ios::out);
        
    Setcursors(15, 5);
    cout << "                                        ";
    Setcursors(15, 4);
    cout << "                                        ";
    Setcursors(15, 4);
    cout << "�������Unsubmit.txt�鿴";
    Setcursors(20, 17);
    cout << "������ɰ��س���";

    Setcursors(8, 8);
    cout << ">>";
    Setcursors(12, 8);
    cout << " �� �� �� �� :";
    while (cin >> Cno)
    {

        if (Cno < 200000 || Cno >= 200200)
        {
            Setcursors(28, 8);
            cout << " ��ΧΪ[200000,200200)";
            Sleep(1000);
            Setcursors(28, 8);
            cout << "                        ";
        }

        else
            break;

        Setcursors(28, 8);
    }

    StuHomework *head = new StuHomework;

    //�ҵ�hash�±�
    int i = 0;
    int newindex = 0;
    int pos = h1(Cno);
    if (cnohash[pos].cno != Cno)
    {
        i = 0;
        newindex = 0;
        while (1)
        {
            i++;
            newindex = (pos + i * h2(Cno)) % Class_NUM;
            if (cnohash[newindex].cno == Cno)
            {
                break;
            }
        }
    }
    string Path = ".\\HandedHomeWork\\";

    char c[10];
    itoa(Cno, c, 10);
    string ccs = c;
    Path.append(ccs);
    Path.append("\\");

    int miss = 0;
    //BST
    if (i == 0)
    {
        GradeNode *p = cnohash[pos].next;
        p = cnohash[pos].next;
        AStack<GradeNode *> s;

        //�����ң�ǰ�����
        while (s.isEmpty() == false || p != NULL)
        {
            while (p != NULL)
            {

                char cc[8];
                itoa(p->sno, cc, 10);
                string newpath;
                newpath = Path;
                string ss = cc;
                newpath.append(ss);
                newpath.append(".txt");

                ifstream inFile(newpath.c_str(), ios::in);
                if (!inFile.is_open())
                {
                    ofstream fout(".\\Unsubmit.txt", ios::app);
                    fout <<p->sno<< " δ�ύ" << endl;
                    fout.close();
                    miss++;
                }
                else
                {

                    string shomework;
                    string temp;
                    while (getline(inFile, temp))
                    {
                        shomework.append(temp);
                    }
                    append(head, p->sno, shomework);
                }
                inFile.close();
                s.push(p);
                p = p->lc;
            }
            if (s.isEmpty() == false)
            {
                p = s.topValue();
                s.pop();
                p = p->rc;
            }
        }
    }
    else
    {
        GradeNode *p = cnohash[newindex].next;
        p = cnohash[newindex].next;
        AStack<GradeNode *> s;
        //�����ң�ǰ�����
        while (s.isEmpty() == false || p != NULL)
        {
            while (p != NULL)
            {
                char cc[8];
                itoa(p->sno, cc, 10);
                string ss = cc;
                string newpath;
                newpath = Path;

                newpath.append(ss);
                newpath.append(".txt");
                //cout << newpath;
                ifstream inFile(newpath.c_str(), ios::in);
                if (!inFile.is_open())
                {
                    ofstream fout(".\\Unsubmit.txt", ios::app);
                    fout <<p->sno<< " δ�ύ" << endl;
                    fout.close();
                    miss++;
                }
                else
                {

                    string shomework;
                    string temp;
                    while (getline(inFile, temp))
                    {
                        shomework.append(temp);
                    }
                    append(head, p->sno, shomework);
                }
                inFile.close();
                s.push(p);
                p = p->lc;
            }
            if (s.isEmpty() == false)
            {
                p = s.topValue();
                s.pop();
                p = p->rc;
            }
        }
    }
    ofstream fout(".\\Unsubmit.txt", ios::app);
    fout << miss << " ��δ�ύ" << endl;
    fout.close();
}
void Check_Grade()
{
    Setcursors(18, 2);
    cout << "��ӭ�����������ϵͳ!!";
    Setcursors(15, 5);
    cout << "���ã�" << Wenyi.id;
    Setcursors(15, 4);
    cout << "1��2��3������ѡ��k��ȷ�ϣ�0�˳�";
    char key;
    int a = 1;
    Setcursors(7, 15);
    cout << "1.��ҵ���"
         << "\t"
         << "2.��鳭Ϯ"
         << "\t"
         << "3.������ҳ";;
    Setcursors(4, 15);
    cout << ">>";
    Setcursors(60, 30);
    cout << " ";
    while (a)
    {
        key = getch();
        switch (key)
        {
        case '1':
            Setcursors(4, 15);
            cout << ">>";
            Setcursors(21, 15);
            cout << "  ";
            Setcursors(37, 15);
            cout << "  ";
            a = 1;
            break;
        case '2':
            Setcursors(4, 15);
            cout << "  ";
            Setcursors(21, 15);
            cout << ">>";
            Setcursors(37, 15);
            cout << "  ";
            a = 2;
            break;
        case '3':
            Setcursors(4, 15);
            cout << "  ";
            Setcursors(21, 15);
            cout << "  ";
            Setcursors(37, 15);
            cout << ">>";
            a = 3;
            break;
        case 'k':
            if (a == 1) //��ҵ���
            {
                RemoveScreen();
                Homework_Cal();
                RemoveScreen();
                Check_Grade();
            }
            else if (a == 2) //��鳭Ϯ
            {
                Setcursors(25, 30);

                RemoveScreen();
                Homework_Check();
                RemoveScreen();
                Check_Grade();
            }
            else if(a == 3){
                RemoveScreen();
                TeacherDo();
                RemoveScreen();
            }
            a = 0;
            break;
        case '0':
            cout << endl
                 << endl
                 << endl
                 << endl;
            Setcursors(60, 30);
            cout << " ";
            exit(0);
            Setcursors(60, 30);
            cout << " ";
            break;
        }
    }
}
void TeacherDo()
{

    Setcursors(18, 2);
    cout << "��ӭ�����������ϵͳ!!";
    Setcursors(15, 5);
    cout << "���ã�" << Wenyi.id;
    Setcursors(15, 4);
    cout << "1��2������ѡ��k��ȷ�ϣ�0�˳�";
    if (isAdded == true)
    {

        fstream file(".\\Grade.txt", ios::out);
        ofstream fout(".\\Grade.txt", ios::app);
        GradeNode *p;
        for (int i = 0; i < Class_NUM; i++)
        {
            if (cnohash[i].cno != -1)
            {
                p = cnohash[i].next;
                AStack<GradeNode *> s;
                //�����ң�ǰ�����д��
                while (s.isEmpty() == false || p != NULL)
                {
                    while (p != NULL)
                    {
                        fout << p->sno << ' ' << cnohash[i].cno << ' ' << p->Ugrade << ' ' << p->Fgrade << ' ' << p->Grade << endl;
                        s.push(p);
                        p = p->lc;
                    }
                    if (s.isEmpty() == false)
                    {
                        p = s.topValue();
                        s.pop();
                        p = p->rc;
                    }
                }
            }
        }
        fout.close();
    }
    char key;
    int a = 1;
    Setcursors(13, 15);
    cout << "1.�ύ�γ̳ɼ�"
         << "\t\t"
         << "2.������ҵ";
    Setcursors(10, 15);
    cout << ">>";
    Setcursors(60, 30);
    cout << " ";
    while (a)
    {
        key = getch();
        switch (key)
        {
        case '1':
            Setcursors(10, 15);
            cout << ">>";
            Setcursors(37, 15);
            cout << "  ";
            Setcursors(60, 30);
            cout << " ";
            a = 1;
            break;
        case '2':
            Setcursors(10, 15);
            cout << "  ";
            Setcursors(37, 15);
            cout << ">>";
            Setcursors(60, 30);
            cout << " ";
            a = 2;
            break;
        case 'k':
            if (a == 1) //�ύ�γ̳ɼ�
            {
                RemoveScreen();
                SetCnoRate();
                RemoveScreen();
                SetGrade();
                //Sleep(800);
                RemoveScreen();
                Continue_End();
                RemoveScreen();
                // PlayUsers();
            }
            else if (a == 2) //������ҵ
            {
                Setcursors(25, 30);

                RemoveScreen();
                PublishHomework();
                RemoveScreen();
                Check_Grade();
                RemoveScreen();

            }
            a = 0;
            break;
        case '0':
            cout << endl
                 << endl
                 << endl
                 << endl;
            Setcursors(60, 30);
            cout << " ";
            exit(0);
            Setcursors(60, 30);
            cout << " ";
            break;
        }
    }
}
void PublishHomework()
{
    fstream file(".\\HomeWork.txt", ios::out);
       
    Setcursors(15, 4);
    cout << "                                   ";
    Setcursors(20, 17);
    cout << "������ɰ��س���";
    string homework;
    Setcursors(7, 5);
    cout << ">>>";
    Setcursors(12, 5);
    cout << "�� �� �� ҵ :";
    Setcursors(7, 7);
    cin >> homework;
    ofstream fout(".\\HomeWork.txt", ios::app);
    fout << homework << endl;
    fout.close();
}
void SetCnoRate()
{
    Setcursors(15, 5);
    cout << "                                        ";
    Setcursors(15, 4);
    cout << "                                        ";
    Setcursors(20, 17);
    cout << "������ɰ��س���";

    Setcursors(8, 8);
    cout << ">>";
    Setcursors(12, 8);
    cout << " �� �� �� �� :";

    Setcursors(12, 12);
    cout << " ƽʱ��ռ��(%):";
    Setcursors(28, 8);
    while (cin >> Cno)
    {

        if (Cno < 200000 || Cno >= 200200)
        {
            Setcursors(28, 8);
            cout << " ��ΧΪ[200000,200200)";
            Sleep(1000);
            Setcursors(28, 8);
            cout << "                        ";
        }

        else
            break;

        Setcursors(28, 8);
    }
    Setcursors(8, 8);
    cout << "  ";
    Setcursors(8, 12);
    cout << ">>";
    Setcursors(28, 12);
    while (cin >> rate)
    {

        if (rate < 0 || rate > 100)
        {
            Setcursors(28, 12);
            cout << "  ��ΧΪ[0,100]";
            Sleep(1000);
            Setcursors(28, 12);
            cout << "                        ";
        }

        else
            break;
        Setcursors(28, 12);
    }
}
void SetGrade()
{
    //�ҵ�hash�±�
    int i = 0;
    int newindex = 0;
    int pos = h1(Cno);
    if (cnohash[pos].cno != Cno)
    {
        i = 0;
        newindex = 0;
        while (1)
        {
            i++;
            newindex = (pos + i * h2(Cno)) % Class_NUM;
            if (cnohash[newindex].cno == Cno)
            {
                break;
            }
        }
    }
    Setcursors(15, 4);
    cout << "                                   ";
    Setcursors(20, 17);
    cout << "������ɰ��س���";
    int student;
    int f_grade;
    int u_grade;
    Setcursors(8, 5);
    cout << ">>";

    Setcursors(12, 5);
    cout << " ѧ �� �� �� :";

    Setcursors(12, 9);
    cout << " ƽ ʱ �� �� :";

    Setcursors(12, 13);
    cout << " �� ĩ �� �� :";

    Setcursors(28, 5);
    //BST
    while (cin >> student)
    {
        int flag = 0;
        Setcursors(8, 5);
        cout << "  ";
        if (i != 0)
        {
            cnohash[newindex].rate = rate;
            GradeNode *p = cnohash[newindex].next;

            while (p != NULL)
            {
                if (student < p->sno)
                {
                    if (p->lc == NULL)
                    {
                        Setcursors(28, 5);
                        cout << "��ѧ��ûѡ�˿�" << endl;
                        Sleep(1000);
                        Setcursors(28, 5);
                        cout << "                                " << endl;
                        break;
                    }
                    else
                        p = p->lc;
                }
                else
                {
                    if (student > p->sno)
                    {
                        if (p->rc == NULL)
                        {
                            Setcursors(28, 5);
                            cout << "��ѧ��ûѡ�˿�" << endl;
                            Sleep(1000);
                            Setcursors(28, 5);
                            cout << "                                " << endl;
                            break;
                        }
                        else
                            p = p->rc;
                    }
                    else
                    {

                        Setcursors(8, 9);
                        cout << ">>";
                        Setcursors(28, 9);
                        while (cin >> u_grade)
                        {
                            if (u_grade < 0 || u_grade > 100)
                            {
                                Setcursors(28, 9);
                                cout << "  ��ΧΪ[0,100]";
                                Sleep(1000);
                                Setcursors(28, 9);
                                cout << "                        ";
                            }

                            else
                                break;
                            Setcursors(28, 9);
                        }
                        Setcursors(8, 9);

                        cout << "  ";
                        Setcursors(8, 13);
                        cout << ">>";
                        Setcursors(28, 13);
                        while (cin >> f_grade)
                        {
                            if (f_grade < 0 || f_grade > 100)
                            {
                                Setcursors(28, 13);
                                cout << "  ��ΧΪ[0,100]";
                                Sleep(1000);
                                Setcursors(28, 13);
                                cout << "                        ";
                            }

                            else
                                break;
                            Setcursors(28, 13);
                        }
                        p->setVal(rate, u_grade, f_grade);
                        flag = 1;
                        break;
                    }
                }
            }
        }
        else
        {
            cnohash[pos].rate = rate;
            GradeNode *p = cnohash[pos].next;

            while (p != NULL)
            {
                if (student < p->sno)
                {
                    if (p->lc == NULL)
                    {
                        Setcursors(28, 5);
                        cout << "1��ѧ��ûѡ�˿�" << endl;
                        Sleep(1000);
                        Setcursors(28, 5);
                        cout << "                                " << endl;
                        break;
                    }
                    else
                        p = p->lc;
                }
                else
                {
                    if (student > p->sno)
                    {
                        if (p->rc == NULL)
                        {
                            Setcursors(28, 5);
                            cout << "2��ѧ��ûѡ�˿�" << endl;
                            Sleep(1000);
                            Setcursors(28, 5);
                            cout << "                                " << endl;
                            break;
                        }
                        else
                            p = p->rc;
                    }
                    else
                    {
                        Setcursors(8, 9);
                        cout << ">>";
                        Setcursors(28, 9);
                        while (cin >> u_grade)
                        {
                            if (u_grade < 0 || u_grade > 100)
                            {
                                Setcursors(28, 9);
                                cout << "  ��ΧΪ[0,100]";
                                Sleep(1000);
                                Setcursors(28, 9);
                                cout << "                        ";
                            }

                            else
                                break;
                            Setcursors(28, 9);
                        }
                        Setcursors(8, 9);
                        cout << "  ";
                        Setcursors(8, 13);
                        cout << ">>";
                        Setcursors(28, 13);
                        while (cin >> f_grade)
                        {
                            if (f_grade < 0 || f_grade > 100)
                            {
                                Setcursors(28, 13);
                                cout << "  ��ΧΪ[0,100]";
                                Sleep(1000);
                                Setcursors(28, 13);
                                cout << "                        ";
                            }

                            else
                                break;
                            Setcursors(28, 13);
                        }
                        p->setVal(rate, u_grade, f_grade);
                        flag = 1;
                        break;
                    }
                }
            }
        }

        if (flag == 1)
            break;
        else
            Setcursors(28, 5);
    }
}
void Continue_End()
{
    Setcursors(15, 4);
    cout << "1��2������ѡ��k��ȷ�ϣ�0�˳�";
    Setcursors(15, 10);
    cout << "��ӳɹ�������";
    char key;
    int a = 1;
    Setcursors(10, 15);
    cout << "1.�������"
         << "\t\t\t"
         << "2.����";
    Setcursors(7, 15);
    cout << ">>";
    Setcursors(60, 30);
    cout << " ";
    while (a)
    {
        key = getch();
        switch (key)
        {
        case '1':
            Setcursors(7, 15);
            cout << ">>";
            Setcursors(37, 15);
            cout << "  ";
            Setcursors(60, 30);
            cout << " ";
            a = 1;
            break;
        case '2':
            Setcursors(7, 15);
            cout << "  ";
            Setcursors(37, 15);
            cout << ">>";
            Setcursors(60, 30);
            cout << " ";
            a = 2;
            break;
        case 'k':
            if (a == 1) //�������
            {
                isAdded = false;
                RemoveScreen();
                SetGrade();
                RemoveScreen();
                Continue_End();
            }
            else if (a == 2) //����TeacherDo()
            {
                RemoveScreen();
                isAdded = true;
                TeacherDo();
                RemoveScreen();
            }
            a = 0;
            break;
        case '0':
            cout << endl
                 << endl
                 << endl
                 << endl;
            Setcursors(60, 30);
            cout << " ";
            exit(0);
            Setcursors(60, 30);
            cout << " ";
            break;
        }
    }
}
void PlayUsers()
{

    Setcursors(18, 2);
    cout << "��ӭ�����������ϵͳ!!";
    Setcursors(15, 4);
    cout << "1��2������ѡ��k��ȷ�ϣ�0�˳�";

    char key;
    int a = 1;
    Setcursors(13, 15);
    cout << "1.ע��"
         << "\t\t  \t"
         << "2.��¼";
    Setcursors(10, 15);
    cout << ">>";
    Setcursors(60, 30);
    cout << " ";
    while (a)
    {
        key = getch();
        switch (key)
        {
        case '1':
            Setcursors(10, 15);
            cout << ">>";
            Setcursors(37, 15);
            cout << "  ";
            Setcursors(60, 30);
            cout << " ";
            a = 1;
            break;
        case '2':
            Setcursors(10, 15);
            cout << "  ";
            Setcursors(37, 15);
            cout << ">>";
            Setcursors(60, 30);
            cout << " ";
            a = 2;
            break;
        case 'k':
            if (a == 1) //ע��
            {
                RemoveScreen();
                UserPassword(Mo);
                Sleep(800);
                RemoveScreen();
                PlayUsers();
            }
            else if (a == 2) //��¼
            {
                Setcursors(25, 30);

                RemoveScreen();

                Login(Wenyi);

                RemoveScreen();
                TeacherDo();
            }
            a = 0;
            break;
        case '0':
            cout << endl
                 << endl
                 << endl
                 << endl;
            Setcursors(60, 30);
            cout << " ";
            exit(0);
            Setcursors(60, 30);
            cout << " ";
            break;
        }
    }
}
void RemoveScreen()
{
    for (int i = 5; i < L - 2; ++i)
    {
        Setcursors(2, 0 + i);
        for (int j = 2; j < C - 2; ++j)
        {
            cout << " ";
        }
    }
}
//ע��
void UserPassword(MANuser &mans)
{
    int a = 1;
    Setcursors(15, 4);
    cout << "                              ";
    Setcursors(15, 5);
    cout << "�û��������벻�ܳ��� 8 λ�ַ�";
    Setcursors(20, 17);
    cout << "������ɰ��س���";
    char Users[9];
    char Users_two[9];
    char Passwords[9];
    char Passwords2[9];
    int flag = 0;

    HashNode *p;

    Setcursors(12, 8);
    cout << "(�ʺ�)  �û���:";
    Setcursors(12, 10);
    cout << "(��һ��)��  ��:";
    Setcursors(12, 12);
    cout << "(�ڶ���)��  ��:";
    Setcursors(8, 8);
    cout << ">>";
    Setcursors(28, 8);
    cin >> Users;
    strcpy(Users_two, Users);
    do
    {

        if (strlen(Users) >= 9)
        {
            Setcursors(28, 8);
            cout << "�û�������,����������         ";
            Sleep(1000);
            Setcursors(28, 8);
            cout << "                              ";
            Setcursors(28, 8);
            cin >> Users;
            strcpy(Users_two, Users);
        }
        else
        {
            flag = 1;
            p = &myhash[h(Users, 2000)];
            while (p->next != NULL)
            {
                if (strcmp(p->next->id.c_str(), Users) == 0)
                {
                    flag = 0;
                    Setcursors(28, 8);
                    cout << "�û�����ע��,����������         ";
                    Sleep(1000);
                    Setcursors(28, 8);
                    cout << "                              ";
                    Setcursors(28, 8);
                    cin >> Users;
                    strcpy(Users_two, Users);
                    break;
                }
                p = p->next;
            }

            if (flag == 1)
                break;
        }
    } while (a);

    Setcursors(8, 8);
    cout << "  ";
    Setcursors(8, 10);
    cout << ">>";

    Setcursors(28, 10);
    cin >> Passwords;
    do
    {
        if (strlen(Passwords) >= 9)
        {
            strcpy(Passwords, "0");
            Setcursors(28, 10);
            cout << "�������,����������           ";
            Sleep(1000);
            Setcursors(28, 10);
            cout << "                              ";
            Setcursors(28, 10);
            cin >> Passwords;
            strcpy(Users, Users_two);
        }
        else
            break;
    } while (a);

    Setcursors(8, 10);
    cout << "  ";
    Setcursors(8, 12);
    cout << ">>";

    Setcursors(28, 12);
    cin >> Passwords2;

    do
    {
        if (strlen(Passwords2) >= 9)
        {
            strcpy(Passwords2, "0");
            Setcursors(28, 12);
            cout << "�������,����������           ";
            Sleep(1000);
            Setcursors(28, 12);
            cout << "                              ";
            Setcursors(28, 12);
            cin >> Passwords2;
            strcpy(Users, Users_two);
        }
        else
            break;
    } while (a);

    if (strcmp(Passwords, Passwords2) != 0)
    {
        RemoveScreen();
        Setcursors(22, 6);
        cout << "�������벻һ��";
        Setcursors(12, 8);
        cout << "(�ʺ�)  �û���:";
        Setcursors(28, 8);
        cout << "                              ";
        strcpy(Users, Users_two);
        Setcursors(28, 8);
        cout << Users;

        Setcursors(12, 10);
        cout << "(��һ��)��  ��:";
        Setcursors(12, 12);
        cout << "(�ڶ���)��  ��:";
        while (1)
        {
            Setcursors(28, 10);
            cout << "                              ";
            Setcursors(28, 12);
            cout << "                              ";

            Setcursors(8, 12);
            cout << "  ";
            Setcursors(8, 10);
            cout << ">>";
            Setcursors(28, 10);
            cin >> Passwords;
            do
            {
                if (strlen(Passwords) >= 9)
                {
                    strcpy(Passwords, "0");
                    Setcursors(28, 10);
                    cout << "�������,����������           ";
                    Sleep(1000);
                    Setcursors(28, 10);
                    cout << "                              ";
                    Setcursors(28, 10);
                    cin >> Passwords;
                    strcpy(Users, Users_two);
                }
                else
                    break;
            } while (a);

            Setcursors(8, 10);
            cout << "  ";
            Setcursors(8, 12);
            cout << ">>";
            Setcursors(28, 12);
            cin >> Passwords2;

            do
            {
                if (strlen(Passwords2) >= 9)
                {
                    strcpy(Passwords2, "0");
                    Setcursors(28, 12);
                    cout << "�������,����������           ";
                    Sleep(1000);
                    Setcursors(28, 12);
                    cout << "                              ";
                    Setcursors(28, 12);
                    cin >> Passwords2;
                    strcpy(Users, Users_two);
                }
                else
                    break;
            } while (a);
            if (strcmp(Passwords, Passwords2) == 0)
            {
                break;
            }
        }
    }

    ofstream fout(".\\Tealogin.txt", ios::app);
    fout << Users << endl;
    fout << Passwords << endl;
    fout.close();
    //д��ȫ��Hash
    p = &myhash[h(Users, 2000)];
    while (p->next != NULL)
        p = p->next;
    p->next = new HashNode(Users, Passwords);

    RemoveScreen();
    Setcursors(25, 12);
    cout << "ע��ɹ�";
    strcpy(mans.id, Users);
    strcpy(mans.passwds, Passwords2);
    //FileLocal(hu);
}
//��¼
void Login(MANuser &who)
{
    int num = 3;
    Setcursors(15, 4);
    //cout << "";
    Setcursors(20, 17);
    cout << "������ɰ��س���";
    char Users[9];
    char Passwords[9];
    Setcursors(8, 8);
    cout << ">>";
    Setcursors(12, 8);
    cout << "  (�ʺ�)�û���:";

    Setcursors(12, 12);
    cout << "        ��  ��:";

    Setcursors(28, 8);
    cin >> Users;

    Setcursors(8, 8);
    cout << "  ";
    Setcursors(8, 12);
    cout << ">>";
    Setcursors(28, 12);
    cin >> Passwords;

    HashNode *p;

    int existname = 0;
    int match = 0;
    p = &myhash[h(Users, 2000)];

    while (p->next != NULL)
    {
        if (strcmp(p->next->id.c_str(), Users) == 0)
        {
            existname = 1;
            if (strcmp(p->next->passwds.c_str(), Passwords) == 0)
            {
                match = 1;
                break;
            }
        }
        p = p->next;
    }

    if (existname == 0 || match == 0)
    {
        RemoveScreen();
        Setcursors(15, 11);
        cout << "�������ID����������,����������";
        Sleep(1000);
        Setcursors(12, 8);
        cout << "(�ʺ�)  �û���:";
        Setcursors(28, 8);
        cout << "                              ";
        Setcursors(12, 12);
        cout << "        ��  ��:";
        Setcursors(28, 12);
        cout << "                              ";
        --num;
        while (1)
        {
            if (num <= 0)
            {
                RemoveScreen();
                PlayUsers();
                num = 3;
                break;
            }
            Setcursors(12, 8);
            cout << "(�ʺ�)  �û���:";
            Setcursors(28, 8);
            cout << "                              ";
            Setcursors(12, 12);
            cout << "        ��  ��:";
            Setcursors(28, 12);
            cout << "                              ";
            Setcursors(15, 11);
            cout << "�������ID����������,����������";
            Sleep(10);
            Setcursors(15, 11);
            cout << "                               ";
            Setcursors(22, 6);
            cout << "�㻹�� " << num << " �λ���";
            Setcursors(8, 12);
            cout << "  ";
            Setcursors(8, 8);
            cout << ">>";
            Setcursors(28, 8);
            cin >> Users;
            Setcursors(8, 8);
            cout << "  ";
            Setcursors(8, 12);
            cout << ">>";
            Setcursors(28, 12);
            cin >> Passwords;

            p = &myhash[h(Users, 2000)];
            while (p->next != NULL)
            {
                if (strcmp(p->next->id.c_str(), Users) == 0)
                {
                    existname = 1;
                    if (strcmp(p->next->passwds.c_str(), Passwords) == 0)
                    {
                        match = 1;
                        break;
                    }
                }
                p = p->next;
            }

            if ((p->next != NULL) && (strcmp(p->next->id.c_str(), Users) == 0) && (strcmp(p->next->passwds.c_str(), Passwords) == 0))
            {
                break;
            }

            --num;
        }
    }

    RemoveScreen();


  Setcursors(20, 12);
    cout << "��½�ɹ���" << endl;
    Setcursors(20, 13);
    strcpy(Wenyi.id, Users);
    strcpy(Wenyi.passwds, Passwords);
    cout << "��ӭ " << Wenyi.id << endl;
int cno;
    int sno;
    int u, f;
    double g;
    

    ifstream fin;
    fin.open(".\\Grade.txt");
    //��
    while (fin >> sno >> cno >> u >> f >> g)
    {
        int pos = h1(cno);
        if (cnohash[pos].cno == -1 || cnohash[pos].cno == cno)
        {
            cnohash[pos].cno = cno;
            
            mybst[pos].insert(sno, u, f, g);
            cnohash[pos].next = mybst[pos].root;
        }
        else
        {
            int i = 0;
            int newindex;
            while (1)
            {
                i++;
                newindex = (pos + i * h2(cno)) % Class_NUM;
                if (cnohash[newindex].cno == -1 || cnohash[newindex].cno == cno)
                {
                    cnohash[newindex].cno = cno;
                    
                    mybst[newindex].insert(sno, u, f, g);
                    cnohash[newindex].next = mybst[newindex].root;

                    break;
                }
            }
        }
    }
    fin.close();
    
   





  
    
    RemoveScreen();
    TeacherDo();
}
int main()
{
    //SetConsoleTitle("�û���¼");         //����̨����
    system("mode con cols=60 lines=40"); //���ƴ���size

    Setcursors(18, 2);
    cout << "��ӭ�����������ϵͳ";
    Setcursors(15, 4);
    cout << "1��2������ѡ��k��ȷ�ϣ�0�˳�";

    HideCursor();
    system("color 000"); //������ɫ

    welcomeUI();
    RemoveScreen();
    //PublishHomework();

    

    string temp1;
    string temp2;
    ifstream refin(".\\Tealogin.txt", ios::in);

    HashNode *p;
    while (getline(refin, temp1))
    {
        getline(refin, temp2);
        p = &myhash[h(temp1, 2000)];
        while (p->next != NULL)
            p = p->next;
        p->next = new HashNode(temp1, temp2);
    }
    refin.close();

    
  PlayUsers();



    Setcursors(0, 30);
    return 0;
}