#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Particle {

public:
	Particle();
	sf::CircleShape particleShape;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	

	void update(float& deltaTime , float& gravity);
};

Particle::Particle() {

	particleShape.setRadius(1.f);
	particleShape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
	velocity = sf::Vector2f(0.f, 0.f);
	

}

void Particle::update(float& deltaTime, float& gravity) {

	acceleration = sf::Vector2f(-(rand() % 200 + 200), (rand() % 200 + 200));
	velocity.x += acceleration.x*deltaTime;
	velocity.y += acceleration.y*deltaTime;
	velocity.y += gravity * deltaTime;

	particleShape.move(velocity*deltaTime);

}

class Game {

public:
	sf::RenderWindow window;
	sf::Clock deltaTimeClock;
	float deltaTime = 0.f;
	float gravity = 980.f;

	Game();

	void update();
	void handleEvents();
	void render();
	void run();

	vector<Particle>particleVector;
};

Game::Game() : window(sf::VideoMode(800, 600), "Particle Generator") {

}

void Game::handleEvents() {

	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl) {
			Particle particleOBJ;
			sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			particleOBJ.particleShape.setPosition(mousepos);
			particleVector.emplace_back(particleOBJ);
		}
	}
}

void Game::update() {

	for (auto& particle : particleVector) {
		particle.update(deltaTime,gravity);
	}

	for (size_t i = 0; i < particleVector.size(); i++) {

		if (particleVector[i].particleShape.getPosition().y >= window.getSize().y || particleVector[i].particleShape.getPosition().y <= 0) {
			particleVector[i].velocity.y = -particleVector[i].velocity.y;
		}
		if (particleVector[i].particleShape.getPosition().x <= 0 || particleVector[i].particleShape.getPosition().x >= window.getSize().x) {
			particleVector[i].velocity.x = -particleVector[i].velocity.x;
		}
	}

}

void Game::render() {

	window.clear();

	for (auto& particle : particleVector) {
		window.draw(particle.particleShape);
	}
	window.display();
}

void Game::run() {

	while (window.isOpen()) {

		deltaTime = deltaTimeClock.restart().asSeconds();

		update();
		handleEvents();
		render();
	}

}

int main() {

	Game game;
	game.run();

}