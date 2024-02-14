#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include <math.h>

GameMainScene::GameMainScene() :back_ground(NULL), player(nullptr),
enemy(nullptr) {
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{

	// 画像の読み込み
	back_ground = LoadGraph("Resource/images/main.bmp");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 30, 30, enemy_image);

	enemy_kusa = LoadGraph("Resource/images/Kusa.bmp");
	enemy_hayashi = LoadGraph("Resource/images/Hayashi.bmp");
	enemy_mori = LoadGraph("Resource/images/Mori.bmp");

	// エラーチェック
	if (back_ground == -1) {
		throw("画像back.bmpがありません\n");
	}
	if (result == -1) {
		throw("画像car.bmpがありません\n");
	}

	// オブジェクトの生成
	player = new Player;
	enemy = new Enemy * [10];

	// オブジェクトの初期化
	player->Initialize();

	for (int i = 0; i < 10; i++) {
		enemy[i] = nullptr;
	}
}

eSceneType GameMainScene::Update()
{
	// プレイヤーの更新
	player->Update();

	// 敵生成処理
	int time = player->GetTime();

	if (time % 25 == 0) {
		for (int i = 0; i < 10; i++) {
			// 値がnullなら
			if (enemy[i] == nullptr) {
				int type = GetRand(3) % 3;
				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}

	// 敵の更新と当たり判定チェック
	for (int i = 0; i < 10; i++) 
	{
		// 値がnullでないなら
		if (enemy[i] != nullptr) 
		{
			enemy[i]->Update(5);

			// 画面外に行ったら、敵を消去してスコア加算
			if (enemy[i]->GetLocation().y >= 640.0f) 
			{
				enemy[i]->Finalize();
				delete enemy[i];	// メモリ開放
				enemy[i] = nullptr;// nullにする
			}

			//当たり判定の確認
			if (IsHitCheck(player, enemy[i]))
			{
				enemy_count[enemy[i]->GetType()]++;
				power += enemy[i]->GetType() + 1;
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	// プレイヤーの値が０未満なら、ニューゲームに遷移する
	if (player->GetTime() < 0.0f)
	{
		return eSceneType::E_NGS;
	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	DrawGraph(0, 0, back_ground, TRUE);

	// 敵の描画
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	// プレイヤーの描画
	player->Draw();

	// UIの描画
	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(16);
	DrawFormatString(510, 20, GetColor(0, 0, 0), "パワー");
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%d", power);
	DrawFormatString(510, 70, GetColor(0, 0, 0), "取れた数");


	DrawGraph(505, 96, enemy_kusa, TRUE);
	DrawGraph(555, 96, enemy_hayashi, TRUE);
	DrawGraph(605, 96, enemy_mori, TRUE);

	for (int i = 0; i < 3; i++) 
	{
		DrawFormatString(510 + (i*50),140,GetColor(255, 255, 255), "%03d",enemy_count[i]);
	}


	// 燃料ゲージの描画
	float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "TIME");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetTime() * 100 / 1800), fy +
		40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}

void GameMainScene::Finalize()
{
	// 動的確保したオブジェクトを消去する
	player->Finalize();
	delete player;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
	delete[] enemy;

	//ランキングデータの読み込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/power_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/power_data.csvが開けませんでした\n");
	}

	//対象ファイルに書き込み
	
	fprintf(fp, "%d,\n", power);
	

	//ファイルクローズ
	fclose(fp);
}

// 現在のシーン情報取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

// あたり判定処理（プレイヤーと敵）
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{

	// 敵情報がなければ、当たり判定を無視する
	if (e == nullptr) {
		return false;
	}

	// 位置情報の差分取得
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	// 当たり判定サイズの大きさを取得
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
	// コリジョンデータより位置情報の差分が小さいなら、ヒット判定
	return ((fabs(diff_location.x)<box_ex.x)&&(fabsf(diff_location.y)<box_ex.y));
}
