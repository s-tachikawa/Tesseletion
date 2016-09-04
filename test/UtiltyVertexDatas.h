
#include "../iruna/Include/iruna.h"


using namespace iruna;
using namespace graphics;

// ボックス用頂点データ構造体
struct SBoxVertexData
{
	math::Vector3 pos;
	math::Vector2 uv;
};

// 板ポリ用頂点データ構造体
struct SBoardVertexBuffer
{
	math::Vector3 pos;
	math::Vector2 uv;
};