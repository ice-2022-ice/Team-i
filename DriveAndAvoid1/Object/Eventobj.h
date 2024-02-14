#pragma once

#include "../Utility/Vector2D.h"

class Eventobj
{
public:
	Eventobj();
	~Eventobj();

	void Initialize(float power, bool active, int rank); //����������
	void Update(float Accel); //�X�V����
	void Draw();//�`�揈��
	void Finalize();//�I������

	int GetScore();	//�X�R�A�l��

public:


private:
	int image[5];		//�摜�f�[�^
	int Explosion_image[16];		//�����摜
	int anim_time;					//�A�j������

	Vector2D location;//�ʒu���W

	bool active;	//�L������

	int rank;		//�I�u�W�F�N�g�̃X�R�A�{��
	int score;		//�l���X�R�A

private:
	void Movement(float Accel);//�ړ�����
};