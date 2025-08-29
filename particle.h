#pragma once

#include "model.h"

//�p�[�e�B�N���N���X
class Particle : public Image
{
public:
	Particle() {};	//�ݽ�׸�
	~Particle() {};	//�޽�׸�

	//���z�֐�
	virtual void init(int index);
	virtual void ctrl();
	virtual void draw();

protected:
	int particleMax;	//�߰è�ِ�

	struct Ptcl
	{
		int		blendMode;	//������Ӱ��
		VECTOR	pos;		//�ʒu
		VECTOR	add;		//�����l
		int		lifeTime;	//��������
		float	size;		//�߰è�ق̻���
		float	alpha;		//�����x
		float	radian;		//�p�x(׼ޱ�)
		bool	isActive;	//�\�����׸�
		//�\���̺̂ݽ�׸�
		Ptcl() {
			pos = VGet(0, 0, 0);
			lifeTime = 500;
			size = 5.0f;
			alpha = 255;	//���S�s����
			radian = 0;
			isActive = false;
		}
	}*ptcl;
};