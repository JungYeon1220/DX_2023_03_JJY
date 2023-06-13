#pragma once
class DunGreed : public Scene
{
public:
	DunGreed();
	virtual ~DunGreed();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class DunPlayer> _player;
	vector<shared_ptr<class DunMonster>> _monsters;
};

