#include <splineengine/Menu.hpp>
#include <cstdlib>


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
		glm::vec3(0.f)
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

	_menuItems[0].scale() = glm::vec3(3.f);
	// TODO
}


void Menu::render() {
	// TODO
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 MVMatrix =  _skybox[0].staticMatrix();

		//std::cout<< getState() << std::endl;
		//Draw _skybox
		glDepthMask(GL_FALSE);
		//MVMatrix = camMatrix *  _skybox[0].matrix();
		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		_renderManager.useProgram(TEXTURE);
		_skybox[0].draw();
		glDepthMask(GL_TRUE);

		MVMatrix = _menuItems[0].staticMatrix();

		if(isRotating() ){
			_rotationAngle += (1 * _rotationDirection);
			rotate( (6 * _rotationDirection) );
			if( _rotationAngle % 10 == 0){
				_rotationAngle = 0;
				_isRotating = false;
			}
		}
		//glDepthFunc(GL_LEQUAL);
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

void Menu::moveToPannel(const int incrementState) {
	_rotationDirection = -incrementState;
	if( (_menuState + incrementState) <0 ){
		_menuState +=5;
	}else{
		_menuState += incrementState;
	}
	_isRotating = true;
}

	std::string Menu::getState(){
		return _action[abs(_menuState%6)];
	}

void Menu::rotate(const float dx){
	_cameras[_chosenCamera]->rotateLeft(dx);
}

}
