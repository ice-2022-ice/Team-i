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

	//画像の読み込み
	int resultStr = LoadDivGraph("Resource/images/Stringimage.png", 2, 2, 1, 100, 100, String_image);
	int resultExp = LoadDivGraph("Resource/images/explosion.png", 16, 4, 4, 32, 32, Explosion_image);

	if (resultStr == -1) 
	{
		throw("文字画像が無い！");
	}

	Back_image[0] = LoadGraph("Resource/images/blowback.png");
	Back_image[1] = LoadGraph("Resource/images/sky.png");
	Back_image[2] = LoadGraph("Resource/images/ground.png");
	
	NGS_Data();
}
//更新処理
eSceneType NewGameScene::Update()
{
	//フェーズ１：「笑」を吹き飛ばす
	if (phase == 1) 
	{
		if (120 < anim_time) 
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

					//最低限のパワーを付与する(一瞬で墜落するのを防ぐため)
					if (Nowpower < 20)Nowpower = 20;
				}
			}
			//爆発する演出
			else
			{
				Flying += 90 + GetRand(20);
				if (60 < anim_time) 
				{
					phase++;
					anim_time = 0;
				}
			}
		}
	}
	//飛行
	else if (phase == 2) 
	{
		//パワーを消費する
		Nowpower -= 0.1;
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
		Flying += 60 + GetRand(20);

		//高度が0になったらフェーズ変更
		if (Altitude < 0) 
		{
			Altitude = 0;
			anim_time = 0;
			phase++;
		}
	}
	else if (phase == 3) 
	{
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
		DrawGraph(0, 0, Back_image[0], TRUE);

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
			DrawRotaGraph(640 / 2 - (50 * size), 480 / 2, size + 25, 0, Explosion_image[num], true);
		}

		SetFontSize(30);
		DrawString(50, 20, "集めたパワー", 0xffffff);

		SetFontSize(64);
		DrawFormatString(50, 50, 0xffffff, "%.1f", Power);
	}
	//飛行
	else if (phase == 2)
	{
		//背景画像
		DrawGraph((int)(-Flying * 0.15) % 640, Altitude % 480, Back_image[1], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640, Altitude % 480 - 480, Back_image[1], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640 + 640, Altitude % 480, Back_image[1], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640 + 640, Altitude % 480 - 480, Back_image[1], TRUE);

		//「笑」の文字
		DrawRotaGraph(640 / 2, 480 / 2, 1.f, anim_time * 0.3, String_image[1], true);

		//記録表示
		SetFontSize(30);
		DrawString(50, 20, "飛距離", 0xffffff);
		DrawFormatString(200, 20, 0xffffff, "%.1f", Nowpower);

		SetFontSize(64);
		DrawFormatString(50, 50, 0xffffff, "%d m", Flying);
	}
	//着地
	else if (phase == 3) 
	{
		//背景画像
		DrawGraph((int)(-Flying * 0.15) % 640, Altitude % 480, Back_image[1], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640, Altitude % 480 - 480, Back_image[1], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640 + 640, Altitude % 480, Back_image[1], TRUE);
		DrawGraph((int)(-Flying * 0.15) % 640 + 640, Altitude % 480 - 480, Back_image[1], TRUE);

		//「笑」の文字
		DrawRotaGraph(640 / 2, 480 / 2, 1.f, 1, String_image[1], true);

		int Ypos = 480 - (480 / 15) * anim_time;
		if (Ypos < 0)Ypos = 0;
		DrawGraph(0, Ypos, Back_image[2], true);

		//記録表示
		SetFontSize(30);
		DrawString(50, 20, "飛距離", 0xffffff);
		DrawFormatString(200, 20, 0xffffff, "%.1f", Nowpower);

		SetFontSize(64);
		DrawFormatString(50, 50, 0xffffff, "%d m", Flying);
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

	fprintf(fp, "%d,\n", Flying);

	//ファイルクローズ
	fclose(fp);
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
		throw("resource/dat/power_data.csv���ǂݍ��߂܂���\n");
	}

	int power;
	//���ʂ��ǂݍ���
	fscanf_s(fp, "%6d,\n", &power);

	Power = (float)power;

	//�t�@�C���N���[�Y
	fclose(fp);
}
