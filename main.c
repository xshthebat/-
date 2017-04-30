#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct Data
{
    char strStuName[20];
    char strStuNum[20];
    int strStuSorce;
}Data; //构造Data数据结构体
typedef struct NODE
{
	Data data;
    struct NODE* pFont;
	struct NODE* pNext;
}Node;   //构造数据节点
Node* p_Head=NULL;//建立数据链表头
Node* create(Node* pHead);//建立n个节点的双向链表
void print(Node* pHead);  //打印全部内容
int strNum(char* str); //判断学号是否正确
Node *findNode(Node* pHead); //查找指定学生
Node* insertNode(Node* pHead); //指定位置插入一个学生的信息
Node* delNode(Node*pHead);  //删除指定学生
void rewrite(Node* pHead);  //修改指定学生信息
Node* sort(Node* pHead);//按学生成绩排序
Node* reverse(Node* pHead);//反序学生信息
Node* freeLink(Node* pHead);//清空学生信息
void saveData(Node* pHead);//保存学生信息爱到文件
Node* loadData(Node* pHead);//从文件中读取学生的信息
void showOrder(void);//显示菜单
int main(void)
{   
    int flog=1,n;
	p_Head=loadData(p_Head);
	showOrder();
	while(flog)
	{
		printf("请输入指令:");
		scanf("%d",&n);
		switch(n)
		{
		  case 1: 
		  p_Head=create(p_Head);
		  break;
		  case 2:
		  print(p_Head); 
		  break;
		  case 3:
          p_Head=delNode(p_Head);
		  break;
		  case 4:
          p_Head=findNode(p_Head);
		  break;
		  case 5:
          p_Head=insertNode(p_Head);
		  break;
		  case 6:
          rewrite(p_Head); 
		  break;
		  case 7:
          p_Head=reverse(p_Head);
		  break;
		  case 8:
		  p_Head=sort(p_Head);
		  break;
		  case 9:
          showOrder();
		  break;
		  case 0:
          saveData(p_Head);
		  flog=0;
		  break;
		  default :
			printf("请输入正确指令!\n");
		}
	}
    p_Head=freeLink(p_Head);
    return 0;
}

Node* create(Node* pHead)//建立n个节点的双向链表
{
  int n,i,flog=0,j,flogs=0;  //节点长度 循环变量 标记
  Node* pFoot=NULL;
  Node* pNew=NULL;
  if(pHead!=NULL)
  {
	  printf("已建立链表,请不要重复建立\n");
	  return pHead;
  }
  pHead=(Node*)malloc(sizeof(Node));
  pHead->data.strStuSorce=0;
  strcpy(pHead->data.strStuName,"\0");
  strcpy(pHead->data.strStuNum,"\0");
  pHead->pFont=NULL;  //头节点前驱指向空
  pHead->pNext=NULL;  //头结点后驱指向空
  pFoot=pHead; //尾节点 指向首节点
  printf("要建立几个学生？:");
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
	  pNew=(Node*)malloc(sizeof(Node));
	  if(pNew==NULL)
	  {
		  printf("内存申请失败！\n");
		  return NULL;
	  }
      while(1)
	  {  
		  printf("请输入第%d组值\n",i);
		  printf("学生姓名:");
		  scanf("%s",pNew->data.strStuName);
		  printf("学生学号:");
		  scanf("%s",pNew->data.strStuNum);            //检验数据合法性
		  printf("学生成绩:");
		  scanf("%d",&pNew->data.strStuSorce);
		  if(pNew->data.strStuName!=NULL&&pNew->data.strStuNum!=NULL&&pNew->data.strStuSorce>=0)
		  {
			  flog++;
		  }
		  for(j=0;j<strlen(pNew->data.strStuNum);j++)
		  {
			   if(pNew->data.strStuNum[j]>='0'&&pNew->data.strStuNum[j]<='9')
			   {
				   flogs+=1;
			   }
		  }
		  if(flogs==strlen(pNew->data.strStuNum)&&flog==1)
		  {
			  flog=0;
			  flogs=0;
              break;
		  }
		  printf("您输入的信息有误 请重新输入!\n");
		  flog=0;
		  flogs=0;
	  }
	  printf("录入完成!\n");
	  pNew->pNext=NULL;  //新节点的后驱指空
      pNew->pFont=pFoot;//新节点的前驱指向尾
	  pFoot->pNext=pNew; //尾节点的后驱指向新节点
	  pFoot=pNew; //尾节点后移
  }
  return pHead; //返回头节点
}
void print(Node* pHead)  //打印全部内容
{
	Node *pTemp=pHead->pNext;
	if(pTemp==NULL||pHead==NULL)
	{
		printf("链表中无数据\n");
		return;
	}
	while(pTemp!=NULL)
	{
		printf("学生姓名:%s 学生学号:%s 学生成绩:%d\n",pTemp->data.strStuName,pTemp->data.strStuNum,pTemp->data.strStuSorce);
		pTemp=pTemp->pNext;
	}
	return ;
}
Node *findNode(Node* pHead) //查找指定学生
{
	Node* pTemp=NULL;
	char str[20]="\0";
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("链表中无数据\n");
		return NULL;
	}
	while(1)
	{
		printf("请输入要查找的学生的学号:");
	    scanf("%s",str);
		if(strNum(str))
		{
			break;
		}
		else
		{
			printf("学号输入错误,请重新输入\n");
		}
    }	
	pTemp=pHead->pNext;
	while(pTemp!=NULL&&strcmp(pTemp->data.strStuNum,str))
	{
		pTemp=pTemp->pNext;
	}
	if(pTemp==NULL)
	{
		return NULL;
	}
	printf("已查找到这个学生:\n");
	printf("学生姓名:%s 学生学号:%s 学生成绩:%d\n",pTemp->data.strStuName,pTemp->data.strStuNum,pTemp->data.strStuSorce);
	return pTemp;
} 
int strNum(char* str) //判断学号是否正确
{
    int i,flog=0;
	for(i=0;i<strlen(str);i++)
	{
          if(str[i]>='0'&&str[i]<='9')
		  {
			  flog++;
		  }
	}
	if(flog==strlen(str))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
Node* insertNode(Node* pHead) //指定位置插入一个学生的信息
{
	 Node* pNode=NULL;
	 Node* pNew=NULL;
	 Node* pTemp=findNode(pHead);
	 int flog=1,i,data,flogs=1;
	 if(pHead==NULL)
	 {
		 printf("链表为空\n");
		 return NULL;
	 }
	 while(pTemp==NULL)
	 {
		 printf("未找到插入位置 请重新查找\n");
		 pTemp=findNode(p_Head);
	 }
	 pNew=(Node*)malloc(sizeof(Node));
	 if(pNew==NULL)
	 {
		 printf("创建节点失败\n");
		 return NULL;
	 }
	 printf("请输入要插入学生的信息:\n");
	 while(flogs)
	 {
          printf("学生姓名:");
		  scanf("%s",pNew->data.strStuName);
		  printf("学生学号:");
		  scanf("%s",pNew->data.strStuNum);
		  printf("学生成绩:");
		  scanf("%d",&pNew->data.strStuSorce);
		  if(pNew->data.strStuName!=NULL&&strNum(pNew->data.strStuNum)&&pNew->data.strStuSorce>=0)
		  {
			  flogs=0;
		  }
		  else
		  {
			  printf("您输入的信息有误,请重新输入\n");
		  }
	 }
	 while(flog)
	 {
		 printf("在此学生前或后插入？\n 0.前 1.后:");
	     scanf("%d",&i);
		 switch(i)
		 {
	     case 1:
		    if(pTemp->pNext==NULL)
			 {
                //在尾节点后驱插入一个新节点
				 pNew->pNext=NULL;  //new后驱指向NULL
				 pNew->pFont=pTemp; //new的前驱指向tem
				 pTemp->pNext=pNew;  //tem的后驱指向new
			 }
			 else
			 {
                  //在其他位置后驱插入一个新节点
				 pNew->pNext=pTemp->pNext;   //new的后驱指向 tem的后驱
				 pNew->pFont=pTemp;  //new的前驱 指向tem
				 (pTemp->pNext)->pFont=pNew; //tem的后驱的前驱 指向new
		 	     pTemp->pNext=pNew;  //tem的后驱指向 new	 
			 }
			 flog=0;
			 break;
		 case 0:
			 pNew->pNext=pTemp; //new的后驱指向tem
			 pNew->pFont=(pTemp->pFont);  //new的前驱指向 temp的前驱
			 (pTemp->pFont)->pNext=pNew;  //tem的前驱的后驱指向new
			 pTemp->pFont=pNew;   //tem的前驱指向new
			 flog=0;
			 break;
		 default :
			 printf("请输入正确的指令\n");
		 }
	 }
	 printf("插入成功\n");
	 print(pHead);
	 return pHead;
}

Node* delNode(Node* pHead)                          //删除指定学生
{
	Node* pTemp=findNode(pHead); 
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("链表为空\n");
		return NULL;
	}
	while(pTemp==NULL)
	{
		printf("未找到指定学生请重新查找\n");
		pTemp=findNode(pHead);
	}
    if(pTemp->pNext==NULL) //若要删尾节点
	{   
		(pTemp->pFont)->pNext=NULL;  //尾节点的前驱的后驱指空
		 pTemp->pFont=NULL;  //尾节点的前驱指空
         free(pTemp);
		  pTemp=NULL;
		  printf("删除成功\n");
		  print(pHead);
		  return pHead;
	}
	else
	{
		(pTemp->pFont)->pNext=pTemp->pNext; //此节点的前驱的后驱指向 此节点的后驱
		(pTemp->pNext)->pFont=pTemp->pFont; //此节点的后驱的前驱指向 此节点的前驱
		pTemp->pFont=NULL; //此节点的前后驱指空
		pTemp->pNext=NULL;
		printf("删除成功！\n");
		print(pHead);
		return pHead;
	}
}
void rewrite(Node* pHead) //修改指定学生的信息
{
	Node* pTemp=NULL;
	int i,flog=1,n,flogs=1;
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("学生信息为空\n");
		return ;
	}
	pTemp=findNode(pHead);
	while(pTemp==NULL)
	{
		printf("未找到此学生，请重新查找\n");
		pTemp=findNode(pHead);
	}
	while(flog)
	{
		while(flogs)
		{ 
			printf("要修改的学生信息:\n 1.姓名 2.学号 3.成绩 0.退出\n");
		    scanf("%d",&n);
			switch(n)
			{
			  case 1:printf("请输入修改后学生的姓名：");
		             scanf("%s",pTemp->data.strStuName);
					 break;
			  case 2:printf("请输入修改后学生的学号：");
		             scanf("%s",pTemp->data.strStuNum);
					 break;
			  case 3:printf("请输入修改后学生的成绩：");
		             scanf("%d",&pTemp->data.strStuSorce);
					 break;
			  case 0:
				     flogs=0;
					 break;
			  default:
				  printf("请输入正确指令:\n");
			}
        
		}
		if(pTemp->data.strStuName!=NULL&&strNum(pTemp->data.strStuNum)&&pTemp->data.strStuSorce>=0)
		{
			flog=0;
		}
		else
		{
			printf("您输入的学生信息有误，请重新输入\n");
		}
	}
	return ;
}
Node* sort(Node* pHead) //按成绩高低排序
{
	Node* pTemp=NULL;
	Node* pFoot=NULL;
	int i=0;
	int j=0;
	int n=0;
    if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("学生信息为空\n");
		return NULL;
	}
	pTemp=pHead->pNext;
	while(pTemp!=NULL)
	{
        pFoot=pTemp; //找出尾节点
		pTemp=pTemp->pNext;//temp后移
		n++;
	}
	for(i=1;i<n;i++)
    {
		for(pTemp=pHead->pNext,j=1;j<n;j++)
        {
			if(pTemp->data.strStuSorce>pTemp->pNext->data.strStuSorce)  //冒泡排序
			{
                if(pTemp->pNext->pNext==NULL)  //若小后为空
				{
					pTemp->pFont->pNext=pTemp->pNext; //大的前驱的后驱指向小的
					pTemp->pNext->pNext=pTemp; //小的后驱指向大的
					pTemp->pNext->pFont=pTemp->pFont; //小的前驱指向大的前驱
					pTemp->pFont=pTemp->pNext; //大的前驱指向小的
					pTemp->pNext=NULL;  //大的后驱指向NULL
				}
				else
				{
                     (pTemp->pFont)->pNext=pTemp->pNext;               //大的前驱的后驱指向小的
					 ((pTemp->pNext)->pNext)->pFont=pTemp;             //小的后驱的前驱指向大的
                      pTemp->pNext=((pTemp->pFont)->pNext)->pNext;     //大的后驱指向小的后驱					 
				      ((pTemp->pFont)->pNext)->pNext=pTemp;            //小的后驱指向大的
                       ((pTemp->pFont)->pNext)->pFont=pTemp->pFont;    //小的前驱指向大前
				       pTemp->pFont=((pTemp->pFont)->pNext);            //大的前驱指向小的
				}
			}
			else
			{
				pTemp=pTemp->pNext;
			}

		}
	}
	print(pHead);
	return pHead;
}
Node* reverse(Node* pHead)   //反序信息
{
	Node* pNewHead=(Node*)malloc(sizeof(Node));//倒序后的头
	 Node* pTemp=pHead->pNext;//临时节点p指向第一个节点
	 Node* pCurrent=NULL;//记住临时节点的下一个
	 Node* pEnd=pNewHead;//记住新链表的尾
	 if(pHead==NULL||pHead->pNext==NULL)
	 {
		 printf("链表为空\n");
		 return NULL;
	 }
	 if(pNewHead==NULL)
	 {
		 printf("申请内存失败\n");
		 return NULL;
	 }
	 pNewHead->pFont=NULL;
	 pNewHead->pNext=NULL; //初始化新头
	 while(pTemp->pNext!=NULL)
	 {
		 pTemp=pTemp->pNext;  //将Temp指向尾
	 }
	 while(pTemp!=pHead)  //遍历到首节点结束
	 {  
		 pCurrent=pTemp->pFont;  //记住零时节点的前一个
		 if(pNewHead->pNext==NULL) //若新链表为空
		 {
              pTemp->pFont=pNewHead;
			  pTemp->pNext=NULL;
			  pNewHead->pNext=pTemp;   //连到新链表上;
              pEnd=pEnd->pNext;  //尾后移
		 }
		 else
		 {
			 pTemp->pFont=pEnd;
			 pTemp->pNext=NULL;
			 pEnd->pNext=pTemp;  //连在新表后
			 pEnd=pEnd->pNext;
		 }
		 pTemp=pCurrent; //Temp向前移
	 }
	 print(pNewHead);
	 free(pHead);
	 pHead=NULL; //清除老头
	 return pNewHead;
}
Node* freeLink(Node* pHead) //清空学生信息
{
	Node* pTemp=NULL;
	Node* pCurrent=NULL;
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("链表为空\n");
		return NULL;
	}
	pTemp=pHead;
    while(pTemp!=NULL)
	{   
		pCurrent=pTemp;
		pTemp=pTemp->pNext;
		free(pCurrent);
		pCurrent=NULL;

	}
	pHead->pNext=NULL;
	printf("清空完成\n");
	print(pHead);
	return pHead;
}
void saveData(Node* pHead)//保存学生信息到文件中
{
	FILE *p=NULL;
	Node *pTemp=NULL;
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("学生信息为空\n");
		return ;
	}
	p=fopen("dat.txt","w+");
	   if(p!=NULL)
	   {    
		  pTemp=pHead->pNext;
		  while(pTemp!=NULL)
		  {
			  fprintf(p,"姓名:%s 学号:%s 成绩:%d\n",pTemp->data.strStuName,pTemp->data.strStuNum,pTemp->data.strStuSorce);
			  pTemp=pTemp->pNext;
		  }
		  if(fclose(p)==0)
		  {  
			   p=NULL;
			   return ;
		  }
		  else
		  {
			  printf("文件关闭失败\n");
			  return ;
		  }
		}
       else
		{
			printf("文件打开失败\n");
			return;
		}
}
Node* loadData(Node* pHead)
{
      FILE *p=fopen("dat.txt","r+");
	  Node *pTemp=NULL;
	  Node *pNew=NULL;
      char strname[20];
	  char strnum[20];
	  int sorce;
	  pHead=(Node*)malloc(sizeof(Node));
      pHead->data.strStuSorce=0;
      strcpy(pHead->data.strStuName,"\0");
      strcpy(pHead->data.strStuNum,"\0");
	  pHead->pFont=NULL;
	  pHead->pNext=NULL;
	  pTemp=pHead;
	  while(fscanf(p,"姓名:%s 学号:%s 成绩:%d\n",strname,strnum,&sorce)==3)
	  { 
		  pNew=(Node*)malloc(sizeof(Node));
		  if(pNew==NULL)
		  {
			  printf("内存申请失败\n");
			  return NULL;
		  }
		  strcpy(pNew->data.strStuName,strname);
		  strcpy(pNew->data.strStuNum,strnum);
		  pNew->data.strStuSorce=sorce;
		  pNew->pNext=NULL;
		  pNew->pFont=pTemp;
		  pTemp->pNext=pNew;
		  pTemp=pTemp->pNext;
	  }
	  fclose(p);
	  p=NULL;
	  return pHead;
}
void showOrder(void)
{
    printf("*********菜单*******\n");
	printf("*****1.建立链表*****\n");
	printf("*****2.打印链表*****\n");
	printf("*****3.删除节点*****\n");
    printf("*****4.查找节点*****\n");
	printf("*****5.插入节点*****\n");
	printf("*****6.修改节点*****\n");
	printf("*****7.反序链表*****\n");
	printf("*****8.排序链表*****\n");
	printf("*****9.查看菜单*****\n");
	printf("*****0.退出保存*****\n");
}
