#include "C:\Users\admin\Documents\Proyecto\Cabeceras\cabeceras.h"
#include "C:\Users\admin\Documents\Proyecto\Cabeceras\gotoxy.h"
#include "C:\Users\admin\Documents\Proyecto\Cabeceras\frame.h"
#include "C:\Users\admin\Documents\Proyecto\Cabeceras\paint.h"

#define TAB 9
#define ENTER 13
#define ESC 27
#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80

#define GROUPS 0
#define STUDENTS 1

#define USER_REGISTRATION 0
#define USER_INQUIRIES 1
#define USER_CHANGES 2
#define USER_REMOVALS 3

#define DEFAULT_COLOR 15
#define DARK_BLUE 31
//#define DARK_GREEN_BLACK 32
#define RED 64
#define YELLOW 224
#define LIGHT_GRAY_BLACK 112
//#define LIGHT_GRAY_GREEN 112
//#define DARK_GRAY 128
#define GREEN_BLACK 160
#define LIGHT_GREEN 176
#define WHITE 240

#define LENGTH_MAX_NAME 40

typedef char StringM[20];
typedef char StringN[LENGTH_MAX_NAME + 1];

typedef struct 
{
	StringM strmsg;
	int pos_X;	
}TypeMenu;

typedef struct
{
	int cve;
	int level;
	StringN teacher;
}Group;

typedef struct
{
	int matricula;
	StringN name;
	double score;
}Student;

TypeMenu menu[3];
TypeMenu sub_menu[4];

int number_groups;
Group *group_list = NULL;
int *number_students_group = NULL;
Student **student_table = NULL;

int flag_menu = 0;
int flag_sub_menu = -1;
char input_key;
int index_order_student_list = -1;
void leaveSystem();
void endScreen();
void emptyArea();
	
void defMenu();
void paintMenu();

void defSubmenu();
void paintSubmenu();

/*
 * Operaciones con archivos.
 */
int loadGroups();
int loadStudents();
int saveGroups();
int saveStudents();
 
/*
 * Funciones Grupos.
 */
void groupRegistration();
void groupQueries();
void groupModify();
void groupsDelete();

int groupKeyExist(int clave);
int groupSearchOption(int *option);
void groupQueriesClave(int search_cve);
void groupQueriesName(const StringN search_name);
void groupQuerieslevel(int search_level);
void groupQueriesGroups();
void loadArray(Group *temp_groups, int *temp_cont, int opc, int *length,const StringN search_name, int search_level);
void printData(Group *temp_groups, int *temp_cont, int opc, int start, int max);
void printFila(Group *temp_groups, int *temp_cont, int opc, int pos, int index);
void optionstoOrder(Group *temp_groups, int *temp_cont, int opc, int opc_order, int length);
void changeGroupsOrder(Group *temp_groups, int *temp_cont, int j);
void controls(Group *temp_groups, int *temp_cont, int length, int opc, int x1, int x2, int *opc_x);
void printList(Student *list, int start, int index_group);
void printFila2(Student *list, int pos, int i);
void move1(Student *list, int length);
void orderStudents(Student *list, int length, int opc);
void changeStudentsOrder(Student *list, int j);

/*
 * Funciones Estudiantes.
 */
void studentRegistration();
void studentQueries();
int studentSearchOption(int *option);
void studentQueriesClave(int search_matricula, int dir[2]);
void printStudentList(Student *list_all, int *group, int start, int length);
void printFila3(Student list, int group, int pos);
void studentQueriesAll();
void studentModify();
void studentDelete();

int studentKeyExist(int matricula, int location[2]);
void moveItems(int dir[2]);
void moveListStudents(Student *temp_list_all, int *index_grupo, int length, int *opc_x);
void orderStudents2(Student *temp_list_all, int *index_grupo, int length, int opc_order);
/*
 * Operaciones con arreglos
 */
int addGroup();
//int addStudent();
int addStudent(int group, int matricula, double score, StringN name, int type);
/*
 * Validar e informar.
 */ 
int isNumber(char c);
void dialogBox(int type);
int inputScore(char* str, int limite) ;
int inputNAME(char *str, int limite);
int inputID(char *str, int limite);


int main()
{	
	defMenu();
	defSubmenu();
	assignColor(WHITE);
	
	paintHoriz(0, 79, 0, LIGHT_GRAY_BLACK);
	paintHoriz(0, 79, 2, LIGHT_GRAY_BLACK);
	paintArea(0, 1, 1, 24, LIGHT_GRAY_BLACK);
	emptyArea();
	paintArea(78, 1, 79, 24, LIGHT_GRAY_BLACK);
	paintHoriz(1, 78, 24, LIGHT_GRAY_BLACK);
	
	positionText(24, 0, " SISTEMA DE CONTROL DE GRUPOS ");
	paintHoriz(1, 78, 1, DARK_BLUE);
	paintMenu();
	
	assignColor(LIGHT_GREEN);
	positionText(menu[flag_menu].pos_X, 1, menu[flag_menu].strmsg);	
	
	loadGroups();///////Loading
	loadStudents();
	
	do
	{
		assignColor(LIGHT_GREEN);
		input_key = getch();
		
		switch(input_key)
		{
			case -32:
					input_key = getch();
					switch(input_key)
					{
						case UP_ARROW:
								if (flag_sub_menu > -1)
								{
									flag_sub_menu = -1;
									paintHoriz(5, 52, 2, LIGHT_GRAY_BLACK);
									gotoxy(menu[flag_menu].pos_X, 1);
								}								
								break;
								
						case LEFT_ARROW:
								
								if(flag_sub_menu == -1)
								{
									assignColor(DARK_BLUE);
									positionText(menu[flag_menu].pos_X, 1, menu[flag_menu].strmsg);	
									
									flag_menu = (flag_menu) ? 0 : 1 ;
									
									assignColor(LIGHT_GREEN);
									positionText(menu[flag_menu].pos_X, 1, menu[flag_menu].strmsg);	
								}else
								{
									assignColor(LIGHT_GREEN);
									positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);	
									
									flag_sub_menu = (flag_sub_menu) ? --flag_sub_menu : 3 ;									
									
									assignColor(YELLOW);
									positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);	
									
								}
								break;
								
						case RIGHT_ARROW:
								if(flag_sub_menu == -1)
								{
									assignColor(DARK_BLUE);
									positionText(menu[flag_menu].pos_X, 1, menu[flag_menu].strmsg);	
									
									flag_menu = (flag_menu) ? 0 : 1 ;
									
									assignColor(LIGHT_GREEN);
									positionText(menu[flag_menu].pos_X, 1, menu[flag_menu].strmsg);	
								}else
								{
									assignColor(LIGHT_GREEN);
									positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);
									
									flag_sub_menu = (flag_sub_menu == 3) ? 0 : ++flag_sub_menu;
									
									assignColor(YELLOW);
									positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);	
								}
								
								break;
													
						case DOWN_ARROW:
								if (flag_sub_menu == -1)
								{
									flag_sub_menu++;
									assignColor(LIGHT_GREEN);
									paintSubmenu();
									assignColor(YELLOW);
									positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);	
								}
								break;
								
					}
					break;
			
			case ENTER:
					if (flag_sub_menu == -1)
					{
						flag_sub_menu++;
						assignColor(LIGHT_GREEN);
						paintSubmenu();
						assignColor(YELLOW);
						positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);	
					}else
					{
						assignColor(WHITE);
						positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);
									
						switch(flag_menu)
						{
							case GROUPS:
									if(number_groups == 0 && flag_sub_menu > 0)
									{
										dialogBox(5); 
										break;
									}
									
									switch(flag_sub_menu)
									{
										case USER_REGISTRATION:
												groupRegistration();
												break;
												
										case USER_INQUIRIES:
												groupQueries();
												break;
												
										case USER_CHANGES: 
												groupModify();
												break;
												
										case USER_REMOVALS: 
												groupsDelete();
												break;
									}
									emptyArea();
									break;
									
							case STUDENTS:
									if(number_groups == 0)
									{
										dialogBox( (flag_sub_menu == 0) ? 9 : 5 );
										break;
									}
									
									switch(flag_sub_menu)
									{
										case USER_REGISTRATION:
												studentRegistration();
												break;
												
										case USER_INQUIRIES:
												studentQueries();
												break;
												
										case USER_CHANGES: 
												studentModify();
												break;
												
										case USER_REMOVALS: 
												studentDelete();
												break;
									}
									emptyArea();
									break;
						}						
						
						assignColor(YELLOW);
						positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);
					}
					break;
			
			case ESC:
					
					leaveSystem();				
					break;
		}		
	}while(1);//input_key != ESC);
}

/*
 * Inicializar el arreglo para el menu principal.
 */
void defMenu()
{
	strcpy(menu[0].strmsg, " GRUPOS ");
	menu[0].pos_X = 6;
	
	strcpy(menu[1].strmsg, " ALUMNOS ");
	menu[1].pos_X = 15;
	
	strcpy(menu[2].strmsg, " TERMINAR ");
	menu[2].pos_X = 65;
}

/*
 * Imprimir el menu principal.
 */
void paintMenu()
{
	int i;
	int separator[5] = {5, 14, 24, 64, 75};
	
	for(i = 0; i < 3; i++)
	{
		positionText(menu[i].pos_X, 1, menu[i].strmsg);	
	}
	
	for(i = 0; i < 5; i++)
	{
		positionText(separator[i], 1, "|");	
	}
}

/*
 * Inicializar el arreglo para los sub menus.
 */
void defSubmenu()
{
	strcpy(sub_menu[0].strmsg, " ALTAS ");
	sub_menu[0].pos_X = 6;
	
	strcpy(sub_menu[1].strmsg, " CONSULTAS ");
	sub_menu[1].pos_X = 14;
	
	strcpy(sub_menu[2].strmsg, " MODIFICACIONES ");
	sub_menu[2].pos_X = 26;
	
	strcpy(sub_menu[3].strmsg, " BAJAS ");
	sub_menu[3].pos_X = 43;
}

/*
 * Imprimir el submenu.
 */
void paintSubmenu()
{
	int i;
	int separator[5] = {5, 13, 25, 42, 50};
	
	for(i = 0; i < 4; i++)
	{
		positionText(sub_menu[i].pos_X, 2, sub_menu[i].strmsg);	
	}
	
	for(i = 0; i < 5; i++)
	{
		positionText(separator[i], 2, "|");	
	}
}

/*
 * Opcion para salir
 */
void leaveSystem()
{
	int leave_system = 0;
	
	if(flag_sub_menu > -1)
	{
		paintHoriz(5, 52, 2, LIGHT_GRAY_BLACK);
	}
				
	assignColor(DARK_BLUE);
	positionText(menu[flag_menu].pos_X, 1, menu[flag_menu].strmsg);	
					
	assignColor(RED);
	positionText(menu[2].pos_X, 1, menu[2].strmsg);	
	
	paintArea(24, 7, 54, 14, DARK_BLUE);
	windowFrame0(24, 7, 54, 14);
	gotoxy(33, 8); printf("%cDesea salir?", 168);
						
	windowFrame0(41, 10, 46, 12);
	positionText(42, 11, " Si ");
										
	windowFrame0(32, 10, 37, 12);
	assignColor(RED);
	positionText(33, 11, " No ");	
	
	do
	{
		input_key = getch();	
		switch(input_key)
		{
			case -32:
					input_key = getch();	
					switch(input_key)
					{
						case LEFT_ARROW:
						case RIGHT_ARROW:
								assignColor(DARK_BLUE);
								if(leave_system)
								{
									positionText(42, 11, " Si ");
								}else
								{
									positionText(33, 11, " No ");
								}
										
								leave_system = (leave_system) ? 0 : 1;
										
								assignColor(RED);
								if(leave_system)
								{
									positionText(42, 11, " Si ");
								}else
								{
									positionText(33, 11, " No ");
								}
								break;
					}
					break;
		}
	}while(input_key != ENTER);
	
	if(leave_system)
	{
		endScreen();
		getch();
		gotoxy(0, 21);
		exit(0);
	}
					
	paintArea(24, 7, 54, 14, WHITE);
	assignColor(DARK_BLUE);
	positionText(menu[2].pos_X, 1, menu[2].strmsg);
					
	assignColor(LIGHT_GREEN);
	positionText(menu[flag_menu].pos_X, 1, menu[flag_menu].strmsg);
					
	if( flag_sub_menu > -1)
	{
		paintSubmenu();
		assignColor(YELLOW);
		positionText(sub_menu[flag_sub_menu].pos_X, 2, sub_menu[flag_sub_menu].strmsg);
	}
}

/*
 * Screen termino.
 */
void endScreen()
{
	assignColor(DEFAULT_COLOR);
	system("cls");
	positionText(1, 0, "  _____ _____            _____ _____           _____    _____   ____  _____  ");
	positionText(1, 1, " / ____|  __ \\     /\\   / ____|_   _|   /\\    / ____|  |  __ \\ / __ \\|  __ \\ ");
	positionText(1, 2, "| |  __| |__) |   /  \\ | |      | |    /  \\  | (___    | |__) | |  | | |__) |");
	positionText(1, 3, "| | |_ |  _  /   / /\\ \\| |      | |   / /\\ \\  \\___ \\   |  ___/| |  | |  _  /");
	positionText(1, 4, "| |__| | | \\ \\  / ____ \\ |____ _| |_ / ____ \\ ____) |  | |    | |__| | | \\ \\");
	positionText(1, 5, " \\_____|_|  \\_\\/_/    \\_\\_____|_____/_/    \\_\\_____/   |_|     \\____/|_|  \\_\\ ");
	
	positionText(10, 8, " _____  _____   ____  ____          _____      ______ _ ");
	positionText(10, 9, "|  __ \\|  __ \\ / __ \\|  _ \\   /\\   |  __ \\    |  ____| |");
	positionText(10, 10, "| |__) | |__) | |  | | |_) | /  \\  | |__) |   | |__  | |");
	positionText(10, 11, "|  ___/|  _  /| |  | |  _ < / /\\ \\ |  _  /    |  __| | |");
	positionText(10, 12, "| |    | | \\ \\| |__| | |_) / ____ \\| | \\ \\    | |____| |____");
	positionText(10, 13, "|_|    |_|  \\_\\\\____/|____/_/    \\_\\_|  \\_\\   |______|______|");
	
	positionText(14, 16, "  _____ _____  _____ _______ ______ __  __");
	positionText(14, 17, " / ____|_   _|/ ____|__   __|  ____|  \\/  |   /\\");
	positionText(14, 18, "| (___   | | | (___    | |  | |__  | \\  / |  /  \\");
	positionText(14, 19, " \\___ \\  | |  \\___ \\   | |  |  __| | |\\/| | / /\\ \\");
	positionText(14, 20, " ____) |_| |_ ____) |  | |  | |____| |  | |/ ____ \\");
	positionText(14, 21, "|_____/|_____|_____/   |_|  |______|_|  |_/_/    \\_\\ ");
}

/*
 * Limpear area de trabajo.
 */
void emptyArea()
{
	paintArea(2, 3, 77, 23, WHITE);
	windowFrame1(2, 3, 77, 23);
}

/*
 * Cargar Grupos
 */
int loadGroups()
{
	FILE *file = fopen("src\\groups.dat", "rb");
	int i;
	
	number_groups = 0;
	
	if( file == NULL)
	{
		return 1; //No se ha podido acceder al archivo
	}
	
	fread(&number_groups, sizeof(int), 1, file);
	
	group_list = (Group *) malloc(sizeof(Group) * number_groups);
	
	for(i = 0; i < number_groups; i++)
	{
		fread(&group_list[i], sizeof(Group), 1, file);
	}
	
	fclose(file);
	
	return 0;
}

/*
 * Cargar Alumnos
 */
int loadStudents()
{
	FILE *file = fopen("src\\students.dat", "rb");
	int i, j;
	
	if( file == NULL)
	{
		return 1; //No se ha podido acceder al archivo
	}
	
	number_students_group = (int *) malloc(sizeof(int) * number_groups);
	student_table = (Student **) malloc(sizeof(Student *) * number_groups);	
	
	for(i = 0; i < number_groups; i++)
	{
		fread(&number_students_group[i], sizeof(int), 1, file);
		student_table[i] = (Student *) malloc(sizeof(Student) * number_students_group[i]);
	}
	
	for(i = 0; i < number_groups; i++)
	{
		for(j = 0; j < number_students_group[i]; j++)
		{
			fread(&student_table[i][j], sizeof(Student), 1, file);
		}
	}	
	
	fclose(file);
	
	return 0;
}

/*
 * Guardar Grupos
 */
int saveGroups()
{
	FILE *file = fopen("src\\groups.dat", "wb");
	int i;
	
	if( file == NULL)
	{
		dialogBox(4);
		return 1; //No se han guardado los cambios
	}
	
	fwrite(&number_groups, sizeof(int), 1, file);
	
	for(i = 0; i < number_groups; i++)
	{
		fwrite(&group_list[i], sizeof(Group), 1, file);
	}	
	
	fclose(file);
	
	return 0;
}

/*
 * Guardar Alumnos
 */
int saveStudents()
{
	FILE *file = fopen("src\\students.dat", "wb");
	int i, j;
	
	if( file == NULL)
	{
		dialogBox(4);
		return 1; //No se han guardado los cambios
	}
	
	for(i = 0; i < number_groups; i++)
	{
		fwrite(&number_students_group[i], sizeof(int), 1, file);		
	}
	
	for(i = 0; i < number_groups; i++)
	{
		for(j = 0; j < number_students_group[i]; j++)
		{
			fwrite(&student_table[i][j], sizeof(Student), 1, file);
		}
	}
	
	fclose(file);
	
	return 0;
}

int groupKeyExist(int clave)
{
	int i;
	for(i = 0; i < number_groups; i++)
	{
		if(group_list[i].cve == clave)
		{
			return i;
		}
	}
	return -1;
}

int studentKeyExist(int matricula, int location[2])
{
	int i, j;
	
	for(i = 0; i < number_groups; i++)
	{
		for(j = 0; j < number_students_group[i]; j++)
		{
			if(student_table[i][j].matricula == matricula)
			{
				location[0] = i;
				location[1] = j;
				return 1;
			}
		}
	}
	
	return 0;
}

/*
 * Agregar grupo.
 */
int addGroup()
{
	int i;
	
	i = groupKeyExist(-1);
	
	if( i > -1 )
	{
		number_students_group[i] = 0;
		return i;
	}
	
	number_groups++;
	
	Group *temp_group_list = (Group *) malloc(sizeof(Group) * number_groups);				
	int *temp_number_students_group = (int *) malloc(sizeof(int) * number_groups); 			
	Student **temp_student_table = (Student **) malloc(sizeof(Student *) * number_groups);
	
	for( i = 0; i < number_groups - 1 ; i++ )
	{
		temp_group_list[i] = group_list[i]; 
		temp_student_table[i] = student_table[i];
		temp_number_students_group[i] = number_students_group[i];
	}
	
	temp_number_students_group[i] = 0;
	
	group_list = temp_group_list;
	number_students_group = temp_number_students_group;
	student_table = temp_student_table;
	
	return i;
}

/*
 * Agregar grupo.
 */
int addStudent(int group, int matricula, double score, StringN name, int type)
{	
	int i;
	
	number_students_group[group]++;
	Student *list_group = (Student *) malloc(sizeof(Student) * number_students_group[group]);
			
	for( i = 0; i < number_students_group[group] - 1; i++)
	{
		list_group[i] = student_table[group][i]; 
	}	
	
	list_group[i].matricula = matricula;
	strcpy(list_group[i].name, name);
	list_group[i].score = score;
	
	student_table[group] = list_group;
	
	if( !saveGroups() && !saveStudents() )
	{
		dialogBox(type); //("Registro Exitoso!");
	}	
	return 0;
}

/*
 * Registrar nuevos grupos.
 */
void groupRegistration()
{
	char input_cve[10], input_level[2];
	StringN input_teacher;
	int index;	
	
	paintArea(15, 5, 64, 19, DARK_BLUE);
	windowFrame0(15, 5, 64, 19);
	positionText(27, 5, " INGRESA DATOS DEL GRUPO ");
	paintArea(65, 6, 66, 19, LIGHT_GRAY_BLACK);
	paintHoriz(17, 66, 20, LIGHT_GRAY_BLACK);
	
	do
	{
		paintArea(29, 7, 51, 14, DARK_BLUE);
		
		windowFrame0(25, 7, 35, 9);
		positionText(27, 7, " CLAVE ");
		windowFrame0(44, 7, 54, 9);
		positionText(46, 7, " NIVEL ");
		windowFrame0(19, 11, 60, 13);
		positionText(26, 11, " PROFESOR ");
		windowFrame0(33, 16, 45, 18);
		positionText(34, 17, " REGISTRAR ");
	
		paintHoriz(26, 34, 8, WHITE); 
		paintHoriz(45, 53, 8, WHITE); 
		paintHoriz(20, 59, 12, WHITE);
		
		gotoxy(26, 8);
		if(!inputID(input_cve, 9))
		{
			gotoxy(49, 8);
			if(!inputID(input_level, 1))
			{
				gotoxy(20, 12);
				if(inputNAME(input_teacher, LENGTH_MAX_NAME))
				{
					break;
				}
			}else
			{
				break;
			}
		}else
		{
			break;			
		}		
				
		assignColor(RED);
		positionText(34, 17, " REGISTRAR ");
		
		do
		{
			input_key = getch();
		}while(input_key != ENTER && input_key != ESC);		
		
		if(input_key == ESC)
		{
			break;
		}
		
		assignColor(DARK_BLUE);
		positionText(34, 17, " REGISTRAR ");
				
		if( atoi(input_cve) < 1 || atoi(input_level) < 1 )
		{
			dialogBox(3); //("Verifique sus datos y vuelva a intentar.");
			continue;
		}
		
		if(groupKeyExist(atoi(input_cve)) > -1)
		{
			dialogBox(2); //("Clave en uso")
			continue;
		}
		
		index = addGroup();
		
		group_list[index].cve = atoi(input_cve);
		group_list[index].level = atoi(input_level);
		strcpy(group_list[index].teacher, input_teacher);
		
		if( !saveGroups() && !saveStudents())
		{
			dialogBox(1);
		}		
	}while(1);
}


int groupSearchOption(int *option)
{
	TypeMenu opt_menu[4]; //pos_X == pos_Y
	int i;
	strcpy(opt_menu[0].strmsg, "  CLAVE   ");
	opt_menu[0].pos_X = 4;
	strcpy(opt_menu[1].strmsg, " PROFESOR ");
	opt_menu[1].pos_X = 5;
	strcpy(opt_menu[2].strmsg, "  NIVEL   ");
	opt_menu[2].pos_X = 6;
	strcpy(opt_menu[3].strmsg, "  GRUPOS  ");
	opt_menu[3].pos_X = 7;
	
	assignColor(YELLOW);
	for( i = 0; i < 4; i++ )
	{
		positionText(4, opt_menu[i].pos_X, "|          |");
		positionText(5, opt_menu[i].pos_X, opt_menu[i].strmsg);
	}
	
	assignColor(LIGHT_GREEN);
	positionText(5, opt_menu[*option].pos_X, opt_menu[*option].strmsg);
	
	do
	{
		input_key = getch();
		switch(input_key)
		{
			case -32:
					input_key = getch();
					switch(input_key)
					{
						case UP_ARROW:
								assignColor(YELLOW);
								positionText(5, opt_menu[*option].pos_X, opt_menu[*option].strmsg);
								
								*option = (*option) ? --*option : 3;
								
								assignColor(LIGHT_GREEN);
								positionText(5, opt_menu[*option].pos_X, opt_menu[*option].strmsg);
								break;
								
						case DOWN_ARROW:
								assignColor(YELLOW);
								positionText(5, opt_menu[*option].pos_X, opt_menu[*option].strmsg);
								
								*option = (*option == 3) ? 0 : ++*option;
								
								assignColor(LIGHT_GREEN);
								positionText(5, opt_menu[*option].pos_X, opt_menu[*option].strmsg);
								break;
					}
					break;
					
			case ENTER:
					return 0;
					
			case ESC:
					return 1;			
		}		
	}while(1);
}

/*
 * Consultas sobre grupos.
 */
void groupQueries()
{
	int option = 0;
	char search_cve[10], search_level[2];
	StringN search_name;
	drawHoriz(2, 77, 9, 205, 204, 185);
	do
	{
		if(groupSearchOption(&option))
		{
			break;
		}
		
		switch(option)
		{
			case 0:
					paintArea(20, 4, 30, 6, DARK_BLUE);
					windowFrame0(20, 4, 30, 6);
					positionText(22, 4, " CLAVE ");
					do
					{
						paintHoriz(21, 29, 5, WHITE);
						gotoxy(21, 5);
						if(!inputID(search_cve, 9))
						{
							groupQueriesClave( groupKeyExist( atoi(search_cve ) ) );
							input_key = 64;
						}
					}while(input_key !=ESC);
					break;
					
			case 1:
					paintArea(20, 4, 60, 6, DARK_BLUE);
					windowFrame0(20, 4, 61, 6);
					positionText(22, 4, " PROFESOR ");				
					do
					{
						paintHoriz(21, 60, 5, WHITE);
						gotoxy(21, 5);
						if(!inputNAME(search_name, 40))
						{
							groupQueriesName(search_name);
							input_key = 64;
						}
					}while(input_key !=ESC);
					break;
			
			case 2:
					paintArea(20, 4, 28, 6, DARK_BLUE);
					windowFrame0(20, 4, 28, 6);
					positionText(21, 4, " NIVEL ");
					do
					{
						paintHoriz(21, 27, 5, WHITE);
						gotoxy(24, 5);
						if(!inputID(search_level, 1))
						{
							groupQuerieslevel(atoi(search_level));
							input_key = 64;
						}
					}while(input_key !=ESC);
					break;
					
			case 3: 
					groupQueriesGroups();
					break;
		}
		
		paintArea(20, 4, 74, 8, WHITE);
	}while(1);
}

void groupQueriesGroups()
{
	Group temp_groups[number_groups];
	int temp_cont[number_groups];
	
	int length;
	int opc_x[4] = {21, 31, 42, 52};
	
	length = 0;
	
	loadArray(temp_groups, temp_cont, 3, &length, " ", -1);
	
	if(!length)
	{
		dialogBox(5);
		drawH(29, 51, 9, 205);
	}else
	{
		assignColor(WHITE);
		positionText(20, 8, "[ ]CLAVE  [ ]NOMBRE  [ ]NIVEL  [ ]No. ALUMNOS");
		
		paintArea(5, 10, 74, 22, DARK_BLUE);
		windowFrame0(5, 10, 74, 22);
		positionText(8, 11, "CLAVE");
		positionText(32, 11, "PROFESOR");
		positionText(60, 11, "NIVEL  ALUMNOS");
		drawHoriz(5, 74, 12, 196, 195, 180);
		drawVerti(15, 10, 12, 179, 194, 193);
		drawVerti(58, 10, 12, 179, 194, 193);
		drawVerti(66, 10, 12, 179, 194, 193);
		
		
		printData(temp_groups, temp_cont, 3, 0, length);
		
		paintHoriz(6, 73, 13, YELLOW);
		printFila(temp_groups, temp_cont, 3, 13, 0);
		
		controls(temp_groups, temp_cont, length, 3, 6, 73, opc_x);
	}
	paintArea(5, 10, 74, 22, WHITE);
}

void groupQueriesClave(int search_cve)
{
	Student *temp_group_students = NULL;
	int i;
	
	if( search_cve == -1)
	{
		dialogBox(6);
		drawH(29, 51, 9, 205);
	}else
	{
		if(number_students_group[search_cve])
		{
			temp_group_students = (Student *) malloc(sizeof(Student) * number_students_group[search_cve]);
			index_order_student_list = search_cve;
				
			for(i = 0; i < number_students_group[search_cve]; i++)
			{
				temp_group_students[i].matricula = student_table[search_cve][i].matricula;
				strcpy(temp_group_students[i].name, student_table[search_cve][i].name);
				temp_group_students[i].score = student_table[search_cve][i].score;
			}
			
			positionText(20, 8, "[ ]MATRICLUA  [ ]NOMBRE  [ ]CALIFICAION");
			
			paintArea(5, 10, 74, 22, DARK_BLUE);
			windowFrame0(5, 10, 74, 22);
			positionText(7, 11, "PROFESOR");
			positionText(64, 11, "NIVEL");
			positionText(6, 13, "MATRICLUA");
			positionText(35, 13, "ALUMNO");
			positionText(65, 13, "PUNTAJE");
			
			drawHoriz(5, 74, 12, 196, 195, 180);
			drawHoriz(5, 74, 14, 196, 195, 180);
			drawVerti(16, 10, 14, 179, 194, 193);
			drawVerti(62, 10, 14, 179, 194, 193);
			drawVerti(70, 10, 12, 179, 194, 193);
			printChar(16, 12, 197);
			printChar(62, 12, 197);
			
			positionText(18, 11, group_list[search_cve].teacher);
			gotoxy(72, 11); printf("%d",group_list[search_cve].level);
			gotoxy(57, 13); printf("1/%d",number_students_group[search_cve]);
			
			printList(temp_group_students, 0, number_students_group[search_cve]);
			
			paintHoriz(6, 73, 15, YELLOW);
			printFila2(temp_group_students, 15, 0);
			
			move1(temp_group_students, number_students_group[search_cve]);
		}else
		{
			dialogBox(5);
			drawH(29, 51, 9, 205);
		}	
	}
	
	paintArea(5, 10, 74, 22, WHITE);
	paintHoriz(20, 60, 8, WHITE);
	
	if(temp_group_students != NULL)
	{
		free(temp_group_students);
	}
}

void groupQueriesName(const StringN search_name)
{
	Group temp_groups[number_groups];
	int temp_cont[number_groups];
	
	int length;
	int opc_x[4] = {21, 0, 31, 41};
	
	length = 0;

	loadArray(temp_groups, temp_cont, 1, &length, search_name, -1);
	
	if(!length)
	{
		dialogBox(6);
		drawH(29, 51, 9, 205);
	}else
	{
		assignColor(WHITE);
		positionText(20, 8, "[ ]CLAVE  [ ]NIVEL  [ ]No. ALUMNOS");
		
		paintArea(23, 10, 53, 22, DARK_BLUE);
		windowFrame0(23, 10, 53, 22);
		drawHoriz(23, 53, 12, 196, 195, 180);
		drawVerti(35, 10, 12, 179, 194, 193);
		drawVerti(43, 10, 12, 179, 194, 193);
		positionText(27, 11, "CLAVE");
		positionText(37, 11, "NIVEL");
		positionText(45, 11, "ALUMNOS");
		
		printData(temp_groups, temp_cont, 1, 0, length);
		
		paintHoriz(24, 52, 13, YELLOW);
		printFila(temp_groups, temp_cont, 1, 13, 0);
		
		controls(temp_groups, temp_cont, length, 1, 24, 52, opc_x);
	}
	
	paintArea(5, 10, 74, 22, WHITE);
	paintHoriz(20, 60, 8, WHITE);
}

void groupQuerieslevel(int search_level)
{
	Group temp_groups[number_groups];
	int temp_cont[number_groups];
	
	int length;
	int opc_x[4] = {21, 31, 0, 42};
	
	length = 0;
	
	loadArray(temp_groups, temp_cont, 2, &length, " ", search_level);
	
	if(!length)
	{
		dialogBox(6);
		drawH(29, 51, 9, 205);
	}else
	{
		assignColor(WHITE);
		positionText(20, 8, "[ ]CLAVE  [ ]NOMBRE  [ ]No. ALUMNOS");
		paintArea(5, 10, 74, 22, DARK_BLUE);
		windowFrame0(5, 10, 74, 22);
		positionText(8, 11, "CLAVE");
		positionText(33, 11, "PROFESOR");
		positionText(62, 11, "NO. ALUMNOS");
		drawHoriz(5, 74, 12, 196, 195, 180);
		drawVerti(15, 10, 12, 179, 194, 193);
		drawVerti(60, 10, 12, 179, 194, 193);
		
		printData(temp_groups, temp_cont, 2, 0, length);
		paintHoriz(6, 73, 13, YELLOW);
		
		printFila(temp_groups, temp_cont, 2, 13, 0);
		controls(temp_groups, temp_cont, length, 2, 6, 73, opc_x);
	}
	
	paintArea(5, 10, 74, 22, WHITE);
	paintHoriz(20, 60, 8, WHITE);
}

void controls(Group *temp_groups, int *temp_cont, int length, int opc, int x1, int x2, int *opc_x)
{
	int index, screen_position, opc_ordenar;
		
	screen_position = 13;
	index = 0;
	opc_ordenar = 0;
	
	do
	{
		input_key = getch();
		switch(input_key)
		{
			case -32:
					input_key = getch();
					switch(input_key)
					{
						case UP_ARROW:
								if(screen_position == 13 && index > 0)
								{
									printData(temp_groups, temp_cont, opc, --index, length);
									paintHoriz(x1, x2, screen_position, YELLOW);
									printFila(temp_groups, temp_cont, opc, screen_position, index);
								}else
								{
									if(screen_position > 13)
									{
										paintHoriz(x1, x2, screen_position, DARK_BLUE);
										printFila(temp_groups, temp_cont, opc, screen_position, index);
										screen_position--;
										index--;
										paintHoriz(x1, x2, screen_position, YELLOW);
										printFila(temp_groups, temp_cont, opc, screen_position, index);
									}
								}
								break;
						
						case DOWN_ARROW:
								if(screen_position == 21 && index < length - 1)
								{
									printData(temp_groups, temp_cont, opc, ++index-8, length);
									paintHoriz(x1, x2, screen_position, YELLOW);
									printFila(temp_groups, temp_cont, opc, screen_position, index);
								}else
								{
									if(screen_position < 21 && index < length - 1)
									{
										paintHoriz(x1, x2, screen_position, DARK_BLUE);
										printFila(temp_groups, temp_cont, opc, screen_position, index);
										screen_position++;
										index++;
										paintHoriz(x1, x2, screen_position, YELLOW);
										printFila(temp_groups, temp_cont, opc, screen_position, index);
									}
								}
								break;
						
						case LEFT_ARROW:
								assignColor(WHITE);
								printChar(opc_x[opc_ordenar], 8, 32);
								assignColor(GREEN_BLACK);
								
								if(opc == 1)
								{
									opc_ordenar = (opc_ordenar == 2) ? 0 : (opc_ordenar == 0) ? 3 : 2;	
								}else
								{
									if(opc == 2)
									{
										opc_ordenar = (opc_ordenar == 3) ? 1 : (opc_ordenar == 0) ? 3 : 0;
									}else
									{
										if(opc == 3)
										{
											opc_ordenar =  (opc_ordenar) ? --opc_ordenar : 3;
										}	
									}	
								}
									
								printChar(opc_x[opc_ordenar], 8, 32);
								screen_position = 13;
								index = 0;
								optionstoOrder(temp_groups, temp_cont, opc, opc_ordenar, length);											
								break;
								
						case RIGHT_ARROW:
								assignColor(WHITE);
								printChar(opc_x[opc_ordenar], 8, 32);
								assignColor(GREEN_BLACK);
								
								if(opc == 1)
								{
									opc_ordenar = (opc_ordenar == 0) ? 2 : (opc_ordenar == 3) ? 0 : 3;	
								}else
								{
									if(opc == 2)
									{
										opc_ordenar = (opc_ordenar == 1) ? 3 : (opc_ordenar == 3) ? 0 : 1;
									}else
									{
										if(opc == 3)
										{
											opc_ordenar = (opc_ordenar == 3) ? 0 : ++opc_ordenar;
										}	
									}	
								}	
								
								printChar(opc_x[opc_ordenar], 8, 32);
								screen_position = 13;
								index = 0;
								optionstoOrder(temp_groups, temp_cont, opc, opc_ordenar, length);
								break;		
					}
					break;
		}
	}while(input_key != ESC);
}

void printList(Student *list, int start, int index_group)
{
	int i, pos = 15;
	paintArea(6, 15, 73, 21, DARK_BLUE);

	for(i = start; i < (start + 7) && i < index_group; i++ , pos++)
	{
		printFila2(list, pos, i);		
	}
}

void printFila2(Student *list, int pos, int i)
{
	gotoxy(6, pos); printf("%9d", list[i].matricula);
	positionText(18, pos, list[i].name);
	gotoxy(67, pos); printf("%.1f", list[i].score);
}

void printFila(Group *temp_groups, int *temp_cont, int opc, int pos, int index)
{
	switch(opc)
	{
		case 1:
				gotoxy(25, pos); printf("%9d", temp_groups[index].cve);
				gotoxy(39, pos); printf("%d", temp_groups[index].level);
				gotoxy(48, pos); printf("%d", temp_cont[index]);
				break;
		
		case 2:
				gotoxy(6, pos); printf("%9d", temp_groups[index].cve);
				positionText(17, pos, temp_groups[index].teacher);
				gotoxy(66, pos); printf("%d", temp_cont[index]);
				break;
				
		case 3:
				gotoxy(6, pos); printf("%9d", temp_groups[index].cve);
				positionText(17, pos, temp_groups[index].teacher);
				gotoxy(62, pos); printf("%d", temp_groups[index].level);
				gotoxy(70, pos); printf("%d", temp_cont[index]);	
				break;
	}
	
}

void printData(Group *temp_groups, int *temp_cont, int opc, int start, int max)
{
	int i, pos = 13;
	switch(opc)
	{
		case 1:
				paintArea(24, 13, 52, 21, DARK_BLUE);
				break;
		case 2:		
		case 3:
				paintArea(6, 13, 73, 21, DARK_BLUE);
				break;
	}
	
	for(i = start; i < (start + 9) && i < max; i++ , pos++)
	{
		printFila(temp_groups, temp_cont, opc, pos, i);		
	}
}

void loadArray(Group *temp_groups, int *temp_cont, int opc, int *length, const StringN search_name, int search_level)
{
	int i, j = 0;
	for(i = 0; i < number_groups; i++)
	{
		if(group_list[i].cve == -1)
		{
			continue;
		}
		
		switch(opc)
		{
			case 1:
					if(strcmp(group_list[i].teacher, search_name)==0)
					{
						temp_groups[j].cve = group_list[i].cve;
						temp_groups[j].level = group_list[i].level;
						strcpy(temp_groups[j].teacher, group_list[i].teacher);
						temp_cont[j] = number_students_group[i];
						j++;
						++*length;	
					}
					break;
					
			case 2:
					if(group_list[i].level == search_level)
					{
						temp_groups[j].cve = group_list[i].cve;
						temp_groups[j].level = group_list[i].level;
						strcpy(temp_groups[j].teacher, group_list[i].teacher);
						temp_cont[j] = number_students_group[i];
						j++;
						++*length;	
					}
					break;
					
			case 3:
					temp_groups[j].cve = group_list[i].cve;
					temp_groups[j].level = group_list[i].level;
					strcpy(temp_groups[j].teacher, group_list[i].teacher);
					temp_cont[j] = number_students_group[i];
					j++;
					++*length;
					break;
		}
	}	
}

void changeGroupsOrder(Group *temp_groups, int *temp_cont, int j)
{
	Group change_data;
	int change_number;
	
	change_data.cve = temp_groups[j].cve;
	change_data.level = temp_groups[j].level;
	strcpy(change_data.teacher, temp_groups[j].teacher);
	change_number = temp_cont[j];
	
  	temp_groups[j].cve = temp_groups[j + 1].cve;
  	temp_groups[j].level = temp_groups[j + 1].level;
  	strcpy(temp_groups[j].teacher, temp_groups[j + 1].teacher);
  	temp_cont[j] = temp_cont[j + 1];
  	
  	temp_groups[j + 1].cve = change_data.cve;
  	temp_groups[j + 1].level = change_data.level;
  	strcpy(temp_groups[j + 1].teacher, change_data.teacher);
  	temp_cont[j +1] = change_number;
}

void changeStudentsOrder(Student *list, int j)
{
	Student change_data;
	int change_number;
	
	change_data.matricula = list[j].matricula;
	change_data.score = list[j].score;
	strcpy(change_data.name, list[j].name);
	
  	list[j].matricula = list[j + 1].matricula;
  	list[j].score = list[j + 1].score;
  	strcpy(list[j].name, list[j + 1].name);
  	
  	list[j + 1].matricula = change_data.matricula;
  	list[j + 1].score = change_data.score;
  	strcpy(list[j + 1].name, change_data.name);
}

void optionstoOrder(Group *temp_groups, int *temp_cont, int opc, int opc_order, int length)
{
	int i, j;
	
	for (i = 0; i < length; i++)
	{
    	for (j = 0; j < length - 1; j++) 
		{      	
	      	switch(opc_order)
			{
				case 0:
				    	if (temp_groups[j].cve > temp_groups[j + 1].cve) 
					  	{
				        	changeGroupsOrder(temp_groups, temp_cont, j);
				      	}
						break;
						
				case 1:
				    	if (strcmp(temp_groups[j].teacher, temp_groups[j + 1].teacher) > 0 ) 
					  	{
				        	changeGroupsOrder(temp_groups, temp_cont, j);
				      	}
						break;
						
				case 2:
				    	if (temp_groups[j].level > temp_groups[j + 1].level) 
					  	{
				        	changeGroupsOrder(temp_groups, temp_cont, j);
				      	}
						break;
						
				case 3:
				    	if (temp_cont[j] < temp_cont[j + 1]) 
					  	{
				        	changeGroupsOrder(temp_groups, temp_cont, j);
				 		}
						break;
			}	      	
    	}
  	}
  	
  	switch(opc)
  	{
  		case 1:
  				printData(temp_groups, temp_cont, opc, 0, length);
				paintHoriz(24, 52, 13, YELLOW);
				printFila(temp_groups, temp_cont, opc, 13, 0);
		  		break;
		case 2:
		case 3:
				printData(temp_groups, temp_cont, opc, 0, length);
				paintHoriz(6, 73, 13, YELLOW);
				printFila(temp_groups, temp_cont, opc, 13, 0);
				break;
	}
}

void move1(Student *list, int length)
{
	int index, screen_position, opc_ordenar;
	int opc_x[3] = {21, 35, 46};	
	screen_position = 15;
	index = 0;
	opc_ordenar = 0;
	
	do
	{
		input_key = getch();
		switch(input_key)
		{
			case -32:
					input_key = getch();
					switch(input_key)
					{
						case UP_ARROW:
								if(screen_position == 15 && index > 0)
								{
									printList(list, --index, length);
									gotoxy(56, 13); printf("%2d",index + 1);									
									paintHoriz(6, 73, screen_position, YELLOW);
									printFila2(list, screen_position, index);
								}else
								{
									if(screen_position > 15)
									{
										paintHoriz(6, 73, screen_position, DARK_BLUE);
										printFila2(list, screen_position, index);
										gotoxy(56, 13); printf("%2d",index--);
										paintHoriz(6, 73, --screen_position, YELLOW);										
										printFila2(list, screen_position, index);
									}
								}
								break;
						
						case DOWN_ARROW:
								if(screen_position == 21 && index < length - 1)
								{
									printList(list, ++index-6, length);
									gotoxy(56, 13); printf("%2d", index + 1);
									paintHoriz(6, 73, screen_position, YELLOW);
									printFila2(list, screen_position, index);
								}else
								{
									if(screen_position < 21 && index < length - 1)
									{
										paintHoriz(6, 73, screen_position, DARK_BLUE);
										printFila2(list, screen_position, index);
										gotoxy(56, 13); printf("%2d", ++index + 1);
										paintHoriz(6, 73, ++screen_position, YELLOW);										
										printFila2(list, screen_position, index);
									}
								}
								break;
						
						case LEFT_ARROW:
								assignColor(WHITE);
								printChar(opc_x[opc_ordenar], 8, 32);
								assignColor(GREEN_BLACK);
								
								opc_ordenar = (opc_ordenar) ? --opc_ordenar : 2;
									
								printChar(opc_x[opc_ordenar], 8, 32);
								screen_position = 15;
								index = 0;											
								orderStudents(list, length, opc_ordenar);
								break;
								
						case RIGHT_ARROW:
								assignColor(WHITE);
								printChar(opc_x[opc_ordenar], 8, 32);
								assignColor(GREEN_BLACK);
								
								opc_ordenar = (opc_ordenar == 2) ? 0 : ++opc_ordenar;	
								
								printChar(opc_x[opc_ordenar], 8, 32);
								screen_position = 15;
								index = 0;
								orderStudents(list, length, opc_ordenar);
								break;	
					}
					break;
		}
	}while(input_key != ESC);
}

void orderStudents(Student *list, int length, int opc_order)
{
	int i, j;
	
	for (i = 0; i < length; i++)
	{
    	for (j = 0; j < length - 1; j++) 
		{      	
	      	switch(opc_order)
			{
				case 0:
				    	if (list[j].matricula > list[j + 1].matricula) 
					  	{
				        	changeStudentsOrder(list, j);
				      	}
						break;
						
				case 1:
				    	if (strcmp(list[j].name, list[j + 1].name) > 0 ) 
					  	{
				        	changeStudentsOrder(list, j);				        	
				      	}
						break;
						
				case 2:
				    	if (list[j].score < list[j + 1].score) 
					  	{
				        	changeStudentsOrder(list, j);
				      	}
						break;
			}	      	
    	}
	}
		
			
	student_table[index_order_student_list] = list;
	
	saveGroups();
	saveStudents();
	
	printList(list, 0, length);	
	gotoxy(56, 13); printf(" 1");		
	paintHoriz(6, 73, 15, YELLOW);
	printFila2(list, 15, 0);
	
	index_order_student_list = -1;
}

/*
 * Modificacion de grupos.
 */
void groupModify()
{
	char input_cve[10], input_level[2];
	StringN input_name;
	int opt_update, stay, found = -1;
	int opt[3][2] = {{24, 10}, {21, 14}, {34, 18}};
	
	do
	{
		assignColor(DARK_BLUE);
		windowFrame0(34, 6, 44, 8);
		positionText(36, 6, " CLAVE ");
		paintHoriz(35, 43, 7, WHITE);
		
		gotoxy(35, 7);
		if(!inputID(input_cve, 9))
		{
			found = groupKeyExist(atoi(input_cve));
		}else
		{
			break;
		} 
		
		if(found < 0)
		{
			dialogBox(6);
		}else
		{
			opt_update = 0;
			strcpy(input_name, group_list[found].teacher);
			itoa(group_list[found].level, input_level, 10);
			
			paintArea(15, 5, 64, 20, DARK_BLUE);
			windowFrame0(15, 5, 64, 20);
			positionText(31, 5, " DATOS DEL GRUPO ");
			paintArea(65, 6, 66, 20, LIGHT_GRAY_BLACK);
			paintHoriz(17, 66, 21, LIGHT_GRAY_BLACK);
			
			while(input_key != ESC)
			{	
				stay = 1;			
				paintArea(29, 7, 51, 14, DARK_BLUE);
				
				windowFrame0(34, 6, 44, 8);
				positionText(36, 6, " CLAVE ");
				
				windowFrame0(19, 9, 29, 11);
				positionText(21, 9, " *NIVEL ");
				
				windowFrame0(19, 13, 60, 15);
				positionText(21, 13, " *PROFESOR ");
				
				windowFrame0(33, 17, 46, 19);
				positionText(34, 18, " ACTUALIZAR ");
				
				paintHoriz(35, 43, 7, WHITE);  
				paintHoriz(20, 28, 10, WHITE); 
				paintHoriz(20, 59, 14, WHITE);			
				
				positionText(16, 22, "*ENTER PARA EDITAR");
				positionText(38, 22, "*ESC PARA CANCELAR EDICION");
				
				gotoxy(35, 7); printf("%d", group_list[found].cve);
				gotoxy(24, 10); printf("%d", group_list[found].level);
				positionText(21, 14, group_list[found].teacher);
				gotoxy(opt[opt_update][0], opt[opt_update][1]);
				
				do
				{
					input_key = getch();
					switch(input_key)
					{
						case -32:
								input_key = getch();
								switch(input_key)
								{
											
									case UP_ARROW:
											if(opt_update > 0)
											{
												if(opt_update == 2)
												{
													assignColor(DARK_BLUE);
													positionText(34, 18, " ACTUALIZAR ");
												}
												opt_update--;
												gotoxy(opt[opt_update][0], opt[opt_update][1]);	
											}	
											break;
											
									case DOWN_ARROW:
											if(opt_update < 2)
											{
												opt_update++;
												if(opt_update == 2)
												{
													assignColor(RED);
													positionText(34, 18, " ACTUALIZAR ");
												}
												gotoxy(opt[opt_update][0], opt[opt_update][1]);	
											}
											break;
								}
								break;
								
						case ENTER:
								switch(opt_update)
								{
									case 0:
											paintHoriz(24, 24, 10, WHITE);
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											if(inputID(input_level, 1))
											{
												input_key = 64;
												itoa(group_list[found].level, input_level, 10);
												positionText(24, 10, input_level);
											}
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											break;
											
									case 1:
											paintHoriz(20, 59, 14, WHITE);
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											if(inputNAME(input_name, LENGTH_MAX_NAME))
											{
												paintHoriz(20, 59, 14, WHITE);
												input_key = 64;
												strcpy(input_name, group_list[found].teacher);
												positionText(21, 14, input_name);
											}
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											break;
											
									case 2:
											assignColor(DARK_BLUE);
											positionText(34, 18, " ACTUALIZAR ");
											
											if(atoi(input_level) == group_list[found].level && !strcmp(input_name, group_list[found].teacher))
											{
												dialogBox(7); //("Sin cambios");
											}else
											{
												if(atoi(input_level) > 0)
												{
													group_list[found].level = atoi(input_level);
													strcpy(group_list[found].teacher, input_name);
													if(saveGroups())
													{
														dialogBox(4); //("No se guardaron los cambios");
													}else
													{
														dialogBox(8); //("Se guardaron los cambios");
													}
												}else
												{
													itoa(group_list[found].level, input_level, 10);
													dialogBox(3); //("Verifique sus datos");
												}
											}
											stay = 0;
											gotoxy(24, 10); printf("%d", group_list[found].level);
											positionText(21, 14, group_list[found].teacher);
											opt_update = 0;
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											break;
								}
								break;
					}
					
				}while(input_key != ESC && stay);	
			}
			paintArea(15, 5, 66, 22, WHITE);
		}
	}while(1);
}

/*
 * Eliminar grupos.
 */
void groupsDelete()
{
	char search_cve[10];
	int found, dir[2];
	
	do
	{	
		found = 0;
		assignColor(DARK_BLUE);
		windowFrame0(19, 8, 31, 10);
		positionText(22, 8, " CLAVE ");
		
		paintHoriz(20, 30, 9, WHITE);
		gotoxy(21, 9);
		if(!inputID(search_cve, 9))
		{
			found = groupKeyExist( atoi(search_cve));
		}else
		{
			break;	
		}
		
		if(found < 0)
		{
			dialogBox(6);
		}else
		{
			paintArea(15, 6, 64, 19, DARK_BLUE);
			windowFrame0(15, 6, 64, 19);
			positionText(31, 6, " DATOS DEL GRUPO ");
			paintArea(65, 7, 66, 19, LIGHT_GRAY_BLACK);
			paintHoriz(17, 66, 20, LIGHT_GRAY_BLACK);
			assignColor(DARK_BLUE);
			
			windowFrame0(19, 8, 31, 10);
			positionText(22, 8, " CLAVE ");
			
			windowFrame0(50, 8, 60, 10);
			positionText(52, 8, " NIVEL ");
			
			windowFrame0(19, 12, 60, 14);
			positionText(35, 12, " PROFESOR ");
			
			windowFrame0(33, 16, 44, 18);
			
			paintHoriz(20, 30, 9, WHITE); 
			paintHoriz(51, 59, 9, WHITE); 
			paintHoriz(20, 59, 13, WHITE);
			
			gotoxy(21, 9); printf("%d", group_list[found].cve);
			gotoxy(55, 9); printf("%d", group_list[found].level);
			positionText(20, 13, group_list[found].teacher);
			assignColor(RED);
			positionText(34, 17, " ELIMINAR ");
			
			do
			{
				input_key = getch();
				if(input_key == ENTER)
				{
					
					group_list[found].cve = -1;
					group_list[found].level = -1;
					strcpy(group_list[found].teacher, "-1");
					number_students_group[found] = 0;
					
					if( !saveGroups() && !saveStudents() )
					{
						dialogBox(11); //("Se elimino con exitoso!");
					}
				}
			}while(input_key != ENTER && input_key !=ESC);
			
			paintArea(15, 6, 66, 20, WHITE);
		}		
	}while(1);
}

/*
 * Registrar nuevos alumnos.
 */
void studentRegistration()
{
	char input_group[10], input_matricula[10], input_score[6];
	StringN input_name;
	int index, location[2];
	
	paintArea(15, 4, 64, 21, DARK_BLUE);
	windowFrame0(15, 4, 64, 21);
	positionText(27, 4, " INGRESA DATOS DEL ALUMNO ");
	paintArea(65, 5, 66, 21, LIGHT_GRAY_BLACK);
	paintHoriz(17, 66, 22, LIGHT_GRAY_BLACK);
	
	do
	{
		paintArea(29, 7, 51, 14, DARK_BLUE);
	
		windowFrame0(24, 6, 36, 8);
		positionText(25, 6, " MATRICULA ");
		windowFrame0(44, 6, 54, 8);
		positionText(45, 6, " PUNTAJE ");
		windowFrame0(19, 10, 60, 12);
		positionText(25, 10, " ALUMNO ");
		windowFrame0(34, 14, 44, 16);
		positionText(36, 14, " GRUPO ");
		windowFrame0(33, 18, 45, 20);
		positionText(34, 19, " REGISTRAR ");
		
		paintHoriz(25, 35, 7, WHITE); 
		paintHoriz(45, 53, 7, WHITE); 
		paintHoriz(20, 59, 11, WHITE);
		paintHoriz(35, 43, 15, WHITE);
		
		gotoxy(26, 7);
		if(!inputID(input_matricula, 9))
		{
			gotoxy(48, 7);
			if(!inputScore(input_score, 3))
			{
				gotoxy(20, 11);
				if(!inputNAME(input_name, LENGTH_MAX_NAME))
				{
					gotoxy(35, 15);
					if(inputID(input_group, 9))
					{
						break;
					}
				}else
				{
					break;
				}
			}else
			{
				break;
			}
		}else
		{
			break;			
		}		
				
		assignColor(RED);
		positionText(34, 19, " REGISTRAR ");
		
		do
		{
			input_key = getch();
		}while(input_key != ENTER && input_key != ESC);		
		
		if(input_key == ESC)
		{
			break;
		}
		
		assignColor(DARK_BLUE);
		positionText(34, 19, " REGISTRAR ");
		
		if(studentKeyExist(atoi(input_matricula), location))
		{
			dialogBox(2); //("Clave en uso")
			continue;
		}else
		{
			if( atoi(input_matricula) < 1 || atof(input_score) > 10.0 ||  atof(input_score) < 0.0 )
			{
				dialogBox(3); //("Verifique sus datos y vuelva a intentar.");
				continue;
			}else
			{
				index = groupKeyExist(atoi(input_group));
				if( index  == -1 )
				{
					dialogBox(10); //("No se ha encontrado el grupo");
					continue;
				}
			}
		}
		
		addStudent(index, atoi(input_matricula), atof(input_score), input_name, 1);
		
	}while(1);
}

int studentSearchOption(int *option)
{
	TypeMenu opt_menu[2]; //pos_X == pos_Y
	int i;
	strcpy(opt_menu[0].strmsg, " MATRICULA ");
	opt_menu[0].pos_X = 5;
	strcpy(opt_menu[1].strmsg, "   TODOS   ");
	opt_menu[1].pos_X = 6;
	
	assignColor(YELLOW);
	for( i = 0; i < 2; i++ )
	{
		positionText(4, opt_menu[i].pos_X, "|           |");
		positionText(5, opt_menu[i].pos_X, opt_menu[i].strmsg);
	}
	
	assignColor(LIGHT_GREEN);
	positionText(5, opt_menu[*option].pos_X, opt_menu[*option].strmsg);
	
	do
	{
		input_key = getch();
		switch(input_key)
		{
			case -32:
					input_key = getch();
					switch(input_key)
					{
						case UP_ARROW:	
						case DOWN_ARROW:
								assignColor(YELLOW);
								positionText(5, opt_menu[*option].pos_X, opt_menu[*option].strmsg);
								
								*option = (*option) ? 0 : 1;
								
								assignColor(LIGHT_GREEN);
								positionText(5, opt_menu[*option].pos_X, opt_menu[*option].strmsg);
								break;
					}
					break;
					
			case ENTER:
					return 0;
					
			case ESC:
					return 1;			
		}		
	}while(1);
}

/*
 * Consultas sobre alumnos.
 */
void studentQueries()
{
	int location[2], option = 0;
	char search_matricula[10];
	drawHoriz(2, 77, 9, 205, 204, 185);
	
	do
	{
		if(studentSearchOption(&option))
		{
			break;
		}
		
		switch(option)
		{
			case 0:
					assignColor(DARK_BLUE);
					windowFrame0(20, 4, 32, 6);
					positionText(21, 4, " MATRICULA ");
					do
					{
						paintHoriz(21, 31, 5, WHITE);
						gotoxy(22, 5);
						if(!inputID(search_matricula, 9))
						{
							studentQueriesClave(studentKeyExist( atoi(search_matricula), location), location);
							input_key = 64;
						}
					}while(input_key !=ESC);
					break;
					
			case 1:
					studentQueriesAll();
					break;
		}
		paintArea(20, 4, 74, 8, WHITE);
		paintArea(5, 10, 74, 22, WHITE);
	}while(1);
}

void studentQueriesClave(int search_matricula, int dir[2])
{
	if( !search_matricula )
	{
		paintArea(15, 11, 66, 21, WHITE);
		dialogBox(6);
		drawH(29, 51, 9, 205);
	}else
	{
		paintArea(15, 11, 64, 20, DARK_BLUE);
		windowFrame0(15, 11, 64, 20);
		positionText(31, 11, " DATOS DEL ALUMNO ");
		paintArea(65, 12, 66, 20, LIGHT_GRAY_BLACK);
		paintHoriz(17, 66, 21, LIGHT_GRAY_BLACK);
		assignColor(DARK_BLUE);
		
		windowFrame0(19, 13, 31, 15);
		positionText(20, 13, " MATRICULA ");
		
		windowFrame0(35, 13, 45, 15);
		positionText(37, 13, " GRUPO ");
		
		windowFrame0(50, 13, 60, 15);
		positionText(51, 13, " PUNTAJE ");
		
		windowFrame0(19, 17, 60, 19);
		positionText(37, 17, " ALUMNO ");
		
		paintHoriz(20, 30, 14, WHITE); 
		paintHoriz(36, 44, 14, WHITE);
		paintHoriz(51, 59, 14, WHITE); 
		paintHoriz(20, 59, 18, WHITE);
		
		gotoxy(21, 14);printf("%d", student_table[dir[0]][dir[1]].matricula);
		gotoxy(36, 14);printf("%d", group_list[dir[0]].cve);
		gotoxy(54, 14);printf("%.1f", student_table[dir[0]][dir[1]].score);
		positionText(20, 18, student_table[dir[0]][dir[1]].name);
		positionText(20, 18, student_table[dir[0]][dir[1]].name);
	}
}

void studentQueriesAll()
{
	Student *temp_list_all = NULL;
	int *index_grupo = NULL;
	int opc_x[4] = {21, 35, 46, 58};
	
	int i, j, k, length = 0;
	
	for(i = 0; i < number_groups; i++)
	{
		length += number_students_group[i];
	}
	
	if(length)
	{
		temp_list_all = (Student *) malloc(sizeof(Student) * length);
		index_grupo = (int *) malloc(sizeof(int) * length);
		
		k = 0;
		for(i = 0; i < number_groups; i++)
		{
			for(j = 0; j < number_students_group[i]; j++)
			{
				temp_list_all[k].matricula = student_table[i][j].matricula;
				strcpy(temp_list_all[k].name, student_table[i][j].name);
				temp_list_all[k].score = student_table[i][j].score;
				index_grupo[k] = group_list[i].cve;
				k++;
			}
		}
		
		assignColor(WHITE);
		positionText(20, 8, "[ ]MATRICULA  [ ]ALUMNO  [ ]PUNTAJE  [ ]GRUPO");
				
		paintArea(5, 10, 74, 22, DARK_BLUE);
		windowFrame0(5, 10, 74, 22);
		positionText(6, 11, "MATRICULA");
		positionText(32, 11, "ALUMNO");
		positionText(57, 11, "PUNTAJE   GRUPO");
		drawHoriz(5, 74, 12, 196, 195, 180);
		drawVerti(15, 10, 12, 179, 194, 193);
		drawVerti(56, 10, 12, 179, 194, 193);
		drawVerti(64, 10, 12, 179, 194, 193);
		
		
		
		printStudentList(temp_list_all, index_grupo, 0, length);
		
		paintHoriz(6, 73, 13, YELLOW);
		printFila3(temp_list_all[0], index_grupo[0], 13);
		
		moveListStudents(temp_list_all, index_grupo, length, opc_x);
	}else
	{
		dialogBox(5);
	}
	
	if(temp_list_all != NULL)
	{
		free(temp_list_all);
	}
	
	if(index_grupo != NULL)
	{
		free(index_grupo);
	}
}

void moveListStudents(Student *temp_list_all, int *index_grupo, int length, int *opc_x)
{
	int index, screen_position, opc_ordenar;
		
	screen_position = 13;
	index = 0;
	opc_ordenar = 0;
	
	do
	{
		input_key = getch();
		switch(input_key)
		{
			case -32:
					input_key = getch();
					switch(input_key)
					{
						case UP_ARROW:
								if(screen_position == 13 && index > 0)
								{
									printStudentList(temp_list_all, index_grupo, --index, length);
									paintHoriz(6, 73, screen_position, YELLOW);
									printFila3(temp_list_all[index], index_grupo[index], screen_position);
								}else
								{
									if(screen_position > 13)
									{
										paintHoriz(6, 73, screen_position, DARK_BLUE);
										printFila3(temp_list_all[index], index_grupo[index], screen_position);
										screen_position--;
										index--;
										paintHoriz(6, 73, screen_position, YELLOW);
										printFila3(temp_list_all[index], index_grupo[index], screen_position);
									}
								}
								break;
						
						case DOWN_ARROW:
								if(screen_position == 21 && index < length - 1)
								{
									printStudentList(temp_list_all, index_grupo, ++index-8, length);
									paintHoriz(6, 73, screen_position, YELLOW);
									printFila3(temp_list_all[index], index_grupo[index], screen_position);
								}else
								{
									if(screen_position < 21 && index < length - 1)
									{
										paintHoriz(6, 73, screen_position, DARK_BLUE);
										printFila3(temp_list_all[index], index_grupo[index], screen_position);
										screen_position++;
										index++;
										paintHoriz(6, 73, screen_position, YELLOW);
										printFila3(temp_list_all[index], index_grupo[index], screen_position);
									}
								}
								break;
						
						case LEFT_ARROW:
								assignColor(WHITE);
								printChar(opc_x[opc_ordenar], 8, 32);
								assignColor(GREEN_BLACK);
								
								opc_ordenar = (opc_ordenar) ?  --opc_ordenar : 3;	
									
								printChar(opc_x[opc_ordenar], 8, 32);
								screen_position = 13;
								index = 0;
								orderStudents2(temp_list_all, index_grupo, length, opc_ordenar);										
								break;
								
						case RIGHT_ARROW:
								assignColor(WHITE);
								printChar(opc_x[opc_ordenar], 8, 32);
								assignColor(GREEN_BLACK);
								
								opc_ordenar = (opc_ordenar == 3) ? 0 : ++opc_ordenar ;
								
								printChar(opc_x[opc_ordenar], 8, 32);
								screen_position = 13;
								index = 0;
								orderStudents2(temp_list_all, index_grupo, length, opc_ordenar);
								break;	
					}
					break;
		}
	}while(input_key != ESC);
}

void printStudentList(Student *list_all, int *group, int start, int length)
{
	int i, pos = 13;
	paintArea(6, 13, 73, 21, DARK_BLUE);
	for(i = start; i < (start + 9) && i < length; i++ , pos++)
	{
		printFila3(list_all[i], group[i], pos);	
	}
}

void printFila3(Student list, int group, int pos)
{
	gotoxy(6, pos); printf("%9d", list.matricula);
	positionText(17, pos, list.name);
	gotoxy(59, pos); printf("%.1f", list.score);
	gotoxy(65, pos); printf("%9d", group);
}

void orderStudents2(Student *list, int *index_grupo, int length, int opc_order)
{
	int i, j;
	int temp_index_grupo;
	
	for (i = 0; i < length; i++)
	{
    	for (j = 0; j < length - 1; j++) 
		{      	
	      	switch(opc_order)
			{
				case 0:
				    	if (list[j].matricula > list[j + 1].matricula) 
					  	{
				        	changeStudentsOrder(list, j);
				        	temp_index_grupo = index_grupo[j];
				        	index_grupo[j] = index_grupo[j + 1];
				        	index_grupo[j + 1] = temp_index_grupo;
				      	}
						break;
						
				case 1:
				    	if (strcmp(list[j].name, list[j + 1].name) > 0 ) 
					  	{
				        	changeStudentsOrder(list, j);
				        	temp_index_grupo = index_grupo[j];
				        	index_grupo[j] = index_grupo[j + 1];
				        	index_grupo[j + 1] = temp_index_grupo;
				      	}
						break;
						
				case 2:
				    	if (list[j].score < list[j + 1].score) 
					  	{
				        	changeStudentsOrder(list, j);
				        	temp_index_grupo = index_grupo[j];
				        	index_grupo[j] = index_grupo[j + 1];
				        	index_grupo[j + 1] = temp_index_grupo;
				      	}
						break;
				
				case 3:
				    	if (index_grupo[j] > index_grupo[j + 1]) 
					  	{
				        	changeStudentsOrder(list, j);
				        	temp_index_grupo = index_grupo[j];
				        	index_grupo[j] = index_grupo[j + 1];
				        	index_grupo[j + 1] = temp_index_grupo;
				      	}
						break;
			}	      	
    	}
  	}
  	
  	printStudentList(list, index_grupo, 0, length);	
	paintHoriz(6, 73, 13, YELLOW);
	printFila3(list[0], index_grupo[0], 13);
}

/*
 * Modificacion de alumnos.
 */
void studentModify()
{
	char input_matricula[10], input_score[6], input_group[10];
	StringN input_name;
	int opt_update, stay, found, found_group = -1;
	int opt[4][2] = {{20, 10}, {28, 14}, {44, 14}, {34, 18}};
	int dir[2];
	
	do
	{
		assignColor(DARK_BLUE);
		windowFrame0(33, 6, 45, 8);
		positionText(34, 6, " MATRICULA ");
		paintHoriz(34, 44, 7, WHITE);
		
		gotoxy(35, 7);
		if(!inputID(input_matricula, 9))
		{
			found = studentKeyExist(atoi(input_matricula), dir);
		}else
		{
			break;
		} 
		
		if(!found)
		{
			dialogBox(6);
		}else
		{
			opt_update = 0;
			
			strcpy(input_name, student_table[dir[0]][dir[1]].name);
			sprintf(input_score, "%.1lf", student_table[dir[0]][dir[1]].score);
			itoa(group_list[dir[0]].cve, input_group, 10);
			
			paintArea(15, 5, 64, 20, DARK_BLUE);
			windowFrame0(15, 5, 64, 20);
			positionText(31, 5, " DATOS DEL ALUMNO ");
			paintArea(65, 6, 66, 20, LIGHT_GRAY_BLACK);
			paintHoriz(17, 66, 21, LIGHT_GRAY_BLACK);
			
			while(input_key != ESC)
			{	
				stay = 1;		
				found_group = -1;	
				paintArea(29, 7, 51, 14, DARK_BLUE);
				
				windowFrame0(33, 6, 45, 8);
				positionText(34, 6, " MATRICULA ");
				
				windowFrame0(19, 9, 60, 11);
				positionText(34, 9, " *ALUMNO ");
				
				windowFrame0(24, 13, 35, 15);
				positionText(25, 13, " *PUNTAJE ");
				
				windowFrame0(43, 13, 53, 15);
				positionText(44, 13, " *GRUPO ");
				
				windowFrame0(33, 17, 46, 19);
				positionText(34, 18, " ACTUALIZAR ");
				
				paintHoriz(34, 44, 7, WHITE);  
				paintHoriz(20, 59, 10, WHITE);	
				paintHoriz(25, 34, 14, WHITE); 
				paintHoriz(44, 52, 14, WHITE);						
				
				positionText(16, 22, "*ENTER PARA EDITAR");
				positionText(38, 22, "*ESC PARA CANCELAR EDICION");
				
				gotoxy(35, 7); printf("%d", student_table[dir[0]][dir[1]].matricula);
				positionText(20, 10, student_table[dir[0]][dir[1]].name);
				gotoxy(28, 14); printf("%.1lf", student_table[dir[0]][dir[1]].score);
				gotoxy(44, 14); printf("%d", group_list[dir[0]].cve);				
				
				gotoxy(opt[opt_update][0], opt[opt_update][1]);
				
				do
				{
					input_key = getch();
					switch(input_key)
					{
						case -32:
								input_key = getch();
								switch(input_key)
								{
											
									case UP_ARROW:
											if(opt_update == 3)
											{
												opt_update = 2;
												assignColor(DARK_BLUE);
												positionText(34, 18, " ACTUALIZAR ");
											}else
											{
												if(opt_update == 1 || opt_update == 2)
												{
													opt_update = 0;
												}
											}
											break;
											
									case LEFT_ARROW:
											if(opt_update == 2)
											{
												opt_update = 1;
											}
											break;
									case RIGHT_ARROW:
											if(opt_update == 1)
											{
												opt_update = 2;
											}
											break;
									case DOWN_ARROW:
											if(!opt_update)
											{
												opt_update = 1;
											}else
											{
												if(opt_update == 1 || opt_update == 2)
												{
													opt_update = 3;
													assignColor(RED);
													positionText(34, 18, " ACTUALIZAR ");
												}
											}
											break;
								}
								gotoxy(opt[opt_update][0], opt[opt_update][1]);	
								break;
								
						case ENTER:
								switch(opt_update)
								{
									case 0:
											paintHoriz(20, 59, 10, WHITE);
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											if(inputNAME(input_name, LENGTH_MAX_NAME))
											{
												paintHoriz(20, 59, 10, WHITE);
												input_key = 64;
												strcpy(input_name, student_table[dir[0]][dir[1]].name);
												positionText(20, 10, input_name);
											}
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											break;
											
									case 1:
											paintHoriz(25, 34, 14, WHITE); 
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											if(inputScore(input_score, 3))
											{
												paintHoriz(25, 34, 14, WHITE); 
												input_key = 64;
												sprintf(input_score, "%.1lf", student_table[dir[0]][dir[1]].score);
												positionText(28, 14, input_score);
											}
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											break;
											
									case 2:
											paintHoriz(44, 52, 14, WHITE);	
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											if(inputID(input_group, 9))
											{
												paintHoriz(44, 52, 14, WHITE);	 
												input_key = 64;
												itoa(group_list[dir[0]].cve, input_group, 10);
												positionText(44, 14, input_group);
											}
											gotoxy(opt[opt_update][0], opt[opt_update][1]);
											break;
									case 3:
											assignColor(DARK_BLUE);
											positionText(34, 18, " ACTUALIZAR ");
											
											if(!strcmp(input_name, student_table[dir[0]][dir[1]].name) && atof(input_score) == student_table[dir[0]][dir[1]].score && atoi(input_group) == group_list[dir[0]].cve)
											{
												dialogBox(7); //("Sin cambios");
											}else
											{
												if(atof(input_score) > 10.0 ||  atof(input_score) < 0.0)
												{
													sprintf(input_score, "%.1lf", student_table[dir[0]][dir[1]].score);
													dialogBox(3); //("Verifique sus datos");
												}else
												{
													if(group_list[dir[0]].cve == atoi(input_group))
													{
														student_table[dir[0]][dir[1]].score = atof(input_score);
														strcpy(student_table[dir[0]][dir[1]].name, input_name);
														if(saveStudents())
														{
															dialogBox(4); //("No se guardaron los cambios");
														}else
														{
															dialogBox(8); //("Se guardaron los cambios");
														}
													}else
													{
														found_group = groupKeyExist(atoi(input_group));
														if(found_group == -1)
														{
															dialogBox(10); //("No se ha encontrado el grupo");
														}else
														{
															moveItems(dir);
															addStudent(found_group, atoi(input_matricula), atof(input_score), input_name, 8);
															dir[0] = found_group;
															dir[1] = number_students_group[found_group] - 1;
														}
														
													}
												}
											}
											stay = 0;
											break;
								}
								break;
					}
					
				}while(input_key != ESC && stay);
			}
			paintArea(15, 5, 66, 22, WHITE);
		}
	}while(1);
}

void moveItems(int dir[2])
{
	int i;
	for(i = dir[1]; i < number_students_group[dir[0]] - 1; i++)
	{
		student_table[dir[0]][i] = student_table[dir[0]][i+1];
	}
	
	number_students_group[dir[0]]--;
}

/*
 * Eliminar alumnos.
 */
void studentDelete()
{
	char search_matricula[10];
	int found, dir[2];
	
	do
	{	
		found = 0;
		assignColor(DARK_BLUE);
		windowFrame0(19, 8, 31, 10);
		positionText(20, 8, " MATRICULA ");
		
		paintHoriz(20, 30, 9, WHITE);
		gotoxy(21, 9);
		if(!inputID(search_matricula, 9))
		{
			found = studentKeyExist( atoi(search_matricula), dir);
		}else
		{
			break;	
		}
		
		if(!found)
		{
			dialogBox(6);
		}else
		{
			paintArea(15, 6, 64, 19, DARK_BLUE);
			windowFrame0(15, 6, 64, 19);
			positionText(31, 6, " DATOS DEL ALUMNO ");
			paintArea(65, 7, 66, 19, LIGHT_GRAY_BLACK);
			paintHoriz(17, 66, 20, LIGHT_GRAY_BLACK);
			assignColor(DARK_BLUE);
			
			windowFrame0(19, 8, 31, 10);
			positionText(20, 8, " MATRICULA ");
			
			windowFrame0(50, 8, 60, 10);
			positionText(51, 8, " PUNTAJE ");
			
			windowFrame0(19, 12, 60, 14);
			positionText(35, 12, " ALUMNO ");
			
			windowFrame0(33, 16, 44, 18);
			
			paintHoriz(20, 30, 9, WHITE); 
			paintHoriz(51, 59, 9, WHITE); 
			paintHoriz(20, 59, 13, WHITE);
			
			gotoxy(21, 9); printf("%d", student_table[dir[0]][dir[1]].matricula);
			gotoxy(54, 9); printf("%.1lf", student_table[dir[0]][dir[1]].score);
			positionText(20, 13, student_table[dir[0]][dir[1]].name);
			assignColor(RED);
			positionText(34, 17, " ELIMINAR ");
			
			do
			{
				input_key = getch();
				if(input_key == ENTER)
				{
					moveItems(dir);
					if( !saveGroups() && !saveStudents() )
					{
						dialogBox(11); //("Se elimino con exitoso!");
					}
				}
			}while(input_key != ENTER && input_key !=ESC);
			
			paintArea(15, 6, 66, 20, WHITE);
		}		
	}while(1);
}


/*
 * Valida clave/matricula.
 */
int inputID(char *str, int limite)
{
	int cont_no_c = 0;
	fflush(stdin);

	do
	{
		input_key = getch();
		switch(input_key)
		{
			case -32:
					input_key = getch();
					switch(input_key)
					{
						case 72:
						case 75:
						case 77:
						case 80:
								continue;
					}
					break;
					
			case 8:
					if(cont_no_c > 0)
					{
						printf("\b \b");
						cont_no_c--;
					}
					break;
					
			case 9:
					break;
					
			case 13:
					if(cont_no_c > 0)
					{
						str[cont_no_c] = '\0';
						return 0;	
					}
					break;
					
			case 27: //regresar al menu principal
					return 1;
					break;
										
			default:
					if(cont_no_c < limite && isNumber(input_key))
					{
						str[cont_no_c] = input_key;
						cont_no_c++;
						printf("%c", input_key);						
					}
					break;
		}
		
	}while(1);
}

/*
 * Valida nombres.
 */
int inputNAME(char *str, int limite)
{
	int cont_no_c = 0;
	
	do
	{
		input_key = getch();
		switch(input_key)
		{
			case -32:
					input_key = getch();
					switch(input_key)
					{
						case 72:
						case 75:
						case 77:
						case 80:
								continue;
					}
					break;
					
			case 8:
					if(cont_no_c > 0)
					{
						printf("\b \b");
						cont_no_c--;
					}
					break;
					
			case 9:
					break;
					
			case 13:
					if(cont_no_c > 0)
					{
						str[cont_no_c] = '\0';
						return 0;	
					}
					break;
					
			case 27: 
					return 1;
					break;
										
			default:
					if(cont_no_c < limite)
					{
						if(cont_no_c == 0 && input_key == ' ')
						{
							continue;
						}
						
						if(cont_no_c > 0 && str[cont_no_c-1] == ' ' && input_key == ' ' )
						{
							continue;
						}
						
						if(input_key >= 97 && input_key <= 122)
						{
							str[cont_no_c] = input_key - 32;
							cont_no_c++;
							printf("%c", input_key - 32);
						}else
						{
							if((input_key >= 65 && input_key <= 90) || (input_key == ' ' || input_key == -91 || input_key == -112))
							{
								str[cont_no_c] = input_key;
								cont_no_c++;
								printf("%c", input_key);
							}else
							{
								switch(input_key)
								{
									case -92:
											input_key = -91;
											break;
									case -96:
											input_key = 65; //NO SOPORTADO
											break;
									case -126:
											input_key = -112;
											break;
									case -95:
											input_key = 73; //NO SOPORTADO
											break;
									case -94:
											input_key = 79; //NO SOPORTADO
											break;
									case -93: 
											input_key = 85; //NO SOPORTADO
											break;
									default:
											continue;
											break;
								}
								str[cont_no_c] = input_key;
								cont_no_c++;
								printf("%c", input_key);
							}
						}
						
					}
					break;
		}
		
	}while(1);
}

/*
 * Punto flotante
 */
int inputScore(char* str, int limite) 
{
	int punto = 0;
	int ps;
    int cont_no_c = 0;
    char input_key;

    fflush(stdin);

    do {
        input_key = getch();

        switch (input_key) 
		{
			case -32:
	                input_key = getch();
	                switch (input_key) 
					{
	                    case 72:
	                    case 75:
	                    case 77:
	                    case 80:
	                        continue;
	                }
	                break;

            case 8:
	                if (cont_no_c > 0) 
					{
	                    printf("\b \b");
	                    cont_no_c--;
	                    if(punto && cont_no_c == ps)
	                    {
	                    	punto = 0; 
						}
	                }
	                break;

            case 9:
                break;

            case 13:
	                if (cont_no_c > 0) 
					{
	                    str[cont_no_c] = '\0';
	                    return 0;
	                }
	                break;

            case 27:  // regresar al menu principal
	                return 1;
	                break;

            case 46:
	                if (cont_no_c < limite && punto == 0) 
					{
	                	punto = 1;
	                	ps = cont_no_c;
	                    str[cont_no_c] = input_key;
	                    cont_no_c++;
	                    printf("%c", input_key);
	                }
	                break;

            default:
	                if (cont_no_c < limite && isNumber(input_key))
					{
	                    str[cont_no_c] = input_key;
	                    cont_no_c++;
	                    printf("%c", input_key);
	                }
	                break;
        }

    }while (1);
}

/*
 * Verifica si es un numero
 */
int isNumber(char c)
{
	return  (c >= 48 && c <= 57 ) ? 1 : 0;
}

/*
 * Genera los menjas al realizar alguna accion
 */
void dialogBox(int type)
{	
	
	switch(type)
	{
		case 1:
				paintArea(29, 7, 51, 14, LIGHT_GREEN);
				positionText(31, 10, "REGISTRO EXITOSO..!");
				break;
				
		case 2:
				paintArea(29, 7, 51, 14, YELLOW);
				positionText(31, 10, "Es posible que la");
				positionText(30, 11, "clave ya este en uso.");
				break;
				
		case 3: 
				paintArea(29, 7, 51, 14, YELLOW);
				positionText(31, 10, "Verifique sus datos");
				positionText(30, 11, "y vuelva a intentar..");
				break;
		
		case 4:
				paintArea(29, 7, 51, 14, RED);
				positionText(33, 10, "No se han podido");
				positionText(31, 11, "guargar los cambios.");
				break;
		
		case 5:
				paintArea(29, 7, 51, 14, RED);
				positionText(33, 10, "No hay registros");
				positionText(34, 11, "disponibles.");
				break;
				
		case 6:
				paintArea(29, 7, 51, 14, RED);
				positionText(31, 9, "No se ha encontrado");
				positionText(35, 10, "el registro");
				positionText(34, 11, "especificado.");
				break;
				
		case 7:
				paintArea(29, 7, 51, 14, YELLOW);
				positionText(33, 9, "Los datos no");
				positionText(35, 10, "presentan");
				positionText(36, 11, "cambios.");
				break;
		
		case 8:
				paintArea(29, 7, 51, 14, LIGHT_GREEN);
				positionText(34, 9, "Los datos se");
				positionText(32, 10, "han actualizado");
				positionText(33, 11, "correctamente.");
				break;
		
		case 9:
				paintArea(29, 7, 51, 14, RED);
				positionText(32, 9, "No existen grupos");
				positionText(33, 10, "primero cree un");
				positionText(33, 11, "grupo para poder");
				positionText(35, 12, "continuar.");
				break;
				
		case 10:
				paintArea(29, 7, 51, 14, YELLOW);
				positionText(31, 9, "No se ha encontrado");
				positionText(35, 10, "el grupo");
				positionText(34, 11, "especificado.");
				break;
				
		case 11:
				paintArea(29, 7, 51, 14, LIGHT_GREEN);
				positionText(33, 9, "Se elimino ");
				positionText(35, 10, "correctamnte");
				positionText(34, 11, "el registro.");
				break;
	}
	
	getch();
	paintArea(29, 7, 51, 14, WHITE);
}
