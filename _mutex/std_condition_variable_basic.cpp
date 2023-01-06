#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <time.h>
using namespace std;

/*
“生产者-消费者”经典模型的简化版
1. producter生成数据，consumer消耗数据
    datasize表示数据数量，producter使datasize+1，consumer使datasize-1
2. datasize=0时，consumer不能再消耗数据
    即，运行中需要保证datasize为非负数

*/

std::mutex mtx;
std::condition_variable cv;
int datasize = 0;


void producter(int id){
    while(true){
        // 模拟生产数据的时间
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(mtx);
            datasize++;
            cout << "producter "<< id << "datasize " << datasize << endl;

        }
        
        /*
        1. 在lock_guard的作用域内还是外?
            从结果上看，在其内外无区别。需要找lihao确认。
        2. cv.notify_one(); 随机唤醒一个等待的线程。
        3. cv.notify_all(); 唤醒所有等待线程。
        */
        cv.notify_all(); 

    }

}

void consumer(int id){
    while(true){
        // 模拟使用数据的时间
        std::this_thread::sleep_for(std::chrono::seconds(2));
        {
            /*
            因为后续程序使用了cv.wait系列函数，
            此处必须使用std::unique_lock
            */
            std::unique_lock<std::mutex> lock(mtx);
            
            /*
            1. cv.wait(lock); 
                表示等待唤醒，但此种写法会被假醒(spurious wakeup)影响

            2. cv.wait(lock, []{return datasize;}); 
                为推荐写法，可避免假醒影响
                (1) 第二个参数传入谓词(predicate)，此处为lambda表达式
                (2) 语义上可以认为等价于
                    while(! datasize){
                        cv.wait(lock);
                    }

            3. cv.wait_for(lock, std::chrono::seconds(5), []{return datasize;});
                表示只等待唤醒5秒。
                等待5秒后，无论谓词返回结果，自动唤醒。
                (1) 此处不可写成
                    while(! datasize){
                        cv.wait_for(lock, std::chrono::seconds(5));
                    }
                    因为可能唤醒后发现datasize为false，仍然处于while循环中
                    即效果上相当于受到了谓词的影响，与真正效果不同。
                (2) 可用clock_gettime验证等待时间

            4. cv.wait_for(lock, duration, predicate)
                相当于cv.wait_until(lock, now_clock + duration, predicate)
            */
            while(! datasize){
                cv.wait(lock);
            }

            datasize--;
            cout<< "\tConsumer "<< id << "datasize " << datasize << endl;
        }
    }
    
}

int main(){

    int product_num = 2; // 生产者线程数
    int consume_num = 10; // 消费者线程数

    // 创建生产者线程
    std::thread product[product_num];
    for (int i = 0; i < product_num; i++){
        product[i] = std::thread(producter, i);
    }

    // 创建消费者线程
    std::thread consume[consume_num];
    for (int i = 0; i < consume_num; i++){
        consume[i] = std::thread(consumer, i);
    }

    // 启动生产者线程
    for (int i = 0; i < product_num; i++){
        product[i].join();
    }  

    // 启动消费者线程
    for (int i = 0; i < consume_num; i++){
        consume[i].join();
    }    

    return 0;
}