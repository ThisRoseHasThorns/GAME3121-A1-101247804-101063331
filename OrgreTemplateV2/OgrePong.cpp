#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include <iostream>
#include "OgreTrays.h"

using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translatepaddle(-80, 0, 0);
Ogre::Vector3 translateball(0.6, 0, 0);
Ogre::Vector3 boundaryUp(0, 0, -50);
Ogre::Vector3 boundaryDown(0, 0, 50);
Ogre::Vector3 boundaryRight(90, 0, 0);
Ogre::Vector3 boundaryLeft(-100, 0, 0);

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
    virtual bool frameRenderingQueued(const FrameEvent&);

    SceneNode* Ballnode;
    SceneNode* Paddlenode;
};
bool BasicTutorial1::frameRenderingQueued(const FrameEvent& evt) {

    //Ballnode->translate(translateball);
    //Paddlenode->setPosition(translatepaddle);
    return true;
    std::cout << translatepaddle << std::endl;
    //Cant get position of ball to reflext translation. No idea how. 
    std::cout << "dumbball" << translateball << std::endl;

};
BasicTutorial1::BasicTutorial1()
    : ApplicationContext("Amber and Raquel's OgrePong (ID's 101063331 and 101247804)")
{
}


void BasicTutorial1::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 140);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);
    //// and tell it to render into the main window
    //getRenderWindow()->addViewport(cam);

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

    Viewport* vp = getRenderWindow()->addViewport(cam);
   
    vp->setBackgroundColour(ColourValue(0.2, 0.2, 0.2));

    // finally something to render
    Ogre::Entity* ent = scnMgr->createEntity("sphere.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    node->setPosition(70, 0, 0);
    node->setScale(0.025, 0.025, 0.025);


    ////The first thing we'll do is create an abstract Plane object. This is not the mesh, it is more of a blueprint.
    Ogre::Entity* cubeEnt = scnMgr->createEntity("cube.mesh");
    Ogre::SceneNode* cubenode = scnMgr->getRootSceneNode()->createChildSceneNode();
    cubenode->attachObject(cubeEnt);
    cubenode->setPosition(0, -45, 0);
    cubenode->setScale(0.3, 0.02, 0.02);

    //Now we will create a new Entity using this mesh.
    //We want to tell our SceneManager not to cast shadows from our ground Entity. It would just be a waste. Don't get confused, this means the ground won't cast a shadow, it doesn't mean we can't cast shadows on to the ground.
   /* Entity* groundEntity = scnMgr->createEntity("ground");
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Examples/Rockwall");*/
    //And finally we need to give our ground a material.
    
    

}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;

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