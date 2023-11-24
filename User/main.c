
#if 0
//ʵ��1������ڵ����ʵ��
#include "list.h"

struct xLIST 				List_test;

struct xLIST_ITEM		xLIST_ITEM1;
struct xLIST_ITEM		xLIST_ITEM2;
struct xLIST_ITEM		xLIST_ITEM3;

int main()
{
	//��ʼ�����ڵ�
	vListInitialise(&List_test);
	
	//��ʼ�����ڵ�
	vListInitialiseItem(&xLIST_ITEM1);
	vListInitialiseItem(&xLIST_ITEM2);
	vListInitialiseItem(&xLIST_ITEM3);
	
	//��������ֵ��ֵ
	xLIST_ITEM1.xItemValue = 1;
	xLIST_ITEM2.xItemValue = 2;
	xLIST_ITEM3.xItemValue = 3;
	
	//��������
	vListInsert(&List_test,&xLIST_ITEM2);
	vListInsert(&List_test,&xLIST_ITEM1);
	vListInsert(&List_test,&xLIST_ITEM3);
	
	while(1);

}

#elif 0
//ʵ��2��ʵ��������л�(�����ȼ��л�)
#include "FreeRTOS.h" 
#include "list.h" 
#include "task.h"


//����һ�������б�ͱ�־λ (ȫ�ֱ���)
portCHAR flag1; 
portCHAR flag2;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ]; 

//����������ƿ��ջ
TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB; 

//��������
void Task1_Entry(void* arg);
void Task2_Entry(void* arg);


int main(void) 
{
	
		//��������
		Task1_Handle = xTaskCreateStatic(	(TaskFunction_t) Task1_Entry, 						//�������	
																			"Task1",																		//��������
																			TASK1_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																			(StackType_t *) Task1Stack,									//ջ��ָ��
																			(TCB_t*) &Task1TCB );												//TCB
		//��������б�
		vListInsert(&pxReadyTasksLists[1],(ListItem_t *)(&Task1TCB.xStateListItem));
	
		//��������
		Task2_Handle = xTaskCreateStatic(	(TaskFunction_t) Task2_Entry, 						//�������	
																			"Task2",																		//��������
																			TASK2_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																			(StackType_t *) Task2Stack,									//ջ��ָ��
																			(TCB_t*) &Task2TCB );												//TCB
		//��������б�
		vListInsert(&pxReadyTasksLists[2],(ListItem_t *)(&Task2TCB.xStateListItem));
	
		//����������
		vTaskStartScheduler();
		while(1);
	
}


/* �����ʱ */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}

//��������Ҫ�󣺶����ĺ���������ѭ���Ҳ��ܷ���
void Task1_Entry(void* arg)
{
	while(1){
	flag1 = 1;
	delay(100);
	flag1 = 0;
	delay(100);
	
	//�л�����
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
	
	//�л�����
	taskYIELD();
	}
}
#elif 0
//ʵ������ʵ��RTOS�е���ʱ��������ʱ
#include "FreeRTOS.h" 
#include "list.h" 
#include "task.h"


//����һ�������б�ͱ�־λ (ȫ�ֱ���)
portCHAR flag1; 
portCHAR flag2;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ]; 

//����������ƿ��ջ
TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB; 

//��������
void Task1_Entry(void* arg);
void Task2_Entry(void* arg);
void vTaskDelay( const TickType_t xTicksToDelay );

int main(void) 
{
	
		//��������
		Task1_Handle = xTaskCreateStatic(	(TaskFunction_t) Task1_Entry, 						//�������	
																			"Task1",																		//��������
																			TASK1_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																			(StackType_t *) Task1Stack,									//ջ��ָ��
																			(TCB_t*) &Task1TCB );												//TCB
		//��������б�
		vListInsert(&pxReadyTasksLists[1],(ListItem_t *)(&Task1TCB.xStateListItem));
	
		//��������
		Task2_Handle = xTaskCreateStatic(	(TaskFunction_t) Task2_Entry, 						//�������	
																			"Task2",																		//��������
																			TASK2_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																			(StackType_t *) Task2Stack,									//ջ��ָ��
																			(TCB_t*) &Task2TCB );												//TCB
		//��������б�
		vListInsert(&pxReadyTasksLists[2],(ListItem_t *)(&Task2TCB.xStateListItem));
	
		//����������
		vTaskStartScheduler();
		while(1);
	
}


void Task1_Entry(void* arg)
{
	while(1){
	flag1 = 1;
	vTaskDelay(2);//��ʱ���õ���1�����ֶ�Ӧ��10ms
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


//�������������ջ��TCB
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
//ʵ���ģ�ʵ�ֶ����ȼ��л�����
#include "FreeRTOS.h" 
#include "list.h" 
#include "task.h"


//����һ�������б�ͱ�־λ (ȫ�ֱ���)
portCHAR flag1; 
portCHAR flag2;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ]; 

//����������ƿ��ջ
TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB; 

//��������
void Task1_Entry(void* arg);
void Task2_Entry(void* arg);
void vTaskDelay( const TickType_t xTicksToDelay );

int main(void) 
{
	
		//��������
		Task1_Handle = xTaskCreateStatic(	(TaskFunction_t) Task1_Entry, 						//�������	
																			"Task1",																		//��������
																			TASK1_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																				1,
																			(StackType_t *) Task1Stack,									//ջ��ָ��
																			(TCB_t*) &Task1TCB );												//TCB
		//��������б�
		vListInsertEnd(&pxReadyTasksLists[1],(ListItem_t *)(&Task1TCB.xStateListItem));
	
		//��������
		Task2_Handle = xTaskCreateStatic(	(TaskFunction_t) Task2_Entry, 						//�������	
																			"Task2",																		//��������
																			TASK2_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																			2,
																			(StackType_t *) Task2Stack,									//ջ��ָ��
																			(TCB_t*) &Task2TCB );												//TCB
		//��������б�
		vListInsertEnd(&pxReadyTasksLists[2],(ListItem_t *)(&Task2TCB.xStateListItem));
	
		//����������
		vTaskStartScheduler();
		while(1);
	
}


void Task1_Entry(void* arg)
{
	while(1){
	flag1 = 1;
	vTaskDelay(2);//��ʱ���õ���1�����ֶ�Ӧ��10ms
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


//�������������ջ��TCB
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
//ʵ���壺ʵ��ʱ��Ƭ����ͬ���ȼ�������ÿ��������������CPU1tick��ʱ��
#include "FreeRTOS.h" 
#include "list.h" 
#include "task.h"


//����һ�������б�ͱ�־λ (ȫ�ֱ���)
portCHAR flag1; 
portCHAR flag2;
portCHAR flag3;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ]; 

//����������ƿ��ջ
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


//��������
void Task1_Entry(void* arg);
void Task2_Entry(void* arg);
void Task3_Entry(void* arg);
void vTaskDelay( const TickType_t xTicksToDelay );

int main(void) 
{
	
		//��������
		Task1_Handle = xTaskCreateStatic(	(TaskFunction_t) Task1_Entry, 						//�������	
																			"Task1",																		//��������
																			TASK1_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																				2,
																			(StackType_t *) Task1Stack,									//ջ��ָ��
																			(TCB_t*) &Task1TCB );												//TCB
		//��������б�
		//vListInsertEnd(&pxReadyTasksLists[1],(ListItem_t *)(&Task1TCB.xStateListItem));
	
		//��������
		Task2_Handle = xTaskCreateStatic(	(TaskFunction_t) Task2_Entry, 						//�������	
																			"Task2",																		//��������
																			TASK2_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																			2,
																			(StackType_t *) Task2Stack,									//ջ��ָ��
																			(TCB_t*) &Task2TCB );												//TCB
		//��������б�
		//vListInsertEnd(&pxReadyTasksLists[2],(ListItem_t *)(&Task2TCB.xStateListItem));
	
		Task3_Handle = xTaskCreateStatic(	(TaskFunction_t) Task3_Entry, 						//�������	
																			"Task3",																		//��������
																			TASK3_STACK_SIZE,														//����ջ�Ĵ�С
																			NULL,																				//�����β�
																			3,
																			(StackType_t *) Task3Stack,									//ջ��ָ��
																			(TCB_t*) &Task3TCB );												//TCB
		//����������
		vTaskStartScheduler();
		while(1);
	
}

/* �����ʱ */
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
	vTaskDelay(1);  //ʱ��ƬΪ1tick
	flag3 = 0;
	vTaskDelay(1);
	
	}
}



//�������������ջ��TCB
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
