#include "veg_info.h"

/*
int main(void)
{

}
*/

















int CreatList(SPECIES_NODE**phead)
{
    SPECIES_NODE *hd=NULL,*pSpeciesNode,mid1;
    BASIC_NODE *pBasicNode,mid2;
    PLANT_NODE *pPlantNode,mid3;
    FILE *pFile;
    int find;
    int re=0;

    if((pFile=fopen(fp_species_info_filename,"rb"))==NULL)
    {
        printf("蔬菜种类信息数据文件打开失败。\n");
        return re;
    }
    printf("蔬菜种类信息数据文件打开成功。\n");

/*从数据文件中读取蔬菜种类信息数据，存入后进先出的主链表中。*/
    while(fread(&mid1,sizeof(SPECIES_NODE),1,pFile)==1)
    {
        pSpeciesNode=(SPECIES_NODE*)malloc(sizeof(SPECIES_NODE));
        *pSpeciesNode=mid1;
        pSpeciesNode->bnext=NULL;
        pSpeciesNode->next=hd;
        hd=pSpeciesNode;
    }
    fclose(pFile);
    if(hd==NULL)
    {
        printf("蔬菜种类信息数据文件加载失败。\n");
        return re;
    }
    printf("蔬菜种类信息数据文件加载成功。\n");
    *phead=hd;
    re+=2;
    

    if((pFile=fopen(fp_basic_info_filename,"rb"))==NULL)
    {
        printf("蔬菜基本信息数据文件打开失败。\n");
        return re;
    }
    printf("蔬菜基本信息数据文件打开成功。\n");
    re+=4;

/*从数据文件中读取蔬菜基本信息数据，存入后进先出的支链表中。*/
    while(fread(&mid2,sizeof(BASIC_NODE),1,pFile)==1)
    {
        pBasicNode=(BASIC_NODE*)malloc(sizeof(BASIC_NODE));
        *pBasicNode=mid2;
        pBasicNode->pnext=NULL;

        pSpeciesNode=hd;
        while(pSpeciesNode!=NULL &&
                ( (pSpeciesNode->spe_num) != (pBasicNode->spe_num) ) )
        {
            pSpeciesNode=pSpeciesNode->next;
        }


        if(pSpeciesNode!=NULL)
        {
            pBasicNode->next=pSpeciesNode->bnext;
            pSpeciesNode->bnext=pBasicNode;
        }
        else
        {
            free(pBasicNode);
        }
    }
    fclose(pFile);

    if((pFile=fopen(fp_plant_info_filename,"rb"))==NULL)
    {
        printf("蔬菜种植信息数据文件打开失败。\n");
        return re;
    }
    printf("蔬菜种植信息数据文件打开成功。\n");
    re+=8;

/*从数据文件中读取蔬菜种植信息数据，存入后进先出的支链表中。*/
    while(fread(&mid3,sizeof(PLANT_NODE),1,pFile)==1)
    {
        pPlantNode=(PLANT_NODE*)malloc(sizeof(PLANT_NODE));
        *pPlantNode=mid3;

        pSpeciesNode=hd;
        find=0;
        while(pSpeciesNode !=NULL && find==0)
        {
            pBasicNode=pSpeciesNode->bnext;
            while(pBasicNode!=NULL &&find==0)
            {
                if((pBasicNode->veg_num)==((pPlantNode->veg_num)))
                {
                    find=1;
                    break;
                }
                pBasicNode=pBasicNode->next;
            }
            pSpeciesNode=pSpeciesNode->next;
        }
        if(find)
        {
            pPlantNode->next=pBasicNode->pnext;
            pBasicNode->pnext=pPlantNode;
        }
        else
        {
            free(pPlantNode);
        }
    }
    fclose(pFile);

    return re;
}

BOOL InsertSpeciesNode(SPECIES_NODE **phead)
{
    char spe_name[50];                 //稍大的数组，用来寄存用户输入，判断输入是否规范
    int i;
    SPECIES_NODE* pSpeciesNode,*hd;
    hd=*phead;
    pSpeciesNode=(SPECIES_NODE*)malloc(sizeof(SPECIES_NODE));
    printf("请输入蔬菜的分类编码:\n");       //获取用户输入
    scanf("%c",pSpeciesNode->spe_num);
    printf("请输入蔬菜的分类名称：\n");
    scanf("%s",spe_name);
    if(strlen(spe_name)>8)              //对用户输入是否规范进行检测
    {
        printf("输入的蔬菜分类名称过长。请重试。\n");
        return FALSE;
    }
    for(i=0;i<8;i++)  {pSpeciesNode->spe_name[i]=spe_name[i];}
    pSpeciesNode->bnext=NULL;
    pSpeciesNode->next=hd;
    hd=pSpeciesNode;
    *phead=hd;
    return TRUE;
}

BOOL ModifySpeciesNode(SPECIES_NODE **phead)
{
    int i;
    SPECIES_NODE *pSpeciesNode=*phead;
    char spe_name[50];                //稍大的数组，用来寄存用户输入，判断输入是否规范
    printf("请输入所要修改的蔬菜的原分类名称：\n");
    scanf("%s",spe_name);
    while((strcmp(pSpeciesNode->spe_name,spe_name)!=0) && (pSpeciesNode!=NULL))  //查询所要修改的节点
    {
        pSpeciesNode=pSpeciesNode->next;
    }
    if(pSpeciesNode==NULL)            //判断是否查询到要修改的节点
    {
        printf("未查询到所要修改的蔬菜的分类名称，请重试。\n");
        return FALSE;
    }
    else
    {
        printf("请输入修改后的蔬菜的分类名称：\n");
        scanf("%s",spe_name);
    }
    if(strlen(spe_name)>8)              //对用户输入是否规范进行检测
    {
        printf("输入的蔬菜分类名称过长。请重试。\n");
        return FALSE;
    }
    else                              //进行修改
    {
        for(i=0;i<8;i++)  {pSpeciesNode->spe_name[i]=spe_name[i];}
        printf("修改成功。\n");
        return TRUE;
    }
}

BOOL DelectSpeciesNode(SPECIES_NODE **phead)
{
    SPECIES_NODE *pSpeciesNode=*phead,*front=pSpeciesNode;
    char spe_name[50];                            //稍大的数组，用来寄存用户输入，判断输入是否规范
    printf("请输入所要删除的蔬菜的分类名称：\n");
    scanf("%s",spe_name);
    if((strcmp(pSpeciesNode->spe_name,spe_name)==0)&&(pSpeciesNode!=NULL)) //判断链表的头节点是否为要删除的节点，若是，则改变头指针地址
    {
        *phead=pSpeciesNode->next;
        printf("删除成功。\n");
        free(pSpeciesNode);
        return TRUE;
    }
    while((strcmp(pSpeciesNode->spe_name,spe_name)==0)&&(pSpeciesNode!=NULL)) //寻找所要删除的蔬菜的分类节点
    {
        front=pSpeciesNode;
        pSpeciesNode=pSpeciesNode->next;
    }
    if(pSpeciesNode==NULL)  //判断是否查询到所要删除的节点
    {
        printf("未查询到所要删除的蔬菜的分类名称，请重试。\n");
        return FALSE;
    }
    else
    {
        front->next=pSpeciesNode->next;
        printf("删除成功。\n");
        free(pSpeciesNode);
        return TRUE;
    }
}

BOOL InsertBasicNode(SPECIES_NODE *hd,BASIC_NODE **phead)
{
    char veg_name[50],ingre[50];         //稍大的数组，用来寄存用户输入，判断输入是否规范
    int i;
    BASIC_NODE* pBasicNode,*mid;
    mid=*phead;
    pBasicNode=(BASIC_NODE*)malloc(sizeof(BASIC_NODE));
    pBasicNode->veg_num=(hd->bnext->veg_num)+1; //获取蔬菜编号：自增长（顺序增加）
    printf("请输入蔬菜名称：\n");
    scanf("%s",veg_name);                //获取用户输入，得到蔬菜名称
    if(strlen(veg_name)>20)              //对用户输入是否规范进行检测
    {
        printf("输入的蔬菜名称过长。请重试。\n");
        return FALSE;
    }
    for(i=0;i<20;i++)  {pBasicNode->veg_name[i]=veg_name[i];}
    pBasicNode->spe_num=hd->spe_num;   //从主链表中，找到该蔬菜的分类编码
    printf("请输入蔬菜的营养成分：\n");
    scanf("%s",ingre);
    if(strlen(ingre)>20)              //对用户输入是否规范进行检测
    {
        printf("输入的蔬菜营养成分过长。请重试。\n");
        return FALSE;
    }
    for(i=0;i<20;i++)  {pBasicNode->ingre[i]=ingre[i];}
    pBasicNode->pnext=NULL;
    pBasicNode->next=mid;
    mid=pBasicNode;
    *phead=mid;
    return TRUE;
}

BOOL ModifyBasicNode(BASIC_NODE **phead)
{
    int i;
    BASIC_NODE *pBasicNode=*phead;
    char veg_name[50],ingre[50];                //稍大的数组，用来寄存用户输入，判断输入是否规范
    printf("请输入所要修改的蔬菜基本信息的蔬菜名称：\n");
    scanf("%s",veg_name);
    while((strcmp(pBasicNode->veg_name,veg_name)!=0)&&(pBasicNode!=NULL)) //查询所要修改的节点
    {
        pBasicNode=pBasicNode->next;
    }
    if(pBasicNode==NULL)            //判断是否查询到要修改的节点
    {
        printf("未查询到所要修改的蔬菜的名称，请重试。\n");
        return FALSE;
    }
    printf("请选择所要修改的蔬菜基本信息的内容：\n（修改蔬菜名称请输入‘1’，修改蔬菜营养成分请输入‘2’）\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1:
            {
                printf("请输入修改后的蔬菜的名称：\n");
                scanf("%s",veg_name);
                if(strlen(veg_name)>20)              //对用户输入是否规范进行检测
                {
                    printf("输入的蔬菜分类名称过长。请重试。\n");
                    return FALSE;
                }
                else                              //进行修改
                {
                    for(i=0;i<20;i++)  {pBasicNode->veg_name[i]=veg_name[i];}
                    printf("修改成功。\n");
                    return TRUE;
                }
                break;
            }
        case 2:
            {
                printf("请输入修改后的蔬菜的营养成分：\n");
                scanf("%s",ingre);
                if(strlen(ingre)>20)              //对用户输入是否规范进行检测
                {
                    printf("输入的蔬菜营养成分字数过多。请重试。\n");
                    return FALSE;
                }
                else                              //进行修改
                {
                    for(i=0;i<20;i++)  {pBasicNode->ingre[i]=ingre[i];}
                    printf("修改成功。\n");
                    return TRUE;
                }
                break;            
            }
    }
}

BOOL DelectBasicNode(BASIC_NODE **phead)
{
    BASIC_NODE *pBasicNode=*phead,*front=pBasicNode;
    char veg_name[50];                            //稍大的数组，用来寄存用户输入，判断输入是否规范
    printf("请输入所要删除的蔬菜基本信息表节点的蔬菜名称：\n");
    scanf("%s",veg_name);
    if((strcmp(pBasicNode->veg_name,veg_name)!=0)&&(pBasicNode!=NULL)) //判断链表的头节点是否为要删除的节点，若是，则改变头指针地址
    {
        *phead=pBasicNode->next;
        printf("删除成功。\n");
        free(pBasicNode);
        return TRUE;
    }
    while((strcmp(pBasicNode->veg_name,veg_name)!=0)&&(pBasicNode!=NULL)) //寻找所要删除的蔬菜的分类节点
    {
        front=pBasicNode;
        pBasicNode=pBasicNode->next;
    }
    if(pBasicNode==NULL)  //判断是否查询到所要删除的节点
    {
        printf("未查询到所要删除的蔬菜的名称，请重试。\n");
        return FALSE;
    }
    else
    {
        front->next=pBasicNode->next;
        printf("删除成功。\n");
        free(pBasicNode);
        return TRUE;
    }
}

BOOL InsertPlantNode(BASIC_NODE *hd,PLANT_NODE **phead)
{
    char year[50];         //稍大的数组，用来寄存用户输入，判断输入是否规范
    int i,area;
    float weight;
    PLANT_NODE* pPlantNode,*mid;
    mid=*phead;
    pPlantNode=(PLANT_NODE*)malloc(sizeof(PLANT_NODE));
    pPlantNode->plant_num=((*phead)->plant_num)+1; //获取种植编号：自增长（顺序增加）
    pPlantNode->veg_num=hd->veg_num;   //从主链表中，找到该蔬菜的蔬菜编号
    printf("请输入该蔬菜的种植面积：\n");
    scanf("%d",&(pPlantNode->area));                //获取用户输入，得到蔬菜的种植面积
    printf("请输入该蔬菜的收获重量：\n");
    scanf("%f",&(pPlantNode->weight));              //获取用户输入，得到蔬菜的收获重量
    printf("请输入该蔬菜的种植年份: \n");
    scanf("%s",year);
    if(strlen(year)>5)              //对用户输入是否规范进行检测
    {
        printf("输入的蔬菜种植年份字数过多。请重试。\n");
        return FALSE;
    }
    for(i=0;i<5;i++)  {pPlantNode->year[i]=year[i];}
    pPlantNode->next=mid;
    mid=pPlantNode;
    *phead=mid;
    return TRUE;
}

BOOL ModifyPlantNode(PLANT_NODE **phead)
{
    int i;
    PLANT_NODE *pPlantNode=*phead;
    char year[50];                //稍大的数组，用来寄存用户输入，判断输入是否规范
    printf("请输入所要修改的蔬菜种植信息的种植年份：\n");
    scanf("%s",year);
    while((strcmp(pPlantNode->year,year)!=0)&&(pPlantNode!=NULL))  //查询所要修改的节点
    {
        pPlantNode=pPlantNode->next;
    }
    if(pPlantNode==NULL)            //判断是否查询到要修改的节点
    {
        printf("未查询到所要修改的种植年份，请重试。\n");
        return FALSE;
    }
    printf("请选择所要修改的蔬菜种植信息的内容：\n（修改种植面积请输入‘1’，修改收获重量请输入‘2’，修改种植年份请输入‘3’）\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1:
            {
                printf("请输入修改后的种植面积：\n");
                scanf("%d",&(pPlantNode->area));
                printf("修改成功。\n");
                return TRUE;
                break;
            }
        case 2:
            {
                printf("请输入修改后的收获重量：\n");
                scanf("%f",&(pPlantNode->weight));
                printf("修改成功。\n");
                return TRUE;
                break;            
            }
        case 3:
            {
                printf("请输入修改后的蔬菜的种植年份：\n");
                scanf("%s",year);
                if(strlen(year)>5)              //对用户输入是否规范进行检测
                {
                    printf("输入的蔬菜种植年份字数过多。请重试。\n");
                    return FALSE;
                }
                else                              //进行修改
                {
                    for(i=0;i<5;i++)  {pPlantNode->year[i]=year[i];}
                    printf("修改成功。\n");
                    return TRUE;
                }
                break;       
            }
    }
}

BOOL DelectPlantNode(PLANT_NODE **phead)
{
    PLANT_NODE *pPlantNode=*phead,*front=pPlantNode;
    char year[50];                            //稍大的数组，用来寄存用户输入，判断输入是否规范
    printf("请输入所要删除的蔬菜种植信息表节点的种植年份：\n");
    scanf("%s",year);
    if((strcmp(pPlantNode->year,year)!=0)&&(pPlantNode!=NULL)) //判断链表的头节点是否为要删除的节点，若是，则改变头指针地址
    {
        *phead=pPlantNode->next;
        printf("删除成功。\n");
        free(pPlantNode);
        return TRUE;
    }
    while((strcmp(pPlantNode->year,year)!=0)&&(pPlantNode!=NULL)) //寻找所要删除的蔬菜的分类节点
    {
        front=pPlantNode;
        pPlantNode=pPlantNode->next;
    }
    if(pPlantNode==NULL)  //判断是否查询到所要删除的节点
    {
        printf("未查询到所要删除的种植年份，请重试。\n");
        return FALSE;
    }
    else
    {
        front->next=pPlantNode->next;
        printf("删除成功。\n");
        free(pPlantNode);
        return TRUE;
    }
}

BOOL QuerySpecies(SPECIES_NODE *hd)
{
    char spe_num;
    printf("请输入所要查询的蔬菜种类的分类编码：\n");
    scanf("%c",&spe_num);
    while(hd->spe_num !=spe_num)
    {
        hd=hd->next;
    }
    if(hd!=NULL)
    {
        printf("蔬菜种类信息表\n");
        printf("分类编码：%c\n分类名称：%s\n\n",spe_num,hd->spe_name);
        printf("%s:",hd->spe_name);
        BASIC_NODE *pBasicNode=hd->bnext;
        while(pBasicNode!=NULL)
        {
            printf("%s.",pBasicNode->veg_name);
        }
        printf("等等\n");
        return TRUE;
    }
    else
    {
        printf("未查询到该分类编码。请重试。\n");
        return FALSE; 
    }
}

BOOL QueryBasicName(SPECIES_NODE *hd)
{
    int i,t,count=0,find=0;
    char veg_name[20];
    BASIC_NODE *pBasicNode=NULL;

    printf("从全部种类中查询请输入‘1’，从某一种类中查询请输入'2':\n");
    scanf("%d",i);
    switch(i)         /*选择查询范围*/
    {
        case 1:
        {
           printf("请输入蔬菜名称关键字/词：\n");
           scanf("%s",veg_name);
           while(hd!=NULL)
           {
               pBasicNode=hd->bnext;
               while(pBasicNode!=NULL)
               {
                    i=0;
                    while((veg_name[0] != pBasicNode->veg_name[i])&&i<19)  i++;
                    for(t=0;t<strlen(veg_name);t++)
                    {
                        if(veg_name[t]==pBasicNode->veg_name[i])
                        {
                            find=1;
                            i++;
                        }
                        else
                        {
                            find=0;
                            break;
                        }
                    }
                    if(find)
                    {
                        printf("蔬菜基本信息表\n");
                        printf("蔬菜编号：%d\n蔬菜名称:%s\n分类编码：%c\n营养成分:%s\n\n",
                        pBasicNode->veg_num,pBasicNode->veg_name,
                        pBasicNode->spe_num,pBasicNode->ingre);
                        find=0;
                        count++;
                    }
               }
               hd=hd->next;
           }
           if(!count) {printf("未查询到含有“%s”字样的蔬菜。\n",veg_name);}
           return TRUE;
           break;
        }
        case 2:
        {
            char spe_name[8];
            printf("请输入所要查询的蔬菜种类的分类名称：\n");
            scanf("%s",spe_name);
            while((strcmp(hd->spe_name,spe_name)!=0)&& (hd!=NULL))  //查询所要修改的节点
            {
                hd=hd->next;
            }
            if(hd==NULL)            //判断是否查询到要修改的节点
            {
                printf("未查询到输入的蔬菜的分类名称，请重试。\n");
                return FALSE;
            }
            else
            {
                printf("请输入蔬菜名称关键字/词：");
                scanf("%s",veg_name);
                pBasicNode=hd->bnext;
               while(pBasicNode!=NULL)
               {
                    i=0;
                    while((veg_name[0] != pBasicNode->veg_name[i])&&i<19)  i++;
                    for(t=0;t<strlen(veg_name);t++)
                    {
                        if(veg_name[t]==pBasicNode->veg_name[i])
                        {
                            find=1;
                            i++;
                        }
                        else
                        {
                            find=0;
                            break;
                        }
                    }
                    if(find)
                    {
                        printf("蔬菜基本信息表\n");
                        printf("蔬菜编号：%d\n蔬菜名称:%s\n分类编码：%c\n营养成分:%s\n\n",
                        pBasicNode->veg_num,pBasicNode->veg_name,
                        pBasicNode->spe_num,pBasicNode->ingre);
                        find=0;
                        count++;
                    }
               }
               if(!count) {printf("未查询到含有“%s”字样的蔬菜。\n",veg_name);}
                return TRUE;
                break;
            }
        }
        
    }
}

BOOL QueryBasicIngre(SPECIES_NODE *hd)
{
    int i,t,count=0,find=0;  //i,t,无实际意义。count记录查询到的信息个数。find表示是否查询到信息。
    char spe_num;
    char ingre[20];
    BASIC_NODE *pBasicNode=NULL;
    printf("请输入所要查询的蔬菜的分类码：\n");
    scanf("%c",&spe_num);
    while((spe_num!=hd->spe_num) && (hd!=NULL))
    {
        hd=hd->next;
    }
    if(hd)
    {
        printf("请输入查询的蔬菜的营养成分关键字/词：\n");
        scanf("%s",ingre);
        pBasicNode=hd->bnext;
        while(pBasicNode!=NULL)
        {
            i=0;
            while((ingre[0] != pBasicNode->ingre[i])&&i<19)  i++;
            for(t=0;t<strlen(ingre);t++)
            {
                if(ingre[t]==pBasicNode->ingre[i])
                {
                    find=1;
                    i++;
                }
                else
                {
                    find=0;
                    break;
                }
            }
            if(find)
            {
                printf("蔬菜基本信息表\n");
                printf("蔬菜编号：%d\n蔬菜名称:%s\n分类编码：%c\n营养成分:%s\n\n",
                pBasicNode->veg_num,pBasicNode->veg_name,
                pBasicNode->spe_num,pBasicNode->ingre);
                find=0;
                count++;
            }
        }
        if(!count) {printf("该种类蔬菜的营养成分中未查询到含有“%s”字样。\n",ingre);}
        return TRUE;
    }
    else
    {
        printf("未查询到该分类码对应的蔬菜种类。\n");
        return TRUE;
    }
}

BOOL QueryPlantYear(SPECIES_NODE *hd)
{
    int i,t,count=0,find=0;
    char veg_name[20];
    char year[5];
    BASIC_NODE *pBasicNode=NULL;
    PLANT_NODE *pPlantNode=NULL;
    printf("请输入蔬菜名称关键字/词：\n");
    scanf("%s",veg_name);
    printf("请输入蔬菜的种植年份：\n");
    scanf("%s",year);
    while(hd!=NULL)
    {
        pBasicNode=hd->bnext;
        while(pBasicNode!=NULL)
        {
            i=0;
            while((veg_name[0] != pBasicNode->veg_name[i])&&i<19)  i++;
            for(t=0;t<strlen(veg_name);t++)
            {
                if(veg_name[t]==pBasicNode->veg_name[i])
                {
                    find=1;
                    i++;
                }
                else
                {
                    find=0;
                    break;
                }
            }
            if(find)
            {
                pPlantNode=pBasicNode->pnext;
                while((strcmp(year,pPlantNode->year)!=0)&&(pPlantNode!=NULL))
                {
                    pPlantNode=pPlantNode->next;
                }
                if(pPlantNode!=NULL)
                {
                    printf("蔬菜全部信息表\n");
                    printf("分类编码：%c\n分类名称：%s\n",hd->spe_num,hd->spe_name);
                    printf("蔬菜编号：%d\n蔬菜名称:%s\n营养成分:%s\n",
                        pBasicNode->veg_num,pBasicNode->veg_name,pBasicNode->ingre);
                    printf("种植编号：%d\n种植面积:%d\n收获重量：%f\n种植年份:%s\n\n",
                        pPlantNode->plant_num,pPlantNode->area,
                        pPlantNode->weight,pPlantNode->year);
                    find=0;
                    count++;
                }
            }
            pBasicNode=pBasicNode->next;
        }
        hd=hd->next;
    }
    if(!count) {printf("未查询到符合要求的蔬菜信息。\n");}
    return TRUE;
}

BOOL QueryPlantName(SPECIES_NODE *hd)
{
    BASIC_NODE *pBasicNode=NULL;
    PLANT_NODE *pPlantNode=NULL;
    char veg_name[20];
    int find=0;
    printf("请输入要查询的蔬菜名称（完整名称）：\n");
    scanf("%s",veg_name);
    while(hd!=NULL)
    {
        pBasicNode=hd->bnext;
        while((strcmp(pBasicNode->veg_name,veg_name)!=0)&&pBasicNode!=NULL)
        {
            pBasicNode=pBasicNode->next;
        }
        if(pBasicNode!=NULL)
        {
            find++;
            pPlantNode=pBasicNode->pnext;
            while(pPlantNode!=NULL)
            {
                printf("编号:%d\n蔬菜编号:%d\n种植面积:%d\n收获重量:%f\n种植年份:%s\n\n",
                    pPlantNode->plant_num,pPlantNode->veg_num,pPlantNode->area,
                    pPlantNode->weight,pPlantNode->year);
                pPlantNode=pPlantNode->next;
            }
            break;
        }
        hd=hd->next;
    }
    if(!find)
    {
        printf("未查询到该蔬菜的信息。\n");
    }
    return TRUE;
}

