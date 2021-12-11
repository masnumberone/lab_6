#include <GL/glut.h>
#include<iostream>
#include <math.h>
#include <gl/glaux.h>
#pragma comment(lib, "C:/GL/Lib/GLAUX.LIB")
#pragma comment(lib, "legacy_stdio_definitions.lib")


#define PI 3.141592653
using namespace std;

// ширина и высота окна
int width = 900, height = 900;

GLfloat camera_x = -0.77;
GLfloat camera_y = -0.2;
GLfloat camera_z = -0.23;
GLfloat delta = 0.1f;
GLfloat lightPos[] = { 1.0, 0.8f, 0.85f, 1.0f };
GLfloat floor_1[] = { 0.0f, 1.0f, 0.0f, 0.0f };
GLfloat shadowMat[16];

GLfloat x_1 = 0.35;
GLfloat y_1 = 0.1;
GLfloat z_1 = 0.45;
GLfloat x_2 = 0.04;
GLfloat y_2 = 0.04;
GLfloat z_2 = 0.43;
GLfloat x_3 = 0.4;
GLfloat y_3 = 0.04;
GLfloat z_3 = 0.4;
GLfloat cx = (x_1 + x_2 + x_3) / 3;
GLfloat cy = (y_1 + y_2 + y_3) / 3;
GLfloat cz = (z_1 + z_2 + z_3) / 3;

GLfloat light_ambient[] = { 0.5 ,0.5, 0.5, 0.2 };
GLfloat light_diffuse[] = { 0.3, 0.4, 0.9, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };


void shadow_matrix(GLfloat vPlaneEquation[], GLfloat vLightPos[], GLfloat destMat[]) {
    // точка света
    GLfloat dot;
    dot = vPlaneEquation[0] * vLightPos[0] + vPlaneEquation[1] * vLightPos[1] + vPlaneEquation[2] * vLightPos[2] + vPlaneEquation[3] * vLightPos[3];

    // вычисление проекций
    destMat[0] = dot - vLightPos[0] * vPlaneEquation[0];
    destMat[4] = 0.0f - vLightPos[0] * vPlaneEquation[1];
    destMat[8] = 0.0f - vLightPos[0] * vPlaneEquation[2];
    destMat[12] = 0.0f - vLightPos[0] * vPlaneEquation[3];

    destMat[1] = 0.0f - vLightPos[1] * vPlaneEquation[0];
    destMat[5] = dot - vLightPos[1] * vPlaneEquation[1];
    destMat[9] = 0.0f - vLightPos[1] * vPlaneEquation[2];
    destMat[13] = 0.0f - vLightPos[1] * vPlaneEquation[3];

    destMat[2] = 0.0f - vLightPos[2] * vPlaneEquation[0];
    destMat[6] = 0.0f - vLightPos[2] * vPlaneEquation[1];
    destMat[10] = dot - vLightPos[2] * vPlaneEquation[2];
    destMat[14] = 0.0f - vLightPos[2] * vPlaneEquation[3];

    destMat[3] = 0.0f - vLightPos[3] * vPlaneEquation[0];
    destMat[7] = 0.0f - vLightPos[3] * vPlaneEquation[1];
    destMat[11] = 0.0f - vLightPos[3] * vPlaneEquation[2];
    destMat[15] = dot - vLightPos[3] * vPlaneEquation[3];
}

void myinit() {
    glClearColor(0.78, 0.40, 0.99, 0.0);

    // освещение
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);


    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);


    glShadeModel(GL_FLAT);
    glFrontFace(GL_CCW);
    shadow_matrix(floor_1, lightPos, shadowMat);
}

void list_cube() {

    glNewList(1, GL_COMPILE);
    // BACK

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2d(0, 1);             glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2d(1, 1);             glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2d(1, 0);             glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2d(0, 0);             glVertex3f(1.0, -1.0, 1.0);

    glEnd();

    // FRONT
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2d(1, 0);             glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2d(0, 0);             glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2d(0, 1);             glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2d(1, 1);             glVertex3f(1.0, 1.0, -1.0);
    glEnd();

    // RIGHT
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2d(1, 1);             glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2d(0, 1);             glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2d(0, 0);             glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2d(1, 0);             glVertex3f(1.0, -1.0, 1.0);
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2d(0, 1);             glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2d(1, 1);             glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2d(1, 0);             glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2d(0, 0);             glVertex3f(-1.0, -1.0, 1.0);
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2d(1, 1);             glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2d(0, 1);             glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2d(0, 0);             glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2d(1, 0);             glVertex3f(1.0, 1.0, -1.0);
    glEnd();

    // BOTTON
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2d(1, 0);             glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2d(0, 0);             glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2d(0, 1);             glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2d(1, 1);             glVertex3f(1.0, -1.0, -1.0);
    glEnd();
    glEndList();
}

void draw_light() {
    glPushMatrix();
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glColor3ub(255, 255, 0);
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();
}

void draw_plane() {
    glColor4f(1.0, 0.93, 0.62, 1.0);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(2.0, 0.0, 2.0);
    glVertex3f(-2.0, 0.0, 2.0);
    glVertex3f(-2.0, 0.0, -2.0);
    glVertex3f(2.0, 0.0, -2.0);
    glEnd();
}

void draw_cube() {
    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0);
    glScalef(0.15, 0.15, 0.15);
    glCallList(1);
    glPopMatrix();

}

void draw_shadow() {
    glPushMatrix();
    glMultMatrixf(shadowMat);
    draw_cube();
    glPopMatrix();
}

void display() {
    // сброс трансформаций
    glLoadIdentity();
    // очищаем экрна и буфер глубины
    gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    list_cube();

    
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    draw_plane();

    glEnable(GL_DEPTH_TEST);
    glColor4f(0.1f, 0.1f, 0.1f, 0.5f);
    draw_shadow();
    glDisable(GL_BLEND);

    glColor3f(1.0f, 0.26f, 0.29f);
    draw_cube();

    glDisable(GL_DEPTH_TEST);
    draw_light();



    // отключение источников света
   // glDisable(GL_LIGHT0);
    glFlush();
    glutSwapBuffers();
}

void special_keys(int key, int x, int y) {

    if (key == GLUT_KEY_RIGHT) {
        camera_x += delta * (-camera_z);
        camera_z += delta * (camera_x);
    }

    else if (key == GLUT_KEY_LEFT) {
        camera_x -= delta * (-camera_z); 
        camera_z -= delta * camera_x;
    }

    else if (key == GLUT_KEY_UP) {
        camera_y+= delta * (-camera_z);
        camera_z += delta * (camera_y);
    }

    else if (key == GLUT_KEY_DOWN) {
        camera_y -= delta * (-camera_z);
        camera_z -= delta * (camera_y);
    }
    else if (key == GLUT_KEY_HOME)
    {
        GLfloat LX = lightPos[0] - cx;
        GLfloat LZ = lightPos[2] - cz;
        GLfloat radVn[] = { LZ,-LX };
        GLfloat dl = sqrt(LZ * LZ + LX * LX);
        GLfloat nlightPosX = lightPos[0] + delta * LZ;
        GLfloat nlightPosZ = lightPos[2] - delta * LX;
        GLfloat LX_1 = nlightPosX - cx;
        GLfloat LZ_1 = nlightPosZ - cz;
        GLfloat dl_1 = sqrt(LZ_1 * LZ_1 + LX_1 * LX_1);
        LX_1 *= dl / dl_1;
        LZ_1 *= dl / dl_1;
        lightPos[0] = cx + LX_1;
        lightPos[2] = cz + LZ_1;
        shadow_matrix(floor_1, lightPos, shadowMat);
    }


   // обновление экрана
    glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: {
        exit(0);
        break;
    }
    case ' ': {
        std::cout << "x = " << camera_x << "; y = " << camera_y << "; z = " << camera_z << "\n";
        break;
    }
    }

    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, 10.0, -10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, 10.0, -10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Пусть тут будет куб");

    // инициализация
    myinit();

    // функции обратного вызова
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special_keys);
    glutKeyboardFunc(keyboard);

    // основной цикл рендеринга
    glutMainLoop();
}