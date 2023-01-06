#include <iostream>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <thread>

/*
参考：
1. https://cloud.tencent.com/developer/article/2146439#
2. https://en.cppreference.com/w/cpp/thread/condition_variable

“生产者-消费者”经典模型：
1. producter生成数据，consumer消耗数据
    g_data_deque.size()表示数据数量，
    producter使g_data_deque.size()+1，
    consumer使g_data_deque.size()-1
2. g_data_deque.size()=0时，consumer不能再消耗数据，运行中需要保证其为非负数
3. g_data_deque.size()<MAX_NUM，即数据数量要不超过最大容量，
    =MAX_NUM时，producter不在生成数据

分析：
1. 此时producter和consumer都需要使用条件变量加锁和唤醒
    producter的等待条件是g_data_deque.size()==MAX_NUM
    consumer的等待条件是g_data_deque==0
*/

std::mutex g_cvMutex;
std::condition_variable g_cv;

//缓存区
std::deque<int> g_data_deque;
//缓存区最大数目
const int  MAX_NUM = 10;
//数据
int g_next_index = 0;

//生产者，消费者线程个数
const int PRODUCER_THREAD_NUM  = 3;
const int CONSUMER_THREAD_NUM = 3;

void  producer_thread(int thread_id)
{
  while (true)
  {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      //加锁
      std::unique_lock <std::mutex> lk(g_cvMutex);
      //当队列未满时，继续添加数据
      /*
      1. [](){ return g_data_deque.size() <= MAX_NUM; } 
         lambda表达式充当谓词功能，当队列未满时返回true
      2. 只有当谓词返回false时，才可能执行wait
      
      */
      g_cv.wait(lk, [](){ return g_data_deque.size() <= MAX_NUM; });

      g_next_index++;
      g_data_deque.push_back(g_next_index);
      std::cout << "producer_thread: " << thread_id << " producer data: " << g_next_index;
      std::cout << " queue size: " << g_data_deque.size() << std::endl;

      //唤醒其他线程 
      g_cv.notify_all();

      //自动释放锁
  }
}

void  consumer_thread(int thread_id)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(550));
        //加锁
        std::unique_lock <std::mutex> lk(g_cvMutex);
        //检测条件是否达成
        g_cv.wait( lk,   []{ return !g_data_deque.empty(); });

        //互斥操作，消息数据
        int data = g_data_deque.front();
        g_data_deque.pop_front();
        std::cout << "\tconsumer_thread: " << thread_id << " consumer data: ";
        std::cout << data << " deque size: " << g_data_deque.size() << std::endl;

        //唤醒其他线程
        g_cv.notify_all();

        //自动释放锁
    }
}


int main()
{
    std::thread arrRroducerThread[PRODUCER_THREAD_NUM];
    std::thread arrConsumerThread[CONSUMER_THREAD_NUM];

    for (int i = 0; i < PRODUCER_THREAD_NUM; i++)
    {
        arrRroducerThread[i] = std::thread(producer_thread, i);
    }

    for (int i = 0; i < CONSUMER_THREAD_NUM; i++)
    {
        arrConsumerThread[i] = std::thread(consumer_thread, i);
    }

    for (int i = 0; i < PRODUCER_THREAD_NUM; i++)
    {
        arrRroducerThread[i].join();
    }

    for (int i = 0; i < CONSUMER_THREAD_NUM; i++)
    {
        arrConsumerThread[i].join();
    }
    
    return 0;
}