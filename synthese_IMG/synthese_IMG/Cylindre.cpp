#include "Cylindre.h"

Point* cylindre(int n, double hauteur, double rayon)
{
    Point* pts_cyl = new Point[n * 2];
    for (int i = 0; i < n; i++)
    {
        double theta = ((double)i / (double)(n/2)) * (2 * M_PI);

        pts_cyl[i].x = rayon * cos(theta);
        pts_cyl[i].y = rayon * sin(theta);
        pts_cyl[i].z = 0;

        pts_cyl[i + n].x = rayon * cos(theta);
        pts_cyl[i + n].y = rayon * sin(theta);
        pts_cyl[i + n].z = hauteur;

        /*
        std::cout << "theta: " << theta << " ";
        std::cout << "point: ";
        std::cout << pts_cyl[i].x << " ";
        std::cout << pts_cyl[i].y << " ";
        std::cout << pts_cyl[i].z << std::endl;
        */
    }

    return pts_cyl;
}

Face* cylindre_faces(Point* pts_cyl, int n)
{
    Face* f_cyl = new Face[n];
    for (int i = 0; i < n; i++)
    {
        Face f{ 0, 0, 0, 0 };

        f.i = i;
        f.l = i + 1;
        f.j = i + n;
        f.k = i + n + 1;
        
        f_cyl[i] = f;
    }
    return f_cyl;
}


void render_cylindre(Face* face_cyl, Point* pts_cyl, int n)
{
    //face supérieure
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
    {
        glVertex3f(pts_cyl[i].x, pts_cyl[i].y, pts_cyl[i].z);
    }
    glEnd();

    for (int i = 0; i < n; i++)
    {
        glBegin(GL_POLYGON);

        glTexCoord2f(((float)i / (float)n), 0);
        glVertex3f(pts_cyl[face_cyl[i].i].x, pts_cyl[face_cyl[i].i].y, pts_cyl[face_cyl[i].i].z);

        glTexCoord2f(((float)i + 1 / (float)n), 1);
        glVertex3f(pts_cyl[face_cyl[i].j].x, pts_cyl[face_cyl[i].j].y, pts_cyl[face_cyl[i].j].z);

        glTexCoord2f(((float)i + 1 / (float)n), 1);
        glVertex3f(pts_cyl[face_cyl[i].k].x, pts_cyl[face_cyl[i].k].y, pts_cyl[face_cyl[i].k].z);

        glTexCoord2f(((float)i / (float)n), 0);
        glVertex3f(pts_cyl[face_cyl[i].l].x, pts_cyl[face_cyl[i].l].y, pts_cyl[face_cyl[i].l].z);

        glEnd();
    }

    //face inférieure
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
    {
        glVertex3f(pts_cyl[i + n].x, pts_cyl[i + n].y, pts_cyl[i + n].z);
    }
    glEnd();
}