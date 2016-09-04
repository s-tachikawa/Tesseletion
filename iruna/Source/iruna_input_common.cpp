//---------------------------------------------------------
// 
//	iruna_io.cpp
//	Iput�n���ʏ���
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_input_common.h"
#include "../Source/iruna_keyboard.h"
#include "../Source/iruna_mouse.h"

namespace iruna
{
namespace io
{

/*----�O���[�o���֐� ��`----------------------------------------------------*/

// �L�[�{�[�h�̎w�肵���L�[�̏�Ԃ�Ԃ�
INPUT_STATE CheckKeyState( U_LONG key )
{
	return Keyboard::GetState( key );
}

// �}�E�X�̎w�肵���L�[�̏�Ԃ�Ԃ�
INPUT_STATE CheckMouseState( MouseButton::Type key )
{
	return Mouse::GetState( key );
}

// �}�E�X�J�[�\���̈ʒu���擾����
POINT GetMousePosition()
{
	return Mouse::GetPosition();
}

}	//	io		end
}	//	iruna	end