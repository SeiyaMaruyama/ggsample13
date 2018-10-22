#pragma once

/*
** �^�C��
*/
#include "gg.h"

namespace gg
{
  /*
  ** ��l�������� (Xorshift �@)
  */
  inline GLfloat xor128()
  {
    static unsigned int x = 123456789;
    static unsigned int y = 362436069;
    static unsigned int z = 521288629;
    static unsigned int w = 88675123;
    unsigned int t = x ^ x << 11;

    x = y;
    y = z;
    z = w;

    return static_cast<GLfloat>(w ^= w >> 19 ^ t ^ t >> 8);
  }

  /*
  ** ���K�������� (Box Muller �@)
  */
  inline void boxmuller(GLfloat *r)
  {
    float a = sqrt(-2.0f * log(((float)xor128() + 1.0f) / 4294967296.0f));
    float b = 6.2831853f * ((float)xor128() + 1.0f) / 4294967296.0f;

    r[0] = a * sin(b);
    r[1] = a * cos(b);
  }

  class GgTileShader
    : public GgSimpleShader
  {
    // �f�荞�݂̃T���v����
    static const int samples = 16;

    // �e�N�X�`�����j�b�g
    GLuint color;             // �J���[�}�b�v�̃e�N�X�`�����j�b�g
    GLint colorLoc;           // �J���[�}�b�v�̃e�N�X�`�����j�b�g�� uniform �ϐ��̏ꏊ
    GLuint depth;             // �f�v�X�}�b�v�̃e�N�X�`�����j�b�g
    GLint depthLoc;           // �f�v�X�}�b�v�̃e�N�X�`�����j�b�g�� uniform �ϐ��̏ꏊ

    // �V���h�E�}�b�s���O�p�̕ϊ��s��
    GLint msLoc;              // �V���h�E�}�b�s���O�p�̕ϊ��s��� uniform �ϐ��̏ꏊ

    // �r���|�[�g
    GLint vpLoc;              // �r���[�|�[�g�� uniform �ϐ��̏ꏊ

    // ����
    GLfloat rn[samples * 2];  // �����e�[�u��
    GLint rnLoc;              // �����e�[�u���� uniform �ϐ��̏ꏊ

  public:

    // �f�X�g���N�^
    virtual ~GgTileShader() {}

    // �R���X�g���N�^
    GgTileShader() {}
    GgTileShader(const char *vert, const char *frag = 0,
      const char *geom = 0, int nvarying = 0, const char **varyings = 0)
      : GgSimpleShader(vert, frag, geom, nvarying, varyings)
    {
      // �v���O������
      GLuint program = get();

      // �e�N�X�`�����j�b�g�� uniform �ϐ��̏ꏊ
      colorLoc = glGetUniformLocation(program, "color");
      depthLoc = glGetUniformLocation(program, "depth");

      // �V���h�E�}�b�s���O�p�� uniform �ϐ��̏ꏊ
      msLoc = glGetUniformLocation(program, "ms");

      // �r���[�|�[�g�� uniform �ϐ��̏ꏊ
      vpLoc = glGetUniformLocation(program, "vp");

      // ������ uniform �ϐ��̏ꏊ
      rnLoc = glGetUniformLocation(program, "rn");
      for (unsigned int i = 0; i < sizeof rn / sizeof rn[0]; i += 2) boxmuller(rn + i);
    }

    // �V�F�[�_�̎g�p�J�n
    void use() const
    {
      // ���N���X�̃V�F�[�_�̐ݒ���Ăяo��
      GgSimpleShader::use();

      // ����
      glUniform2fv(rnLoc, sizeof rn / sizeof rn[0] / 2, rn);

      // �r���[�|�[�g
      GLint vp[4];
      glGetIntegerv(GL_VIEWPORT, vp);
      glUniform2f(vpLoc, static_cast<GLfloat>(vp[2]), static_cast<GLfloat>(vp[3]));

      // �e�N�X�`�����j�b�g
      glUniform1i(colorLoc, 0);
      glUniform1i(depthLoc, 1);
    }

    // �V���h�E�}�b�s���O�p�̕ϊ��s��
    void loadShadowMatrix(const GLfloat *m) { glUniformMatrix4fv(msLoc, 1, GL_FALSE, m); }
    void loadShadowMatrix(const GgMatrix &m) { loadShadowMatrix(m.get()); }
  };
}
