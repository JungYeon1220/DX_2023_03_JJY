#pragma once
class Arkanoid : public Scene
{
public:
	Arkanoid();
	virtual ~Arkanoid();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Bar> _bar;
	shared_ptr<Ball> _ball;
	shared_ptr<Stage> _stage;

	shared_ptr<Line> _wall1;
	shared_ptr<Line> _wall2;

};

