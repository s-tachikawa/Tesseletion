//*********************************************************************
/*!
	@file	iruna_graphics.h
	@brief	グラフィックス系一括インクルード
	@author	立川 翔野
	@date	2011/06/23	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_GRAPHICS_H
#define IRUNA_GRAPHICS_H

/*----インクルード-------------------------------------------------*/
//	Device系
#include "../Include/iruna_device_controller.h"

//	Material系
#include "../Include/iruna_material.h"
#include "../Include/iruna_color4.h"

//	Shder系
#include "../Include/iruna_efect.h"
#include "../Include/iruna_vertex_shader.h"
#include "../Include/iruna_pixel_shader.h"
#include "../Include/iruna_hull_shader.h"
#include "../Include/iruna_domain_shader.h"

//	3D系
#include "../Include/iruna_camera.h"
#include "../Include/iruna_bord.h"
#include "../Include/iruna_model.h"
#include "../Include/iruna_model_data.h"
#include "../Include/iruna_model_loader.h"
#include "../Include/iruna_animetion_controller.h"

//	2D系
#include "../Include/iruna_sprite.h"
#include "../Include/iruna_text.h"

//	Surface系
#include "../Include/iruna_surface.h"
#include "../Include/iruna_texture.h"
#include "../Include/iruna_font.h"
#include "../Include/iruna_viewport.h"
#include "../Include/iruna_cube_texture.h"

//	Vertex系
#include "../Include/iruna_vertex_buffer.h"
#include "../Include/iruna_index_buffer.h"
#include "../Include/iruna_vertex_declaration.h"


#endif	//	IRUNA_GRAPHICS_H	end