//#include "DxLib.h"
//#include "Scene/SceneManager.h"
//#include <thread>
//#include <mutex>
//#include <string>
//
//// �f�o�b�O�p�̃e�L�X�g
//std::string debugText = "Initial Debug Info";  // �����̃f�o�b�O���
//std::mutex debugTextMutex;  // �f�o�b�O�����X���b�h�Z�[�t�ɂ��邽�߂̃~���[�e�b�N�X
//
//// �f�o�b�O���̍X�V�֐�
//// �����Ŏ󂯎�����V�����f�o�b�O�����A�X���b�h�Z�[�t�ɍX�V���܂��B
//void UpdateDebugInfo(const std::string& info) {
//    // debugTextMutex���g���āA�����X���b�h����̋�����h�~
//    std::lock_guard<std::mutex> lock(debugTextMutex);
//    debugText = info;  // �f�o�b�O�����X�V
//
//    // �f�o�b�O�E�B���h�E������
//    HWND hwnd = FindWindowA("DebugWindowClass", NULL);
//    if (hwnd) {
//        // �E�B���h�E��������΁A�ĕ`���v��
//        InvalidateRect(hwnd, NULL, TRUE);
//    }
//}
//
//// �E�B���h�E�v���V�[�W��
//// �E�B���h�E�ɑ���ꂽ���b�Z�[�W����������֐��ł��B
//// �E�B���h�E���ǂ̂悤�ɓ��삷�邩�i�`���T�C�Y�ύX���j���Ǘ����܂��B
//LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//    PAINTSTRUCT ps;  // �`��p�̍\����
//    HDC hdc;  // �f�o�C�X�R���e�L�X�g�i�`�揈���Ɏg�p�j
//
//    switch (message) {
//    case WM_PAINT:
//        // �E�B���h�E�̍ĕ`�揈��
//        hdc = BeginPaint(hWnd, &ps);
//        {
//            RECT rect;
//            GetClientRect(hWnd, &rect);  // �E�B���h�E�̃N���C�A���g�̈�̃T�C�Y���擾
//
//            // ���F�̃u���V���쐬
//            HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
//            // �w�i�𔒐F�œh��Ԃ�
//            FillRect(hdc, &rect, whiteBrush);
//
//            // �f�o�b�O����`��i�X���b�h�Z�[�t�ɂ��邽�߃~���[�e�b�N�X�Ń��b�N�j
//            std::lock_guard<std::mutex> lock(debugTextMutex);
//            TextOut(hdc, 10, 10, debugText.c_str(), debugText.size()); // �f�o�b�O����(10,10)���W�ɕ\��
//        }
//        EndPaint(hWnd, &ps);
//        break;
//
//    case WM_SIZE:
//        // �E�B���h�E�T�C�Y�ύX���ɍĕ`���v��
//        InvalidateRect(hWnd, NULL, TRUE);
//        break;
//
//    case WM_DESTROY:
//        // �E�B���h�E������ꂽ�Ƃ��A�A�v���P�[�V�����I���̃��b�Z�[�W�𑗂�
//        PostQuitMessage(0);
//        break;
//
//    default:
//        // �f�t�H���g�̃��b�Z�[�W����
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// �f�o�b�O�E�B���h�E�����E���b�Z�[�W���[�v�֐�
//// �f�o�b�O�E�B���h�E�𐶐����A���b�Z�[�W���[�v���J�n����֐�
//void DebugWindowThread(HINSTANCE hInstance) {
//    // �E�B���h�E�N���X�̐ݒ�
//    WNDCLASS wc = { 0 };
//    wc.lpfnWndProc = DebugWndProc;  // �E�B���h�E�v���V�[�W���i���b�Z�[�W�����֐��j
//    wc.hInstance = hInstance;  // �C���X�^���X�n���h��
//    wc.lpszClassName = "DebugWindowClass";  // �E�B���h�E�N���X��
//
//    RegisterClass(&wc);  // �E�B���h�E�N���X��o�^
//
//    // �E�B���h�E�̍쐬
//    HWND debugWnd = CreateWindowEx(
//        0,
//        "DebugWindowClass",  // �E�B���h�E�N���X��
//        "Debug Window",      // �E�B���h�E�̃^�C�g��
//        WS_OVERLAPPEDWINDOW, // �E�B���h�E�̃X�^�C���i�W���I�ȃE�B���h�E�j
//        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, // �����ʒu�ƃT�C�Y
//        NULL, NULL, hInstance, NULL
//    );
//
//    // �E�B���h�E�̕\��
//    ShowWindow(debugWnd, SW_SHOW);
//
//    // ���b�Z�[�W���[�v
//    MSG msg;
//    while (GetMessage(&msg, nullptr, 0, 0)) {
//        TranslateMessage(&msg);  // ���b�Z�[�W�̖|��
//        DispatchMessage(&msg);   // ���b�Z�[�W�̃f�B�X�p�b�`
//    }
//}
//
//// �f�o�b�O�E�B���h�E��ʃX���b�h�ŋN������֐�
//// ���C���X���b�h���u���b�N�����Ƀf�o�b�O�E�B���h�E��ʃX���b�h�ŋN�����邽�߂̊֐�
//void StartDebugWindow(HINSTANCE hInstance) {
//    // �ʃX���b�h�Ńf�o�b�O�E�B���h�E���N��
//    std::thread debugThread(DebugWindowThread, hInstance);
//    debugThread.detach();  // ���C���X���b�h�ɉe����^���Ȃ��悤�X���b�h���f�^�b�`
//}
//
//
//// �v���O������ WinMain ����n�܂�܂�
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	SetWindowText("TakeruHertus");
//
//	SetGraphMode(1280, 740, 16);//�Q�[����ʂ̊K�w�x
//	SetWindowSize(1280, 740);//�\����̃T�C�Y
//
//	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
//	ChangeWindowMode(true);
//
//	if (DxLib_Init() == -1)		// �c�w���C�u��������������
//	{
//		return -1;			// �G���[���N�����璼���ɏI��
//	}
//
//	SetDrawScreen(DX_SCREEN_BACK);
//	
//	//�V�[���}�l�[�W���[�̎Q��
//	SceneManager& sceneManager = SceneManager::GetInstance();
//	sceneManager.Init();//�V�[���̏�����
//	
//	// �f�o�b�O�E�B���h�E�̊J�n
//	StartDebugWindow(hInstance);
//	
//	VECTOR position = VGet(10.0f, 20.0f, 30.0f);
//
//	// �Q�[�����[�v
//	while (ProcessMessage() != -1)
//	{
//		// ���̃t���[���̊J�n�������o���Ă���
//		LONGLONG start = GetNowHiPerformanceCount();
//
//		// �`����s���O�ɉ�ʂ��N���A����
//		ClearDrawScreen();
//
//		// �Q�[���̏���
//		sceneManager.Update();//�V�[���̍X�V
//		sceneManager.Draw();//�V�[���̕`��
//
//		if(position.x >= 300.0f)
//        {
//            position.x = 0.0f;
//        }
//
//		position.x++;
//
//#ifdef _DEBUG
//		// �v���C���[�̈ʒu�� (x, y, z) ���Ɖ���
//		std::string newDebugInfo = "Player Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + ")";
//       
//
//        UpdateDebugInfo(newDebugInfo);
//
//		
//#endif // _DEBUG
//
//		// ��ʂ��؂�ւ��̂�҂�
//		ScreenFlip();
//
//		// esc�L�[�ŃQ�[���I��
//		if (CheckHitKey(KEY_INPUT_ESCAPE))
//		{
//			break;
//		}
//
//		
//		// FPS60�ɌŒ肷��
//		while (GetNowHiPerformanceCount() - start < 16667)
//		{
//			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
//		}
//	}
//
//	sceneManager.Final();//�V�[���̉��
//
//	DxLib_End();				// �c�w���C�u�����g�p�̏I������
//
//	return 0;				// �\�t�g�̏I�� 
//}


#include "DxLib.h"
#include "Scene/SceneManager.h"
#include <thread>
#include <mutex>
#include <string>
#include <vector>
// �f�o�b�O�p�̃e�L�X�g���X�g
std::vector<std::string> debugTexts = { "Initial Debug Info" };
std::mutex debugTextMutex;
// �f�o�b�O����ǉ�����֐�
void AddDebugInfo(const std::string& info) {
    std::lock_guard<std::mutex> lock(debugTextMutex);
    debugTexts.push_back(info);
    HWND hwnd = FindWindowA("DebugWindowClass", NULL);
    if (hwnd) {
        InvalidateRect(hwnd, NULL, TRUE); // �E�B���h�E���ĕ`��
    }
}
// �f�o�b�O�����X�V����֐�
void UpdateDebugInfo(int index, const std::string& info) {
    std::lock_guard<std::mutex> lock(debugTextMutex);
    if (index < debugTexts.size()) {
        debugTexts[index] = info;
    }
    else {
        debugTexts.push_back(info);
    }
    HWND hwnd = FindWindowA("DebugWindowClass", NULL);
    if (hwnd) {
        InvalidateRect(hwnd, NULL, TRUE); // �E�B���h�E���ĕ`��
    }
}
// �f�o�b�O�E�B���h�E�̃E�B���h�E�v���V�[�W��
LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
            FillRect(hdc, &rect, whiteBrush);
            std::lock_guard<std::mutex> lock(debugTextMutex);
            int y = 10;
            for (const auto& text : debugTexts) {
                TextOut(hdc, 10, y, text.c_str(), text.size());
                y += 20;
            }
        }
        EndPaint(hWnd, &ps);
        break;
    case WM_SIZE:
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// �f�o�b�O�E�B���h�E�̐����ƃ��b�Z�[�W���[�v�����s����֐�
void DebugWindowThread(HINSTANCE hInstance) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DebugWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "DebugWindowClass";
    RegisterClass(&wc);
    HWND debugWnd = CreateWindowEx(
        0,
        "DebugWindowClass",
        "Debug Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL
    );
    ShowWindow(debugWnd, SW_SHOW);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
// �f�o�b�O�E�B���h�E��ʃX���b�h�ŋN������֐�
void StartDebugWindow(HINSTANCE hInstance) {
    std::thread debugThread(DebugWindowThread, hInstance);
    debugThread.detach();
}



// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �Q�[���E�B���h�E�̏����ݒ�
    SetWindowText("TakeruHertus");
    SetGraphMode(1280, 740, 16);
    SetWindowSize(1280, 740);
    ChangeWindowMode(TRUE);
    // DxLib�̏�����
    if (DxLib_Init() == -1) {
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);
    // �V�[���}�l�[�W���[�̏�����
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.Init();

    VECTOR position = VGet(0, 0, 0);
    VECTOR count = VGet(0, 0, 0);

    // �f�o�b�O�E�B���h�E�̋N��
    StartDebugWindow(hInstance);
    // �Q�[�����[�v
    while (ProcessMessage() != -1)
    {
        // �Q�[�������̊J�n�������L�^
        LONGLONG start = GetNowHiPerformanceCount();
        // �`���ʂ��N���A
        ClearDrawScreen();
        // �V�[���̍X�V�ƕ`��
        sceneManager.Update();
        sceneManager.Draw();

        if (position.x >= 300.0f)
        {
            position.x = 0.0f;
        }
            
        position.x++;


        if (count.x >= 300.0f)
        {
            count.x = 0.0f;
        }

        count.x++;
        

#ifdef _DEBUG
        // �f�o�b�O���̍X�V�i��Ƃ���FPS��\���j
        UpdateDebugInfo(0, "FPS: " + std::to_string(1000.0 / (GetNowHiPerformanceCount() - start + 1)));

        UpdateDebugInfo(1, "PlayerDebugData");
        UpdateDebugInfo(2, "Player Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + ")");
        UpdateDebugInfo(3, "Player Count: (" + std::to_string(count.x) + ", " + std::to_string(count.y) + ", " + std::to_string(count.z) + ")");

       
#endif
        // ��ʂ̃t���b�v
        ScreenFlip();
        // ESC�L�[�ŃQ�[���I��
        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }
        // FPS��60�ɌŒ�
        while (GetNowHiPerformanceCount() - start < 16667) {}
    }
    // �V�[���̏I��������DxLib�̏I��
    sceneManager.Final();
    DxLib_End();
    return 0;
}