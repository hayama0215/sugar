#include "dust.h"
Dust::Dust()
{
	loadImage("image/smoke.png");	//�߰è�ى摜�̓Ǎ���

	//�p�[�e�B�N�������̔z����m��
	particleMax = 20;
	ptcl = (Ptcl*)malloc(sizeof(Ptcl) * particleMax);

	//������
	for (int i = 0; i < particleMax; i++) {
		init(i);
	}
}

void Dust::init(int index)
{
	ptcl[index].blendMode = DX_BLENDMODE_ADD;	//���Z����
	ptcl[index].pos = VGet((float)GetRand(2)+10, 0, 0);	//�ʒu
	ptcl[index].lifeTime = GetRand(50);		//��������
	ptcl[index].size = 10.0f;					//�߰è�ق̻���
	ptcl[index].alpha = GetRand(64) + 192 - 1;	//�����x
	ptcl[index].radian = 0;			//�p�x(׼ޱ�)
	ptcl[index].isActive = false;	//�\�����׸�
}

void Dust::ctrl()
{
	for (int i = 0; i < particleMax; i++) 
	{
		if (ptcl[i].isActive) continue;	//���쒆�͔�΂�

		ptcl[i].isActive = true;	//���쒆�ɂ���
		ptcl[i].pos = pos;			//��ڲ԰�̈ʒu(����)
		ptcl[i].pos.y = -3.0f;		//�n�ʂ���
		break;	//1����������break;
	}

	for (int i = 0; i < particleMax; i++)
	{
		if (!ptcl[i].isActive) continue;	//������͔�΂�

		ptcl[i].pos.y += 0.08f;	//�㏸������
		ptcl[i].alpha -= (float)GetRand(10) * 0.1f;
		ptcl[i].lifeTime--;		//�����޳�
		if (ptcl[i].lifeTime <= 0) {
			init(i);
		}
	}
}
