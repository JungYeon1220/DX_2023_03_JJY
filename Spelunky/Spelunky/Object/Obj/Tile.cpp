#include "framework.h"
#include "Tile.h"

Tile::Tile()
{
	_transform = make_shared<Transform>();
	_sprite = make_shared<Sprite_Frame>(L"Resource/Texture/floor_cave.png", Vector2(12, 12));
	_col = make_shared<RectCollider>(_sprite->GetClipsize());
	_transform->SetParent(_col->GetTransform());
}

Tile::~Tile()
{
}

void Tile::TileSelect(Tile::Type value)
{
	_type = value;
	if (value == Tile::Type::EMPTY)
		_selected = Vector2(11, 11);
	else if (value == Tile::Type::NORMAL)
		_selected = Vector2(0, 0);
}

bool Tile::Block(shared_ptr<Collider> col)
{
	return false;
}

void Tile::Update()
{
	_col->GetTransform()->SetPosition(_pos);
	_transform->Update();
	_sprite->SetCurClip(_selected);
	_sprite->Update();
	_col->Update();
}

void Tile::Render()
{
	_transform->SetWorldBuffer(0);
	_sprite->Render();
	_col->Render();
}
