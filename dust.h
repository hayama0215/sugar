#pragma once
#include "particle.h"
//�����N���X
class Dust : public Particle
{
public:
	Dust();//�ݽ�׸�
	~Dust() {//�޽�׸�
		free(ptcl);	//�̈���
	};

	void init(int index);	//����������
	void ctrl();			//���쏈��

	inline void setPosition(VECTOR pos) {//�ʒu��ݒ�
		this->pos = pos;
	}
};