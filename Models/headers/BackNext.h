#ifndef BACKNEXT_H
#define BACKNEXT_H

#include <string>
#include <vector>
#include <QDir>

class BackNext
{
    private:
        std::string m_pathName;
        int m_index;
        int m_currentIndex;
		static QDir ms_dir_cache;
    public:
        BackNext();
        BackNext(const char * _name);
        void AddState(int _index = -1);
        void RemoveLastState();
        void RemoveState(int _index);
		void RemoveTemporyFile();
        std::string & GetCurrentStatePathName();
        int GetIndexCurrentStatePathName()const;
};

std::string to_string(int _nb);

#endif // BACKNEXT_H
