#include <bangtal.h>
using namespace bangtal;

int main(void)
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	// ����� �����Ѵ�.
	auto scene = Scene::create("��Ÿ���̽�", "images/background.png");

	auto santaX = 0, santaY = 500;
	auto santa = Object::create("images/santa.png", scene, santaX, santaY);

	auto startButton = Object::create("images/start.png", scene, 590, 70);
	auto endButton = Object::create("images/end.png", scene, 590, 20);
	auto playButton = Object::create("images/play.png", scene, 610, 30, false);

	auto timer = Timer::create(10.f);

	showTimer(timer);
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		showMessage("�� ��� ���� ����!!");

		playButton->hide();
		startButton->setImage("images/restart.png");
		startButton->show();
		endButton->show();

		return true;
	});
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startButton->hide();
		endButton->hide();
		playButton->show();

		santaX = 0;
		santa->locate(scene, santaX, santaY);

		timer->set(10.f);
		timer->start();

		return true;
	});
	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
	});

	playButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		// ��Ÿ�� x������ 30��ŭ �̵��Ѵ�.
		santaX = santaX + 30;
		santa->locate(scene, santaX, santaY);

		if (santaX > 1280) {
			showMessage("���� ��� ����~~");
			timer->stop();

			playButton->hide();
			startButton->setImage("images/restart.png");
			startButton->show();
			endButton->show();
		}

		return true;
	});

	// ������ �����Ѵ�.
	startGame(scene);

	return 0;
}