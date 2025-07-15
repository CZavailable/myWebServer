#include <iostream>
#include <functional>
#include <atomic>
#include <chrono>
#include <future>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Buffer.h"
#include "ThreadPool.h"

using namespace std;

std::atomic<int> total_msgs_sent(0);  // 全局消息发送统计

void oneClient(int msgs, int wait) {
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.40.129");
    addr.sin_port = htons(1234);
    int ret = ::connect(sockfd,(sockaddr*)&addr,sizeof(addr));
    if(ret == -1){
        perror("连接服务端失败");
    }

    Buffer* sendBuffer = new Buffer();
    Buffer* readBuffer = new Buffer();

    sleep(wait);
    int count = 0;

    auto start = std::chrono::steady_clock::now();

    while (count < msgs) {
        sendBuffer->append("I'm client!");
        ssize_t write_bytes = ::write(sockfd, sendBuffer->peekAllAsString().c_str(), sendBuffer->readableBytes());
        if (write_bytes == -1) {
            perror("write failed");
            break;
        }

        int already_read = 0;
        char buf[1024];
        auto read_start = std::chrono::steady_clock::now();
        bool read_success = false;
        bool read_timeout = false;

        while (true) {
            memset(&buf, 0, sizeof(buf));
            ssize_t read_bytes = ::read(sockfd, buf, sizeof(buf));
            if (read_bytes > 0) {
                readBuffer->append(buf, read_bytes);
                already_read += read_bytes;

                if (already_read >= sendBuffer->readableBytes()) {
                    read_success = true;
                    break;
                }
            } else if (read_bytes == 0) {
                fprintf(stderr, "server disconnected!\n");
                goto cleanup;
            } else {
                if (errno == EINTR) continue;
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    break;  // 非阻塞或数据暂时不可读
                }
                perror("read failed");
                goto cleanup;
            }

            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - read_start).count() > 5) {
                fprintf(stderr, "read timeout\n");
                read_timeout = true;
                break;
            }
        }

        ++count;
        if (read_success) ++total_msgs_sent;
        if (read_timeout) break;

        readBuffer->retrieveAll();
    }

    {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "One client finished in " << elapsed.count() << " seconds." << std::endl;
    }

cleanup:
    delete sendBuffer;
    delete readBuffer;
}


int main(int argc, char* argv[]) {
    int threads = 100;
    int msgs = 100;
    int wait = 0;
    int o;
    const char* optstring = "t:m:w:";
    while ((o = getopt(argc, argv, optstring)) != -1) {
        switch (o) {
            case 't':
                threads = stoi(optarg);
                break;
            case 'm':
                msgs = stoi(optarg);
                break;
            case 'w':
                wait = stoi(optarg);
                break;
            case '?':
                printf("error optopt: %c\n", optopt);
                printf("error opterr: %d\n", opterr);
                break;
        }
    }

    auto global_start = chrono::steady_clock::now();

    ThreadPool* pool = new ThreadPool(threads);
    for (int i = 0; i < threads; ++i) {
        pool->add(bind(oneClient, msgs, wait));
    }

    delete pool;  // 等待所有线程执行完毕

    auto global_end = chrono::steady_clock::now();
    chrono::duration<double> total_time = global_end - global_start;

    cout << "\n======= Performance Summary =======\n";
    cout << "Total clients       : " << threads << "\n";
    cout << "Messages per client : " << msgs << "\n";
    cout << "Total messages sent : " << total_msgs_sent.load() << "\n";
    cout << "Total time taken    : " << total_time.count() << " seconds\n";
    cout << "QPS (requests/sec)  : " << total_msgs_sent.load() / total_time.count() << "\n";
    cout << "===================================\n";

    return 0;
}
