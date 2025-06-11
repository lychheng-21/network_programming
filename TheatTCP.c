#include <windows.h> // Deadlock is Server and client do a active in a time (send and recieve same time)
#include <stdio.h>   // 

#define MAXCNT 100000000
int count = 0;
CRITICAL_SECTION cs;

DWORD WINAPI MyThread1(LPVOID arg)
{
	for (int i = 0; i < MAXCNT; i++) {
		EnterCriticalSection(&cs);
		count += 2;
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI MyThread2(LPVOID arg)
{
	for (int i = 0; i < MAXCNT; i++) {
		EnterCriticalSection(&cs);
		count -= 2;
		LeaveCriticalSection(&cs);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	// �Ӱ� ���� �ʱ�ȭ
	InitializeCriticalSection(&cs);

	// ������ �� �� ����
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, MyThread2, NULL, 0, NULL);

	// ������ �� �� ���� ���
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	// �Ӱ� ���� ����
	DeleteCriticalSection(&cs);

	// ��� ���
	printf("count = %d\n", count);
	return 0;
}