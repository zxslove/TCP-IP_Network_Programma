/*
    创建多线程服务器, pthread_join加入执行流
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
void* thread_main(void* arg);

int main(int argc, char* argv[])
{
    pthread_t t_id;
    int pthread_argm = 5;
    void* thr_ret;

    if(pthread_create(&t_id, NULL, thread_main, (void*)&pthread_argm) != 0)
    {
        puts("pthread_create error!");
        return -1;
    }

    if(pthread_join(t_id, &thr_ret) != 0)
    {
        puts("pthread_join error!");
        return -1; 
    }
    
    printf("Thread return msg: %s\n", (char*)thr_ret);
    free(thr_ret);
    return 0;
}

void* thread_main(void* arg)
{
    int i;
    int cnt = *((int*)arg);
    char* msg = (char*)malloc(sizeof(char)*50);
    strcpy(msg, "I am thread!");

    for(i = 0 ; i < cnt; ++i)
    {
        sleep(1);
        printf("runing thread: %d\n", i);
    }
    return (void*)msg;
}