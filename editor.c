#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100
#define NOT_FOUND -1
//定义行结构体：
struct line
{
	char text[MAX_LEN];  //本行文本
	int num;  //行号
	struct line *next; //指向下一个行的指针
	struct line *prior; //指向前一个行的指针
};
int lnum;
struct line *start; 	   //指向线性表中第一行的指针
struct line *last; 	   //指向线性表中最后一行的指针
struct line *find(int);    //查找指定行是否存在
void patchup(int, int);    //对当前行以后的每行的行号加1或
void delete_text(int);     //删除一行文字
void list();   //显示文件的全部内容
void save();   //保存文件
void load();   //打开文件，初始化线性表
void insert(char str[], int linenum, int position); //插入文字到一行的中间
void printline(int linenum);   //打印一行文字
void deletestr(int linenum, int position, int lenth); //删除一个字符串
int findstr(char * to_find);  //查找字符串
int menu_select();        //显示主菜单
int menu_select_insert();//显示插入功能子菜单
int menu_select_delete();//显示删除功能子菜单
int menu_select_print(); //显示打印功能子菜单
int menu_select_move();  //显示移动功能子菜单
void enter(int linenum); //插入一行文字
void enter_empty(int linenum); //插入一个空白行
//下列函数是系统主函数，提供系统主界面，通过选择项转入执行插入、删除、查存盘、读人文件等功能的界面。
int main(void)
{
	char str[MAX_LEN];
	int choice;
	int linenum = 1;
	int number = 0;
	start = NULL;
	last = NULL;
	load(); //打开文件，初始化线性表
	do{
		choice = menu_select();
		switch (choice)
		{
		case 1:		//执行插入功能	
			choice = menu_select_insert();//显示插入子菜单
			switch (choice)
			{
			case 1:   //插入一行
				printf("\t行号:");
				scanf("%d", &linenum);
				enter(linenum);
				break;
			case 2:  //插入到指定行的指定列
				printf("输入插入位置一行号：");
				scanf("%d", &linenum);
				printf("输入插入位置-列号：");
				scanf("%d", &number);
				printf("要插入的字符串：");
				scanf("%s", str);
				insert(str, linenum, number);
				break;
 
			case 3:   //退出插入
				break;
			}
			break;
		case 2:			//执行删除功能
			choice = menu_select_delete();  // 删除子菜单
			switch (choice)
			{
			case 1:   //删除指定行
				printf("\t行号:");
				scanf("%d", &linenum);
				break;
			case 2:   //删除指定的字符串
				printf("要删除的字符串：");
				scanf("%s", str);
				number = findstr(str);
				if (number == NOT_FOUND)
					printf("没有找到");
				else
					deletestr(lnum, number, strlen(str));
				break;
			case 3: 	//退出删除
				break;
			}
			break;
		case 3:  	//执行显示功能
			choice = menu_select_print(); //显示子菜单
			switch (choice) 	//显示指定行
			{
			case 1:
				printf("\t行号:");
				scanf("%d", &linenum);
				printline(linenum);
				break;
			case 2:		//显示全部
				list();
				break;
			case 3:		//退出显示
				break;
			}
			break;
		case 4:			//执行查找功能
			printf("输入想要查找的字符串：");
			scanf("%s", str);
			number = findstr(str);
			if (number == NOT_FOUND)
				printf("没有找到");
			else
				printf("要查找的字符串所在行号:%d，列号:%d\n", lnum, number + 1);
			break;
		case 5:		//执行替换功能
			printf("输入被替换的字符串：");
			scanf("%s", str);
			number = findstr(str);
			if (number == NOT_FOUND)
				printf("没有找到");
			else
			{
				deletestr(lnum, number, strlen(str));
				printf("要替换的字符串：");
				scanf("%s", str);
				insert(str, lnum, number + 1);
			}
			break;
 
		case 6:     //执行移动功能
			choice = menu_select_move();   //移动子菜单
			switch (choice)
			{
			case 1:   // 向下移动一行
				printf("输人要移动的字符串所在行号：");
				scanf("%d", &linenum);
				enter_empty(linenum);
				break;
			case 2:   //向上移动一行
				printf("输入要移动的字符串所在行号：");
				scanf("%d", &linenum);
				delete_text(linenum - 1);
				break;
			case 3:   //向右移动一列
				printf("输人要移动的字符串所在行号：");
				scanf("%d", &linenum);
				printf("输入要移动的字符串所在列号：");
				scanf("%d", &number);
				str[0] = ' ';
				str[1] = '\0';
				insert(str, linenum, number);
				break;
			case 4:   //向左移动
				printf("输入要移动的字符串所在行号：");
				scanf("%d", &linenum);
				printf("输入要移动的字符串所在列号：");
				scanf("%d", &number);
				if (number <= 0)
					printf("该列不存在");
				else
					deletestr(linenum, number - 2, 1);
				break;
			case 5:   //退出移动
				break;
			}
			break;
		case 7:		//执行存盘功能
			save();
			break;
		case 8:		//执行读入文件功能
			load();
			break;
		case 9:		//执行退出功能
			exit(0);
			break;
		}
	} while (1);
	return 0;
}
//下列函数是主菜单功能的提示界面，其功能是说明主菜单中选项
int menu_select()
{
	int c;
	printf("\n\t\t1.插入\n");
	printf("\t\t2.删除\n");
	printf("\t\t3.显示\n");
	printf("\t\t4.查找\n");
	printf("\t\t5.替换\n");
	printf("\t\t6.移动\n");
	printf("\t\t7.文件存盘\n");
	printf("\t\t8.装入文件\n");
	printf("\t\t9.退出\n");
	do
	{
		printf("\n\n\t\t请按数字选择：");
		scanf("%d", &c);
	} while (!(c >= 1 && c <= 9));
	return(c);
}
 
//下列函数是插入子菜单功能的提示界面，其功能是说明在插入菜单下选项的含义。
int menu_select_insert()
{
	int c;
	printf("\n\t\t1.插入一行文字\n");
	printf("\t\t2.插入一段文字\n");
	printf("\t\t3.返回上级菜单\n");
	do{
		printf("\n\n\t\t请按数字选择：");
		scanf("%d", &c);
	} while (!(c >= 1 && c <= 3));
	return(c);
}
//下列函数是删除子菜单功能的提示界面，其功能是说明在删除子菜单下选项的含义。
int menu_select_delete()
{
	int c;
	printf("\n\t\t1.删除一行文字\n");
	printf("\t\t2.删除一段文字\n");
	printf("\t\t3.返回上级菜单\n");
	do{
		printf("\n\n\t\t请按数字选择：");
		scanf("%d", &c);
	} while (!(c >= 1 && c <= 3));
	return(c);
}
//下列函数是显示子菜单功能的提示界面，其功能是说明在显示子菜单下选项的含义
int menu_select_print()
{
	int c;
	printf("\n\t\t1.显示一行\n");
	printf("\t\t2.全部显示\n");
	printf("\t\t3.返回上级菜单\n");
	do{
		printf("\n\n\t\t请按数字选择：");
		scanf("%d", &c);
	}while(!(c >= 1 && c <= 3));
	return(c);
}
//下列函数是移动子菜单功能的提示界面，其功能是说明在移动子菜单下选项的含义
int menu_select_move()
{
	int c;
	printf("\n\t\t1.向下移动一行\n");
	printf("\t\t2.向上移动一行\n");
	printf("\t\t3.向右移动一列\n");
	printf("\t\t4.向左移动一列\n");
	printf("\t\t5.返回上级菜单\n");
	do{
		printf("\n\n\t\t请按数字选择：");
		scanf("%d", &c);
	} while (!(c >= 1 && c <= 5));
	return(c);
}
//下列函数的功能是在指定的行号 linenum处插入一行文字。
void enter(int linenum)
{
	struct line * info, * q, * p;
	p = start;
	q = NULL;
	while (p && p->num != linenum) //找到插入行
	{
		q = p;
		p = p->next;
	}
	if (p == NULL && (q->num + 1) != linenum)	//指定行不存在，不能插入
	{
		printf("输入的行号不存在");
	}
	else // 指定行存在，进行插入
	{
		info = (struct line *)malloc(sizeof(struct line));
		printf("输入要输入的字符串");
		scanf("%s", info->text);
		info->num = linenum;
		if (linenum == 1)  //插入在第一行
		{
			info->next = p;
			p->prior = info;
			info->prior = NULL;
			start = info;
		}
		else if (q->num != linenum)  //插入在最后一行
		{
			q->next = info;
			info->next = p;
			info->prior = q;
		}
		else     //插入在其他行
		{
			q->next = info;
			info->next = p;
			p->prior = info;
			info->prior = q;
		}
		while (p)   //如果不是插入在最后一行，插入行后面的行号都加1
		{
			p->num = p->num + 1;
			p = p->next;
		}
	}
}
 
//下列函数是为其他功能提供的一个辅助函数，它的功能是当文本内容插在文件中间时
//其下面的内容的行号必须增加1，而删除时，被删除的文本后面的行号必减1.
void patchup(int n, int incr)
{
	struct line *i;
	i = find(n);
	i = i->next;
	while (i)
	{
		i->num = i->num + incr;
		i = i->next;
	}
}
//下列函数的功能是在指定行处插入一个空白行。
void enter_empty(int linenum)
{
	struct line *info, *p;
	info = (struct line *)malloc(sizeof(struct line));
	if (!info)
	{
		printf("\t！内存不够！\n");
		exit(0);
	}
	info->text[0] = ' ';
	info->text[1] = '\0';
	info->num = linenum;
	if (find(linenum))    //如果要插人的行号存在，则进行插入
	{
		p = start;
		if (linenum == 1)    //插入在首行
		{
			info->next = p;
			start = info;
			info->prior = NULL;
			p->prior = info;
		}
		else  //插入在其他行
		{
			while (p->next->num != linenum)
				p = p->next;
			info->next = p->next;
			p->next->prior = info;
			p->next = info;
			info->prior = p;
		}
		patchup(linenum, 1);
	}
	else
		printf("该行不存在");
}
 
//下列函数的功能是插入文字到一行的中间。要是插入位置和现有位置中间有间隔，会补全空格
void insert(char str[], int linenum, int position)
{
	struct line * info;
	int len, i;
	int lenth;
	char rest_str[MAX_LEN], nostr[2] = { " " };
	info = start;
	while (info && info->num != linenum)   //查询要插入的行
	{
		info = info->next;
	}
	if (info == NULL)
		printf("不存在该行！\n");
	else if (position < 0)
		printf("不存在该列！\n");
	else    //如果行和列都存在，则进行插入
	{
		lenth = strlen(info->text);
		if (lenth < position)	//插入列大于本行文件列数
		{
			len = position - lenth - 1;
			for (i = 0; i < len; i++)
				strcat(info->text, nostr);   //将空余的部分插入空格符
			strcat(info->text, str);    //插入字符到列的未尾
		}
		else   //插入列在本行文字的中间
		{
			strcpy(rest_str, &info->text[position - 1]);
			strcpy(&info->text[position - 1], str);
			strcat(info->text, rest_str);
		}
	}
}
 
//下列函数的功能是删除指定行、指定位置、长度为 lenth的一段文字。
void deletestr(int linenum, int position, int lenth)
{
	struct line * info;
	char rest_str[MAX_LEN];
	info = find(linenum);
	if (info == NULL)
		printf("该行没有字符！n");
	else
	{
		if (strlen(info->text) <= (position + lenth))  //本行的字符长度<=待删除的列号+删除长度，直接在当前位置插入'\0'
			info->text[position] = '\0';
		else
		{
			strcpy(rest_str, &info->text[position + lenth]);
			strcpy(&info->text[position], rest_str);
		}
	}
}
//下列函数的功能是删除指定行号 lineup的文字。
void delete_text(int linenum)
{
	struct line * info, *p;
	info = start;
	while ((info->num < linenum) && info)
		info = info->next;
	if (info->next == NULL)
		printf("该行不存在");
	else
	{
		p = info->next;
		if (start == info) //如果删除的是第一行
		{
			start = info->next;
			if (start)  //如果删除后，不为空
				start->prior = NULL;
			else  //删除后为空
				last = NULL;
		}
		else
		{
			info->prior->next = info->next;  //指定行的上一行指向指定行的下一行
			if (info != last) //如果不是最后一行
				info->next->prior = info->prior;  //修改其下一行的指向头的指针 
			else  //如果是最后一行，修改尾指针
				last = info->prior;
		}
		free(info);
		while (p)
		{
			p->num = p->num - 1;
			p = p->next;
		}
	}
}
//下列函数的功能是查找一段文字。
int findstr(char * to_find)
{
	struct line * info;
	int i = 0, find_len, found = 0, position;
	char substring[MAX_LEN];
	info = start;
	lnum = 0;  //匹配到的行号
	find_len = strlen(to_find);
	while (info && !found)   //查询
	{
		i = 0;  //行间循环
		while (!found && (i <= strlen(info->text) - find_len))  //行内查找循环
		{
			strcpy(substring, &info->text[i], find_len);
			substring[find_len] = '\0';
			if (strcmp(substring, to_find) == 0)
			{
				found = 1;
				lnum = info->num;
			}
			else
				++i;
		}
		info = info->next;
	}
	if (found)  //查找成功
		position = i;
	else   //查找不成功
		position = NOT_FOUND;
	return(position);
}
//下列函数的功能是查找指定行，如果查找成功返回结点所在的行指针。
struct line * find(int linenum)
{
	struct line * info;
	info = start;
	while (info)
	{
		if (linenum != info->num)
			info = info->next;
		else
			break;
	}
	return (info);
}
 
//下列函数的功能是显示指定行
void printline(int linenum)
{
	struct line *info;
	info = find(linenum);
	if (info)
		printf("%d:%s\n", info->num, info->text);
	else
		printf("该行不存在");
}
//下列函数的功能是显示线性表中的所有文本
void list()
{
	struct line * info;
	info = start;
	while (info)
	{
		printf("%d:%s\n", info->num, info->text);
		info = info->next;
	}
	printf("\n\n");
}
//下列函数的功能是把线性表中的所有文字保存到文件中
void save()
{
	struct line	* info;
	char * p;
	FILE * fp;
	if ((fp = fopen("D:\\text.txt", "w")) == NULL){
		printf("\t文件打不开！n");
		exit(0);
	}
	printf("\t正在存入文件！\n");
	info = start;
	while (info)
	{
		p = info->text;
		while (*p)
			putc(*p++, fp);
		putc('\n', fp);
		info = info->next;
	}
	fclose(fp);
}
//下列函数的功能是把文本文件中的内容读入到线性表中。
void load()
{
	struct line *info, *temp;  //info指向当前行，temp指向info的前驱行
	char c;
	FILE *fp;  //文件指针
	int inct, i;  //行计数器
	temp = NULL;
	if ((fp = fopen("D:\\text.txt", "r")) == NULL)
	{
		printf("\t文件打不开！\n");
		exit(0);
	}
	printf("\n\t正装入文件！\n");
	start = (struct line*)malloc(sizeof(struct line)); //动态生成一行的结点空间
	info = start;
	inct = 1;
	while ((c = fgetc(fp)) != EOF)
	{
		i = 0;
		info->text[i] = c;
		i++;
		while ((c = fgetc(fp)) != '\n')  //从文件中读取一行字符到线性表中，文件中每一行以\n为结束标
		{
			info->text[i] = c;
			i++;
		}
		info->text[i] = '\0';  //线性表中每行末尾的结束标志
		info->num = inct++;  //行号和计数器都加1
		info->next = (struct line*)malloc(sizeof(struct line));
		if (!info->next)
		{
			printf("\n\t内存已经用完！");
			exit(0);
		}
		info->prior = temp;
		temp = info;
		info = info->next;
	}
	temp->next = NULL;
	last = temp;
	free(info);
	start->prior = NULL;
	fclose(fp);
}
