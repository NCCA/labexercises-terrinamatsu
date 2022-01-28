#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Util.h>
#include <iostream>

NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget(_parent)
{

}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::changeNumberOfParticles(int _num)
{
  m_emitter->changeNumberParticles(_num);
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
  m_project = ngl::perspective(45.0f, static_cast<float>(_w)/_h, 0.1, 300);
}

const auto ColourShader="ColourShader";

void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  ngl::ShaderLib::loadShader(ColourShader, "shaders/ColourVertex.glsl", "shaders/ColourFragment.glsl");
  ngl::ShaderLib::use(ColourShader);

  m_emitter = std::make_unique<Emitter>(400'000, ngl::Vec3(0.0f,10.0f,0.0f));
  startTimer(10);

  ngl::VAOPrimitives::createSphere("sphere", 0.05f, 20);

  m_view = ngl::lookAt({10,10,10}, {0,0,0}, {0,1,0});
}

void NGLScene::timerEvent(QTimerEvent *_timer)
{
  m_emitter->update();
  update();
}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  rotX.rotateX(m_win.spinXFace);
  rotY.rotateY(m_win.spinYFace);
  m_mouseGlobalTX = rotX * rotY;
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  ngl::VAOPrimitives::draw("sphere");

  ngl::ShaderLib::use(ColourShader);
  ngl::ShaderLib::setUniform("MVP", m_project*m_view*m_mouseGlobalTX);
  
  m_emitter->render();

}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  
  case Qt::Key_Left: m_emitter->updatePos(-0.1f, 0.0f, 0.0f); break;
  case Qt::Key_Right: m_emitter->updatePos(0.1f, 0.0f, 0.0f); break;

  case Qt::Key_Up: m_emitter->updatePos(0.0f, 0.0f, 0.1f); break;
  case Qt::Key_Down: m_emitter->updatePos(0.0f, 0.0f, -0.1f); break;

  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
