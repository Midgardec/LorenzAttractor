#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <vector>

float sigma = 10.0;
float beta = 8.0 / 3.0;
float rho = 28.0;

const int numPointsPerCurve = 100000000;
const float dt = 0.0001;

struct Point {
    float x, y, z;

    Point(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Curve {
    std::vector<Point> points;
    float color[3];
};

std::vector<Curve> curves;

void addCurve() {
    float x = ((float) rand() / (float) RAND_MAX - 0.5) * 20.0;
    float y = ((float) rand() / (float) RAND_MAX - 0.5) * 20.0;
    float z = ((float) rand() / (float) RAND_MAX) * 50.0;

    Curve curve;
    curve.color[0] = (float) rand() / (float) RAND_MAX;
    curve.color[1] = (float) rand() / (float) RAND_MAX;
    curve.color[2] = (float) rand() / (float) RAND_MAX;

    for (int i = 0; i < 1; i++) {
        float dx = sigma * (y - x);
        float dy = x * (rho - z) - y;
        float dz = x * y - beta * z;

        x += dx * dt;
        y += dy * dt;
        z += dz * dt;

        curve.points.emplace_back(x, y, z);
    }

    curves.push_back(curve);
}

void drawCurves() {
    for (const Curve &curve: curves) {
        glBegin(GL_LINE_STRIP);
        glColor3f(curve.color[0], curve.color[1], curve.color[2]);

        for (const Point &point: curve.points) {
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
    }
}
GLfloat angle=0;
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float eyeX = 80 * sin(0.5);
    float eyeY = 50;
    float eyeZ = 80 * cos(0.5);
    float centerX = 0;
    float centerY = 0;
    float centerZ = 0;

    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 1, 0);
    angle+=1.f;
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    drawCurves();

    glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
        case 27: // ESC key
            exit(0);
            break;
    }
}
void animate(int value) {
    for (Curve &curve: curves) {
        Point &lastPoint = curve.points.back();
        float x = lastPoint.x;
        float y = lastPoint.y;
        float z = lastPoint.z;

        for (int i = 0; i < 100; i++) {
            float dx = sigma * (y - x);
            float dy = x * (rho - z) - y;
            float dz = x * y - beta * z;

            x += dx * dt;
            y += dy * dt;
            z += dz * dt;
        }

        curve.points.emplace_back(x, y, z);
    }

    glutPostRedisplay();
    glutTimerFunc(50,animate, value); // вызываем функцию animate снова через 25 миллисекунд
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / (float)height, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Lorenz Attractor");glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(10, animate, 0);

    addCurve();
    addCurve();
    addCurve();
    addCurve();
    addCurve();
    addCurve();
    addCurve();
    addCurve();
    addCurve();
    addCurve();
    addCurve();
    addCurve();

    glutMainLoop();
    return 0;
}

