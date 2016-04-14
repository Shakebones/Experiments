#include <stdio.h>
#include <glut.h>

extern void get_density(int N, float *density, float *density_prev, float *velocity_u, float *velocity_v, float *velocity_w, float diff, float dt);

extern void get_velocity(int N, float *velocity_u, float *velocity_v,  float *velocity_w, float *velocity_u_prev, float *velocity_v_prev, float *velocity_w_prev, float visc, float dt);

typedef enum {
    false = 0,
    true = 1
} wuBOOL;

const int windowWidth = 1280;
const int windowHeight = 720;

GLfloat translationX;
GLfloat translationY;
GLfloat translationZ;

GLfloat rotationX;
GLfloat rotationY;

int N;

GLfloat timeStep;
GLfloat diffuse;
GLfloat viscocity;
GLfloat force;
GLfloat source;

GLfloat *velocityU;
GLfloat *velocityV;
GLfloat *velocityW;

GLfloat *previousVelocityU;
GLfloat *previousVelocityV;
GLfloat *previousVelocityW;

GLfloat *density;
GLfloat *previousDensity;

GLfloat alpha = 0.03;

wuBOOL addVelocityX = false;
wuBOOL addVelocityY = true;
wuBOOL addVelocityZ = false;
wuBOOL addDensity = true;

wuBOOL drawVelocity = false;

int wuIndex(int i, int j, int k)
{
    const int eachGridSize = N + 2;
    //return i + eachGridSize * j + eachGridSize * eachGridSize * k;
	return i * eachGridSize * eachGridSize + j * eachGridSize + k;
}

void wuInitialize()
{
    rotationX = 20;
    rotationY = -30;
    
    translationX = 0;
    translationY = 0;
    translationZ = -5.0;
    
    N = 42;
    timeStep = 0.1;
    viscocity = 0.0f;
	//diffuse = 0.0f;
    force = 100;
    source = 100.0;
    
    const int eachGridCount = N + 2;
    const int size = eachGridCount * eachGridCount * eachGridCount;
    
    velocityU = (GLfloat *)malloc(size * sizeof(GLfloat));
    velocityV = (GLfloat *)malloc(size * sizeof(GLfloat));
    velocityW = (GLfloat *)malloc(size * sizeof(GLfloat));
    
    previousVelocityU = (GLfloat *)malloc(size * sizeof(GLfloat));
    previousVelocityV = (GLfloat *)malloc(size * sizeof(GLfloat));
    previousVelocityW = (GLfloat *)malloc(size * sizeof(GLfloat));
    
    density = (GLfloat *)malloc(size * sizeof(GLfloat));
    previousDensity = (GLfloat *)malloc(size * sizeof(GLfloat));
    
    memset(velocityU, 0, sizeof(GLfloat) * size);
    memset(velocityV, 0, sizeof(GLfloat) * size);
    memset(velocityW, 0, sizeof(GLfloat) * size);
    
    memset(previousVelocityU, 0, sizeof(GLfloat) * size);
    memset(previousVelocityV, 0, sizeof(GLfloat) * size);
    memset(previousVelocityW, 0, sizeof(GLfloat) * size);
    
    memset(density, 0, sizeof(GLfloat) * size);
    memset(previousDensity, 0, sizeof(GLfloat) * size);
}

void wuSource(GLfloat *density, GLfloat *u, GLfloat *v, GLfloat *w)
{
    int indexX, indexY, indexZ;
    const int eachGridSize = N + 2;
    const int size = eachGridSize * eachGridSize *eachGridSize;
    
    memset(u, 0, sizeof(GLfloat) * size);
    memset(v, 0, sizeof(GLfloat) * size);
    memset(w, 0, sizeof(GLfloat) * size);
    memset(density, 0, sizeof(GLfloat) * size);
 
    if (addVelocityX == true)
    {
        indexX = 2;
        indexY = N/2;
        indexZ = N/2;
        
        u[wuIndex(indexX, indexY, indexZ)] = force;
        addVelocityX = false;
    }
    
    if (addVelocityY == true)
    {
        indexX = N/2;
        indexY = 2;
        indexZ = N/2;
        
        v[wuIndex(indexX, indexY, indexZ)] = force;
        addVelocityY = true;
    }
    
    if (addVelocityZ == true)
    {
        indexX = N/2;
        indexY = N/2;
        indexZ = 2;
        
        w[wuIndex(indexX, indexY, indexZ)] = force;
        addVelocityZ = false;
    }
    
    if (addDensity == true)
    {
        indexX = N/2;
        indexY = 2;
        indexZ = N/2;
        
        density[wuIndex(indexX, indexY, indexZ)] = source;
        addDensity = true;
    }
}

void wuDrawGrid()
{
    glLineWidth(1.0f);
    
    glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.3f, 0.0f, 0.0f);
    
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.3f, 0.0f);
    
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.3f);
    
        glVertex3f(1.3f, 0.0f, 0.0f);
        glVertex3f(1.3f, 1.3f, 0.0f);
    
        glVertex3f(1.3f, 1.3f, 0.0f);
        glVertex3f(0.0f, 1.3f, 0.0f);
    
        glVertex3f(0.0f, 1.3f, 1.3f);
        glVertex3f(0.0f, 0.0f, 1.3f);
    
        glVertex3f(0.0f, 1.3f, 1.3f);
        glVertex3f(0.0f, 1.3f, 0.0f);
    
        glVertex3f(1.3f, 0.0f, 0.0f);
        glVertex3f(1.3f, 0.0f, 1.3f);
    
        glVertex3f(0.0f, 0.0f, 1.3f);
        glVertex3f(1.3f, 0.0f, 1.3f);
    
        glVertex3f(1.3f, 1.3f, 0.0f);
        glVertex3f(1.3f, 1.3f, 1.3f);
    
        glVertex3f(1.3f, 1.3f, 1.3f);
        glVertex3f(1.3f, 0.0f, 1.3f);
    
        glVertex3f(0.0f, 1.3f, 1.3f);
        glVertex3f(1.3f, 1.3f, 1.3f);
    
    glEnd();
}

void wuDrawDensity()
{
    GLfloat positionX;
    GLfloat positionY;
    GLfloat positionZ;
    
    GLfloat density000;
    GLfloat density010;
    GLfloat density100;
    GLfloat density110;
    GLfloat density001;
    GLfloat density011;
    GLfloat density101;
    GLfloat density111;
    
    GLfloat h= 1.3f/N;
    
    glBegin(GL_QUADS);
    for(int x =0; x < N; x++)
    {
        positionX = (x - 0.5f) * h;
        
        for(int y = 0; y < N; y++)
        {
            positionY = (y - 0.5f) * h;
            
            for(int z = 0; z < N; z++)
            {
                positionZ= (z - 0.5f) * h;
                
                density000 = density[wuIndex(x, y, z)];
                density010 = density[wuIndex(x, y + 1, z)];
                density100 = density[wuIndex(x + 1, y, z)];
                density110 = density[wuIndex(x + 1, y + 1, z)];
                
                density001=density[wuIndex(x, y, z + 1)];
                density011=density[wuIndex(x, y + 1, z + 1)];
                density101=density[wuIndex(x + 1, y, z + 1)];
                density111=density[wuIndex(x + 1, y + 1, z + 1)];
                
                glColor4f(density111, density111, density111, alpha);
                glVertex3f(positionX + h, positionY + h, positionZ + h);
                
                glColor4f(density011, density011, density011, alpha);
                glVertex3f(positionX, positionY + h, positionZ + h);
                
                glColor4f(density001, density001, density001, alpha);
                glVertex3f(positionX, positionY, positionZ + h);
                
                glColor4f(density101, density101, density101, alpha);
                glVertex3f(positionX + h, positionY, positionZ + h);
                
                glColor4f(density110, density110, density110, alpha);
                glVertex3f(positionX + h, positionY + h, positionZ);
                
                glColor4f(density111, density111, density111, alpha);
                glVertex3f(positionX + h, positionY + h, positionZ + h);
                
                glColor4f(density101, density101, density101, alpha);
                glVertex3f(positionX + h, positionY, positionZ + h);
                
                glColor4f(density100, density100, density100, alpha);
                glVertex3f(positionX + h, positionY, positionZ);
                
                glColor4f(density010, density010, density010, alpha);
                glVertex3f(positionX, positionY + h, positionZ);
                
                glColor4f(density110, density110, density110, alpha);
                glVertex3f(positionX + h, positionY + h, positionZ);
                
                glColor4f(density100, density100, density100, alpha);
                glVertex3f(positionX + h, positionY, positionZ);
                
                glColor4f(density000, density000, density000, alpha);
                glVertex3f(positionX, positionY, positionZ);
                
                glColor4f(density011, density011, density011, alpha);
                glVertex3f(positionX, positionY + h, positionZ + h);
                
                glColor4f(density010, density010, density010, alpha);
                glVertex3f(positionX, positionY + h, positionZ);
                
                glColor4f(density000, density000, density000, alpha);
                glVertex3f(positionX, positionY, positionZ);
                
                glColor4f(density001, density001, density001, alpha);
                glVertex3f(positionX, positionY, positionZ + h);
                
                glColor4f(density100, density100, density100, alpha);
                glVertex3f(positionX + h, positionY, positionZ);
                
                glColor4f(density000, density000, density000, alpha);
                glVertex3f(positionX, positionY, positionZ);
                
                glColor4f(density001, density001, density001, alpha);
                glVertex3f(positionX, positionY, positionZ + h);
                
                glColor4f(density101, density101, density101, alpha);
                glVertex3f(positionX+h, positionY, positionZ + h);
                
                glColor4f(density110, density110, density110, alpha);
                glVertex3f(positionX + h, positionY + h, positionZ);
                
                glColor4f(density010, density010, density010, alpha);
                glVertex3f(positionX, positionY + h, positionZ);
                
                glColor4f(density011, density011, density011, alpha);
                glVertex3f(positionX, positionY + h, positionZ + h);
                
                glColor4f(density111, density111, density111, alpha);
                glVertex3f(positionX + h, positionY + h, positionZ + h);
            }
        }
    }
    glEnd();
}

void wuDrawVelocity()
{
    GLfloat positionX;
    GLfloat positionY;
    GLfloat positionZ;
    
    GLfloat h = 1.3f/N;
    glColor3f(0.0, 1.0, 0.0);
    
    for (int x = 0; x < N; x++)
    {
        positionX = (x - 0.5f) * h;
        for (int y = 0; y < N; y++)
        {
            positionY = (y - 0.5f) * h;
            for (int z = 0; z < N; z++)
            {
                positionZ = (z - 0.5f) * h;
                glBegin(GL_LINES);
                    glVertex3f(positionX, positionY, positionZ);
                    glVertex3f(positionX + velocityU[wuIndex(x, y, z)]/20,
                               positionY + velocityV[wuIndex(x, y, z)]/20,
                               positionZ + velocityW[wuIndex(x, y, z)]/20);
                glEnd();
            }
        }
    }
    
}

void wuDisplay()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glTranslatef(translationX, translationY, translationZ);
    
    glRotatef(rotationX, 1.0f, 0, 0);
    glRotatef(rotationY, 0, 1.0f, 0);
    
    if (drawVelocity) wuDrawVelocity();
    else wuDrawDensity();
    
    wuDrawGrid();
    glPopMatrix();
    glutSwapBuffers();
}

void wuReshape(GLint width, GLint height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0, (float)width/height, 0.001, 100.0);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f);
}

void wuSpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
        rotationX -= 2.0f;
    }
    
    if(key == GLUT_KEY_DOWN) {
        rotationX += 2.0f;
    }
    
    if(key == GLUT_KEY_LEFT) {
        rotationY += 2.0f;
    }
    
    if(key == GLUT_KEY_RIGHT) {
        rotationY -= 2.0f;
    }
    
    glutPostRedisplay();
}

void wuKeyBoard(unsigned char key, int x, int y)
{
    if(key == 'i' || key == 'I')
    {
        addDensity = true;
    }
    if(key == 'x' || key == 'X')
    {
        addVelocityX = true;
    }
    
    if(key == 'y' || key == 'Y')
    {
        addVelocityY = true;
    }
    
    if(key == 'z' || key == 'Z')
    {
       addVelocityZ = true;
    }
    
    if(key == 'w' || key == 'W')
    {
        translationZ = translationZ + 0.1;
    }
    
    if(key == 's' || key == 'S')
    {
        translationZ = translationZ - 0.1;
    }
    
    if(key == 'a' || key == 'A')
    {
        translationX = translationX + 0.1;
    }
    
    if(key == 'd' || key == 'D')
    {
        translationX = translationX - 0.1;
    }
    
    if(key == 'q' || key == 'Q')
    {
        translationY = translationY + 0.1;
    }
    
    if(key == 'e' || key == 'E')
    {
        translationY = translationY - 0.1;
    }
    
    if(key == 'c' || key == 'C')
    {
        const int size = (N + 2) * (N + 2) * (N + 2);
        
        memset(velocityU, 0, sizeof(GLfloat) * size);
        memset(velocityV, 0, sizeof(GLfloat) * size);
        memset(velocityW, 0, sizeof(GLfloat) * size);
        
        memset(previousVelocityU, 0, sizeof(GLfloat) * size);
        memset(previousVelocityV, 0, sizeof(GLfloat) * size);
        memset(previousVelocityW, 0, sizeof(GLfloat) * size);
        
        memset(density, 0, sizeof(GLfloat) * size);
        memset(previousDensity, 0, sizeof(GLfloat) * size);
    }
    
    if(key == 'v' || key == 'V')
    {
        drawVelocity = !drawVelocity;
    }
}

void wuIdle()
{
    wuSource(previousDensity, previousVelocityU, previousVelocityV, previousVelocityW);
	get_velocity(N, velocityU, velocityV, velocityW, previousVelocityU, previousVelocityV, previousVelocityW, 0.0f, timeStep);
    get_density(N, density, previousDensity, velocityU, velocityV, velocityW, 0.0f, timeStep);    
    glutPostRedisplay();
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    
    wuInitialize();
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("GAS Simulation test");
    
    glutDisplayFunc(wuDisplay);
    glutReshapeFunc(wuReshape);
    glutSpecialFunc(wuSpecialKeys);
    glutKeyboardFunc(wuKeyBoard);
    glutIdleFunc(wuIdle);
    
    glutMainLoop();
    return 0;
}

