#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize(); //����������
	void Update(); //�X�V����
	void Draw();//�`�揈��
	void Finalize();//�I������

public:
	void SetActive(bool flg);//�L���t���O
	Vector2D GetLocation() const;//�ʒu���W�̎擾
	Vector2D GetBoxSize() const;//�����蔻��̑傫���̎擾
	float GetTime() const;//���Ԏ擾����

private:
	bool is_active; //�L����Ԃ��H
	int image;		//�摜�f�[�^
	Vector2D location;//�ʒu���W
	Vector2D box_size;//�����蔻��̑傫��
	float angle;//�p�x
	float time;//����

private:
	void Movement();//�ړ�����
};