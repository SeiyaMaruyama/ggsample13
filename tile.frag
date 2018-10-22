#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// �s���͗l�̐F
const vec4 c1 = vec4(0.9, 0.9, 0.9, 1.0);
const vec4 c2 = vec4(0.6, 0.7, 0.8, 1.0);

// �f�荞�݂̂ڂ��
const float sigma = 0.005;

// �ގ�
uniform vec4 kspec;                                 // ���ʔ��ˌW��

// �e�N�X�`�����W�̃T���v��
uniform sampler2D color;                            // �J���[�}�b�v�p
uniform sampler2DShadow depth;                      // �f�v�X�}�b�v�p

// �V���h�E�}�b�s���O�p�̃f�[�^
uniform vec2 vp;                                    // �r���[�|�[�g�̑傫��
uniform vec2 rn[16];                                // �񎟌����K����

// ���X�^���C�U����󂯎�钸�_�����̕�Ԓl
in vec4 iamb;                                       // �����̔��ˌ����x
in vec4 idiff;                                      // �g�U���ˌ����x
in vec4 ispec;                                      // ���ʔ��ˌ����x
in vec2 tc;                                         // �J���[�}�b�v�̃e�N�X�`�����W

// �t���[���o�b�t�@�ɏo�͂���f�[�^
layout (location = 0) out vec4 fc;                  // �t���O�����g�̐F

void main()
{
  // �s���͗l
  vec4 a = mix(c1, c2, mod(floor(tc.x * 2.0) + floor(tc.y * 2.0), 2.0));
  vec2 p = gl_FragCoord.xy / vp;
  vec4 c = texture(color, p);

  fc = (iamb + idiff) * a + ispec + kspec * c;
}
