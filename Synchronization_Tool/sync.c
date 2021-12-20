#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define POINTS 4
#define FIRST_STREET 1
#define SECOND_STREET 2

void *position1(void *arg);
void *position2(void *arg);
void *position3(void *arg);
void *position4(void *arg);
pthread_mutex_t control,worker = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t readyToDepart,Depart;

//used in thread
int waitCarNumAtPoint[POINTS+1];
int departTime[POINTS+1];
int canDepartCar[POINTS+1];

int curLine,passedCarNum,passingCar;
int tick;
int check;
typedef struct waitLinkList{
	int car;
	struct waitLinkList *rlink;
	struct waitLinkList *llink;
}LIST;

LIST *head = NULL;
LIST *tail = NULL;

//push on top
void push(int car);
//pop from tail
void pop(int car);
LIST* initNode(int car);

//test set 
/*int carNum = 10;
int carList[11] = {0,4,4,3,4,1,2,2,3,3,3};*/

//nomal set
int carNum;
int *carList;

//set passingCar, arrived Car 
void findArriveAndPassingCar(int tick); 
//print paassed, waiting vehicles 
void printState(int tick);

int checkBreakTime();
void giveChanceOfDepart();

int main(int argc, char *argv[])
{
	
	printf("number of vehicles :");
	scanf("%d",&carNum);
	
	carList = (int *)malloc(sizeof(int) * carNum+1);
	srand(time(NULL));
	printf("Start Point :");
	for(int i = 1; i <= carNum; i++)
	{
		carList[i] = rand() % 4 +1;
		printf("%d ",carList[i]);
	}
	printf("\n");
	
	curLine = 0;
	passedCarNum = 0;
	passingCar = 0;
	tick = 1;

	pthread_t tids[POINTS];
	pthread_create(&tids[0],NULL,position1,NULL);	
	pthread_create(&tids[1],NULL,position2,NULL);	
	pthread_create(&tids[2],NULL,position3,NULL);	
	pthread_create(&tids[3],NULL,position4,NULL);
	//ready = 0;
	pthread_barrier_init(&readyToDepart,NULL,2);
	pthread_barrier_init(&Depart,NULL,2);
	
	while(1)
	{
		pthread_mutex_lock(&control);
		if(tick <= carNum)
		{
			waitCarNumAtPoint[carList[tick]]++;
			push(carList[tick]);
		}

		findArriveAndPassingCar(tick);	
		//give the Chance of depart to threads
		giveChanceOfDepart();
		//wait until ready to depart	
		pthread_barrier_wait(&readyToDepart);
		pthread_barrier_wait(&Depart);
		if(passedCarNum == carNum-1 && checkBreakTime()) 
		{
			break;
		}	
		//after depart 
		printState(tick++);

		pthread_mutex_unlock(&control);
	}
		
	while(passedCarNum < carNum)
	{
		printState(tick++);
		findArriveAndPassingCar(tick);
	}
	printState(tick++);
	pthread_barrier_destroy(&readyToDepart);
	pthread_barrier_destroy(&Depart);
	
	for(int i = 1; i <= POINTS; i++) canDepartCar[i] = 1;		
	for(int i = 0; i< 4; i++)
	{
		pthread_join(tids[i],NULL);
	}
	for(int i = 1; i <= carNum; i++)
	{
		switch(carList[i]){
			case 1 : waitCarNumAtPoint[1]++; break;
			case 2 : waitCarNumAtPoint[2]++; break;
			case 3 : waitCarNumAtPoint[3]++; break;
			case 4 : waitCarNumAtPoint[4]++; break;
		}
	}
	
	printf("Number Of vehicles passed from each start point\n");
	
	printf("P1 : %d\n",waitCarNumAtPoint[1]);
	printf("P2 : %d\n",waitCarNumAtPoint[2]);
	printf("P3 : %d\n",waitCarNumAtPoint[3]);
	printf("P4 : %d\n",waitCarNumAtPoint[4]);
	printf("Total time : %d\n",tick-1);
	
	
}
int checkBreakTime()
{
	int check = 1;
	for(int i = 1; i <= POINTS; i++)
	{
		if(waitCarNumAtPoint[i] > 0) check = 0;
	}
	return check;
}

void giveChanceOfDepart()
{
	//when there is no car on the street 
	if(curLine == 0) 
	{
		//if there is POINTS at start point ,the cars can have chance to depart 
		for(int i = 1; i <= POINTS; i++)
		{
			(waitCarNumAtPoint[i] > 0) ? (canDepartCar[i] = 1) : (canDepartCar[i] = 0);
		}
	}//when there is car on street
	else{
		//find car on the ohere sied of start point 
		if(passingCar <= 2)
		{
			(waitCarNumAtPoint[curLine+2] > 0) ? (canDepartCar[curLine+2] = 1) : (canDepartCar[curLine] = 1);
		}
		else
		{
			(waitCarNumAtPoint[curLine] > 0) ? (canDepartCar[curLine] = 1) : (canDepartCar[curLine+2] = 1);
		}
	}
}
void *position1(void *arg)
{
	int myPoint = 1;

	while(1)
	{
		//wait until get Chance to depart
		while(canDepartCar[myPoint] == 0); 
		if(passedCarNum == carNum  && checkBreakTime()) break;
		
		pthread_mutex_lock(&worker);
		//Depart Car 
		if(canDepartCar[myPoint] == 1){
			pthread_barrier_wait(&readyToDepart);
			//Take away of other's depart Chance 
			for(int i = 1; i <= POINTS; i++) canDepartCar[i] = 0;
			
			if(curLine != SECOND_STREET && passingCar != myPoint)
			{
				departTime[myPoint] = tick;
				waitCarNumAtPoint[myPoint]--;
				pop(myPoint);
				curLine = FIRST_STREET;
			}	
			pthread_barrier_wait(&Depart);
		}
		pthread_mutex_unlock(&worker); 
	}
	
}
void *position2(void *arg)
{
	int myPoint = 2;

	while(1)
	{
		
		//wait until get Chance to depart
		while(canDepartCar[myPoint] == 0); 
		
		if(passedCarNum == carNum  && checkBreakTime()) break;
		pthread_mutex_lock(&worker);
		//Depart Car 
		if(canDepartCar[myPoint] == 1){

			pthread_barrier_wait(&readyToDepart);
			//Take away of other's depart Chance 
			for(int i = 1; i <= POINTS; i++) canDepartCar[i] = 0;
		
			if(curLine != FIRST_STREET && passingCar != myPoint)
			{
				departTime[myPoint] = tick;
				waitCarNumAtPoint[myPoint]--;
				pop(myPoint);
				curLine = SECOND_STREET;
			}

			pthread_barrier_wait(&Depart);
		}
		pthread_mutex_unlock(&worker); 
	}
	
}
void *position3(void *arg)
{
	int myPoint = 3;

	while(1)
	{
		
		//wait until get Chance to depart
		while(canDepartCar[myPoint] == 0); 

		if(passedCarNum == carNum  && checkBreakTime()) pthread_exit(NULL);
		pthread_mutex_lock(&worker);

		//Depart Car 
		if(canDepartCar[myPoint] == 1){

			pthread_barrier_wait(&readyToDepart);

			//Take away of other's depart Chance 
			for(int i = 1; i <= POINTS; i++) canDepartCar[i] = 0;
			if(curLine != SECOND_STREET && passingCar != myPoint)
			{
				departTime[myPoint] = tick;
				waitCarNumAtPoint[myPoint]--;
				pop(myPoint);
				curLine = FIRST_STREET;
			}
	
			pthread_barrier_wait(&Depart);
		}
		
		pthread_mutex_unlock(&worker); 
	}
	
}
void *position4(void *arg)
{
	int myPoint = 4;

	while(1)
	{
		
		//wait until get Chance to depart
		while(canDepartCar[myPoint] == 0); 
		if(passedCarNum == carNum  && checkBreakTime()) break;
		pthread_mutex_lock(&worker);
		//Depart Car 
		if(canDepartCar[myPoint] == 1){

			pthread_barrier_wait(&readyToDepart);
			
			//Take away of other's depart Chance 
			for(int i = 1; i <= POINTS; i++) canDepartCar[i] = 0;

			if(curLine != FIRST_STREET && passingCar != myPoint)
			{
				departTime[myPoint] = tick;
				waitCarNumAtPoint[myPoint]--;
				pop(myPoint);
				curLine = SECOND_STREET;
			}
			pthread_barrier_wait(&Depart);
		}
		pthread_mutex_unlock(&worker); 
	}
	
}
LIST* initNode(int car)
{
	LIST *tmp = (LIST*)malloc(sizeof(LIST));
	tmp->car = car;
	tmp->rlink = NULL;
	tmp->llink = NULL;
	return tmp;
}
void push(int car)
{
	LIST *tmp = initNode(car);
	if(head == NULL){
		head = tmp;
		tail = head;
		return;
	}

	tmp->rlink = head;
	head->llink = tmp;
	head = tmp;
}

void pop(int car)
{
	if(head ==NULL)
		return;
	if(head == tail && head->car == car)
	{
		free(head);
		head = NULL;
		tail = NULL;
	}
	if(car == 0) return; 
	LIST *cur = tail;
	while(cur != NULL)
	{
		if(cur->car == car)
		{
			//when cur is head 
			if(cur->llink == NULL)
			{
				head = cur->rlink;
				cur->rlink->llink = NULL;
				free(cur);
			}
			//when cur is tail
			else if(cur->rlink == NULL)
			{
				tail = cur->llink;
				cur->llink->rlink = NULL;
				free(cur);
			}else{
				cur->llink->rlink = cur->rlink;
				cur->rlink->llink = cur->llink;
				free(cur);
			}
			break;
		}
		cur = cur->llink;
	}
}
//find car at tick 
void findArriveAndPassingCar(int tick)
{
	int tmpLine = curLine; 
	for(int i = 1; i<= POINTS; i++)
	{
		//find car that arrived
		if((tick - departTime[i]) == 2 && departTime[i] > 0)
		{
			passingCar = 0;
			curLine = 0;
			passedCarNum++;
		}
	}
	for(int i = 1; i<= POINTS; i++)
	{
		// find car that is at middle of street 
		if((tick - departTime[i]) == 1 && departTime[i] > 0)
		{
			passingCar = i;
			curLine = tmpLine;
		}
	}
}


void printState(int tick)
{
	printf("tick : %d\n",tick);
	printf("===========================================\n");
	printf("Passed Vehicle\n Car ");	
	if(passingCar != 0) printf("%d\n",passingCar);
	else printf("\n");

	printf("Waiting Vehicle\n Car ");	
	if(tail != NULL)
	{
		LIST* cur = tail;
		while(cur != NULL)
		{
			printf("%d ",cur->car);
			cur = cur->llink;
		}
		printf("\n");
	}else{
		printf("\n");
	}	
	printf("===========================================\n");

}

