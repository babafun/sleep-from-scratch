#define SYS_write 1
#define SYS_nanosleep 35 
#define SYS_exit 60


typedef struct timespec {
    long tv_sec;
    long tv_nsec;
} timespec;

long syscall1(long number, long arg1) {
    long result;

    __asm__ __volatile__(
        "syscall"
        : "=a" (result)
        : "a" (number), "D" (arg1)
        : "rcx", "r11", "memory"
    );

    return result;
}


long syscall2(long number, long arg1, long arg2) {
    long result;

    __asm__ __volatile__(
        "syscall"
        : "=a" (result)
        : "a" (number), "D" (arg1), "S" (arg2)
        : "rcx", "r11", "memory"
    );

    return result;
}


long syscall3(long number, long arg1, long arg2, long arg3) {
    long result;

    __asm__ __volatile__(
        "syscall"
        : "=a" (result)
        : "a" (number), "D" (arg1), "S" (arg2), "d" (arg3)
        : "rcx", "r11", "memory"
    );

    return result;
}


int parse_int(const char *raw_int) {
    int result = 0;
    const char *cursor = raw_int;

    while (*cursor >= '0' && *cursor <= '9') {
        result = result * 10 + (*cursor - '0');
        cursor++;
    }

    return result;
}


long unsigned strlen(const char *string) {
    const char *cursor = string;
    while (*cursor) {
        cursor++;
    }

    long unsigned result = cursor - string;
    return result;
}


void print(const char *string) {
    syscall3(SYS_write, 1, (long)string, strlen(string));
}


void sleep(long seconds) {
    timespec duration = {0};
    duration.tv_sec = seconds;

    syscall2(SYS_nanosleep, (long)(&duration), 0);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        print("Usage: sleep NUMBER\nPause for NUMBER seconds\n");
        return 1;
    }

    char *raw_seconds = argv[1];
    long seconds = parse_int(raw_seconds);

    print("Sleeping for ");
    print(raw_seconds);
    print(" seconds\n");
    sleep(seconds);

    return 0;
}

#ifdef __cplusplus  
extern "C" {
#endif

 void exit(int code) {
    syscall1(SYS_exit, code);

    for(;;) {}
}


__attribute__((naked)) void _start() {
    __asm__ __volatile__(
        "xor %ebp, %ebp\n"
        "mov (%rsp), %rdi\n"
        "lea 8(%rsp), %rsi\n"
        "and $-16, %rsp\n"
        "call main\n"
        "mov %rax, %rdi\n"
        "call exit\n"
    );
}

#ifdef __cplusplus
}
#endif