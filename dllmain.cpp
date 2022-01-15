// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "stdio.h"
#include <intrin.h>
#include "time.h"
#include <stdint.h>

#pragma warning(disable:4996)

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" _declspec(dllexport) unsigned int** asmCallStr(int eax_init) {
    unsigned int** rez = (unsigned int**)malloc(4 * sizeof(unsigned int*));
    for (int i = 0; i < 4; i++)
        rez[i] = (unsigned int*)malloc(2 * sizeof(unsigned int));

    unsigned int a[2], b[2], c[2], d[2];
    __asm {
        /* do the call. */
        mov eax, eax_init;
        cpuid;
        /* save results. */
        mov a, eax;
        mov b, ebx;
        mov c, ecx;
        mov d, edx;
    }
    a[1] = 0;
    b[1] = 0;
    c[1] = 0;
    d[1] = 0;

    *(rez) = a;
    *(rez + 1) = b;
    *(rez + 2) = c;
    *(rez + 3) = d;

    return rez;
}

extern "C" _declspec(dllexport) char* processorManufacturerSignature() {

    unsigned int** rez = asmCallStr(0);

    unsigned int b[2], c[2], d[2];

    b[0] = rez[1][0];
    b[1] = rez[1][1];

    d[0] = rez[3][0];
    d[1] = rez[3][1];

    c[0] = rez[2][0];
    c[1] = rez[2][1];

    char* res = (char*)calloc(13, sizeof(char));

    sprintf(res, "%s%s%s", b, d, c);
    return res;
}

extern "C" _declspec(dllexport) char* brandString() {
    char* res = (char*)calloc(50, sizeof(char));
    char* res1 = (char*)calloc(17, sizeof(char));
    char* res2 = (char*)calloc(17, sizeof(char));
    char* res3 = (char*)calloc(17, sizeof(char));

    unsigned int a[2], b[2], c[2], d[2];

    unsigned int** rez = asmCallStr(0x80000002);

    a[0] = rez[0][0];
    a[1] = rez[0][1];

    b[0] = rez[1][0];
    b[1] = rez[1][1];

    c[0] = rez[2][0];
    c[1] = rez[2][1];

    d[0] = rez[3][0];
    d[1] = rez[3][1];

    sprintf(res1, "%s%s%s%s", a, b, c, d);

    rez = asmCallStr(0x80000003);

    a[0] = rez[0][0];
    a[1] = rez[0][1];

    b[0] = rez[1][0];
    b[1] = rez[1][1];

    c[0] = rez[2][0];
    c[1] = rez[2][1];

    d[0] = rez[3][0];
    d[1] = rez[3][1];

    sprintf(res2, "%s%s%s%s", a, b, c, d);


    rez = asmCallStr(0x80000004);

    a[0] = rez[0][0];
    a[1] = rez[0][1];

    b[0] = rez[1][0];
    b[1] = rez[1][1];

    c[0] = rez[2][0];
    c[1] = rez[2][1];

    d[0] = rez[3][0];
    d[1] = rez[3][1];
    sprintf(res3, "%s%s%s%s", a, b, c, d);

    sprintf(res, "%s%s%s", res1, res2, res3);
    return res;
}

extern "C" _declspec(dllexport) unsigned int* asmCallInt(int eax_init, int ecx_init) {
    unsigned int* rez = (unsigned int*)malloc(4 * sizeof(unsigned int));
    unsigned a, b, c, d;

    __asm {
        /* do the call. */
        mov eax, eax_init;
        mov ecx, ecx_init;
        cpuid;
        /* save results. */
        mov a, eax;
        mov b, ebx;
        mov c, ecx;
        mov d, edx;
    }

    *(rez) = a;
    *(rez + 1) = b;
    *(rez + 2) = c;
    *(rez + 3) = d;

    return rez;
}

extern "C" _declspec(dllexport) char* decToBin(int dec) {
    char* binary = (char*)malloc(33);

    int i = 31;
    while (dec > 0) {
        if (dec % 2 == 0)
            *(binary + i) = '0';
        else
            *(binary + i) = '1';
        dec = dec / 2;
        i--;
    }
    for (int j = 0; j <= i; j++)
        *(binary + j) = '0';
    *(binary + 32) = '\0';

    return binary;
}

extern "C" _declspec(dllexport)char** outputEax(char* binary) {
    char** res = (char**)calloc(6, sizeof(char*));
    for (int i = 0; i < 6; i++)
        res[i] = (char*)calloc(10, sizeof(char));

    char* efid = (char*)malloc(9);
    strncpy(efid, (binary + 4), 8);
    efid[8] = '\0';
    sprintf(res[0], "%s", efid);

    char* emid = (char*)malloc(5);
    strncpy(emid, (binary + 12), 4);
    emid[4] = '\0';
    sprintf(res[1], "%s", emid);

    char* pt = (char*)malloc(3);
    strncpy(pt, (binary + 18), 2);
    pt[2] = '\0';
    sprintf(res[2], "%s", pt);

    char* fid = (char*)malloc(5);
    strncpy(fid, (binary + 20), 4);
    fid[4] = '\0';
    sprintf(res[3], "%s", fid);

    char* m = (char*)malloc(5);
    strncpy(m, (binary + 24), 4);
    m[4] = '\0';
    sprintf(res[4], "%s", m);

    char* sid = (char*)malloc(5);
    strncpy(sid, (binary + 28), 4);
    sid[4] = '\0';
    sprintf(res[5], "%s", sid);

    return res;
}

extern "C" _declspec(dllexport) char** processorFeaturesAndModel() {

    unsigned int* rez = asmCallInt(1, 0);

    return outputEax(decToBin(rez[0]));
}

extern "C" _declspec(dllexport) int* frequencyInfo() {
    int* res = (int*)calloc(3, sizeof(int));

    int cpuInfo[4] = { 0, 0, 0, 0 };
    __cpuid(cpuInfo, 0);
    if (cpuInfo[0] >= 0x16) {
        __cpuid(cpuInfo, 0x16);

        *res = cpuInfo[0];
        *(res + 1) = cpuInfo[1];
        *(res + 2) = cpuInfo[2];
    }

    return res;
}

extern "C" _declspec(dllexport) int* systemInfoProcessor() {
    int* res = (int*)calloc(4, sizeof(int));
    SYSTEM_INFO sysinfo;

    GetSystemInfo(&sysinfo);

    *res = sysinfo.dwNumberOfProcessors;
    *(res + 1) = sysinfo.dwProcessorType;
    *(res + 2) = sysinfo.wProcessorLevel;
    *(res + 3) = sysinfo.dwActiveProcessorMask;

    return res;
}

extern "C" _declspec(dllexport) int* systemInfoMemory() {
    int* res = (int*)calloc(4, sizeof(int));
    SYSTEM_INFO sysinfo;

    GetSystemInfo(&sysinfo);

    *res = sysinfo.dwPageSize;
    *(res + 1) = sysinfo.dwAllocationGranularity;
    *(res + 2) = (int)sysinfo.lpMinimumApplicationAddress;
    *(res + 3) = (int)sysinfo.lpMaximumApplicationAddress;

    return res;
}

int binToDec(char* binary) {
    int decimal = 0;
    int pow = 1;

    for (int i = strlen(binary) - 1; i >= 0; i--) {
        if (*(binary + i) == '1')
            decimal += pow;
        pow *= 2;
    }

    return decimal;
}

char** printCacheFeaturesL2(char* binary) {
    char** res = (char**)calloc(6, sizeof(char*));
    for (int i = 0; i < 6; i++)
        res[i] = (char*)calloc(20, sizeof(char));

    char* cacheSizeL2 = (char*)malloc(17);
    strncpy(cacheSizeL2, binary, 16);
    cacheSizeL2[16] = '\0';
    sprintf(res[0], "%d", binToDec(cacheSizeL2));

    char* cacheAssocL2 = (char*)malloc(5);
    strncpy(cacheAssocL2, (binary + 16), 4);
    cacheAssocL2[4] = '\0';
    switch (binToDec(cacheAssocL2)) {
    case 0: sprintf(*(res + 1), "%s", "Disabled"); break;
    case 1: sprintf(*(res + 1), "%s", "Direct mapped"); break;
    case 2: sprintf(*(res + 1), "%s", "2-Way"); break;
    case 4: sprintf(*(res + 1), "%s", "4-Way"); break;
    case 6: sprintf(*(res + 1), "%s", "8-Way"); break;
    case 8: sprintf(*(res + 1), "%s", "16-Way"); break;
    case 15: sprintf(*(res + 1), "%s", "Fully associative"); break;
    default: sprintf(*(res + 1), "%s", "Reserved");
    }

    char* cacheLineSizeL2 = (char*)malloc(9);
    strncpy(cacheLineSizeL2, (binary + 24), 8);
    cacheLineSizeL2[8] = '\0';
    sprintf(res[2], "%d", binToDec(cacheLineSizeL2));

    return res;
}

extern "C" _declspec(dllexport) char** cacheFeaturesL2() {

    unsigned int* rez = asmCallInt(0x80000006, 0);
    char** res = printCacheFeaturesL2(decToBin(rez[2]));
    return res;
}

int* printVirtualAndPhysicalAddrSize(char* eax) {
    int* res = (int*)calloc(2, sizeof(int));

    char* virtualAddrSize = (char*)malloc(9);
    strncpy(virtualAddrSize, (eax + 16), 8);
    virtualAddrSize[8] = '\0';
    res[0] = binToDec(virtualAddrSize);

    char* physicalAddrSize = (char*)malloc(9);
    strncpy(physicalAddrSize, (eax + 24), 8);
    physicalAddrSize[8] = '\0';
    res[1] = binToDec(physicalAddrSize);

    return res;
}

extern "C" _declspec(dllexport) int* virtualAndPhysicalAddrSize() {

    unsigned int* rez = asmCallInt(0x80000008, 0);
    int* res = printVirtualAndPhysicalAddrSize(decToBin(rez[0]));

    return res;
}

long long dim_max = 100000000;

double* mem_acc() {
    double* res = (double*)calloc(2, sizeof(double));
    clock_t t;
    double total_t = 0;

    long long* arr = (long long*)calloc(dim_max, sizeof(long long));


    for (long long i = 1; i < dim_max; i++) {
        t = clock();
        *(arr + i) = *(arr + i - 1) + 2;
        t = clock() - t;
        total_t += t;
    }

    double time_taken = ((double)total_t) / CLOCKS_PER_SEC;
    double instr_sec = 2 * (dim_max - 1) / time_taken;

    res[0] = time_taken;
    res[1] = instr_sec;

    free(arr);
    return res;
}

extern "C" _declspec(dllexport) double* perf_mem_acc(int nb_tests) {
    double* rez = (double*)calloc(nb_tests * 2 + 2, sizeof(double));

    double sum_time = 0;
    double sum_instr_sec = 0;

    for (int i = 0; i < nb_tests; i++) {
        double* res = mem_acc();
        rez[2 * i] = res[0];
        rez[2 * i + 1] = res[1];
        sum_time += res[0];
        sum_instr_sec += res[1];
        free(res);
    }
    double overall_time = sum_time / (float)nb_tests;
    double overall_instr_sec = sum_instr_sec / (float)nb_tests;

    rez[2 * nb_tests] = overall_time;
    rez[2 * nb_tests + 1] = overall_instr_sec;

    return rez;
}

double* encrypt(const char* sourcefile, const char* destfile) {

    clock_t t;
    double total_proc = 0;
    double total_acc = 0;
    double total_rw = 0;
    double* res = (double*)calloc(6, sizeof(double));

    t = clock();

    FILE* f = fopen(sourcefile, "r");
    FILE* g = fopen(destfile, "w");

    t = clock() - t;
    total_acc += t;

    if (f == NULL)
    {
        puts("eroare");
        res[0] = -1;
        return res;
    }
    int key = 11;
    char s[4096];
    int i = 0;
    int m = 0;

    while (!feof(f))
    {
        m++;

        t = clock();

        fgets(s, 4096, f);

        t = clock() - t;
        total_rw += t;

        i = strlen(s);
        for (int j = 0; j < i; j++) {
            t = clock();

            s[j] = s[j] ^ key;

            t = clock() - t;
            total_proc += t;
        }


        t = clock();

        fputs(s, g);

        t = clock() - t;
        total_rw += t;

        strcpy(s, "");
    }

    t = clock();

    fclose(f);
    fclose(g);

    t = clock() - t;
    total_acc += t;


    double time_taken_proc = ((double)total_proc) / CLOCKS_PER_SEC;
    double instr_sec_proc = (m - 1) * 4096 + i;
    res[0] = time_taken_proc;
    res[1] = instr_sec_proc;

    double time_taken_acc = ((double)total_acc) / CLOCKS_PER_SEC;
    double instr_sec_acc = 4;
    res[2] = time_taken_acc;
    res[3] = instr_sec_acc;

    double time_taken_rw = ((double)total_rw) / CLOCKS_PER_SEC;
    double instr_sec_rw = 2 * m;
    res[4] = time_taken_rw;
    res[5] = instr_sec_rw;

    return res;
}

double* decrypt(const char* sourcefile, const char* destfile) {
    clock_t t;
    double total_proc = 0;
    double total_acc = 0;
    double total_rw = 0;
    double* res = (double*)calloc(6, sizeof(double));

    t = clock();

    FILE* f = fopen(sourcefile, "r");
    FILE* g = fopen(destfile, "w");

    t = clock() - t;
    total_acc += t;

    if (f == NULL)
    {
        puts("eroare");
        res[0] = -1;
        return res;
    }
    int key = 11;
    char s[4096];
    int i = 0;
    int m = 0;

    while (!feof(f))
    {
        m++;

        t = clock();

        fgets(s, 4096, f);

        t = clock() - t;
        total_rw += t;

        i = strlen(s);
        for (int j = 0; j < i; j++) {
            t = clock();

            s[j] = s[j] ^ key;

            t = clock() - t;
            total_proc += t;
        }
        t = clock();

        fputs(s, g);

        t = clock() - t;
        total_rw += t;

        strcpy(s, "");
    }

    t = clock();

    fclose(f);
    fclose(g);

    t = clock() - t;
    total_acc += t;

    double time_taken_proc = ((double)total_proc) / CLOCKS_PER_SEC;
    double instr_proc = (m - 1) * 4096 + i;
    res[0] = time_taken_proc;
    res[1] = instr_proc;

    double time_taken_acc = ((double)total_acc) / CLOCKS_PER_SEC;
    double instr_acc = 4;
    res[2] = time_taken_acc;
    res[3] = instr_acc;

    double time_taken_rw = ((double)total_rw) / CLOCKS_PER_SEC;
    double instr_rw = 2 * m;
    res[4] = time_taken_rw;
    res[5] = instr_rw;

    return res;
}

extern "C" _declspec(dllexport) double* perf_encrypt_decrypt_proc(int nb_tests) {
    double* rez = (double*)calloc(nb_tests * 2 + 2, sizeof(double));
    double sum_time_proc = 0;
    double sum_instr_sec_proc = 0;

    for (int i = 0; i < nb_tests; i++) {
        double* res_en = encrypt("text_in.txt", "text_out.txt");
        double* res_de = decrypt("text_out.txt", "text_out_decr.txt");

        double time_total_proc = res_en[0] + res_de[0];
        double instr_sec_total_proc = (res_en[1] + res_de[1]) / time_total_proc;
        rez[2 * i] = time_total_proc;
        rez[2 * i + 1] = instr_sec_total_proc;
        sum_time_proc += time_total_proc;
        sum_instr_sec_proc += instr_sec_total_proc;

    }
    double overall_time_proc = sum_time_proc / (float)nb_tests;
    double overall_instr_sec_proc = sum_instr_sec_proc / (float)nb_tests;

    rez[2 * nb_tests] = overall_time_proc;
    rez[2 * nb_tests + 1] = overall_instr_sec_proc;

    return rez;
}

extern "C" _declspec(dllexport) double* perf_encrypt_decrypt_acc(int nb_tests) {
    double* rez = (double*)calloc(nb_tests * 2 + 2, sizeof(double));
    double sum_time_acc = 0;
    double sum_instr_sec_acc = 0;

    for (int i = 0; i < nb_tests; i++) {
        double* res_en = encrypt("text_in.txt", "text_out.txt");
        double* res_de = decrypt("text_out.txt", "text_out_decr.txt");

        double time_total_acc = res_en[2] + res_de[2];
        double instr_sec_total_acc = (res_en[3] + res_de[3]) / time_total_acc;
        rez[2 * i] = time_total_acc;
        rez[2 * i + 1] = instr_sec_total_acc;
        sum_time_acc += time_total_acc;
        sum_instr_sec_acc += instr_sec_total_acc;

    }
    double overall_time_acc = sum_time_acc / (float)nb_tests;
    double overall_instr_sec_acc = sum_instr_sec_acc / (float)nb_tests;

    rez[2 * nb_tests] = overall_time_acc;
    rez[2 * nb_tests + 1] = overall_instr_sec_acc;

    return rez;
}

extern "C" _declspec(dllexport) double* perf_encrypt_decrypt_rw(int nb_tests) {
    double* rez = (double*)calloc(nb_tests * 2 + 2, sizeof(double));
    double sum_time_rw = 0;
    double sum_instr_sec_rw = 0;

    for (int i = 0; i < nb_tests; i++) {
        double* res_en = encrypt("text_in.txt", "text_out.txt");
        double* res_de = decrypt("text_out.txt", "text_out_decr.txt");

        double time_total_rw = res_en[4] + res_de[4];
        double instr_sec_total_rw = (res_en[5] + res_de[5]) / time_total_rw;
        rez[2 * i] = time_total_rw;
        rez[2 * i + 1] = instr_sec_total_rw;
        sum_time_rw += time_total_rw;
        sum_instr_sec_rw += instr_sec_total_rw;

    }
    double overall_time_rw = sum_time_rw / (float)nb_tests;
    double overall_instr_sec_rw = sum_instr_sec_rw / (float)nb_tests;

    rez[2 * nb_tests] = overall_time_rw;
    rez[2 * nb_tests + 1] = overall_instr_sec_rw;
    return rez;
}

double* mandelbrot() {
    const double xmin = 0.27085;
    const double xmax = 0.27100;
    const double ymin = 0.004640;
    const double ymax = 0.004810;

    /* Maximum number of iterations, at most 65535. */
    const uint16_t maxiter = (unsigned short)60000;

    /* Image size, width is given, height is computed. */
    const int xres = 1024;
    const int yres = (xres * (ymax - ymin)) / (xmax - xmin);

    /* Precompute pixel width and height. */
    double dx = (xmax - xmin) / xres;
    double dy = (ymax - ymin) / yres;

    double x, y; /* Coordinates of the current point in the complex plane. */
    double u = 0.0, v = 0.0; /* Coordinates of the iterated point. */
    int i, j; /* Pixel counters */
    int k; /* Iteration counter */
    double u2 = u * u;
    double v2 = v * v;

    double* res = (double*)calloc(2, sizeof(double));
    clock_t t;
    double total_t = 0;

    for (j = 0; j < yres; j++) {
        t = clock();

        y = ymax - j * dy;

        t = clock() - t;
        total_t += t;
        for (i = 0; i < xres; i++) {
            t = clock();

            x = xmin + i * dx;

            t = clock() - t;
            total_t += t;
            /* iterate the point */
            for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
                t = clock();

                v = 2 * u * v + y;
                u = u2 - v2 + x;
                u2 = u * u;
                v2 = v * v;

                t = clock() - t;
                total_t += t;
            }
        }
    }

    double time_taken = ((double)total_t) / CLOCKS_PER_SEC;
    double instr_sec = yres * (1 + xres * (1 + k)) / time_taken;

    res[0] = time_taken;
    res[1] = instr_sec;

    return res;
}

extern "C" _declspec(dllexport) double* perf_mandelbrot(int nb_tests) {
    double* rez = (double*)calloc(nb_tests * 2 + 2, sizeof(double));
    double sum_time = 0;
    double sum_instr_sec = 0;

    for (int i = 0; i < nb_tests; i++) {
        double* res = mandelbrot();
        rez[2 * i] = res[0];
        rez[2 * i + 1] = res[1];
        sum_time += res[0];
        sum_instr_sec += res[1];
        free(res);
    }
    double overall_time = sum_time / (float)nb_tests;
    double overall_instr_sec = sum_instr_sec / (float)nb_tests;

    rez[2 * nb_tests] = overall_time;
    rez[2 * nb_tests + 1] = overall_instr_sec;

    return rez;
}

void printEaxCache(char* binary, int index, char** res) {

    char* cacheType = (char*)malloc(6);
    strncpy(cacheType, (binary + 27), 5);
    cacheType[5] = '\0';

    char* chType = (char*)calloc(20, sizeof(char));

    switch (binToDec(cacheType)) {
    case 0: sprintf(chType, "Null, no more caches"); break;
    case 1: sprintf(chType, "Data cache"); break;
    case 2: sprintf(chType, "Instruction cache"); break;
    case 3: sprintf(chType, "Unified cache"); break;
    default: sprintf(chType, "Reserved");
    }

    *(res + index * 13) = chType;

    char* cacheLvl = (char*)malloc(4);
    strncpy(cacheLvl, (binary + 24), 3);
    cacheLvl[3] = '\0';

    sprintf(*(res + index * 13 + 1), "%d", binToDec(cacheLvl));

    char* nbProcBin = (char*)malloc(7);
    strncpy(nbProcBin, binary, 6);
    nbProcBin[6] = '\0';
    sprintf(*(res + index * 13 + 2), "%d", binToDec(nbProcBin) + 1);

    char* nbThreadsBin = (char*)malloc(13);
    strncpy(nbThreadsBin, (binary + 6), 12);
    nbThreadsBin[12] = '\0';
    sprintf(*(res + index * 13 + 3), "%d", binToDec(nbThreadsBin) + 1);

    if (*(binary + 22) == '1')
        sprintf(*(res + index * 13 + 4), "YES");
    else
        sprintf(*(res + index * 13 + 4), "NO");

    if (*(binary + 23) == '1')
        sprintf(*(res + index * 13 + 5), "YES");
    else
        sprintf(*(res + index * 13 + 5), "NO");

    return;
}

void printEbxCache(char* binary, int index, char** res) {

    char* ways = (char*)malloc(11);
    strncpy(ways, binary, 10);
    ways[10] = '\0';
    sprintf(*(res + index * 13 + 6), "%d", binToDec(ways) + 1);

    char* physLinePart = (char*)malloc(11);
    strncpy(physLinePart, (binary + 10), 10);
    physLinePart[10] = '\0';
    sprintf(*(res + index * 13 + 7), "%d", binToDec(physLinePart) + 1);

    char* sysCoherLineSize = (char*)malloc(13);
    strncpy(sysCoherLineSize, (binary + 20), 12);
    sysCoherLineSize[12] = '\0';
    sprintf(*(res + index * 13 + 8), "%d", binToDec(sysCoherLineSize) + 1);
}

void printEcxCache(char* binary, int index, char** res) {
    sprintf(*(res + index * 13 + 9), "%d", binToDec(binary) + 1);
}

void printEdxCache(char* binary, int index, char** res) {
    if (*(binary + 29) == '1')
        sprintf(*(res + index * 13 + 10), "YES");
    else
        sprintf(*(res + index * 13 + 10), "NO");

    if (*(binary + 30) == '1')
        sprintf(*(res + index * 13 + 11), "YES");
    else
        sprintf(*(res + index * 13 + 11), "NO");
}

long long int cacheSizeInBytes(char* ebx, char* ecx) {
    long long int cacheSize = 0;

    char* ways = (char*)malloc(11);
    strncpy(ways, ebx, 10);
    ways[10] = '\0';

    char* physLinePart = (char*)malloc(11);
    strncpy(physLinePart, (ebx + 10), 10);
    physLinePart[10] = '\0';

    char* sysCoherLineSize = (char*)malloc(13);
    strncpy(sysCoherLineSize, (ebx + 20), 12);
    sysCoherLineSize[12] = '\0';

    cacheSize = (binToDec(ways) + 1) * (binToDec(physLinePart) + 1) * (binToDec(sysCoherLineSize) + 1) * (binToDec(ecx) + 1);

    return cacheSize;
}

void deterministicCacheParameters(int val, char** res) {
    //val va avea o valoare intre 0 si 3 (val = nivelul cache analizat)

    unsigned int* rez = asmCallInt(4, val);

    printEaxCache(decToBin(rez[0]), val, res);
    printEbxCache(decToBin(rez[1]), val, res);
    printEcxCache(decToBin(rez[2]), val, res);
    printEdxCache(decToBin(rez[3]), val, res);
    sprintf(*(res + val * 13 + 12), "%f", (float)cacheSizeInBytes(decToBin(rez[1]), decToBin(rez[2])) / (1024 * 1024));

    return;
}

extern "C" _declspec(dllexport) char** wrapperDeterministicCacheParameters() {
    char** res = (char**)calloc(52, sizeof(char*));
    for (int i = 0; i < 52; i++)
        res[i] = (char*)calloc(20, sizeof(char));

    for (int i = 0; i < 4; i++) {
        deterministicCacheParameters(i, res);
    }

    return res;
}

extern "C" _declspec(dllexport) double* grade_my_pc() {
    double* rez = (double*)calloc(6, sizeof(double));

    int grade_integ;
    int grade_float;
    int grade_file_acc;
    int grade_file_rw;
    int grade_heap;

    double* rez_integ = perf_encrypt_decrypt_proc(10);
    double time_integ = rez_integ[20];
    free(rez_integ);
    if (time_integ < 0.9)
        grade_integ = 10;
    else
        if (time_integ < 1.5)
            grade_integ = 9;
        else
            if (time_integ < 2.1)
                grade_integ = 8;
            else
                if (time_integ < 2.7)
                    grade_integ = 7;
                else
                    if (time_integ < 3.3)
                        grade_integ = 6;
                    else
                        if (time_integ < 3.9)
                            grade_integ = 5;
                        else
                            if (time_integ < 4.5)
                                grade_integ = 4;
                            else
                                if (time_integ < 5.1)
                                    grade_integ = 3;
                                else
                                    if (time_integ < 5.7)
                                        grade_integ = 2;
                                    else
                                        grade_integ = 1;

    double* rez_float = perf_mandelbrot(100);
    double time_float = rez_float[200];
    free(rez_float);
    if (time_float < 0.025)
        grade_float = 10;
    else
        if (time_float < 0.05)
            grade_float = 9;
        else
            if (time_float < 0.075)
                grade_float = 8;
            else
                if (time_float < 0.1)
                    grade_float = 7;
                else
                    if (time_float < 0.125)
                        grade_float = 6;
                    else
                        if (time_float < 0.15)
                            grade_float = 5;
                        else
                            if (time_float < 0.175)
                                grade_float = 4;
                            else
                                if (time_float < 0.2)
                                    grade_float = 3;
                                else
                                    if (time_float < 0.225)
                                        grade_float = 2;
                                    else
                                        grade_float = 1;

    double* rez_file_acc = perf_encrypt_decrypt_acc(10);
    double time_file_acc = rez_file_acc[20];
    free(rez_file_acc);
    if (time_file_acc < 0.009)
        grade_file_acc = 10;
    else
        if (time_file_acc < 0.019)
            grade_file_acc = 9;
        else
            if (time_file_acc < 0.029)
                grade_file_acc = 8;
            else
                if (time_file_acc < 0.1)
                    grade_file_acc = 7;
                else
                    if (time_file_acc < 0.18)
                        grade_file_acc = 6;
                    else
                        if (time_file_acc < 0.25)
                            grade_file_acc = 5;
                        else
                            if (time_file_acc < 0.32)
                                grade_file_acc = 4;
                            else
                                if (time_file_acc < 0.39)
                                    grade_file_acc = 3;
                                else
                                    if (time_file_acc < 0.46)
                                        grade_file_acc = 2;
                                    else
                                        grade_file_acc = 1;

    double* rez_file_rw = perf_encrypt_decrypt_rw(10);
    double time_file_rw = rez_file_rw[20];
    free(rez_file_rw);
    if (time_file_rw < 0.5)
        grade_file_rw = 10;
    else
        if (time_file_rw < 1)
            grade_file_rw = 9;
        else
            if (time_file_rw < 1.5)
                grade_file_rw = 8;
            else
                if (time_file_rw < 7)
                    grade_file_rw = 7;
                else
                    if (time_file_rw < 20)
                        grade_file_rw = 6;
                    else
                        if (time_file_rw < 30)
                            grade_file_rw = 5;
                        else
                            if (time_file_rw < 40)
                                grade_file_rw = 4;
                            else
                                if (time_file_rw < 50)
                                    grade_file_rw = 3;
                                else
                                    if (time_file_rw < 60)
                                        grade_file_rw = 2;
                                    else
                                        grade_file_rw = 1;

    double* rez_mem_acc = perf_mem_acc(10);
    double time_mem_acc = rez_mem_acc[20];
    free(rez_mem_acc);
    if (time_mem_acc < 4)
        grade_file_acc = 10;
    else
        if (time_mem_acc < 6)
            grade_heap = 9;
        else
            if (time_mem_acc < 8)
                grade_heap = 8;
            else
                if (time_mem_acc < 10)
                    grade_heap = 7;
                else
                    if (time_mem_acc < 12)
                        grade_heap = 6;
                    else
                        if (time_mem_acc < 16)
                            grade_heap = 5;
                        else
                            if (time_mem_acc < 20)
                                grade_heap = 4;
                            else
                                if (time_mem_acc < 24)
                                    grade_heap = 3;
                                else
                                    if (time_mem_acc < 28)
                                        grade_heap = 2;
                                    else
                                        grade_heap = 1;

    rez[0] = grade_integ;
    rez[1] = grade_float;
    rez[2] = grade_file_acc;
    rez[3] = grade_file_rw;
    rez[4] = grade_heap;
    rez[5] = (grade_integ + grade_float + grade_file_acc + grade_file_rw + grade_heap) / 5.0;
    return rez;
}