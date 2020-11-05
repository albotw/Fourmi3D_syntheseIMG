#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

/*class Point*/
class Point {
public:
    //coordonnées x, y et z du point
    double x;
    double y;
    double z;
    // couleur r, v et b du point
    float r;
    float g;
    float b;
};
//Tableau pour stocker les sommets du cube et leur couleur

char presse;
int anglex, angley, x, y, xold, yold;
int haut = 0;

double animValue_tete = 0.0;
bool incrTete = true;
double animValue_queue = 0.0;
bool incrQueue = false;

double zoom = 60.0f;
GLfloat posProj[4];
GLfloat posAmbient[4];

void affichage();
void clavier(unsigned char touche, int x, int y);
void reshape(int x, int y);
void idle();
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
//====================================================
void specialKeyInput(int key, int x, int y);
double toRadians(double degres);

int main(int argc, char** argv)
{
    /* initialisation de glut et creation
       de la fenetre */
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    //glShadeModel(GL_SMOOTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("cube");

    /* Initialisation d'OpenGL */
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

    //couleur des polygones
    //GLfloat ambientMat[] = { 0.24725, 0.1995, 0.0745 };
    //GLfloat diffuseMat[] = { 0.75164, 0.60648, 0.22649 };
    //GLfloat specularMat[] = { 0.628281, 0.555802, 0.366065 };
    //GLfloat alphaMat = 51.2;

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMat);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularMat);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMat);
    //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, alphaMat);

    //lumière
    glEnable(GL_LIGHTING);

    posProj[0] = 0;
    posProj[1] = 10;
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

    posAmbient[0] = 0;
    posAmbient[1] = -5;
    posAmbient[2] = 0;

    GLfloat ambient2[] = { 0.0, 0.5, 0.0, 1.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient2);
    glLightfv(GL_LIGHT1, GL_POSITION, posAmbient);
    glEnable(GL_LIGHT1);


    //fonctions glut
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

void idle()
{
    if (animValue_tete >= 15.0)
    {
        incrTete = false;
    }
    else if (animValue_tete <= -15.0)
    {
        incrTete = true;
    }

    if (animValue_queue >= 10.0)
    {
        incrQueue = false;
    }
    else if (animValue_queue <= -10.0)
    {
        incrQueue = true;
    }

    if (incrTete)
        animValue_tete += 0.01;
    else
        animValue_tete -= 0.01;

    if (incrQueue)
        animValue_queue += 0.05;
    else
        animValue_queue -= 0.05;

    glutPostRedisplay();
}

double toRadians(double degres)
{
    return degres / 180 * M_PI;
}
//================================================================
// Méthodes modélisation fourmi.
void patte()
{
    glPushMatrix();
    glRotatef(15, -1, 0, 0);

    glPushMatrix();
    glColor3f(0.3f, 1.0f, 0.3f);
    glTranslatef(0, 0, 1.0);
    glScalef(0.15, 0.15, 2.0);
    glutSolidCylinder(1.0, 1.0, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.3, 0.3);
    glTranslatef(0, 0, 3.15);
    glScalef(0.2, 0.2, 0.2);
    glutSolidSphere(1.0, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3, 1.0, 0.3);

    glTranslatef(0, 0, 3.15);
    glRotatef(90, 1.0, 0.0, 0.0);

    glTranslatef(0, 0, 0.2);
    glScalef(0.10, 0.10, 2.0);
    glutSolidCylinder(1.0, 1.0, 10, 10);
    glPopMatrix();

    glPopMatrix();
}

void antenne()
{
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-3, 0.8, 0.6);
    glRotatef(90, 0, 1, 0);
    glRotatef(45, -1, 0, 0);
    glRotatef(25, 0, 0, 1);
    glScalef(0.05, 0.6, 0.05);
    glutSolidCylinder(1, 1, 10, 10);
    glPopMatrix();

    //jointure inter
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(-3.35, 1.19, 0.85);
    glScalef(0.03, 0.03, 0.03);
    glutSolidSphere(1.0, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.4, 0.5, 0.6);
    glTranslatef(-3.35, 1.19, 0.85);
    glRotatef(90, 0, -1, 0);
    glScalef(0.02, 0.02, 2.0);
    glutSolidCylinder(1, 1, 10, 10);
    glPopMatrix();
}

void abdomen()
{
    glPushMatrix();
    glColor3f(1.0, 0.3, 0.3);
    glScalef(1.6, 1.0, 1.0);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}

void queue()
{
    glPushMatrix();
    glRotatef(animValue_queue, 0, 0, 1);

    glPushMatrix();

    glTranslatef(1.4, 0, 0);
    glRotatef(20, 0, 0, 1);

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(0.5, 0.5, 0.35);
    glRotatef(90, 0, 1.0, 0);
    glutSolidCylinder(1.0, 1.0, 10, 10);
    glPopMatrix();

    glColor3f(0.0f, 0.4f, 0.6f);
    glTranslatef(1.8, 0, 0);
    glScalef(1.8, 1.2, 1.2);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    glPopMatrix();
}

void tete()
{
    //animation continue
    glPushMatrix();
    glRotatef(animValue_tete, 0, 1, 0);
        //jointure
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-2.0, 0, 0);

        glRotatef(90, 0, 1.0, 0);
        glScalef(0.3, 0.3, 0.6);
        glutSolidCylinder(1.0, 1.0, 10, 10);
        glPopMatrix();

        //tête
        glPushMatrix();
        glColor3f(0.4, 0.4, 0.7);
        glTranslatef(-2.5, 0, 0);
        glScalef(0.9, 0.7, 0.9);
        glutSolidSphere(1.0, 50, 50);
        glPopMatrix();

        //yeux
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-3.2, 0, 0);
        glScalef(0.2, 0.2, 0.2);

        glPushMatrix();
        glTranslatef(0, 0, -2);
        glutSolidSphere(1, 50, 50);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0, 2);
        glutSolidSphere(1, 50, 50);
        glPopMatrix();

        glPopMatrix();

        //antennes
        antenne();

        glPushMatrix();
        glScalef(1.0, 1.0, -1.0);
        antenne();
        glPopMatrix();
    glPopMatrix();
}
//=================================================================

void affichage()
{
    int i, j;
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    // recadrage de l'afichage
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 500.0 / 500.0, 0.1, 100.0);
    
    //glLoadIdentity();
    //glOrtho(-10, 10, -10, 10, -7, 15);
    glPopMatrix();

    //affichage des polygones
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(angley, 1.0, 0.0, 0.0);
    glRotatef(anglex, 0.0, 1.0, 0.0);
    
    //glPopMatrix();

    glLightfv(GL_LIGHT0, GL_POSITION, posProj);
    glLightfv(GL_LIGHT1, GL_POSITION, posAmbient);

    abdomen();
    queue();
    tete();

    //pattes coté gauche
    patte();

    glPushMatrix();
    glRotatef(45, 0.0, 1.0, 0.0);
    patte();
    glPopMatrix();

    glPushMatrix();
    glRotatef(45, 0.0, -1.0, 0.0);
    patte();
    glPopMatrix();

    //pattes coté droit
    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    patte();

    glPushMatrix();
    glRotatef(45, 0.0, -1.0, 0.0);
    patte();
    glPopMatrix();

    glPushMatrix();
    glRotatef(45, 0.0, 1.0, 0.0);
    patte();
    glPopMatrix();

    glPopMatrix();

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

    //On echange les buffers
    glutSwapBuffers();
}

void clavier(unsigned char touche, int x, int y)
{
    switch (touche)
    {
    case 'z':
        zoom -= 10.0f;
        std::cout << "zoom: " << zoom << std::endl;
        glutPostRedisplay();
        break;

    case 'Z':
        zoom += 10.0f;
        std::cout << "zoom: " << zoom << std::endl;
        glutPostRedisplay();
        break;

    case 'p': /* affichage du carre plein */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();
        break;
    case 'f': /* affichage en mode fil de fer */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();
        break;
    case 's': /* Affichage en mode sommets seuls */
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glutPostRedisplay();
        break;
    case 'd':
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;
    case 'D':
        glDisable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;
    case 'm':
        haut += 1;
        affichage();
        break;
    case 'q': /*la touche 'q' permet de quitter le programme */
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
    /* si on appuie sur le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        presse = 1; /* le booleen presse passe a 1 (vrai) */
        xold = x; /* on sauvegarde la position de la souris */
        yold = y;
    }
    /* si on relache le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        presse = 0; /* le booleen presse passe a 0 (faux) */
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
    if (presse) /* si le bouton gauche est presse */
    {
        /* on modifie les angles de rotation de l'objet
       en fonction de la position actuelle de la souris et de la derniere
       position sauvegardee */
        anglex = anglex + (x - xold);
        angley = angley + (y - yold);
        glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold = x; /* sauvegarde des valeurs courante de le position de la souris */
    yold = y;
}
