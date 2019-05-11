#include "DxLib.h"
////////////////////////////////////////////////////////////////
// Bitmap Text class
// 
// �����`�A���t�@�x�b�g�����񂾃r�b�g�}�b�v�摜���t�H���g�Ƃ��ēo�^
// ���������ʕ\������N���X
////////////////////////////////////////////////////////////////

#ifndef __BITMAPTEXT_H__
#define __BITMAPTEXT_H__

class BitmapText
{
public:
	BitmapText();
	~BitmapText();

	void          setBackGroundAlpha(bool bg_alpha_on) { m_bgalpha = bg_alpha_on; }                 // �t�H���g�w�i�𓧉߂��邩�H
	void          setFontImage(int Xnum, int Ynum, const char* fontImgfilename);                          // �t�H���g�摜���t�H���g���Z�b�g����
	void          setFontColor(int r, int g, int b);                                                // �t�H���g�J���[�Z�b�g
	void          setFontColorShadow(int r, int g, int b);                                          // �e�J���[���Z�b�g
	void          textDrawRandom(int x, int y, const char* string, int maxRand, int countDown);           // �����_�������\��
	
	void          setFontShadowOffset(int ofsX, int ofsY);                                          // �e�t�H���g�ʒu�I�t�Z�b�g
	void          textDraw(int x, int y, const char* string);                                             // �e�L�X�g��`��
	void          textDrawWithShadow(int x, int y, const char* string);                                   // �e�t���Ńe�L�X�g�`��

	void          textDrawMessage(int x, int y,const  char* string, unsigned int display_lengh);          // ���b�Z�[�W���\���i��������������j
	void          textDrawMessageWithShadow(int x, int y, const char*string, unsigned int display_lengh); // ���b�Z�[�W���\���i��������������j
	void          reMapText(const char* remapText); // �r�b�g�}�b�v�ɕ���ł��镶��������āA�e�L�X�g���當���������悤�ɂ���B�i�������ŕK�v�j

private:
	int           m_fontImg[256] ; // �t�H���g�C���[�W�z��
	int           m_fontMap[256] ; // �����}�b�v char�^�������t�H���g�C���[�W�z��Y�����ԍ��̃}�b�s���O

	unsigned int  m_sizeX        ; // �t�H���g1���������T�C�Y
	unsigned int  m_sizeY        ; // �t�H���g1�������c�T�C�Y	
	int           m_shadowOffsetX; // �e�t�H���g�ʒu�I�t�Z�b�gX
	int           m_shadowOffsetY; // �e�t�H���g�ʒu�I�t�Z�b�gY
	bool          m_useflag      ; // �t�H���g�g�p�\�t���O
	bool          m_bgalpha      ; // �����w�i�𓧉߂����邩

	int           isString(char c)          ; // �������C���[�W�z��̓Y�����ɕϊ�
	unsigned char R, G, B;         // �����F 
	unsigned char m_shadow_R;
	unsigned char m_shadow_G;
	unsigned char m_shadow_B;
};

#endif