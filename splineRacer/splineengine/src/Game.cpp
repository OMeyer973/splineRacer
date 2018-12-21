#include <splineengine/Game.hpp>
#include <splineengine/CubeMap.hpp>

namespace splineengine {

Game::Game()
	:_player(), _spline()
{
	std::cout << "infinite game constructor called " << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;

	RenderManager _renderManager(*_cameras[_chosenCamera]);
}

Game::Game(std::string levelName)
	:_player(), _spline(levelName)
{
	// TODO
	std::cout << "game from level constructor called " << std::endl;
}


Game::~Game() {
	std::cout << "game destructor called " << std::endl;
}


void Game::loadLevel(std::string levelName) {
	// TODO
}


void Game::loadLevel() {
	// TODO

	// TODO : get models from asset manager
	//Model planemodel("plane");

	AssetManager& assetManager = AssetManager::instance();

	// GameObject testObject(assetManager.models()[PLANEMODEL]);
	// _obstacles.push_back(testObject);

    for (float i=0; i<100; ++i) {
        _obstacles.push_back (GameObject(
        	assetManager.models()[PLANEMODEL],
            glm::vec3(3+i/8, 0.f, 1.5f),
            glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3(0.0f, 0.0f, i/5)
        ));
    }
}


void Game::update() {
	// TODO
}


void Game::render() {
	std::cout << "Game Render" << std::endl;
	// TODO

	// TODO : have sthis working
	GLuint programId = _obstacles[0].model().program().getGLId();
	
	GLint uMVPMatrix = glGetUniformLocation(programId, "uMVPMatrix");
	GLint uMVMatrix = glGetUniformLocation(programId, "uMVMatrix");
	GLint uNormalMatrix = glGetUniformLocation(programId, "uNormalMatrix");
	
	for (float i=0; i<_obstacles.size(); ++i) {

		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], _obstacles[i].matrix());
		
		// // TODO : MOVE THIS SHIT TO RENDERMANAGER
		// glBindTexture(GL_TEXTURE_2D, textures[0]);
		// glUniform1i(textureLocation, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// TODO : have this working
		glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(_renderManager.projMatrix() * _renderManager.MVMatrix()));
		glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(_renderManager.MVMatrix()));
		glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(_renderManager.normalMatrix()));
		
	    _obstacles[i].draw();

    }

}


}
