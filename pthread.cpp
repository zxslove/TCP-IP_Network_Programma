/*
    创建多线程服务器
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void* thread_main(void* arg);

int main(int argc, char* argv[])
{
    pthread_t t_id;
    int pthread_argm = 5;
    if(pthread_create(&t_id, NULL, thread_main, (void*)&pthread_argm) != 0)
    {
        printf("cretae thread error!");
    }
    sleep(10);
    printf("end of main");
    return 0;
}

void* thread_main(void* arg)
{
    int i;
    int cnt = *((int*)arg);
    for(i = 0; i < cnt; ++i)
    {
        sleep(1);
        printf("runing thread: %d\n", i);
    }
    return NULL;
}