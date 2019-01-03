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
	_isRotatingHorizontally = false;
	_isRotatingVertically = false;
	_displayLevels = false;
	_tickVertical = 1;
	//lvl normal selected by default
	_levelState = 1;

	_menuItems.push_back(GameObject(
		assetManager.models()["frontmenu"], 0, true,
		glm::vec3(0.f),
		glm::vec3(1.f),
		glm::vec3(0.f)
	));

	for(int i =0; i<4; i++){
		_menuItems.push_back(GameObject(
			assetManager.models()["menu"],0,false,
			glm::vec3(0.f,-2 + i*1.f,2.5f),
			glm::vec3(.15f),
			glm::vec3(0.f)
			//glm::vec3(0.f,-(0.5f + (i-1)*0.2f), 0.f)
			//glm::vec3(0.f,-(-10.f + i*10.f),0.f)
		));
	}
	_skybox.push_back(GameObject(
		assetManager.models()["skybox"], 0,  true,
		glm::vec3(0.f),
		glm::vec3(100.f),
		glm::vec3(0.f)
	));

	_menuItems[0].scale() = glm::vec3(1.5f);

	_menuItems[1].model().setTexture("Scores.png");
	_menuItems[2].model().setTexture("QuitToMenu.png");
	_menuItems[0].model().setTexture("Save.png");

	glEnable(GL_DEPTH_TEST);
}

Menu::~Menu(){
	std::cout << "menu desctructor called " << std::endl;
}

void Menu::update() {

	// for(float i =1; i< _menuItems.size();i++){
	// 	_menuItems[i].scale() = glm::vec3(.01f);
	// }

	if(isRotatingHorizontally() ){
		_rotationAngle += (1 * _rotationDirection);
		rotateHorizontally( (6 * _rotationDirection) );
		if( _rotationAngle % 10 == 0){
			_rotationAngle = 0;
			_isRotatingHorizontally = false;
		}
	}
	if(isRotatingVertically()){
		for(int i = 0;i<_levels.size()+1;i++){
			_menuItems[i+1].sPosition() += glm::vec3(0.f,(0.2f * _rotationDirection),0.f);
		}
		//std::cout << _menuItems[1].sPosition() << std::endl;
		if(_tickVertical == 5){
			_tickVertical=0;
			_isRotatingVertically =false;
		}
		_tickVertical++;
	}

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


		//glDepthFunc(GL_LEQUAL);
		// Update MVMatrix according to the object's transformation
		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		_renderManager.useProgram(TEXTURE);
		//_renderManager.applyTransformations(TEXTURE);

		// for (float i=0; i<_menuItems.size(); ++i) {
		//    //MVMatrix = camMatrix * _menuItems[i].matrix();
		//   //_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		// 	_renderManager.useProgram(NORMAL);
		// 	_renderManager.applyTransformations(NORMAL, _renderManager.MVMatrix());
			_menuItems[0].draw();
		//}

		//display levels
		if(_displayLevels){
			for(float i=1; i< _menuItems.size();i++){
				  MVMatrix = _menuItems[i].staticMatrix();
				  _renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
					_renderManager.useProgram(TEXTURE);
					_renderManager.applyTransformations(TEXTURE);
					_menuItems[i].draw();
			}
		}
}

void Menu::moveToPannel(const int pannelState) {
	_rotationDirection = -pannelState;
	if( (_menuState + pannelState) <0 ){
		_menuState +=5;
	}else{
		_menuState += pannelState;
	}
	if(getState() == "Play"){
		_displayLevels = true;
	} else {
		_displayLevels = false;
	}

	_isRotatingHorizontally = true;
}

std::string Menu::getState(){
	return _action[abs(_menuState%6)];
}

void Menu::rotateHorizontally(const float dx){
	_cameras[_chosenCamera]->rotateLeft(dx);
}

void Menu::moveToLevel(const int lvlUpOrDown){

	if( (_levelState  -lvlUpOrDown) < 0 ){
		_levelState = 0;
		_isRotatingVertically = false;
	}else if( (_levelState -lvlUpOrDown > (_levels.size()-1) ) ){

		_levelState = _levels.size()-1 ;
		_isRotatingVertically = false;
	}else{
	 	_levelState+= -lvlUpOrDown;
		std::cout << "Level : " << _levels[_levelState] << " Selected" <<  std::endl;
		_rotationDirection = -lvlUpOrDown;
		_isRotatingVertically = true;
	}

}


void Menu::rotateVertically(const float dx){
	_cameras[_chosenCamera]->rotateUp(dx);
}


}
