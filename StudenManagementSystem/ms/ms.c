#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "ms.h"
#include "show.h"

#define drv_cmd(x) drv_cmd_##x

static void drv_cmd_H(struct class_node * class);
static void drv_cmd_T(struct class_node * class);
static void drv_cmd_P(struct class_node * class);
static void drv_cmd_L(struct class_node * class);
static void drv_cmd_A(struct class_node * class);
static void drv_cmd_S(struct class_node * class);
static void drv_cmd_Q(struct class_node * class);
static void drv_cmd_W(struct class_node * class);
static void drv_cmd_X(struct class_node * class);
static int drv_end(struct class_node * class);


char ms_buf[SIZE];



struct grades_node inode;

struct grades_node gnode;

//========================================================//

static void drv_gets_help_num(struct class_node * class)
{

    if(class->num < 10)
    {
        show_mian[sizeof(show_mian) - 33] = '0';

        show_mian[sizeof(show_mian) - 32] = class->num + '0';
    }
    else
    {
        show_mian[sizeof(show_mian) - 33] = class->num / 10 + '0';

        show_mian[sizeof(show_mian) - 32] = class->num % 10 + '0';
    }

    class->buf = show_mian;
    
}

static void drv_show_help(struct class_node * class)
{
    system("clear");

    drv_gets_help_num(class);
   
    printf("%s", class->buf);

}

static int drv_show_null(struct class_node * class)
{
    if(!class->num)
    {
        system("clear");

        printf("%s", show_null);

        sleep(2);

        my_opt.cmd = drv_cmd(H);

        return 1;
    }

    return 0;

}


static void drv_gets_grades(struct grades_node * node)
{
    
    if(node->id < 10)
    {
        grades2[21] = '0';

        grades2[22] = node->id + '0';
    }
    else
    {
        grades2[21] = node->id / 10 + '0';

        grades2[22] = node->id % 10 + '0';
    }

    sprintf(&grades2[28], "%.1f", node->Language);

    sprintf(&grades2[37], "%.1f", node->Math);

    sprintf(&grades2[45], "%.1f", node->English);

    sprintf(&grades2[55], "%.1f", node->Grage);

    for(int i = 0; i < 70; i++)
    {
        if(grades2[i] == 0)grades2[i] =  ' ';
    }

    printf("%s", grades2);
}


static int drv_show_grades(struct class_node * class)
{
    if(drv_show_null(class)) return 0;

    system("clear");

    printf("%s", grahead1);

    do{

        drv_gets_grades(class->node);

        class->node = class->node->node;

    }while (class->node->id);
    
    return 1;
}

//================================================================//

//初始化链表
static struct grades_node * drv_creat_grades_node(int id, float lan, float math, float eng)
{
    struct grades_node * node = (struct grades_node *)malloc(sizeof(struct grades_node));

    if(node == NULL)
    {
        printf("inode malloc failure\n");

        return NULL;
    }

    node->node = node; 

    node->id = id;

    node->Language = lan;

    node->Math = math;

    node->English = eng;

    node->Grage = lan + math + eng;

    node->Average = node->Grage / 3;

    return node;
}

//id插入链表
static int drv_insert_node_id(struct class_node * class, struct grades_node * node)
{

    class->num += 1;

    class->node = &inode;

    while((class->node->node->id < node->id) && (class->node->node->id))

    class->node = class->node->node;
       
    node->node = class->node->node;

    class->node->node = node;

    return 0;

}

static int drv_delete_node(struct class_node * class, int id)
{
    class->node = &inode;

    for(int i = 0; i < class->num; i++)
    {
        if(class->node->node->id == id) break;

        class->node = class->node->node;
    }

    if(class->node->node->id != id)
    {
        printf("没有当前学生的信息\n");

        return 0;
    }

    struct grades_node * p = class->node->node;

    class->node = p->node;

    free(p);

    class->node = &gnode;

    for(int i = 0; i < class->num; i++)
    {
        if(class->node->node->id == id) break;

        class->node = class->node->node;
    }

    p = class->node->node;

    class->node = p->node;

    free(p);

    p = NULL;

    class->num -= 1;

    return 0;

}

static int drv_insert_node_before(struct grades_node * node1, struct grades_node * node2)
{
    while(node1->node->id) node1 = node1->node;

    node2->node = node1->node;

    node1->node = node2;
}

//grade插入链表
static int drv_insert_node_gr(struct class_node * class, struct grades_node * node)
{

    class->node = &gnode;

    while(class->node->node->id)
    {
        if(class->node->node->Grage > node->Grage)class->node = class->node->node;

        else break;      
    }

    node->node = class->node->node;

    class->node->node = node;

    return 0;
}


static void drv_close_list1(struct grades_node * list)
{
    struct grades_node * p = list->node;

    list = NULL;

    if(p)
    {
        free(p);

        p = p->node;
    }
}

static void drv_close_list2(struct intput_grages_list * list)
{
    struct intput_grages_list * p = list->node;

    list = NULL;

    if(p)
    {
        free(p);

        p = p->node;
    }
}



//================================================================//



static int drv_str_int(char * str, int size)
{
    int num = 0;

    for(int i = 0; i < size; i++)

    num = num * 10 + (str[i] - '0');

    return num;
}

static void drv_show_grades_t(struct grades_node * node)
{
    system("clear");

    printf("\n\n                                         按H键返回\n");

    printf("%s", grahead1);

    while (node->id)

    node = node->node;

    node = node->node;

    do{
            
        drv_gets_grades(node);

        node = node->node;

    }while (node->id);
}

static struct intput_grages_list * drv_intput_list_init(int id)
{
    struct intput_grages_list * list = (struct intput_grages_list *)malloc(sizeof(struct intput_grages_list));

    if(list == NULL) return NULL;

    list->id = id;

    strcpy(list->data, grades1);

    list->node = list;

    list->data[grades1_1] = 0;

    list->data[grades1_2] = 0;

    list->data[grades1_3] = 0;

    list->data[grades1_4] = 0;

    return list;
}

static void drv_input_list_before(struct intput_grages_list * list1, struct intput_grages_list * list2)
{
    while(list1->node->id) list1 = list1->node;

    list2->node = list1->node;

    list1->node = list2;
}



static int drv_get_grades(struct class_node * class, struct grades_node * node, struct intput_grages_list * list)
{
    struct intput_grages_list * list1 = drv_intput_list_init(1);

    drv_input_list_before(list, list1);

tiaozhuan1:

    do{

        printf("%s", list->data);

        list = list->node;

    }while(list->id);

    memset(ms_buf, 0, SIZE);

    fgets(ms_buf, SIZE, stdin);

    if((ms_buf[0] == 'H') || (ms_buf[0] == 'h')) 
    {
        my_opt.cmd = drv_cmd(H);

        return 1;
    }

    if(ms_buf[0] <= '0' || ms_buf[0] > '9') 
    {
        system("clear");

        goto tiaozhuan1;
    }
    int id = drv_str_int(ms_buf, strlen(ms_buf) - 1);

    class->node = inode.node;

    for(int i = 0; i < class->num; i++)
    {
        if(class->node->id == id)
        {
            printf("\n      该同学成绩已存在，请重新输入\n");

            sleep(1);

            system("clear");

            goto tiaozhuan1;
        }

        class->node = class->node->node;
    }

    strncpy(&list1->data[grades1_1], ms_buf, strlen(ms_buf) - 1);

    system("clear");

tiaozhuan2:

    do{

        printf("%s", list->data);

        list = list->node;

    }while(list->id);

    memset(ms_buf, 0, SIZE);

    fgets(ms_buf, SIZE, stdin);

    if(ms_buf[0] == '\n')
    {
        system("clear");

        goto tiaozhuan2;
    } 

    char * p = ms_buf;

    float lan = strtof(p, &p);
    
    if((lan > 100) || (lan < 0))
    {
        printf("\n      输入错误，请重新输入\n");

        sleep(1);

        system("clear");

        goto tiaozhuan2;
    }

    strncpy(&list1->data[grades1_2], ms_buf, strlen(ms_buf) - 1);

    system("clear");

tiaozhuan3:

    do{

        printf("%s", list->data);

        list = list->node;

    }while(list->id);

    memset(ms_buf, 0, SIZE);

    fgets(ms_buf, SIZE, stdin);

    if(ms_buf[0] == '\n') 
    {
        system("clear");

        goto tiaozhuan3;
    }

    p = ms_buf;

    float math = strtof(p, &p);
    
    if((math > 100) || (math < 0))
    {
        printf("\n      输入错误，请重新输入\n");

        sleep(1);

        system("clear");

        goto tiaozhuan3;
    }

    strncpy(&list1->data[grades1_3], ms_buf, strlen(ms_buf) - 1);

    system("clear");

tiaozhuan4:

    do{

        printf("%s", list->data);

        list = list->node;

    }while(list->id);

    memset(ms_buf, 0, SIZE);

    fgets(ms_buf, SIZE, stdin);

    if(ms_buf[0] == '\n')
    {
        system("clear");

        goto tiaozhuan4;
    } 

    p = ms_buf;

    float eng = strtof(p, &p);
    
    if((eng > 100) || (eng < 0))
    {
        printf("\n      输入错误，请重新输入\n");

        sleep(1);

        system("clear");

        goto tiaozhuan4;
    }

    strncpy(&list1->data[grades1_4], ms_buf, strlen(ms_buf) - 1);

    struct grades_node * node1 = drv_creat_grades_node(id, lan, math, eng);

    drv_insert_node_before(node, node1);

    struct grades_node * node2 = drv_creat_grades_node(node1->id, node1->Language, node1->Math, node1->English);

    struct grades_node * node3 = drv_creat_grades_node(node1->id, node1->Language, node1->Math, node1->English);

    drv_insert_node_id(class, node2);

    drv_insert_node_gr(class, node3);

    system("clear");

    return 0;
}


static int drv_rev_grades(struct class_node * class, struct grades_node * node, struct intput_grages_list * list)
{
    struct intput_grages_list * list1 = drv_intput_list_init(1);

    drv_input_list_before(list, list1);

tiaozhuan11:

    do{

        printf("%s", list->data);

        list = list->node;

    }while(list->id);

    memset(ms_buf, 0, SIZE);

    fgets(ms_buf, SIZE, stdin);

    if((ms_buf[0] == 'H') || (ms_buf[0] == 'h')) 
    {
        my_opt.cmd = drv_cmd(H);

        return 1;
    }

    if(ms_buf[0] == '\n') 
    {
        system("clear");

        goto tiaozhuan11;
    }
    int id = drv_str_int(ms_buf, strlen(ms_buf) - 1);

    class->node = inode.node;

    while(class->node->id)
    {
        if(class->node->id == id) break;

        class->node = class->node->node;
    }

    if(class->node->id == 0)
    {
        printf("\n      没有该同学成绩，请重新输入\n");

        sleep(1);

        system("clear");

        goto tiaozhuan11;
    }

    strncpy(&list1->data[grades1_1], ms_buf, strlen(ms_buf) - 1);

    system("clear");

tiaozhuan12:

    do{

        printf("%s", list->data);

        list = list->node;

    }while(list->id);

    memset(ms_buf, 0, SIZE);

    fgets(ms_buf, SIZE, stdin);

    if(ms_buf[0] == '\n')
    {
        system("clear");

        goto tiaozhuan12;
    } 

    char * p = ms_buf;

    float lan = strtof(p, &p);
    
    if((lan > 100) || (lan < 0))
    {
        printf("\n      输入错误，请重新输入\n");

        sleep(1);

        system("clear");

        goto tiaozhuan12;
    }

    strncpy(&list1->data[grades1_2], ms_buf, strlen(ms_buf) - 1);

    system("clear");

tiaozhuan13:

    do{

        printf("%s", list->data);

        list = list->node;

    }while(list->id);

    memset(ms_buf, 0, SIZE);

    fgets(ms_buf, SIZE, stdin);

    if(ms_buf[0] == '\n') 
    {
        system("clear");

        goto tiaozhuan13;
    }

    p = ms_buf;

    float math = strtof(p, &p);
    
    if((math > 100) || (math < 0))
    {
        printf("\n      输入错误，请重新输入\n");

        sleep(1);

        system("clear");

        goto tiaozhuan13;
    }

    strncpy(&list1->data[grades1_3], ms_buf, strlen(ms_buf) - 1);

    system("clear");

tiaozhuan14:

    do{

        printf("%s", list->data);

        list = list->node;

    }while(list->id);

    memset(ms_buf, 0, SIZE);

    fgets(ms_buf, SIZE, stdin);

    if(ms_buf[0] == '\n')
    {
        system("clear");

        goto tiaozhuan14;
    } 

    p = ms_buf;

    float eng = strtof(p, &p);
    
    if((eng > 100) || (eng < 0))
    {
        printf("\n      输入错误，请重新输入\n");

        sleep(1);

        system("clear");

        goto tiaozhuan14;
    }

    strncpy(&list1->data[grades1_4], ms_buf, strlen(ms_buf) - 1);

    struct grades_node * node1 = drv_creat_grades_node(id, lan, math, eng);

    drv_insert_node_before(node, node1);

    class->node->Language = lan;

    class->node->Math = math;

    class->node->English = eng;

    class->node->Grage = lan + math + eng;
     
    class->node = &gnode;

    while(class->node->node->id != id) class->node = class->node->node;

    struct grades_node * node3 = class->node->node;

    node3->Language = lan;

    node3->Math = math;

    node3->English = eng;

    node3->Grage = lan + math + eng;

    class->node->node = node3->node;

    node3->node = node3;

    drv_insert_node_gr(class, node3);

    system("clear");

    return 0;
}




static void drv_choose_h(struct class_node * class)
{
    switch (ms_buf[0])
    {
        case 'H': my_opt.cmd = drv_cmd(H); break;

        case 'T': my_opt.cmd = drv_cmd(T); break;

        case 'S': my_opt.cmd = drv_cmd(S); break;

        case 'P': my_opt.cmd = drv_cmd(P); break;

        case 'Q': my_opt.cmd = drv_cmd(Q); break;
    
        default:

            printf("\n     输入命令错误\n");

            sleep(2);

            my_opt.cmd = drv_cmd(H);

            break;
    }
}

static void drv_choose_p(struct class_node * class)
{
    switch (ms_buf[0])
    {
        case 'H': my_opt.cmd = drv_cmd(H); break;

        case 'T': my_opt.cmd = drv_cmd(T); break;

        case 'X': my_opt.cmd = drv_cmd(X); break;

        case 'S': my_opt.cmd = drv_cmd(S); break;
    
        default:

            printf("\n              输入命令错误\n");

            sleep(2);

            my_opt.cmd = drv_cmd(P);

            break;

    }
}

static void drv_choose_s(struct class_node * class)
{
    switch (ms_buf[0])
    {
        case 'H': my_opt.cmd = drv_cmd(H); break;

        case 'T': my_opt.cmd = drv_cmd(T); break;

        case 'X': my_opt.cmd = drv_cmd(X); break;

        case 'P': my_opt.cmd = drv_cmd(P); break;
    
        default:

            printf("\n          输入命令错误\n");

            sleep(2);

            my_opt.cmd = drv_cmd(P);

            break;

    }
}

//=============================================================//



static void drv_cmd_H(struct class_node * class)
{
    drv_show_help(class);

    fgets(ms_buf, SIZE, stdin);

    drv_choose_h(class);
}

static void drv_cmd_T(struct class_node * class)
{
    system("clear");

    struct grades_node * node = drv_creat_grades_node(0, 0, 0, 0);

    struct intput_grages_list * list = drv_intput_list_init(0);

    strcpy(list->data, grahead2);

    while(1)
    {
        if(drv_get_grades(class, node, list)) break;        
    }
    
    drv_close_list1(node); 

    drv_close_list2(list);
}


static void drv_cmd_P(struct class_node * class)
{
    class->node = gnode.node;

    if(drv_show_grades(class))
    {
        printf("\n\n\n            返回：H  录入成绩：T  按学号查看：S  修改成绩：X\n\n            请输入命令=");

        fgets(ms_buf, SIZE, stdin);

        drv_choose_p(class);
    }

}

static void drv_cmd_X(struct class_node * class)
{
    system("clear");

    struct grades_node * node = drv_creat_grades_node(0, 0, 0, 0);

    struct intput_grages_list * list = drv_intput_list_init(0);

    strcpy(list->data, grahead2);

    while(1)
    {
        if(drv_rev_grades(class, node, list)) break;        
    }
    
    drv_close_list1(node); 

    drv_close_list2(list);
}

static void drv_cmd_S(struct class_node * class)
{
    class->node = inode.node;

    if(drv_show_grades(class))
    {
        printf("\n\n\n            返回：H  录入成绩：T  按成绩查看：P  修改成绩：X\n\n            请输入命令=");

        fgets(ms_buf, SIZE, stdin);

        drv_choose_s(class);
    }

    
}



static void drv_cmd_Q(struct class_node * class)
{
    drv_end(class);

    system("clear");

    class->state = 0;
}



static int drv_end(struct class_node * class)
{
    struct grades_node * p = inode.node;

    while(p->id) 
    {
        free(p);

        p = p->node;
    } 

    p = gnode.node;

    while(p->id) 
    {
        free(p);

        p = p->node;
    } 

    free(class);

    return 0;
}


static struct class_node * drv_init(void)
{
    struct class_node * myclass = (struct class_node *)malloc(sizeof(struct class_node));

    if(myclass == NULL)
    {
        printf("myclass malloc failure\n");

        return NULL;
    }

    myclass->num = 0;

    myclass->state = 1;

    myclass->buf = show_mian;

    inode.id = 0;

    inode.node = &inode;

    gnode.id = 0;

    gnode.node = &gnode;

    myclass->node = &inode;

    return myclass;
    
}



void drv_opt_init(void)
{
    my_opt.init = drv_init;

    my_opt.cmd = drv_cmd(H);
}


