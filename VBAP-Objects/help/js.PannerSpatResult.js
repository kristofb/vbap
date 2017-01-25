/*2D VU meter configured with 4 speakers at a square corners

C.BARATAY
http://wwww.bzhtec.com

*/

post("2D special vu-meter by C.Baratay http://www.bzhtec.com");inlets=1;outlets=0;var _x = 0;var _y = 0;var _zeroAt = 0;var L_SP = 0.5;var MAX_V = 0.8;var MAX_MAX = MAX_V*MAX_V;// set up inlets/outlets/assist stringssetinletassist(0,"x");setinletassist(1,"y)");setoutletassist(0,"x");setoutletassist(1,"y");setoutletassist(2,"max value");var width = box.rect[2] - box.rect[0];var mysketchbg=new Sketch(width,width)mysketchbg.ortho3d();sketch.ortho3d();var vbrgb = [0.,0.,0.,1.];var vfrgb = [0.73,0.39,0,1.];var vrgb2 = [0.6,0.,0.,1.];var vred = [0.6,0.,0.,1.];var nombre_hp=4;var hp=[-Math.PI/4.0,Math.PI/4.0,Math.PI*3.0/4.0,-Math.PI*3.0/4.0];var source=[0,0,0,0];var vfontsize=0.2;// process argumentsif (jsarguments.length>1)  vfrgb[0] = jsarguments[1]/255.;if (jsarguments.length>2)  vfrgb[1] = jsarguments[2]/255.;if (jsarguments.length>3)  vfrgb[2] = jsarguments[3]/255.;if (jsarguments.length>4)  vbrgb[0] = jsarguments[4]/255.;if (jsarguments.length>5)  vbrgb[1] = jsarguments[5]/255.;if (jsarguments.length>6)  vbrgb[2] = jsarguments[6]/255.;if (jsarguments.length>7)  vrgb2[0] = jsarguments[7]/255.;if (jsarguments.length>8)  vrgb2[1] = jsarguments[8]/255.;if (jsarguments.length>9)  vrgb2[2] = jsarguments[9]/255.;autowatch=1;drawbg();draw();function drawbg() // cette fonction sert � cr�er la position des hps en arriere plan{  with (mysketchbg)  {    glenable("depth_test");    shapeslice(30,40);    glcullface("back");    //   erase background    glclearcolor(vbrgb[0],vbrgb[1],vbrgb[2],vbrgb[3]);    glclear();    moveto(0,0);    // Background sphere    glcolor(vfrgb);    sphere(L_SP);    // choisi la couleur des boules qui symbolisent les hps    glcolor(vfrgb);    // En fonction du nombre de hp que l'on donne,  il dessine les boules.    for(i=0;i<nombre_hp;i++)    {      moveto(L_SP*Math.cos(hp[i]),L_SP*Math.sin(hp[i]));      sphere(0.20);    }    draw();    refresh();  }}function draw(){  with (sketch)  {    glenable("depth_test");    shapeslice(20,40);    glcullface("back");    // erase background    glclearcolor(vbrgb[0],vbrgb[1],vbrgb[2],vbrgb[3]);    glclear();    // Apres avoir effac� le fond,    // on affiche l'image qui contient les hps    // En utilisant cette m�thode, on a un r�sultat bien plus efficace que    // si on dessine les hps � chaque fois que l'on d�place le curceur.    copypixels(mysketchbg,0,0);    // En fonction du nombre de hp que l'on donne,  il dessine les boules.    for(i=0;i<nombre_hp;i++)    {      moveto(L_SP*Math.cos(hp[i]),L_SP*Math.sin(hp[i]));      vrgb2[0] = (source[i]>1) ? 1 : source[i];      vrgb2[1] = source[i]>=1 ? 0 : 1;      glcolor(vrgb2);      sphere(source[i]*L_SP);    }  }}function sourcegain(n,g){	source[n-1] = g;}function bang(){	draw();	refresh();}function hp_pos(){  hp=[]; // efface les anciennes donn�es.  nombre_hp=arguments.length;  for(i=0;i<arguments.length;i++)  {    hp[i]=((((360-arguments[i])+_zeroAt)/180.0*Math.PI));  }  drawbg();  refresh();}function forcesize(w,h){  if (w!=h)  {    h = w;    box.size(w,h);  }}forcesize.local = 1;function onresize(w,h){  forcesize(w,h);  width = box.rect[2] - box.rect[0];  mysketchbg=new Sketch(width,width); //Lorsque l'objet est redimensionn�,  //on redimensionne �galement la deuxieme sketch  mysketchbg.ortho3d();  draw();  refresh();}onresize.local = 1; //privatefunction fsaa(v){  sketch.fsaa = v;  bang();}function frgb(r,g,b){  vfrgb[0] = r/255.;  vfrgb[1] = g/255.;  vfrgb[2] = b/255.;  draw();  refresh();}function rgb2(r,g,b){  vrgb2[0] = r/255.;  vrgb2[1] = g/255.;  vrgb2[2] = b/255.;  draw();  refresh();}function brgb(r,g,b){  vbrgb[0] = r/255.;  vbrgb[1] = g/255.;  vbrgb[2] = b/255.;  draw();  refresh();}