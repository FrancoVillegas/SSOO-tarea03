#include <iostream>
#include <thread>
#include <unistd.h>
#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>
using namespace std;
  
void impar(int n){
    pid_t pid = syscall(SYS_gettid);
    int a = 1;
    for (int i = 0; i < n; i++) {
        cout << "Valor Impar: " << a << " - "
            << "PPIDE = " << pid << "\n";
        a+=2;
        this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void fibo(int n){
    int a = 0, b = 1, c = 0;
    pid_t pid1 = syscall(SYS_gettid);
    for (int i = 1; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
        cout << "Valor Fibonacci: " << c << " - "
            << "PPIDE = " << pid1 << "\n";
        this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void sigint(int a){ /*Cuando recibe una señal no hace nada.*/ cout << "\n";
} 

int main(int argvc, char * argv[]){
    signal(SIGINT, sigint);
    signal(SIGTSTP, sigint);
    signal(SIGQUIT, sigint);
    std::thread thread1(impar, 50);
    std::thread thread2(fibo, 50);
    thread1.join();
    thread2.join();
    return 0;
}