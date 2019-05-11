#include "bitmapText.h"

const int maxImageNum = 256;

BitmapText::BitmapText()
{
	m_useflag      = false;
	m_bgalpha      = true ;

	for (int i = 0; i < maxImageNum; i++)
	{
		m_fontMap[i] = -1;
	}
	R = G = B = 255;
	m_shadow_R = 64;
	m_shadow_G = 64;
	m_shadow_B = 64;

	m_shadowOffsetX = 1;
	m_shadowOffsetY = 1;

}

BitmapText::~BitmapText()
{
	// �t�H���g�C���[�W�̉��
	if (m_useflag)
	{
		for (int i = 0; i < maxImageNum; i++)
		{
			DeleteGraph(m_fontImg[i]);
		}
	}
	m_useflag = false;
}

void BitmapText::setFontImage(int Xnum, int Ynum, const char * fontImgfilename)
{
	int tmpImg, imgX, imgY;

	// �t�@�C�����ǂݍ���
	tmpImg = LoadGraph(fontImgfilename);
	if (tmpImg == -1)
	{
		printf("fontfile load failed:[%s]", fontImgfilename);
		return;
	}
	//�@�摜�T�C�Y�c���擾
	GetGraphSize(tmpImg, &imgX, &imgY);
	DeleteGraph(tmpImg);

	// �t�H���g1���̏c���T�C�Y�擾
	m_sizeX = imgX / Xnum;
	m_sizeY = imgY / Ynum;

	// �摜�ǂݍ���
	LoadDivGraph(fontImgfilename, Xnum*Ynum, Xnum, Ynum, m_sizeX, m_sizeY, m_fontImg);
	m_useflag = true;
}

void BitmapText::textDraw(int x, int y, const char * string)
{
	//�t�H���g�g�p�\��
	if (!m_useflag)
		return;

	//�e�L�X�g�`��J�n
	int text_x, text_y, img;
	text_x = x;
	text_y = y;

	while (*string)
	{

		// ���������s�̏ꍇ�͉��s�{�߂�
		if (*string == '\n')
		{
			text_x = x;
			text_y += m_sizeY;
			string++;
			continue;
		}

		//�����`��
		img = isString(*string);
		if (img >= 0)
		{
			DrawGraph(text_x, text_y, m_fontImg[img], m_bgalpha);
		}

		// �����`��ʒu�i�߂�
		text_x += m_sizeX;
		string++;
	}

	SetDrawBright(255, 255, 255);
}

void BitmapText::textDrawWithShadow(int x, int y, const char * string)
{
	//�e�����`��
	SetDrawBright(m_shadow_R, m_shadow_G, m_shadow_B);
	textDraw(x + m_shadowOffsetX, y + m_shadowOffsetY, string);

	//�����`��
	SetDrawBright(R, G, B);
	textDraw(x, y, string);

}

void BitmapText::textDrawRandom(int x, int y, const char* string, int maxRand, int countDown)
{
	char randloopWidth = 'z' - '!';
	char *randString;

	int cnt=0;
	while (string[cnt])
		cnt++;

	randString = new char[cnt + 1];

	//���݂̕������烉���_��������쐬
	cnt = 0;
	char randCount;
	while (*string)
	{
		randCount = (maxRand % randloopWidth - countDown) < 0 ? 0 : (maxRand % randloopWidth - countDown);
		randString[cnt] = *string + randCount;
		cnt++;
		string++;
	}
	randString[cnt] = '\0';

	textDraw(x, y, randString);

	delete[] randString;
}

void BitmapText::textDrawMessage(int x, int y, const char * string, unsigned int display_lengh)
{
	// ���������J�E���g���A�\�����������{���̕�������葽����΂��̂܂ܕ\��
	size_t len = strlen(string);
	if (len < display_lengh)
	{
		textDraw(x, y, string);
		return;
	}

	// ��������display_length���ŕ\��
	char* tmpStr = new char[display_lengh + 1];
	for (unsigned int i = 0; i < display_lengh; i++)
	{
		tmpStr[i] = string[i];
	}
	tmpStr[display_lengh] = '\0';

	textDraw(x, y, tmpStr);

	delete[] tmpStr;
}

void BitmapText::textDrawMessageWithShadow(int x, int y, const char * string, unsigned int display_lengh)
{
	// ���������J�E���g���A�\�����������{���̕�������葽����΂��̂܂ܕ\��
	size_t len = strlen(string);
	if (len < display_lengh)
	{
		textDrawWithShadow(x, y, string);
		return;
	}

	// ��������display_length���ŕ\��
	char* tmpStr = new char[display_lengh + 1];
	for (unsigned int i = 0; i < display_lengh; i++)
	{
		tmpStr[i] = string[i];
	}
	tmpStr[display_lengh] = '\0';

	textDrawWithShadow(x, y, tmpStr);

	delete[] tmpStr;
}


void BitmapText::setFontColor(int r, int g, int b)
{
	R = r; G = g; B = b;
	SetDrawBright(R, G, B);
}

void BitmapText::setFontColorShadow(int r, int g, int b)
{
	m_shadow_R = r;
	m_shadow_G = g;
	m_shadow_B = b;
}

void BitmapText::setFontShadowOffset(int ofsX, int ofsY)
{
	m_shadowOffsetX = ofsX;
	m_shadowOffsetY = ofsY;
}
	
void BitmapText::reMapText(const char *remapText)
{
	int num = 0;
	const char *p ;

	p = remapText;
	char n = 0;
	while (*p && n < 255)
	{
		m_fontMap[*p++] = n++;
	}

}

int BitmapText::isString(char c)
{
	return m_fontMap[c];
}
