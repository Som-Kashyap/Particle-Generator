#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Particle {

public:

	sf::CircleShape particleShape;
	sf::Vector2f velocity;

	Particle();

	void update();
};

Particle::Particle() {

	particleShape.setRadius(5.f);
	particleShape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
	velocity = sf::Vector2f(5.f, 5.f);

}

void Particle::update() {

	particleShape.move(velocity);

}

class Game {

public:
	sf::RenderWindow window;

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
			particleVector.emplace_back(particleOBJ);
		}
	}
}

void Game::update() {

	for (auto& particle : particleVector) {
		particle.update();
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
		update();
		handleEvents();
		render();
	}

}

int main() {

	Game game;
	game.run();

}