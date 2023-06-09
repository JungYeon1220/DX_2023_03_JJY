#include "framework.h"
#include "MazeBlock.h"

MazeBlock::MazeBlock()
{
	_rect = make_shared<RectCollider>(Vector2(), Vector2(14, 14));

	HBRUSH able = CreateSolidBrush(GREEN);
	HBRUSH disable = CreateSolidBrush(RED);
	HBRUSH player = CreateSolidBrush(WHITE);
	HBRUSH end = CreateSolidBrush(BLUE);
	HBRUSH path = CreateSolidBrush(GREY);
	HBRUSH visited = CreateSolidBrush(DARK_GREY);

	_brushes.push_back(able);
	_brushes.push_back(disable);
	_brushes.push_back(player);
	_brushes.push_back(end);
	_brushes.push_back(path);
	_brushes.push_back(visited);

}

MazeBlock::~MazeBlock()
{
	for (auto brush : _brushes)
	{
		DeleteObject(brush);
	}
}

void MazeBlock::Update()
{
	_rect->Update();
}

void MazeBlock::Render(HDC hdc)
{
	if (_type == BlockType::NONE)
		return;

	SelectObject(hdc, _brushes[static_cast<unsigned int>(_type)]);
	_rect->Render(hdc);
}
