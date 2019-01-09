#include <splineengine/Menu.hpp>
#include <splineengine/Model.hpp>
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
	//Text skurt = Text();
	std::cout << "menu init" << std::endl;
	AssetManager& assetManager = AssetManager::instance();

	assetManager.setupText();

	//setting all the boolean used to determine the state of the menu
	_isRotatingHorizontally = false;
	_isRotatingVertically = false;
	_displayLevels = false;
	_tickVertical = 1;
	//lvl normal selected by default
	_selectedLevel = 1;

	//Pushing extruded hexagon
	_menuItems.push_back(GameObject(
		assetManager.models()["frontmenu"],
		Spline(),
		"frontMenuText.png",
		true,
		Transform(
			glm::vec3(0.f),
			glm::vec3(3.5f),
			glm::vec3(0.f)
		)
	));

	//pushing pannels to chose level -maybe change name of model to be more specific
	for(int i =0; i<4; i++){
		// std::cout << "Nom texture : " << _levels[3-i] + std::string(".png") << std::endl;
		_menuItems.push_back(GameObject(
			assetManager.models()["menu"],Spline(),
			_levels[3-i] + std::string(".png"),
			false,
			Transform(
				glm::vec3(0.f, -4 + i*2.f, 2.4f),
				glm::vec3(0.25f),
				glm::vec3(0.f)
			)
			//glm::vec3(0.f,-(0.5f + (i-1)*0.2f), 0.f)
			//glm::vec3(0.f,-(-10.f + i*10.f),0.f)
		));
	}
	//pushing skybox
	_skybox.push_back(GameObject(
		assetManager.models()["skybox"], Spline(),
		"skybox_desert.png",
		true,
		Transform(
			glm::vec3(0.f),
			glm::vec3(100.f),
			glm::vec3(0.f)
		)
	));

	_renderManager.initMenuLights();

	glEnable(GL_DEPTH_TEST);
}

Menu::~Menu(){
	std::cout << "menu desctructor called " << std::endl;
}

void Menu::update() {
	float dt = Settings::instance().deltaTime();
	// ^utilise ça pour cotrôler tes vitesses de ritation / déplacement


	// for(float i =1; i< _menuItems.size();i++){
	// 	_menuItems[i].scale() = glm::vec3(.01f);
	// }


	// If a move to a left or right pannel is detected, then smooth camera turn around
	if(isRotatingHorizontally() ){
		_rotationAngle += (_rotationDirection);
		rotateHorizontally( (6 * _rotationDirection) );
		if( _rotationAngle % 10 == 0){
			_rotationAngle = 0;
			_isRotatingHorizontally = false;
		}
	}
	// If a move to chose a different level is detected, then smooth transition to move pannels up or down
	if(isRotatingVertically()){
		for(int i = 0;i<_levels.size()+1;i++){
			_menuItems[i+1].sPosition() += 0.4f * _rotationDirection * upVec;
		}
		//std::cout << _menuItems[1].sPosition() << std::endl;
		//Used to stop the movement from up to down and down to up

		if(_tickVertical == 5){
			_tickVertical=0;
			_isRotatingVertically =false;
		}
		_tickVertical++;
	}
	// Interaction with current selected
	// for(int i = 0;i<_levels.size()+1;i++){
	// 	if(i == _selectedLevel){;
	// 		_menuItems[i+1].rotation() = glm::vec3(0.12f,0.f,0.f);
	// 	}else{
	// 		_menuItems[i+1].rotation() = glm::vec3(0.f);
	// 	}
	// }

	// TODO
}

void Menu::render() {
	// TODO
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// _renderManager.updateMVMatrix(*_cameras[_chosenCamera], glm::mat4(1), glm::vec3());
	_renderManager.updateGlobalMatrix();
	_renderManager.updateMenuLights();

	glm::mat4 MVMatrix = _skybox[0].staticMatrix();

	//std::cout<< selectedMenu() << std::endl;
	// Draw _skybox
	glDepthMask(GL_FALSE);
	// MVMatrix = camMatrix *  _skybox[0].matrix();
	_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix, _skybox[0].scale());
	_renderManager.useProgram(TEXTURE);
	_skybox[0].draw();
	glDepthMask(GL_TRUE);

	MVMatrix = _menuItems[0].staticMatrix();

	//glDepthFunc(GL_LEQUAL);
	// Update MVMatrix according to the object's transformation
	_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix, _menuItems[0].scale());
	_renderManager.useProgram(MULTI_LIGHT);

	_menuItems[0].draw();

	//display levels
	if(_displayLevels){
		for(float i=1; i< _menuItems.size();i++){
			MVMatrix = _menuItems[i].staticMatrix();
			_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix, _menuItems[i].scale());
			_renderManager.useProgram(MULTI_LIGHT);
			_menuItems[i].draw();
		}
	}
}

void Menu::changePannel(const int pannelState) {
	_rotationDirection = -pannelState;

	if((_selectedMenu + pannelState) < 0) {
		_selectedMenu +=5;
	} else {
		_selectedMenu += pannelState;
	}
	if(selectedMenu() != "Play") {
		_displayLevels = false;
	}

	_isRotatingHorizontally = true;
}

void Menu::rotateHorizontally(const float dx) {
	_cameras[_chosenCamera]->rotateLeft(dx);
}

void Menu::changeLevel(const int lvlUpOrDown) {

	if((_selectedLevel  -lvlUpOrDown) < 0) {
		_selectedLevel = 0;
		_isRotatingVertically = false;
	} else if ((_selectedLevel -lvlUpOrDown > (_levels.size()-1))) {

		_selectedLevel = _levels.size() - 1;
		_isRotatingVertically = false;
	} else {
	 	_selectedLevel += -lvlUpOrDown;
		std::cout << "Level : " << selectedLevel() << " Selected" <<  std::endl;
		_rotationDirection = -lvlUpOrDown;
		_isRotatingVertically = true;
	}

}


void Menu::rotateVertically(const float dx){
	_cameras[_chosenCamera]->rotateUp(dx);
}


}
