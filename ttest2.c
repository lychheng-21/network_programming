#include <windows.h>
#include <stdio.h>

DWORD WINAPI MyThread(LPVOID arg)
{
	while (1);
	return 0;
}

int main()
{
	// �켱���� ���� ������ ����Ѵ�.
	printf("�켱����: %d ~ %d\n", THREAD_PRIORITY_IDLE,
		THREAD_PRIORITY_TIME_CRITICAL);

	// CPU ������ �˾Ƴ���.
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// CPU ������ŭ �����带 �����Ѵ�.
	for (int i = 0; i < (int)si.dwNumberOfProcessors; i++) {
		// �����带 �����Ѵ�.
		HANDLE hThread = CreateThread(NULL, 0, MyThread, NULL, 0, NULL);
		// �켱������ ���� �����Ѵ�.
		SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
		CloseHandle(hThread);
	}

	// �켱������ ���� �����Ѵ�.
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
	Sleep(1000);
	printf("�� ������ ����!\n");
	return 0;
}