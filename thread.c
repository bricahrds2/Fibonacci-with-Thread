#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// -----------------------
void* fib_thread(void *ptr);  // Prototype for the thread "fib_thread".

// -----------------------
// The struct below is used as the parameter for threads created.
struct msg_struct{
   int n;  // The parameter n (<= 100). for the Fibonacci sequence.
   char *s; // A string with your self-defined message. 
   char *name; // A string for the thread name, such as Thread 1, Thread 2, ...., Thread4.
   int result[100]; // An integer array to hold the Fibonacci results.
};

// -----------------------
int fib(int n) 
{
// Write your code for the Fibonacci sequence.
// Input parameter: an integer n (<= 100).
// Return value: the nth Fibonacci number as the integer data type.
	if(n <=1)
		return n;
	return fib(n-1) + fib(n - 2);
}

//printf("%d\n",fib(3));

// -----------------------
void fib_print(struct msg_struct *msg)
{
    // This function prints the content of a "msg_struct" instance.
    printf("%s\n",msg->name);
    printf("%s\n",msg->s);
    printf("%d\n",msg->n);
    //printf("%d\n",msg->result);
    
   for(int i = 0; i <= msg->n; i++)
      printf("%d ", msg->result[i]);
   printf("\n");
}



int main() {

//printf("******* ---> %d\n",fib(10));

// Declare four (4) thread identifiers here.
	pthread_t t1id; pthread_t t2id; pthread_t t3id; pthread_t t4id;
	pthread_attr_t attr1; pthread_attr_t attr2; pthread_attr_t attr3; pthread_attr_t attr4; 
	
// 1). Declare four (4) "msg_struct" instances used for thread parameters and 2). assign them initial values.
	struct msg_struct test1;
	test1.n = 12;
	test1.s = "YodieGang";
	test1.name = "Thread_1";
	
	struct msg_struct test2;
	test2.n = 10;
	test2.s = "Blinkerton";
	test2.name = "Thread_2";
	
	struct msg_struct test3;
	test3.n = 15;
	test3.s = "PenDulum City";
	test3.name = "Thread_3";
	
	struct msg_struct test4;
	test4.n = 5;
	test4.s = "Fulcrum";
	test4.name = "Thread_4";
	
// 1). Create four (4) threads and 2). Pass initialized parameters into it. 
	pthread_attr_init(&attr1);
	pthread_create(&t1id, &attr1, fib_thread,(void*) &test1);

	pthread_attr_init(&attr2);
	pthread_create(&t2id, &attr2, fib_thread,(void*) &test2);
	
	pthread_attr_init(&attr3);
	pthread_create(&t3id, &attr3, fib_thread,(void*) &test3);
	
	pthread_attr_init(&attr4);
	pthread_create(&t4id, &attr4, fib_thread,(void*) &test4);
	
// Synchronization system calls to control the execution sequence. 
	pthread_join(t1id, NULL);
	pthread_join(t2id, NULL);
	pthread_join(t3id, NULL);
	pthread_join(t4id, NULL);
// Calls to the "fib_print()" function for the output.
	fib_print(&test1);
	fib_print(&test2);
	fib_print(&test3);
	fib_print(&test4);
    return 0;
}

// -----------------------
// Execution for the thread.
void* fib_thread(void *ptr)
{
// Extract the sequence parameter, n from the thread parameter, a "struct msg_struct" instance in this case, for the Fibonacci sequence calculation.
// Call the "fib(int n)" function to calculate the values for the Fib sequence and store them in the "result" array in order.
	struct msg_struct *msg = (struct msg_struct *) ptr;
	int num = msg->n;
	int holder[100];
	int out;
	
	for(int i = 0; out != fib(num) ; i++){
		if(i>=2){
			out = holder[i-1] + holder[i-2];
			holder[i] = out;
		//printf(" %d",out);
		}
		else{
			holder[i] = i;
			//printf(" %d",i);
		}
	}
	//memcpy(msg->result,holder,num);
	for(int i = 0; i <= num; i++){
		msg->result[i]=holder[i];
	}
	
}
