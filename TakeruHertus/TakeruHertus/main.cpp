//#include "DxLib.h"
//#include "Scene/SceneManager.h"
//#include <thread>
//#include <mutex>
//#include <string>
//
//// デバッグ用のテキスト
//std::string debugText = "Initial Debug Info";  // 初期のデバッグ情報
//std::mutex debugTextMutex;  // デバッグ情報をスレッドセーフにするためのミューテックス
//
//// デバッグ情報の更新関数
//// 引数で受け取った新しいデバッグ情報を、スレッドセーフに更新します。
//void UpdateDebugInfo(const std::string& info) {
//    // debugTextMutexを使って、複数スレッドからの競合を防止
//    std::lock_guard<std::mutex> lock(debugTextMutex);
//    debugText = info;  // デバッグ情報を更新
//
//    // デバッグウィンドウを検索
//    HWND hwnd = FindWindowA("DebugWindowClass", NULL);
//    if (hwnd) {
//        // ウィンドウが見つかれば、再描画を要求
//        InvalidateRect(hwnd, NULL, TRUE);
//    }
//}
//
//// ウィンドウプロシージャ
//// ウィンドウに送られたメッセージを処理する関数です。
//// ウィンドウがどのように動作するか（描画やサイズ変更等）を管理します。
//LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//    PAINTSTRUCT ps;  // 描画用の構造体
//    HDC hdc;  // デバイスコンテキスト（描画処理に使用）
//
//    switch (message) {
//    case WM_PAINT:
//        // ウィンドウの再描画処理
//        hdc = BeginPaint(hWnd, &ps);
//        {
//            RECT rect;
//            GetClientRect(hWnd, &rect);  // ウィンドウのクライアント領域のサイズを取得
//
//            // 白色のブラシを作成
//            HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
//            // 背景を白色で塗りつぶし
//            FillRect(hdc, &rect, whiteBrush);
//
//            // デバッグ情報を描画（スレッドセーフにするためミューテックスでロック）
//            std::lock_guard<std::mutex> lock(debugTextMutex);
//            TextOut(hdc, 10, 10, debugText.c_str(), debugText.size()); // デバッグ情報を(10,10)座標に表示
//        }
//        EndPaint(hWnd, &ps);
//        break;
//
//    case WM_SIZE:
//        // ウィンドウサイズ変更時に再描画を要求
//        InvalidateRect(hWnd, NULL, TRUE);
//        break;
//
//    case WM_DESTROY:
//        // ウィンドウが閉じられたとき、アプリケーション終了のメッセージを送る
//        PostQuitMessage(0);
//        break;
//
//    default:
//        // デフォルトのメッセージ処理
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// デバッグウィンドウ生成・メッセージループ関数
//// デバッグウィンドウを生成し、メッセージループを開始する関数
//void DebugWindowThread(HINSTANCE hInstance) {
//    // ウィンドウクラスの設定
//    WNDCLASS wc = { 0 };
//    wc.lpfnWndProc = DebugWndProc;  // ウィンドウプロシージャ（メッセージ処理関数）
//    wc.hInstance = hInstance;  // インスタンスハンドル
//    wc.lpszClassName = "DebugWindowClass";  // ウィンドウクラス名
//
//    RegisterClass(&wc);  // ウィンドウクラスを登録
//
//    // ウィンドウの作成
//    HWND debugWnd = CreateWindowEx(
//        0,
//        "DebugWindowClass",  // ウィンドウクラス名
//        "Debug Window",      // ウィンドウのタイトル
//        WS_OVERLAPPEDWINDOW, // ウィンドウのスタイル（標準的なウィンドウ）
//        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, // 初期位置とサイズ
//        NULL, NULL, hInstance, NULL
//    );
//
//    // ウィンドウの表示
//    ShowWindow(debugWnd, SW_SHOW);
//
//    // メッセージループ
//    MSG msg;
//    while (GetMessage(&msg, nullptr, 0, 0)) {
//        TranslateMessage(&msg);  // メッセージの翻訳
//        DispatchMessage(&msg);   // メッセージのディスパッチ
//    }
//}
//
//// デバッグウィンドウを別スレッドで起動する関数
//// メインスレッドをブロックせずにデバッグウィンドウを別スレッドで起動するための関数
//void StartDebugWindow(HINSTANCE hInstance) {
//    // 別スレッドでデバッグウィンドウを起動
//    std::thread debugThread(DebugWindowThread, hInstance);
//    debugThread.detach();  // メインスレッドに影響を与えないようスレッドをデタッチ
//}
//
//
//// プログラムは WinMain から始まります
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	SetWindowText("TakeruHertus");
//
//	SetGraphMode(1280, 740, 16);//ゲーム画面の階層度
//	SetWindowSize(1280, 740);//表示上のサイズ
//
//	// 一部の関数はDxLib_Init()の前に実行する必要がある
//	ChangeWindowMode(true);
//
//	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
//	{
//		return -1;			// エラーが起きたら直ちに終了
//	}
//
//	SetDrawScreen(DX_SCREEN_BACK);
//	
//	//シーンマネージャーの参照
//	SceneManager& sceneManager = SceneManager::GetInstance();
//	sceneManager.Init();//シーンの初期化
//	
//	// デバッグウィンドウの開始
//	StartDebugWindow(hInstance);
//	
//	VECTOR position = VGet(10.0f, 20.0f, 30.0f);
//
//	// ゲームループ
//	while (ProcessMessage() != -1)
//	{
//		// このフレームの開始時刻を覚えておく
//		LONGLONG start = GetNowHiPerformanceCount();
//
//		// 描画を行う前に画面をクリアする
//		ClearDrawScreen();
//
//		// ゲームの処理
//		sceneManager.Update();//シーンの更新
//		sceneManager.Draw();//シーンの描画
//
//		if(position.x >= 300.0f)
//        {
//            position.x = 0.0f;
//        }
//
//		position.x++;
//
//#ifdef _DEBUG
//		// プレイヤーの位置が (x, y, z) だと仮定
//		std::string newDebugInfo = "Player Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + ")";
//       
//
//        UpdateDebugInfo(newDebugInfo);
//
//		
//#endif // _DEBUG
//
//		// 画面が切り替わるのを待つ
//		ScreenFlip();
//
//		// escキーでゲーム終了
//		if (CheckHitKey(KEY_INPUT_ESCAPE))
//		{
//			break;
//		}
//
//		
//		// FPS60に固定する
//		while (GetNowHiPerformanceCount() - start < 16667)
//		{
//			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
//		}
//	}
//
//	sceneManager.Final();//シーンの解放
//
//	DxLib_End();				// ＤＸライブラリ使用の終了処理
//
//	return 0;				// ソフトの終了 
//}


#include "DxLib.h"
#include "Scene/SceneManager.h"
#include <thread>
#include <mutex>
#include <string>
#include <vector>
// デバッグ用のテキストリスト
std::vector<std::string> debugTexts = { "Initial Debug Info" };
std::mutex debugTextMutex;
// デバッグ情報を追加する関数
void AddDebugInfo(const std::string& info) {
    std::lock_guard<std::mutex> lock(debugTextMutex);
    debugTexts.push_back(info);
    HWND hwnd = FindWindowA("DebugWindowClass", NULL);
    if (hwnd) {
        InvalidateRect(hwnd, NULL, TRUE); // ウィンドウを再描画
    }
}
// デバッグ情報を更新する関数
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
        InvalidateRect(hwnd, NULL, TRUE); // ウィンドウを再描画
    }
}
// デバッグウィンドウのウィンドウプロシージャ
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
// デバッグウィンドウの生成とメッセージループを実行する関数
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
// デバッグウィンドウを別スレッドで起動する関数
void StartDebugWindow(HINSTANCE hInstance) {
    std::thread debugThread(DebugWindowThread, hInstance);
    debugThread.detach();
}



// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ゲームウィンドウの初期設定
    SetWindowText("TakeruHertus");
    SetGraphMode(1280, 740, 16);
    SetWindowSize(1280, 740);
    ChangeWindowMode(TRUE);
    // DxLibの初期化
    if (DxLib_Init() == -1) {
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);
    // シーンマネージャーの初期化
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.Init();

    VECTOR position = VGet(0, 0, 0);
    VECTOR count = VGet(0, 0, 0);

    // デバッグウィンドウの起動
    StartDebugWindow(hInstance);
    // ゲームループ
    while (ProcessMessage() != -1)
    {
        // ゲーム処理の開始時刻を記録
        LONGLONG start = GetNowHiPerformanceCount();
        // 描画画面をクリア
        ClearDrawScreen();
        // シーンの更新と描画
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
        // デバッグ情報の更新（例としてFPSを表示）
        UpdateDebugInfo(0, "FPS: " + std::to_string(1000.0 / (GetNowHiPerformanceCount() - start + 1)));

        UpdateDebugInfo(1, "PlayerDebugData");
        UpdateDebugInfo(2, "Player Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + ")");
        UpdateDebugInfo(3, "Player Count: (" + std::to_string(count.x) + ", " + std::to_string(count.y) + ", " + std::to_string(count.z) + ")");

       
#endif
        // 画面のフリップ
        ScreenFlip();
        // ESCキーでゲーム終了
        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }
        // FPSを60に固定
        while (GetNowHiPerformanceCount() - start < 16667) {}
    }
    // シーンの終了処理とDxLibの終了
    sceneManager.Final();
    DxLib_End();
    return 0;
}