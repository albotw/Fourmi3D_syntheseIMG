#include "Sphere.h"


Point* sphere(int n, int m)
{
    Point* sphere = new Point[n * m]{ 0 };

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double theta = 1 * ((double)j / (double)(m - 1.0)) * M_PI;
            double phi = 1 * ((double)i / (double)n) * (2 * M_PI);

            sphere[j + (i * m)].x = sin(theta) * cos(phi);
            sphere[j + (i * m)].z = sin(theta) * sin(phi);
            sphere[j + (i * m)].y = cos(theta);

            std::cout << "point " << (j + (i * m)) << ":";
            std::cout << sphere[j + (i * m)].x << " ";
            std::cout << sphere[j + (i * m)].y << " ";
            std::cout << sphere[j + (i * m)].z << " " << std::endl;
        }
    }
    return sphere;
}

Face* sphere_faces(Point* sphere, int n, int m)
{
    Face* face_sphere = new Face[n * m]{ 0 };
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            Face f{ 0, 0, 0, 0 };
            //glTexCoord2d((double)i/((double)n-1), (double)j/((double)m-1));

            f.i = (i * m) + j;
            f.l = (i * m) + j + 1;

            if (i != n - 1)
            {
                std::cout << "path 1 ";
                f.j = (i + 1) * m + j;
                f.k = (i + 1) * m + j + 1;

            }
            else
            {
                std::cout << "path 2 ";
                f.j = j;
                f.k = j + 1;
            }

            std::cout << "face: ";
            std::cout << f.i << " " << f.j << " " << f.k << " " << f.l << std::endl;

            face_sphere[j + (i * m)] = f;
        }
    }

    return face_sphere;
}

void render_sphere(Point* sphere, Face* face_sphere, int n, int m)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < (n * m); i++)
    {
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(sphere[face_sphere[i].i].x, sphere[face_sphere[i].i].y, sphere[face_sphere[i].i].z);
        glVertex3f(sphere[face_sphere[i].j].x, sphere[face_sphere[i].j].y, sphere[face_sphere[i].j].z);
        glVertex3f(sphere[face_sphere[i].k].x, sphere[face_sphere[i].k].y, sphere[face_sphere[i].k].z);
        glVertex3f(sphere[face_sphere[i].l].x, sphere[face_sphere[i].l].y, sphere[face_sphere[i].l].z);
    }
    glEnd();
}