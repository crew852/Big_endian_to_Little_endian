#include <stdio.h>
#include <stdint.h>
#include <pcap.h>

// 빅 엔디언을 리틀 엔디언으로 변환하는 함수
uint32_t swapEndian(uint32_t data) {
    return ((data >> 24) & 0xFF) | ((data >> 8) & 0xFF00) | ((data << 8) & 0xFF0000) | ((data << 24) & 0xFF000000);
    // '000000FF' FF위치로 밀고 and 연산 | '0000FF00' FF위치로 밀고 and 연산 ...
    //=>> FF자리만 AND연산으로 남음
}

int main() {
    FILE *inputFile, *outputFile;
    uint32_t data;

    // 입력 파일 열기
    inputFile = fopen("file1.bin", "rb");
    if (inputFile == NULL) {
        perror("입력 파일 열기 실패");
        return 1;
    }

    // 출력 파일 열기
    outputFile = fopen("file2.bin", "wb");
    if (outputFile == NULL) {
        perror("출력 파일 열기 실패");
        fclose(inputFile);
        return 1;
    }

    // 파일의 데이터를 16진수로 출력
    printf("원본 데이터: %08X\n", data);
    while (fread(&data, sizeof(uint32_t), 1, inputFile) == 1) {

        // 빅 엔디언을 리틀 엔디언으로 변환
        uint32_t littleEndianData = swapEndian(data);

        // 변환된 데이터를 출력
        printf("변환된 데이터: %08X\n", littleEndianData);

        // 변환된 데이터를 출력 파일에 쓰기
        fwrite(&littleEndianData, sizeof(uint32_t), 1, outputFile);
    }

    // 파일 닫기
    fclose(inputFile);
    fclose(outputFile);

    printf("엔디언 변환 완료\n");

    return 0;
}