#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h> 


/*菜农种植信息 链表结构节点*/
typedef struct plant_node
{
    int plant_num;              //种植编号
    int veg_num;                //蔬菜编号（同基本信息表中的蔬菜编号）
    int area;                   //种植面积
    float weight;               //收获重量
    char year[5];               //种植年份
    struct plant_node *next;    //指向下一节点的指针
}PLANT_NODE;

/*蔬菜基本信息 链表结构节点*/
typedef struct basic_node
{
    int veg_num;                //蔬菜编号
    char veg_name[20];          //蔬菜名称
    char spe_num;               //分类码
    char ingre[20];             //营养成分
    struct basic_node *next;    //指向下一节点的指针
    struct plant_node *pnext;   //指向菜农种植信息支链的指针
}BASIC_NODE;

/*蔬菜种类信息 链表结构节点（主链)*/
typedef struct species_node
{
    char spe_num;                    //分类编码
    char spe_name[8];               //分类名称
    struct species_node *next;      //指向下一节点的指针
    struct basic_node *bnext;       //指向蔬菜基本信息支链的指针
}SPECIES_NODE;


/*某年各类蔬菜收获总重量统计信息 链表结构节点*/
typedef struct one_year_node
{
    char spe_name[8];           //分类名称
    int total_area;             //某年某类蔬菜种植总面积
    int total_weight;           //某年某类蔬菜收获总重量
    struct one_year_node *next; //指向下一节点的指针；
}ONE_YEAR_NODE;

/*起止年份内各种蔬菜总重量统计信息  链表结构节点*/
typedef struct years_node
{
    char veg_name[20];          //蔬菜名称
    char spe_name[8];           //分类名称
    int total_area;             //某年某类蔬菜种植总面积
    int total_weight;           //某年某类蔬菜收获总重量
    struct years_node *next;    //指向下一节点的指针；
}YEARS_NODE;

/*某种类蔬菜已有数量统计信息  链表结构节点*/







char *fp_sys_name="菜农种植信息管理系统"; /*系统名称*/
char *fp_species_info_filename="species.dat";
char *fp_basic_info_filename="basic.dat";
char *fp_plant_info_filename="plant.dat";


int CreatList(SPECIES_NODE**phead);

BOOL InsertSpeciesNode(SPECIES_NODE **phead);
BOOL ModifySpeciesNode(SPECIES_NODE **phead);
BOOL DelectSpeciesNode(SPECIES_NODE **phead);
BOOL InsertBasicNode(SPECIES_NODE *hd,BASIC_NODE **phead);
BOOL ModifyBasicNode(BASIC_NODE **phead);
BOOL DelectBasicNode(BASIC_NODE **phead);
BOOL InsertPlantNode(BASIC_NODE *hd,PLANT_NODE **phead);
BOOL ModifyPlantNode(PLANT_NODE **phead);
BOOL DelectPlantNode(PLANT_NODE **phead);

BOOL QuerySpecies(SPECIES_NODE *hd);
BOOL QueryBasicName(SPECIES_NODE *hd);
BOOL QueryBasicIngre(SPECIES_NODE *hd);
BOOL QueryPlantYear(SPECIES_NODE *hd);
BOOL QueryPlantName(SPECIES_NODE *hd);
