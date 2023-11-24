
#if 0
//实验1：链表节点插入实验
#include "list.h"

struct xLIST 				List_test;

struct xLIST_ITEM		xLIST_ITEM1;
struct xLIST_ITEM		xLIST_ITEM2;
struct xLIST_ITEM		xLIST_ITEM3;

int main()
{
	//初始化根节点
	vListInitialise(&List_test);
	
	//初始化各节点
	vListInitialiseItem(&xLIST_ITEM1);
	vListInitialiseItem(&xLIST_ITEM2);
	vListInitialiseItem(&xLIST_ITEM3);
	
	//辅助排序值赋值
	xLIST_ITEM1.xItemValue = 1;
	xLIST_ITEM2.xItemValue = 2;
	xLIST_ITEM3.xItemValue = 3;
	
	//插入链表
	vListInsert(&List_test,&xLIST_ITEM2);
	vListInsert(&List_test,&xLIST_ITEM1);
	vListInsert(&List_test,&xLIST_ITEM3);
	
	while(1);

}

#elif 0
//实验2：实现任务的切换(非优先级切换)
#include "FreeRTOS.h" 
#include "list.h" 
#include "task.h"


//创建一个就绪列表和标志位 (全局变量)
portCHAR flag1; 
portCHAR flag2;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ]; 

//创建任务控制块和栈
TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB; 

//函数声明
void Task1_Entry(void* arg);
void Task2_Entry(void* arg);


int main(void) 
{
	
		//创建任务
		Task1_Handle = xTaskCreateStatic(	(TaskFunction_t) Task1_Entry, 						//任务入口	
																			"Task1",																		//任务名称
																			TASK1_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																			(StackType_t *) Task1Stack,									//栈顶指针
																			(TCB_t*) &Task1TCB );												//TCB
		//插入就绪列表
		vListInsert(&pxReadyTasksLists[1],(ListItem_t *)(&Task1TCB.xStateListItem));
	
		//创建任务
		Task2_Handle = xTaskCreateStatic(	(TaskFunction_t) Task2_Entry, 						//任务入口	
																			"Task2",																		//任务名称
																			TASK2_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																			(StackType_t *) Task2Stack,									//栈顶指针
																			(TCB_t*) &Task2TCB );												//TCB
		//插入就绪列表
		vListInsert(&pxReadyTasksLists[2],(ListItem_t *)(&Task2TCB.xStateListItem));
	
		//开启调度器
		vTaskStartScheduler();
		while(1);
	
}


/* 软件延时 */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}

//任务函数，要求：独立的函数，无限循环且不能返回
void Task1_Entry(void* arg)
{
	while(1){
	flag1 = 1;
	delay(100);
	flag1 = 0;
	delay(100);
	
	//切换任务
	taskYIELD();
	}
}

void Task2_Entry(void* arg)
{
	while(1){
	flag2 = 1;
	delay(100);
	flag2 = 0;
	delay(100);
	
	//切换任务
	taskYIELD();
	}
}
#elif 0
//实验三：实现RTOS中的延时：阻塞延时
#include "FreeRTOS.h" 
#include "list.h" 
#include "task.h"


//创建一个就绪列表和标志位 (全局变量)
portCHAR flag1; 
portCHAR flag2;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ]; 

//创建任务控制块和栈
TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB; 

//函数声明
void Task1_Entry(void* arg);
void Task2_Entry(void* arg);
void vTaskDelay( const TickType_t xTicksToDelay );

int main(void) 
{
	
		//创建任务
		Task1_Handle = xTaskCreateStatic(	(TaskFunction_t) Task1_Entry, 						//任务入口	
																			"Task1",																		//任务名称
																			TASK1_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																			(StackType_t *) Task1Stack,									//栈顶指针
																			(TCB_t*) &Task1TCB );												//TCB
		//插入就绪列表
		vListInsert(&pxReadyTasksLists[1],(ListItem_t *)(&Task1TCB.xStateListItem));
	
		//创建任务
		Task2_Handle = xTaskCreateStatic(	(TaskFunction_t) Task2_Entry, 						//任务入口	
																			"Task2",																		//任务名称
																			TASK2_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																			(StackType_t *) Task2Stack,									//栈顶指针
																			(TCB_t*) &Task2TCB );												//TCB
		//插入就绪列表
		vListInsert(&pxReadyTasksLists[2],(ListItem_t *)(&Task2TCB.xStateListItem));
	
		//开启调度器
		vTaskStartScheduler();
		while(1);
	
}


void Task1_Entry(void* arg)
{
	while(1){
	flag1 = 1;
	vTaskDelay(2);//此时设置的是1个数字对应的10ms
	flag1 = 0;
	vTaskDelay(2);
	
	}
} 

void Task2_Entry(void* arg)
{
	while(1){
	flag2 = 1;
	vTaskDelay(2);
	flag2 = 0;
	vTaskDelay(2);
	
	}
}


//创建空闲任务的栈和TCB
TCB_t IdleTaskTCB;
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE]; 


void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
                                    StackType_t **ppxIdleTaskStackBuffer, 
                                    uint32_t *pulIdleTaskStackSize )
{
		*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
		*ppxIdleTaskStackBuffer=IdleTaskStack; 
		*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

#elif 0
//实验四：实现多优先级切换任务
#include "FreeRTOS.h" 
#include "list.h" 
#include "task.h"


//创建一个就绪列表和标志位 (全局变量)
portCHAR flag1; 
portCHAR flag2;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ]; 

//创建任务控制块和栈
TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB; 

//函数声明
void Task1_Entry(void* arg);
void Task2_Entry(void* arg);
void vTaskDelay( const TickType_t xTicksToDelay );

int main(void) 
{
	
		//创建任务
		Task1_Handle = xTaskCreateStatic(	(TaskFunction_t) Task1_Entry, 						//任务入口	
																			"Task1",																		//任务名称
																			TASK1_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																				1,
																			(StackType_t *) Task1Stack,									//栈顶指针
																			(TCB_t*) &Task1TCB );												//TCB
		//插入就绪列表
		vListInsertEnd(&pxReadyTasksLists[1],(ListItem_t *)(&Task1TCB.xStateListItem));
	
		//创建任务
		Task2_Handle = xTaskCreateStatic(	(TaskFunction_t) Task2_Entry, 						//任务入口	
																			"Task2",																		//任务名称
																			TASK2_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																			2,
																			(StackType_t *) Task2Stack,									//栈顶指针
																			(TCB_t*) &Task2TCB );												//TCB
		//插入就绪列表
		vListInsertEnd(&pxReadyTasksLists[2],(ListItem_t *)(&Task2TCB.xStateListItem));
	
		//开启调度器
		vTaskStartScheduler();
		while(1);
	
}


void Task1_Entry(void* arg)
{
	while(1){
	flag1 = 1;
	vTaskDelay(2);//此时设置的是1个数字对应的10ms
	flag1 = 0;
	vTaskDelay(2);
	
	}
} 

void Task2_Entry(void* arg)
{
	while(1){
	flag2 = 1;
	vTaskDelay(2);
	flag2 = 0;
	vTaskDelay(2);
	
	}
}


//创建空闲任务的栈和TCB
TCB_t IdleTaskTCB;
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE]; 


void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
                                    StackType_t **ppxIdleTaskStackBuffer, 
                                    uint32_t *pulIdleTaskStackSize )
{
		*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
		*ppxIdleTaskStackBuffer=IdleTaskStack; 
		*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

#elif 1
//实验五：实现时间片，相同优先级的任务每个任务轮流享有CPU1tick的时间
#include "FreeRTOS.h" 
#include "list.h" 
#include "task.h"


//创建一个就绪列表和标志位 (全局变量)
portCHAR flag1; 
portCHAR flag2;
portCHAR flag3;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ]; 

//创建任务控制块和栈
TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    128
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    128
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB; 

TaskHandle_t Task3_Handle;
#define TASK3_STACK_SIZE                    128
StackType_t Task3Stack[TASK3_STACK_SIZE];
TCB_t Task3TCB; 


//函数声明
void Task1_Entry(void* arg);
void Task2_Entry(void* arg);
void Task3_Entry(void* arg);
void vTaskDelay( const TickType_t xTicksToDelay );

int main(void) 
{
	
		//创建任务
		Task1_Handle = xTaskCreateStatic(	(TaskFunction_t) Task1_Entry, 						//任务入口	
																			"Task1",																		//任务名称
																			TASK1_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																				2,
																			(StackType_t *) Task1Stack,									//栈顶指针
																			(TCB_t*) &Task1TCB );												//TCB
		//插入就绪列表
		//vListInsertEnd(&pxReadyTasksLists[1],(ListItem_t *)(&Task1TCB.xStateListItem));
	
		//创建任务
		Task2_Handle = xTaskCreateStatic(	(TaskFunction_t) Task2_Entry, 						//任务入口	
																			"Task2",																		//任务名称
																			TASK2_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																			2,
																			(StackType_t *) Task2Stack,									//栈顶指针
																			(TCB_t*) &Task2TCB );												//TCB
		//插入就绪列表
		//vListInsertEnd(&pxReadyTasksLists[2],(ListItem_t *)(&Task2TCB.xStateListItem));
	
		Task3_Handle = xTaskCreateStatic(	(TaskFunction_t) Task3_Entry, 						//任务入口	
																			"Task3",																		//任务名称
																			TASK3_STACK_SIZE,														//任务栈的大小
																			NULL,																				//任务形参
																			3,
																			(StackType_t *) Task3Stack,									//栈顶指针
																			(TCB_t*) &Task3TCB );												//TCB
		//开启调度器
		vTaskStartScheduler();
		while(1);
	
}

/* 软件延时 */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}



void Task1_Entry(void* arg)
{
	while(1){
	flag1 = 1;
	delay(100);
	flag1 = 0;
	delay(100);
	
	}
} 

void Task2_Entry(void* arg)
{
	while(1){
	flag2 = 1;
	delay(100);
	flag2 = 0;
	delay(100);
	
	}
}

void Task3_Entry(void* arg)
{
	while(1){
	flag3 = 1;
	vTaskDelay(1);  //时间片为1tick
	flag3 = 0;
	vTaskDelay(1);
	
	}
}



//创建空闲任务的栈和TCB
TCB_t IdleTaskTCB;
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE]; 


void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
                                    StackType_t **ppxIdleTaskStackBuffer, 
                                    uint32_t *pulIdleTaskStackSize )
{
		*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
		*ppxIdleTaskStackBuffer=IdleTaskStack; 
		*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

#endif 
