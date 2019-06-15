/*
* Copyright(C), 2007-2008, XUPT Univ.	
* ������ţ�TTMS_UC_02 
* File name: Seat.c		  
* Description : ������λ����ҵ���߼���	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015��4��22��	
*/
#include<stdio.h>
#include <stdlib.h>
#include "../Common/list.h"
#include "Seat.h"

static const char SEAT_DATA_FILE[] = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";
/*
�������ܣ���������һ������λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ���ӵ���λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��
*/
int Seat_Srv_Add(const seat_t *data){
						// �벹������
	Seat_Perst_Insert(*data);
	return 0;
}

/*
�������ܣ�����������λ���ݡ�
����˵����listΪseat_list_t����ָ�룬��ʾ��Ҫ���ӵ�������λ�����γɵ�������
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�������������λ�ı�־��
*/
int Seat_Srv_AddBatch(seat_list_t list){
	// �벹������
       return 0;
}

/*
�������ܣ������޸�һ����λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ�޸ĵ���λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��޸�����λ�ı�־��
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
�������ܣ�������λIDɾ��һ����λ��
����˵����IDΪ���ͣ���ʾ��Ҫɾ������λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��
*/
int Seat_Srv_DeleteByID(int ID){
	// �벹������
       return 1;
}

/*
�������ܣ�������λID��ȡ��λ���ݡ�
����˵������һ������IDΪ���ͣ���ʾ��λID���ڶ�������bufΪseat_tָ�룬ָ�����ȡ����λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ȡ����λ�ı�־��
*/
int Seat_Srv_FetchByID(int ID, seat_t *buf){
	// �벹������
       return 0;
}

/*
�������ܣ������ݳ���IDɾ��������λ��
����˵����roomIDΪ���ͣ���ʾ��Ҫɾ��������λ���ݳ���ID��
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ�����ݳ���������λ�ı�־��
*/
inline int Seat_Srv_DeleteAllByRoomID(int roomID)
{
	
	if(rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE)<0)//������,��� 0 ,���� -1
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
		if (fread(&buf, sizeof(seat_t), 1, fpSour)) //�������,�� size ��� ����count ��,�fpsour��
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
�������ܣ����ݸ����ݳ������С�������ʼ���ݳ�����������λ���ݣ�����ÿ����λ��㰴�в�����λ������
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ʼ�����ݳ�����������λ��
*/
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID)
{
	Seat_Perst_SelectByRoomID(list,roomID);
        return 0;

}

/*
�������ܣ������ݳ���ID��ø��ݳ�������Ч��λ��
����˵������һ������listΪseat_list_t���ͣ���ʾ��ȡ������Ч��λ����ͷָ�룬�ڶ�������roomIDΪ���ͣ���ʾ��Ҫ��ȡ��Ч��λ���ݳ���ID��
�� �� ֵ�����ͣ���ʾ�ݳ�������Ч��λ������
*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
       // �벹������
       return 0;
}

/*
�������ܣ����ݸ����ݳ������С�������ʼ���ݳ�����������λ���ݣ�����ÿ����λ��㰴�в�����λ������
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ʼ�����ݳ�����������λ��
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
	for(int i = 0;i < rowsCount;i++)		// �벹������
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
�������ܣ�����λ����list����λ�кš��кŽ�������
����˵����listΪseat_list_t���ͣ���ʾ��������λ����ͷָ�롣
�� �� ֵ���ޡ�
*/
void Seat_Srv_SortSeatList(seat_list_t list) {
       // �벹������
}

/*
�������ܣ���һ����λ�����뵽���������λ�����С�
����˵������һ������listΪseat_list_t���ͣ���ʾ�����������λ����ͷָ�룬�ڶ�������nodeΪseat_node_tָ�룬��ʾ��Ҫ�������λ���ݽ�㡣
�� �� ֵ���ޡ�
*/
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
       // �벹������
}

/*
�������ܣ�������λ���С��кŻ�ȡ��λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ���ʾ��λ����ͷָ�룬
         �ڶ�������rowΪ���ͣ���ʾ����ȡ��λ���кţ�����������columnΪ���ͣ���ʾ����ȡ��λ���кš�
�� �� ֵ��Ϊseat_node_tָ�룬��ʾ��ȡ������λ���ݡ�
*/
seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
       // �벹������
       return NULL;
}

/*
�������ܣ�������λID�������л�ȡ��λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ�ָ����λ�����������ڶ�������IDΪ���ͣ���ʾ��λID��
�� �� ֵ��seat_node_t���ͣ���ʾ��ȡ����λ���ݡ�
*/
seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {
       // �벹������
       return NULL;
}