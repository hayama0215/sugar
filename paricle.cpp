#include "particle.h"

//����������
void Particle::init(int index)
{
	ptcl[index].blendMode = DX_BLENDMODE_ADD;	//���Z����
	ptcl[index].pos = VGet((float)GetRand(2), 0, 0);	//�ʒu
	ptcl[index].lifeTime = GetRand(500);		//��������
	ptcl[index].size = 5.0f;					//�߰è�ق̻���
	ptcl[index].alpha = GetRand(64) + 192 - 1;	//�����x
	ptcl[index].radian = 0;			//�p�x(׼ޱ�)
	ptcl[index].isActive = true;	//�\�����׸�
}

//���쏈��
void Particle::ctrl()
{
	for (int i = 0; i < particleMax; i++)
	{
		float wide = (float)GetRand(10) * 0.01f;
		ptcl[i].pos.x += cos(ptcl[i].radian) * wide;
		ptcl[i].radian += (float)GetRand(10) * 0.01f;
		ptcl[i].pos.y += 0.05f;
		ptcl[i].alpha -= (float)GetRand(5) * 0.1f;
		ptcl[i].lifeTime--;
		if (ptcl[i].lifeTime <= 0) {
			init(i);
		}
	}
}
//�\������
void Particle::draw()
{
	for (int i = 0; i < particleMax; i++)
	{
		alpha = ptcl[i].alpha;
		alphaOn();		//�����x��L���ɂ���
		drawBillboard(ptcl[i].pos,
			ptcl[i].size, ptcl[i].radian);
	}
	alphaOff();	//�����x�𖳌��ɂ���
}
