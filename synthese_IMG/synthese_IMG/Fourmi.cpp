#include "Fourmi.h"
//================================================================
// Méthodes modélisation fourmi.
void patte()
{
    glPushMatrix();
    glRotatef(15, -1, 0, 0);

    glPushMatrix();
    marron();
    glTranslatef(0, 0, 1.0);
    glScalef(0.15, 0.15, 2.0);
    glutSolidCylinder(1.0, 1.0, 10, 10);
    glPopMatrix();

    glPushMatrix();
    marron();
    glTranslatef(0, 0, 3.15);
    glScalef(0.2, 0.2, 0.2);
    glutSolidSphere(1.0, 10, 10);
    glPopMatrix();

    glPushMatrix();
    marron();

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
    glRotatef(animValue_antenne, 0, 1, 0);

    glPushMatrix();
    marron();
    glTranslatef(0, 0.8, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(0.05, 0.6, 0.05);
    glutSolidCylinder(1, 1, 10, 10);
    glPopMatrix();

    //jointure inter
    glPushMatrix();
    marron();
    glTranslatef(-0.02, 1.35, 0);
    glScalef(0.03, 0.03, 0.03);
    glutSolidSphere(1.0, 10, 10);
    glPopMatrix();

    glPushMatrix();
    marron();
    glTranslatef(0, 1.35, 0);
    glRotatef(90, 0, -1, 0);
    glScalef(0.02, 0.02, 2.0);
    glutSolidCylinder(1, 1, 10, 10);
    glPopMatrix();

    glPopMatrix();
}

void abdomen()
{
    glPushMatrix();
    marron();
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
    marron();
    glScalef(0.5, 0.5, 0.35);
    glRotatef(90, 0, 1.0, 0);
    glutSolidCylinder(1.0, 1.0, 10, 10);
    glPopMatrix();

    marron();
    glTranslatef(1.8, 0, 0);
    glScalef(1.8, 1.2, 1.2);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    glPopMatrix();
}

void mandibule()
{
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glScalef(0.1, 0.1, 1);
    glutSolidCylinder(1, 1, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.1, 0);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.1, 0);
    glRotatef(animValue_mandibule, 0, 0, 1);

    glPushMatrix();
    glRotatef(90, 1, 1, 0);

    glScalef(0.1, 0.1, 1.2);

    glTranslatef(0, 0, 0.05);
    glutSolidCylinder(1, 1, 10, 10);
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
    marron();
    glTranslatef(-2.0, 0, 0);
    glRotatef(90, 0, 1.0, 0);
    glScalef(0.3, 0.3, 0.6);
    glutSolidCylinder(1.0, 1.0, 10, 10);
    glPopMatrix();

    //tête
    glPushMatrix();
    marron();
    glTranslatef(-2.5, 0, 0);
    glScalef(1, 0.7, 0.9);
    glutSolidSphere(1.0, 50, 50);
    glPopMatrix();

    //mandibule droite
    glPushMatrix();
    glColor3f(1, 1, 1);
    marron();

    glTranslatef(-2.5, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(90, 1, 0, 0);

    glPushMatrix();
    glTranslatef(-0.5, -0.8, 0);
    glScalef(0.5, 0.5, 0.5);
    mandibule();
    glPopMatrix();
    glPopMatrix();

    //mandibule gauche
    glPushMatrix();
    glColor3f(1, 1, 1);
    marron();

    glTranslatef(-2.5, 0, 0);
    glRotatef(90, 0, -1, 0);
    glRotatef(90, -1, 0, 0);

    glPushMatrix();
    glTranslatef(-0.5, -0.8, 0);
    glScalef(0.5, 0.5, 0.5);
    mandibule();
    glPopMatrix();
    glPopMatrix();

    //yeux
    glPushMatrix();
    glTranslatef(-2.7, 0, 0);
    glScalef(0.2, 0.2, 0.2);

    glPushMatrix();
    glTranslatef(0, 0.2, -4);
    render_sphere(pts_oeil1, faces_oeil1, n_oeil, m_oeil);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.2, 4);
    render_sphere(pts_oeil2, faces_oeil2, n_oeil, m_oeil);
    glPopMatrix();

    glPopMatrix();

    //antennes
    glPushMatrix();

    glTranslatef(-2.5, 0, 0);
    glRotatef(20, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0, 0, 0.5);
    glRotatef(20, 0, 1, 0);
    antenne();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -0.5);
    glRotatef(20, 0, -1, 0);
    antenne();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}

void fourmi()
{
    abdomen();
    tete();
    queue();

    //pattes coté gauche
    glPushMatrix();
    glRotatef(10 * cos(animValue_patte + (M_PI) / 2), 1, 1, 0);
    patte();
    glPopMatrix();

    glPushMatrix();
    glRotatef(10 * cos(animValue_patte + (M_PI) / 3), 1, 1, 0);
    glPushMatrix();
    glRotatef(45, 0.0, 1.0, 0.0);
    patte();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(10 * cos(animValue_patte + (2 * M_PI) / 3), 1, 1, 0);
    glPushMatrix();
    glRotatef(45, 0.0, -1.0, 0.0);
    patte();
    glPopMatrix();
    glPopMatrix();

    //pattes coté droit
    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);

    glPushMatrix();
    glRotatef(10 * sin(animValue_patte + (M_PI) / 2), 1, 1, 0);
    patte();
    glPopMatrix();

    glPushMatrix();
    glRotatef(10 * sin(animValue_patte + (M_PI) / 3), 1, 1, 0);
    glPushMatrix();
    glRotatef(45, 0.0, -1.0, 0.0);
    patte();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(10 * sin(animValue_patte + (2 * M_PI) / 3), 1, 1, 0);
    glPushMatrix();
    glRotatef(45, 0.0, 1.0, 0.0);
    patte();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}
//=================================================================

void marron()
{
    glColor3f(0.7, 0.3, 0);
}