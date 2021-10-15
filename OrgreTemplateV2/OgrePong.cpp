#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include <iostream>
#include "OgreTrays.h"

//#include "ConsoleColor.h"
//Hi I updated it again test
using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translatepaddle(0, 0, 50);
Ogre::Vector3 translateball(20, 0, 0);
Ogre::Vector3 boundaryUp(0, 100, 0);
Ogre::Vector3 boundaryDown(0, -100, 0);
Ogre::Vector3 boundaryRight(100, 0, 0);
Ogre::Vector3 boundaryLeft(-100, 0, 0);

class ExampleFrameListener : public Ogre::FrameListener
{
private:
	Ogre::SceneNode* _node;
	
public:

	ExampleFrameListener(Ogre::SceneNode* node)
	{
		_node = node;
		
	}

	bool frameStarted(const Ogre::FrameEvent& evt)
	{
		//_node->translate(Ogre::Vector3(0.1, 0, 0));
		_node->translate(translateball * evt.timeSinceLastFrame);
		if (_node->getPosition().x >= boundaryRight.x)
		{
			translateball = Vector3(-20, 0, 0);
		}
		if (_node->getPosition().x <= boundaryLeft.x)
		{
			translateball = Vector3(20, 0, 0);
		}

		return true;
	}
};

	



class BasicTutorial1
	: public ApplicationContext
	, public InputListener
	

{
public:
	BasicTutorial1();
	virtual ~BasicTutorial1() {}

	OgreBites::TrayListener myTrayListener;
	OgreBites::Label* mInfoLabel;
	void setup();
	
	bool keyPressed(const KeyboardEvent& evt);
	void createFrameListener();
	
	/*virtual bool frameRenderingQueued(const FrameEvent&);*/
private:
	SceneNode* Ballnode;
	SceneNode* Paddlenode;
	Root* root;
	SceneManager* scnMgr;
public:
	
	virtual bool frameRenderingQueued(const FrameEvent& evt) {

		
		Paddlenode->setPosition(translatepaddle);
		return true;
		std::cout << translatepaddle << std::endl;
		
		std::cout << "dumbball" << translateball << std::endl;



		std::cout << Ballnode->getPosition().x;
	};



};






BasicTutorial1::BasicTutorial1()
	: ApplicationContext("Amber and Raquel's OgrePong (ID's 101063331 and 101247804)")
{
}




void BasicTutorial1::setup()
{
	
	//std::cout << white;
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);

	
	// get a pointer to the already created root
	Root* root = getRoot();
	SceneManager* scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// -- tutorial section start --
	//! [turnlights]
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	//! [turnlights]

	//! [newlight]
	Light* light = scnMgr->createLight("MainLight");
	SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	//! [newlight]

	//! [lightpos]
	lightNode->setPosition(20, 80, 50);
	//! [lightpos]

	//! [camera]
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	//camNode->setPosition(0, 47, 222);
	OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
	scnMgr->addRenderQueueListener(mOverlaySystem);
	addInputListener(mTrayMgr);
	int a = 5;
	mInfoLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
	mInfoLabel = mTrayMgr->createLabel(TL_TOPLEFT, "NumberOfLives", "3", 150);
	mInfoLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
	mInfoLabel = mTrayMgr->createLabel(TL_TOPLEFT, "ScoreAmount:", "100", 150);
	mInfoLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Timer", "Time:", 150);
	mInfoLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "TimeLeft", "3:00", 150);
	mInfoLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Frames", "FPS:", 150);
	mInfoLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "FrameAmount", "FrameNumber", 150);

	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);
	//! [camera]

	//! [entity1]

	//! [entity1]

	//! [entity1node]
	SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	//! [entity1node]

	//! [entity1nodeattach]

	//! [entity1nodeattach]

	//! [cameramove]
	camNode->setPosition(0, 200, 0);
	//! [cameramove]
	camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);

	//Now, let's create another Entity and SceneNode, but this time we'll give it a new position.


	//by default it's true


	//root node doesn't have a name




	////! [entity2]
	//Entity* ogreEntity2 = scnMgr->createEntity("ogrehead.mesh");
	//SceneNode* ogreNode2 = scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(84, 48, 0));
	//ogreNode2->attachObject(ogreEntity2);
	////! [entity2]

	//! [entity3]

	//! [entity4]
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Ball", RGN_DEFAULT,
		plane,
		10, 10, 20, 20,
		true,
		1, 5, 5,
		Vector3::UNIT_Z);

	Entity* ent = scnMgr->createEntity("Ball");
	ent->setCastShadows(false);
	Ballnode = scnMgr->createSceneNode("Character");
	Ballnode->attachObject(ent);
	scnMgr->getRootSceneNode()->addChild(Ballnode);
	Ballnode->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.0f));
	//And finally we need to give our ground a material.

	Plane plane2(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Paddle", RGN_DEFAULT,
		plane,
		8, 70, 20, 20,
		true,
		5, 5, 5,
		Vector3::UNIT_Z);

	Entity* groundEntity2 = scnMgr->createEntity("Paddle");
	ent->setCastShadows(false);
	Paddlenode = scnMgr->createSceneNode("Paddle1");
	Paddlenode->attachObject(groundEntity2);
	scnMgr->getRootSceneNode()->addChild(Paddlenode);
	Paddlenode->setPosition(Ogre::Vector3(0.0f, 0, 50.0f));
	Paddlenode->setScale(Ogre::Vector3(7.0, 0.1, 0.2));
	
	createFrameListener();


	// -- tutorial section end --
}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case SDLK_LEFT:
		translatepaddle += Ogre::Vector3(-10, 0, 0);
		std::cout << "dumb up translate:" << translatepaddle << std::endl;
		if (translatepaddle.x <= boundaryLeft.x)
		{
			translatepaddle = Ogre::Vector3(-80, 0, 50);
		}
		break;
	case SDLK_RIGHT:
		translatepaddle += Ogre::Vector3(10, 0, 0);
		std::cout << "dumb down" << translatepaddle << std::endl;
		if (translatepaddle.x >= boundaryRight.x)
		{
			translatepaddle = Ogre::Vector3(80, 0, 50);
		}
		break;

	default:
		break;
	}
	return true;
}



void BasicTutorial1::createFrameListener()
{
	Ogre::FrameListener* FrameListener = new ExampleFrameListener(Ballnode);
	mRoot->addFrameListener(FrameListener);
	Ogre::FrameListener* FrameListener2 = new ExampleFrameListener(Paddlenode);
	mRoot->addFrameListener(FrameListener2);
}


int main(int argc, char** argv)
{
	try
	{
		BasicTutorial1 app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}

//! [fullsource]


