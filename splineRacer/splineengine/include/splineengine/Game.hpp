#pragma once
#ifndef __GAME__HPP
#define __GAME__HPP

#include <string>
#include <list>
#include "common.hpp"
#include "json.hpp"

#include "AssetManager.hpp"
#include "Player.hpp"
#include "Chaser.hpp"
#include "Obstacle.hpp"
#include "Collectable.hpp"

#include "RenderManager.hpp"
#include "Camera.hpp"
#include "POVCamera.hpp"
#include "TrackballCamera.hpp"

namespace splineengine {

// ids of gamemodes
const int CLASSIC = 0;
const int ENDLESS = 1;

// ids of gamestates
const int RUNNING = 0;
const int LEVELWIN = 1;
const int LEVELLOSE = 2;
const int ENDLESSOVER = 3;
const int EXITING = 4;

// name of the 3D model of the player
const std::string playerModelName = "plane";
// how long is displayed the end screen before going back to the menu ?
const float endScreenTime = 5.f;
// maximum distance to the player (folowing the spline) at wich collision checks will happend
const float maxCollideDistance = 50.f;
// maximum distance to the player (folowing the spline) at wich objects will be rendered
const float maxRenderDistance = 70.f;


/// \brief class wich represents the game scene , the player and their mechanics
class Game {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default constructor for infinite game
	    Game();

		/// \brief constructor with level name for loading level
	    Game(const std::string& levelName);

		/// \brief destructor
		~Game();

        // CONST GETTERS
		/// \brief get the player as a const ref
	    const Player& player() const { return _player; }

	    const int gameState() const { return _gameState; }

	    // NON-CONST GETTERS (can be used as setters)
	    /// \brief get the player as a ref
	    Player& player() { return _player; }


		//METHODS

		/// \brief update called at each frame (for the physics)
		void update();

		/// \brief renders the scene at each frame
		void render();

		/// \brief rotate the camera in the horizontal direction by dx pixels
		void moveCameraX(const float dx);
		/// \brief rotate the camera in the vertical direction by dx pixels
		void moveCameraY(const float dy);
		/// \brief zoom the camera view  by a factor of dz
		void zoomCamera(const float dz);
		/// \brief switch between the different available cameras
		void changeCamera();


	private:
		/// \brief creates a radom level
		void generateLevel(const float start, const float finish);
		/// \brief load the given level
		void loadLevel(const std::string& levelName);

		/// \brief returns a single gameobject from it's json description
		//TODO : throw exception when loading a bad file
		GameObject gameObjFromJson(nlohmann::json j);

		/// \brief order a list of gameobject according to their FWD position coordinate
		// TODO : replace template with gameobject polymorphism or check the type or idk ... 
		template <typename T>
		void orderObjListFwd(std::list<T>& objList);

		/// \brief Handle collision between 2 GameObjects
		// TODO : replace template with gameobject polymorphism or check the type or idk ... 
		template <typename T, typename U>
		void handleCollision(T& firstObject, U& secondObject);


		/// \brief renders a list of gameObjects and remove those far behind the player  
		// TODO : replace template with gameobject polymorphism or check the type or idk ... 
		template <typename T>
		void renderObjList(std::list<T>& objList);
		
		/// \brief update the obstacles physics, check for collisions with player 
		///\brief and handle the collision behaviour  
		void updateObstacleList(std::list<Obstacle>&  objList);

		/// \brief update the obstacles physics, check for collisions with player 
		///\brief and handle the collision behaviour  
		void updateCollectableList(std::list<Collectable>&  objList);

		// MEMBERS
		// gamemodes : CLASSIC, ENDLESS
		int _gameMode;
		// state of the game : RUNNING, LEVELWIN, LEVELLOSE, ENDLESSOVER, EXITING
		int _gameState = RUNNING;
		
		// timer before going back to the menu when a end screen is reached
		float _endScreenTimer = endScreenTime;

		/// \brief manage the camera transformations
		RenderManager _renderManager;
		/// \brief vector of pointers on available cameras
		std::vector<std::unique_ptr<Camera>> _cameras;
		/// \brief id of the current camera
		int _chosenCamera;

		/// \brief represents the spline
	    Spline _spline;
		/// \brief represents the player
		Player _player;
		/// \brief represents the skybox
		GameObject _skybox;

		/// \brief the ennemy chasing the player !
		Chaser _alien;

		/// \brief Represents the finish line
		GameObject _finishLine;

		// game objects lists (ordered along the spline acording to their FWD coordinate)
	    std::list<GameObject> _decorations;
	    std::list<Obstacle> _obstacles;
	    std::list<Collectable> _collectables;
};

}
#endif
