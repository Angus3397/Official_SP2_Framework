/******************************************************************************/
/*!
\file	Assignment02.cpp
\author Team NoticeMeSenpai
\brief
Set up and Build model keroro 
*/
/******************************************************************************/
#include "2D_PhysicAndCollision.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "GLFW\glfw3.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Light.h"
#include "Utility.h"
#include "MyMath.h"
#include "LoadTGA.h"

/******************************************************************************/
/*!
\brief
Default constructor - initialise variables 
*/
/******************************************************************************/
twoD_scene::twoD_scene()
{

}


/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
twoD_scene::~twoD_scene()
{
}

/******************************************************************************/
/*!
\brief
Initialise OPENGL or variables
*/
/******************************************************************************/
void twoD_scene::Init()
{
    // Init VBO here
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //Enable depth buffer and depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Default to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    m_programID = LoadShaders("Shader//Texture.vertexshader","Shader//Blending.fragmentshader" );
    m_parameters[U_MVP] = glGetUniformLocation(m_programID,"MVP");
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

    // Use our shader
    glUseProgram(m_programID);

    //Initialize all meshes here
    meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 1.0f, 0.25f), 1.f);

    meshList[GEO_LINE] = MeshBuilder::GenerateLines("line", Color(1, 0, 0), hb1.unitVecX.x, hb1.unitVecX.y, hb1.Position.x, hb1.Position.y);

    meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//MineCraftText.tga");
    glGenerateMipmap(GL_TEXTURE_2D);

    Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.LoadMatrix(ortho);

    translateX = translateY  = tx = ty = rotate  = r = 0;
    scale = s = 1.f;
    velocity = 10.f;
}

/******************************************************************************/
/*!
\brief
Update screen

\param dt - time
*/
/******************************************************************************/
void twoD_scene::Update(double dt)
{
    if(Application::IsKeyPressed('D'))
    {
        translateX += hb1.unitVecX.x * velocity * dt;
        translateY += hb1.unitVecX.y * velocity * dt;
    }

    if(Application::IsKeyPressed('A'))
    {
        translateX -= hb1.unitVecX.x * velocity * dt;
        translateY -= hb1.unitVecX.y * velocity * dt;
    }

    if(Application::IsKeyPressed('W'))
    {
        if (collide == true)
        {
            Vector2 impulse;
            Vector2 normalw(0, 1);
            impulse = -(hb1.unitVecY * normalw) * normalw;
            hb1.unitVecY += impulse * 10;
        }
        translateY += hb1.unitVecY.y * velocity * dt;
        translateX += hb1.unitVecY.x * velocity * dt;
    }

    if(Application::IsKeyPressed('S'))
    {
        if (collide == true)
        {
            Vector2 impulse;
            Vector2 normalw(0, 1);
            impulse = -(hb1.unitVecY * normalw) * normalw;
            hb1.unitVecY += impulse;
        }

        translateY -= hb1.unitVecY.y * velocity * dt;
        translateX -= hb1.unitVecY.x * velocity * dt;
    }

    if(Application::IsKeyPressed('Z'))
    {
        scale += dt;
    }

    if(Application::IsKeyPressed('X'))
    {
        scale -= dt;
    }
    
    if(Application::IsKeyPressed('R'))
    {
        r += velocity *dt;
    }
    
    //rotate += dt * velocity;
    s = 5;
    tx = ty = 30;
    collide = false;
    t = dt;
}

/******************************************************************************/
/*!
\brief
Render mesh code

\param mesh
\param enableLight - turn on or off lightning on the object
*/
/******************************************************************************/
void twoD_scene::RenderMesh(Mesh *mesh, bool enableLight)
{
    Mtx44 MVP, objView, objView_inverse_transpose;

    MVP = projectionStack.Top() * viewStack.Top() * sceneStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

    if(mesh->textureID > 0)
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    }

    else
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
    }


    mesh->Render();

    if(mesh->textureID > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

/******************************************************************************/
/*!
\brief
Render text in 3D world

\param mesh
    mesh list

\param text
    text to be render on the screen

\param color
    color of the text
*/
/******************************************************************************/
void twoD_scene::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;
	
	glDisable(GL_DEPTH_TEST);

    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

    float offset = 0;

	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 0.55f, 0, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * sceneStack.Top() * characterSpacing;
	    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

/******************************************************************************/
/*!
\brief
Render text on screen

\param mesh
    mesh list

\param text
    text to be render on the screen

\param color
    color of the text

\param size 
    size of the text

\param x
    x position of the text

\param y
    y position of the text
*/
/******************************************************************************/
void twoD_scene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
    if(!mesh || mesh->textureID <= 0) //Proper error check
		return;
	
	glDisable(GL_DEPTH_TEST);

    //Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	sceneStack.PushMatrix();
	sceneStack.LoadIdentity(); //Reset modelStack
	sceneStack.Scale(size, size, size);
	sceneStack.Translate(x, y, 0);

    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.55f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * sceneStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}

    sceneStack.PopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

    projectionStack.PopMatrix();
	viewStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

/******************************************************************************/
/*!
\brief
render all obj or models here
*/
/******************************************************************************/
string convert (float number){
    std::ostringstream buff;
    buff << number;
    return buff.str(); 
}

void twoD_scene::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Mtx44 Translate, Rotate, Scale;
    Mtx44 model;
    Translate.SetToIdentity();
    Rotate.SetToIdentity();
    Scale.SetToIdentity();
    model.SetToIdentity();
    
    

    // first square
    sceneStack.PushMatrix();
    sceneStack.Translate(translateX, translateY, 0);
    sceneStack.Rotate(r, 0, 0, 1);
    sceneStack.Scale(scale, scale, 1);
    RenderMesh(meshList[GEO_QUAD], false);

    /*hb1.Set(
        Vector2(( ( ((1* scale) * (cos(r))) + ((-1* scale) * (-sin(r))) ) + translateX), ( (((1* scale) * (sin(r))) + ((-1* scale) * cos(r))) + translateY)), 
        Vector2(( ( ((1* scale) * (cos(r))) + ((1* scale) * (-sin(r))) ) + translateX), ( (((1* scale) * (sin(r))) + ((1* scale) * cos(r))) + translateY)),
        Vector2(( ( ((-1* scale) * (cos(r))) + ((1* scale) * (-sin(r))) ) + translateX), ( (((-1* scale) * (sin(r))) + ((1* scale) * cos(r))) + translateY)), 
        Vector2(( ( ((-1* scale) * (cos(r))) + ((-1* scale) * (-sin(r))) ) + translateX), ( (((-1* scale) * (sin(r))) + ((-1* scale) * cos(r))) + translateY)));*/
    sceneStack.PopMatrix();

    Translate.SetToTranslation(translateX, translateY, 0);
    Rotate.SetToRotation(r, 0, 0, 1);
    Scale.SetToScale(scale, scale, 4);

    hb1.Set(
        Translate * Rotate * Scale *Vector2(1 ,-1) , 
        Translate * Rotate * Scale *Vector2(1 ,1),
        Translate * Rotate * Scale *Vector2(-1 ,1), 
        Translate * Rotate * Scale *Vector2(-1 ,-1));






    meshList[GEO_LINE] = MeshBuilder::GenerateLines("line", Color(1, 0, 0), hb1.unitVecX.x + translateX, hb1.unitVecX.y + translateY, hb1.Position.x, hb1.Position.y);
    meshList[GEO_LINE2] = MeshBuilder::GenerateLines("line", Color(0, 0, 1), hb1.unitVecY.x + translateX, hb1.unitVecY.y + translateY, hb1.Position.x, hb1.Position.y);

    // line
    sceneStack.PushMatrix();
    RenderMesh(meshList[GEO_LINE], false);
    sceneStack.PopMatrix();

    // line
    sceneStack.PushMatrix();
    RenderMesh(meshList[GEO_LINE2], false);
    sceneStack.PopMatrix();




    Translate.SetToIdentity();
    Rotate.SetToIdentity();
    Scale.SetToIdentity();
    model.SetToIdentity();

    // second square
    sceneStack.PushMatrix();
    sceneStack.Translate(tx, ty, 0);
    sceneStack.Rotate(rotate, 0, 0, 1);
    sceneStack.Scale(s, s, 1);
    RenderMesh(meshList[GEO_QUAD], false);


    Translate.SetToTranslation(tx, ty, 0);
    Rotate.SetToRotation(rotate, 0, 0, 1);
    Scale.SetToScale(s, s, 4);
    hb2.Set(
        Translate * Rotate * Scale *Vector2(1 ,-1) , 
        Translate * Rotate * Scale *Vector2(1 ,1),
        Translate * Rotate * Scale *Vector2(-1 ,1), 
        Translate * Rotate * Scale *Vector2(-1 ,-1));

    sceneStack.PopMatrix();

    check.SATCheckCollision(hb1, hb2, collide);

    std::cout << collide << std::endl;

    // text
    RenderTextOnScreen(meshList[GEO_TEXT], convert(hb1.HalfHeight) + " :halfHeight", Color(1, 1, 1), 2, 2, 27);
    RenderTextOnScreen(meshList[GEO_TEXT], convert(hb1.HalfWidth) + " :halfWidth", Color(1, 1, 1), 2, 2, 25);
    RenderTextOnScreen(meshList[GEO_TEXT], "[" + convert(hb1.unitVecX.x) + ", " +  convert(hb1.unitVecX.y)+"] unitVecX", Color(1, 1, 1), 2, 2, 23);
    RenderTextOnScreen(meshList[GEO_TEXT], "[" + convert(hb1.unitVecY.x) + ", " +  convert(hb1.unitVecY.y)+"] unitVecY", Color(1, 1, 1), 2, 2, 21);
    RenderTextOnScreen(meshList[GEO_TEXT], "[" + convert(hb1.Position.x) + ", " +  convert(hb1.Position.y)+"] center", Color(1, 1, 1), 2, 2, 19);
}

/******************************************************************************/
/*!
\brief
Delete buffers
*/
/******************************************************************************/
void twoD_scene::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}