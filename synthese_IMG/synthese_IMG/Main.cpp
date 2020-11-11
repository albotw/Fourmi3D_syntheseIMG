#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "Sphere.h"
#include "Fourmi.h"

//================================================
/*variables*/

char presse;
int anglex, angley, x, y, xold, yold;
int haut = 0;

double zoom = 60.0f;
GLfloat posProj[4];
GLfloat posAmbient[4];

int width;
int height;
int bpp;
unsigned char* tex;

//===================================================
/*signatures des méthodes*/
void affichage();
void clavier(unsigned char touche, int x, int y);
void reshape(int x, int y);
void idle();
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
void specialKeyInput(int key, int x, int y);
void updateAnimPattes();
unsigned char* loadJpegImage(const char* fichier, int* width, int* height, int* bpp);

int main(int argc, char** argv)
{
    /*création et paramètrage de la fenêtre et de GLUT*/
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("cube");

    /* Initialisation d'OpenGL */
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    
    /*coloration des polygones*/
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);

    /*Lumière 0: spot blanc au dessus de la fourmi*/
    posProj[0] = 0;
    posProj[1] = 15;
    posProj[2] = 0;
    posProj[3] = 0;
    GLfloat dirProj[] = { 0.0, 0.0, 0.0 };
    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01);
    glLightfv(GL_LIGHT0, GL_POSITION, posProj);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirProj);
    glEnable(GL_LIGHT0);

    /*Lumière 1: ambiente verte en dessous de la fourmi*/
    posAmbient[0] = 0;
    posAmbient[1] = -5;
    posAmbient[2] = 0;
    GLfloat ambient2[] = { 0.0, 0.4, 0.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient2);
    glLightfv(GL_LIGHT1, GL_POSITION, posAmbient);
    glEnable(GL_LIGHT1);

    /*création des yeux (primitive Sphere)*/
    pts_oeil1 = sphere(n_oeil, m_oeil);
    faces_oeil1 = sphere_faces(pts_oeil1, n_oeil, m_oeil);

    pts_oeil2 = sphere(n_oeil, m_oeil);
    faces_oeil2 = sphere_faces(pts_oeil2, n_oeil, m_oeil);

    /*chargement et paramétrage des textures*/
    tex = loadJpegImage("noir.png", &width, &height, &bpp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    /*liaison fonctions glut avec fonctions définies*/
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutIdleFunc(idle);
    glutSpecialFunc(specialKeyInput);

    glutMainLoop();
    
    return 0;
}

unsigned char* loadJpegImage(const char* fichier, int* width, int* height, int* bpp)
{
    /*chargement de l'image*/
    unsigned char* image = stbi_load(fichier, width, height, bpp, 3);

    /*vérification du chargement*/
    if (image == nullptr)
        std::cout << "Erreur, impossible de charger l'image " << fichier << std::endl;
    else
        std::cout << "Texture chargee: " << fichier << std::endl;

    return image;
}


void updateAnimPattes()
{
    /*mise a jour de l'animation des pattes. pas dans idle() car déclenchée par un event clavier*/
    if (incrPatte)
        animValue_patte += 0.3;
    else
        animValue_patte -= 0.5;
}

void idle()
{
    /*mise a jour des animations*/

    /*vérification des seuils*/
    if (animValue_tete >= 15.0)
        incrTete = false;
    else if (animValue_tete <= -15.0)
        incrTete = true;

    if (animValue_queue >= 10.0)
        incrQueue = false;
    else if (animValue_queue <= -10.0)
        incrQueue = true;

    if (animValue_antenne >= 10.0)
        incrAntenne = false;
    else if (animValue_antenne <= 0.9)
        incrAntenne = true;

    if (animValue_mandibule >= 10.0)
        incrMandibule = false;
    else if (animValue_mandibule <= 0.0)
        incrMandibule = true;

    /*modification des valeurs*/
    if (incrTete)
        animValue_tete += 0.01;
    else
        animValue_tete -= 0.01;

    if (incrQueue)
        animValue_queue += 0.01;
    else
        animValue_queue -= 0.01;

    if (incrAntenne)
        animValue_antenne += 0.1;
    else
        animValue_antenne -= 0.1;

    if (incrMandibule)
        animValue_mandibule += 0.04;
    else
        animValue_mandibule -= 0.04;

    /*actualisation de l'affichage*/
    glutPostRedisplay();
}

void affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    /*définition de la perspective et application du zoom*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 500.0 / 500.0, 0.1, 100.0);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*positionnement de la caméra*/
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(angley, 1.0, 0.0, 0.0);
    glRotatef(anglex, 0.0, 1.0, 0.0);

    /*application des lumières*/
    glLightfv(GL_LIGHT0, GL_POSITION, posProj);
    glLightfv(GL_LIGHT1, GL_POSITION, posAmbient);

    /*application des textures*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    //fourmi();

    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(1, 0, 0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 1, 0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 0, 1.0);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void clavier(unsigned char touche, int x, int y)
{
    switch (touche)
    {
    case 'z':   /*Zoom avant*/
        zoom -= 10.0f;
        std::cout << "zoom: " << zoom << std::endl;
        glutPostRedisplay();
        break;

    case 'Z':   /*Zomm arriere*/
        zoom += 10.0f;
        std::cout << "zoom: " << zoom << std::endl;
        glutPostRedisplay();
        break;

    case '1': /* affichage du carre plein */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();
        break;
    case '2': /* affichage en mode fil de fer */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();
        break;
    case '3': /* Affichage en mode sommets seuls */
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glutPostRedisplay();
        break;

    case 'e':
        updateAnimPattes();
        glutPostRedisplay();
        break;

    case 27: /*la touche 'q' permet de quitter le programme */
        exit(0);
    }
}

void reshape(int x, int y)
{
    if (x < y)
        glViewport(0, (y - x) / 2, x, x);
    else
        glViewport((x - y) / 2, 0, y, y);
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        presse = 1; 
        xold = x; 
        yold = y;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        presse = 0;
}

void specialKeyInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        angley += 10.0f;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        angley -= 10.0f;
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        anglex += 10.0f;
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        anglex -= 10.0f;
        glutPostRedisplay();
        break;
    }
}

void mousemotion(int x, int y)
{
    if (presse)
    {
        anglex = anglex + (x - xold);
        angley = angley + (y - yold);
        glutPostRedisplay();
    }

    xold = x;
    yold = y;
}
