#pragma once
#include "DxLib.h"
#include<stdlib.h>
#include<time.h>
#include<Math.h>
#include <cmath>	//���w�֐��p

//�}�N����`
#define WND_W	1200			//����޳��
#define WND_H	600		//����޳����

#define ErrMsg(s, f) MessageBox(NULL, s, f, MB_OK);
#define ToRadian(x)(x*DX_PI_F /180.0f)	//�x��׼ޱݕϊ�

#define SPEED_MAX 1.0f //�ő�̑��x
#define PLAYER_NUM 2 //�v���C���[�̐�
#define ITEM_MAX 7 
#define ITEM_lINTERVAL 250
#define SHOT_INTERVAL 60
#define SHOT_SPEED 5
#define GOAL_TRACK 3
#define ENEMY_NUM 4
#define COLOR_NUM 6//�Ԃ̐F�̎��

// �}�b�v�͈�
#define MAP_MAX_X 1000.0f
#define MAP_MAX_Z 1000.0f

//��ʂ̑J�ڂ̗񋓑�
enum class Mode
{
	TITLE,
	SETTING,
	PLAY,
	FIN,
};
