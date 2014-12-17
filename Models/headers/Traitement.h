#ifndef __TRAITEMENT_H__
#define __TRAITEMENT_H__
/*
 * @author INFS3D_Prj03 (Benjamin Gounine && Florian Faglin)
 */

//! Traitement
/*! Cette classe contient tous les traitements que l'on peut effectuer sur les images*/
template<class T>
class Traitement{
    /*private :

        unsigned int pixel(T**, float, float, unsigned int, unsigned int, unsigned int, unsigned int);*/
    public :

        //static T** redimentionnement(T**, unsigned int, unsigned int ,unsigned int ,unsigned int);

        static T** Negative(T**, unsigned int, unsigned int);

        static T** VerticalMirror(T**, unsigned int, unsigned int);

        static T** HorizontalMirror(T**, unsigned int, unsigned int);

        //static T** flou_moy(T**, unsigned int, unsigned int);

        //static T** flou(T**, unsigned int, unsigned int);

        //static T** rehaussement_4connexites(T**, unsigned int, unsigned int);

        //static T** rehaussement_8connexites(T**, unsigned int, unsigned int);

        //static T** detect_bord_vertical(T**, unsigned int, unsigned int);

        //static T** detect_bord_horizontal(T** , unsigned int, unsigned int);

        //static T** rotation(T**, unsigned int, unsigned int);

        //static T** histo(T**, unsigned int, unsigned int);
};
/*
template <typename T>
unsigned int Traitement<T>::pixel(T** tab, float i, float j,unsigned int width_in, unsigned int height_in, unsigned int width_out, unsigned int height_out){
    float x(0);
    float y(0);
    x = (float)(i/width_out)*height_in;
    y = (float)(j/height_out)*width_in;
    if(x >= height_in)
        x =  height_in-1;
    if (y >= width_in)
        y =  width_in-1;
    return tab[(unsigned int)x][(unsigned int)y];
}

template <typename T>
T** Traitement<T>::redimentionnement(T** tab_in, unsigned int width_in, unsigned int height_in, unsigned int width_out, unsigned int height_out){
    //Creation d'une copie du tableau mis en entree
    T** tab_out = new T*[height_in];
    for(unsigned int i=0 ; i<height_in ; i++)
        tab_out[i] = new T[width_in];
    //Copie du tableau mis en entree
    for(unsigned int i=0 ; i<height_in ; i++)
        for(unsigned int j=0 ; j<width_in ; j++)
            tab_out[i][j] = tab_in[i][j];
    //Application du traitement pour chaque pixel
    for(unsigned int i=0 ; i< height_out ; i++)
        for(unsigned int j=0 ; j < width_out; j++)
            tab_in[i][j] = pixel(tab_out, i, j, width_in, height_in, width_out, height_out);
        return tab_out;
}*/

template <typename T>
T** Traitement<T>::Negative(T** tab_in, unsigned int width_in, unsigned int height_in)
{
    //Creation d'une copie du tableau mis en entree
    T** tab_out = new T*[height_in];
    for(unsigned int i=0 ; i<height_in ; i++)
        tab_out[i] = new T[width_in];

    //Copie de l'image en mettant la valeur de pixel à 255-la valeur de départ
    for(unsigned int i = 0; i < height_in; i++)
        for(unsigned int j=0; j<width_in; j++)
            tab_out[i][j] = 255 - tab_in[i][j];
    return tab_out;
}

template <typename T>
T** Traitement<T>::VerticalMirror(T** tab_in, unsigned int width_in, unsigned int height_in)
{
    //Creation d'une copie du tableau mis en entree
    T** tab_out = new T*[height_in];
        for(unsigned int i=0 ; i<height_in ; i++)
            tab_out[i] = new T[width_in];

    //Copie de l'image pixel par pixel en inversant les colonnes
    for(unsigned int i = 0; i < height_in; i++)
        for(unsigned int j=0, k=width_in; j<width_in; j++, k--)
            tab_out[i][j] = tab_in[i][k];
    return tab_out;
}

 template <typename T>
 T** Traitement<T>::HorizontalMirror(T** tab_in, unsigned int width_in, unsigned int height_in)
 {
     //Creation d'une copie du tableau mis en entree
     T** tab_out = new T*[height_in];
     for( unsigned int i=0 ; i<height_in ; i++)
        tab_out[i] = new T[width_in];

     //Copie de l'image pixel par pixel en inversant les lignes
     for(unsigned int i = 0; i < height_in; i++)
        for(unsigned int j=0; j<width_in; j++)
                tab_out[i][j] = tab_in[(height_in-1-i)][j];
     return tab_out;
 }
/*
  template <typename T>
 T** Traitement<T>::flou_moy(T** tab_in, unsigned int width_in, unsigned int height_in)
 {

 }

   template <typename T>
T** Traitement<T>::flou(T** tab_in, unsigned int width_in, unsigned int height_in)
 {

 }

 template <typename T>
T** Traitement<T>::rehaussement_4connexites(T** tab_in, unsigned int width_in, unsigned int height_in)
 {

 }

 template <typename T>
T** Traitement<T>::rehaussement_8connexites(T** tab_in, unsigned int width_in, unsigned int height_in)
 {

 }

 template <typename T>
T** Traitement<T>::detect_bord_vertical(T** tab_in, unsigned int width_in, unsigned int height_in)
 {

}

template <typename T>
T** Traitement<T>::detect_bord_horizontal(T** tab_in, unsigned int width_in, unsigned int height_in)
 {

}

 template <typename T>
T** Traitement<T>::rotation(T** tab_in, unsigned int width_in, unsigned int height_in)
{
    //Creation d'une copie du tableau mis en entree
    // inversion des lignes et des colonnes
    T** tab_out = new T*[width_in];
    for(unsigned int i=0 ; i<width_in ; i++)
        tab_out[i] = new T[height_in];

    for(unsigned int i=0; i<width_in; i++)
        for(unsigned int j=0; j<height_in; j++)
            tab_out[i][j] = tab_in[j][i];
    return tab_out;
}

template <typename T>
T** Traitement<T>::histo(T** tab_in, unsigned int width_in, unsigned int height_in)
 {

 }*/
#endif
