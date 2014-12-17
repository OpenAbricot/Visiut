#include "Models/headers/BackNext.h"
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
    m_index = 0;
    m_currentIndex = 0;
    m_pathName = "";
}

//! Constructeur avec argument 
/*!
	Ce constructeur permet de cr&eacute;er un repertoire temporaire pour la sauvegarde d'images temporaires.
	\param _name est le nom de l'image ouverte.
*/
BackNext::BackNext(const char * _name){
    m_index = 0;
    m_currentIndex = 0;
	//On récupère le nom du fichier et on la met dans un string
	string name = string(_name);
	//On récupère l'extension de l'image
    string extension = name.substr(name.rfind("."), name.size()-1);
	//On récupère le nom de l'image sans l'extension
    name = name.substr(0,name.rfind("."));
	//Si le répertoire temporaire n'existe pas
	if(!ms_dir_cache.exists()){
		qDebug() << "Fichier existe ? : " << !ms_dir_cache.exists();
		//On crée le repertoire temporaire
		qDebug() << ms_dir_cache.mkpath(ms_dir_cache.path());
		qDebug() << ms_dir_cache.mkdir("tmp");
	}
	//On génere le chemin de l'image temporaire
	m_pathName = ms_dir_cache.path().toStdString()+"/tmp/"+name+to_string(m_index)+extension;
}

QDir BackNext::ms_dir_cache = QDir(".visiut3/");

//! M&eacute;thode AddState
/*! 
	Cette m&eacute;thode permet d'ajouter un &eacute;tat, c'est &agrave; dire qu'elle va incr&eacute;menter 
	un compteur qui contiendra le nombre d'images temporaires enregistr&eacute;s sur le disque.
	\param _index est la nouvelle valeur du compteur. Par d&eacutefaut, _index vaut -1.
*/
void BackNext::AddState(int _index){
    if(_index == -1)
		m_index++;
	else
		m_index = _index;
	m_currentIndex = m_index;
    string extension = m_pathName.substr(m_pathName.rfind("."), m_pathName.size()-1);
    m_pathName = m_pathName.substr(0,m_pathName.rfind("."));
	if(m_index <= 9)
		m_pathName = m_pathName.substr(0,m_pathName.size()-1)+to_string(m_index)+extension;
	else
		m_pathName = m_pathName.substr(0, m_pathName.size()-2)+to_string(m_index)+extension;
}

//! M&eacute;thode RemoveLastState
/*!
	Cette m&eacute;thode d&eacute;cr&eacute;mente le nombre d'images enregistr&eacute;s sur le disque.
*/
void BackNext::RemoveLastState(){
	m_currentIndex--;
    RemoveState(m_index-1);
}

//! M&eacute;thode RemoveState
/*!
	Cette m&eacute;thode permet de supprimer un &eacute;tat pr&eacute;cis&eacute; en param&egrave;tre.
	\param _index est un entier qui correspond &agrave; l'image &agrave; supprimer.
*/
//---------------------------On part du principe qu'on enlevera pas plus de 1000 traitements (À améliorer dans l'avenir)------------------------------------------------//
void BackNext::RemoveState(int _index){
    m_index = _index;
    string extension = m_pathName.substr(m_pathName.rfind("."), m_pathName.size()-1);
    m_pathName = m_pathName.substr(0,m_pathName.rfind("."));
    if(m_index < 9)
        m_pathName = m_pathName.substr(0, m_pathName.size()-1)+to_string(m_index)+extension;
    else if(m_index >= 9 && m_index < 100)
        m_pathName = m_pathName.substr(0, m_pathName.size()-2)+to_string(m_index)+extension;
    cout << "Remove "+GetCurrentStatePathName() << endl;

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//! M&eactue;thode RemoveTemporyFile
/*! Supprime le dossier temporaire qui contient les images temporaires */
void BackNext::RemoveTemporyFile(){

	while(m_index > 0){
		QFile::remove(GetCurrentStatePathName().data());
		qDebug() << QString(GetCurrentStatePathName().data());
		RemoveLastState();
	}

	if(ms_dir_cache.exists()){
		ms_dir_cache.rmdir("tmp");
		ms_dir_cache.rmpath(ms_dir_cache.path());
	}
}

//! M&eacute;thode GetCurrentStatePathName
/*!
	\return le chemin de l'image temporaire courante.
*/
string & BackNext::GetCurrentStatePathName(){
    return m_pathName;
}

//! M&eacute;thode GetIndexCurrentStatePathName
/*!
	\return l'index courant, l'id de l'image ouverte (courante)
*/
int BackNext::GetIndexCurrentStatePathName()const{
    return m_currentIndex;
}


string to_string(int _nb){
    stringstream ss;
    ss << _nb;
    return ss.str();
}

