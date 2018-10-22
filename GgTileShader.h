#pragma once

/*
** �^�C��
*/
#include "gg.h"

namespace gg
{

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
      const char *geom = 0, int nvarying = 0, const char **varyings = 0);

    // �V�F�[�_�̎g�p�J�n
    virtual void use() const;

    // �V���h�E�}�b�s���O�p�̕ϊ��s��
    void loadShadowMatrix(const GLfloat *m) { glUniformMatrix4fv(msLoc, 1, GL_FALSE, m); }
    void loadShadowMatrix(const GgMatrix &m) { loadShadowMatrix(m.get()); }
  };
}
