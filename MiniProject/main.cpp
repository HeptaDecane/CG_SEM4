#include"bits/stdc++.h"
#include"GL/freeglut.h"

#define vertex glVertex3f

int proj = 1, newMouse = 0, mouseRot = 1, mouseTrn = 0, view = 0;

float turn = 50.0, tipp = 30.0, twst = 0.0, xClick = 0, yClick = 0, xtm = 0.0, ytm = 0.0, scale = 1.0, xCar = 0.0;

GLfloat light1spc[] = {0.20, 0.20, 0.15, 1.00},
        light1dfs[] = {0.70, 0.70, 0.65, 1.00},
		light1amb[] = {0.25, 0.25, 0.20, 1.00},
		light1pos[] = {0.20, 2.50, 5.20, 1.00};

GLfloat light2spc[] = {0.00, 0.00, 0.00, 1.00},
        light2dfs[] = {0.30, 0.30, 0.35, 1.00},
		light2amb[] = {0.20, 0.20, 0.25, 1.00},
		light2pos[] = {1.50, -2.00,-4.00, 0.01};

//-----------------------------------------   keybord   --------------------------------------------

void keybord(unsigned char ch, int x, int y){
    std::cout<<"KeyPress '"<<ch<<"'\n";
    switch(ch){
        case 'p':
            proj=!proj;
            break;

        case 'r':
            mouseTrn = 0;
            mouseRot = 1;
            break;

        case 't':
            mouseTrn = 1;
            mouseRot = 0;
            break;

        case 'z':
            turn = 0.0; tipp = 0.0;
            xtm  = 0.0; ytm  = 0.0;
            scale  = 1.0;
            break;

        case '-':
            scale *= 0.92;
            break;

        case '+':
            scale *= 1.06;
            break;

        case 'a':
            xCar += 2.00;
            break;

        case 'd':
            xCar -= 2.00;
            break;

        case ' ':
            view = 1;
            break;

        case  27:
            exit(0);
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

//------------------------------------------   mouse   ---------------------------------------------

void mouse(int button, int state, int x, int y){
    xClick = x;
    yClick = y;

    newMouse = 1;
}

//------------------------------------------   motion   --------------------------------------------

void motion(int x, int y){
    float turnDel, tippDel, xDel, yDel;

    static int c = 0, xSave, ySave;
    static float turnSave = 0.0, tippSave = 0.0;

    if(newMouse){
       newMouse = 0;
       xSave = xClick;
       ySave = yClick;
    }

    if(mouseRot){
       turnDel = x - xSave;
       turn += turnDel;

       tippDel = y - ySave;
       tipp += tippDel;

    }
    else if(mouseTrn){
       xDel = float(x - xSave) * 0.01;
       xtm  += xDel;

       yDel = float(y - ySave) * 0.01;
       ytm  -= yDel;
    }

    xSave = x;
    ySave = y;

    glutPostRedisplay();
}

//---------------------------------------   displayString   ------------------------------------------

void displayString(int x, int y, std::string str, int font){
    int len,i;
	glColor3f(0.502,0.278,0.110);    //rgb(128, 71, 28)
	glRasterPos2f(x, y);
    len = str.length();
    for (i = 0; i < len; i++){
		if(font==1)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
		if(font==2)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
		if(font==3)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,str[i]);
		if(font==4)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);
	}
}

//---------------------------------------   indexView   ------------------------------------------

void indexView(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,900.0,0.0,600.0,50.0,-50.0);

    displayString(300,550,"CGL MINI-PROJECT",1);		//correct cordinate according to name
    displayString(300,549,"__________________",1);
    displayString(50,500,"[]   HELP",2);
    displayString(100,470,"1. MOUSE:",2);
    displayString(150,450,"#  Drag to Change Orientation",2);
    displayString(100,400,"2. KEYBOARD:",2);
    displayString(150,380,"#  A     :   Move Forward",2);
    displayString(150,360,"#  D     :   Move Reverse",2);
    displayString(150,340,"#  +     :   Zoom In",2);
    displayString(150,320,"#  -     :   Zoom Out",2);
    displayString(150,300,"#  P     :   Projection/Perspective",2);
    displayString(150,280,"#  R     :   Rotation Mode",2);
    displayString(150,260,"#  T     :   Translation Mode",2);
    displayString(150,240,"#  Z     :   Initial View",2);
    displayString(150,220,"#  Esc :    Exit",2);
    displayString(300,180,"TAP SPACE BAR TO ENTER",2);
    displayString(750,50,"Batch: H1",3);
    displayString(790,40,"21164",3);
    displayString(790,30,"21165",3);
    displayString(790,20,"21168",3);

    glutPostRedisplay();
}

//---------------------------------------   initLights   ------------------------------------------

void initLights(void){
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1spc);
    glLightfv(GL_LIGHT1, GL_DIFFUSE , light1dfs);
    glLightfv(GL_LIGHT1, GL_AMBIENT , light1amb);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

    glLightfv(GL_LIGHT2, GL_SPECULAR, light2spc);
    glLightfv(GL_LIGHT2, GL_DIFFUSE , light2dfs);
    glLightfv(GL_LIGHT2, GL_AMBIENT , light2amb);
    glLightfv(GL_LIGHT2, GL_POSITION, light2pos);

    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE  );
}

//----------------------------------------   drawRoad   -------------------------------------------

void drawRoad(void){
    glColor3f(0.30,0.25,0.30);
    glEnable(GL_LIGHTING);

    glPushMatrix();
       glTranslatef(0.0, -25.0, 0.0);
       glScalef(2000, 0.3, 3.0);
       glutSolidCube(-20.0f);
    glPopMatrix();
}

//---------------------------------------   renderWheel   -----------------------------------------

void renderWheel(int xt, int yt, int zt){
    glPushMatrix();
        glColor3f(0.32, 0.32, 0.32);
        glTranslatef(xt, yt, zt);
        glutSolidTorus(2,5,12,36);
        glColor3f(0.55, 0.55, 0.55);
        glutSolidTorus(1.5,2,12,36);
    glPopMatrix();
}

//-----------------------------------------   drawCar   -------------------------------------------

void drawCar(void){
    glDisable(GL_LIGHTING);

    glBegin(GL_QUADS);
        glColor3f(0.3, 0.6, 0.6);
        vertex(-40,  0, 15); vertex( 40,  0, 15); vertex( 40,-15, 15); vertex(-40,-15, 15);  // left
        vertex(-40,  0,-15); vertex( 40,  0,-15); vertex( 40,-15,-15); vertex(-40,-15,-15);  // right

        glColor3f(0.4, 0.6, 0.6);
        vertex( 40,  0,-15); vertex( 40,  0, 15); vertex( 40,-15, 15); vertex( 40,-15,-15);  // back
        vertex(-40,  0,-15); vertex(-40,  0, 15); vertex(-40,-15, 15); vertex(-40,-15,-15);  // front

        glColor3f(0.7, 0.7, 0.7);
        vertex(-40.1,-14,-15); vertex(-40.1, -14, 15); vertex(-40.1,-10, 14); vertex(-40.1,-10,-14);  // HeadBeam


        glColor3f(0.4, 0.6, 0.8);
        vertex(-40,  0, 15); vertex(-40,  0,-15); vertex( 40,  0,-15); vertex( 40,  0, 15);  // trunks
        vertex(-10, 10, 15); vertex(-10, 10,-15); vertex( 20, 10,-15); vertex( 20, 10, 15);  // roof

        glColor3f(0.7, 0.6, 0.7);
        vertex(-20,  0, 15); vertex(-10, 10, 15); vertex( 20, 10, 15); vertex( 25,  0, 15);  // window l
        vertex(-20,  0,-15); vertex(-10, 10,-15); vertex( 20, 10,-15); vertex( 25,  0,-15);  // window r

        glColor3f(0.8, 0.7, 0.8);
        vertex(-10, 10, 15); vertex(-20,  0, 15); vertex(-20,  0,-15); vertex(-10, 10,-15);  // windshield
        vertex( 20, 10, 15); vertex( 20, 10,-15); vertex( 25,  0,-15); vertex( 25,  0, 15);  // rear window

       glColor3f(0.4, 0.5, 0.5);
       vertex(-40,-15, 15); vertex(-40,-15,-15); vertex( 40,-15,-15); vertex( 40,-15, 15);  // bottom
    glEnd();


    // Render wheels using torus's with lighting on.

     glEnable(GL_LIGHTING);
     renderWheel(-20,-15, 15);
     renderWheel( 20,-15, 15);
     renderWheel(-20,-15,-15);
     renderWheel( 20,-15,-15);
}

//---------------------------------------   sceneView   ------------------------------------------

void sceneView(void){
    static float x = 2.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(not proj)
        glOrtho(-x, x, -x, x, 0.0, 10.0);
    else
        gluPerspective(60.0, 1.0, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(xtm, ytm, -4.0);                   // Place objects between near and far clipping planes.
    glRotatef(tipp, 1, 0, 0);                       // Rotate around screen horizontal axis.
    glRotatef(turn, 0, 1, 0);                       // Rotate around world vertical axis.
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
    glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
    glScalef(scale, scale, scale);                  // Scale world relative to its origin.
    glScalef(0.02, 0.02, 0.02);

    drawRoad();
    glTranslatef(-xCar, 0.0, 0.0);
    drawCar ();
}

//------------------------------------------   Main Display()   ----------------------------------

void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.996, 0.972, 0.789, 1.0);     //rgb(254,248,196)
    if(not view)
        indexView();
    else
        sceneView();

    glutSwapBuffers();
}

//-----------------------------------------   initGL   --------------------------------------------

void initGL(void)
{
    initLights();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_AMBIENT_AND_DIFFUSE, GL_FRONT);
    glColorMaterial(GL_SPECULAR, GL_FRONT);
}

//----------------------------------------   initGlut   -------------------------------------------

int initGlut(void)
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(800,200);
    glutInitWindowSize(800,800);
    glutCreateWindow("3D Car Model On Road");
    glutKeyboardFunc(keybord);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);


}

//------------------------------------------   main   ----------------------------------------------

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    initGlut();
    initGL();

    glutMainLoop();

    return(0);
}

//-------------------------------------------   END   ----------------------------------------------
