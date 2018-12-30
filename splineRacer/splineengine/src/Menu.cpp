#include <splineengine/Menu.hpp>


namespace splineengine {

Menu::Menu()
{
	std::cout << "front menu constructor called " << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;
	RenderManager _renderManager(*_cameras[_chosenCamera]);
}

void Menu::init() {
	std::cout << "menu init" << std::endl;
	AssetManager& assetManager = AssetManager::instance();
	_isRotating = false;

	_menuItems.push_back(GameObject(
		assetManager.models()["frontmenu"], 0, true,
		glm::vec3(0.f),
		glm::vec3(2.f),
		glm::vec3(0.f, 0.f, 0.f)
	));
	_skybox.push_back(GameObject(
		assetManager.models()["skybox"], 0,  true,
		glm::vec3(0.f),
		glm::vec3(100.f),
		glm::vec3(0.f)
	));

	glEnable(GL_DEPTH_TEST);
}

Menu::~Menu(){
	std::cout << "menu desctructor called " << std::endl;
}

void Menu::update() {
	// TODO
}


void Menu::render() {
	// TODO
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 camMatrix = glm::mat4(1);
		glm::mat4 MVMatrix = camMatrix * _skybox[0].staticMatrix();

		//Draw _skybox
		glDepthMask(GL_FALSE);
		//MVMatrix = camMatrix *  _skybox[0].matrix();
		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		_renderManager.useProgram(TEXTURE);
		_skybox[0].draw();
		glDepthMask(GL_TRUE);


		//_menuItems[0].scale() = glm::vec3(5.8f);

		MVMatrix = camMatrix * _menuItems[0].staticMatrix();
		// Update MVMatrix according to the object's transformation
		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		_renderManager.useProgram(TEXTURE);
		// _renderManager.applyTransformations(TEXTURE);

		// for (float i=0; i<_menuItems.size(); ++i) {
		//    //MVMatrix = camMatrix * _menuItems[i].matrix();
		//   //_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		// 	_renderManager.useProgram(NORMAL);
		// 	_renderManager.applyTransformations(NORMAL, _renderManager.MVMatrix());
			_menuItems[0].draw();
		//}
}

void Menu::moveToPannel(const float dx) {
	_cameras[_chosenCamera]->rotateLeft(dx * 6);
}


}
