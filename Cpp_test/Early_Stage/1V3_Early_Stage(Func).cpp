//
//  1v3(func)(cpp)
//
//  Created by Ye172 on 16/8/30.
//  Copyright © 2016年 Yee172. All rights reserved.
//

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

//类型设置//

typedef struct card
{
    int hs;
    int ds;
}
Card;

typedef struct pai
{
    int zu;
    int shu;
    int where[8];
}
Pai;

//类型设置//


//函数声明//

/*  00  */
void scrpau(float);
/*  01  */
Card * preparepaidui(Card*);
/*  02  */
Card * xipai(Card*);
/*  03  */
void fapai(Card*,Card*,int);
/*  04  */
int paishu(Card*);
/*  05  */
int zushu(Pai*);
/*  06  */
void sort(Card*);
/*  07  */
void sort(Pai*);
/*  08  */
Pai * card_pai(Card*);
/*  09  */
void zhanshipai(Card*);
/*  10  */
void kanpai_1(Card*);
/*  11  */
void kanpai_2(Card*);
/*  12  */

//函数声明//


//创建函数//

/*  00  */
void scrpau(float f)
{
    clock_t delay=f * CLOCKS_PER_SEC;
    clock_t start=clock();
    while(clock()-start<delay);
}
/*  01  */
Card * preparepaidui(Card *p)
{
    int dianshu[]={3,4,5,6,7,8,9,10,11,12,13,14,16};
    int i;
    for (i=0;i<52;i++)
    {
        p[i].hs = i % 4 + 1;
        p[i].ds = dianshu[i / 4];
    }
    p[52].hs = -1;p[52].ds = 101;
    p[53].hs = -2;p[53].ds = 102;
    for(i=0;i<54;i++)
    {
        p[i+54] = p[i];
    }
    p[108] = {0,0};
    return p;
}
/*  02  */
Card * xipai(Card *p)
{
    srand((unsigned)time(0));
    Card temp;
    int x,y,i;
    for (i=0;i<1000;i++)
    {
        x = rand() % 108;
        y = rand() % 108;
        temp = p[x];
        p[x] = p[y];
        p[y] = temp;
    }
    return p;
}
/*  03  */
void fapai(Card *zong,Card *fen,int n)
{
    int i,j;
    for (i=0,j=0;i<n;i++)
    {
        fen[i] = zong[0];
        do{
            zong[j] = zong[j+1];
            j++;
        }while (zong[j].hs != 0);
        j = 0;
    }
    fen[n].hs = 0;fen[n].ds = 0;
}
/*  04  */
int paishu(Card *p)
{
    int num = 0;
    while (p->ds)
    {
        num++;
        p++;
    }
    return num;
}
/*  05  */
int zushu(Pai *a)
{
    int num = 0;
    while (a->zu)
    {
        num++;
        a++;
    }
    return num;
}
/*  06  */
void sort(Card *p)
{
    int i,j,n;
    Card temp;
    n=paishu(p);
    for (i=1;i<=n;i++)
    {
        for (j=1;i+j<=n;j++)
        {
            if (4*(p+j-1)->ds+(p+j-1)->hs<4*(p+j)->ds+(p+j)->hs)
            {
                temp=*(p+j-1);
                *(p+j-1)=*(p+j);
                *(p+j)=temp;
            }
        }
        
    }
}
/*  07  */
void sort(Pai *a)
{
    int i,j;
    Pai temp;
    for (i=0;i<zushu(a);i++)
    {
        for (j=0;i+j<zushu(a);j++)
        {
            if (a[j].shu < a[j+1].shu)
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
/*  08  */
Pai * card_pai(Card *p)
{
    static Pai a[15];
    int i,j=0;
    sort(p);
    for (i=0,j=0;j<15;j++)
    {
        if (p[i].ds==0) break;
        a[j].zu=p[i].ds;
        a[j].shu=1;
        a[j].where[a[j].shu-1] = i;
        i++;
        while (a[j].zu==p[i].ds)
        {
            a[j].shu++;
            a[j].where[a[j].shu-1] = i;
            i++;
        }
    }
    return a;
}
/*  09  */
void zhanshipai(Card *p)
{
    int i;
    int n = paishu(p);
    cout << "牌标|";
    for (i = 1;i<=n;i++)
    {
        printf("%02d",i);
        cout << "|";
    }
    cout << endl << "花色|";
    for (i=0;i<n;i++)
    {
        switch(p[i].hs)
        {
            case 1:printf("♠️ ");break;
            case 2:printf("❤️ ");break;
            case 3:printf("♣️ ");break;
            case 4:printf("♦️ ");break;
            case -1:printf("小");break;
            case -2:printf("大");break;
        }
        cout << "|";
    }
    cout << endl << "点数|";
    for (i=0;i<n;i++)
    {
        switch(p[i].ds)
        {
            case 3:printf(" 3");break;
            case 4:printf(" 4");break;
            case 5:printf(" 5");break;
            case 6:printf(" 6");break;
            case 7:printf(" 7");break;
            case 8:printf(" 8");break;
            case 9:printf(" 9");break;
            case 10:printf("10");break;
            case 11:printf(" J");break;
            case 12:printf(" Q");break;
            case 13:printf(" K");break;
            case 14:printf(" A");break;
            case 16:printf(" 2");break;
            case 101:printf("王");break;
            case 102:printf("王");break;
        }
        cout << "|";
    }
    cout << endl;
    printf("牌数:%d\n",n);
}
/*  10  */
void kanpai_1(Card *p)
{
    sort(p);
    zhanshipai(p);
}
/*  11  */
void kanpai_2(Card *p)
{
    Card q[34] = {0,0};
    Pai *a;
    int i,j;
    sort(p);
    i = 0;
    while (p[i].ds > 100)
    {
        q[i] = p[i];
        p[i] = p[paishu(p)-1];
        p[paishu(p)-1] = {0,0};
        i++;
    }
    a = card_pai(p);
    sort(a);
    while (a[0].shu)
    {
        for (j=0;j<a[0].shu;j++)
        {
            q[i] = p[a[0].where[j]];
            i++;
        }
        a[0].shu = 0;
        sort(a);
    }
    zhanshipai(q);
}
/*  12  */


/*
Fenlei pai_fenlei(pai *p)
{
    int i,lian;
    Fenlei a = {0,0,0,0,0};
    for (lian=0,i=0;i<15;i++)
    {
        if (p[i].shu == 1) a.dan++;
        if (p[i].shu == 2) a.dui++;
        if (p[i].shu == 3) a.san++;
        if (p[i].shu > 3) a.zha++;
        if (i>0 && p[i].zu-p[i-1].zu == -1 && p[i].zu < 100 && p[i].shu == p[i-1].shu < 4) lian ++;
        else if(lian * p[i-1].shu > 4) a.shun++,lian = 1;
        else lian = 1;
        if (p[i].zu+p[i-1].zu==203 && p[i].shu+p[i-1].shu == 4) a.zha++,a.dui -= 2;
    }
    return a;
}
*/


/* test room */

int main()
{
    Card paidui[109],p1[34],p2[34],p3[34],p4[34];
    preparepaidui(paidui);
    xipai(paidui);
    fapai(paidui, p1, 33);fapai(paidui, p2, 25);fapai(paidui, p3, 25);fapai(paidui, p4, 25);
    kanpai_2(p1);kanpai_2(p2);kanpai_2(p3);kanpai_2(p4);
    return 0;
}
