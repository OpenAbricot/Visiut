#include "BackNext.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <QDir>
#include <QFile>
#include <QDebug>

using namespace std;


//! Classe BackNext

//!	Constructeur par d&eacute;faut
/*! Permet de cr&eacute;er un objet BackNext*/
BackNext::BackNext(){
	//On initialise tous les attributs par défaut
    index = 0;
    currentIndex = 0;
    pathName = "";
}

//! Constructeur avec argument
/*!
	Ce constructeur permet de cr&eacute;er un repertoire temporaire pour la sauvegarde d'images temporaires.
	\param _name est le nom de l'image ouverte.
*/
BackNext::BackNext(const char * _name){
    index = 0;
    currentIndex = 0;
	//On récupère le nom du fichier et on la met dans un string
	string name = string(_name);
	//On récupère l'extension de l'image
    string extension = name.substr(name.rfind("."), name.size()-1);
	//On récupère le nom de l'image sans l'extension
    name = name.substr(0,name.rfind("."));
	//Si le répertoire temporaire n'existe pas
	if(!dir_cache.exists()){
		qDebug() << "Fichier existe ? : " << !dir_cache.exists();
		//On crée le repertoire temporaire
		qDebug() << dir_cache.mkpath(dir_cache.path());
		qDebug() << dir_cache.mkdir("tmp");
	}
	//On génere le chemin de l'image temporaire
	pathName = dir_cache.path().toStdString()+"/tmp/"+name+to_string(index)+extension;
}

QDir BackNext::dir_cache = QDir(".visiut3/");

//! M&eacute;thode AddState
/*!
	Cette m&eacute;thode permet d'ajouter un &eacute;tat, c'est &agrave; dire qu'elle va incr&eacute;menter
	un compteur qui contiendra le nombre d'images temporaires enregistr&eacute;s sur le disque.
	\param _index est la nouvelle valeur du compteur. Par d&eacutefaut, _index vaut -1.
*/
void BackNext::addState(int _index){
    if(_index == -1)
		index++;
	else
		index = _index;
	currentIndex = index;
    string extension = pathName.substr(pathName.rfind("."), pathName.size()-1);
    pathName = pathName.substr(0,pathName.rfind("."));
	if(index <= 9)
		pathName = pathName.substr(0,pathName.size()-1)+to_string(index)+extension;
	else
		pathName = pathName.substr(0, pathName.size()-2)+to_string(index)+extension;
}

//! M&eacute;thode RemoveLastState
/*!
	Cette m&eacute;thode d&eacute;cr&eacute;mente le nombre d'images enregistr&eacute;s sur le disque.
*/
void BackNext::removeLastState(){
	currentIndex--;
    RemoveState(index-1);
}

//! M&eacute;thode RemoveState
/*!
	Cette m&eacute;thode permet de supprimer un &eacute;tat pr&eacute;cis&eacute; en param&egrave;tre.
	\param _index est un entier qui correspond &agrave; l'image &agrave; supprimer.
*/
//---------------------------On part du principe qu'on enlevera pas plus de 1000 traitements (À améliorer dans l'avenir)------------------------------------------------//
void BackNext::removeState(int _index){
    index = _index;
    string extension = pathName.substr(pathName.rfind("."), pathName.size()-1);
    pathName = pathName.substr(0,pathName.rfind("."));
    if(index < 9)
        pathName = pathName.substr(0, pathName.size()-1)+to_string(index)+extension;
    else if(index >= 9 && index < 100)
        pathName = pathName.substr(0, pathName.size()-2)+to_string(index)+extension;
    cout << "Remove "+getCurrentStatePathName() << endl;

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//! M&eactue;thode RemoveTemporyFile
/*! Supprime le dossier temporaire qui contient les images temporaires */
void BackNext::removeTemporyFile(){

	while(index > 0){
		QFile::remove(getCurrentStatePathName().data());
		qDebug() << QString(getCurrentStatePathName().data());
		RemoveLastState();
	}

	if(dir_cache.exists()){
		dir_cache.rmdir("tmp");
		dir_cache.rmpath(dir_cache.path());
	}
}

//! M&eacute;thode getCurrentStatePathName
/*!
	\return le chemin de l'image temporaire courante.
*/
string & BackNext::getCurrentStatePathName(){
    return pathName;
}

//! M&eacute;thode getIndexCurrentStatePathName
/*!
	\return l'index courant, l'id de l'image ouverte (courante)
*/
int BackNext::getIndexCurrentStatePathName()const{
    return currentIndex;
}


string to_string(int _nb){
    stringstream ss;
    ss << _nb;
    return ss.str();
}
