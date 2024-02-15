#include "NewGameScene.h"
#include"DxLib.h"
#include <math.h>
#include "GameMainScene.h"
#include "../Utility/InputControl.h"

NewGameScene::NewGameScene()
{
	Initialize();
}

NewGameScene::~NewGameScene()
{

}

//初期化処理
void NewGameScene::Initialize()
{
	//パワー決定
	Nowpower = 0;

	Flying = 0;
	Altitude = 0;
	Accel = 0;

	phase = 1;
	anim_time = 0;
	Rand_time = 0;

	//画像の読み込み
	int resultStr = LoadDivGraph("Resource/images/Stringimage.png", 2, 2, 1, 100, 100, String_image);
	int resultExp = LoadDivGraph("Resource/images/explosion.png", 16, 4, 4, 32, 32, Explosion_image);

	if (resultStr == -1) 
	{
		throw("文字画像が無い！");
	}

	Back_image[0] = LoadGraph("Resource/images/blowback.png");
	Back_image[1] = LoadGraph("Resource/images/blowback_a.png");
	Back_image[2] = LoadGraph("Resource/images/sky.png");
	Back_image[3] = LoadGraph("Resource/images/ground.png");

	// オブジェクトの生成
	eventobj = new Eventobj;

	// オブジェクトの初期化
	eventobj->Initialize(0, false, 99);
	
	//BGM読み込み
	boomSE = LoadSoundMem("Resource/sounds/nc250095.mp3");
	bakuSE= LoadSoundMem("Resource/sounds/maou_se_onepoint03.mp3");
	resultBGM= LoadSoundMem("Resource/sounds/maou_se_jingle05.mp3");
	//エラーチェック
	if (boomSE == -1)
	{
		throw("Resource/sounds/nc250095.mp3がありません\n");
	}
	if (bakuSE == -1)
	{
		throw("Resource/sounds/maou_se_onepoint03.mp3がありません\n");
	}
	if (resultBGM == -1)
	{
		throw("Resource/sounds/maou_se_jingle05.mp3がありません\n");
	}

	NGS_Data();

}

//更新処理
eSceneType NewGameScene::Update()
{
	//フェーズ１：「笑」を吹き飛ばす
	if (phase == 1) 
	{
		
		if (90 < anim_time)
		{
			//パワーを消費して「爆」の文字を大きくする
			if (0 < Power)
			{

				//受け取ったパワーを飛行用のパワーに変換
				Power -= 0.3;
				Nowpower += 0.3;

				//パワーが0になったら一旦アニメーションをリセット
				if (Power < 0)
				{
					Power = 0;
					anim_time = 0;
					PlaySoundMem(boomSE, DX_PLAYTYPE_BACK);

					//最低限のパワーを付与する(一瞬で墜落するのを防ぐため)
					if (Nowpower < 20)Nowpower = 20;
				}
			}
			//爆発する演出
			else
			{
				//計測開始する
				Flying += 100;
				Record += 90 + GetRand(20);

				if (60 < anim_time) 
				{
					phase++;
					anim_time = 0;

					//最初のランダムイベントをセット
					Rand_time = GetRand(60) + 120;

				}
			}
		}
		else if (0 < Power)
		{
			//BGMが流れてないときに再生
			if (CheckSoundMem(bakuSE) != TRUE)
			{
				PlaySoundMem(bakuSE, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		
	}
	//飛行
	else if (phase == 2) 
	{
		//パワーを消費する
		Nowpower -= 0.07;
		if (0 < Nowpower) 
		{
			//パワーがあるなら上向きの加速度を加える
			Accel = 7;
		}
		else
		{
			//パワーが無くなったなら加速度を徐々に下向きにする
			Accel -= 0.1;
			if (Accel < -10)Accel = -10;
		}

		//加速度に応じて現在の高度を更新
		Altitude += Accel;

		Flying += 100;
		Record += 60 + GetRand(20);

		//ランダムイベント
		Rand_time--;

		//イベントオブジェクト更新
		eventobj->Update(Accel);
		Record += eventobj->GetScore();

		if (Rand_time <= 0)
		{
			//次のランダムイベントをセット
			Rand_time = GetRand(60) + 120;

			if (GetRand(99) < 75)
			{
				//パワーが一定以上の場合
				if (10 < Nowpower)
				{
					//イベントオブジェクト有効化
					eventobj->Initialize(Nowpower, true, GetRand(4));
				}
				//落下速度と高度が十分にある場合
				else if (Accel < -5 && 240 < Altitude)
				{
					//イベントオブジェクト有効化
					eventobj->Initialize(Nowpower, true, GetRand(4));
				}
			}
		}

		//高度が一定以下になったらフェーズ変更
		if (Altitude < 0) 
		{
			Altitude = 0;
			anim_time = 0;
			phase++;
		}
	}
	else if (phase == 3) 
	{
		if (anim_time < 15) 
		{
			Flying += 100;
			Record += 60 + GetRand(20);
		}

		if (120 < anim_time)
		{
			return eSceneType::E_RESULT;
		}
	}

	anim_time++;
	return GetNowScene();
}

//描画処理
void NewGameScene::Draw() const
{

	//爆破
	if (phase == 1)
	{
		//背景画像
		if (0 < Power || anim_time < 20)DrawGraph(0, 0, Back_image[0], false);
		else DrawGraph(0, 0, Back_image[1], TRUE);

		//文字画像
		float size = Nowpower * 0.05 + 1;
		int num = anim_time / 4;
		//爆発するまで「爆」の文字を表示
		if (0 < Power || num < 4) DrawRotaGraph(640 / 2 - (50 * size), 480 / 2, size, 0, String_image[0], true);

		//「笑」の文字を表示・移動
		if (0 < Power || anim_time < 12)DrawRotaGraph(640 / 2 + 50, 480 / 2, 1.f, 0, String_image[1], true);
		else DrawRotaGraph(640 / 2 + 50 + (anim_time - 12) * 60, 480 / 2 - (anim_time - 12) * 50, 1.f, (anim_time - 12), String_image[1], true);

		//爆発
		size = Nowpower * 0.05 + 1;
		if (Power <= 0 && num < 16)
		{
			DrawRotaGraph(640 / 2 - (50 * size), 480 / 2, size * 7, 0, Explosion_image[num], true);
		}

		int fadein = anim_time * 5;
		if (300 < fadein || Power <= 0)fadein = 300;

		SetFontSize(30);
		DrawString(-250 + fadein, 20, "集めたパワー", 0x000000);

		SetFontSize(64);
		DrawFormatString(-250 + fadein, 50, 0x000000, "%.1f", Power);

	}
	//飛行
	else if (phase == 2)
	{
		//背景画像
		DrawGraph((int)(-Flying * 0.15) % 640, Altitude % 480, Back_image[2], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640, Altitude % 480 - 480, Back_image[2], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640 + 640, Altitude % 480, Back_image[2], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640 + 640, Altitude % 480 - 480, Back_image[2], TRUE);

		//「笑」の文字
		DrawRotaGraph(640 / 2, 480 / 2, 1.f, anim_time * 0.3, String_image[1], true);

		// イベントオブジェクト描画
		eventobj->Draw();

		//記録表示
		SetFontSize(30);
		DrawString(50, 20, "飛距離", 0xffffff);

		SetFontSize(64);
		DrawFormatString(50, 50, 0xffffff, "%d m", Record);
	}
	//着地
	else if (phase == 3)
	{
		//背景画像
		DrawGraph((int)(-Flying * 0.15) % 640, Altitude % 480, Back_image[2], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640, Altitude % 480 - 480, Back_image[2], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640 + 640, Altitude % 480, Back_image[2], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640 + 640, Altitude % 480 - 480, Back_image[2], TRUE);

		//「笑」の文字
		if (anim_time < 15)DrawRotaGraph(640 / 2, 480 / 2, 1.f, anim_time * 0.3, String_image[1], true);
		else DrawRotaGraph(640 / 2, 480 / 2, 1.f, 1, String_image[1], true);

		//地面を描画する
		int Ypos = 480 - (480 / 15) * anim_time;
		if (Ypos < 0)Ypos = 0;
		DrawGraph(0, Ypos, Back_image[3], true);

		//爆発の表示コマ決定
		int num = (anim_time - 15) / 4;

		if (15 < anim_time && num < 16)
		{
			//爆発
			DrawRotaGraph(640 / 2, 480 / 2, 15, 0, Explosion_image[num], true);
		}

		//記録表示
		SetFontSize(30);
		DrawString(50, 20, "飛距離", 0xffffff);

		SetFontSize(64);
		DrawFormatString(50, 50, 0xffffff, "%d m", Record);
	}
}

//終了処理
void NewGameScene::Finalize()
{
	//ランキングデータの読み込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/power_data.csvが開けませんでした\n");
	}

	//対象ファイルに書き込み

	fprintf(fp, "%d,\n", Record);
	
	//BGMが流れてないときに再生
		if (CheckSoundMem(resultBGM) != TRUE)
		{
			PlaySoundMem(resultBGM, DX_PLAYTYPE_BACK,TRUE);
		}

	//ファイルクローズ
	fclose(fp);

	//動的確保領域の解放
	delete eventobj;
}

//現在のシーン情報取得
eSceneType NewGameScene::GetNowScene() const
{
	return eSceneType::E_NGS;
}

void NewGameScene::NGS_Data()
{
	//�t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/power_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("resource/dat/power_data.csvが開けませんでした\n");
	}

	int power;
	//���ʂ��ǂݍ���
	fscanf_s(fp, "%6d,\n", &power);

	Power = (float)power;

	//�t�@�C���N���[�Y
	fclose(fp);
}
