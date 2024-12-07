#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // for open()
#include <unistd.h> // for read(), write(), close()

#include "cat_command.h"

void my_cat(const char *filename) {
    // 파일 열기
    int fd = open(filename, O_RDONLY);
    if (fd < 0) { // 파일을 열지 못한 경우
        perror("cat");
        return;
    }

    // 읽기 및 출력용 버퍼
    char buf[1024];
    ssize_t bytes_read;

    // 파일을 읽어서 출력
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, bytes_read) < 0) { // 표준 출력에 쓰기
            perror("write");
            close(fd);
            return;
        }
    }

    // 읽기 오류 처리
    if (bytes_read < 0) {
        perror("read");
    }

    // 파일 닫기
    close(fd);
}
