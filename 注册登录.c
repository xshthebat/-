#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct CODE
{
	char name[20];
	char password[20];
	struct CODE *pNext; 
}Code; //注册信息节点声明
Code* P_Head=NULL;   //声明注册信息头
Code* addCode(Code* pHead); //增加一个注册信息 
void saveCode(Code* pHead); //保存注册信息 
Code* loadCode(Code* pHead);//读取注册信息 
int lookup(Code* pHead,char* name); //判断是否存在用户  
int lookupPassword(Code* pHead,char* name,char * password); //查询指定账户密码是否正确 
void print(Code* pHead);//打印账号密码 
int loginIn(Code* pHead);//登录程序
int main(void)
{   
    P_Head=loadCode(P_Head);
    loginIn(P_Head);
    saveCode(P_Head);
	return 0;
} 
Code* addCode(Code* pHead)
{
	Code* pNew=(Code*)malloc(sizeof(Code));
	Code* pTemp=NULL; //记住尾节点 
	char ch;
	char psw[20]; //二次输入密码检验; 
	int p=0,flog1=1,flog2=1;
	if(pNew==NULL)
	{
		printf("内存申请失败\n");
		return NULL;
	} 
	pTemp=pHead;
	while(pHead!=NULL&&pTemp->pNext!=NULL)
	{
		pTemp=pTemp->pNext;   //遍历找尾 头不为空 
	}
	while(flog1) //判断是否注册过  
   {
			printf("请输入注册信息:\n");
			printf("账号:");
			scanf("%s",pNew->name);
			if(lookup(pHead,pNew->name)==0) //判断是否存在用户 
			{
				flog1=0;
				printf("该账号可以使用!\n"); 
			}
			else
			{
				printf("该账号已经注册过,请重新输入\n");
				continue;
			}            
			while(flog2)
		    {	
		       printf("密码:");
			   while((ch=getch())!='\r')//判断是否为回车
					{
						if(ch==8)
						{
							putchar('\b');
							putchar(' ');
							putchar('\b');
							if(p>0)
							p--;
						} 
						if(!isdigit(ch)&&!isalpha(ch))//判断是否是数字或字符串
						  continue;
						putchar('*');
						pNew->password[p++]=ch;//保存密码 
					} 
					pNew->password[p]='\0';//字符串结尾
					p=0;
					printf("\n请再次输入密码:");
						while((ch=getch())!='\r')//判断是否为回车
					{
						if(ch==8)
						{
							putchar('\b');
							putchar(' ');
							putchar('\b');
							if(p>0)
							p--;
						} 
						if(!isdigit(ch)&&!isalpha(ch))//判断是否是数字或字符串
						  continue;
						putchar('*');
						psw[p++]=ch;//保存密码 
					} 
					psw[p]='\0';//字符串结尾
					p=0;
					if(strcmp(pNew->password,psw)==0)
					{
						flog2=0;
					}
					else
						printf("\n二次密码输入错误,请重新输入\n");
			} 
	}
	pNew->pNext=NULL;
	if(pHead==NULL)   //头若为空 新节点变为头 
	{
		pHead=pNew;
	printf("\n注册成功！\n");
		return pHead;
	}	
	pTemp->pNext=pNew; //头不为空 接在尾之后 
	printf("\n注册成功！\n");
	return pHead;
} 
void saveCode(Code* pHead) //保存注册信息到文件中
{
	Code* pTemp=NULL;
	FILE *p=NULL;
	char buf[30];
	if(pHead==NULL)
	{
		printf("注册信息为空\n");
		return ;
	} 
	p=fopen("register.dat","wb+");
	if(p==NULL)
	{
		printf("文件打开失败\n");
		return ;
	}
	pTemp=pHead;
    while(pTemp!=NULL)
    {
    	strcpy(buf,pTemp->name);
		strcat(buf," ");
		strcat(buf,pTemp->password);
		fwrite(buf,1,strlen(buf),p);
		fwrite("\r\n",1,strlen("\r\n"),p);
    	pTemp=pTemp->pNext;
	}
	fclose(p);
	p=NULL;
} 
Code* loadCode(Code* pHead)  //读取注册信息
{
	FILE * p=NULL;
	Code *pTemp=NULL;
	char buf[30];
	int i,j,flog=1; 
	Code* pNew=NULL; 
	p=fopen("register.dat","rb+");
	if(p==NULL)
	{
		printf("文件打开失败\n");
		return NULL;
	}
	while(fgets(buf,30,p)!=NULL)
	{
			pNew=(Code*)malloc(sizeof(Code));
	      if(pNew==NULL)
				{
					printf("内存申请失败\n");
					return NULL; 
				}
		 for(i=0,j=0;i<30;i++)
	     {
	       if(flog==1)
		 	 {
		 		pNew->name[i]=buf[i];
		 		if(buf[i]==' ')
	     	   {
                pNew->name[i]='\0';
                flog=0;
                continue;
			   }
		      }
			if(flog==0)
			   {
				pNew->password[j]=buf[i];
				if(buf[i]=='\r')
				{
					pNew->password[j]='\0';
					flog=1;
				    break;
				}
				j++;
			   }
		}
		   pNew->pNext=NULL;
		     if(pHead==NULL)
			   {
			   	  pHead=pNew;
			   	  pTemp=pHead;
			   }
			else
			   {
			   	pTemp->pNext=pNew; 
			   	pTemp=pTemp->pNext;
			   }
	}
	fclose(p);
	return pHead;
}
int lookup(Code* pHead,char* name) //判断是否存在用户
{
	Code *pTemp=NULL;
	if(pHead==NULL)
	{
		return 0;
	} 
	pTemp=pHead;
	while(pTemp!=NULL)
	{
		if(strcmp(name,pTemp->name)==0)
		{
			return 1;
		}
		pTemp=pTemp->pNext;
	}
	return 0;
} 
void print(Code*pHead)
{
	Code* pTemp=NULL;
	if(pHead==NULL)
	{
		return ;
	}
	pTemp=pHead;
	while(pTemp!=NULL)
	{
		printf("账号:%s,密码:%s\n",pTemp->name,pTemp->password);
		pTemp=pTemp->pNext;
	}
	return ;
} 

int lookupPassword(Code* pHead,char* name,char * password) //查询指定账户密码是否正确
{
	Code* pTemp;
	if(pHead==NULL)
	{
		return 0; 
	} 
	if(lookup(pHead,name)==1)
	{
		pTemp=pHead;
		while(pTemp!=NULL)
		{
			if(strcmp(pTemp->password,password)==0)
			{
			   return 1;
			}
			pTemp=pTemp->pNext;
		}
		return 0;
	}
	
} 
int loginIn(Code* pHead) //登录程序
{
    Code* pTemp=NULL;
    char name[20];
	char password[20]; 
	char ch;
	int p,flog=1,n;
	if(pHead==NULL)
	{
		printf("信息为空,请注册\n");
		return 0; 
	}
   while(1)
 {	printf("请输入账号信息:\n");
	printf("账号:");
	scanf("%s",name);
	printf("密码:");
	 while((ch=getch())!='\r')//判断是否为回车
	  {
			if(ch==8)
			{
			   putchar('\b');
			   putchar(' ');
			   putchar('\b');
			   if(p>0)
				p--;
			} 
			if(!isdigit(ch)&&!isalpha(ch))//判断是否是数字或字符串
				continue;
			putchar('*');
			password[p++]=ch;//保存密码 
     } 
		password[p]='\0';//字符串结尾 
		p=0;
	 if(lookupPassword(pHead,name,password)==1)
	 {
	 	printf("\n登录成功!\n");
	 	return 1; //根据账号 判断权限  后续... 
	 }
	 printf("\n账号或密码错误,请重试，或退出登录\n");
	 printf("1.重试 2.退出登录\n");
	 while(flog) 
	 {
	 scanf("%d",&n);
	  switch(n)
	  {case 1 :
	  	flog=0;
	 	break;
	  case 2 :
	  	flog=0;
	 	return 0;
	 	break;
	  default :
	 	printf("请输入正确指令\n"); 
	  } 
	 }
 }
} 
