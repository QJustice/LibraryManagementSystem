// 图书管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//图书管理
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

//结构体群
struct User																//用户
{
	char id[100];														//用户名
	char password[100];													//密码
	char type[100];														//用户类型
	struct User* next;
};

struct Reader															//读者
{
	char id[100];														//用户名		
	char company[100];													//单位
	char telephone[100];												//联系方式
	int can_borrow;														//可借数
	int already_borrow;													//已借数
	struct Reader* next;
};

struct Book
{
	int num;															//序列号
	char id[100];														//书号
	char type[100];														//书名
	char author[100];													//作者
	char press[100];													//出版社
	int stock;															//库存
	int borrowed;														//借出
	int p1;
	int p2;
	int p3;
	struct Book* next;
};

struct Data
{
	int year;															//年
	int month;															//月
	int day;															//日
};

struct Brrecord
{
	char reader_id[100];												//借书者用户名
	char book_id[100];													//书号
	struct Data borrow_data;											//借书日期
	struct Data return_data;											//还书日期
	struct Brrecord* next;
};

struct Key
{
	char keyword[100];													//检索关键字
	int head;															//头指针
	int lengh;															//长度
	struct Key* next;
};

//全局常量

//路径常量
const char* file_reader_data = "D://booksystem//Reader_data.txt";
const char* file_user_data = "D://booksystem//User_data.txt";
const char* file_book_data = "D://booksystem//data//book.txt";
const char* file_brrecord_data = "D://booksystem//data//book_borrowing_and_returning_records.txt";
const char* file_name_data = "D://booksystem//data//book_name.txt";
const char* file_author_data = "D://booksystem//data//book_aut.txt";
const char* file_press_data = "D://booksystem//data//book_pub.txt";
//初始化常量	
const int loanable_number = 10;											//初始可借数
const int borrowed_amount = 0;											//初始已借数

//调试工具函数
void print_test(struct Brrecord* p)
//void print_test(struct Book* p)
{
	while (p)
	{
		printf("%s %s %d-%d-%d %d-%d-%d\n", p->reader_id, p->book_id, p->borrow_data.year, p->borrow_data.month, p->borrow_data.day, p->return_data.year, p->return_data.month, p->return_data.day);
		//printf("%d %s %s %d %d\n", p->num, p->id, p->type, p->stock, p->borrowed);
		p = p->next;
	}
}

//函数群

//工具函数
void start_interface(void);												//开始界面
void id_register(void);													//注册
int login_system(void);													//登陆系统
void exit_program(void);												//退出程序
void display_main_menu(int);											//显示主菜单
void Encrypted_input(char*);											//加密输入
void Encrypted_input_confirm(char*);									//加密确认输入
void dictionary_sort_show(int);											//字典排序输出
struct Data current_system_time(void);									//提取系统当前日期
void clear_buffer(void);												//清空缓冲区
void program_sleep(void);												//程序休眠

//系统管理员
void user_management(void);												//用户管理
void reader_management(void);											//读者管理

//用户管理菜单
void user_information_input(void);										//用户信息输入
void user_information_modification(void);								//用户信息修改
void user_information_deletion(void);									//用户信息删除
void user_information_display(void);									//用户信息显示
void user_password_modification(void);									//用户密码修改

//读者管理菜单	
void reader_information_input(void);									//读者信息输入
void reader_information_modification(void);								//读者信息修改
void reader_information_deletion(void);									//读者信息删除
void reader_information_inquiry(void);									//读者信息查询
void reader_information_display(void);									//读者信息显示

//图书管理员
void book_management(void);												//图书管理
void book_circulation_management(void);									//图书流通管理

//图书管理子系统	
void book_information_input(void);										//图书信息输入
void book_information_modification(void);								//图书信息修改
void book_information_inquiry(int);										//图书信息查询
void book_number_inquiry(void);											//按书号查询
void book_title_query(void);												//按书名查询
void author_query(void);													//按作者查询
void press_inquiry(void);													//按出版社查询
void summary_statistics(void);											//汇总统计

//图书流通管理子系统
void book_borrowing_processing(void);										//借书处理
void book_return(void);														//还书处理

//普通读者
void borrowing_query(void);												//借阅查询

//文件操作函数

//建立链表函数群
struct Key* temp_storage_key(const char* position);	//临时链表存储检索表数据
struct User* temp_storage_user(void);						//临时链表存储用户数据
struct Reader* temp_storage_reader(void);				//临时链表存储读者信息
struct Book* temp_storage_book(void);						//临时链表存储书籍信息
struct Brrecord* temp_storage_br(void);				//临时链表存储借还记录

//释放内存函数群
void free_list_key(struct Key* head);									//释放检索表链表内存					
void free_list_user(struct User* head);									//释放用户数据链表内存
void free_list_reader(struct Reader* head);								//释放读者数据链表内存
void free_list_book(struct Book* head);									//释放图书信息链表内存
void free_list_brrecord(struct Brrecord* head);							//释放借还记录链表内存

//文件写入函数群
int write_data_user(struct User* head, const char* position);			//写入用户数据
int write_data_reader(struct Reader* head, const char* position);		//写入读者数据
int write_data_book(struct Book* head, const char* position);			//写入图书数据
int write_data_br(struct Brrecord* head, const char* position);			//写入借还数据


int main()
{
	start_interface();
	return 0;
}

void start_interface(void)
{
	int flag;
	do
	{
		system("cls");
		printf("***图书管理系统***\n\n");
		printf("   1.登陆系统\n");
		printf("   2.账号注册\n");
		printf("   0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	display_main_menu(login_system());
			break;
		case 2: id_register();
			break;
		case 0: exit_program();
			break;
		default: flag = 1;
		}
		if (1 == flag)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag != 0);
}

void id_register(void)
{

	struct Reader irr;													//存储已输入读者信息
	struct User iru;													//存储已输入读者信息
	struct User temp;													//临时存储文件内容
	system("cls");
	printf("***账号注册***\n\n");
	printf("用户名: ");
	scanf("%s", iru.id);
	printf("密码: ");
	Encrypted_input_confirm(iru.password);
	printf("\n");
	printf("工作单位: ");
	scanf("%s", irr.company);
	printf("手机号: ");
	scanf("%s", irr.telephone);
	int flag;															//标记当前注册用户名是否被注册过
																		//已被注册标记为1，未被注册过标记为0
	do
	{
		flag = 0;														//初始化，假定当前用户名未被注册
		FILE* fp = fopen(file_user_data, "r");
		//用户文件内搜索当前注册的用户名
		while (fscanf(fp, "%s %s %s", temp.id, temp.password, temp.type) != EOF)
		{
			if (strcmp(iru.id, temp.id) == 0)
			{
				//用户文件发现当前用户名
				flag = 1;												//可判定当前用户名已被注册过并标记
				printf("此用户名已被申请， 请重新输入其他用户名\n");
				printf("用户名: ");
				scanf("%s", iru.id);									//提示用户重新输入用户名并自动覆盖原来的用户名数据
				break;
			}
		}
		fclose(fp);
	} while (flag != 0);												//标记为非零，循环一直执行判断当前输入的用户名是否可用
																		//标记为零代表用户文件中未找到当前用户名，当前用户名可用，退出循环
	FILE* fpr = fopen(file_reader_data, "a");							//文件中追加写入
	FILE* fpu = fopen(file_user_data, "a");
	if (NULL == fpr || NULL == fpu)										//文件打开失败系统给出提示并退出系统
	{
		printf("system error\nlogin has failed\n");
		exit_program();
	}
	else
	{
		fprintf(fpr, "%s %s %s %d %d\n", iru.id, irr.company, irr.telephone, loanable_number, borrowed_amount);
		fprintf(fpu, "%s %s %s\n", iru.id, iru.password, "reader");		//注册账号默认为读者
		fclose(fpr);
		fclose(fpu);
	}
	int flag_sel;														//标记操作指令是否非法
	do
	{
		system("cls");
		printf("注册成功\n\n");
		printf("1.返回登陆界面\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;														//操作指令
		flag_sel = 0;													//假定当前输入指令合法
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	start_interface();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;											//非法输入则标记	
		}
		if (1 == flag_sel)												//判断是否为非法输入
		{
			//非法输入给出提示并清空缓冲区
			printf("无效输入，请重新输入.\n\n");
			program_sleep();											//程序休眠
			clear_buffer();												//清空缓冲区
		}
	} while (flag_sel != 0);											//输入合法才可退出循环
}

int login_system(void)
{
	struct User lsu, flsu;												//存储键盘键入的数据与文件输入的数据
	int type_num = -1;													//用户类型标记
	system("cls");
	printf("***登陆系统***\n\n");
	printf("用户名:");
	scanf("%s", lsu.id);
	printf("密码:");
	Encrypted_input(lsu.password);
	int flag = -1;														//标记出错情况
	int kill_count = 0;													//统计密码错误次数
	FILE* fpu;
	do
	{
		fpu = fopen(file_user_data, "r");
		if (NULL == fpu)
		{
			printf("system error\n");
			exit_program();
		}
		else
		{
			while (fscanf(fpu, "%s %s %s", flsu.id, flsu.password, flsu.type) != EOF)
			{
				if (strcmp(lsu.id, flsu.id) == 0 && strcmp(lsu.password, flsu.password) != 0)
				{
					//用户名正确密码错误标记为1
					flag = 1;
					//密码错误次数加1
					kill_count++;
				}
				else if (strcmp(lsu.id, flsu.id) != 0 && strcmp(lsu.password, flsu.password) == 0)
				{
					//用户名错误密码正确标记为2
					flag = 2;
				}
				else if (strcmp(lsu.id, flsu.id) == 0 && strcmp(lsu.password, flsu.password) == 0)
				{
					//用户名密码都正确
					flag = 0;
					break;
				}
			}
			fclose(fpu);
			//密码错误输入次数少于3次则提示用户重新输入密码
			if (kill_count < 3)
			{ 
				//根据错误标记进行相应操作
				switch (flag)
				{
				case 1:
				{
					printf("\n密码错误\n");
					printf("当前可输入次数为：%d\n", 3 - kill_count);
					printf("请重新输入密码:");
					Encrypted_input(lsu.password);
					break;
				}
				case 2:
				case -1:
				{
					printf("\n未注册用户名\n");
					printf("请重新输入用户名与密码\n");
					printf("用户名:");
					scanf("%s", lsu.id);
					printf("密码:");
					Encrypted_input(lsu.password);
					break;
				}
				}
			}
			else
			{
				printf("\n输入错误次数过多，系统强制退出\n");
				exit(0);
			}

		}

	} while (flag != 0);
	//根据用户类型标记身份
	if (strcmp(flsu.type, "Administration") == 0)
		type_num = 1;
	else if (strcmp(flsu.type, "librarian") == 0)
		type_num = 2;
	else if (strcmp(flsu.type, "reader") == 0)
		type_num = 3;
	//返回用户类型标记
	return type_num;
}

void exit_program(void)
{
	printf("Exit the progrom\n Goodbay\n");
	exit(0);
}

void display_main_menu(int type)
{
	//根据所接收参数判断用户身份并显示相应菜单
	if (1 == type)
	{
		int flag;
		do
		{
			system("cls");
			printf("***系统管理员菜单***\n\n");
			printf("1.用户管理\n");
			printf("2.读者管理\n");
			printf("3.返回登陆界面\n");
			printf("0.退出系统\n");
			printf("请输入相关指令编号:");
			int sel;
			flag = 0;
			scanf("%d", &sel);
			switch (sel)
			{
			case 1:	user_management();
				break;
			case 2:	reader_management();
				break;
			case 3:	start_interface();
				break;
			case 0: exit_program();
				break;
			default: flag = 1;
			}
			if (1 == flag)
			{
				printf("无效输入，请重新输入.\n");
				program_sleep();
				clear_buffer();
			}
		} while (flag != 0);
	}
	else if (2 == type)
	{
		int flag;
		do
		{
			system("cls");
			printf("***图书管理员菜单***\n\n");
			printf("1.用户密码修改\n");
			printf("2.图书管理\n");
			printf("3.图书流通管理\n");
			printf("4.返回登陆界面\n");
			printf("0.退出系统\n");
			printf("请输入相关指令编号:");
			int sel;
			flag = 0;
			scanf("%d", &sel);
			switch (sel)
			{
			case 1:
			{
				user_password_modification();
				system("pause");
				int flag_sel;
				do
				{
					system("cls");
					printf("1.返回上一级\n");
					printf("0.退出系统\n\n");
					printf("请输入相关指令编号:");
					int sel;
					flag_sel = 0;
					scanf("%d", &sel);
					switch (sel)
					{
					case 1:	display_main_menu(2);
						break;
					case 0: exit_program();
						break;
					default: flag_sel = 1;
					}
					if (1 == flag_sel)
					{
						printf("无效输入，请重新输入.\n\n");
						program_sleep();
						clear_buffer();
					}
				} while (flag_sel != 0);
				break;
			}
			case 2: book_management();
				break;
			case 3: book_circulation_management();
				break;
			case 4:	start_interface();
				break;
			case 0: exit_program();
				break;
			default: flag = 1;
			}
			if (1 == flag)
			{
				printf("无效输入，请重新输入.\n");
				program_sleep();
				clear_buffer();
			}
		} while (flag != 0);
	}
	else if (3 == type)
	{
		int flag;
		do
		{
			system("cls");
			printf("***读者菜单***\n\n");
			printf("1.密码修改\n");
			printf("2.图书查询\n");
			printf("3.借阅查询\n");
			printf("4.汇总统计\n");
			printf("5.返回登陆界面\n");
			printf("0.退出系统\n");
			printf("请输入相关指令编号:");
			int sel;
			flag = 0;
			scanf("%d", &sel);
			switch (sel)
			{
			case 1:
			{
				user_password_modification();
				system("pause");
				int flag_sel;
				do
				{
					system("cls");
					printf("1.返回上一级\n");
					printf("0.退出系统\n\n");
					printf("请输入相关指令编号:");
					int sel;
					flag_sel = 0;
					scanf("%d", &sel);
					switch (sel)
					{
					case 1:	display_main_menu(3);
						break;
					case 0: exit_program();
						break;
					default: flag_sel = 1;
					}
					if (1 == flag_sel)
					{
						printf("无效输入，请重新输入.\n\n");
						program_sleep();
						clear_buffer();
					}
				} while (flag_sel != 0);
				break;
			}
			case 2: book_information_inquiry(1);
				break;
			case 3: borrowing_query();
				break;
			case 4:
			{
				summary_statistics();
				system("pause");
				int flag_sel;
				do
				{
					system("cls");
					printf("1.返回上一级\n");
					printf("0.退出系统\n\n");
					printf("请输入相关指令编号:");
					int sel;
					flag_sel = 0;
					scanf("%d", &sel);
					switch (sel)
					{
					case 1:	display_main_menu(3);
						break;
					case 0: exit_program();
						break;
					default: flag_sel = 1;
					}
					if (1 == flag_sel)
					{
						printf("无效输入，请重新输入.\n\n");
						program_sleep();
						clear_buffer();
					}
				} while (flag_sel != 0);
				break;
			}
			case 5:	start_interface();
				break;
			case 0: exit_program();
				break;
			default: flag = 1;
			}
			if (1 == flag)
			{
				printf("无效输入，请重新输入.\n");
				program_sleep();
				clear_buffer();
			}
		} while (flag != 0);
	}
}

void Encrypted_input(char* str)
{
	char temp_password[100];											//临时存入输入数据
	int i = 0;
	//_getch()函数不显示输入内容
	while ((temp_password[i] = _getch()) != '\r')
	{
		//输入位置打印*号实现加密效果
		printf("*");
		i++;
	}
	temp_password[i] = '\0';											//加入字符串终止符
	strcpy(str, temp_password);											//把加密输入内容拷贝给相应字符串
}

void Encrypted_input_confirm(char* str)
{
	int flag;															//标记两次输入内容是否相同
	char temp_password[100];
	char temp[100];
	do
	{
		flag = 0;														//假定两次输入内容相同
		Encrypted_input(temp_password);
		printf("\n再次输入密码: ");
		Encrypted_input(temp);
		if (strcmp(temp_password, temp) != 0)
		{
			//两次输入内容不不相同标记为1
			flag = 1;
			printf("\n两次输入密码并不相同\n");
			printf("请重新输入密码: ");
		}
	//两次输入不相同需要重新输入
	} while (flag);
	strcpy(str, temp_password);											//把加密内容拷贝给指定字符串
}

void dictionary_sort_show(int n)
{
	if (1 == n)															//用户文件内容
	{
		struct User* p, * p1, * p2, * x, * t;
		p = temp_storage_user();									//文件内容存入链表为排序做准备
		p1 = p->next;
		p->next = NULL;
		while (p1 != NULL)
		{
			x = p;
			p2 = p->next;
			while (p2 != NULL && strcmp(p2->id, p1->id) <= 0)
			{
				x = p2;
				p2 = p2->next;
			}
			t = p1->next;
			p1->next = p2;
			x->next = p1;
			p1 = t;
		}
		p1 = p;
		struct User* kill = p1;
		while (p1 != NULL)
		{
			printf("%s %s\n", p1->id, p1->type);
			p1 = p1->next;
		}
		free_list_user(kill);											//释放内存空间
	}
	if (2 == n)															//读者文件内容
	{
		struct Reader* p, * p1, * p2, * x, * t;
		p = temp_storage_reader();
		p1 = p->next;
		p->next = NULL;
		while (p1 != NULL)
		{
			x = p;
			p2 = p->next;
			while (p2 != NULL && strcmp(p2->id, p1->id) <= 0)
			{
				x = p2;
				p2 = p2->next;
			}
			t = p1->next;
			p1->next = p2;
			x->next = p1;
			p1 = t;
		}
		p1 = p;
		while (p1 != NULL)
		{
			printf("%s %s %s %d %d\n", p1->id, p1->company, p1->telephone, p1->can_borrow, p1->already_borrow);
			p1 = p1->next;
		}
		struct Reader* kill = p1;
		free_list_reader(kill);
	}
}

struct Data current_system_time(void)
{
	struct Data temp;
	struct tm* lt;
	time_t t;
	time(&t);											//获取Unix时间
	lt = localtime(&t);									//转为时间结构
	temp.year = lt->tm_year + 1900;
	temp.month = lt->tm_mon + 1;
	temp.day = lt->tm_mday;
	return temp;
}

void clear_buffer(void)
{
	rewind(stdin);														//更新清空缓冲区
}

void program_sleep(void)
{
	Sleep(500);															//系统休眠
}

void user_management(void)
{
	int flag;
	do
	{
		system("cls");
		printf("***用户管理子系统***\n\n");
		printf("1.用户信息输入\n");
		printf("2.用户信息修改\n");
		printf("3.用户信息删除\n");
		printf("4.用户信息显示\n");
		printf("5.用户密码修改\n");
		printf("6.返回上一级\n");
		printf("0.退出系统\n");
		printf("请输入相关指令编号:");
		int sel;
		flag = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	user_information_input();
			break;
		case 2: user_information_modification();
			break;
		case 3: user_information_deletion();
			break;
		case 4:	user_information_display();
			break;
		case 5:
		{
			user_password_modification();
			system("pause");
			int flag_sel;
			do
			{
				system("cls");
				printf("1.返回上一级\n");
				printf("0.退出系统\n\n");
				printf("请输入相关指令编号:");
				int sel;
				flag_sel = 0;
				scanf("%d", &sel);
				switch (sel)
				{
				case 1:	 user_management();
					break;
				case 0: exit_program();
					break;
				default: flag_sel = 1;
				}
				if (1 == flag_sel)
				{
					printf("无效输入，请重新输入.\n\n");
					program_sleep();
					clear_buffer();
				}
			} while (flag_sel != 0);
			break;
		}
		case 6: display_main_menu(1);
			break;
		case 0: exit_program();
			break;
		default: flag = 1;
		}
		if (1 == flag)
		{
			printf("无效输入，请重新输入.\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag != 0);

}

void reader_management(void)
{
	int flag;
	do
	{
		system("cls");
		printf("***读者管理子系统***\n\n");
		printf("1.读者信息输入\n");
		printf("2.读者信息修改\n");
		printf("3.读者信息删除\n");
		printf("4.读者信息查询\n");
		printf("5.读者信息显示\n");
		printf("6.返回上一级\n");
		printf("0.退出系统\n");
		printf("请输入相关指令编号:");
		int sel;
		flag = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	reader_information_input();
			break;
		case 2: reader_information_modification();
			break;
		case 3: reader_information_deletion();
			break;
		case 4: reader_information_inquiry();
			break;
		case 5: reader_information_display();
			break;
		case 6: display_main_menu(1);
			break;
		case 0: exit_program();
			break;
		default: flag = 1;
		}
		if (1 == flag)
		{
			printf("无效输入，请重新输入.\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag != 0);
}

void user_information_input(void)
{
	struct User* head = NULL;
	struct User temp_insert;
	FILE* fp = fopen(file_user_data, "r");
	if (NULL == fp)
	{
		printf("system error\n");
		printf("文件打开失败！检查文件目录是否正确。\n");
		system("pause");
		exit_program();
	}
	else
	{
		printf("请输入新用户用户名：");
		scanf("%s", temp_insert.id);
		printf("请输入新用户密码：");
		Encrypted_input(temp_insert.password);
		printf("\n请输入新用户类型：\n");
		int flag_choice;
		do
		{
			printf("\n1.Administration(系统管理员) \n");
			printf("2.librarian(图书管理员) \n\n");
			printf("请输入相关指令编号:");
			int choice;
			flag_choice = 0;
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:	strcpy(temp_insert.type, "Administration");
				break;
			case 2: strcpy(temp_insert.type, "librarian");
				break;
			default: flag_choice = 1;
			}
			if (1 == flag_choice)
			{
				printf("无效输入，请重新输入.\n\n");
				clear_buffer();
			}
		} while (flag_choice != 0);
		struct User temp;
		struct User* current = NULL, * prev = NULL;
		//文件内容全部写入链表
		while (fscanf(fp, "%s %s %s", temp.id, temp.password, temp.type) != EOF)
		{
			current = (struct User*)malloc(sizeof(struct User));
			strcpy(current->id, temp.id);
			strcpy(current->password, temp.password);
			strcpy(current->type, temp.type);
			current->next = NULL;
			if (NULL == head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
		//新键入的数据写入结构体并接入链表尾
		current = (struct User*)malloc(sizeof(struct User));
		strcpy(current->id, temp_insert.id);
		strcpy(current->password, temp_insert.password);
		strcpy(current->type, temp_insert.type);
		current->next = NULL;
		if (head == NULL)
			head = current;
		else
			prev->next = current;
	}
	//写入数据
	if (0 == write_data_user(head, file_user_data))
		printf("写入失败，检查写入文件目录是否正确。\n");
	else
		printf("写入成功\n");
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	user_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void user_information_modification(void)
{
	int flag;
	int flag_sel = 0;
	do
	{
		system("cls");
		printf("1.用户类型\n");
		printf("2.重置密码\n");
		printf("0.返回上一级\n");
		printf("请输入相关指令编号:");
		int sel;
		flag = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	flag_sel = 1;
			break;
		case 2: flag_sel = 2;;
			break;
		case 0: user_management();
			break;
		default: flag = 1;
		}
		if (1 == flag)
		{
			printf("无效输入，请重新输入.\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag != 0);
	if (1 == flag_sel)
	{
		char temp_id[50];
		struct User* p, * L;
		int is_no_find_flag = 1;										//标记是否找到指定用户
		L = p = temp_storage_user();
		printf("请输入需要修改信息的用户名\n");
		scanf("%s", temp_id);
		while (p)
		{
			//遍历链表寻找中指定用户
			if (strcmp(temp_id, p->id) == 0)
			{
				//找到指定用户标记找到
				is_no_find_flag = 0;
				printf("请输入新用户类型：\n");
				int flag_choice;
				do
				{
					printf("\n1.Administration(系统管理员) \n");
					printf("2.librarian(图书管理员) \n");
					printf("3.reader(读者)\n\n");
					printf("请输入相关指令编号:");
					int choice;
					flag_choice = 0;
					scanf("%d", &choice);
					switch (choice)
					{
					case 1:	strcpy(p->type, "Administration");
						break;
					case 2: strcpy(p->type, "librarian");
						break;
					case 3: strcpy(p->type, "reader");
						break;
					default: flag_choice = 1;
					}
					if (1 == flag_choice)
					{
						printf("无效输入，请重新输入.\n\n");
						clear_buffer();
					}
				} while (flag_choice != 0);
			}
			p = p->next;
		}
		if (is_no_find_flag)
			printf("未找到该用户\n");
		else
		{
			if (0 == write_data_user(L, file_user_data))
				printf("写入失败，检查写入文件目录是否正确。\n");
			else
				printf("写入成功\n");
		}
		system("pause");
		int flag_sel;
		do
		{
			system("cls");
			printf("1.返回上一级\n");
			printf("0.退出系统\n\n");
			printf("请输入相关指令编号:");
			int sel;
			flag_sel = 0;
			scanf("%d", &sel);
			switch (sel)
			{
			case 1:	user_information_modification();
				break;
			case 0: exit_program();
				break;
			default: flag_sel = 1;
			}
			if (1 == flag_sel)
			{
				printf("无效输入，请重新输入.\n\n");
				program_sleep();
				clear_buffer();
			}
		} while (flag_sel != 0);
	}
	else if (2 == flag_sel)
	{
		char temp_id[50];
		struct User* p, * L;
		int is_no_find_flag = 1;
		L = p = temp_storage_user();
		printf("请输入需要修改信息的用户名\n");
		scanf("%s", temp_id);
		while (p)
		{
			if (strcmp(temp_id, p->id) == 0)
			{
				is_no_find_flag = 0;
				strcpy(p->password, "123456");
			}
			p = p->next;
		}
		if (is_no_find_flag)
			printf("未找到该用户\n");
		else
		{
			if (0 == write_data_user(L, file_user_data))
				printf("重置失败，检查写入文件目录是否正确。\n");
			else
				printf("重置密码为：123456\n");
		}
		system("pause");
		int flag_sel;
		do
		{
			system("cls");
			printf("1.返回上一级\n");
			printf("0.退出系统\n\n");
			printf("请输入相关指令编号:");
			int sel;
			flag_sel = 0;
			scanf("%d", &sel);
			switch (sel)
			{
			case 1:	user_information_modification();
				break;
			case 0: exit_program();
				break;
			default: flag_sel = 1;
			}
			if (1 == flag_sel)
			{
				printf("无效输入，请重新输入.\n\n");
				program_sleep();
				clear_buffer();
			}
		} while (flag_sel != 0);
	}
}

void user_information_deletion(void)
{
	char temp_id[50];
	struct User* up, * ustorage_head, * utail, * ukill;
	int is_no_find_flag1 = 1;
	utail = ustorage_head = up = temp_storage_user();
	printf("请输入需要删除的用户名: ");
	scanf("%s", temp_id);
	while (up)
	{
		//遍历链表并删除指定节点
		if (strcmp(up->id, temp_id) == 0)
		{
			is_no_find_flag1 = 0;
			if (up == ustorage_head)
				ustorage_head = ustorage_head->next;
			else
				utail->next = up->next;
			ukill = up;
			up = up->next;
			free(ukill);
		}
		else
		{
			utail = up;
			up = up->next;
		}
	}

	struct Reader* rp, * rstorage_head, * rtail, * rkill;
	int is_no_find_flag2 = 1;
	rtail = rstorage_head = rp = temp_storage_reader();
	while (rp)
	{
		if (strcmp(rp->id, temp_id) == 0)
		{
			is_no_find_flag2 = 0;
			if (rp == rstorage_head)
				rstorage_head = rstorage_head->next;
			else
				rtail->next = rp->next;
			rkill = rp;
			rp = rp->next;
			free(rkill);
		}
		else
		{
			rtail = rp;
			rp = rp->next;
		}
	}
	if (is_no_find_flag1 && is_no_find_flag2)
		printf("未找到该用户\n");
	else
	{
		int success_flag1 = 1;
		int success_flag2 = 1;

		success_flag1 = write_data_user(ustorage_head, file_user_data);
		success_flag2 = write_data_reader(rstorage_head, file_reader_data);
		if (0 == success_flag1 && 0 == success_flag2)
			printf("删除失败，检查写入文件目录是否正确。\n");
		else
			printf("删除成功\n");
	}
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	user_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void user_information_display(void)
{
	dictionary_sort_show(1);											//排序并输出
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	user_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void user_password_modification(void)
{
	char temp_id[50];
	char temp_password[50];
	char old_password[50];
	struct User* p, * L;
	int is_no_find_flag = 1;
	L = p = temp_storage_user();									//文件内容写入链表
	printf("请输入需要修改密码的用户名: ");
	scanf("%s", temp_id);
	while (p)
	{
		//遍历链表寻找指定用户
		if (strcmp(temp_id, p->id) == 0)
		{
			is_no_find_flag = 0;
			int f = 1;
			do
			{
				//验证原密码
				printf("请输入原密码：");
				Encrypted_input(old_password);
				if (0 == strcmp(p->password, old_password))
				{
					f = 0;
					printf("\n请输入新密码：");
					Encrypted_input_confirm(temp_password);
					strcpy(p->password, temp_password);
				}
				else
				{
					printf("\n原密码不正确，修改失败\n");
					printf("请重新输入原密码\n");
					system("pause");
				}
			} while (f);
			break;
		}
		p = p->next;
	}
	if (is_no_find_flag)
		printf("未找到该用户\n");
	else
	{
		int success_flag1 = 1;

		success_flag1 = write_data_user(L, file_user_data);
		if (0 == success_flag1)
			printf("\n修改失败，检查写入文件目录是否正确。\n");
		else
			printf("\n修改成功\n");
	}
}

void reader_information_input(void)
{
	int f1 = 1, f2 = 1;
	struct User* head = NULL;
	struct User temp_insert;
	FILE* fp = fopen(file_user_data, "r");
	if (NULL == fp)
	{
		printf("system error\n");
		printf("文件打开失败！检查文件目录是否正确。\n");
		system("pause");
		exit_program();
	}
	else
	{
		printf("请输入新用户用户名：\n");
		scanf("%s", temp_insert.id);
		printf("请输入新用户密码：\n");
		Encrypted_input(temp_insert.password);
		strcpy(temp_insert.type, "reader");
		struct User temp;
		struct User* current = NULL, * prev = NULL;
		while (fscanf(fp, "%s %s %s", temp.id, temp.password, temp.type) != EOF)
		{
			current = (struct User*)malloc(sizeof(struct User));
			strcpy(current->id, temp.id);
			strcpy(current->password, temp.password);
			strcpy(current->type, temp.type);
			current->next = NULL;
			if (NULL == head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
		current = (struct User*)malloc(sizeof(struct User));
		strcpy(current->id, temp_insert.id);
		strcpy(current->password, temp_insert.password);
		strcpy(current->type, temp_insert.type);
		current->next = NULL;
		if (head == NULL)
			head = current;
		else
			prev->next = current;
	}
	struct Reader* rhead = NULL;
	struct Reader rtemp_insert;
	FILE* rfp = fopen(file_reader_data, "r");
	if (NULL == rfp)
	{
		printf("system error\n");
		printf("文件打开失败！检查文件目录是否正确。\n");
		system("pause");
		exit_program();
	}
	else
	{

		struct Reader* rcurrent = NULL, * rprev = NULL;
		while (fscanf(rfp, "%s %s %s %d %d", rtemp_insert.id, rtemp_insert.company, rtemp_insert.telephone, &rtemp_insert.can_borrow, &rtemp_insert.already_borrow) != EOF)
		{
			rcurrent = (struct Reader*)malloc(sizeof(struct Reader));
			strcpy(rcurrent->id, rtemp_insert.id);
			strcpy(rcurrent->company, rtemp_insert.company);
			strcpy(rcurrent->telephone, rtemp_insert.telephone);
			rcurrent->can_borrow = rtemp_insert.can_borrow;
			rcurrent->already_borrow = rtemp_insert.already_borrow;
			rcurrent->next = NULL;
			if (NULL == rhead)
				rhead = rcurrent;
			else
				rprev->next = rcurrent;
			rprev = rcurrent;
		}
		printf("\n输入读者工作单位：");
		scanf("%s", rtemp_insert.company);
		printf("输入读者联系方式：");
		scanf("%s", rtemp_insert.telephone);
		rtemp_insert.can_borrow = loanable_number;
		rtemp_insert.already_borrow = borrowed_amount;
		rcurrent = (struct Reader*)malloc(sizeof(struct Reader));
		strcpy(rcurrent->id, temp_insert.id);
		strcpy(rcurrent->company, rtemp_insert.company);
		strcpy(rcurrent->telephone, rtemp_insert.telephone);
		rcurrent->can_borrow = rtemp_insert.can_borrow;
		rcurrent->already_borrow = rtemp_insert.already_borrow;
		rcurrent->next = NULL;
		rprev->next = rcurrent;
	}
	f1 = write_data_user(head, file_user_data);
	f2 = write_data_reader(rhead, file_reader_data);

	if (f1 == 0 || f2 == 0)
		printf("写入失败，检查写入文件目录是否正确。\n");
	else
		printf("写入成功\n");
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	reader_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void reader_information_modification(void)
{
	struct Reader temp;
	char temp_id[50];
	struct Reader* p, * L;
	int is_no_find_flag = 1;
	L = p = temp_storage_reader();
	printf("请输入需要修改信息的用户名\n");
	scanf("%s", temp_id);
	while (p)
	{
		if (strcmp(temp_id, p->id) == 0)
		{
			is_no_find_flag = 0;
			printf("输入读者单位：");
			scanf("%s", temp.company);
			strcpy(p->company, temp.company);
			printf("输入读者电话号码：");
			scanf("%s", temp.telephone);
			strcpy(p->telephone, temp.telephone);
		}
		p = p->next;
	}
	if (is_no_find_flag)
		printf("未找到该用户\n");
	else
	{
		if (0 == write_data_reader(L, file_reader_data))
			printf("写入失败，检查写入文件目录是否正确。\n");
		else
			printf("写入成功\n");
	}
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	reader_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void reader_information_deletion(void)
{
	char temp_id[50];
	struct User* up, * ustorage_head, * utail, * ukill;
	int is_no_find_flag1 = 1;
	utail = ustorage_head = up = temp_storage_user();
	printf("请输入需要删除的用户名\n");
	scanf("%s", temp_id);
	while (up)
	{
		if (strcmp(up->id, temp_id) == 0)
		{
			is_no_find_flag1 = 0;
			if (up == ustorage_head)
				ustorage_head = ustorage_head->next;
			else
				utail->next = up->next;
			ukill = up;
			up = up->next;
			free(ukill);
		}
		else
		{
			utail = up;
			up = up->next;
		}
	}

	struct Reader* rp, * rstorage_head, * rtail, * rkill;
	int is_no_find_flag2 = 1;
	rtail = rstorage_head = rp = temp_storage_reader();
	while (rp)
	{
		if (strcmp(rp->id, temp_id) == 0)
		{
			is_no_find_flag2 = 0;
			if (rp == rstorage_head)
				rstorage_head = rstorage_head->next;
			else
				rtail->next = rp->next;
			rkill = rp;
			rp = rp->next;
			free(rkill);
		}
		else
		{
			rtail = rp;
			rp = rp->next;
		}
	}
	if (is_no_find_flag1 || is_no_find_flag2)
		printf("未找到该用户\n");
	else
	{
		int success_flag1 = 1;
		int success_flag2 = 1;

		success_flag1 = write_data_user(ustorage_head, file_user_data);
		success_flag2 = write_data_reader(rstorage_head, file_reader_data);
		if (0 == success_flag1)
			printf("删除失败，检查写入文件目录是否正确。\n");
		else
			printf("删除成功\n");
	}
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	reader_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void reader_information_inquiry(void)
{
	char temp_id[50];
	printf("请输入需要查询的用户名\n");
	scanf("%s", temp_id);
	struct Reader* rp, * rstorage_head, * rtail;
	int is_no_find_flag2 = 1;
	rtail = rstorage_head = rp = temp_storage_reader();
	while (rp)
	{
		if (strcmp(rp->id, temp_id) == 0)
		{
			is_no_find_flag2 = 0;
			printf("用户名 ：%s\n", rp->id);
			printf("工作单位：%s\n", rp->company);
			printf("联系方式：%s\n", rp->telephone);
			printf("可借书数：%d\n", rp->can_borrow);
			printf("已借书数：%d\n", rp->already_borrow);
			break;
		}
		else
		{
			rtail = rp;
			rp = rp->next;
		}
	}
	if (is_no_find_flag2)
		printf("未找到该用户\n");
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	reader_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void reader_information_display(void)
{
	dictionary_sort_show(2);
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	reader_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void book_management(void)
{
	int flag;
	do
	{
		system("cls");
		printf("1.图书信息输入\n");
		printf("2.图书信息修改\n");
		printf("3.图书信息查询\n");
		printf("4.汇总统计\n");
		printf("5.返回上一级\n");
		printf("0.退出系统\n");
		printf("请输入相关指令编号:");
		int sel;
		flag = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1: book_information_input();
			break;
		case 2: book_information_modification();
			break;
		case 3: book_information_inquiry(2);
			break;
		case 4:
		{
			summary_statistics();
			system("pause");
			int flag_sel;
			do
			{
				system("cls");
				printf("1.返回上一级\n");
				printf("0.退出系统\n\n");
				printf("请输入相关指令编号:");
				int sel;
				flag_sel = 0;
				scanf("%d", &sel);
				switch (sel)
				{
				case 1:	book_management();
					break;
				case 0: exit_program();
					break;
				default: flag_sel = 1;
				}
				if (1 == flag_sel)
				{
					printf("无效输入，请重新输入.\n\n");
					program_sleep();
					clear_buffer();
				}
			} while (flag_sel != 0);
			break;
		}
		case 5: display_main_menu(2);
			break;
		case 0: exit_program();
			break;
		default: flag = 1;
		}
		if (1 == flag)
		{
			printf("无效输入，请重新输入.\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag != 0);
}

void book_circulation_management(void)
{
	int flag;
	do
	{
		system("cls");
		printf("1.借书处理\n");
		printf("2.还书处理\n");
		printf("3.返回上一级\n");
		printf("0.退出系统\n");
		printf("请输入相关指令编号:");
		int sel;
		flag = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1: book_borrowing_processing();
			break;
		case 2: book_return();
			break;
		case 3: display_main_menu(2);
			break;
		case 0: exit_program();
			break;
		default: flag = 1;
		}
		if (1 == flag)
		{
			printf("无效输入，请重新输入.\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag != 0);
}

void book_information_input(void)
{
	struct Book temp_input;
	printf("请输入书本号：");
	scanf("%s", temp_input.id);
	printf("请输入书本名称：");
	scanf("%s", temp_input.type);
	printf("请输入书本作者：");
	scanf("%s", temp_input.author);
	printf("请输入书本出版社：");
	scanf("%s", temp_input.press);
	printf("请输入书本库存：");
	scanf("%d", &temp_input.stock);
	temp_input.borrowed = 0;
	printf("请输入相关检索信息：a, b, c");
	scanf("%d %d %d", &temp_input.p1, &temp_input.p2, &temp_input.p3);
	struct Book* head = NULL;
	FILE* fp = fopen(file_book_data, "r");
	if (NULL == fp)
	{
		printf("system error\n");
		exit_program();
	}
	else
	{
		struct Book temp;
		struct Book* current = NULL, * prev = NULL;
		int i = 1;
		while (fscanf(fp, "%d %s %s %s %s %d %d %d %d %d", &temp.num, temp.id, temp.type, temp.author, temp.press, &temp.stock, &temp.borrowed, &temp.p1, &temp.p2, &temp.p3) != EOF)
		{
			i++;
			current = (struct Book*)malloc(sizeof(struct Book));
			current->num = temp.num;
			strcpy(current->id, temp.id);
			strcpy(current->type, temp.type);
			strcpy(current->author, temp.author);
			strcpy(current->press, temp.press);
			current->stock = temp.stock;
			current->borrowed = temp.borrowed;
			current->p1 = temp.p1;
			current->p2 = temp.p2;
			current->p3 = temp.p3;
			current->next = NULL;
			if (NULL == head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
		current = (struct Book*)malloc(sizeof(struct Book));
		current->num = i;
		strcpy(current->id, temp_input.id);
		strcpy(current->type, temp_input.type);
		strcpy(current->author, temp_input.author);
		strcpy(current->press, temp_input.press);
		current->stock = temp_input.stock;
		current->borrowed = temp_input.borrowed;
		current->p1 = temp_input.p1;
		current->p2 = temp_input.p2;
		current->p3 = temp_input.p3;
		current->next = NULL;
		prev->next = current;
	}
	int f;
	f = write_data_book(head, file_book_data);
	if (f == 0)
		printf("写入失败\n");
	else
		printf("写入成功\n");
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	book_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void book_information_modification(void)
{
	struct Book* p, * L;
	struct Book temp;
	int is_no_find_flag = 1;
	L = p = temp_storage_book();
	printf("请输入书本id：");
	scanf("%s", temp.id);
	while (p)
	{
		if (strcmp(temp.id, p->id) == 0)
		{
			is_no_find_flag = 0;
			printf("请输入书本库存：");
			scanf("%d", &p->stock);
		}
		p = p->next;
	}
	if (is_no_find_flag)
		printf("未找到该书\n");
	else
	{
		if (0 == write_data_book(L, file_book_data))
			printf("写入失败，检查写入文件目录是否正确。\n");
		else
			printf("写入成功\n");
	}
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	book_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void book_information_inquiry(int n)
{
	int flag;
	do
	{
		system("cls");
		printf("1.按书号查询\n");
		printf("2.按书名查询\n");
		printf("3.按作者查询\n");
		printf("4.按出版社查询\n");
		printf("5.返回上一级\n");
		printf("0.退出系统\n");
		printf("请输入相关指令编号:");
		int sel;
		flag = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1: book_number_inquiry();
			break;
		case 2: book_title_query();
			break;
		case 3: author_query();
			break;
		case 4: press_inquiry();
			break;
		case 5:
		{
			if (n == 1)
				display_main_menu(3);
			else
				book_management();
			break;
		}
		case 0: exit_program();
			break;
		default: flag = 1;
		}
		if (1 == flag)
		{
			printf("无效输入，请重新输入.\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag != 0);
}

void book_number_inquiry(void)
{
	struct Book* p, * kill;
	char temp_id[50];
	int is_no_find_flag = 1;
	kill = p = temp_storage_book();
	printf("请输入书本id：");
	scanf("%s", temp_id);
	while (p)
	{
		if (strcmp(temp_id, p->id) == 0)
		{
			is_no_find_flag = 0;
			printf("书本名称：");
			printf("%s\n", p->type);
			printf("书本作者：");
			printf("%s\n", p->author);
			printf("书本出版社：");
			printf("%s\n", p->press);
			printf("书本库存：");
			printf("%d\n", p->stock);
			printf("已借出：");
			printf("%d\n", p->borrowed);
			printf("相关检索信息：a, b, c");
			printf("%d %d %d\n", p->p1, p->p2, p->p3);
		}
		p = p->next;
	}
	if (is_no_find_flag)
		printf("未找到该书\n");
	free_list_book(kill);
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	book_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void book_title_query()
{
	system("cls");
	char book_name[100];
	int head, lengh;
	int is_find;
	printf("请输入书名：");
	scanf("%s", book_name);
	struct Key* kp = NULL, * kkill;
	kkill = kp = temp_storage_key(file_name_data);
	is_find = 0;
	while (kp)
	{
		if (0 == strcmp(kp->keyword, book_name))
		{
			is_find = 1;
			head = kp->head;
			lengh = kp->lengh;
			break;
		}
		kp = kp->next;
	}
	free_list_key(kkill);
	if (0 == is_find)
		printf("未找到相关检索表信息，请检查检索表文件或书名\n");
	else
	{
		int count = 0;
		int find_book = 0;
		struct Book* bp = NULL, * bkill;
		bkill = bp = temp_storage_book();
		while (bp)
		{
			if (0 == strcmp(book_name, bp->type))
			{
				find_book = 1;
				count++;
				printf("\n\n");
				printf("书本名称：");
				printf("%s\n", bp->type);
				printf("书本作者：");
				printf("%s\n", bp->author);
				printf("书本出版社：");
				printf("%s\n", bp->press);
				printf("书本库存：");
				printf("%d\n", bp->stock);
				printf("已借出：");
				printf("%d\n", bp->borrowed);
				printf("相关检索信息：a, b, c ");
				printf("%d %d %d\n", bp->p1, bp->p2, bp->p3);
				printf("\n\n");
			}
			if (bp->num == head || count == lengh)
				break;
			bp = bp->next;
		}
		if (0 == find_book)
			printf("未找到此书\n");
		free_list_book(bkill);
	}
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	book_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void author_query()
{
	system("cls");
	char book_aut[100];
	int head, lengh;
	int is_find;
	printf("请输入作者名：");
	scanf("%s", book_aut);
	struct Key* kp = NULL, * kkill;
	kkill = kp = temp_storage_key(file_author_data);
	is_find = 0;
	while (kp)
	{
		if (0 == strcmp(kp->keyword, book_aut))
		{
			is_find = 1;
			head = kp->head;
			lengh = kp->lengh;
			break;
		}
		kp = kp->next;
	}
	free_list_key(kkill);
	if (0 == is_find)
		printf("未找到相关检索表信息，请检查检索表文件或作者名\n");
	else
	{
		int count = 0;
		int find_book = 0;;
		struct Book* bp = NULL, * bkill;
		bkill = bp = temp_storage_book();
		while (bp)
		{
			if (0 == strcmp(book_aut, bp->author))
			{
				find_book = 1;
				count++;
				printf("\n\n");
				printf("书本名称：");
				printf("%s\n", bp->type);
				printf("书本作者：");
				printf("%s\n", bp->author);
				printf("书本出版社：");
				printf("%s\n", bp->press);
				printf("书本库存：");
				printf("%d\n", bp->stock);
				printf("已借出：");
				printf("%d\n", bp->borrowed);
				printf("相关检索信息：a, b, c ");
				printf("%d %d %d\n", bp->p1, bp->p2, bp->p3);
				printf("\n\n");
			}
			if (bp->num == head || count == lengh)
				break;
			bp = bp->next;
		}
		if (0 == find_book)
			printf("未找到此书\n");
		free_list_book(bkill);
	}
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	book_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void press_inquiry()
{
	system("cls");
	char book_pub[100];
	int head, lengh;
	int is_find;
	printf("请输入出版社：");
	scanf("%s", book_pub);
	struct Key* kp = NULL, * kkill;
	kkill = kp = temp_storage_key(file_press_data);
	is_find = 0;
	while (kp)
	{
		if (0 == strcmp(kp->keyword, book_pub))
		{
			is_find = 1;
			head = kp->head;
			lengh = kp->lengh;
			break;
		}
		kp = kp->next;
	}
	free_list_key(kkill);
	if (0 == is_find)
		printf("未找到相关检索表信息，请检查检索表文件或作者名\n");
	else
	{
		int count = 0;
		int find_book = 0;;
		struct Book* bp = NULL, * bkill;
		bkill = bp = temp_storage_book();
		while (bp)
		{
			if (0 == strcmp(book_pub, bp->press))
			{
				find_book = 1;
				count++;
				printf("\n\n");
				printf("书本名称：");
				printf("%s\n", bp->type);
				printf("书本作者：");
				printf("%s\n", bp->author);
				printf("书本出版社：");
				printf("%s\n", bp->press);
				printf("书本库存：");
				printf("%d\n", bp->stock);
				printf("已借出：");
				printf("%d\n", bp->borrowed);
				printf("相关检索信息：a, b, c ");
				printf("%d %d %d\n", bp->p1, bp->p2, bp->p3);
				printf("\n\n");
			}
			if (bp->num == head || count == lengh)
				break;
			bp = bp->next;
		}
		if (0 == find_book)
			printf("未找到此书\n");
		free_list_book(bkill);

	}
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	book_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void summary_statistics(void)
{
	system("cls");
	struct Book* p, * kill;
	kill = p = temp_storage_book();
	printf("书号       书名       作者       出版社     剩余库存\n");
	while (p)
	{
		
		printf("%-10s %-10s %-10s %-10s %-10d\n", p->id, p->type, p->author, p->press, p->stock - p->borrowed);
		p = p->next;
	}
	free_list_book(kill);
}

void book_borrowing_processing(void)
{
	char reader_id[100];
	char book_id[100];
	printf("请输入用户名：");
	scanf("%s", reader_id);
	printf("请输入书号：");
	scanf("%s", book_id);
	struct Reader* p;
	int no_find_user = 1;
	p = temp_storage_reader();
	while (p)
	{
		if (strcmp(reader_id, p->id) == 0)
		{
			no_find_user = 0;
			if (p->can_borrow > p->already_borrow)
			{
				int borrowed_flag = 0;
				struct Brrecord* fp = NULL, * fL = NULL;
				fL = fp = temp_storage_br();

				while (fp)
				{
					if (strcmp(reader_id, fp->reader_id) == 0 && strcmp(book_id, fp->book_id) == 0 && fp->return_data.year == 0)
					{
						borrowed_flag = 1;
						break;
					}
					fp = fp->next;
				}
				if (borrowed_flag)
				{
					printf("此用户曾借此书但未归还，请先归还\n");
					printf("借书记录：未归还状态\n");
					printf("书号：%s\n", fp->book_id);
					printf("借书日期：%d-%d-%d\n", fp->borrow_data.year, fp->borrow_data.month, fp->borrow_data.day);
				}
				else
				{
					struct Book* p;
					p = temp_storage_book();
					int no_find_book = 1;
					while (p)
					{
						if (strcmp(book_id, p->id) == 0)
						{
							no_find_book = 0;
							if (p->stock > p->borrowed)
							{
								struct Brrecord* p = NULL, * L = NULL;
								L = p = temp_storage_br();

								if (p != NULL)
									while (p->next)
										p = p->next;
								struct Brrecord* current = NULL;
								struct Data nowtime = current_system_time();
								current = (struct Brrecord*)malloc(sizeof(struct Brrecord));
								strcpy(current->reader_id, reader_id);
								strcpy(current->book_id, book_id);
								current->borrow_data.year = nowtime.year;
								current->borrow_data.month = nowtime.month;
								current->borrow_data.day = nowtime.day;
								current->return_data.year = 0;
								current->return_data.month = 0;
								current->return_data.day = 0;
								current->next = NULL;
								if (L == NULL)
									L = current;
								else
									p->next = current;
								int f;
								f = write_data_br(L, file_brrecord_data);
								if (f == 0)
									printf("借还记录文件写入失败\n");
								else
									printf("借还记录写入成功\n");
								struct Book* bp, * bL;
								bL = bp = temp_storage_book();
								while (bp)
								{
									if (strcmp(book_id, bp->id) == 0)
										bp->borrowed++;
									bp = bp->next;
								}
								if (0 == write_data_book(bL, file_book_data))
									printf("写入失败，检查写入文件目录是否正确。\n");
								else
									printf("图书文件内容更新成功\n");

								struct Reader* rp, * rL;
								rL = rp = temp_storage_reader();
								while (rp)
								{
									if (strcmp(reader_id, rp->id) == 0)
										rp->already_borrow++;
									rp = rp->next;
								}
								if (0 == write_data_reader(rL, file_reader_data))
									printf("写入失败，检查写入文件目录是否正确。\n");
								else
									printf("读者信息更新成功\n");
							}
							else
								printf("此书已全部借出，暂无库存\n");
						}
						p = p->next;
					}
					if (no_find_book)
						printf("不存在此书\n");
				}
			}
			else
				printf("已达最大可借数，请归还已借书后再尝试借书\n");
		}
		p = p->next;
	}
	if (no_find_user)
		printf("不存在此用户\n");
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	 book_circulation_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void book_return()
{
	char reader_id[100];
	char book_id[100];
	printf("请输入用户名：");
	scanf("%s", reader_id);
	printf("请输入书号：");
	scanf("%s", book_id);
	struct Reader* p;
	int no_find_user = 1;
	p = temp_storage_reader();
	while (p)
	{
		if (strcmp(reader_id, p->id) == 0)
		{
			no_find_user = 0;
			int borrowed_flag = 1;
			struct Brrecord * fp = NULL, * fL = NULL;
			fL = fp = temp_storage_br();
			while (fp)
			{
				if (strcmp(reader_id, fp->reader_id) == 0 && strcmp(book_id, fp->book_id) == 0 && fp->return_data.year == 0)
				{
					borrowed_flag = 0;
					break;
				}
				fp = fp->next;
			}
			if (borrowed_flag)
				printf("未找到此用户的借阅未归还记录，请检查用户名是否正确，书本号是否正确\n");
			else
			{
				struct Book * p;
				p = temp_storage_book();
				int no_find_book = 1;
				while (p)
				{
					if (strcmp(book_id, p->id) == 0)
					{
						no_find_book = 0;
						struct Brrecord* p = NULL, * L = NULL;
						L = p = temp_storage_br();
						while (p)
						{
							if (strcmp(book_id, p->book_id) == 0 && p->return_data.year == 0)
							{
								struct Data nowtime = current_system_time();
								p->return_data.year = nowtime.year;
								p->return_data.month = nowtime.month;
								p->return_data.day = nowtime.day;
								break;
							}
							p = p->next;
						}
						int f;
						f = write_data_br(L, file_brrecord_data);
						if (f == 0)
							printf("借还记录文件写入失败\n");
						else
							printf("借还记录写入成功\n");
						struct Book * bp, * bL;
						bL = bp = temp_storage_book();
						while (bp)
						{
							if (strcmp(book_id, bp->id) == 0)
								bp->borrowed--;
							bp = bp->next;
						}
						if (0 == write_data_book(bL, file_book_data))
							printf("写入失败，检查写入文件目录是否正确。\n");
						else
							printf("图书文件内容更新成功\n");

						struct Reader* rp, * rL;
						rL = rp = temp_storage_reader();
						while (rp)
						{
							if (strcmp(reader_id, rp->id) == 0)
								rp->already_borrow--;
							rp = rp->next;
						}
						if (0 == write_data_reader(rL, file_reader_data))
							printf("写入失败，检查写入文件目录是否正确。\n");
						else
							printf("读者信息更新成功\n");
					}
					p = p->next;
				}
				if (no_find_book)
					printf("借书记录已找到，但图书文件不存在此书，引发错误，请联系图书管理员，更正\n");
			}
		}
		p = p->next;
	}
	if (no_find_user)
		printf("不存在此用户\n");
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	 book_circulation_management();
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

void borrowing_query(void)
{
	char temp_id[50];
	struct Reader* p, * L;
	int is_no_find_flag = 1;
	L = p = temp_storage_reader();
	printf("请输入您的用户名:");
	scanf("%s", temp_id);
	while (p)
	{
		if (strcmp(temp_id, p->id) == 0)
		{
			is_no_find_flag = 0;
			printf("可借数量为：");
			printf("%d\n", p->can_borrow);
			printf("已借数量为：");
			printf("%d\n", p->already_borrow);
		}
		p = p->next;
	}
	if (is_no_find_flag)
		printf("未找到该用户\n");
	system("pause");
	int flag_sel;
	do
	{
		system("cls");
		printf("1.返回上一级\n");
		printf("0.退出系统\n\n");
		printf("请输入相关指令编号:");
		int sel;
		flag_sel = 0;
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:	display_main_menu(3);
			break;
		case 0: exit_program();
			break;
		default: flag_sel = 1;
		}
		if (1 == flag_sel)
		{
			printf("无效输入，请重新输入.\n\n");
			program_sleep();
			clear_buffer();
		}
	} while (flag_sel != 0);
}

struct Key* temp_storage_key(const char* position)
{
	struct Key* head = NULL;
	FILE* fp = fopen(position, "r");
	if (NULL == fp)
	{
		printf("System error.File open failed\n");
		exit_program();
	}
	else
	{
		struct Key temp;
		struct Key* current = NULL, * prev = NULL;
		int i = 0;
		while (fscanf(fp, "%s %d %d", temp.keyword, &temp.head, &temp.lengh) != EOF)
		{
			current = (struct Key*)malloc(sizeof(struct Key));
			strcpy(current->keyword, temp.keyword);
			current->head = temp.head;
			current->lengh = temp.lengh;
			current->next = NULL;
			if (NULL == head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
	}
	return head;
}

struct User* temp_storage_user(void)
{
	struct User* head = NULL;
	FILE* fp = fopen(file_user_data, "r");
	if (NULL == fp)
	{
		printf("System error.File open failed\n");
		exit_program();
	}
	else
	{
		struct User temp;
		struct User* current = NULL, * prev = NULL;
		int i = 0;
		while (fscanf(fp, "%s %s %s", temp.id, temp.password, temp.type) != EOF)
		{
			current = (struct User*)malloc(sizeof(struct User));
			strcpy(current->id, temp.id);
			strcpy(current->password, temp.password);
			strcpy(current->type, temp.type);
			current->next = NULL;
			if (NULL == head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
	}
	return head;
}

struct Reader* temp_storage_reader(void)
{
	struct Reader* head = NULL;
	FILE* fp = fopen(file_reader_data, "r");
	if (NULL == fp)
	{
		printf("System error.File open failed\n");
		exit_program();
	}
	else
	{
		struct Reader temp;
		struct Reader* current = NULL, * prev = NULL;
		int i = 0;
		while (fscanf(fp, "%s %s %s %d %d", temp.id, temp.company, temp.telephone, &temp.can_borrow, &temp.already_borrow) != EOF)
		{
			current = (struct Reader*)malloc(sizeof(struct Reader));
			strcpy(current->id, temp.id);
			strcpy(current->company, temp.company);
			strcpy(current->telephone, temp.telephone);
			current->can_borrow = temp.can_borrow;
			current->already_borrow = temp.already_borrow;
			current->next = NULL;
			if (NULL == head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
	}
	return head;
}

struct Book* temp_storage_book(void)
{
	struct Book* head = NULL;
	FILE* fp = fopen(file_book_data, "r");
	if (NULL == fp)
	{
		printf("System error.File open failed\n");
		exit_program();
	}
	else
	{
		struct Book temp;
		struct Book* current = NULL, * prev = NULL;
		while (fscanf(fp, "%d %s %s %s %s %d %d %d %d %d", &temp.num, temp.id, temp.type, temp.author, temp.press, &temp.stock, &temp.borrowed, &temp.p1, &temp.p2, &temp.p3) != EOF)
		{
			current = (struct Book*)malloc(sizeof(struct Book));
			current->num = temp.num;
			strcpy(current->id, temp.id);
			strcpy(current->type, temp.type);
			strcpy(current->author, temp.author);
			strcpy(current->press, temp.press);
			current->stock = temp.stock;
			current->borrowed = temp.borrowed;
			current->p1 = temp.p1;
			current->p2 = temp.p2;
			current->p3 = temp.p3;
			current->next = NULL;
			if (NULL == head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
	}
	return head;
}

struct Brrecord* temp_storage_br(void)
{
	struct Brrecord* head = NULL;
	FILE* fp = fopen(file_brrecord_data, "r");
	if (NULL == fp)
	{
		printf("System error.File open failed\n");
		exit_program();
	}
	else
	{
		struct Brrecord temp;
		struct Brrecord* current = NULL, * prev = NULL;
		while (fscanf(fp, "%s %s %d-%d-%d %d-%d-%d", temp.reader_id, temp.book_id, &temp.borrow_data.year, &temp.borrow_data.month, &temp.borrow_data.day, &temp.return_data.year, &temp.return_data.month, &temp.return_data.day) != EOF)
		{
			current = (struct Brrecord*)malloc(sizeof(struct Brrecord));
			strcpy(current->reader_id, temp.reader_id);
			strcpy(current->book_id, temp.book_id);
			current->borrow_data.year = temp.borrow_data.year;
			current->borrow_data.month = temp.borrow_data.month;
			current->borrow_data.day = temp.borrow_data.day;
			current->return_data.year = temp.return_data.year;
			current->return_data.month = temp.return_data.month;
			current->return_data.day = temp.return_data.day;
			current->next = NULL;
			if (NULL == head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
	}
	return head;
}

void free_list_key(struct Key* head)
{
	struct Key* freeNode;

	while (NULL != head)
	{
		freeNode = head;
		head = head->next;
		free(freeNode);
	}
}

void free_list_user(struct User* head)
{
	struct User* freeNode;

	while (NULL != head)
	{
		freeNode = head;
		head = head->next;
		free(freeNode);
	}
}

void free_list_reader(struct Reader* head)
{
	struct Reader* freeNode;

	while (NULL != head)
	{
		freeNode = head;
		head = head->next;
		free(freeNode);
	}
}

void free_list_book(struct Book* head)
{
	struct Book* freeNode;

	while (NULL != head)
	{
		freeNode = head;
		head = head->next;
		free(freeNode);
	}
}

void free_list_brrecord(struct Brrecord* head)
{
	struct Brrecord* freeNode;

	while (NULL != head)
	{
		freeNode = head;
		head = head->next;
		free(freeNode);
	}
}

int write_data_user(struct User* head, const char* position)
{
	FILE* fp = fopen(position, "w");
	struct User* kill = head;
	if (NULL == fp)
		return 0;
	while (head)
	{
		fprintf(fp, "%s %s %s\n", head->id, head->password, head->type);
		head = head->next;
	}
	free_list_user(kill);
	fclose(fp);
	return 1;
}

int write_data_reader(struct Reader* head, const char* position)
{
	FILE* fp = fopen(position, "w");
	struct Reader* kill = head;
	if (NULL == fp)
		return 0;
	while (head)
	{
		fprintf(fp, "%s %s %s %d %d\n", head->id, head->company, head->telephone, head->can_borrow, head->already_borrow);
		head = head->next;
	}
	free_list_reader(kill);
	fclose(fp);
	return 1;
}

int write_data_book(struct Book* head, const char* position)
{
	FILE* fp = fopen(position, "w");
	struct Book* kill = head;
	if (NULL == fp)
		return 0;
	while (head)
	{
		fprintf(fp, "%d %s %s %s %s %d %d %d %d %d\n", head->num, head->id, head->type, head->author, head->press, head->stock, head->borrowed, head->p1, head->p2, head->p3);
		head = head->next;
	}
	free_list_book(kill);
	fclose(fp);
	return 1;
}

int write_data_br(struct Brrecord* head, const char* position)
{
	FILE* fp = fopen(position, "w");
	struct Brrecord* kill = head;
	if (NULL == fp)
		return 0;
	while (head)
	{
		fprintf(fp, "%s %s %d-%d-%d %d-%d-%d\n", head->reader_id, head->book_id, head->borrow_data.year, head->borrow_data.month, head->borrow_data.day, head->return_data.year, head->return_data.month, head->return_data.day);
		head = head->next;
	}
	free_list_brrecord(kill);
	fclose(fp);
	return 1;
}

