#include<stdio.h>
#include"../Service/Sale.h"
#include"Sale_UI.h"
#include"../Common/list.h"
#include"../Service/Play.h"
#include"Ticket_UI.h"
#include"../Service/Account.h"
static const int SALE_PAGE_SIZE = 5;
static const int SALESANALYSIS_PAGE_SIZE = 5;
static const int TICKET_PAGE_SIZE = 10;

void Sale_UI_MgtEntry()
{
	if(gl_CurUser.type!=USR_CLERK||gl_CurUser.type!=USR_ANOMY){
        printf("you can't join in there!please input the [Enter]");
        getchar();
		return 0;
	}
	system("clear");
	char choice; 
	char name[20];
	int i;
	int play_id;
	play_node_t *pos;


	play_list_t list;
	play_list_t list_fetch;
	List_Init(list,play_node_t);
	List_Init(list_fetch,play_node_t);

	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SALE_PAGE_SIZE;
	Play_Srv_FetchAll(list_fetch);
	paging.totalRecords = Play_Srv_FetchAll(list);     //获取全部 剧目 信息
	Paging_Locate_FirstPage(list,paging);

	do
	{	printf(
				"\n======================================================================================\n");
		printf(
				"***************************** Projection Play List ***********************************\n");

		printf( "%5s %15s %5s %10s %3s %3s %10s %10s     %3s\n","ID","NAME","TYPE","AREA","RATING","DURATION","STARTDATA","ENDDATA","PRICE");
		printf( "--------------------------------------------------------------------------------------\n");

		Paging_ViewPage_ForEach(list,paging,play_node_t,pos,i)
		{
			printf( "%5d %15s %5d %10s %6d %6d %7d%3d%3d %4d%3d%3d     %4d\n",pos->data.id,pos->data.name,pos->data.type,pos->data.area,pos->data.rating,pos->data.duration,pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day,pos->data.price);	
		}
	

		printf( "----------------Total Recoeds: %2d---------------------------Page %2d   %2d   -----------\n",paging.totalRecords,Pageing_CurPage(paging),Pageing_TotalPages(paging));
	
		printf("**************************************************************************************\n");


		printf( "[C]show Schedule      [S]find play name          [P]rev       [N]ext         [R]eturn          \n");
		printf( "======================================================================================\n");
		printf("please input your choice : ");
		setbuf(stdin,NULL);
		scanf( "%c",&choice);
		getchar( );
		switch(choice)
		{
			case'c':
			case'C':
				printf( "please input play_id  :");
				scanf( "%d",&play_id);
				getchar( );
				Sale_UI_ShowScheduler(play_id);
				break;
			case's':
			case'S':
				printf( "please input the Play_ name :");
				setbuf(stdin,NULL);
				gets(name);
				system("clear");
				Play_Srv_FetchByName(list_fetch,name);
				Play_Srv_Print(list_fetch);
				break;

			case'n':
			case'N':
				if(!Pageing_IsLastPage(paging))
				{
					Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
				}
				break;
			case'P':
			case'p':
				if(!Pageing_IsFirstPage(paging))
				{
					Paging_Locate_OffsetPage(list, paging,-1, play_node_t);
				}
				break;
		}

	}while(choice != 'r' && choice != 'R');


}

void Sale_UI_ShowScheduler(int play_id)     //通过 剧目ID 显示 演出计划
{
	system("clear");
	int i;
	char choice;
	int schedule_id;
	
	schedule_list_t list;
	schedule_node_t *pos;
	Pagination_t paging;

	List_Init(list,schedule_node_t);

	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;

	paging.totalRecords = Schedule_Srv_FetchByPlay(list,play_id);    //获取   演出计划链表
	Paging_Locate_FirstPage(list,paging);

	do
	{
		printf( "===================================================================================================\n");
		printf( "*****************************************Schedule  List*******************************************\n");
		printf( "---------------------------------------------------------------------------------------------------\n");

		printf( " Schedule ID     Play ID      Stdio ID       fang ying ri qi     fang ying shi jian     seat_count\n");
		printf( "---------------------------------------------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(list,paging,schedule_node_t,pos,i)
		{
			printf( "         %3d         %3d          %3d             %3d.%2d.%2d           %3d:%3d:%3d               %d  \n",pos->data.id,pos->data.play_id,pos->data.studio_id,pos->data.date.year,pos->data.date.month,pos->data.date.day,pos->data.time.hour,pos->data.time.minute,pos->data.time.second,pos->data.seat_count);

		}

		printf( "-----totalRecords : %2d  -----------------------------Page %2d /%2d ------------------------------------\n",paging.totalRecords,Pageing_CurPage(paging),Pageing_TotalPages(paging));
		
		printf( "[T] Show Ticket     [N]ext     [P]rev    [R]eturn \n");
		printf( "Your choice : ");
		setbuf(stdin,NULL);

		scanf( "%c",&choice);
		getchar( );

		switch(choice)
		{
			case'T':
			case't':
				printf( "Please input Schedule ID:");
				setbuf(stdin,NULL);
				scanf( "%d",&schedule_id);
				getchar( );
				Sale_UI_ShowTicket(schedule_id);
				break;
			case'N':
			case'n':
				if (!Pageing_IsLastPage(paging))
				{
					Paging_Locate_OffsetPage(list, paging, 1, schedule_node_t);
				}
				break;
			case'p':
			case'P':
				if (!Pageing_IsFirstPage(paging))
				{
					Paging_Locate_OffsetPage(list, paging, -1, schedule_node_t);
				}
				break;
	
		}
		

	}while(choice == 'r' && choice == 'R');


}

int Sale_UI_ShowTicket(int schedule_id)
{
	seat_list_t list;
	List_Init(list,seat_node_t);
	int studio_ID;
	
	printf( "please input the studio ID :");
	scanf( "%d",&studio_ID);
	getchar( );
	int seat = Seat_Srv_FetchValidByRoomID(list,studio_ID);
	
	int i;
	char choice;
	ticket_node_t *pos;
	Pagination_t paging;

//	List_Init(list,seat_node_t);
	paging.offset = 0;
	paging.pageSize = TICKET_PAGE_SIZE;
	ticket_list_t list_ti;
	
	List_Init(list_ti,ticket_node_t);

	paging.totalRecords = Ticket_Srv_FetchBySchID_ticket(list_ti,schedule_id);
	Paging_Locate_FirstPage(list_ti,paging);
	do
	{
		system("clear");
	//	paging.totalRecords = Ticket_Srv_FetchBySchID(schedule_id,list_ti);
	//
	//
		printf( "====================================================================================\n");
		printf( "*****************************************Ticket*************************************\n");
		printf( "------------------------------------------------------------------------------------\n");
		printf( "Ticket ID          Scheuid ID         Seat ID       Price             Ticket Status\n");
		Paging_ViewPage_ForEach(list_ti,paging,ticket_t,pos,i)
		{
			printf("  %5d               %5d            %5d      %5d                     %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);
		}

		printf( "------Total Records  : %2d ------------------------Page %2d / %2d----------------------\n",paging.totalRecords,Pageing_CurPage(paging),Pageing_TotalPages(paging));

		printf( "[N]ext    [P]rev    [S]ale Ticket      [R]eturn    \n");
		printf( "Your choice:");
		scanf( "%c",&choice);
		getchar( );
		switch(choice)
		{
			case'n':
			case'N':
				if (!Pageing_IsLastPage(paging)) 
				{
					Paging_Locate_OffsetPage(list_ti, paging, 1, ticket_node_t);
				}

				break;
			case'p':
			case'P':
				if (!Pageing_IsFirstPage(paging)) 
				{
					Paging_Locate_OffsetPage(list_ti, paging, -1,ticket_node_t);
				}
				break;
			case'S':
			case's':
				Sale_UI_SellTicket(list_ti,list);
				//paging.totalRecords = Ticket_Srv_FetchBySchID(schedule_id,list_ti);
				break;

		}

	}while(choice != 'R'  && choice != 'r');
}


int Sale_UI_SellTicket(ticket_list_t list_t,seat_list_t list_s)
{

	seat_node_t * seat = NULL;
	setbuf(stdin,NULL);
	sale_t data_t;
	int row,col;
	while(1)
	{
		printf("please input the row you want to buy :");
		scanf( "%d",&row);
		printf("please input the col you want to buy :");
		scanf( "%d",&col);
		getchar( );
		seat = Seat_Srv_FindByRowCol(list_s,row,col);

		if(NULL == seat)
		{
			printf( "the seat is not exit!\n");
			continue;
		}

		if(seat->data.status == '@')
		{
			printf("the seat is broken!\n\n");
		}
		else if(seat->data.status == ' ')
		{
			printf("the seat is empty!!\n");
		}
		else
		{
			break;
		}
	}
	
		ticket_t buf;
		account_t buf_a;

		Ticket_Srv_FetchByID(seat->data.id,&buf);
		if(buf.status == 1)
		{
			printf( "the ticket is Sale!\n");
			return 0;
		}
		else
		{
			data_t.ticket_id = buf.id;

			buf.status = 1;
			Ticket_Srv_Modify(&buf);
			while(1)
			{
				printf( "please input the saler ID:");
				scanf( "%d",&data_t.user_id);
				if(!Account_Srv_FetchByID(data_t.user_id,&buf_a))
				{
					continue;
				}
				else
				{
					break;
				}
			}
			data_t.type = 1;
			data_t.value = buf.price;
			printf( "please input date:");
			scanf( "%d%d%d",&data_t.date.year,&data_t.date.month,&data_t.date.day);
			getchar( );
			printf( "please input time:");
			scanf( "%d%d%d",&data_t.time.hour,&data_t.time.minute,&data_t.time.second);
			getchar( );

			Sale_Srv_Add(&data_t);

			Ticket_UI_Print(buf);
		}
	
}



void Sale_UI_ReturnTicket()
{

    int id;
    ticket_t buf;
    sale_t refound;
    printf("请输入票的ID");
    scanf("%d",&id);
    if(Ticket_Srv_FetchByticketID(id,&buf)==1)   //查询票是否存在
    {
        if(buf.status == 1)//查询票是否售出
        {
	   buf.status = 0; 
           Ticket_Srv_Modify(&buf);   //调用Ticket_Srv_Modify函数修改票的状态
	   
	   refound.ticket_id = buf.id;
	   refound.value = buf.price;
	   refound.type = -1;  //SALE_REFOUND退票
           printf("please input date   ");
           scanf("%d%d%d",&refound.date.year,&refound.date.month,&refound.date.day);

	   printf( "please input time ");
	   scanf( "%d%d%d",&refound.time.hour,&refound.time.minute,&refound.time.second);
	   printf( "please input Salesperson ID:");
	   scanf( "%d",&refound.user_id);
           Sale_Srv_Add(&refound);
        }
        else
        {
            printf("该票还未被售出");
        }
    }

    else
    {
        printf("票务数据错误");
    }

}  
