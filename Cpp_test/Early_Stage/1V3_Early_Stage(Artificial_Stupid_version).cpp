//
//  1v3(AI:easy)(Cpp)
//
//  Created on 16/8/23.
//

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iostream>

using namespace std;

const int NUM=27;
typedef struct card
{
    int hs;
    int ds;
}
Card;

typedef struct precard
{
    Card cdpai[34];
    int zsmax;
    int zsmin;
    int duishu;
    int mode;
    int dsmax;
}
Precard;

int huase[]={1,2,3,4};
int dianshu[]={3,4,5,6,7,8,9,10,11,12,13,14,16};
int joker[]={101,102};
int NOA=3;//NOA stands for the number of abandoning.
int who=0;//used for recording the last caster.0--player,1--AI

int paishu(Card*);
Card* Preparepaidui(Card*);
Card* xipai(Card*);
void kanpai(Card*);
void fapai(Card*,Card*,int);
void reini(Precard*);
void sort(Card*);
void scrpau(float);
Precard* chupai(Card*,Precard*);
Precard* AIchupai(Card*,Precard*);
Precard* chulicdpai(Precard*);
void card(Card*);
void gaojikanpai(Card*);

int main(void) //The main function is here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
{
    //system("color 70");
    printf("和电脑玩斗地主！你是地主！\n");
    //system("pause");
weizhi:Card paidui[109],Player[34],AI1[34],AI2[34],AI3[34];
    Card *p0=paidui,*p1=Player,*p2=AI1,*p3=AI2,*p4=AI3;
    
    Precard q={{{0,0}},0,0,0,-1,0};//mode==-1表示空牌堆,mode==0表示无效牌堆//
    Precard *p_q=&q;
    
    p0=Preparepaidui(p0);
    p0=xipai(p0);
    fapai(p0,p1,33);
    fapai(p0,p2,25);
    fapai(p0,p3,25);
    fapai(p0,p4,25);
    while(paishu(p1)*paishu(p2)*paishu(p3)*paishu(p4))
    {
        p_q=chupai(p1,p_q); if(paishu(p1)==0) {printf("你赢了！\n");break;}
        p_q=AIchupai(p2,p_q);if(paishu(p2)==0) {printf("对手赢了！\n");break;}
        p_q=AIchupai(p3,p_q);if(paishu(p3)==0) {printf("对手赢了！\n");break;}
        p_q=AIchupai(p4,p_q);if(paishu(p4)==0) {printf("对手赢了！\n");break;}
    }
    goto weizhi;
    //system("pause");
    return 0;
}
void scrpau(float f)
{
    clock_t delay=f * CLOCKS_PER_SEC;
    clock_t start=clock();
    while(clock()-start<delay);
}

Card* Preparepaidui(Card *p)
{
    int i,j;
    for(i=0;i<=51;i++)
    {
        p->hs=huase[i%4];
        p->ds=dianshu[i/4];
        p++;
    }
    p->ds=joker[0];p->hs=-1;
    p++;
    p->ds=joker[1];p->hs=-2;
    p++;
    for(j=0;j<=53;j++)
    {
        p->hs=(p-54)->hs;
        p->ds=(p-54)->ds;
        p++;
    }
    p=p-108;
    (p+108)->ds=0;
    (p+108)->hs=0;
    return p;
}

Card* xipai(Card *p)
{
    srand((unsigned)time(0));
    int x,y,i;
    int hstemp,dstemp;
    for(i=0;i<=999;i++)
    {
        x=rand()%108;
        y=rand()%108;
        hstemp=(p+x)->hs;
        (p+x)->hs=(p+y)->hs;
        (p+y)->hs=hstemp;
        dstemp=(p+x)->ds;
        (p+x)->ds=(p+y)->ds;
        (p+y)->ds=dstemp;
    }
    return p;
}

void card(Card *p)
{
    switch(p->hs)
    {
        case 1:printf("♠️ ");break;
        case 2:printf("❤️ ");break;
        case 3:printf("♣️ ");break;
        case 4:printf("♦️ ");break;
        default:;
    }
    switch(p->ds)
    {
        case 3:printf("3");break;
        case 4:printf("4");break;
        case 5:printf("5");break;
        case 6:printf("6");break;
        case 7:printf("7");break;
        case 8:printf("8");break;
        case 9:printf("9");break;
        case 10:printf("10");break;
        case 11:printf("J");break;
        case 12:printf("Q");break;
        case 13:printf("K");break;
        case 14:printf("A");break;
        case 16:printf("2");break;
        case 101:printf("小王");break;
        case 102:printf("大王");break;
    }
}

void kanpai(Card *p)
{
    int i;
    int n=paishu(p);
    sort(p);
    for(i=1;i<=n;i++,p++)
    {
        printf("牌%3d:",i);
        card(p);
        printf("\n");
    }
    printf("牌数:%d\n",n);
}

void gaojikanpai(Card *p)
{
    sort(p);
    int i;
    int n = paishu(p);
    cout << "牌标|";
    for (i = 1;i<=n;i++)
    {
        printf("%02d",i);
        cout << "|";
    }
    cout << endl << "花色|";
    for (i = 0;i<n;i++)
    {
        switch(p->hs)
        {
            case 1:printf("♠️ ");break;
            case 2:printf("❤️ ");break;
            case 3:printf("♣️ ");break;
            case 4:printf("♦️ ");break;
            case -1:printf("小");break;
            case -2:printf("大");break;
        }
        cout << "|";
        p++;
    }
    p -= n;
    cout << endl << "点数|";
    for (i = 0;i<n;i++)
    {
        switch(p->ds)
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
        p++;
    }
    p -= n;
    cout << endl;
    printf("牌数:%d\n",n);
}


void fapai(Card *zong,Card *fen,int n)
{
    int i,j,k;
    for(i=1;i<=n;i++)
    {
        *fen=*zong;
        fen++;
        zong++;
    }
    fen->ds=0;
    fen->hs=0;
    fen=fen-n;
    zong=zong-n;
    for(j=1;j<=n;j++)
    {
        for(k=0;k<=paishu(zong)-1;k++) *(zong+k)=*(zong+k+1);
    }
}

int paishu(Card *p)
{
    int num=0;
    while(p->ds)
    {
        num++;
        p++;
    }
    return num;
}


void sort(Card *p)
{
    int i,j,n;
    struct card temp;
    n=paishu(p);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(4*(p+j-1)->ds+(p+j-1)->hs<4*(p+j)->ds+(p+j)->hs)
            {
                temp=*(p+j-1);
                *(p+j-1)=*(p+j);
                *(p+j)=temp;
            }
        }
        
    }
}

void reini(Precard *p_q)
{
    int i;
    for(i=0;i<=33;i++) (*(p_q->cdpai+i)).ds=0;
    p_q->zsmax=0;
    p_q->zsmin=0;
    p_q->duishu=0;
    p_q->mode=-1;
    p_q->dsmax=0;
}


Precard* chupai(Card *p,Precard *p_q)
{
    if(NOA==3)
    {
        NOA=0;
        reini(p_q);
    }
    Precard q1={{{0,0}},0,0,0,-1,0};
    Precard *p_q1=&q1;
    int s[34]={0};
    int ss;
    int i=0;
    printf("该你了，这是你的牌:\n");
    scrpau(1.5);
    gaojikanpai(p);
    printf("请输入要出的牌的序号：（依次输入并用空格分隔，以0结束。若不出则直接输0）\n");
shuru: 	for(i=0;i<=33;i++) s[i]=0;
    i=0;
    scanf("%d",&ss);
    while(ss)
    {
        s[i]=ss;
        i++;
        scanf("%d",&ss);
    }
    s[i]=0;
    int I=i;//记录下所出的牌的序号，张数恰好为i//
    i=0;
    while(s[i])
    {
        *(p_q1->cdpai+i)=*(p+s[i]-1);
        i++;
    }
    p_q1=chulicdpai(p_q1);
    if(s[0]==0&&p_q->mode!=-1)
    {
        NOA++;
        system("clear");
        printf("你不出。\n\n");
        return p_q;
    }
    else if((((p_q1->mode!=p_q->mode&&p_q->mode!=-1)||(p_q1->mode==-1&&p_q->mode==-1)||p_q1->dsmax<=p_q->dsmax)&&p_q->mode<400&&p_q1->mode<400)/*都不是炸弹且不符*/||(p_q->mode>400&&(p_q1->mode<400)/*之前是炸弹，但之后不是*/||p_q1->mode>400&&p_q->mode>400&&((p_q->zsmax==p_q1->zsmax&&p_q->dsmax>=p_q1->dsmax)/*同阶炸弹，但是比不过*/&&(p_q->dsmax>p_q1->dsmax)/*炸弹阶数低*/)))
    {
        printf("出牌不符合规则！请重新输入\n");
        reini(p_q1);
        goto shuru;
    }
    else
    {
        system("clear");
        printf("你出了:\n");
        NOA=0;
        who=0;
        i=0;
        while(s[i])
        {
            card(p+s[i]-1);
            (p+s[i]-1)->ds=-1;
            (p+s[i]-1)->hs=0;
            printf("\n");
            i++;
        }
        printf("\n");
        sort(p);
        *p_q=*p_q1;
        reini(p_q1);
        return p_q;
    }
}


Precard* chulicdpai(Precard *p_q)
{
    sort(p_q->cdpai);
    int i,j,k;//i用于记录所读取的牌的位置，j用于记录点数种类（堆数），k用于记录3张牌的堆数//
    int d[13]={0},z[13]={0},t[13]={0};
    for(i=0,j=0,k=0;j<=12;j++)
    {
        if((*(p_q->cdpai+i)).ds==0) break;
        d[j]=(*(p_q->cdpai+i)).ds;
        z[j]=1;
        i++;
        while(d[j]==(*(p_q->cdpai+i)).ds)
        {
            z[j]++;
            i++;
        }
        if(z[j]==3)
        {
            t[k]=d[j];
            k++;
        }
    }//最终i即为输入的牌的张数,k即为输入的三张牌的堆数//
    j=0;
    p_q->zsmin=z[0];
    while(z[j])
    {
        p_q->zsmax=p_q->zsmax>z[j]?p_q->zsmax:z[j];
        p_q->zsmin=p_q->zsmin<z[j]?p_q->zsmin:z[j];
        j++;
    }
    p_q->duishu=j;
    if(p_q->zsmax==p_q->zsmin)
    {
        if(d[0]==102&&d[1]==101&&z[0]==2&&z[1]==2)
        {
            p_q->mode=1000;
            p_q->dsmax=102;
        }//王炸
        if(p_q->duishu==1)
        {
            p_q->mode=p_q->zsmax*100+p_q->duishu;
            p_q->dsmax=d[0];
        }
        if((p_q->zsmax)*(p_q->duishu)>=5&&p_q->duishu-1==d[0]-d[j-1]&&d[0]<=14)
        {
            p_q->mode=p_q->zsmax*100+p_q->duishu;
            p_q->dsmax=d[0];
        }
        if(p_q->zsmax>=4&&p_q->duishu>=2)
        {
            p_q->mode=-1;
            p_q->dsmax=0;
        }
    }
    if(p_q->zsmax==3&&p_q->zsmin==2&&i%5==0&&i/5==k&&t[0]-t[k-1]==k-1)
    {
        p_q->mode=k;
        p_q->dsmax=t[0];
        p_q->zsmax=5;
    }
    return p_q;
}

Precard* AIchupai(Card *p,Precard *p_q)
{
    scrpau(1);
    if(NOA==3)
    {
        reini(p_q);
        NOA=0;
    }
    int max=paishu(p);
    sort(p);
    Precard q1={{{0,0}},0,0,0,-1,0},q2={{{0,0}},0,0,0,-1,0};//q1用于整理AI手牌，q2用于存放出的牌//
    Precard *p_q1=&q1,*p_q2=&q2;
    for(int n=0;n<=max-1;n++)
    {
        *(p_q1->cdpai+n)=*(p+n);
    }
    
    //开始整理AI手牌//
    int i,j,k;//i用于记录所读取的牌的位置，j用于记录点数种类（堆数），k用于记录3张牌的堆数//
    int d[13]={0},z[13]={0},t[13]={0};
    for(i=0,j=0,k=0;j<=12;j++)
    {
        if((*(p_q1->cdpai+i)).ds==0) break;
        d[j]=(*(p_q1->cdpai+i)).ds;
        z[j]=1;
        i++;
        while(d[j]==(*(p_q1->cdpai+i)).ds)
        {
            z[j]++;
            i++;
        }
        if(z[j]==3)
        {
            t[k]=d[j];
            k++;
        }
    }//最终i即为输入的牌的张数,k即为输入的三张牌的堆数//
    int K=k;
    j=0;
    p_q1->zsmin=z[0];
    while(z[j])
    {
        p_q1->zsmax=p_q1->zsmax>z[j]?p_q1->zsmax:z[j];
        p_q1->zsmin=p_q1->zsmin<z[j]?p_q1->zsmin:z[j];
        j++;
    }
    p_q1->duishu=j;
    if(p_q1->zsmax==p_q1->zsmin)
    {
        if(d[0]==102&&d[1]==101&&z[0]==2&&z[1]==2)
        {
            p_q1->mode=1000;
            p_q1->dsmax=102;
        }
        if(p_q1->duishu==1)
        {
            p_q1->mode=p_q1->zsmax*100+p_q1->duishu;
            p_q1->dsmax=d[0];
        }
        if((p_q1->zsmax)*(p_q1->duishu)>=5&&p_q1->duishu-1==d[0]-d[j-1]&&d[0]<=14)
        {
            p_q1->mode=p_q1->zsmax*100+p_q1->duishu;
            p_q1->dsmax=d[0];
        }
        if(p_q1->zsmax>=4&&p_q1->duishu>=2)
        {
            p_q1->mode=-1;
            p_q1->dsmax=0;
        }
    }
    if(p_q1->zsmax==3&&p_q1->zsmin==2&&i%5==0&&i/5==k)
    {
        p_q1->mode=k;
        p_q1->dsmax=t[0];
    }
    //整理AI手牌结束。//
    
    //先手出牌策略：//
    int sernum0;
    sernum0=(p_q->duishu)*(p_q->zsmax);
    if(p_q->mode==-1)
    {
        int ser,sernum;
        for(ser=0;ser<=max-1;ser++)
        {
            sernum=max-ser;
            int s;
            for(s=0;s<=sernum-1;s++) *(p_q2->cdpai+s)=*(p+ser+s);
            p_q2=chulicdpai(p_q2);
            if(p_q2->mode>0&&p_q2->mode<=400)
            {
                printf("对手出了\n");
                who=1;
                NOA=0;
                for(s=0;s<=sernum-1;s++)
                {
                    card(p+ser+s);
                    (p+ser+s)->ds=-1;
                    (p+ser+s)->hs=0;
                    printf("\n");
                }
                sort(p);
                printf("它还有%d张牌\n\n",paishu(p));
                *p_q=*p_q2;
                reini(p_q1);
                reini(p_q2);
                return p_q;
            }
            reini(p_q2);
        }
    }
    //跟牌策略://
    if(p_q->mode>100&&p_q->mode<400&&((who==1&&p_q->zsmax==1&&p_q->dsmax<=14)||(who==1&&p_q->zsmax>1&&p_q->dsmax<=13)||who==0))
    {
        int ser,sernum;
        sernum=(p_q->zsmax)*(p_q->duishu);
        for(ser=max-sernum;ser>=0;ser--)
        {
            int s;
            for(s=0;s<=sernum-1;s++)	*(p_q2->cdpai+s)=*(p+ser+s);
            p_q2=chulicdpai(p_q2);
            if(sernum==1&&((p+ser)->ds==(p+ser+1)->ds||(p+ser)->ds==(p+ser-1)->ds)&&(p+ser)->ds<=14)
            {
                reini(p_q2);
                continue;
            }
            if(p_q2->mode==p_q->mode&&p_q2->dsmax>p_q->dsmax)
            {
                printf("对手出了\n");
                who=1;
                NOA=0;
                for(s=0;s<=sernum-1;s++)
                {
                    card(p+ser+s);
                    (p+ser+s)->ds=-1;
                    (p+ser+s)->hs=0;
                    printf("\n");
                }
                sort(p);
                printf("它还有%d张牌\n\n",paishu(p));
                *p_q=*p_q2;
                reini(p_q1);
                reini(p_q2);
                return p_q;
            }
        }
    }
    
    //跟 三带二//
    reini(p_q2);
    if(p_q->mode<100&&p_q->mode>0&&t[0]>p_q->dsmax)
    {
        int ser1,sernum1,s1;
        int ser2,sernum2,s2;
        int s=0;
        for(K=k-1;K>=0;K--)
        {
            if(t[K]>p_q->dsmax)
            {
                for(ser1=max-2;ser1;ser1--)
                {
                    if((p+ser1)->ds==t[K]) {s1=ser1-2;break;}
                }
                for(ser2=max-1;ser2>=0;ser2--)
                {
                    if((p+ser2)->ds==(p+ser2+1)->ds&&(p+ser2)->ds!=t[K]) {s2=ser2;break;}
                }
                if(ser1&&ser2>=0)
                {
                    printf("对手出了\n");
                    who=1;
                    NOA=0;
                    for(s=0;s<=2;s++)
                    {
                        *(p_q2->cdpai+s)=*(p+s1+s);
                        card(p+s1+s);
                        (p+s1+s)->ds=-1;
                        (p+s1+s)->hs=0;
                        printf("\n");  
                    }
                    
                    for(s=0;s<=1;s++)
                    {
                        *(p_q2->cdpai+s+3)=*(p+s2+s);
                        card(p+s2+s);
                        (p+s2+s)->ds=-1;
                        (p+s2+s)->hs=0;
                        printf("\n");
                    }
                    p_q2=chulicdpai(p_q2);
                    sort(p);
                    printf("它还有%d张牌\n\n",paishu(p));
                    *p_q=*p_q2;
                    reini(p_q1);
                    reini(p_q2);
                    return p_q;	
                }
            }
        }
    }
    
    
    
    
    
    
    //炸弹回应策略(针对玩家)//
    if(who==0)
    {
        if(p_q->mode>0&&p_q->mode<=400)
        {
            int ser,sernum;
            for(sernum=4;sernum<=8;sernum++)
            {
                for(ser=max-sernum;ser>=0;ser--)
                {
                    int s;
                    for(s=0;s<=sernum-1;s++)	*(p_q2->cdpai+s)=*(p+ser+s);
                    p_q2=chulicdpai(p_q2);
                    if(p_q2->mode>400)
                    {
                        printf("对手出了\n");
                        who=1;
                        NOA=0;
                        for(s=0;s<=sernum-1;s++)
                        {
                            card(p+ser+s);
                            (p+ser+s)->ds=-1;
                            (p+ser+s)->hs=0;
                            printf("\n");  
                        }
                        sort(p);
                        printf("它还有%d张牌\n\n",paishu(p));
                        *p_q=*p_q2;
                        reini(p_q1);
                        reini(p_q2);
                        return p_q;
                    }
                }
            }
        }
        
        
        if(p_q->mode>400)
        {
            int ser,sernum;
            sernum=(p_q->zsmax)*(p_q->duishu);
            for(ser=max-sernum;ser>=0;ser--)
            {
                int s;
                for(s=0;s<=sernum-1;s++)	*(p_q2->cdpai+s)=*(p+ser+s);
                p_q2=chulicdpai(p_q2);
                if((p_q2->mode==p_q->mode&&p_q2->dsmax>p_q->dsmax)||p_q2->mode>p_q->mode)
                {
                    printf("对手出了\n");
                    who=1;
                    NOA=0;
                    for(s=0;s<=sernum-1;s++)
                    {
                        card(p+ser+s);
                        (p+ser+s)->ds=-1;
                        (p+ser+s)->hs=0;
                        printf("\n");  
                    }
                    sort(p);
                    printf("它还有%d张牌\n\n",paishu(p));
                    *p_q=*p_q2;
                    reini(p_q1);
                    reini(p_q2);
                    return p_q;
                }
            }
        }
    }
    
    printf("对手不出\n它还有%d张牌\n\n",paishu(p));
    NOA++;
    return p_q;
}