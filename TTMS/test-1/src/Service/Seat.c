/*
* Copyright(C), 2007-2008, XUPT Univ.	
* 用例编号：TTMS_UC_02 
* File name: Seat.c		  
* Description : 设置座位用例业务逻辑层	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015年4月22日	
*/
#include<stdio.h>
#include <stdlib.h>
#include "../Common/list.h"
#include "Seat.h"

static const char SEAT_DATA_FILE[] = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";
/*
函数功能：用于添加一个新座位数据。
参数说明：data为seat_t类型指针，表示需要添加的座位数据结点。
返 回 值：整型，表示是否成功添加了座位的标志。
*/
int Seat_Srv_Add(const seat_t *data){
						// 请补充完整
	Seat_Perst_Insert(*data);
	return 0;
}

/*
函数功能：批量添加座位数据。
参数说明：list为seat_list_t类型指针，表示需要添加的批量座位数据形成的链表。
返 回 值：整型，表示是否成功添加了批量座位的标志。
*/
int Seat_Srv_AddBatch(seat_list_t list){
	// 请补充完整
       return 0;
}

/*
函数功能：用于修改一个座位数据。
参数说明：data为seat_t类型指针，表示需要修改的座位数据结点。
返 回 值：整型，表示是否成功修改了座位的标志。
*/


int Seat_Srv_Del(const seat_t *data)
{
	Seat_Perst_Del(*data);
	return 0;
}
int Seat_Srv_Modify(const seat_t *data){
	
	Seat_Perst_Update(*data);
        //Seat_Perst_Del(*data);
	return 0;
}

/*
函数功能：根据座位ID删除一个座位。
参数说明：ID为整型，表示需要删除的座位数据结点。
返 回 值：整型，表示是否成功删除了座位的标志。
*/
int Seat_Srv_DeleteByID(int ID){
	// 请补充完整
       return 1;
}

/*
函数功能：根据座位ID获取座位数据。
参数说明：第一个参数ID为整型，表示座位ID，第二个参数buf为seat_t指针，指向待获取的座位数据结点。
返 回 值：整型，表示是否成功获取了座位的标志。
*/
int Seat_Srv_FetchByID(int ID, seat_t *buf){
	// 请补充完整
       return 0;
}

/*
函数功能：根据演出厅ID删除所有座位。
参数说明：roomID为整型，表示需要删除所有座位的演出厅ID。
返 回 值：整型，表示是否成功删除了演出厅所有座位的标志。
*/
inline int Seat_Srv_DeleteAllByRoomID(int roomID)
{
	
	if(rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE)<0)//靠靠靠,靠� 0 ,靠靠 -1
	{
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;  

	fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb"); 

	if (NULL == fpSour )
	{
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SEAT_DATA_FILE, "wb");   

	if ( NULL == fpTarg ) 
	{
		printf("Cannot open file %s!\n", SEAT_DATA_TEMP_FILE);
		return 0;
	}

	seat_t buf;  

	int found = 0;
	while (!feof(fpSour)) 
	{
		if (fread(&buf, sizeof(seat_t), 1, fpSour)) //靠靠靠�,靠 size 靠� 靠靠count 靠,縡psour靠
		{
			if (roomID == buf.id) 
			{
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(seat_t), 1, fpTarg);
		}

	}

	fclose(fpTarg);
	fclose(fpSour);

	remove(SEAT_DATA_TEMP_FILE);

	return found;

}

/*
函数功能：根据给定演出厅的行、列数初始化演出厅的所有座位数据，并将每个座位结点按行插入座位链表。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功初始化了演出厅的所有座位。
*/
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID)
{
	Seat_Perst_SelectByRoomID(list,roomID);
        return 0;

}

/*
函数功能：根据演出厅ID获得该演出厅的有效座位。
参数说明：第一个参数list为seat_list_t类型，表示获取到的有效座位链表头指针，第二个参数roomID为整型，表示需要提取有效座位的演出厅ID。
返 回 值：整型，表示演出厅的有效座位个数。
*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
       // 请补充完整
       return 0;
}

/*
函数功能：根据给定演出厅的行、列数初始化演出厅的所有座位数据，并将每个座位结点按行插入座位链表。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功初始化了演出厅的所有座位。
*/
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,int colsCount)
{
	FILE *fp = NULL;
	fp = fopen(SEAT_DATA_FILE,"ab");
	if(fp == NULL)
	{
		printf( "the file not in here\n");
		return 0;
	}
//	fp = fseek(fp,-1L,SEEK_END);
	int n = 1;
	seat_list_t temp;
	List_Init(list,seat_node_t);
	for(int i = 0;i < rowsCount;i++)		// 请补充完整
	{
		for(int j = 0;j < colsCount;j++)
		{
			temp = (seat_list_t)malloc(sizeof(seat_node_t));
			temp->data.id = n;
			temp->data.roomID = roomID;
			temp->data.row = i;
			temp->data.column = j;
			temp->data.status = 1;
			List_AddTail(list,temp);
			printf( "n =   %d\n",n);
			if(fwrite(temp,sizeof(seat_node_t),1,fp))     n++;

		}
	}
/*	fseek(fp,-sizeof(seat_node_t),SEEK_CUR);

	fread(temp,sizeof(seat_node_t),1,fp);
	printf( "n  =  %d     stu =  %d      ",temp->data.id,temp->data.status);*/
	fclose(fp);
        return 0;
}

/*
函数功能：对座位链表list按座位行号、列号进行排序。
参数说明：list为seat_list_t类型，表示待排序座位链表头指针。
返 回 值：无。
*/
void Seat_Srv_SortSeatList(seat_list_t list) {
       // 请补充完整
}

/*
函数功能：将一个座位结点加入到已排序的座位链表中。
参数说明：第一个参数list为seat_list_t类型，表示待插入结点的座位链表头指针，第二个参数node为seat_node_t指针，表示需要插入的座位数据结点。
返 回 值：无。
*/
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
       // 请补充完整
}

/*
函数功能：根据座位的行、列号获取座位数据。
参数说明：第一个参数list为seat_list_t类型，表示座位链表头指针，
         第二个参数row为整型，表示待获取座位的行号，第三个参数column为整型，表示待获取座位的列号。
返 回 值：为seat_node_t指针，表示获取到的座位数据。
*/
seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
       // 请补充完整
       return NULL;
}

/*
函数功能：根据座位ID在链表中获取座位数据。
参数说明：第一个参数list为seat_list_t类型，指向座位数据链表，第二个参数ID为整型，表示座位ID。
返 回 值：seat_node_t类型，表示获取的座位数据。
*/
seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {
       // 请补充完整
       return NULL;
}
