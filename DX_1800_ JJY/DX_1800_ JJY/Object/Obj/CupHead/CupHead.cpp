#include "framework.h"
#include "CupHead.h"

CupHead::CupHead()
{
	_col = make_shared<CircleCollider>(50);
	_transform = make_shared<Transform>();

	CreateAction("Idle",0.1f, Action::Type::PINGPONG);
	CreateAction("Run");

	_col->GetTransform()->SetPosition(CENTER);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 20));

	_actions[State::IDLE]->Play();
	_actions[State::RUN]->Play();


}

CupHead::~CupHead()
{
}

void CupHead::Update()
{
	Input();

	_col->Update();
	_transform->Update();

	_actions[_state]->Update();

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Update();
}

void CupHead::Render()
{
	_transform->SetWorldBuffer(0);
	_sprites[_state]->Render();

	_col->Render();
}

void CupHead::PostRender()
{
	ImGui::SliderInt("State", (int*)&_state, 0, 1);
}

void CupHead::Input()
{
	if (KEY_PRESS('A'))
	{
		_col->GetTransform()->AddVector2(Vector2(-1.0f, 0.0f) * _speed * DELTA_TIME);
		SetLeft();
		SetAction(State::RUN);
	}
	else if (KEY_UP('A'))
	{
		SetAction(State::IDLE);
	}

	if (KEY_PRESS('D'))
	{
		_col->GetTransform()->AddVector2(Vector2(1.0f, 0.0f) * _speed * DELTA_TIME);
		SetRight();
		SetAction(State::RUN);
	}
	else if (KEY_UP('D'))
	{
		SetAction(State::IDLE);
	}
}

void CupHead::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	string xmlPath = "Resource/Cuphead/" + name + ".xml";
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Cuphead/" + wName + L".png";

	shared_ptr<SRV> srv = ADD_SRV(srvPath);
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;
	float averageW = 0;
	float averageH = 0;
	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		averageW += w;
		averageH += h;
		count++;

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, name, type, speed);
	action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW/count, averageH/count));
	_sprites.push_back(sprite);
}

void CupHead::SetAction(State state)
{
	if (_state == state)
		return;

	_actions[_state]->Reset();
	_actions[_state]->Pause();

	_state = state;
	_actions[_state]->Play();
}
