#include <windows.h>
#include <C:\glut-3.7.6-bin\include\GL\glut.h>
#include <stdlib.h>


static int shoulder = 0, elbow = 0, base=0;
//angulos de las uniones (grados de libertad)

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void display(void)
{
    //rutina de render
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);            //Funciones para profundidad

    glColor3f (1.0, 0.0, 0.0);    //Color Rojo
    glutSolidSphere(0.5, 10, 8);//Esfera de la base
    glPushMatrix();
        glRotatef ((GLfloat) base, 0.0, 1.0, 0.0);        //Gira la base en Y
        glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);    //Gira el hombro en Z
        glPushMatrix();                //Guadra el estado de la matriz anterior
            glTranslatef (1.5, 0.0, 0.0);    //Traslada la primer parte en X
            glScalef (3.0, 1.0, 1.0);        //Escala el cubo a un rectangulo
            glColor3f (1.0, 1.0, 1.0);        //Color Blanco
            glutWireCube (1.0);                //Cubo de 1 unidad de lado
        glPopMatrix();                //Bota la matriz recuperando la posicion anterior
        glTranslatef (3, 0.0, 0.0);    //Mueve el punto central al final de la primer pieza
        glColor3f (1.0, 0.0, 0.0);    //Color rojo para la esfera
        glutSolidSphere(0.5, 10, 8);//Esfera de radio 0.5
        glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);    //Angulo de la siguiente union
        glPushMatrix();                //Guadra el estado de la matriz anterior
            glTranslatef (1.5, 0.0, 0.0);    //Ajusta la pieza al inicio de la union
            glScalef (3.0, 1.0, 1.0);        //Escala la matriz
            glColor3f (1.0, 1.0, 1.0);        //Color Blanco
            glutWireCube (1.0);                //Cubo
        glPopMatrix();                //Bota la matriz recuperando la posicion anterior
        glTranslatef (3, 0.0, 0.0);    //Traslada el centro al final del brazo
        glColor3f (1.0, 0.0, 0.0);    //color Rojo
        glutSolidSphere(0.5, 10, 8);//Ultima esfera
    glPopMatrix(); //vuelve a la matriz original (identidad)
    glutSwapBuffers(); //Intercambia los buffers
}

void reshape (int w, int h) //Funcion que adecua el render a la ventana
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 7.0, 12.0, 0.0, 3.0, 0.0, 0.0, 1.0, 0.0);
    //posicion de la camara,    A donde apunta, vector superior
}

void keyboard (unsigned char key, int x, int y) //Control del teclado
{
    switch (key) {
        case 's':
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
            break;
        case 'S':
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();
            break;
        case 'e':
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();
            break;
        case 'E':
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();
            break;
        case 'b':
            base = (base + 5) % 360;
            glutPostRedisplay();
            break;
        case 'B':
            base = (base - 5) % 360;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) //Funcion principal
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
