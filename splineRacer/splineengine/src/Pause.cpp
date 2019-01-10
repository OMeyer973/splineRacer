#include <splineengine/Pause.hpp>


namespace splineengine {

Pause::Pause()
{
	if (debug) std::cout << "pause constructor called " << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;
	RenderManager _renderManager(*_cameras[_chosenCamera]);

}

int Pause::init() {
	// TODO
	if (debug) std::cout << "pause init " << std::endl;

	AssetManager& assetManager = AssetManager::instance();

	_selectedMenu = 1;
	_tickVertical = 0;

	_isMoving = false;

	for(int i=0; i<_pauseArray.size(); i++){
		_pauseItems.push_back(GameObject(
		assetManager.models()["menu"],
		Spline(),
		_pauseArray[i]+ std::string(".png"),
		true,
		Transform(
			glm::vec3(0.f,-2.f + i*4.f,2.f),
			glm::vec3(0.30f),
			glm::vec3(0.f)
		)
	));
	}

	// for(int i =0; i<2;i++){
	// 	_selectors.push_back(GameObject(
	// 		assetManager.models()["prism"],
	// 		Spline(),
	// 		"default.png",
	// 		false,
	// 		Transform(
	// 			glm::vec3(-2.f + i*4.f,2.f,2.f),
	// 			glm::vec3(0.30f),
	// 			glm::vec3(0.f)
	// 		)
	// 	));
	// }
	return 0;
}


void Pause::update() {
	// TODO
	float dt = Settings::instance().deltaTime();
	// for(int i =0; i<_pauseItems.size();i++){ //erreur chelou
	// 	if(_selectedMenu == i){
	// 		_pauseItems[i].setTexture( _pauseArray[i]+ std::string(".png") );
	// 	}else{
	// 		_pauseItems[i].setTexture( _pauseArray[i]+ std::string(".png"));
	// 	}
	// }
	if (_selectedMenu == 1) {
		_pauseItems[1].setTexture("ContinueSelected.png");
	} else {
		_pauseItems[1].setTexture("Continue.png");
	}
	if (_selectedMenu == 0) {
		_pauseItems[0].setTexture("QuitToMenuSelected.png");
	} else {
		_pauseItems[0].setTexture("QuitToMenu.png");
	}
	// if(_isMoving){
	// 	for(int i =0; i<2;i++){
	// 		_selectors[i].sPosition()  += 1.f * _movementDirection * upVec;
	// 	}
	// 	_tickVertical++;
	// 	std::cout << _tickVertical << std::endl;
	// 	if(_tickVertical == 4){
	// 		_isMoving = false;
	// 		_tickVertical =0;
	// 	}
	// }
}


void Pause::render() {
	// TODO
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//_renderManager.splineCamMatrix() = _spline.camMatrix(_player.sPosition());
	//glDepthMask(GL_FALSE);
	_renderManager.updateMenuLights();

	glm::mat4 MVMatrix;
	for(float i=0; i< _pauseItems.size();i++){
		MVMatrix = _pauseItems[i].staticMatrix();
		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix, _pauseItems[i].scale());
		_renderManager.useProgram(TEXTURE);
		_pauseItems[i].draw();

	}
	// for(float i=0; i< _selectors.size();i++){
	// 	MVMatrix = _selectors[i].staticMatrix();
	// 	_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix, _selectors[i].scale());
	// 	_renderManager.useProgram(DIRECTIONAL_LIGHT);
	// 	_selectors[i].draw();
	//
	// }
	//glDepthMask(GL_TRUE);
}


void Pause::moveSelectors(float dy) {
	if((_selectedMenu + dy) > 1) {
		_selectedMenu = 1;
	} else if ((_selectedMenu +dy) < 0) {
		_selectedMenu = 0;
	} else {
		_isMoving = true;
		_selectedMenu += dy;
	}
	_movementDirection = dy;
	if (debug) std::cout << _pauseArray[_selectedMenu] << std::endl;
}


}
