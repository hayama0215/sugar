#pragma once
#include "particle.h"
//»šºƒNƒ‰ƒX
class Dust : public Particle
{
public:
	Dust();//ºÝ½Ä×¸À
	~Dust() {//ÃÞ½Ä×¸À
		free(ptcl);	//—Ìˆæ‰ð•ú
	};

	void init(int index);	//‰Šú‰»ˆ—
	void ctrl();			//‘€ìˆ—

	inline void setPosition(VECTOR pos) {//ˆÊ’u‚ðÝ’è
		this->pos = pos;
	}
};